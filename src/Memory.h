/*
 *	Memory.h
 *
 * 	Some stuff to do with dynamic memory allocation..
 */

#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <malloc.h>
#include <alloca.h>
#include <string.h>

#define NEW(t)		((t *)malloc( sizeof( t )))
#define STRDUP(s)	(strdup((s)))
#define FREE(p)		(free((p)))

#define STACK(t)	((t *)alloca( sizeof( t )))
#define STACK_STR(s)	(strdupa((s)))

#endif

/*
 * 	EOF
 */
