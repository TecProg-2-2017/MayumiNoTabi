/*!
 *  \file File component.cpp
 *  \brief Implementation of Component class
 *
 *  Here is the implementation of Component's methods
 *
 *  \sa component.hpp
 */

#include <component.hpp>
#include <gameObject.hpp>

#include <assert.h>

/*!
  @fn       bool Component::kills_component(float time)
  @brief    Sets the death of a component
  @param    float time
  @return   boolean value
  @warning  none
*/

bool Component::kills_component(float time) {
  LOG_METHOD_START("Component::kills_component");
  LOG_VARIABLE("time", time);

  UNUSED(time);

  LOG_METHOD_CLOSE("Component::kills_component", "true (hardcoded)");

  // How can I possibly check this??
  return true;
}

/*!
  @fn       void Component::own(GameObject *go)
  @brief    Assigns a object as property (like a ownage thing) of a component
  @param    GameObject *go
  @return   void
  @warning  none
*/

void Component::own(GameObject *go) {
  LOG_METHOD_START("Component::own");
  // LOG_VARIABLE("go", go.to_string);

  assert(go != NULL);

  entity = go->uid;

  LOG_METHOD_CLOSE('Componet::own', 'void');
}
