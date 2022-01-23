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

#define SLOT_L SLOT2
#define SLOT_R SLOT1

class Ranger
{

	public:

		Ranger(int slot_l, int slot_r);
		void moveTo(long position, float speed = 100);

	private:

		EncoderOnBoardMotor MotorL;
		EncoderOnBoardMotor MotorR;

};

//! @cond SuppressGuard
#endif
//! @endcond
