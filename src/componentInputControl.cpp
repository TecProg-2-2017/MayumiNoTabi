/*
*  File: componentInputControl.cpp
*
*  Description:  Implements componentInputControl class
*/

#include <componentInputControl.hpp>
#include <game.hpp>

CompInputControl::CompInputControl(function<void(GameObject*,float)> f):func{f} {
}

/*!
  * @fn CompInputControl::~CompInputControl()
  * @brief No params destructor method
  * @param No params
*/

CompInputControl::~CompInputControl() {

}

/*!
  * @fn CompInputControl::Update(float time)
  * @brief Updates input control according to the time param
  * @param float time
*/

void CompInputControl::update(float time) {
	func(GO(entity),time);
}

/*!
  * @fn CompInputControl::Render()
  * @brief Renders input control, obviously not necessary
  * @param No params
*/

void CompInputControl::render() {
}

/*!
  * @fn Component::type CompInputControl::GetType()
  * @brief Returns if the component is if the 'input control' type
  * @param float time
*/

Component::type CompInputControl::get_type() const {
	return Component::type::t_input_control;
}
