/*!
 *  \file File componentAnimation.cpp
 *  \brief Implementation of CompAnim class
 *
 *  This file has the implementation of CompAnim class
 *
 *  \sa componentAnimation.hpp
 */

#include <componentAnimation.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <complib.hpp>
#include <game.hpp>
#include <stateStage.hpp>
#include <txtFuncs.hpp>

#include <assert.h>

// #include <inputManager.hpp>

//! A constructor.
  /*!
  This is a constructor method of CompAnim class
  */

// Constructor method with no params
CompAnim::CompAnim() {
  LOG_METHOD_START("CompAnim::CompAnim (blank)");
  LOG_METHOD_CLOSE("CompAnim::CompAnim (blank)", "constructor");
}

//! A constructor.
  /*!
   This is a constructor method of CompAnim class
  */

CompAnim::CompAnim(string filename, CompCollider* temporary_collider) {
  LOG_METHOD_START("CompAnim::CompAnim");
  LOG_VARIABLE("filename", filename);

  assert(filename != "");

	ifstream in(ANIMATION_PATH + filename + ".txt");

	// Treats possible file opening error
	if (!in.is_open()) {
    cerr << "Erro ao abrir arquivo de animação '" << filename << "'" << endl;
  }
  else {
    string name = "";
    string img_file = "";
    string animation_file = "";
    string type = "";

    int f_count = 0;
    int f_counter_x = 0;
    int f_counter_y = 0;
    int collider_counter = 0;

    float f_time = 0;
    float x_axis = 0;
    float y_axis = 0;
    float width = 0;
    float height = 0;
    float r = 0;

    in >> img_file;
    in >> f_count;
    in >> f_counter_x;
    in >> f_counter_y;
    in >> f_time;

		sp.Open(img_file, f_counter_x, f_counter_y, f_time, f_count);

		colliders.resize(f_count, nullptr);

		FOR(i, f_count) {
      in >> collider_counter;

			if (collider_counter) {
        colliders[i] = new CompCollider{};
				colliders[i]->entity = entity;

				FOR(j, collider_counter) {

          in >> x_axis;
          in >> y_axis;
          in >> width;
          in >> height;
          in >> r;

          colliders[i]->colls.emplace_back(entity,
            temporary_collider->colls[0].cType,
            Rect{x_axis, y_axis, width, height});

            colliders[i]->colls[j].useDefault = temporary_collider->colls[0].useDefault;
            colliders[i]->colls[j].active = temporary_collider->colls[0].active;
          }
        }
        else {
          // Do nothing
        }

        int function_counter = 0;
        in >> function_counter;

        string function_name = "";

        FOR(funcI, function_counter) {
          in >> function_name;

          if (txtFuncsF.count(function_name)) {
            frameFunc[i].push_back(txtFuncsF[function_name](in));
          }
          else {
            // Do nothing
          }
        }
      }

      in.close();
    }

    // Changes called value to false if frameFunc has no elements in it
    if (frameFunc.count(0)) {
      called = false;
    }
    else {
      // Do nothing
  }

  LOG_METHOD_CLOSE("CompAnim::CompAnim", "constructor");
}

//! A destructor.
  /*!
  This is a destructor method of CompAnim class
  */

CompAnim::~CompAnim() {
  LOG_METHOD_START("CompAnim::~CompAnim");
  // Iterates through coliders

  FOR(i, colliders.size()) {

		// Ignores deletion if current collider equals current frame
		if (i == get_current_frame()) {
			continue;
    }
    else {
      // Do nothing
    }

    delete colliders[i];
  }

  LOG_METHOD_CLOSE("CompAnim::~CompAnim", "destructor");
}

/*!
  @fn       bool CompAnim::Looped()const
  @brief    Returns if the animation is looped (true) or not (false)
  @param    none
  @return   bool velue defining if animation is looped or not
  @warning  none
*/

bool CompAnim::is_looped()const {
  LOG_METHOD_START("CompAnim::Looped");

  bool is_animation_looped = sp.is_looped();

  LOG_METHOD_CLOSE("CompAnim::Looped", is_animation_looped);
  assert(is_animation_looped == true || is_animation_looped == false);
  return is_animation_looped;
}

/*!
	@fn       void CompAnim::update(float time)
	@brief    updates the animation
	@param    float time
	@return   void
	@warning  none
*/

void CompAnim::update(float time) {
  LOG_METHOD_START("CompAnim::update");
  LOG_VARIABLE("time", time);

  int frame1 = get_current_frame(); //!< Used later for comparrison with next frame
  int frame2 = get_current_frame(); //!< Assigns the new frame to this variable for
  //!< comparing with the previous one

  LOG_VARIABLE("frame1", frame1);
  LOG_VARIABLE("frame2", frame2);

  // Checks if the animation has not been called && calls it
  checks_animation_call(frame1);

	sp.update(time);

  set_new_frame(frame1, frame2);

  LOG_METHOD_CLOSE("CompAnim::update", "void");
}

/*!
  @fn       void CompAnim::checks_animation_call(int frame)
  @brief    checks if the animation has been called
  @param    int frame
  @return   void
  @warning  none
*/

void CompAnim::checks_animation_call(int frame) {
  LOG_METHOD_START("CompAnim::checks_animation_call");
  LOG_VARIABLE("frame", frame);
  LOG_VARIABLE("called", called);

  assert(frame >= 0);

  if (!called) {
    // Iterates through frame
    for (auto &foo : frameFunc[frame]) {
      foo(GO(entity));
    }

    called = true;
  }
  else {
    // Do nothing
  }
  LOG_METHOD_CLOSE("CompAnim::checks_animation_call", "void");
}

/*!
	@fn       void CompAnim::render()
	@brief    renders current animation
	@param    none
	@return   void
	@warning  none
*/

void CompAnim::render() {
  LOG_METHOD_START("CompAnim::render");

  Rect full_box = GO(entity)->FullBox(); //!< Used to save the
  //!< position to render
  Vec2 corner = full_box.corner();
  Vec2 render_pos = corner.renderPos();

  sp.SetFlipH(GO(entity)->flipped);
	sp.render(render_pos, GO(entity)->rotation, Camera::camera_zoom);

  LOG_METHOD_CLOSE("CompAnim::render", "void");
}

/*!
  @fn       void CompAnim::own(GameObject* go)
  @brief    Sets ownage of a animation to a game object
  @param    GameObject* go
  @return   void
  @warning  none
*/

void CompAnim::own(GameObject* go) {
  LOG_METHOD_START("CompAnim::own");

	entity = go->uid;

	// Iterates through the colliders and defines its ownage if they're not null
	for (CompCollider *coll:colliders) {
    if (coll != nullptr) {
      coll->own(go);
    }
    else {
      // Do nothing
    }
  }

  int frame = get_current_frame();

  set_current_frame(frame, true);

  LOG_METHOD_CLOSE("CompAnim::own", "void");
}

/*!
  @fn       void CompAnim::compare_frames(int frame1, int frame2)
  @brief    compares the frames
  @param    int frame1, int frame2
  @return   bool
  @warning  none
*/

bool CompAnim::compare_frames(int frame1, int frame2) {
  LOG_METHOD_START("CompAnim::compare_frames");
  LOG_VARIABLE("frame1", frame1);
  LOG_VARIABLE("frame2", frame2);

  assert(frame1 >= 0 and frame2 >= 0);

  if (frame1 != frame2) {
    LOG_METHOD_CLOSE("CompAnim::compare_frames", 'true');

    return true;
  }
  else {
    LOG_METHOD_CLOSE("CompAnim::compare_frames", 'false');

    return false;
  }
}

/*!
  @fn       int CompAnim::get_frame_count()const
  @brief    Returns current frame count as a integer
  @param    none
  @return   int value of frame count
  @warning  none
*/

int CompAnim::get_frame_count() const {
  LOG_METHOD_START("CompAnim::get_frame_count");

  int qtd_frame = sp.get_frame_count();

  LOG_METHOD_CLOSE("CompAnim::get_frame_count", qtd_frame);
  return qtd_frame;
}

/*!
  @fn       int CompAnim::get_current_frame()const
  @brief    Returns current frame as a integer
  @param    none
  @return   int with the number of the current frame
  @warning  none
*/

int CompAnim::get_current_frame() const {
  LOG_METHOD_START("CompAnim::get_current_frame");

  int current_frame = sp.get_current_frame();

  LOG_METHOD_CLOSE("CompAnim::get_current_frame", current_frame);
  assert(current_frame > -1);
  return current_frame;
}

/*!
  @fn       void CompAnim::set_current_frame(int frame, bool force)
  @brief    Sets the current frame
  @param    int frame, bool force
  @return   void
  @warning  none
*/

void CompAnim::set_current_frame(int frame, // range: unknown
                                 bool force) { // true to force current frame

  LOG_METHOD_START("CompAnim::set_current_frame");
  LOG_VARIABLE("frame", frame);
  LOG_VARIABLE("force", force);


  // Set frame as current if it isn't already
  if (frame != get_current_frame()) {
    sp.set_frame(frame);

    for (auto &foo : frameFunc[frame]) {
      foo(GO(entity));
    }

    called = true;
    force = true;
  }
  else {
    // Do nothing
  }

  // Sets current frame by force
  set_current_frame_by_force(frame, force);
}

/*!
  @fn       void CompAnim::set_new_frame(int frame1, int frame2)
  @brief    sets the new frame if it is not already set
  @param    int frame1, int frame2
  @return   void
  @warning  none
*/

void CompAnim::set_new_frame(int frame1, int frame2) {
  LOG_METHOD_START("CompAnim::set_new_frame");
  LOG_VARIABLE("frame1", frame1);
  LOG_VARIABLE("frame2", frame2);

  assert(frame1 >= 0 and frame2 >= 0);

  // Checks if current frames is the same as the next one, if they're not the
  // next frame is set
  if (compare_frames(frame1, frame2)) {
    called = false;
    set_current_frame(frame2, true);
  }
  else {
    // Do nothing
  }
  LOG_METHOD_CLOSE("CompAnim::set_new_frame", "void");
}

/*!
@fn       void CompAnim::set_current_frame_by_force(int frame, bool force)
@brief    Sets the current frame by force
@param    int frame, bool force
@return   void
@warning  none
*/

void CompAnim::set_current_frame_by_force(int frame,
                                          bool force) {

  LOG_METHOD_START("CompAnim::set_current_frame_by_force");
  LOG_VARIABLE("frame", frame);
  LOG_VARIABLE("force", force);


  // Sets current frame by force
  if (force == true) {

    // proceeds if frame exists or sets as null
    if (colliders[frame] != nullptr) {
      GO(entity)->SetComponent(Component::type::t_collider, colliders[frame]);
    }
    else if (GO(entity)->HasComponent(Component::type::t_collider)) {
      GO(entity)->components[Component::type::t_collider] = nullptr;
    }
    else {
      // Do nothing
    }
  }
  else {
    // Do nothing
  }
  LOG_METHOD_CLOSE("CompAnim::set_current_frame_by_force", "void");
}

/*!
	@fn       Component::type CompAnim::get_type()const
	@brief    Returns type of the animation as a constant value
	@param    none
	@return   Component::type type of the animation
	@warning  none
*/

Component::type CompAnim::get_type()const {
  LOG_METHOD_START("CompAnim::get_type");
  LOG_METHOD_CLOSE("CompAnim::get_type", Component::type::t_animation);
  return Component::type::t_animation;
}
