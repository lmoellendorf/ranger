/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Simplified Ranger Movements
 *
 * @details
 */

#include "LmRanger.h"
#include "LmTimer.h"

Ranger::Ranger(int slot_l = SLOT_L, int slot_r = SLOT_R) :
	motor_l(slot_l), motor_r(slot_r) {}

void Ranger::moveTo(long position, float speed)
{
	Ranger::motor_l.rotate(position, speed, false);
	Ranger::motor_r.rotate(-position, speed, false);
}
