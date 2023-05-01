/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified controll of Makeblock mBot Ranger on board Motor Encoder
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
		void rotate(long angle, float speed = 100);

		/**
		 * Rotate by the requested number of degrees.
		 *
		 * @param angle  Angle in degrees to rotate the motor by
		 * @param speed  Speed in degrees/second
		 * @param block  Waits for the move to complete if true
		 */
		void rotate(long angle, float speed, bool block);

		/**
		 * Rotate by the requested number of degrees.
		 *
		 * @param angle  Angle in degrees to rotate the motor by
		 * @param speed  Speed in degrees/second
		 * @param block  Waits for the move to complete if true
		 * @param sync   Tries to keep two motors in sync if true
		 *               This feature is experimental
		 */
		void rotate(long angle, float speed, bool block, bool sync);

		/**
		 * Causes motor to rotate forward until Stop() is called.
		 *
		 * @param speed  Speed in degrees/second
		 */
		void forward(float speed);

		/**
		 * Causes motor to stop, pretty much instantaneously.
		 */
		void stop(void);

		/**
		 * Reset the tachometer associated with this motor.
		 */
		void resetTachoCount(void);

		/**
		 * Return the tachometer count.
		 *
		 * @return  Current tachometer count in degrees
		 */
		int getTachoCount(void);

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
		static void isrProcessEncoder1(void);
		static void isrProcessEncoder2(void);
		static void positionReached(int16_t slot, int16_t ext_id);
		static bool isPositionReached(int16_t slot);
		static bool arePositionsReached(void);
		static void resetPositionReached(int16_t slot);
		static void setSynced(bool on);
		static bool getSynced(void);
		static void syncCurrentSpeed(void);
		static void loop(void);
		static int slot2Index(int slot);
		static MeEncoderOnBoard *slot2Encoder(int slot);
		int slot;
};

//! @cond SuppressGuard
#endif
//! @endcond
