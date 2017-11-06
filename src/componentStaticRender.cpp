/*!
 *  @file File componentStaticRender.cpp
 *  @brief Implementation of the class of static components in the game
 *
 *  The class implemented here provides to the game the position of the static elements
 *
 *
 *  Auxiliary documentation
 *  @sa componentStaticRender.hpp
 *
 *  @warning All variables are initialized
 */

#include <game.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <componentStaticRender.hpp>
#include <assert.h>
//#include <inputManager.hpp>


//! A constructor.
    /*!
    This is a constructor method of componentStaticRender class
    */

CompStaticRender::CompStaticRender(const Sprite &sprite,
	                                 const Vec2 &position,
																	 const bool camerascaling):sprite{sprite},position{position},
																	 cameraScaling{camerascalin}{

		// Method body its empty
		LOG_METHOD_START('CompStaticRender::CompStaticRender');
		LOG_METHOD_CLOSE('CompStaticRender::CompStaticRender', "constructor");
}

//! A destructor.
    /*!
      This is a destructor method of componentStaticRender class
    */
CompStaticRender::~CompStaticRender() {
	// Method body its empty
	LOG_METHOD_START('CompStaticRender::CompStaticRender');
	LOG_METHOD_CLOSE('CompStaticRender::CompStaticRender', "destructor");
}

/*!
	@fn CompStaticRender::Update(float time)
	@brief Method that update the current time of Sprite apparition
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void CompStaticRender::update(float time) { // Time range 0.0 - 60.0

	LOG_METHOD_START('CompStaticRender::update');
	LOG_VARIABLE("CompMovement::update", "time");

	assert(time > 0.0 and time < 60.0)

	sp.update(time);

	LOG_METHOD_CLOSE('CompStaticRender::update', "void");

}

/*!
	@fn CompStaticRender::Render()
	@brief Method that render a static element
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompStaticRender::render() {

	Vec2 position = position;

	LOG_METHOD_START('CompStaticRender::render');
	LOG_VARIABLE("CompMovement::render", "position");

	assert(position != NULL);

	camScaling(position);

	LOG_METHOD_CLOSE('CompStaticRender::render', "void");

}

/*!
	@fn Component::type CompStaticRender::get_type()const
	@brief Method that render the type element movement
	@return The method returns the type of movement of the static element
	@warning Method that requires review of comment
*/
Component::type CompStaticRender::get_type()const{

	LOG_METHOD_START('CompStaticRender::get_type');
	LOG_METHOD_CLOSE('CompStaticRender::get_type');

	return Component::type::t_static_render;

}

//! Functions to be called by the methods in order to perform actions

void camScaling(Vec2 position){

	LOG_METHOD_START('camScaling');
	LOG_VARIABLE("CompMovement::position", "position");

	assert(position != NULL);

	position = GO(entity)->Box().corner() + position.rotate(GO(entity)->rotation);
	sprite.SetFlipH(GO(entity)->flipped);

	if (camScaling) {
			sprite.Render((position-CAMERA)*CAMERAZOOM,GO(entity)->rotation, CAMERAZOOM);
	}
	else {
			sprite.Render(position,GO(entity)->rotation, 1);
	}

	LOG_METHOD_CLOSE('camScaling', "void");

}
