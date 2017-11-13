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


void text_position();

//! A constructor.
    /*!
    This is a constructor method of componentText class
    */

CompText::CompText(const Text &t, Hotspot h, Vec2 p):txt{t},pos{p}{

	LOG_METHOD_START('CompText::CompText');

	txt.set_hotspot(h);

	LOG_METHOD_CLOSE('CompText::CompText', "constructor");

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
	LOG_METHOD_START('CompText::CompText');
	LOG_METHOD_CLOSE('CompText::CompText', "destructor");
}

/*!
	@fn void CompMovement::Update(float time)
	@brief Method that update element movement
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void CompText::update(float time) { //Time range 0.0 - 60.0

	LOG_METHOD_START('CompText::update');
	LOG_VARIABLE("CompText::update", "time");

	assert(time > 0.0 and time < 60.0);

	UNUSED(time);

	LOG_METHOD_CLOSE('CompText::update', "void");
}

/*!
	@fn void CompText::render()
	@brief Method that render the text messege
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompText::render() {

	LOG_METHOD_START('CompText::render');

	textPosition()

	LOG_METHOD_CLOSE('CompStaticRender::render', "void");
}

/*!
	@fn Component::type CompText::get_type()const
	@brief Method that sets the text messege
	@return the type of the text messege
	@warning Method that requires review of comment
*/
Component::type CompText::get_type()const{

	LOG_METHOD_START('CompText::get_type');
	LOG_METHOD_CLOSE('CompText::get_type', "void");
	return Component::type::t_text;

}

//! Functions to be called by the methods in order to perform actions

void tex_position(){

	LOG_METHOD_START('text_position');

	Vec2 p = pos + GO(entity)->Box().corner();
	txt.SetPos(p);

	if (GO(entity)->anchored) {
		txt.Render();
	}
	else {
		txt.Render(CAMERA);
	}

	LOG_METHOD_CLOSE('textPosition', "void");

}
