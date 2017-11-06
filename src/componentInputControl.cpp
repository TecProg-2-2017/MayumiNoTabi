/*
*  File: componentInputControl.cpp
*
*  Description:  Implements componentInputControl class
*/

#include <componentInputControl.hpp>
#include <game.hpp>

/*!
  * @fn CompInputControl::CompInputControl()
  * @brief No params constructor method
  * @param No params
*/

CompInputControl::CompInputControl(function<void(GameObject*,float)> f):func{f} {
	LOG_METHOD_START('CompInputControl::CompInputControl');

	LOG_METHOD_CLOSE('CompInputControl::CompInputControl', "constructor");
}

/*!
  * @fn CompInputControl::~CompInputControl()
  * @brief No params destructor method
  * @param No params
*/

CompInputControl::~CompInputControl() {
	LOG_METHOD_START('CompInputControl::CompInputControl');

	LOG_METHOD_CLOSE('CompInputControl::CompInputControl', "destructor");
}

/*!
  * @fn CompInputControl::update(float time)
  * @brief Updates input control according to the time param
  * @param float time
*/

void CompInputControl::update(float time) {
	LOG_METHOD_START('CompInputControl::update');
	LOG_VARIABLE("CompInputControl::update", "time");

	assert(time >= 0);

	LOG_METHOD_CLOSE('CompGravity::CompGravity', "void");

	func(GO(entity), time);
}

/*!
  * @fn CompInputControl::render()
  * @brief Renders input control, obviously not necessary
  * @param No params
*/

void CompInputControl::render() {
	//! Non renderizable component
	LOG_METHOD_START('CompInputControl::render');

	LOG_METHOD_CLOSE('CompInputControl::render', "void");
}

/*!
  * @fn Component::type CompInputControl::get_type()
  * @brief Returns if the component is if the 'input control' type
  * @param float time
*/

Component::type CompInputControl::get_type() const {
	LOG_METHOD_START('CompInputControl::get_type');

	LOG_METHOD_CLOSE('CompInputControl::get_type', t_input_control.to_string());
	return Component::type::t_input_control;
}
