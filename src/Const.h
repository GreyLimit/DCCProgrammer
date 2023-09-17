/*
 *	Define generic program constants here.
 */

#ifndef _CONST_H_
#define _CONST_H_

/*
 *	Generic constant values which are self evident.
 */

#define TRUE		(0==0)
#define FALSE		(0==1)
#define ERROR		(-1)
#define EOS		'\0'
#define SPACE		' '
#define EQUALS		'='
#define OR		'|'
#define OBRACKET	'['
#define CBRACKET	']'


/*
 *	Key symbols used in the program
 */
#define MASK_SEPARATOR	'/'
#define BINARY_PREFIX	'b'
#define OCTAL_PREFIX	'o'
#define HEX_PREFIX	'x'

/*
 *	Generalised sizes for buffers of various uses.
 */
#define NUMBER_BUFFER		16
#define TEXT_BUFFER		128

/*
 *	Set a fixed IO buffer size
 */
#define BUFFER		128


#endif

/*
 *	EOF
 */
