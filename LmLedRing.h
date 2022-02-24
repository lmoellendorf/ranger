/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_LED_RING_
#define LM_LED_RING_
//! @endcond

#include <MeRGBLed.h>

class LedRing
{

	public:

		static void StartRainbow(void);
		static void StopRainbow(void);

	private:

		static MeRGBLed led;
		static volatile float j, f, k;
		static void ColorLoop();
};

//! @cond SuppressGuard
#endif
//! @endcond
