#ifndef COMPTIMERHPP
#define COMPTIMERHPP

#include <common.hpp>
#include <component.hpp>
#include <timer.hpp>

#define COMPTIMER(x)  ((CompTimer*)x. components[Component::type::t_timer])
#define COMPTIMERp(x) ((CompTimer*)x->components[Component::type::t_timer])

class CompTimer : public Component{
	//private members
	Timer t;
	float limit;
public:
	//public members

	CompTimer(float l);
	~CompTimer();
	void update(float time);
	void render();
	void own(GameObject* go);
	Component::type get_type()const;
};

#endif//COMPTIMERHPP
