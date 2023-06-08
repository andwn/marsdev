## Migrating a project to Marsdev

### In General

- The toolchain path variable is MARSDEV, default /opt/toolchains/mars.
- From there, stuff related to M68000 (MD CPU) is in m68k-elf, for SH-2 (32X CPU) sh-elf.

Marsdev was originally forked from Gendev, but there are some paths that may be a level up or down from what they were.
Compare the paths in your Makefile with those in an example project and fix them accordingly.


### From SGDK (Official Windows releases)

SGDK projects are expected to work without changes and can be compiled in the usual way.

If you get file/path not found errors, make sure the GDK environment variable is set,
and note that paths on most Unix filesystems are case-sensitive.


### From an old dated release to v1.0.0-rc1 or later

The default installation path has changed from `${HOME}/mars` to `/opt/toolchain/mars`.
In addition, tools that were previously installed to `mars/bin` are now installed to `mars/m68k-elf/bin` instead.
You may need to update these paths in your project's Makefile.

The below applies only to SGDK projects:

SGDK integration had some annoying bugs and the following changes were made,
both to resolve those bugs, and make maintaining the integration easier:

- SGDK's built in Makefiles are now used with minimal changes instead of a completely custom one.
- SGDK `bin`, `include` and `lib` paths are moved into `m68k-elf` instead of being at the root.
- A GDK variable is set to the path `$MARSDEV/m68k-elf`.

In the best case scenario, you would only have to do the following:

1. Replace your Makefile with the one from the SGDK example project
2. Delete `sega.s`, and make sure `rom_head.c` is in `src/boot` (create if it doesn't exist).

Note that the new Makefile is just a wrapper that runs SGDK's `makefile.gen`.
