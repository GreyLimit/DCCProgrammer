/*
 * 	Compare.c
 *
 * 	A front end for string comparison so that the program
 * 	can be switch between ignoring caes and being case sensitive.
 */

#include "Options.h"

/*
 *	Here is our routine for comparing text.
 */
int compare( char *a, char *b ) {
	if( option_flags & OPT_IGNORE_CASE ) return( strcasecmp( a, b ));
	return( strcmp( a, b ));
}

extern int compare_n( char *a, char *b, int n ) {
	if( option_flags & OPT_IGNORE_CASE ) return( strncasecmp( a, b, n ));
	return( strncmp( a, b, n ));
}


/*
 * 	EOF
 */
