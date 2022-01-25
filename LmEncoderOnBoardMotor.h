/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_ENCODER_ON_BOARD_MOTOR_
#define LM_ENCODER_ON_BOARD_MOTOR_
//! @endcond

#include <MeEncoderOnBoard.h>
#include <MePort.h>

class EncoderOnBoardMotor
{

	public:

		EncoderOnBoardMotor(int slot);
		void move_to(long position, float speed = 100);


	private:

		static MeEncoderOnBoard Encoder1;
		static MeEncoderOnBoard Encoder2;
		static bool pos_reached[2];
		static void isr_process_encoder1(void);
		static void isr_process_encoder2(void);
		static void reached_position(int16_t slot, int16_t extID);
		int slot;
};

//! @cond SuppressGuard
#endif
//! @endcond
