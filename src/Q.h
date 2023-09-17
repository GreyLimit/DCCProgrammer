/*
 * 	Q.h
 *
 * 	Define the working area where the Q values are
 * 	coordinated.
 */

#ifndef _Q_H_
#define _Q_H_

#include "OS.h"
#include "Status.h"
#include "Const.h"
#include "Config.h"

/************************************************************************
 *									*
 *	The Generator Q Constants are captured here			*
 *									*
 ************************************************************************/

extern STATUS display_q_constants( int dcc );
extern bool have_q_constant( int q );
extern STATUS read_q_constant( int dcc, int q );
extern STATUS read_q( int q, int *value );
extern STATUS write_q( int q, int value );
extern STATUS write_q_constant( int dcc, int q );


#endif

/*
 * 	EOF
 */
