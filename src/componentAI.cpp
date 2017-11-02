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

#include <assert.h>

//#include <camera.hpp>
//#include <inputManager.hpp>

//! A constructor.
  /*!
  This is a constructor method of the componentAI class
  */

CompAI::CompAI(aiFunc func):foo{func} { // aiFunc=function<void(CompAI*,float)>;
  LOG_METHOD_START("CompAI::CompAI");
  LOG_MSG("no code in this method...")
  LOG_METHOD_CLOSE("CompAI::CompAI", "don't know at all");
}

//! A destructor.
  /*!
  This is a destructor method of the componentAi class
  */

CompAI::~CompAI() {
  LOG_METHOD_START("CompAI::~CompAI");
  LOG_MSG("no code in this method...")
  LOG_METHOD_CLOSE("CompAI::~CompAI", "don't know at all");
}

/*!
  @fn       void CompAI::update(float time)
  @brief    Updates the component AI based on the time param
  @param    float value that resembles time
  @return   void
  @warning  none
*/

void CompAI::update(float time) {
  LOG_METHOD_START("CompAI::update");
  LOG_VARIABLE("time", time);

  foo(this, time);  // Maybe I should leave it's name like this
  
  LOG_METHOD_CLOSE("CompAI::update", "void");
}

/*!
  @fn       void CompAI::render()
  @brief    Renders component ai
  @param    none
  @return   void
  @warning  Empty
*/

void CompAI::render_component_ai() {
  LOG_METHOD_START("CompAI::render_component_ai");
  LOG_MSG("no code in this method...")
  LOG_METHOD_CLOSE("CompAI::render_component_ai", "void");
}

/*!
  @fn       Component::type CompAI::get_type()const
  @brief    Method that picks a component type and returns it
  @param    none
  @return   Component::type
  @warning  none
*/

Component::type CompAI::get_type()const {
  LOG_METHOD_START("CompAI::get_type");

  LOG_METHOD_CLOSE("CompAI::get_type", Component::type::t_ai);
  assert(Component::type::t_ai != NULL);
  return Component::type::t_ai;
}
