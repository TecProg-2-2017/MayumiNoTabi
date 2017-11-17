/*!
 *  @file File componentMovement.cpp
 *  @brief Implementation of the class of component movements present in the game
 *
 *  The class implemented here provides to the game the speed and type
 *  of movement that a given element can perform
 *
 *  Auxiliary documentation
 *  @sa componentMovement.hpp
 *
 *  @warning All variables are initialized
 */

#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>
#include <assert.h>


//! Functions to be called by the methods in order to perform actions

/*!
	@fn CompMovement::chooseTypeComponentMovement
	@brief Chooses the kid of the movement executed by the specified component
	@params float time
*/

void CompMovement::chooseTypeComponentMovement(float time){

 	assert(time > 0.0 and time < 60.0 ); // CPPCheck engine checks if the assertive condition (Always true)

	UNUSED(time);
	GO(entity)->pos += move;

	if (mType == moveType::t_bullet){
		GO(entity)->rotation = speed.angle();
	}
	else {
		//Nothing to do
	}
}

/*!
	@fn CompMovement::CompMovement()
	@brief Constructor method for CompMovement
	@params const Vec2& sprite, moveType move_type
*/

CompMovement::CompMovement(const Vec2& sprite, moveType move_type): mType{move_type},speed{sprite} {
	LOG_METHOD_START('CompMovement::CompMovement');



	LOG_METHOD_CLOSE('CompMovement::CompMovement', "constructor");

}

/*!
	@fn CompMovement::~CompMovement()
	@brief Desstructor method for CompMovement
	@params No params
*/

CompMovement::~CompMovement() {
	LOG_METHOD_START('CompMovement::~CompMovement');

	LOG_METHOD_CLOSE('CompMovement::~CompMovement', "destructor");
	// Method body its empty


}



/*!
	@fn void CompMovement::update(float time)
	@brief Method that update element movement
	@return The execution of this method returns no value
	@warning Method that requires review of comment
	@param float time
*/

void CompMovement::update(float time) {
	LOG_METHOD_START('CompMovement::update');
	LOG_VARIABLE("CompMovement::update", "time");

	assert(time >= 0);

	chooseTypeComponentMovement(time);

	LOG_METHOD_CLOSE('CompMovement::update', "void");

	assert(time > 0.0 and time < 60.0 );

}

/*!
	@fn void CompMovement::render()
	@brief Method that render the new element movement
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/


void CompMovement::render() {
	//! Non renderizable component
	LOG_METHOD_START('CompMovement::render');

	LOG_METHOD_CLOSE('CompMovement::render', "void");
}

/*!
	@fn Component::type CompMovement::get_type()
	@brief Method that sets the type of movement
	@return Component class object
	@warning Method that requires review of comment
*/

Component::type CompMovement::get_type()const{
	LOG_METHOD_START('CompMovement::get_type');


  return Component::type::t_movement;
}
