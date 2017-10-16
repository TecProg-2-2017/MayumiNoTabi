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
  camera_is_following = true;
  camera_focus = new_focus;
}

/*!
  @fn       void Camera::unfollow()
  @brief    Method that defines the camera's focus not to follow
  @param    none
  @return   void
  @warning  none
*/

void Camera::unfollow() {
  camera_is_following = false;
}

/*!
  @fn       uint CompTimer::get_camera_focus()
  @brief    Method that returns the camera's focus value
  @param    none
  @return   unsigned int focus value
  @warning  none
*/

uint Camera::get_camera_focus() {
  return camera_focus;
}


/*!
  @fn       void Camera::update_camera(float time)
  @brief    Updates the camera
  @param    float time
  @return   void
  @warning  TODO in decision structure
*/

void Camera::update_camera(float time) {
  Vec2 center = camera_position + (WINSIZE/2/camera_zoom); //!< Newvalue for center

      // Zooms in if z key is pressed
  if (INPUT.IsKeyDown(KEY(z))) {
    camera_zoom += 0.5 * time;
    camera_zoom = min(camera_zoom, MAX_ZOOM);

    //cout<<"camera_zoom: "<<camera_zoom<<endl;
  }

  // Zooms out if x key is pressed

  if (INPUT.key_is_down(KEY(x))) {
    camera_zoom -= 0.5 * time;
    camera_zoom = max(camera_zoom, MIN_ZOOM);

    //cout<<"camera_zoom: "<<camera_zoom<<endl;
  }

  // Centers screen
  center_camera_to(center);

  // TODO: add else(do nothing)
  // Defines camera position in either follow or static or do nothing
  if (camera_is_following) {
    center_camera_to(GO(camera_focus)->Box().center());
  }
  else if (!camera_is_locked) {
    camera_speed = Vec2(0,0);

    // defines camera speed according to the arrow key that has been pressed.
    // (left)
    if (INPUT.key_is_down(KEY_LEFT)) {
      camera_speed.x -= CAMERA_SPEED;
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (right)
    if (INPUT.key_is_down(KEY_RIGHT)){
      camera_speed.x += CAMERA_SPEED;
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (up)
    if (INPUT.key_is_down(KEY_UP)) {
      camera_speed.y -= CAMERA_SPEED;
    }

    // defines camera speed according to the arrow key that has been pressed.
    // (down)
    if (INPUT.key_is_down(KEY_DOWN)) {
      camera_speed.y += CAMERA_SPEED;
    }

    // TODO: math refactoring
    camera_speed /= camera_zoom;
    camera_speed *= time;
    camera_position += camera_speed;

    // if (camera_speed != Vec2(0,0)) {
    // 	cout << "camera x= " << pos.x << "\t y= " << pos.y << endl;
    // }
  }
}

/*!
  @fn       void Camera::CenterTo(const Vec2& vector)
  @brief    Centers camera to a pre-stablished position
  @param    const Vec2& vector
  @return   void
  @warning  TODO: some math must be simplified
*/

void Camera::center_camera_to(const Vec2& vec2_vector) {
  // TODO: break down math
  Vec2 target = vec2_vector - (WINSIZE/2/camera_zoom); //!< Updates the camera 
                                                       //!< target
  // Minimum values
  camera_position.x = min(camera_position.x, target.x + camera_size.x);
  camera_position.y = min(camera_position.y, target.y + camera_size.y);

  // maximum vaues
  camera_position.x = max(camera_position.x, target.x - camera_size.x);
  camera_position.y = max(camera_position.y, target.y - camera_size.y);
}

/*!
  @fn       Vec2 Camera::render_camera_pos(const Vec2& vec2_vector)
  @brief    Renders camera's position
  @param    const Vec2& vec2_vector
  @return   Rendered camera position
  @warning  TODO: fix return to no longer be an math expression
*/

Vec2 Camera::render_camera_pos(const Vec2& vec2_vector) {
  return (vec2_vector - CAMERA) * CAMERAZOOM;
}

/*!
  @fn       float Camera::render_camera_pos_x(const float& x_axis_pos)
  @brief    Method that renders x axis position
  @param    const float& x_axis_pos
  @return   Rendered position on x axis for camera
  @warning  TODO: fix return to no longer be an math expression
*/

float Camera::render_camera_pos_x(const float& x_axis_pos) {
  return (x_axis_pos - CAMERA.x) * CAMERAZOOM;
}

/*!
  @fn       float Camera::render_camera_pos_y(const float& y_axis_pos)
  @brief    Method that renders y axis position
  @param    const float& y_axis_pos
  @return   Rendered position on y axis for camera
  @warning  TODO: fix return to no longer be an math expression
*/

float Camera::render_camera_pos_y(const float& y_axis_pos) {
  return (y_axis_pos - CAMERA.y) * CAMERAZOOM;
}
