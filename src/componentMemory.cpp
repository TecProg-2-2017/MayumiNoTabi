/*
*  File: componentMemory.cpp
*
*  Description:  Implements componentMemory class
*/

#include <componentMemory.hpp>

/*!
  * @fn CompMemory::CompMemory()
	* @brief No params constructor method
  * @param No params
*/

CompMemory::CompMemory() {

}

/*!
  * @fn CompMemory::~CompMemory()
	* @brief No params destructor method
  * @param No params
*/

CompMemory::~CompMemory() {

}

/*!
  * @fn CompMemory::update(float time)
	* @brief Updates memory according to the time param
  * @param No params
*/


void CompMemory::update(float time) {
	//! TODO: Refactorate decision strucuture
	for(auto& t:timers)t.second.add_time(time);
}

/*!
  * @fn CompMemory::Render()
	* @brief Renders memory, obviously not necessary
  * @param No params
*/

void CompMemory::render() {

}

/*!
  * @fn Component::type CompMemory::get_type()
	* @brief Returns if the component is if the 'memory' type
  * @param No params
	* @return Component::type::t_memory
	* @brief Obtain the component type
*/

Component::type CompMemory::get_type() const {
	return Component::type::t_memory;
}
