#ifndef COMPONENTAIHPP
#define COMPONENTAIHPP

#include <common.hpp>
#include <component.hpp>

class CompAI;
using aiFunc=function<void(CompAI*,float)>;

#define COMPAI(x)  ((CompAI*)x. components[Component::type::t_ai])
#define COMPAIp(x) ((CompAI*)x->components[Component::type::t_ai])

class CompAI : public Component{
	//private members
public:
	//public members
	enum state{idling,looking,walking,attacking,stomping,charging,count};
	aiFunc foo;

	CompAI(aiFunc func);
	~CompAI();
	void render_component_ai();
	void update(float time);
	void render();
	Component::type get_type()const;
};

#endif//COMPONENTAIHPP
