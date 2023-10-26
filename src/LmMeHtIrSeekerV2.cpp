/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief HiTechnic Infrared Seeker for Arduino
 *
 * @details
 */

#include "LmMeHtIrSeekerV2.h"

MeHtIrSeekerV2::MeHtIrSeekerV2(MePort port, int mode): HtIrSeekerV2(mode)
{
        port.dWrite1(1);
}

MeHtIrSeekerV2::MeHtIrSeekerV2(void): MeHtIrSeekerV2(PORT_6, AC)
{
}
