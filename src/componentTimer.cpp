/*!
 *  @file File componentTimer.cpp
 *  @brief Implementation of the class of game time
 *
 *  The class implemented here provides to the game the time limit
 *
 *  Auxiliary documentation
 *  @sa componentTimer.hpp
 *
 *  @warning All variables are initialized
 */


//#include <compLib.hpp>
//#include <camera.hpp>
//#include <inputManager.hpp>

#include <gameObject.hpp>
#include <assert.h>

//! A constructor.
    /*!
    This is a constructor method of componentTimer class
    */

CompTimer::CompTimer(float limit):limit{limit}{

	LOG_METHOD_START('CompTimer::CompTimer');

	assert(limit >= 0.0);

	LOG_METHOD_CLOSE('CompTimer::CompTimer', "constructor");
}

//! A destructor.
    /*!
      This is a destructor method of componentText class
    */

CompTimer::~CompTimer() {
	// Method body its empty
	LOG_METHOD_START('CompTimer::CompTimer');
	LOG_METHOD_CLOSE('CompTimer::CompTimer', "destructor");
}

/*!
	@fn CompTimer::update(float time)
	@brief Method that update the game time
	and check the time limit
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/




void CompTimer::update(float time) { //Time range 0.0 - 60.0

	LOG_VARIABLE("CompTimer::update", "time");
	assert(time > 0.0 and time < 60.0);

	t.add_time(time);

	if (t.get_time()>limit) {
		GO(entity)->dead=true;
	}

}

/*!
	@fn void CompTimer::render()
	@brief Method that render the game time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompTimer::render() {
	// Method body its empty
}

/*!
	@fn void CompTimer::own(GameObject* go)
	@brief Method that monitor the game element
	@param GameObject* go
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompTimer::own(GameObject* go) {

	LOG_VARIABLE("CompTimer::own", "go");

	assert(go != NULL);

	entity=go->uid;
}

/*!
	@fn void CompMovement::Update(float time)
	@brief Method that sets the game time
	@return The method return the current time
	@warning Method that requires review of comment
*/

Component::type CompTimer::get_type() const{
	return Component::type::t_timer;
}

//! Functions to be called by the methods in order to perform actions

void updateTimeByLimit(){

	LOG_METHOD_START('updateTimeByLimit');

	t.add_time(time);

	if (t.get_time()>limit) {
		GO(entity)->dead=true;
	}
	else {
		//Nothing to do
	}

	LOG_METHOD_CLOSE('updateTimeByLimit', "void");

}
