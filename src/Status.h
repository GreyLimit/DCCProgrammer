/*
 * 	Status.h
 *
 * 	Define an enumerated type to be used as a function result
 * 	type allowing a more granular return than success/failure
 * 	(true/false).  The module will require a mechanism to
 * 	facilitate conversion from binary flag to human text.
 */

#ifndef _STATUS_H_
#define _STATUS_H_

/*
 *	Lets capture all those possible status values (errors):
 */
typedef enum {
	SUCCESS			= 0,	/* Always ZERO for simply error checking */
					/* so any error is non-zero (ie true). */

	/*
	 *	Results relating to Configuration Variables.
	 */
	CV_NUMBER_INVALID	= 1,
	CV_ELEMENT_INVALID	= 2,
	CV_VALUE_INVALID	= 3,
	CV_VALUE_OVERWRITE	= 4,
	CV_VALUE_UNDEFINED	= 5,
	/*
	 *	Results relating to Logical Values.
	 */
	LV_NAME_INVALID		= 10,
	LV_NUMBER_INVALID	= 11,
	LV_CASES_INVALID	= 12,
	LV_VALUE_NUMERIC	= 13,
	LV_VALUE_ENUMERATED	= 14,
	LV_VALUE_INVALID	= 15,
	LV_VALUE_INCOMPLETE	= 16,
	LV_INDEX_INVALID	= 17,
	/*
	 *	Input errors
	 */
	INVALID_DIGIT		= 20,
	BASE_INVALID		= 21,
	RANGE_INVALID		= 22,
	/*
	 *	Programming track IO errors
	 */
	DCC_READ_FAILED		= 30,
	DCC_WRITE_FAILED	= 31,
	DCC_RESULT_INVALID	= 32,
	DCC_IO_FAILED		= 33,
	/*
	 *	General operation errors, probably rooted
	 * 	in a coding error.
	 */
	UNDEFINED_ERROR		= 40,
	BUFFER_OVERFLOW		= 41,
	NOT_IMPLEMENTED		= 42
	
} STATUS;


/*
 *	Return textual version of status value.
 */
extern char *explain( STATUS value );

#endif

/*
 *	EOF
 */
