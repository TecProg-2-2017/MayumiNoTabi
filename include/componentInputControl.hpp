#ifndef COMPONENTINPUTCONTROLHPP
#define COMPONENTINPUTCONTROLHPP

#include <common.hpp>

#include <component.hpp>

class GameObject;

#define COMPINPUTCONT(x)  ((CompInputControl*)x. components[Component::type::t_input_control])
#define COMPINPUTCONTp(x) ((CompInputControl*)x->components[Component::type::t_input_control])

class CompInputControl : public Component{
	function<void(GameObject*, float)> func;
public:
	CompInputControl(function<void(GameObject*, float)> f);
	~CompInputControl();

	void update(float time);
	void render();
	Component::type get_type()const;
};

#endif//COMPONENTINPUTCONTROLHPP
