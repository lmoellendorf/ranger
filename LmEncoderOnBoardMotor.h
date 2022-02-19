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
		void Rotate(long angle, float speed = 100);
		void Rotate(long angle, float speed, bool block);
		void Rotate(long angle, float speed, bool block, bool sync);
		void Forward(float speed);
		void Stop(void);


	private:

		/**
		 * This one is private untill I found out what the purpose of
		 * `ratio` is - if you know, please let me know!
		 */
		EncoderOnBoardMotor(int slot, float ratio);
		static MeEncoderOnBoard encoder1;
		static MeEncoderOnBoard encoder2;
		static bool pos_reached[2];
		static bool synced;
		static void IsrProcessEncoder1(void);
		static void IsrProcessEncoder2(void);
		static void PositionReached(int16_t slot, int16_t ext_id);
		static bool IsPositionReached(int16_t slot);
		static bool ArePositionsReached(void);
		static void ResetPositionReached(int16_t slot);
		static void SetSynced(bool on);
		static bool GetSynced(void);
		static void syncCurrentSpeed(void);
		static void Loop(void);
		static int Slot2Index(int slot);
		static MeEncoderOnBoard *Slot2Encoder(int slot);
		int slot;
};

//! @cond SuppressGuard
#endif
//! @endcond
