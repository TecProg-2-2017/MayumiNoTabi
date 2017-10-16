#ifndef COMPONENTHPHPP
#define COMPONENTHPHPP

#include <common.hpp>
#include <component.hpp>
#include <timer.hpp>

#define COMPHP(x)  ((CompHP*)x. components[Component::type::t_hp])
#define COMPHPp(x) ((CompHP*)x->components[Component::type::t_hp])

class CompHP : public Component{
	//private members
public:
	//public members
	int total, current;
	bool showHP,showDMG;
	float cooldown;
	Timer damageCoolDown;


	CompHP(int tot=100,bool showHP=false,bool showDMG=false,float dmgCD=0.0f);
	CompHP(int tot,int cur,bool showHP=false,bool showDMG=false,float dmgCD=0.0f);
	~CompHP();

	void damage(int damage);

	void update(float time);
	void render();
	Component::type get_type()const;
};

#endif//COMPONENTHPHPP
