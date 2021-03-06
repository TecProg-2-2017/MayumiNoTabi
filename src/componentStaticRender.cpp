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
																	 const bool camerascaling):sp{sprite},pos{position},
																	 camScaling{camerascaling}{

		// Method body its empty
}

//! A destructor.
    /*!
      This is a destructor method of componentStaticRender class
    */
CompStaticRender::~CompStaticRender() {
	// Method body its empty
}

//! Functions to be called by the methods in order to perform actions

void CompStaticRender::cam_scaling(Vec2 position){

	position = GO(entity)->Box().corner() + position.rotate(GO(entity)->rotation);
	sp.SetFlipH(GO(entity)->flipped);

	if (camScaling) {
			sp.render((position-CAMERA)*CAMERAZOOM,GO(entity)->rotation, CAMERAZOOM);
	}
	else {
			sp.render(position,GO(entity)->rotation, 1);
	}
}

/*!
	@fn CompStaticRender::Update(float time)
	@brief Method that update the current time of Sprite apparition
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/
void CompStaticRender::update(float time) { // Time range 0.0 - 60.0

	assert(time > 0.0 and time < 60.0);
	sp.update(time);
}

/*!
	@fn CompStaticRender::Render()
	@brief Method that render a static element
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void CompStaticRender::render() {

	Vec2 position = position;
	cam_scaling(position);

}

/*!
	@fn Component::type CompStaticRender::get_type()const
	@brief Method that render the type element movement
	@return The method returns the type of movement of the static element
	@warning Method that requires review of comment
*/
Component::type CompStaticRender::get_type()const{
	return Component::type::t_static_render;
}
