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
		void RotateTo(long position, float speed, bool block);
		void Stop(void);


	private:

		static MeEncoderOnBoard encoder1;
		static MeEncoderOnBoard encoder2;
		static bool pos_reached[2];
		static void IsrProcessEncoder1(void);
		static void IsrProcessEncoder2(void);
		static void PositionReached(int16_t slot, int16_t ext_id);
		static bool IsPositionReached(int16_t slot);
		static bool ArePositionsReached(void);
		static void ResetPositionReached(int16_t slot);
		static void Loop1(void);
		static void Loop2(void);
		static void LoopSynced(void);
		int slot;
		//FIXME
		void RotateTo(long position, float speed, bool block, bool sync);
};

//! @cond SuppressGuard
#endif
//! @endcond
