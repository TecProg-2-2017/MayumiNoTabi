/*
 *  File: timer.cpp
 *
 *  Description:  Implements Timer class
 */

#include <timer.hpp>

// No params constructor method for Timer
Timer::Timer() {

}

// Adds time to Timer's time
// Recivies the param dTime,as a float, that represents time that will bee add
void Timer::Update(float dTime) {
	time += dTime;
}

// Resets the Timer's time
void Timer::Restart() {
	time = 0;
}

// Returns the Timer's time
float Timer::Get() {
	return time;
}
