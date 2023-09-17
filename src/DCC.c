/*
 *	The implementation code for the DCC interface.
 */

#include "OS.h"
#include "Const.h"
#include "DCC.h"

/*
 *	set up something to simplify switching between
 *	alternate DCC drivers
 */
#if DCC_PLUS_PLUS_COMPATIBILITY
#define SELECT_ALT(a,b)		b
#elif DCC_GENERATOR_COMPATIBILITY
#define SELECT_ALT(a,b)		a
#else
#error "DCC Compatibility not set."
#endif

/*
 *	Define the maximum  number of DCC arguments we will contemplate.
 */
#define ARG_LIMIT	16

/*
 *	Define the number of milliseconds the device read routine
 *	is prepared to wait for data.
 */
#define POLL_TIMEOUT	2000

/*
 *	Timeout counter to resending command.
 */
#ifndef RETRY_WAIT
#define RETRY_WAIT	8
#endif

/*
 *	Retry limit for whole commands.
 */
#ifndef RETRY_COUNT
#define RETRY_COUNT	2
#endif

/*
 *	How many time do we retry a single bit.
 */
#ifndef BIT_RETRIES
#define BIT_RETRIES	4
#endif

/*
 *	Simple routine to read in a response from the device.
 */
static int read_device( int device, char *buffer, int size ) {
	struct pollfd	pfd;
	char		c;
	int		i,
			l;

	l = 0;
	i = FALSE;
	size--;
	while( TRUE ) {
		pfd.fd = device;
		pfd.events = POLLIN;
		pfd.revents = 0;
		if( poll( &pfd, 1, POLL_TIMEOUT ) != 1 ) {
			/*
			 *	No data received in the time specified, so
			 *	we say that nothing has been returned.
			 */
			return( 0 );
		}
		if( read( device, &c, 1 ) != 1 ) {
			/*
			 *	To get here poll() *must* have returned
			 *	with the device read ready, so we *must*
			 *	be able to read at least a single byte.
			 *
			 *	If not, then something is wrong.
			 *
			 *	Yes, this code is not efficient as it makes
			 *	many, many read() system calls, and in
			 *	a daemon or time critical piece of code this
			 *	would be wrong.  In this program this is
			 *	acceptable for the code simplifications it
			 *	offers.
			 */
			return( ERROR );
		}
		switch( c ) {
			case SELECT_ALT( '[', '<' ): {
				/* Start packet, or RE-start packet */
				l = 0;
				i = TRUE;
				break;
			}
			case SELECT_ALT( ']', '>' ): {
				/* Yeah, end packet if in one. */
				if( i ) {
					buffer[ l ] = EOS;

#ifdef DISPLAY_DCC_COMMS
					printf( "DCC->\"%s\"\n", buffer );
#endif

#ifdef DCC_PLUS_PLUS_COMPATIBILITY
					return( l );
#else
					if( buffer[ 0 ] != 'L' ) return( l );
					l = 0;
					i = FALSE;
#endif
				}
				break;
			}
			default: {
				if( i ) {
					if( l < size ) {
						buffer[ l++ ] = c;
						/*
						 *	We enforce some consistency in the returned
						 *	text by inserting a SPACE after the initial
						 *	result character (so making breaking into a
						 *	series of EOS terminated strings simpler).
						 */
						if( l == 1 ) buffer[ l++ ] = SPACE;
					}
				}
				break;
			}
		}
	}
	return( 0 );
}

/*
 *	Simple routine to break a buffer into a series of EOS terminated values.
 */
static int divide_buffer( char *buffer, int len, char *seps, char **arg, int max ) {
	int	a, b;

	a = 0;
	b = TRUE;
	while( len > 0 ) {
		if( strchr( seps, *buffer ) != NULL ) {
			*buffer = EOS;
			b = TRUE;
		}
		else {
			if( b && ( a < max )) arg[ a++ ] = buffer;
			b = FALSE;
		}
		buffer++;
		len--;
	}

#ifdef DISPLAY_DCC_COMMS
	for( b = 0; b < a; b++ ) printf( "[%d]=\"%s\"\n", b, arg[ b ]);
#endif

	return( a );
}

/*
 *	Send command and wait for a specified reply
 */
static int communication( int device, const char *cmd, int len, char *reply, char *buffer, int size, char **arg, int max ) {
	int	a, l, c;

#ifdef DISPLAY_DCC_COMMS
	printf( "DCC<-\"" );
	for( int i = 0; i < len; i++ ) {
		if( cmd[ i ] < SPACE ) {
			printf( "\\%03o", (int)cmd[ i ]);
		}
		else {
			printf( "%c", cmd[ i ]);
		}
	}
	printf( "\"\n" );
#endif

	if( write( device, cmd, len ) == ERROR ) return( ERROR );
	c = RETRY_WAIT;
	while(( l = read_device( device, buffer, size )) != ERROR ) {
		if( l > 0 ) {
			/*
			 *	Some data to handle
			 */
			if(( a = divide_buffer( buffer, l, SELECT_ALT( " ", " |" ), arg, max )) > 0 ) {
				if( strcmp( arg[ 0 ], reply ) == 0 ) return( a );
			}
		}
		else {
			/*
			 *	Read timed out (no data received), work out if
			 *	we need to try resending command.
			 */
			if( c == 0 ) {
				
#ifdef DISPLAY_DCC_COMMS
				printf( "DCC<-Resend!\n" );
#endif

				if( write( device, cmd, len ) == ERROR ) return( ERROR );
				c = RETRY_WAIT;
			}
			else {
				c--;
			}
		}
	}
	return( ERROR );
}

/*
 *	Turn ON or OFF DCC track power
 */
int turn_on_dcc( int device ) {
	char	buffer[ BUFFER ];
	char	*arg[ ARG_LIMIT ];
	int	count;

	count = RETRY_COUNT;
	while( count-- ) {
		if( communication( device, SELECT_ALT( "[P2]\r", "<1>\r" ), SELECT_ALT( 5, 4 ), SELECT_ALT( "P", "p" ), buffer, BUFFER, arg, ARG_LIMIT ) == 2 ) {
			if( atoi( arg[ 1 ]) == SELECT_ALT( 2, 1 )) return( TRUE );
		}
	}
	return( FALSE );
}

int turn_off_dcc( int device ) {
	char	buffer[ BUFFER ];
	char	*arg[ ARG_LIMIT ];
	int	count;

	count = RETRY_COUNT;
	while( count-- ) {
		if( communication( device, SELECT_ALT( "[P0]\r", "<0>\r" ), SELECT_ALT( 5, 4 ), SELECT_ALT( "P", "p" ), buffer, BUFFER, arg, ARG_LIMIT ) == 2 ) {
			if( atoi( arg[ 1 ]) == 0 ) return( TRUE );
		}
	}
	return( FALSE );
}

/*
 *	Read a specific CV from the device attached to the PROGRAMMING
 * 	TRACK.
 */
#if DCC_PLUS_PLUS_COMPATIBILITY
int dcc_read_cv( int device, int cv ) {
	/*
	 *	For DCC Plus Plus Firmware:
	 *	---------------------------
	 *
	 *	<R CV CALLBACKNUM CALLBACKSUB>
	 *
	 *	reads a Configuration Variable from the decoder of an engine on the programming track
	 *
	 *	CV: the number of the Configuration Variable memory location in the decoder to read from (1-1024)
	 *	CALLBACKNUM: an arbitrary integer (0-32767) that is ignored by the Base Station and is simply echoed
	 *	back in the output - useful for external programs that call this function
	 *	CALLBACKSUB: a second arbitrary integer (0-32767) that is ignored by the Base Station and is simply
	 *	echoed back in the output - useful for external programs (e.g. DCC++ Interface) that call this function
	 *
	 *	returns: <r CALLBACKNUM|CALLBACKSUB|CV VALUE)
	 *
	 *	where VALUE is a number from 0-255 as read from the requested CV, or -1 if read could not be verified
	 *
	 *	Note:	The SPACE between the "<r" and the "CALLBACKNUM" is not present in
	 *		the reply from the DCC++ device.  The read_device() routine assists
	 *		us by inserting one.
	 */
	char	cmd[ BUFFER ],
		buffer[ BUFFER ],
		*arg[ ARG_LIMIT ];
	int	count;

	sprintf( cmd, "<R %d %d 0>\r", cv, cv);
	count = RETRY_COUNT;
	while( count-- ) {
		if( communication( device, cmd, strlen( cmd ), "r", buffer, BUFFER, arg, ARG_LIMIT ) == 4 ) {
			if( atoi( arg[ 1 ]) == cv ) return( atoi( arg[ 3 ]));
		}
	}
	return( ERROR );
}
#endif


/*
 *	Read a specific bit from a specific CV from the device
 *	attached to the PROGRAMMING TRACK.  The value of mask
 * 	should contain only a single set bit.
 */
#if DCC_GENERATOR_COMPATIBILITY
int dcc_read_cv_bit( int device, int cv, int bitno ) {
	/*
	 *	For DCC Generator Firmware
	 *	--------------------------
	 *
	 *	Verify CV bit value (Programming track)
	 *	-------------------------------------
	 *
	 *	Compare the specified CV bit with the supplied
	 *	value, if they are the same, return 1, otherwise
	 *	(or in the case of failure) return 0.
	 *
	 *	[R CV BIT VALUE] -> [R CV BIT VALUE STATE]
	 *
	 *		CV:	Number of CV to set (1-1024)
	 *		BIT:	Bit number (0 LSB - 7 MSB)
	 *		VALUE:	0 or 1
	 *		STATE:	1=Confirmed, 0=Failed
	 */

	char	cmd[ BUFFER ],
		buffer[ BUFFER ],
		*arg[ ARG_LIMIT ];
	int	count;
	bool	is_zero,
		is_one;

	is_zero = FALSE;
	sprintf( cmd, "[R %d %d 0]\r", cv, bitno );
	count = RETRY_COUNT;
	while( count-- ) {
		if( communication( device, cmd, strlen( cmd ), "R", buffer, BUFFER, arg, ARG_LIMIT ) == 5 ) {
			if( atoi( arg[ 3 ]) == cv ) {
				is_zero = ( atoi( arg[ 4 ]) == 1 );
				break;
			}
		}
	}
	is_one = FALSE;
	sprintf( cmd, "[R %d %d 1]\r", cv, bitno );
	count = RETRY_COUNT;
	while( count-- ) {
		if( communication( device, cmd, strlen( cmd ), "R", buffer, BUFFER, arg, ARG_LIMIT ) == 5 ) {
			if( atoi( arg[ 3 ]) == cv ) {
				is_one = ( atoi( arg[ 4 ]) == 1 );
				break;
			}
		}
	}
	if( is_zero == is_one ) return( ERROR );
	return( is_one? 1: 0 );
}
#endif

int dcc_write_cv( int device, int cv, byte value ) {
#if DCC_PLUS_PLUS_COMPATIBILITY
	/*
	 *	For DCC Plus Plus Firmware:
	 *	---------------------------
	 *
	 *	<W CV VALUE CALLBACKNUM CALLBACKSUB>
	 *
	 *	writes, and then verifies, a Configuration Variable to the decoder of an engine on the programming track
	 *
	 *	CV: the number of the Configuration Variable memory location in the decoder to write to (1-1024)
	 *	VALUE: the value to be written to the Configuration Variable memory location (0-255)
	 *	CALLBACKNUM: an arbitrary integer (0-32767) that is ignored by the Base Station and is simply echoed back
	 *	in the output - useful for external programs that call this function
	 *	CALLBACKSUB: a second arbitrary integer (0-32767) that is ignored by the Base Station and is simply echoed
	 *	back in the output - useful for external programs (e.g. DCC++ Interface) that call this function
	 *
	 *	returns: <r CALLBACKNUM|CALLBACKSUB|CV Value)
	 *
	 *	where VALUE is a number from 0-255 as read from the requested CV, or -1 if verification read fails
	 *
	 *	Note:	The SPACE between the "<r" and the "CALLBACKNUM" is not present in
	 *		the reply from the DCC++ device.  The read_device() routine assists
	 *		us by inserting one.
	 */

	char	cmd[ BUFFER ],
		buffer[ BUFFER ],
		*arg[ ARG_LIMIT ];
	int	count;

	sprintf( cmd, "<W %d %d %d 0>\r", cv, value, cv );
	count = RETRY_COUNT;
	while( count-- ) {
		if( communication( device, cmd, strlen( cmd ), "r", buffer, BUFFER, arg, ARG_LIMIT ) == 5 ) {
			if( atoi( arg[ 3 ]) == cv ) return( atoi( arg[ 4 ]));
		}
	}
	return( ERROR );

#elif DCC_GENERATOR_COMPATIBILITY
	/*
	 *	For DCC Generator Firmware
	 *	--------------------------
	 *
	 *	Set CV value (Programming track)
	 *	--------------------------------
	 *
	 *	[S CV VALUE] -> [S CV VALUE STATE]
	 *
	 *		CV:	Number of CV to set (1-1024)
	 *		VALUE:	8 bit value to apply (0-255)
	 *		STATE:	1=Confirmed, 0=Failed
	 */

	char	cmd[ BUFFER ],
		buffer[ BUFFER ],
		*arg[ ARG_LIMIT ];
	int	count;

	sprintf( cmd, "[S%d %d]\r", cv, value );
	count = RETRY_COUNT;
	while( count-- ) {
		if( communication( device, cmd, strlen( cmd ), "S", buffer, BUFFER, arg, ARG_LIMIT ) == 4 ) {
			if(( atoi( arg[ 1 ]) == cv )&&( atoi( arg[ 2 ]) == value )) {
				if( atoi( arg[ 3 ]) == 1 ) {
					//
					//	Should verify content now.
					//
					return( value );
				}
			}
		}
	}
	return( ERROR );
#else
#error "DCC Compatibility not specified."
#endif
}

	/*
	 *
	 *	Verify CV value (Programming track)
	 *	-----------------------------------
	 *
	 *	[V CV VALUE] -> [V CV VALUE STATE]
	 *
	 *		CV:	Number of CV to set (1-1024)
	 *		VALUE:	8 bit value to apply (0-255)
	 *		STATE:	1=Confirmed, 0=Failed
	 */


/*
 *	Write a sub-set of bit in a specific CV to the device
 *	attached to the PROGRAMMING TRACK.
 */
int dcc_write_masked_cv( int device, int cv, byte mask, byte value ) {
#if DCC_PLUS_PLUS_COMPATIBILITY
	/*
	 *	For DCC Plus Plus Firmware:
	 *	---------------------------
	 *
	 *	<b ... >
	 *
	 *	The DCC++ Arduino Sketch would seem to include this ability
	 *	but it is not clear why it includes a CAB id in the command.
	 *
	 *	For the moment I will ignore this option and fail the call.
	 */

	return( ERROR );

#elif DCC_GENERATOR_COMPATIBILITY
	/*
	 *	Set CV bit value (Programming track)
	 *	------------------------------------
	 *
	 *	Set the specified CV bit with the supplied
	 *	value.
	 *
	 *	[U CV BIT VALUE] -> [U CV BIT VALUE STATE]
	 *
	 *		CV:	Number of CV to set (1-1024)
	 *		BIT:	Bit number (0 LSB - 7 MSB)
	 *		VALUE:	0 or 1
	 *		STATE:	1=Confirmed, 0=Failed
	 *
	 */
	char	cmd[ BUFFER ],
		buffer[ BUFFER ],
		*arg[ ARG_LIMIT ];
	int	count,
		b, v, q;

	q = 0;
	for( b = 0; b < 8; b++ ) {
		if( mask & ( 1 << b )) {
			v = ( value & ( 1 << b ))? 1: 0;
			q++;
			sprintf( cmd, "[U%d %d %d]\r", cv, b, v );
			count = RETRY_COUNT;
			while( count-- ) {
				if( communication( device, cmd, strlen( cmd ), "U", buffer, BUFFER, arg, ARG_LIMIT ) == 5 ) {
					if(( atoi( arg[ 1 ]) == cv )&&( atoi( arg[ 2 ]) == b )&&( atoi( arg[ 3 ]) == v )) {
						if( atoi( arg[ 4 ]) == 1 ) {
							q--;
							break;
						}
					}
				}
			}
		}
	}
	return( q? ERROR: value );
#else
#error "DCC Compatibility not specified."
#endif
}


/*
 *	Routines used to read a DCC generators internal parameters
 * 	(called "Q" values as these are accessed through the "Q"
 * 	command).
 */
#if DCC_GENERATOR_COMPATIBILITY
int get_q_count( int dcc ) {
	char	cmd[ BUFFER ],
		buffer[ BUFFER ],
		*arg[ ARG_LIMIT ];

	assert( dcc != ERROR );

	sprintf( cmd, "[Q]\r" );
	if( communication( dcc, cmd, strlen( cmd ), "Q", buffer, BUFFER, arg, ARG_LIMIT ) == 2 ) return( atoi( arg[ 1 ]));
	return( ERROR );
}

bool get_q_variable( int dcc, int q, int *value, char *buffer, int len ) {
	char	cmd[ BUFFER ],
		result[ BUFFER ],
		*arg[ ARG_LIMIT ];

	assert( dcc != ERROR );
	assert( value != NULL );
	assert( buffer != NULL );
	assert( len > 0 );

	sprintf( cmd, "[Q%d]\r", q );
	if( communication( dcc, cmd, strlen( cmd ), "Q", result, BUFFER, arg, ARG_LIMIT ) == 4 ) {
		*value = atoi( arg[ 2 ]);
		strncpy( buffer, arg[ 3 ], len );
		return( TRUE );
	}
	return( FALSE );
}

bool set_q_variable( int dcc, int q, int v ) {
	return( FALSE );
}

#endif


/*
 *	EOF
 */
