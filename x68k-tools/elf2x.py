#!/usr/bin/env python3

import sys
import os
import struct
from elftools.elf.elffile import ELFFile
from elftools.elf.relocation import RelocationSection

STACK_SIZE = 64*(2**10)

packulong = lambda x: struct.pack('>I', x)
packuword = lambda x: struct.pack('>H', x)


infile = sys.argv[1]
in_name, in_ext = os.path.splitext(infile)
outfile = sys.argv[2]

with open(sys.argv[1], 'rb') as f:
    elffile = ELFFile(f)

    entrypoint = elffile.header['e_entry']
        
    text = elffile.get_section_by_name('.text')
    text_vals = text.data()

    data = elffile.get_section_by_name('.data')
    if data != None:
        data_vals = data.data()
    else:
        data_vals = b''

    bss = elffile.get_section_by_name('.bss')
    if bss != None:
        bss_size = bss.data_size
    else:
        bss_size = 0

    reloc_table = b''

    hasTextReloc = False
    hasDataReloc = False
    for section in elffile.iter_sections():
        if isinstance(section, RelocationSection):
            if section.name == '.rela.text':
                hasTextReloc = True
            elif section.name == '.rela.data':
                hasDataReloc = True

    sec_names = []
    if hasTextReloc:
        sec_names.append('.rela.text')
    if hasDataReloc:
        sec_names.append('.rela.data')

    # find relocations
    reloc_address = 0

    for name in sec_names:
        section = elffile.get_section_by_name(name)
        #print(f'{section.name}')
        symbol_table = elffile.get_section(section['sh_link'])
        relocs = []
        for relocation in section.iter_relocations():
            symbol = symbol_table.get_symbol(relocation['r_info_sym'])
            offset = relocation['r_offset']
            assert(offset % 2 == 0)
            relocs.append((symbol, offset))

        relocs.sort(key=lambda x: x[1])
        for r in relocs:
            symbol = r[0]
            offset = r[1]
            #print("name: %s offset: 0x%x" % (symbol.name, offset))
            delta = offset-reloc_address
            #print("new target: 0x%x" % delta)
            if delta < 2**16:
                reloc_table += packuword(delta)
                reloc_address += delta
            else:
                reloc_table += packuword(1)
                reloc_table += packulong(delta)
                reloc_address += delta

text_len = len(text_vals)
data_len = len(data_vals)
reloc_len = len(reloc_table)

X_magic = b'HU'
with open(outfile, 'wb') as f:
    f.write(X_magic + b'\0\0' + packulong(0) + packulong(entrypoint) +
            packulong(text_len) + packulong(data_len) +
            packulong(STACK_SIZE + bss_size) +
            packulong(reloc_len) + packulong(0) +
            b'\0'*32 + text_vals + data_vals + reloc_table)
