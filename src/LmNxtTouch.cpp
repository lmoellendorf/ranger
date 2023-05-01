/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Use NXT Touch sensors with Makeblock mBot Ranger
 *
 * @details
 */

#include "LmNxtTouch.h"

NxtTouch::NxtTouch(uint8_t port): Touch(MePort(port).pin1())
{
}
