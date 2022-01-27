/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_RANGER_
#define LM_RANGER_
//! @endcond

#include <LmEncoderOnBoardMotor.h>
#include <MeRGBLed.h>

#define SLOT_L SLOT2
#define SLOT_R SLOT1
// Auriga on-board light ring has 12 LEDs
#define LEDNUM  12

class Ranger
{

	public:

		Ranger(int slot_l, int slot_r);
		void MoveTo(long position, float speed = 100);
		void StartRainbow(void);
		void StopRainbow(void);

	private:

		EncoderOnBoardMotor motor_l;
		EncoderOnBoardMotor motor_r;
		static MeRGBLed led;
		static volatile float j, f, k;
		static void ColorLoop();
};

//! @cond SuppressGuard
#endif
//! @endcond
