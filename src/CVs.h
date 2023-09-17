/*
 * 	CVs.h
 *
 * 	Define the working area where the CV values are
 * 	coordinated.
 */

#ifndef _CVS_H_
#define _CVS_H_

#include "OS.h"
#include "Status.h"
#include "Const.h"
#include "Config.h"

/************************************************************************
 *									*
 *	The Control Variables are captured in the following		*
 *	structures and code.						*
 *									*
 ************************************************************************/
/*
 *	Define the number of CVs we will manage.
 *
 *	CVs are numbered from 1 to 1024 (defined below).
 */
#define MINIMUM_CV_NUMBER	1
#define MAXIMUM_CV_NUMBER	1024

/*
 *	The actual number of CVs we will handle.
 */
#define TOTAL_CV_COUNT		(1+(MAXIMUM_CV_NUMBER-MINIMUM_CV_NUMBER))


/*
 *	Initialise the CV table as empty with no data from a decoder.
 */
extern void empty_cv_table( void );

/*
 *	The CV access routines offer "alternative" views into the data.
 * 
 *	Routine names "base_" read and write purely to the data as read
 *	from the decoder.
 *
 *	Routine names "final_" read and write the CV values "through"
 * 	the "future value" data set providing the ability to set what
 * 	the CV values will look like.
 */

/*
 *	Extract CV value from decoder on the programming track
 */
extern STATUS read_cv( int dcc, int cv, byte mask );

/*
 * 	Read and write whole (or part) CV values.
 *
 *	The value of "mask" indicates (where bits are 1) which of the
 *	value bits are pertinent.
 *
 * 	Data (either base or final) can only be written once; an attempt
 * 	to over-write it is considered an error.
 */
extern STATUS base_read_cv( int cv, byte *mask, byte *value );
extern STATUS final_read_cv( int cv, byte *mask, byte *value );
extern STATUS final_write_cv( int cv, byte mask, byte value );

/*
 * 	This final routine provides the "delta" information between
 * 	the base data provided and the final data desired.  This is
 *	the bit mask of bits that need changing and their new values.
 */
extern STATUS get_cv_delta( int cv, byte *mask, byte *value );

#endif

/*
 * 	EOF
 */
