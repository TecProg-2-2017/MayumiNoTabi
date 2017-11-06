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
	bool show_HP,show_damage;
	float cooldown;
	Timer damage_cooldown;


	CompHP(int tot = 100, bool show_HP = false,bool show_damage = false,float damage_CD = 0.0f);
	CompHP(int tot,int cur, bool show_HP = false,bool show_damage = false,float damage_CD = 0.0f);
	~CompHP();

	void damage(int damage);

	void update(float time);
	void render();
	Component::type get_type()const;
};

#endif//COMPONENTHPHPP
