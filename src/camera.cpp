/*!
 *  \file File camera.cpp
 *  \brief Implementation of Camera class
 *
 *  The class implemented here defines the game's camera logic
 *
 *  \sa camera.hpp
 */

#include <camera.hpp>

#include <common.hpp>

#include <game.hpp>
#include <gameObject.hpp>
#include <inputManager.hpp>

#include <assert.h>

// Macros declaration
#define CAMERA_SPEED 500	// unit:
#define MAX_ZOOM 1.0f		 	// unit:
#define MIN_ZOOM 0.2f			// unit:

// uint is actually the short for unsigned int
uint Camera::camera_focus = 0; //!<  Global variable defining camera focus value

Vec2 Camera::camera_position = 0;    //!<  Global variable defining camera pos
Vec2 Camera::camera_speed = 0;       //!<  Global variable defining camera speed
Vec2 Camera::camera_size{100, 50}; //!<  Global variable defining camera size

float Camera::camera_zoom = 1.0f; //!< Global variable defining camera zoom

bool Camera::camera_is_locked = false; //!< Global variable defining camera lock
bool Camera::camera_is_following = false; //!< Global variable defining camera
                                       //!< behavior

/*!
  @fn       void Camera::follow(uint new_focus)
  @brief    Method that defines the camera's focus to follow
  @param    uint new_focus
  @return   void
  @warning  none
*/

void Camera::follow(uint new_focus) { // Range: bigger than 0
  LOG_METHOD_START('Camera::follow');
  LOG_VARIABLE("new_focus", new_focus);

  assert(new_focus >= 0);

  camera_is_following = true;
  camera_focus = new_focus;

  LOG_METHOD_CLOSE('Camera::follow', "void");
}

/*!
  @fn       void Camera::unfollow()
  @brief    Method that defines the camera's focus not to follow
  @param    none
  @return   void
  @warning  none
*/

void Camera::unfollow() {
  LOG_METHOD_START('Camera::unfollow');

  camera_is_following = false;

  LOG_VARIABLE('camera_is_following', camera_is_following);
  LOG_METHOD_CLOSE('Camera::unfollow', 'void');
}


/*!
  @fn       void Camera::CenterTo(const Vec2& vector)
  @brief    Centers camera to a pre-stablished position
  @param    const Vec2& vector
  @return   void
  @warning  TODO: some math must be simplified
*/

void Camera::center_camera_to(const Vec2& vec2_vector) {
  LOG_METHOD_START('Camera::center_camera_to');
  LOG_VARIABLE('vec2_vector', vec2_vector);

  Vec2 half_winsize = WINSIZE / 2;
  Vec2 target = vec2_vector - (half_winsize / camera_zoom);//!< Updates the camera
                                                           //!< target

  LOG_VARIABLE('half_winsize', half_winsize);
  LOG_VARIABLE('target', target.to_string);

  // Minimum values
  camera_position.x = min(camera_position.x, target.x + camera_size.x);
  camera_position.y = min(camera_position.y, target.y + camera_size.y);

  // maximum vaues
  camera_position.x = max(camera_position.x, target.x - camera_size.x);
  camera_position.y = max(camera_position.y, target.y - camera_size.y);

  LOG_METHOD_CLOSE("Camera::center_camera_to", "void");
}

/*!
  @fn       void Camera::update_camera(float time)
  @brief    Updates the camera
  @param    float time
  @return   void
  @warning  none
*/

void Camera::update_camera(float time) {
  LOG_METHOD_START('Camera::update_camera');
  LOG_VARIABLE("time", time);

  Vec2 half_winsize = WINSIZE / 2;

  Vec2 center = camera_position + (half_winsize / camera_zoom); //!< Newvalue for center

  LOG_VARIABLE("center", center.to_string);

  // Updates zoom
  update_camera_zoom(time);
  // Centers screen
  center_camera_to(center);
  // Updates screen
  update_camera_speed(time);

  LOG_METHOD_CLOSE('Camera::update_camera', 'void');
}

/*!
  @fn       uint CompTimer::get_camera_focus()
  @brief    Method that returns the camera's focus value
  @param    none
  @return   unsigned int focus value
  @warning  none
*/

uint Camera::get_camera_focus() {
  LOG_METHOD_START('Camera::get_camera_focus');
  LOG_METHOD_CLOSE('Camera::get_camera_focus', camera_focus);

  assert(camera_focus >= 0);
  return camera_focus;
}

/*!
  @fn       Vec2 Camera::render_camera_pos(const Vec2& vec2_vector)
  @brief    Renders camera's position
  @param    const Vec2& vec2_vector
  @return   Rendered camera position
  @warning  TODO: fix return to no longer be an math expression
*/

Vec2 Camera::render_camera_pos(const Vec2& vec2_vector) {
  LOG_METHOD_START("Camera::render_camera_pos");
  LOG_VARIABLE("vec2_vector", vec2_vector);


  Vec2 rendered_camera_pos = (vec2_vector - CAMERA) * CAMERAZOOM;

  LOG_METHOD_CLOSE("Camera::render_camera_pos", rendered_camera_pos.to_string());

  return rendered_camera_pos;
}

/*!
  @fn       void Camera::update_camera_zoom(float time)
  @brief    Updates the camera's zoom
  @param    float time
  @return   void
  @warning  none
*/

void Camera::update_camera_zoom(float time) {
  LOG_METHOD_START("Camera::update_camera_zoom");
  LOG_VARIABLE("time", time);

  // Zooms in if z key is pressed
  if (INPUT.IsKeyDown(KEY(z))) {
    LOG_MSG("if (INPUT.IsKeyDown(KEY(z)))");

    camera_zoom = camera_zoom + (0.5 * time);
    camera_zoom = min(camera_zoom, MAX_ZOOM);
  }
  else {
    // Do nothing
  }

  // Zooms out if x key is pressed
  if (INPUT.key_is_down(KEY(x))) {
    LOG_MSG("if (INPUT.IsKeyDown(KEY(x)))");

    camera_zoom = (0.5 * time) - camera_zoom;
    camera_zoom = max(camera_zoom, MIN_ZOOM);
  }
  else {
    // Do nothing
  }

  LOG_METHOD_CLOSE("Camera::update_camera_zoom", "void");
}

/*!
  @fn       void Camera::update_camera_speed(float time)
  @brief    Updates the camera's speed
  @param    float time
  @return   void
  @warning  none
  */

void Camera::update_camera_speed(float time) {
  LOG_METHOD_START("Camera::update_camera_speed");
  LOG_VARIABLE("time", time);

  // Defines camera position in either follow or static or do nothing
  if (camera_is_following) {
    LOG_MSG("if (camera_is_following)");

    center_camera_to(GO(camera_focus)->Box().center());
  }
  else if (!camera_is_locked) {
    LOG_MSG("else if (!camera_is_locked)");

    camera_speed = Vec2(0, 0);

    // defines camera speed according to the arrow key that has been pressed.
    // (left)
    if (INPUT.key_is_down(KEY_LEFT)) {
      LOG_MSG("if (INPUT.key_is_down(KEY_LEFT))");

      camera_speed.x = camera_speed.x - CAMERA_SPEED;
    }
    else {
      // Do nothing
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (right)
    if (INPUT.IsKeyDown(KEY_RIGHT)) {
      LOG_MSG("if (INPUT.IsKeyDown(KEY_RIGHT)");

      camera_speed.x = camera_speed.x + CAMERA_SPEED;
    }
    else {
      // Do nothing
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (up)
    if (INPUT.key_is_down(KEY_UP)) {
      LOG_MSG("if (INPUT.key_is_down(KEY_UP)");

      camera_speed.y = camera_speed.y - CAMERA_SPEED;
    }
    else {
      // Do nothing
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (down)
    if (INPUT.key_is_down(KEY_DOWN)) {
      LOG_MSG("if (INPUT.key_is_down(KEY_DOWN))");

      camera_speed.y = CAMERA_SPEED + camera_speed.y;
    }
    else {
      // Do nothing
    }

    camera_speed = camera_speed / camera_zoom;
    camera_speed = camera_speed * time;
    camera_position = camera_position + camera_speed;
  }
  LOG_METHOD_CLOSE("Camera::update_camera_speed", "void");
}

/*!
  @fn       float Camera::render_camera_pos_x(const float& x_axis_pos)
  @brief    Method that renders x axis position
  @param    const float& x_axis_pos
  @return   Rendered position on x axis for camera
  @warning  TODO: fix return to no longer be an math expression
*/

float Camera::render_camera_pos_x(const float& x_axis_pos) {
  LOG_METHOD_START("Camera::render_camera_pos_x");
  LOG_VARIABLE("x_axis_pos", x_axis_pos);

  // Stores return value
  float rendered_x = (x_axis_pos - CAMERA.x) * CAMERAZOOM;

  LOG_METHOD_CLOSE("Camera::render_camera_pos_y", rendered_x);
  return rendered_x;
}

/*!
  @fn       float Camera::render_camera_pos_y(const float& y_axis_pos)
  @brief    Method that renders y axis position
  @param    const float& y_axis_pos
  @return   Rendered position on y axis for camera
  @warning  TODO: fix return to no longer be an math expression
*/

float Camera::render_camera_pos_y(const float& y_axis_pos) {
  LOG_METHOD_START("Camera::render_camera_pos_y");
  LOG_VARIABLE("y_axis_pos", y_axis_pos);

  // Stores return value
  float rendered_y = (y_axis_pos - CAMERA.y) * CAMERAZOOM;

  LOG_METHOD_CLOSE("Camera::render_camera_pos_y", rendered_y);
  return rendered_y;
}
