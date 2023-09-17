/*
 * 	CVs.c
 *
 * 	Define the working area where the CV values are
 * 	coordinated.
 */

#include "CVs.h"
#include "DCC.h"

/*
 *	Capture a single CV value and future value.
 */
typedef struct {
	/*
	 * 	Declare storage of data recovered from the decoder
	 * 	through the DCC read CV and read CV Bit commands.
	 */
	byte		read_mask,
			read_value;
	/*
	 *	Declare storage of the data "yet to be written" to
	 * 	the decoder.
	 */
	byte		write_mask,
			write_value;
} VARIABLE;

/*
 *	This is the array where we will process all the CV values.
 */
static VARIABLE configuration_variable[ TOTAL_CV_COUNT ];

/*
 * 	Syntactic sugar for accessing the CV array
 */
#define CV_VALID(x)	(((x)>=MINIMUM_CV_NUMBER)&&((x)<=MAXIMUM_CV_NUMBER))
#define CV_INDEX(x)	((x)-MINIMUM_CV_NUMBER)

/*
 *	initialise the CV table as empty with no data from a decoder.
 */
void empty_cv_table( void ) {
	int	i;

	/*
	 *	Clear out the table with nothing read and nothing
	 * 	set to be written.
	 */
	for( i = 0; i < TOTAL_CV_COUNT; i++ ) {
		VARIABLE *v = &( configuration_variable[ i ]);
		
		v->read_mask = 0;
		v->read_value = 0;
		v->write_mask = 0;
		v->write_value = 0;
	}
}

/*
 *	Extract CV value from decoder on the programming track
 */
STATUS read_cv( int dcc, int cv, byte mask ) {
	VARIABLE	*v;
	int		value;

	assert( dcc != ERROR );
	
	if( !CV_VALID( cv )) return( CV_NUMBER_INVALID );
	
	v = &( configuration_variable[ CV_INDEX( cv )]);

	assert(( v->read_value & v->read_mask ) == v->read_value );
	assert(( v->write_value & v->write_mask ) == v->write_value );
	
	if(( v->read_mask & mask ) == mask ) return( SUCCESS );
	
#if DCC_PLUS_PLUS_COMPATIBILITY
	if(( value = dcc_read_cv( dcc, cv )) == ERROR ) return( DCC_READ_FAILED );
	if(( value < 0 )||( value > 255 )) return( DCC_RESULT_INVALID );
	mask = 0xff;
#elif DCC_GENERATOR_COMPATIBILITY
	value = 0;
	for( int b = 0; b < 8; b++ ) {
		byte	m;

		m = 1 << b;
		switch( dcc_read_cv_bit( dcc, cv, b )) {
			case ERROR: {
				return( DCC_READ_FAILED );
			}
			case 0: {
				break;
			}
			case 1: {
				value |= m;
				break;
			}
			default: {
				return( DCC_RESULT_INVALID );
			}
		}
	}
#else
#error "Compatibility not defined."
#endif	/*
	 *	Cleared to update the base value.
	 */
	v->read_value |= (byte)value;
	v->read_mask |= mask;
	return( SUCCESS );
}

/*
 * 	Read and write whole CV values.
 */
STATUS base_read_cv( int cv, byte *mask, byte *value ) {
	VARIABLE	*v;
	
	assert( mask != NULL );
	assert( value != NULL );
	
	if( !CV_VALID( cv )) return( CV_NUMBER_INVALID );

	v = &( configuration_variable[ CV_INDEX( cv )]);

	assert(( v->read_value & v->read_mask ) == v->read_value );
	assert(( v->write_value & v->write_mask ) == v->write_value );
	
	*mask = v->read_mask;
	*value = v->read_value;
	return( SUCCESS );
}

STATUS final_read_cv( int cv, byte *mask, byte *value ) {
	VARIABLE	*v;
	
	assert( mask != NULL );
	assert( value != NULL );
	
	if( !CV_VALID( cv )) return( CV_NUMBER_INVALID );
	
	v = &( configuration_variable[ CV_INDEX( cv )]);

	assert(( v->read_value & v->read_mask ) == v->read_value );
	assert(( v->write_value & v->write_mask ) == v->write_value );
	
	*mask = v->read_mask | v->write_mask;
	*value = ( v->read_value & ~v->write_mask )| v->write_value;
	return( SUCCESS );
}

STATUS final_write_cv( int cv, byte mask, byte value ) {
	VARIABLE	*v;
	
	if( !CV_VALID( cv )) return( CV_NUMBER_INVALID );
	
	v= &( configuration_variable[ CV_INDEX( cv )]);

	assert(( v->read_value & v->read_mask ) == v->read_value );
	assert(( v->write_value & v->write_mask ) == v->write_value );
	assert(( value & mask ) == value );
	
	/*
	 * 	Check the write once criteria.
	 */
	if( v->write_mask & mask ) return( CV_VALUE_OVERWRITE );
	/*
	 *	Cleared to update the base value.
	 */
	v->write_value |= value;
	v->write_mask |= mask;
	return( SUCCESS );
}

/*
 * 	This final routine provides the "delta" information between
 * 	the base data provided and the final data desired.  This is
 *	the bit mask of bits that need changing and their new values.
 */
STATUS get_cv_delta( int cv, byte *mask, byte *value ) {
	VARIABLE	*v;
	byte		m, d, b;

	
	assert( mask != NULL );
	assert( value != NULL );
	
	if( !CV_VALID( cv )) return( CV_NUMBER_INVALID );
	
	v = &( configuration_variable[ CV_INDEX( cv )]);

	assert(( v->read_value & v->read_mask ) == v->read_value );
	assert(( v->write_value & v->write_mask ) == v->write_value );

	m = 0;
	d = 0;
	for( b = 0x80; b; b >>= 1 ) {
		if( v->write_mask & b ) {
			if( v->read_mask & b ) {
				/*
				 *	Add to result only if the corresponding
				 *	value bits are different and so need
				 * 	changing.
				 */
				if(( v->read_value & b ) != ( v->write_value & b )) {
					m |= b;
					d |= v->write_value & b;
				}
			}
			else {
				/*
				 *	just copy in the write data.
				 */
				m |= b;
				d |= v->write_value & b;
			}
		}
	}
	*mask = m;
	*value = d;
	return( SUCCESS );
}


/*
 * 	EOF
 */
