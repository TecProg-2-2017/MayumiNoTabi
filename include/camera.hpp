#ifndef CAMERAHPP
#define CAMERAHPP

#include <common.hpp>

#include <geometry.hpp>
#include <inputManager.hpp>

class GameObject;

#define CAMERA Camera::camera_position
#define CAMERAZOOM Camera::camera_zoom
#define CAMERALOCK Camera::camera_is_locked
#define RENDERPOS Camera::render_camera_pos
#define RENDERPOSX Camera::render_camera_pos_x
#define RENDERPOSY Camera::render_camera_pos_y


class Camera {
  static bool camera_is_following;
  static uint camera_focus;

public:
  static Vec2 camera_position;
  static Vec2 camera_speed;
  static Vec2 camera_size;
  static float camera_zoom;
  static bool camera_is_locked;

  static void follow(uint new_focus);
  static void unfollow();
  static uint get_camera_focus();

  static void update_camera(float time);
  static void update_camera_zoom(float time);
  static void update_camera_speed(float time);

  static void center_camera_to(const Vec2& vec2_vector);

  static Vec2 render_camera_pos(const Vec2& vec2_vector);
  static float render_camera_pos_x(const float& x_axis_pos);
  static float render_camera_pos_y(const float& y_axis_pos);
};

#endif
