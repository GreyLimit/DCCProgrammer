/*
 * 	Q.c
 *
 * 	Define the working area where the Q values are
 * 	coordinated.
 */

#include "Q.h"
#include "Memory.h"
#include "DCC.h"

/************************************************************************
 *									*
 *	The Generator Q Constants are captured here			*
 *									*
 ************************************************************************/
/*
 *	Define an arbitrary limit on the number of valid q constant values
 */ 
#define Q_MAXMUMIM_CONSTANTS	100

/*
 *	A structure used to keep track of a single Q variable current
 * 	and/or future value.
 */
typedef struct _q_variable {
	int			number;
	char			*name;
	bool			have_base,
				have_future;
	int			base,
				future;
	struct _q_variable	*next;
} q_variable;

/*
 *	Here we keep track of the total number of Q variables.  This
 *	is set to ERROR at initialisation.
 */
static int total_q_variables = ERROR;

/*
 *	This will be where the Q variables are kept.
 */
static q_variable *q_root = NULL;



/*
 *	Find a q record.
 */
static q_variable *find_q( int q ) {
	for( q_variable *p = q_root; p; p = p->next ) {
		if( p->number == q ) return( p );
	}
	return( NULL );
}

/*
 *	DO we have a copy of s specified Q variable?
 */
bool have_q_constant( int q ) {
	return( find_q( q ) != NULL );
}

STATUS read_q_constant( int dcc, int q ) {
	char		buffer[ BUFFER ];
	int		v;
	q_variable	*p;

	if( dcc == ERROR ) return( DCC_IO_FAILED );
	if(( p = find_q( q ))) return( SUCCESS );
	if( total_q_variables == ERROR ) {
		int t = get_q_count( dcc );
		if(( t < 0 )||( t > Q_MAXMUMIM_CONSTANTS )) return( RANGE_INVALID );
		total_q_variables = t;
	}
	if(( q < 1 )||( q >= total_q_variables )) return( RANGE_INVALID );
	if( !get_q_variable( dcc, q, &v, buffer, BUFFER )) return( DCC_RESULT_INVALID );
	p = NEW( q_variable );
	p->number = q;
	p->have_base = TRUE;
	p->base = v;
	p->name = STRDUP( buffer );
	p->have_future = FALSE;
	p->future = ERROR;
	p->next = q_root;
	q_root = p;
	return( SUCCESS );
}


/*
 *	Displaying the Q Constants will also initialise all the
 *	associated data structure above.  Though this is not
 * 	required for other routines to work.
 */
STATUS display_q_constants( int dcc ) {
	STATUS		ret;
	int		q;
	q_variable	*p;

	if( dcc == ERROR ) return( DCC_IO_FAILED );
	
	assert( total_q_variables == ERROR );
	assert( q_root == NULL );

	/*
	 *	Start by getting total Q variables available.
	 */
	q = get_q_count( dcc );
	if(( q < 0 )||( q > Q_MAXMUMIM_CONSTANTS )) return( RANGE_INVALID );
	total_q_variables = q;
	for( q = 0; q < total_q_variables; q++ ) {
		if(( ret = read_q_constant( dcc, q ))) return( ret );
		if(( p = find_q( q ))) printf( "q%d = %d (%s)\n", p->number, p->base, p->name );
	}
	return( SUCCESS );
}

STATUS read_q( int q, int *value ) {
	q_variable	*p;

	if(( p = find_q( q )) == NULL ) return( RANGE_INVALID );
	if( p->have_future ) {
		*value = p->future;
	}
	else {
		if( p->have_base ) {
			*value = p->base;
		}
		else {
			return( UNDEFINED_ERROR );
		}
	}
	return( SUCCESS );
}

STATUS write_q( int q, int value ) {
	q_variable	*p;

	if(( p = find_q( q )) == NULL ) return( RANGE_INVALID );
	p->have_future = TRUE;
	p->future = value;
	return( SUCCESS );
}

STATUS write_q_constant( int dcc, int q ) {
	q_variable	*p;

	if( dcc == ERROR ) return( DCC_IO_FAILED );
	if(( p = find_q( q )) == NULL ) return( RANGE_INVALID );
	if( p->have_future ) if( !set_q_variable( dcc, q, p->future )) return( DCC_IO_FAILED );
	return( SUCCESS );
}

/*
 * 	EOF
 */
