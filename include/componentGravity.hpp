#ifndef COMPGRAVITYHPP
#define COMPGRAVITYHPP

#include <common.hpp>
#include <component.hpp>

#define COMPGRAVITY(x)  ((CompGravity*)x. components[Component::type::t_gravity])
#define COMPGRAVITYp(x) ((CompGravity*)x->components[Component::type::t_gravity])

class CompGravity : public Component{
	//private members
	float gravity;
public:
	//public members
	CompGravity(float gravity=GRAVITY);
	~CompGravity();

	void update(float time);
	void render();
	Component::type get_type() const;
};

#endif//COMPGRAVITYHPP
