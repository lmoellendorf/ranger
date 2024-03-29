/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief HiTechnic Infrared Seeker for Arduino
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_ME_HT_IR_SEEKER_V2_
#define LM_ME_HT_IR_SEEKER_V2_
//! @endcond

#include <LmHtIrSeekerV2.h>
#include <MePort.h>

class MeHtIrSeekerV2: public HtIrSeekerV2
{

	public:
		MeHtIrSeekerV2(MePort port, int mode);
		MeHtIrSeekerV2(void);

	private:

};

//! @cond SuppressGuard
#endif
//! @endcond
