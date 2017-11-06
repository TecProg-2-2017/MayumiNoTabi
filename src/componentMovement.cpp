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

#include <game.hpp>
#include <gameObject.hpp>
#include <componentMovement.hpp>
#include <assert.h>


//! Functions to be called by the methods in order to perform actions

void chooseTypeComponentMovement(float time){

 	assert(time > 0.0 and time < 60.0 ); // CPPCheck avalia a condição da assertiva (Se está sempre true)

	UNUSED(time);
	GO(entity)->position += move;

	if (mType == moveType::type_bullet){
		GO(entity)->rotation = speed.angle();
	}
	else {
		//Nothing to do
	}
}

//! Functions to be called by the methods in order to perform actions

void choose_type_component_movement(float time){
	LOG_METHOD_START('choose_type_component_movement');
	LOG_VARIABLE("choose_type_component_movement", "time");

	assert(time >= 0);

	UNUSED(time);
	GO(entity)->position += move;

	if (mType == moveType::type_bullet){
		GO(entity)->rotation = speed.angle();
	}
	else {
		//Nothing to do
	}
	LOG_METHOD_CLOSE('choose_type_component_movement', "void");
}


//! A constructor.
    /*!
    This is a constructor method of componentMovement class
    */

CompMovement::CompMovement(const Vec2& sprite, moveType move_type): mType{move_type},speed{s} {
	LOG_METHOD_START('CompMovement::CompMovement');
	LOG_VARIABLE("CompMovement::CompMovement", "sprite", "move_type");

	assert(sprite >= 0);
	assert(move_type != NULL);

	LOG_METHOD_CLOSE('CompMovement::CompMovement', "constructor");

}

//! A destructor.
    /*!
      This is a destructor method of componentMovement class
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

	choose_type_component_movement(time);

	LOG_METHOD_CLOSE('CompMovement::update', "void");

	assert(time > 0.0 and time < 60.0 );

	UNUSED(time);
	GO(entity)->position += move;

	assert(time > 0.0 and time < 60.0 )
	chooseTypeComponentMovement(time);


	if (mType == moveType::type_bullet){
		GO(entity)->rotation = speed.angle();
	}

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
	@fn Component::type CompMovement::GetType()const
	@brief Method that sets the type of movement
	@return Component class object
	@warning Method that requires review of comment
*/

Component::type CompMovement::get_type()const{
	LOG_METHOD_START('CompMovement::get_type');

	LOG_METHOD_CLOSE('CompMovement::get_type', t_movement.to_string());

  return Component::type::t_movement;
}
