#ifndef COMPONENTCOLLIDERHPP
#define COMPONENTCOLLIDERHPP

#include <common.hpp>

#include <component.hpp>
#include <tileMap.hpp>

#define colliderFunc std::function<void(const Coll &a,const Coll &b)>

#define COMPCOLLIDER(x)  ((CompCollider*)x. components[Component::type::t_collider])
#define COMPCOLLIDERp(x) ((CompCollider*)x->components[Component::type::t_collider])

class CompCollider : public Component{
public:
	//members
	enum collType{t_any,t_ground,t_h_ground,t_player,t_monster,t_bullet,t_solid,t_count};
	struct Coll{
		const uint &entity;
		Vec2 position;
		Vec2 size;
		const collType cType = t_any;
		bool active = true;
		map<collType,colliderFunc> useDefault;//use custom collision handler against colliders of _type

		Coll(const uint &e,collType type,const Rect &rectangle = Rect{0.0f,0.0f,1.0f,1.0f});
		Coll(const uint &e,collType type,const Vec2 &position,const Vec2 &sz=Vec2{1.0f,1.0f});

		Rect Box() const;

		void collision_check(const Coll &other_component);
		Vec2 collides(const Coll &other_component,const Vec2& move,const Vec2& moved=Vec2{}) const;
	};
	vector<Coll> colls;

	//constructor/destructor
	CompCollider();
	CompCollider(collType type,const Rect &rectangle=Rect{0.0f,0.0f,1.0f,1.0f});
	CompCollider(collType type,const Vec2 &position,const Vec2 &sz=Vec2{1.0f,1.0f});
	//functions
	void collision_check(CompCollider *other_component);

	void update(float time);
	void render();
	void own(GameObject *object);
	bool kills_component(float time);//return true to remove this component
	Component::type get_type() const;
};

#endif//COMPONENTCOLLIDERHPP
