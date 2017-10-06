#ifndef COMPONENTHPP
#define COMPONENTHPP

#include <common.hpp>

class GameObject;

class Component{
public:
	uint entity;
	enum type{
		t_first,
		t_input_control,
		t_ai,

		t__,

		t_animation,
		t_animation_control,
		t_collider,
		t_text,
		//t_click,
		t_static_render,
		//t_animated_render,
		//t_particle_emmiter,
		t_hp,
		t_movement,
		t_gravity,
		t_memory,
		t_timer,
		t_sound,
		t_count,
	};

	Component() {};
	virtual ~Component() {};

	virtual void update(float time)=0;
	virtual void render()=0;
	virtual void own(GameObject *go);
	virtual bool kills_component(float time);//return true to remove this component
	virtual type get_type()const=0;
};

#endif//COMPONENTHPP
