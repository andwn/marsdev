/*
 * resgen - Generates an asm source file to quickly include files into a MegaDrive ROM,
 * because writing a bunch of incbins & headers for content is tedious as heck!
 * 
 * Compile & use:
 * gcc resgen.c -o resgen
 * ./resgen [options] <file [more files...]> <output file>
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRLEN 128

enum { FALSE, TRUE };

enum { ST_GAS, ST_VASM };

int main(int argc, char *argv[]) {
	// Options
	int label_align = 2;
	int dma_align = FALSE;
	//int test_input = TRUE;
	int create_header = TRUE;
	int syntax = ST_GAS;
	char head_type[MAX_STRLEN] = "uint8_t";
	// Parse options
	if(argc < 3) {
		printf("Usage: resgen [options] <file [more files...]> <output file>\n");
		return EXIT_SUCCESS;
	}
	int arg;
	for(arg = 1; arg < argc - 2; arg++) {
		if(argv[arg][0] == '-') {
			switch(argv[arg][1]) {
				case 'a': // Custom per-label align, default is 2
				// If set to 0 or 1, no align line is added
				label_align = atoi(&argv[arg][2]);
				break;
				case 'd': // Align whole file to 0x10000, for DMA
				dma_align = TRUE;
				break;
				//case 'i': // Don't test if input files exist
				//test_input = FALSE;
				//break;
				case 'n': // Don't create a C header file
				create_header = FALSE;
				break;
				case 't': // Change the type of the header variable, default uint8_t
				sprintf(head_type, "%s", &argv[arg][2]);
				break;
				case 'v': // Use vasm instead of gas syntax
				syntax = ST_VASM;
				break;
				default: printf("Unknown arg: '%s'\n", argv[arg]);
			}
		} else {
			break;
		}
	}
	// Output files
	char out_s_name[MAX_STRLEN], out_h_name[MAX_STRLEN];
	sprintf(out_s_name, "%s.s", argv[argc-1]);
	sprintf(out_h_name, "%s.h", argv[argc-1]);
	FILE *out_s = fopen(out_s_name, "wb");
	if(!out_s) {
		printf("Failed to create asm file '%s'\n", out_s_name);
		return EXIT_FAILURE;
	}
	FILE *out_h;
	if(create_header) {
		out_h = fopen(out_h_name, "wb");
		if(!out_h) {
			printf("Failed to create header file '%s'\n", out_h_name);
			return EXIT_FAILURE;
		}
	}
	if(dma_align) {
		fprintf(out_s, "\t.align 0x10000 /* To avoid DMA address wrapping */\n\n");
	}
	// Input files
	if(argc - arg < 2) {
		printf("Usage: resgen [options] <file [more files...]> <output file>\n");
		return EXIT_SUCCESS;
	}
	for(; arg < argc - 1; arg++) {
		int in_size = 0;
		//if(test_input) {
			FILE *in = fopen(argv[arg], "rb");
			if(!in) {
				printf("Failed to open input file '%s'\n", argv[arg]);
				continue;
			}
			fseek(in, 0, SEEK_END);
			in_size = ftell(in);
			fclose(in);
		//}
		// Clean out bad characters from the filename to create our label/variable
		char var_name[MAX_STRLEN];
		strcpy(var_name, argv[arg]);
		for(int i = 0; i < strlen(var_name); i++) {
			if(var_name[i] == '/' || var_name[i] == '\\') var_name[i] = '_';
			if(var_name[i] == '-' || var_name[i] == '\'') var_name[i] = '_';
			if(var_name[i] == '(' || var_name[i] == ')') var_name[i] = '_';
			if(var_name[i] == '[' || var_name[i] == ']') var_name[i] = '_';
			if(var_name[i] == '.') {
				var_name[i] = '\0';
				break;
			}
		}
		// Add global label with incbin to asm source to embed file in rom
		if(syntax == ST_GAS) {
			fprintf(out_s, "\t.globl %s\n", var_name);
			if(label_align > 1) fprintf(out_s, "\t.align %d\n", label_align);
			fprintf(out_s, "%s:\n", var_name);
			fprintf(out_s, "\t.incbin \"%s\"\n\n", argv[arg]);
		} else if(syntax == ST_VASM) {
			fprintf(out_s, "\tpublic _%s\n", var_name);
			if(label_align > 1) fprintf(out_s, "\talign %d\n", label_align);
			fprintf(out_s, "_%s:\n", var_name);
			fprintf(out_s, "\tincbin \"%s\"\n\n", argv[arg]);
		}
		// Add declaration to header so C code can use it
		if(create_header) {
			fprintf(out_h, "extern const %s %s[%d];\n", head_type, var_name, in_size);
		}
	}
	
	fclose(out_s);
	if(create_header) fclose(out_h);
	
	return EXIT_SUCCESS;
}
