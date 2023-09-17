/*
 * 	Compare.h
 *
 * 	A front end for string comparison so that the program
 * 	can be switch between ignoring caes and being case sensitive.
 */

#ifndef _COMPARE_H_
#define _COMPARE_H_

/*
 *	Here is our routine for comparing text.
 */
extern int compare( char *a, char *b );
extern int compare_n( char *a, char *b, int n );

#endif


/*
 * 	EOF
 */
