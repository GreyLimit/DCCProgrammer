/*
 *	Config.h
 *
 * 	Declare parameterised constants which configure which features
 *	are enabled and how the program operates.
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

/*
 *	DCC Plus Plus Compatibility
 *	---------------------------
 *
 *	To implement compatibility with the Arduino
 *	DCC Plus Plus firmware, located at:
 *
 *		https://github.com/DccPlusPlus/BaseStation
 *
 *	You should define DCC_PLUS_PLUS_COMPATIBILITY as 1.
 */
#define DCC_PLUS_PLUS_COMPATIBILITY	0

/*
 *	Define DCC_GENERATOR_COMPATIBILITY as 1 to enable compatibility
 * 	with the "Blue Boox" DCC Generator solution developed by
 *	Jeff Penfold.
 */
#define DCC_GENERATOR_COMPATIBILITY	1

/*
 *	Sanity check - only one of the above compatibility modes
 * 	can be enabled at once.
 */
#if ( DCC_PLUS_PLUS_COMPATIBILITY + DCC_GENERATOR_COMPATIBILITY ) != 1
#error "Only one of DCC_PLUS_PLUS_COMPATIBILITY or DCC_GENERATOR_COMPATIBILITY can be set to 1"
#endif

/*
 *	Define how often we try to read the CV values
 *	before giving up.
 */
#define RETRY_COUNT	2

/*
 *	Define the maximum number of binary data items which
 *	are combined to make a single structured value.
 */
#define BINARY_DATA_LIMIT	28

/*
 *	Define the maximum number of test cases which can be
 *	associated with a single logical value.
 */
#define TEST_CASE_LIMIT	8

/*
 *	Define the maximum number of enumeration values supported.
 */
#define ENUMERATIONS_LIMIT	256



#endif

/*
 * 	EOF
 */
