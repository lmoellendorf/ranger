/**
 * @copyright Lars Möllendorf
 * @file
 * @author Lars Möllendorf <lars@moellendorf.eu>
 * @brief Piggy-back timing functions on to timer 0 using its compare A or B
 *        ISRs
 *
 * @details
 */

#include "LmTimer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>
#include <Arduino.h>

timer_cb Timer::callbacks[n_cb] = {0};
int Timer::cb_count(0);
int Timer::counter(0);

void Timer::RegisterCallback(timer_cb callback)
{
	for (int cb = 0; cb < n_cb; cb++) {
		if (callbacks[cb]) {
			if (callbacks[cb] == callback)
				return;

			continue;
		}

		// enable timer compare interrupt
		TIMSK0 |= (1 << OCIE0A);
		noInterrupts();
		callbacks[cb] = callback;
		cb_count++;
		interrupts();
		return;
	}
}

void Timer::UnregisterCallback(timer_cb callback)
{
	for (int cb = 0; cb < n_cb; cb++) {
		if (callbacks[cb] != callback)
			continue;

		noInterrupts();
		callbacks[cb] = NULL;
		cb_count--;
		interrupts();
	}
}

ISR(TIMER0_COMPA_vect)
{
	if ((Timer::counter++) % (8 * Timer::cb_count))
		return;

	for (int cb = 0; cb < n_cb; cb++) {
		if (!Timer::callbacks[cb])
			continue;

		Timer::callbacks[cb]();
	}
}
