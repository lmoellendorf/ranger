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

#include <MeEncoderOnBoard.h>

#define SLOT_L SLOT2
#define SLOT_R SLOT1

class Ranger
{

	public:

		static MeEncoderOnBoard _EncoderL;
		static MeEncoderOnBoard _EncoderR;
		static bool pos_l_reached;
		static bool pos_r_reached;

		Ranger(int slot_l, int slot_r);
		void moveTo(long position, float speed = 100);

	private:

		static void isr_process_encoderL(void);
		static void isr_process_encoderR(void);
		static void reached_position(int16_t slot, int16_t extID);
};

//! @cond SuppressGuard
#endif
//! @endcond
