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

		/**
		 * Constructor to assign one of the two onboard slots to a
		 *
		 * @param slot  On board encoder slot to use
		 * 		(SLOT1 is right, SLOT_2 is left)
		 */
		EncoderOnBoardMotor(int slot);

		/**
		 * Rotate by the requested number of degrees.
		 *
		 * @param angle  Angle in degrees to rotate the motor by
		 * @param speed  Speed in degrees/second
		 */
		void Rotate(long angle, float speed = 100);

		/**
		 * Rotate by the requested number of degrees.
		 *
		 * @param angle  Angle in degrees to rotate the motor by
		 * @param speed  Speed in degrees/second
		 * @param block  Waits for the move to complete if true
		 */
		void Rotate(long angle, float speed, bool block);

		/**
		 * Rotate by the requested number of degrees.
		 *
		 * @param angle  Angle in degrees to rotate the motor by
		 * @param speed  Speed in degrees/second
		 * @param block  Waits for the move to complete if true
		 * @param sync   Tries to keep two motors in sync if true
		 *               This feature is experimental
		 */
		void Rotate(long angle, float speed, bool block, bool sync);

		/**
		 * Causes motor to rotate forward until Stop() is called.
		 *
		 * @param speed  Speed in degrees/second
		 */
		void Forward(float speed);

		/**
		 * Causes motor to stop, pretty much instantaneously.
		 */
		void Stop(void);

		/**
		 * Reset the tachometer associated with this motor.
		 */
		void ResetTachoCount(void);

		/**
		 * Return the tachometer count.
		 *
		 * @return  Current tachometer count in degrees
		 */
		int GetTachoCount(void);

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
