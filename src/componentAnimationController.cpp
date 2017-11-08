/*!
 *  \file File componentAnimationController.cpp
 *  \brief Implementation of componentAnimationController class
 *
 *  The class implemented here is a controller for the animations
 *
 *  \sa componentAnimationController.hpp
 */

#include <componentAnimationController.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <game.hpp>

#include <assert.h>

//#include <inputManager.hpp>

//! A constructor.
  /*!
  This is a constructor method of CompAnimControl class
  */

CompAnimControl::CompAnimControl(string filename, CompCollider* collider) {
  LOG_METHOD_START("CompAnimControl::CompAnimControl");
  LOG_VARIABLE("filename", filename);
  LOG_VARIABLE("collider", collider.to_string());

  assert(collider != NULL);
  assert(filename != "");

  ifstream in(ANIMATION_PATH + filename + ".txt");

  // Checks if the animation's .txt file is already opened
  if (!in.is_open()) {
    cerr << "Erro ao abrir arquivo de grupo de animações '" << filename << "'";
    cerr << endl;
  }
  else {
    string name = "";
    string animation_filename = "";

    in >> name;
    in >> animation_filename;

    prev = name;
    cur = prev;

    animations[name] = make_unique<CompAnim>(animation_filename, collider);

    while (in >> name >> animation_filename) {
      animations[name] = make_unique<CompAnim>(animation_filename, collider);
    }

    in.close();
  }

  LOG_METHOD_CLOSE("CompAnimControl::CompAnimControl", "constructor");
}

//! A destructor.
  /*!
  This is a destructor method of CompAnimControl class
  */

CompAnimControl::~CompAnimControl() {
  LOG_METHOD_START("CompAnimControl::~CompAnimControl");
  LOG_METHOD_CLOSE("CompAnimControl::~CompAnimControl", "destructor");
}

/*!
  @fn       bool CompAnimControl::kills_component(float time)
  @brief    Method for rendering player's death animation
  @param    float time value
  @return   boolean value
  @warning  TODO: alternative flux in condition structures
*/

bool CompAnimControl::kills_component(float time) { // range: unknown
  LOG_METHOD_START("CompAnimControl::kills_component");
  LOG_VARIABLE("time", time);
  UNUSED(time);

  // Checks if die animation isn't in animations
  if (!animations.count("die")) {
    return true;
  }
  else {
    // Do nothing
  }

  // Checks if player is dying
  if (dying) {

    // Makes method return true if current animation isn't player's death
    if (cur != "die") {
      LOG_METHOD_CLOSE("CompAnimControl::kills_component", "true");
      return true;
    }
    else {
      // Do nothing
    }
  }
  else {
    change_current("die", false);
    dying = true;
  }

  LOG_METHOD_CLOSE("CompAnimControl::kills_component", "false");
  return false;
}

/*!
  @fn       void CompAnimControl::change_current(string anim, bool rep)
  @brief    Changes current animation
  @param    string anim, bool rep
  @return   void
  @warning  none
*/

void CompAnimControl::change_current(string animation_name,
                            bool repeat_animation) {// repeats animation if true
  LOG_METHOD_START("CompAnimControl::change_current");
  LOG_VARIABLE("animation_name", animation_name);
  LOG_VARIABLE("repeat_animation", repeat_animation);

  assert(animation_name != "");

  // Checks if animations vector has anything
  if (animations.count(animation_name)) {

    // TODO: add else (do nothing)
    // Checks if current animation is the one to be shown
    if (cur != animation_name) {

      // If true, makes the animation repeat itself
      if (repeat) {
        prev = cur;
      }
      else {
        // Do nothing
      }

      repeat = repeat_animation;
      cur = animation_name;

      get_current().set_current_frame(0);
      get_current().sp.looped = false;
      get_current().own(GO(entity));
    }
    else {
      // Do nothing
    }
  }
  else {
    cerr << "Erro: Controle de animação nao tem animação '";
    cerr << animation_name;
    cerr << "' entity uid = " << entity << endl;
  }

  LOG_METHOD_CLOSE("CompAnimControl::change_current", "void");
}

/*!
  @fn       void CompAnimControl::update(float time)
  @brief    Updates the animation according to time
  @param    float value resembling time
  @return   void
  @warning  none
*/

void CompAnimControl::update(float time) {
  LOG_METHOD_START("CompAnimControl::update");
  LOG_VARIABLE("time", time);

  // Checks if current animation is in the 'library'
  if (animations.count(cur)) {
    get_current().update(time);

    // Checks if current animation is a looped type or set to repeat
    if (!repeat and get_current().is_looped()) {

      // Defines current frame as 'dead' if Mayumi dies
      if (dying) {
        cur = "dead";
      }
      else {
        change_current(prev);

        get_current().sp.looped = false;
        get_current().update(time);
      }
    }
    else {
      // Do nothing
    }
  }
  else {
    // Do nothing
  }
  LOG_METHOD_CLOSE("CompAnimControl::update", "void");
}

/*!
  @fn       void CompAnimControl::render()
  @brief    Renders current animation
  @param    none
  @return   void
  @warning  none
*/

void CompAnimControl::render() {
  LOG_METHOD_START("CompAnimControl::render");

  // Tries to find the current animation on animations vector, render if found
  if (animations.count(cur)) {
    get_current().render();
  }
  else {
    // Do nothing
  }
  LOG_METHOD_CLOSE("CompAnimControl::render", "void");
}

/*!
  @fn       void CompAnimControl::own(GameObject *go)
  @brief    Sets ownage of animation to a Game Object
  @param    GameObject object
  @return   void
  @warning  none
*/

void CompAnimControl::own(GameObject *game_object) {
  LOG_METHOD_START("CompAnimControl::own");
  LOG_VARIABLE("game_object", game_object.to_string());

  assert(game_object != NULL);

  entity = go->uid;

  for (auto &anim:animations) {
    anim.second->own(go);
  }

  get_current().own(go);
  LOG_METHOD_CLOSE("CompAnimControl::own", "void");
}

/*!
  @fn
  @brief    Returns current animation object
  @param    none
  @return   CompAnim& type animation object pointer
  @warning  none
*/

CompAnim &CompAnimControl::get_current() {
  LOG_METHOD_START("CompAnimControl::get_current");
  LOG_METHOD_CLOSE("CompAnimControl::get_current", "pointer to current animation");

  assert(*animations[cur] != NULL);
  return *animations[cur];
}

/*!
  @fn       const string& CompAnimControl::get_current_name()const
  @brief    Returns current animation's name as a constant
  @param    none
  @return   const string with animation name
  @warning  none
*/

const string &CompAnimControl::get_current_name() const {
  LOG_METHOD_START("CompAnimControl::get_current_name");
  LOG_METHOD_CLOSE("CompAnimControl::get_current_name", current);
  assert(current != '');
  return current;
}

/*!
  @fn       string& CompAnimControl::get_current_name()
  @brief    Returns current animation's name
  @param    none
  @return   string with current animation's name
  @warning  none
*/

string &CompAnimControl::get_current_name() {
  LOG_METHOD_START("CompAnimControl::get_current_name");
  LOG_METHOD_CLOSE("CompAnimControl::get_current_name", current);
  assert(current != "");
  return current;
}

/*!
  @fn       Component::type CompAnimControl::get_type()const
  @brief    Returns type of component (or animation) as a constant
  @param    none
  @return   const Component::type
  @warning  none
*/

Component::type CompAnimControl::get_type()const {
  LOG_METHOD_START("CompAnimControl::get_type");
  LOG_METHOD_CLOSE("CompAnimControl::get_type", Component::type::t_animation_control.to_string());
  assert(Component::type::t_animation_control != NULL);
  return Component::type::t_animation_control;
}
