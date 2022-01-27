/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Piggy-back timing functions on to timer 0 using its compare A or B
 *        ISRs
 *
 * @details
 */

//! @cond SuppressGuard
#ifndef LM_TIMER_
#define LM_TIMER_
//! @endcond

#define n_cb 8

typedef void(*timer_cb)(void);

class Timer
{

	public:

		static void RegisterCallback(timer_cb callback);
		static void UnregisterCallback(timer_cb callback);
		static timer_cb callbacks[n_cb];
		static int cb_count, counter;

	private:



};

//! @cond SuppressGuard
#endif
//! @endcond
