/*!
 *  \file File componentMovement.cpp
 *  \brief Implementation of the class of component movements present in the game
 *
 *  The class implemented here provides to the game the speed and type
 *  of movement that a given element can perform
 *
 *  \sa componentMovement.hpp
 */

#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>

//#include <camera.hpp>
//#include <inputManager.hpp>

//! A constructor.
    /*!
    This is a constructor method of componentMovement class
    */
CompMovement::CompMovement(const Vec2& sprite,moveType movetype):mType{movetype},speed{s}{}

//! A destructor.
    /*!
      This is a destructor method of componentMovement class
    */
CompMovement::~CompMovement() {}

/*!
	@fn void CompMovement::Update(float time)
	@brief Method that update element movement
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/


/*!
	@fn void CompMovement::update(float time)
	@brief Method that update element movement
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompMovement::update(float time) {
	UNUSED(time);
	GO(entity)->position+=move;
	if (mType==moveType::type_bullet)GO(entity)->rotation=speed.angle();
}

/*!
	@fn void CompMovement::render()
	@brief Method that render the new element movement
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void CompMovement::render() {}

/*!
	@fn Component::type CompMovement::GetType()const
	@brief Method that sets the type of movement
	@return Component class object
	@warning Method that requires review of comment
*/

Component::type CompMovement::get_type()const{
	return Component::type::t_movement;
}
