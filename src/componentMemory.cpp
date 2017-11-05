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
	LOG_METHOD_START('CompMemory::CompMemory');

	LOG_METHOD_CLOSE('CompMemory::CompMemory', "constructor");
}

/*!
  * @fn CompMemory::~CompMemory()
	* @brief No params destructor method
  * @param No params
*/

CompMemory::~CompMemory() {
	LOG_METHOD_START('CompMemory::CompMemory');

	LOG_METHOD_CLOSE('CompMemory::CompMemory', "destructor");
}

/*!
  * @fn CompMemory::update(float time)
	* @brief Updates memory according to the time param
  * @param No params
*/


void CompMemory::update(float time) {
	LOG_METHOD_START('CompMemory::update');
	LOG_VARIABLE("CompMemory::update", "time");

	assert(time >= 0);

	for(auto& t:timers) {
		t.second.add_time(time);
	}
	LOG_METHOD_CLOSE('CompMemory::update', "void");
}

/*!
  * @fn CompMemory::render()
	* @brief Renders memory, obviously not necessary
  * @param No params
*/

void CompMemory::render() {
	//! Non renderizable component
	LOG_METHOD_START('CompMemory::render');

	LOG_METHOD_CLOSE('CompMemory::render', "void");
}

/*!
  * @fn Component::type CompMemory::get_type()
	* @brief Returns if the component is if the 'memory' type
  * @param No params
	* @return Component::type::t_memory
	* @brief Obtain the component type
*/

Component::type CompMemory::get_type() const {
	LOG_METHOD_START('CompMemory::get_type');

	LOG_METHOD_CLOSE('CompMemory::get_type', t_memory.to_string());
	return Component::type::t_memory;
}
