/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

#include "LmRanger.h"

Ranger::Ranger(int slot_l = SLOT_L, int slot_r = SLOT_R) :
	MotorL(slot_l), MotorR(slot_r) {}

void Ranger::moveTo(long position, float speed)
{
	Ranger::MotorL.moveTo(position, speed);
	Ranger::MotorR.moveTo(-position, speed);
}
