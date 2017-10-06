#ifndef COMPANIMATIONCONTROLLERHPP
#define COMPANIMATIONCONTROLLERHPP

#include <common.hpp>

#include <component.hpp>
#include <geometry.hpp>
#include <componentAnimation.hpp>

#define COMPANIMCONT(x)  ((CompAnimControl*)x.components[Component::type::t_animation_control])
#define COMPANIMCONTPOINTER(x) ((CompAnimControl*)x->components[Component::type::t_animation_control])

class Collider;

class CompAnimControl : public Component{
  //private members
  map<string,unique_ptr<CompAnim>> animations;
  string cur;
  string prev;
  bool repeat=true;
  bool dying=false;
public:
  //public members
  CompAnimControl(string filename,CompCollider* collider);
  ~CompAnimControl();

  void change_current(string anim,bool rep=true);
  CompAnim& get_current();
  const string& get_current_name()const;
  string& get_current_name();

  void update(float time);
  void render();
  void own(GameObject *game_object);
  bool kills_component(float time);
  Component::type get_type()const;
};

#endif
