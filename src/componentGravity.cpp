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

}

/*!
	* @fn CompGravity::~CompGravity()
	* @brief No params destructor method
	* @param No params
*/

CompGravity::~CompGravity() {

}

/*!
	* @fn CompGravity::Update(float time)
	* @brief Updates the current gravity value according the 'time' param
	* @param float time
*/

void CompGravity::update(float time) {
	//! Verifies if element has a type that characterizes movement in Y axis
	if(GO(entity)->HasComponent(Component::type::t_movement)) {
		COMPMOVEp(GO(entity))->speed.y+=gravity*time;
	}
}

/*!
	* @fn CompCollider::Coll::Collides(const Coll &other,const Vec2 &move,const Vec2 &moved)
	* @brief Renders gravity on screen, obviously not needed
	* @param No params
*/

void CompGravity::render() {

}

/*!
	* @fn Component::type CompGravity::get_type() const{
  * @brief Returns if the component is if the 'gravity' type
	* @param No params
	* @return Component::type::t_gravity
*/

Component::type CompGravity::get_type() const{
	return Component::type::t_gravity;
}
