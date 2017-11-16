 /*!
 *  \file File timer.cpp
 *  \brief Implementation of the class Timer
 *
 *  Auxiliary documentation
 *  \sa timer.hpp
 */
#include <timer.hpp>
#include <assert.h>

/*!
	@class Timer
	@brief This class provides the timer to the game
*/

//! A constructor.
    /*!
    This is a empty constructor method of Timer class
    */
Timer::Timer() {
	LOG_METHOD_START("Timer::Timer");
	LOG_MSG("This is a empty constructor method of Timer class");
	LOG_METHOD_CLOSE("Timer::Timer", "constructor");
}

/*!
	@fn void Timer::add_time(float additional_time)
	@brief Method that adds time to the timer
	@param additional_time
	@brief A float, that represents time that will bee add to the timer
	@return The execution of this method returns no value
*/
void Timer::add_time(float additional_time) {
	LOG_METHOD_START("Timer::add_time");
	LOG_VARIABLE("time", time);
	time+=additional_time;
	LOG_METHOD_CLOSE("Timer::add_time","void");
}

/*!
	@fn void Timer::restart_time()
	@brief Method that resets the timer
	@return The execution of this method returns no value
*/
void Timer::restart_time() {
	LOG_METHOD_START("Timer::restart_time");
	time=0;
	LOG_METHOD_CLOSE("Timer::restart_time","void");
}

/*!
	@fn float Timer::get_time()
	@brief A getter of the attribute time
	@return A positive float, that represents the timer's current time
*/
float Timer::get_time() {
	LOG_METHOD_START("Timer::get_time");
	LOG_METHOD_CLOSE("time",time);
	assert(time >= 0);
	return time;
}
