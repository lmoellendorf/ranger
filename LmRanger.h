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
		void move_to(long position, float speed = 100);
		static void Ranger::color_loop();
		static volatile float j, f, k;

	private:

		EncoderOnBoardMotor MotorL;
		EncoderOnBoardMotor MotorR;
		static MeRGBLed Ranger::led;
};

//! @cond SuppressGuard
#endif
//! @endcond
