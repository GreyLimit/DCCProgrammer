//
//	These are the includes for the OS stuff.
//

#ifndef _OS_H_
#define _OS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <signal.h>
#include <poll.h>
#include <netdb.h>
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>
#include <alloca.h>
#include <dirent.h>
#include <stdint.h>

/*
 *	Define here any base types we feel the environment is missing.
 */
typedef uint8_t		bool;
typedef uint8_t		byte;
typedef uint16_t	word;
typedef uint32_t	dword;

#endif

//
//	EOF
//
