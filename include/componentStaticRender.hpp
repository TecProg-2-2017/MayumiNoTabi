#ifndef COMPSTATICRENDERHPP
#define COMPSTATICRENDERHPP

#include <common.hpp>

#include <component.hpp>
#include <geometry.hpp>
#include <sprite.hpp>

#define COMPSTATICRENDER(x)  ((CompStaticRender*)x. components[Component::type::t_static_render])
#define COMPSTATICRENDERp(x) ((CompStaticRender*)x->components[Component::type::t_static_render])

class CompStaticRender : public Component{
	//private members
public:
	//public members
	Sprite sp;
	Vec2 pos;
	bool camScaling;

	CompStaticRender(const Sprite &sp,const Vec2 &p=Vec2{}, const bool cs = true);
	~CompStaticRender();

	void cam_scaling(Vec2 position);
	void update(float time);
	void render();
	Component::type get_type()const;
};

#endif//COMPSTATICRENDERHPP
