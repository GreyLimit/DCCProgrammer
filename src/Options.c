/*
 * 	Options.c
 *
 * 	The capture and processing of command line arguments.
 */

#include "Options.h"

//
//	Global Flags
//
prog_options option_flags = OPT_NONE;

/************************************************************************
 *									*
 *	Program options.						*
 *									*
 ************************************************************************/

//
//	The program flags:
//
typedef struct {
	 char		*flag,
			*usage;
	 prog_options	opt;
} option_flag;

static option_flag flags[] = {
	{ "--variables",	"Display variable definitions table",		OPT_VARIABLES		},
	{ "--constants",	"Display the DCC Generator parameters",		OPT_CONSTANTS		},
	{ "--read",		"Extract data from the decoder chip",		OPT_READ		},
	{ "--write",		"Write changes back to the decoder chip",	OPT_WRITE		},
	{ "--dump",		"Display details of data and updates",		OPT_DUMP		},
	{ "--full",		"Extend dump to include unset data",		OPT_FULL		},
	{ "--ignore-case",	"Ignore case when comparing text",		OPT_IGNORE_CASE		},
	{ "--hex",		"Display partial CVs in hexadecimal",		OPT_HEXADECIMAL		},
	{ "--oct",		"Display partial CVs in octal",			OPT_OCTAL		},
	{ "--verbose",		"Display content information",			OPT_VERBOSE		},
	{ "--very-verbose",	"Display content context information",		OPT_VERY_VERBOSE	},
	{ "--help",		"Display usage help",				OPT_HELP		},
	{ "--debug",		"Display debugging information",		OPT_DEBUG		},
	{ "--debug-verbose",	"Display extended debugging information",	OPT_DEBUG_VERBOSE	},
	{ NULL }
};

//
//	Scan program arguments and return the index of the
//	first non-option argument or -ve if there was an issue.
//
int scan_flags( int argc, char *argv[]) {
	int		i;
	option_flag	*o;

	for( i = 1; i < argc; i++ ) {
		if( strncmp( argv[ i ], "--", 2 ) != 0 ) break;
		for( o = flags; o->flag != NULL; o++ ) {
			if( strcmp( argv[ i ], o->flag ) == 0 ) {
				option_flags |= o->opt;
				break;
			}
		}
		if( o->flag == NULL ) {
			printf( "Unrecognised flag '%s'\n", argv[ i ]);
			return( -i );
		}
	}
	if( option_flags & OPT_HELP ) {
		printf( "Usage:\n" );
		printf( "\t%s [{options}] {dcc device}? {variable}(={value})? cv{number}(={value}/{mask})?\n\n", argv[ 0 ]);
		for( o = flags; o->flag != NULL; o++ ) {
			printf( "\t%-20s%s\n", o->flag, o->usage );
		}
		printf( "\nThis version compiled to support the \"%s\" system.\n", (DCC_GENERATOR_COMPATIBILITY? "DCC Generator": "Arduino DCC++" ));
		printf( "\nAll DCC IO is directed to the Programming Track only.\n" );
		printf( "Variable assignment in decimal or enumerated values.\n" );
		printf( "CV{number} assignment in hexadecimal(h), decimal, octal(o)\n" );
		printf( "or binary(b) where numbers are prefixed by the letter\n" );
		printf( "indicated when not decimal.\n" );
	}
	return( i );
}


/*
 * 	EOF
 */
