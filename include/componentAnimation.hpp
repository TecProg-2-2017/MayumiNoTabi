#ifndef COMPANIMATIONHPP
#define COMPANIMATIONHPP

#include <common.hpp>

#include <component.hpp>
#include <geometry.hpp>
#include <sprite.hpp>
#include <componentCollider.hpp>

#define COMPANIM(x)  ((CompAnim*)x. components[Component::type::t_animation])
#define COMPANIMPOINTER(x) ((CompAnim*)x->components[Component::type::t_animation])

class CompAnim : public Component{
public:
	//public members
	vector<CompCollider*> colliders;
	map<int,vector<function<void(GameObject*)>>> frameFunc;
	Sprite sp;
	bool called=true;
	CompAnim();
	CompAnim(string file,CompCollider* coll);
	~CompAnim();

private:

	int get_frame_count()const;
	int get_current_frame()const;
	void set_current_frame(int frame, bool force=false);
  void set_current_frame_by_force(int frame, bool force);

	bool is_looped()const;

  void update(float time);
  void checks_animation_call(int frame);
  bool compare_frames(int frame1, int frame2);
  void set_new_frame(int frame1, int frame2);

	void own(GameObject *go);
	void render();
	Component::type get_type()const;
};

#endif
