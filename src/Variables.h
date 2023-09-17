/*
 * 	Variables.h
 *
 * 	Define all the CV configuration data the program uses
 *	to understand what the CVs actually represent.
 */

#ifndef _VARIABLES_H_
#define _VARIABLES_H_

#include "OS.h"
#include "Const.h"
#include "Config.h"
#include "Status.h"


/************************************************************************
 *									*
 *	DCC Configuration Data.						*
 *									*
 ************************************************************************/

/*
 *	The following structure and variable definition
 *	describes the CV structure (as specified by
 *	the DCCwiki web site) and is used by the program
 *	to read and write logical data from or to a DCC
 *	decoder.
 */

/*
 *	Capture how a value (or part of a larger value) is
 *	encoded in a single CV
 */
typedef struct {
	int		cv,				/* Which CV */
			bits,				/* How many bits */
			lsb;				/* Least significant bit */
} BINARY_DATA;

/*
 *	Capture a complete binary value across one, or more,
 *	CV values.
 */
typedef struct {
	char		*name;				/* What we call this value */
	bool		combined;			/* True if the data is a single value */
	int		elements;			/* How many data items are required. */
	BINARY_DATA	data[ BINARY_DATA_LIMIT ];	/* Details about where the value is */
							/* kept, MSB first, LSB last */
} BINARY_VALUE;

/*
 *	Define a Logical condition that can be tested
 *	against CV values, or asserted INTO the CV values.
 */
typedef struct {
	char		*test;				/* The name of this test */
	int		value;				/* The value to test for. */
	bool		negated;			/* Negate the result. */
	int		reset;				/* Value to apply to set this case */
	BINARY_VALUE	*where;				/* How to find it */
} BINARY_CASE;

/*
 *	Define a system for capturing enumerated values
 */
typedef struct {
	char		*name;
	int		value;
} ENUMERATION;

typedef struct {
	char		*name;				/* Name of the enumeration */
	bool		exclusive;			/* Exclusive: only 1 valid at a time */
	int		values;				/* Number of enumerations */
	ENUMERATION	value[ ENUMERATIONS_LIMIT ];	/* Individual enumerations. */
} ENUMERATIONS;

/*
 *	Define a Logical value and details of how
 *	it is interpreted.
 */
typedef struct {
	char		*name;				/* The name of this logical value */
	int		asserts;			/* How many test cases are there? */
	BINARY_CASE	*test[ TEST_CASE_LIMIT ];	/* Set of tests. */
	ENUMERATIONS	*values;			/* Set of enumerations, NULL if not used */
	bool		read_write;			/* True/False */
	int		minimum,			/* if no enumerations, minimum */
			maximum;			/* and maximum values. */
	BINARY_VALUE	*value;				/* Where and how the value is kept. */
} LOGICAL_VALUE;


/*
 *	Define the functional access routines.
 */

/*
 *	Locate a variable by name or abstract index number (0..N)
 */
extern LOGICAL_VALUE *find_variable_by_name( char *name );
extern LOGICAL_VALUE *find_variable_by_number( int number );

/*
 *	Read the content of a variable from the decoder
 * 	on the programming track.
 */
extern STATUS read_variable( int dcc, LOGICAL_VALUE *func );

/*
 *	Return the name of the variable.
 */
extern char *get_variable_name( LOGICAL_VALUE *func );

/*
 *	Can the variable be updated?  Is it read/write?
 */
extern bool is_variable_updatable( LOGICAL_VALUE *func );

/*
 *	Is the variable an enumerated type?  This has an impact
 * 	on which variable read/write routines should be used
 * 	when reading or modifying its content.
 */
extern bool is_variable_enumerated( LOGICAL_VALUE *func );

/*
 *	Return the number of elements a logical value contains
 * 	(ie, "Is this an array?")  All non-array values return 1
 * 	and are accessed as element 0.  Arrays return a value N
 * 	(where N greater than 1) and are accessed with element
 * 	numbers 0 to N-1.
 */
extern int get_variable_elements( LOGICAL_VALUE *func );

/*
 *	Read and write routines provide structured access to
 * 	the raw CV values.
 */
extern STATUS read_int_variable( LOGICAL_VALUE *func, int element, int *value );
extern STATUS read_enum_variable( LOGICAL_VALUE *func, int element, char *value, int size );
extern STATUS write_int_variable( LOGICAL_VALUE *func, int element, int value );
extern STATUS write_enum_variable( LOGICAL_VALUE *func, int element, char *value );

/*
 *	Dump the Variable database to the provided stream.
 */
extern void dump_variables_database( FILE *stream );

#endif

/*
 *	EOF
 */
