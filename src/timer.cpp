 /*!
 *  \file File timer.cpp
 *  \brief Implementation of the class Timer
 *
 *  Auxiliary documentation
 *  \sa timer.hpp
 */
#include <timer.hpp>

/*!
	@class Timer
	@brief This class provides the timer to the game
*/

//! A constructor.
    /*!
    This is a empty constructor method of Timer class
    */
Timer::Timer() {

}

/*!
	@fn void Timer::Update(float dTime)
	@brief Method that adds time to the timer
	@param dTime
	@brief A float, that represents time that will bee add to the timer
	@return The execution of this method returns no value
*/
void Timer::Update(float dTime) {
	time += dTime;
}

/*!
	@fn void Timer::Restart()
	@brief Method that resets the timer
	@return The execution of this method returns no value
*/
void Timer::Restart() {
	time = 0;
}

/*!
	@fn float Timer::Get()
	@brief A getter of the attribute time
	@return A positive float, that represents the timer's current time
*/
float Timer::Get() {
	return time;
}
