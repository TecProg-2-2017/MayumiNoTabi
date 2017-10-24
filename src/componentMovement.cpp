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

//! Functions to be called by the methods in order to perform actions

void chooseTypeComponentMovement(float time){

	UNUSED(time);
	GO(entity)->position += move;

	if (mType == moveType::type_bullet){
		GO(entity)->rotation = speed.angle();
	}
	else {
		//Nothing to do
	}
}


//! A constructor.
    /*!
    This is a constructor method of componentMovement class
    */

CompMovement::CompMovement(const Vec2& sprite,moveType movetype):

	mType{movetype},speed{s}{
		// Method body its empty
}

//! A destructor.
    /*!
      This is a destructor method of componentMovement class
    */

CompMovement::~CompMovement() {
	// Method body its empty
}


/*!
	@fn void CompMovement::Update(float time)
	@brief Method that update element movement
	@param float time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompMovement::update(float time) {

	chooseTypeComponentMovement(time);

}

/*!
	@fn void CompMovement::render()
	@brief Method that render the new element movement
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/


void CompMovement::render() {
	// Method body its empty
}



/*!
	@fn Component::type CompMovement::GetType()const
	@brief Method that sets the type of movement
	@return Component class object
	@warning Method that requires review of comment
*/
Component::type CompMovement::get_type()const{
  return Component::type::t_movement;
}
