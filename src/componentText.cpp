/*!
 *  @file File componentText.cpp
 *  @brief Implementation of the class of text components present in the game
 *
 *  The class implemented here provides to the game the messeges elements
 *
 *  Auxiliary documentation
 *  @sa componentText.hpp
 *
 *  @warning All variables are initialized
 */


#include <game.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <componentText.hpp>
#include <assert.h>
//#include <inputManager.hpp>

//! Functions to be called by the methods in order to perform actions

void CompText::textPosition(){
	Vec2 p = pos + GO(entity)->Box().corner();
	txt.set_box_position(p);

	if (GO(entity)->anchored) {
		txt.render();
	}
	else {
		txt.render(CAMERA);
	}
}


//! A constructor.
    /*!
    This is a constructor method of componentText class
    */
CompText::CompText(const Text &t, Hotspot h, Vec2 p):txt{t},pos{p}{
	txt.set_hotspot(h);
}

//! A constructor.
    /*!
    This is a another constructor method of componentText class
		with overload
    */
CompText::CompText(string text, int size, SDL_Color c, Hotspot h, Vec2 p):txt{text, size, c},pos{p}{
	txt.set_hotspot(h);
}

//! A destructor.
    /*!
      This is a destructor method of componentText class
    */
CompText::~CompText() {
	// Method body its empty
}

/*!
	@fn void CompMovement::Update(float time)
	@brief Method that update element movement
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void CompText::update(float time) { //Time range 0.0 - 60.0

	assert(time > 0.0 and time < 60.0);
	UNUSED(time);
}

/*!
	@fn void CompText::render()
	@brief Method that render the text messege
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompText::render() {
	textPosition();
}

/*!
	@fn Component::type CompText::get_type()const
	@brief Method that sets the text messege
	@return the type of the text messege
	@warning Method that requires review of comment
*/
Component::type CompText::get_type()const{
	return Component::type::t_text;
}
