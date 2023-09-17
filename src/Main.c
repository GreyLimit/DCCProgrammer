/*
 *  	This is a Linux command line utility for
 *	reading and writing the DCC CV variables
 *	of a decoder attached to the programming
 *	track of a DCC++ controller module.
 */

#include "OS.h"
#include "Const.h"
#include "Config.h"
#include "Serial.h"
#include "Variables.h"
#include "CVs.h"
#include "Q.h"
#include "DCC.h"
#include "Options.h"
#include "Compare.h"


/************************************************************************
 *									*
 *	Program code follows.						*
 *									*
 ************************************************************************/

/*
 *	Define simple binary to human digit array.
 */
static char *conversion = "0123456789ABCDEF";

/*
 *	Generate a "bit" wise view of a byte value
 */
static void display_number( byte value, char buffer[ NUMBER_BUFFER ]) {
	char	stack[ NUMBER_BUFFER ],
		prefix;
	int	top, shift, mask, fill;

	top = 0;
	if( option_flags & OPT_OCTAL ) {
		prefix = OCTAL_PREFIX;
		shift = 3;
		mask = 7;
	}
	else {
		if( option_flags & OPT_HEXADECIMAL ) {
			prefix = HEX_PREFIX;
			shift = 4;
			mask = 15;
		}
		else {
			prefix = BINARY_PREFIX;
			shift = 1;
			mask = 1;
		}
	}
	if( value ) {
		while( value ) {
			stack[ top++ ] = conversion[ value & mask ];
			value >>= shift;
		}
	}
	else {
		stack[ top++ ] = '0';
	}
	fill = 0;
	buffer[ fill++ ] = prefix;
	while( top ) buffer[ fill++ ] = stack[ --top ];
	buffer[ fill ] = EOS;
}

/*
 *	Step through all the logical values and display the current
 *	settings.
 */
static STATUS dump_cv_table( FILE *stream, bool full ) {
	STATUS		ret;
	LOGICAL_VALUE	*look;
	byte		m, v;
	int		num, elements, val;
	bool		enumerated;
	char		buffer[ TEXT_BUFFER ];

	fprintf( stream, "Decoder CVs\n" );
	fprintf( stream, "===========\n" );
	for( int i = 1; i <= MAXIMUM_CV_NUMBER; i++ ) {
		if(( ret = base_read_cv( i, &m, &v ))) return( ret );
		switch( m ) {
			case 0: break;
			case 0xff: {
				fprintf( stream, "\tcv%d = %d\n", i, (int)v );
				break;
			}
			default: {
				char	b[ NUMBER_BUFFER ];

				display_number( v, b );
				fprintf( stream, "\tcv%d = %d(%s", i, (int)v, b );
				display_number( m, b );
				fprintf( stream, "%c%s)\n", MASK_SEPARATOR, b );
				break;
			}
		}
	}
	fprintf( stream, "Decoder Functions\n" );
	fprintf( stream, "=================\n" );
	num = 0;
	while(( look = find_variable_by_number( num++ ))) {
		elements = get_variable_elements( look );
		enumerated = is_variable_enumerated( look );
		for( int e = 0; e < elements; e++ ) {
			if( enumerated ) {
				ret = read_enum_variable( look, e, buffer, TEXT_BUFFER );
			}
			else {
				ret = read_int_variable( look, e, &val );
				snprintf( buffer, TEXT_BUFFER, "%d", val );
			}
			if(( ret == LV_CASES_INVALID )||( ret == LV_VALUE_INCOMPLETE )) {
				if( option_flags & OPT_FULL ) {
					fprintf( stream, "\t%s%s ", get_variable_name( look ), ( is_variable_updatable( look )? ":": "(ro):" ));
					fprintf( stream, "[%s]\n", (( ret == LV_CASES_INVALID )? "unconfigured": "undefined" ));
				}
				goto do_next;
			}
			if( ret != SUCCESS ) return( ret );
			if( e == 0 ) fprintf( stream, "\t%s%s", get_variable_name( look ), ( is_variable_updatable( look )? ":": "(ro):" ));
			fprintf( stream, "%s%s", (( e == 0 )? " ": ", "), buffer );
		}
		printf( "\n" );
		
		/*
		 *	For simply code we simply jump here to exit from
		 * 	a switch statement nested inside a while loop.
		 */
	do_next:
		/*
		 * 	Go round and do the next one.
		 */
	}
	fprintf( stream, "CV Updates\n" );
	fprintf( stream, "==========\n" );
	for( int i = 1; i <= MAXIMUM_CV_NUMBER; i++ ) {
		if(( ret = get_cv_delta( i, &m, &v ))) return( ret );
		switch( m ) {
			case 0: break;
			case 0xff: {
				fprintf( stream, "\tcv%d = %d\n", i, (int)v );
				break;
			}
			default: {
				char	b[ NUMBER_BUFFER ];

				display_number( v, b );
				fprintf( stream, "\tcv%d = %d(%s", i, (int)v, b );
				display_number( m, b );
				fprintf( stream, "%c%s)\n", MASK_SEPARATOR, b );
				break;
			}
		}
	}
	return( SUCCESS );
}

/*
 *	Individual character conversion.
 */
static int get_value( char d ) {
	if(( d >= '0' )&&( d <= '9' )) return( d - '0' );
	if(( d >= 'a' )&&( d <= 'f' )) return( d - ( 'a' - 10 ));
	if(( d >= 'A' )&&( d <= 'F' )) return( d - ( 'A' - 10 ));
	return( ERROR );
}

/*
 *	A simple text to number conversion.
 */
static STATUS evaluate( char *text, byte *value ) {
	int	sum, d,
		base;
	char	c;

	assert( text != NULL );

	switch( *text ) {
		case BINARY_PREFIX: {
			text++;
			base = 2;
			break;
		}
		case OCTAL_PREFIX: {
			text++;
			base = 8;
			break;
		}
		case HEX_PREFIX: {
			text++;
			base = 16;
			break;
		}
		default: {
			base = 10;
			break;
		}
	}
	sum = 0;
	while(( c = *text++ )) {
		if(( d = get_value( c )) == ERROR ) return( INVALID_DIGIT );
		if( d >= base ) return( BASE_INVALID );
		sum = sum * base + d;
	}
	if( sum >= 256 ) return( RANGE_INVALID );
	*value = sum;
	return( SUCCESS );
}

/*
 *	Break a supplied CV value into value and a mask component.
 */
static STATUS extract_value_mask( char *text, byte *value, byte *mask ) {
	STATUS	ret;
	char	*s;

	if(( s = strchr( text, MASK_SEPARATOR ))) *s++ = EOS;
	if(( ret = evaluate( text, value ))) return( ret );
	if( s ) {
		if(( ret = evaluate( s, mask ))) return( ret );
	}
	else {
		*mask = 0xff;
	}
	return( SUCCESS );
}

/*
 * 	The routine for primary processing of the arguments to the program.
 */
static STATUS argument_processor( int dcc, char *arg ) {
	char		*eq;
	int		cv, q;
	LOGICAL_VALUE	*lv;
	STATUS		ret;

	/*
	 *	Is this an assignment?
	 */
	if(( eq = strchr( arg, EQUALS ))) *eq++ = EOS;
	/*
	 *	Is this a "Q" Constant assignment?
	 */
	if(( compare_n( arg, "q", 1 ) == 0 )&&(( q = atoi( arg+1 )) > 0 )) {
		int	value;
		
		/*
		 *	Code for manipulation of DCC Generator configuration
		 *	constants.
		 */
		if( eq ) {
			
			value = atoi( eq );
			if(( !have_q_constant( q ))&&(( ret = read_q_constant( dcc, q )))) return( ret );
			if(( ret = write_q( q, value ))) return( ret );
		}
		else {
			if(( !have_q_constant( q ))&&(( ret = read_q_constant( dcc, q )))) return( ret );
			if(( ret = read_q( q, &value ))) return( ret );
			printf( "q%d = %d\n", q, value );
		}
	}
	else {
		/*
		 *	Is this a direct CV assignment?
		 */
		if(( compare_n( arg, "cv", 2 ) == 0 )&&(( cv = atoi( arg+2 )) > 0 )) {
			byte	mask, value;
			
			/*
			 *	Code for direct manipulation of CV[] values where
			 *	cv is the number of the configuration variable.
			 */
			if( eq ) {
				if(( ret = extract_value_mask( eq, &value, &mask ))) return( ret );
				if(( dcc != ERROR )&&(( ret = read_cv( dcc, cv, mask )))) return( ret );
				if(( ret = final_write_cv( cv, mask, value ))) return( ret );
			}
			else {
				if(( dcc != ERROR )&&(( ret = read_cv( dcc, cv, 0xff )))) return( ret );
			}
		}
		else {
			int	value;
			
			/*
			 *	Code for indirect logical variable manipulation.
			 */
			if(( lv = find_variable_by_name( arg ))) {
				/*
				 *	Are we expected to pre-read the value of the variable.
				 */
				if(( dcc != ERROR )&&(( ret = read_variable( dcc, lv )))) return( ret );
				/*
				 *	Found so we can process.
				 */
				if( eq ) {
					if( is_variable_enumerated( lv )) {
						if(( ret = write_enum_variable( lv, 0, eq ))) return( ret );
					}
					else {
						value = atoi( eq );
						if(( ret = write_int_variable( lv, 0, value ))) return( ret );
					}
				}
			}
			else {
				return( LV_NAME_INVALID );
			}
		}
	}
	return( SUCCESS );
}

/*
 *	Push updates back into the decoder.
 */
static STATUS update_decoder( int dcc ) {
	STATUS	ret;
	byte	v, m;
	int	errors;

	assert( dcc != ERROR );

	errors = 0;
	for( int i = 1; i <= MAXIMUM_CV_NUMBER; i++ ) {
		if(( ret = get_cv_delta( i, &m, &v ))) return( ret ); 
		switch( m ) {
			case 0: {
				/*
				 *	No bits in this CV need updating.
				 */
				break;
			}
			case 0xff: {
				/*
				 *	The whole CV is being re-written
				 */
				if( dcc_write_cv( dcc, i, (int)v ) == ERROR ) errors++;
				break;
			}
			default: {
				if( dcc_write_masked_cv( dcc, i, (int)m, (int)v ) == ERROR ) errors++;
				break;
			}
		}
	}
	return( errors? DCC_WRITE_FAILED: SUCCESS );
}


/************************************************************************
 *									*
 *	Main program code.						*
 *									*
 ************************************************************************/

int main( int argc, char *argv[] ) {
	int	arg, dcc, errors;
	char	*port;
	STATUS	ret;

	/*
	 *	Collect arguments.
	 */
	if(( arg = scan_flags( argc, argv )) <= 0 ) return( -arg );

	/*
	 *	Dump variable definitions if requested.
	 */
	if( option_flags & OPT_VARIABLES ) dump_variables_database( stdout );

	/*
	 *	Are there any args left?
	 */
	if( arg == argc ) return( 0 );
	
	/*
	 *	Start by making the CV table cache empty.
	 */
	empty_cv_table();

	/*
	 *	If we are required to be in READ only or WRITE only
	 *	mode then we need to have a connection through a
	 * 	DCC controller to the programming track
	 */
	if( option_flags & ( OPT_READ | OPT_WRITE )) {
		/*
		 *	In this case the first non flag value must (hopefully)
		 * 	be the device name.
		 */
		port = argv[ arg++ ];
		
		/*
		 *	Establish connection to the DCC device
		 */
#if DCC_PLUS_PLUS_COMPATIBILITY
		if(( dcc = open_serial_port( port, 115200 )) == ERROR ) {
			perror( "Unable to open DCC++ serial connection" );
			return( 3 );
		}
#elif DCC_GENERATOR_COMPATIBILITY
		if(( dcc = open_serial_port( port, 38400 )) == ERROR ) {
			perror( "Unable to open DCC Generator serial connection" );
			return( 3 );
		}
#else
#error "DCC compatibility not set."
#endif
		/*
		 *	The Arduino will reboot at this point.  Pause for 5 seconds.
		 */
		sleep( 5 );
		/*
		 *	Turn OFF then ON DCC power
		 */
		(void)turn_off_dcc( dcc );
		if( !turn_on_dcc( dcc )) {
			printf( "Unable to turn track on.\n" );
			close( dcc );
			return( 4 );
		}
		/*
		 *	There seems to be a need to wait at this point.
		 */
		sleep( 3 );
	}
	else {
		/*
		 *	Not using the programming track so we set the
		 * 	dcc file descriptor to ERROR.
		 */
		dcc = ERROR;
		port = NULL;
	}
	
	/*
	 * 	DCC Generator constant handling
	 */
	if(( option_flags & OPT_CONSTANTS )&&(( ret = display_q_constants( dcc )))) printf( "Reading constants failed, error \"%s\".\n", explain( ret ));


	/*
	 *	Run through the arguments and process each one in turn.
	 */
	errors = 0;
	while( arg < argc ) {
		if(( ret = argument_processor((( option_flags & OPT_READ )? dcc: ERROR ), argv[ arg ]))) {
			printf( "\"%s\" error: '%s'\n", argv[ arg ], explain( ret ));
			errors++;
		}
		arg++;
	}

	/*
	 *	Post-processing after all the arguments have been examined.
	 */
	if( errors ) {
		printf( "%d error%s detected, further processing skipped.\n", errors, (( errors == 1 )? "": "s" ));
	}
	else {
		/*
		 *	Final output required?
		 */
		if( option_flags & OPT_DUMP ) dump_cv_table( stdout, ( option_flags & OPT_FULL ));

		/*
		 *	Update the decoder if write flag set.
		 */
		if(( option_flags & OPT_WRITE )&&(( ret = update_decoder( dcc )))) printf( "Decoder update failed, error \"%s\".\n", explain( ret ));
	}

	/*
	 *	Close DCC connection and exit.
	 */
	if( dcc != ERROR ) {
		turn_off_dcc( dcc );
		close( dcc );
	}
	/*
	 *	Done
	 */
	return( 0 );
}

/*
 *	EOF
 */
