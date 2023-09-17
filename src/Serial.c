/*
 *	Serial port implementation
 */

#include "OS.h"
#include "Const.h"
#include "Serial.h"

/*
 *	Lookup table of baud rates and bit map equivs.
 */
#define BAUD_TABLE struct baud_table
BAUD_TABLE {
	int	line_speed;
	int	parameter;
};
static BAUD_TABLE bauds[] = {
	{ 300,		B300	},
	{ 600,		B600	},
	{ 1200,		B1200	},
	{ 1800,		B1800	},
	{ 2400,		B2400	},
	{ 4800,		B4800	},
	{ 9600,		B9600	},
	{ 19200,	B19200	},
	{ 38400,	B38400	},
	{ 57600,	B57600	},
	{ 115200,	B115200	},
	{ 230400,	B230400	},
	{ 0, 0 }
};

/*
 *	Routine used to open a serial port.
 */
int open_serial_port( char *port, int baud ) {
	int		fd, i;
	struct termios	t;

	/*
	 *	Find the baud rate
	 */
	for( i = 0; bauds[ i ].line_speed > 0; i++ ) {
		if( baud == bauds[ i ].line_speed ) {
			break;
		}
	}
	if( bauds[ i ].line_speed == 0 ) {
		i = B9600;
	}
	else {
		i = bauds[ i ].parameter;
	}
	/*
	 *	Now - open the port!
	 */
	if(( fd = open( port, O_RDWR | O_NOCTTY | O_NDELAY )) == ERROR ) {
		perror( "Opening Serial port" );
	}
	else {
		fcntl( fd, F_SETFL, 0 );
		if( tcgetattr( fd, &t ) == ERROR ) {
			perror( "Unable to read remote port line characteristics" );
		}
		else {
			t.c_cflag &= ~( PARENB | CSIZE );	/* No Parity */
			t.c_cflag |= ( CS8 );			/* Eight bit bytes */
			
			t.c_lflag = 0;				/* No local processing required */
			t.c_oflag = 0;				/* No OUTPUT processing required */
			t.c_iflag = 0;				/* No INPUT processing required */

			cfsetispeed( &t, i );
			cfsetospeed( &t, i );
			if( tcsetattr( fd, TCSANOW, &t ) == ERROR ) {
				perror( "Unable to write remote port line characteristics" );
			}
		}
	}
	return( fd );
}

/*
 *	EOF
 */
