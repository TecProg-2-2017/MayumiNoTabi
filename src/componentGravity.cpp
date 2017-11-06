/*
*  File: componentGravity.cpp
*
*  Description:  Implements CompGravity class
*/

#include <componentGravity.hpp>
#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>

/*!
	* @fn CompGravity::CompGravity(float g)
	* @brief Constructor Method for component collider
	* @param float gravity
*/

CompGravity::CompGravity(float gravity):gravity{gravity} {
	LOG_METHOD_START('CompGravity::CompGravity');
	LOG_VARIABLE("CompGravity::CompGravity", gravity);

	assert(gravity >= 0);

	LOG_METHOD_CLOSE('CompGravity::CompGravity', "constructor");
}

/*!
	* @fn CompGravity::~CompGravity()
	* @brief No params destructor method
	* @param No params
*/

CompGravity::~CompGravity() {
	LOG_METHOD_START('CompGravity::~CompGravity');

	LOG_METHOD_CLOSE('CompGravity::~CompGravity', "destructor");
}

/*!
	* @fn CompGravity::Update(float time)
	* @brief Updates the current gravity value according the 'time' param
	* @param float time
*/

void CompGravity::update(float time) {
	LOG_METHOD_START('CompGravity::update');
	LOG_VARIABLE("CompGravity::update", time);

	assert(time >= 0);

	//! Verifies if element has a type that characterizes movement in Y axis
	if(GO(entity)->HasComponent(Component::type::t_movement)) {
		COMPMOVEp(GO(entity))->speed.y += gravity*time;
	}
	else {
		// Nothing to Do
	}
	LOG_METHOD_CLOSE('CompGravity::CompGravity', "void");
}

/*!
	* @fn CompCollider::Coll::Collides(const Coll &other,const Vec2 &move,const Vec2 &moved)
	* @brief Renders gravity on screen, obviously not needed
	* @param No params
*/

void CompGravity::render() {
	//! Non renderizable component
	LOG_METHOD_START('CompGravity::render');

	LOG_METHOD_CLOSE('CompGravity::render', "void");
}

/*!
	* @fn Component::type CompGravity::get_type() const{
  * @brief Returns if the component is if the 'gravity' type
	* @param No params
	* @return Component::type::t_gravity
*/

Component::type CompGravity::get_type() const{
	LOG_METHOD_START('CompGravity::get_type');

	LOG_METHOD_CLOSE('CompGravity::get_type', t_gravity.to_string());

	return Component::type::t_gravity;
}
