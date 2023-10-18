/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Use NXT Touch sensors with Makeblock mBot Ranger
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_NXT_TOUCH_
#define LM_NXT_TOUCH_
//! @endcond

#include <MePort.h>
#include <LmTouch.h>

class NxtTouch: public Touch
{

	public:

		/**
		 * Constructor to assign RJ25 port to NXT Touch sensor
		 *
		 * @param port  RJ25 port from PORT_6 to PORT10
		 */
		NxtTouch(uint8_t port);

};

//! @cond SuppressGuard
#endif
//! @endcond
