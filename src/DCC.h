/*
 *	Set of routines to front end the DCC++ device.
 */

#ifndef _DCC_H_
#define _DCC_H_

#include "OS.h"
#include "Config.h"

/*
 *	Turn ON/OFF track power.
 */
extern int turn_on_dcc( int device );
extern int turn_off_dcc( int device );

/*
 *	Read a specific CV from the device attached to the PROGRAMMING
 * 	TRACK.
 */
#if DCC_PLUS_PLUS_COMPATIBILITY
extern int dcc_read_cv( int device, int cv );
#endif

/*
 *	Read a specific bit from a specific CV from the device
 *	attached to the PROGRAMMING TRACK.  The value of mask
 * 	should contain only a single set bit.
 */
#if DCC_GENERATOR_COMPATIBILITY
extern int dcc_read_cv_bit( int device, int cv, int bitno );
#endif

/*
 *	Write a specific CV to the device attached to the
 *	PROGRAMMING TRACK.
 */
extern int dcc_write_cv( int device, int cv, byte value );

/*
 *	Write a sub-set of bit in a specific CV to the device
 *	attached to the PROGRAMMING TRACK.
 */
extern int dcc_write_masked_cv( int device, int cv, byte mask, byte value );

/*
 *	Routines used to read a DCC generators internal parameters
 * 	(called "Q" values as these are accessed through the "Q"
 * 	command).
 */
#if DCC_GENERATOR_COMPATIBILITY
extern int get_q_count( int dcc );
extern bool get_q_variable( int dcc, int q, int *value, char *buffer, int len );
extern bool set_q_variable( int dcc, int q, int v );
#endif

#endif

/*
 *	EOF
 */
