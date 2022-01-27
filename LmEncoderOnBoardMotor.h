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
		void RotateTo(long position, float speed = 100);
		void RotateTo(long position, float speed, bool sync);


	private:

		static MeEncoderOnBoard encoder1;
		static MeEncoderOnBoard encoder2;
		static bool pos_reached[2];
		static void IsrProcessEncoder1(void);
		static void IsrProcessEncoder2(void);
		static void PositionReached(int16_t slot, int16_t ext_id);
		static void Loop(void);
		static void LoopSynced(void);
		int slot;
};

//! @cond SuppressGuard
#endif
//! @endcond
