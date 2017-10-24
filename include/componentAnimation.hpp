#ifndef COMPANIMATIONHPP
#define COMPANIMATIONHPP

#include <common.hpp>

#include <component.hpp>
#include <geometry.hpp>
#include <sprite.hpp>
#include <componentCollider.hpp>

#define COMPANIM(x)  ((CompAnim*)x. components[Component::type::t_animation])
#define COMPANIMp(x) ((CompAnim*)x->components[Component::type::t_animation])

class CompAnim : public Component{
public:
	vector<CompCollider*> colliders;
	map<int,vector<function<void(GameObject*)>>> frameFunc;
	Sprite sp;
	bool called=true;

	//public members
	CompAnim();
	CompAnim(string file,CompCollider* coll);
	~CompAnim();

	int get_frame_count()const;
	int get_current_frame()const;
	void set_current_frame(int frame, bool force=false);
  void set_current_frame_by_force(int frame, bool force);

	bool Looped()const;

  void Update(float time);
  void checks_animation_call(int frame);
  bool compare_frames(int frame1, int frame2);
  void set_new_frame(int frame1, int frame2);

	void own(GameObject *go);
	void Render();
	Component::type GetType()const;
};

#endif
