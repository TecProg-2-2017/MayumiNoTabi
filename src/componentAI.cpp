/*!
 *  \file File componentAi.cpp
 *  \brief Implementation of artificial inteligence of the in-game components
 *
 *  The class implemented here defines the AI logic behind the components
 *
 *  \sa componentAI.hpp
 */

#include <componentAI.hpp>
#include <game.hpp>

//#include <camera.hpp>
//#include <inputManager.hpp>

// TODO: Refactorate

//! A constructor.
  /*!
  This is a constructor method of the componentAI class
  */

CompAI::CompAI(aiFunc func):foo{func} { // aiFunc=function<void(CompAI*,float)>;

}

//! A destructor.
  /*!
  This is a destructor method of the componentAi class
  */

CompAI::~CompAI() {

}

/*!
  @fn       void CompAI::update(float time)
  @brief    Updates the component AI based on the time param
  @param    float value that resembles time
  @return   void
  @warning  none
*/

void CompAI::update(float time) {
  foo(this,time);  // Maybe I should leave it's name like this
}

/*!
  @fn       void CompAI::render()
  @brief    Renders component ai
  @param    none
  @return   void
  @warning  Empty
*/

void CompAI::render_component_ai() {
}

/*!
  @fn       Component::type CompAI::get_type()const
  @brief    Method that picks a component type and returns it
  @param    none
  @return   Component::type
  @warning  TODO: refactorate for better understanding
*/

Component::type CompAI::get_type()const {
  return Component::type::t_ai;
}
