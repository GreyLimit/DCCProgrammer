/*
 * 	Status.c
 *
 * 	Define an enumerated type to be used as a function result
 * 	type allowing a more granular return than success/failure
 * 	(true/false).  The module will require a mechanism to
 * 	facilitate conversion from binary flag to human text.
 */

#include "OS.h"
#include "Status.h"


/*
 *	simple conversion table.
 */
typedef struct {
	char		*exp;
	STATUS		val;
} EXPLAINS;

static EXPLAINS explains_list[] = {
	{ "Success",				SUCCESS			},
	{ "CV number invalid",			CV_NUMBER_INVALID	},
	{ "CV element invalid",			CV_ELEMENT_INVALID	},
	{ "CV value invalid",			CV_VALUE_INVALID	},
	{ "CV value overwrite",			CV_VALUE_OVERWRITE	},
	{ "CV value undefined",			CV_VALUE_UNDEFINED	},
	{ "LV name invalid",			LV_NAME_INVALID		},
	{ "LV number invalid",			LV_NUMBER_INVALID	},
	{ "LV cases invalid",			LV_CASES_INVALID	},
	{ "LV value numeric",			LV_VALUE_NUMERIC	},
	{ "LV value enumerated",		LV_VALUE_ENUMERATED	},
	{ "LV value invalid",			LV_VALUE_INVALID	},
	{ "LV value incomplete",		LV_VALUE_INCOMPLETE	},
	{ "LV index invalid",			LV_INDEX_INVALID	},
	{ "Invalid digit",			INVALID_DIGIT		},
	{ "Base invalid",			BASE_INVALID		},
	{ "Range invalid",			RANGE_INVALID		},
	{ "Decoder read failed",		DCC_READ_FAILED		},
	{ "Decoder write failed",		DCC_WRITE_FAILED	},
	{ "DCC controller invalid result",	DCC_RESULT_INVALID	},
	{ "IO to DCC generator failed",		DCC_IO_FAILED		},
	{ "Undefined error",			UNDEFINED_ERROR		},
	{ "Buffer overflow",			BUFFER_OVERFLOW		},
	{ "Not implemented",			NOT_IMPLEMENTED		},
	{ NULL }
};

/*
 *	Return textual version of status value.
 */
char *explain( STATUS value ) {
	for( int i = 0; explains_list[ i ].exp; i++ ) if( value == explains_list[ i ].val ) return( explains_list[ i ].exp );
	return( "unexplained" );
}


/*
 * 	EOF
 */
