/*
 * 	Options.h
 *
 * 	The capture and processing of command line arguments.
 */

#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include "OS.h"
#include "Config.h"
#include "Variables.h"


/************************************************************************
 *									*
 *	Option Flags.							*
 *									*
 ************************************************************************/
typedef enum {
	//
	//	Default: no options.
	//
	OPT_NONE		= 00000,
	//
	//	Data display options.
	//
	OPT_VARIABLES		= 000001,	// Just dump valid variable names
	OPT_CONSTANTS		= 000002,	// Access/Modify DCC Generator constants
	OPT_000004		= 000004,	// Unused.
	//
	OPT_READ		= 000010,	// Tell program to operate in read only mode.
	OPT_WRITE		= 000020,	// Tell program to operate in write only mode.
	OPT_DUMP		= 000040,	// Dump out details of data gathered and changes
						// pending.
	OPT_FULL		= 000100,	// Perform a full table dump.
	//
	OPT_IGNORE_CASE		= 000200,	// Enable the case less comparison of text.
	OPT_VERBOSE		= 000400,	// Display everything the program did read.
	OPT_VERY_VERBOSE	= 001000,	// .. also include the set of possible values.
	//
	//	Flags affecting some numeric display information.
	//
	OPT_HEXADECIMAL		= 002000,	// Output partial CV values in Hex
	OPT_OCTAL		= 004000,	// Output partial CV values in Octal
	//
	//	Help and debugging.
	//
	OPT_HELP		= 010000,
	OPT_DEBUG		= 020000,
	OPT_DEBUG_VERBOSE	= 040000
} prog_options;

//
//	Global Flags
//
extern prog_options option_flags;

//
//	Scan program arguments and return the index of the
//	first non-option argument or -ve if there was an issue.
//
extern int scan_flags( int argc, char *argv[]);

#endif

/*
 * 	EOF
 */
