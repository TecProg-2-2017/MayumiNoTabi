/*
 * File: gameObject.cpp
 *
 * Description: Create and generate objects game features.
 */
#include <gameObject.hpp>
#include <game.hpp>
#include <common.hpp>
#include <componentMovement.hpp>
#include <camera.hpp>
#include <complib.hpp>
#include <stateStage.hpp>
#include <txtFuncs.hpp>
#include <music.hpp>
#include <assert.h>

GameObject::GameObject():uid{goCount++};
GameObject::GameObject (const Vec2 &pos_,float r,Hotspot hs,bool a);
GameObject::GameObject (const Rect &rect,float r,Hotspot hs,bool a);
GameObject::GameObject (const Rect &rect,float r,Hotspot hs,bool a);
GameObject::~GameObject();
void GameObject::update(float time);
void GameObject::Render();
void GameObject::render();
void GameObject::AddComponent(Component* component);
void GameObject::ReplaceComponent(Component* component);
void GameObject::RemoveComponent(Component::type t);
void GameObject::SetComponent(Component::type t,Component* component);
bool GameObject::HasComponent(size_t t);
void GameObject::AttachObj(GameObject* obj);
void GameObject::AttachTo(GameObject* obj);
void GameObject::UnAttachObj(GameObject* obj);
void GameObject::UnAttach();
bool GameObject::IsDead();
bool GameObject::Remove();
Rect GameObject::Box();
Rect GameObject::Box(const Vec2& p,const Vec2 &sz);
Rect GameObject::FullBox();
template<int atkDist,int seeDist,
         int id> void HostileAIfunc(CompAI* ai,float time);
void PassiveAIfunc(CompAI* ai,float time);
template<int atkDist,int seeDist,int stCD,int atkCount,int stompCount >
                               void PumbaAiFunc(CompAI* ai,float time);
void PlayerControlFunc(GameObject* go, float time);
void PlayerMonsterCollision(const CompCollider::Coll &a,const CompCollider::Coll &b);
void PlayerBlockCollision(const CompCollider::Coll &a,const CompCollider::Coll &b);
void EmptyCollision(const CompCollider::Coll &a,const CompCollider::Coll &b);
uint GameObject::MakePlayer(const Vec2 &pos);
uint GameObject::Create(const string& blueprint, const Vec2& pos, const Vec2& aux);
uint GameObject::MakeTarget(const Vec2 &pos);
uint GameObject::MakeMike(const Vec2 &pos);
uint GameObject::MakeBanshee(const Vec2 &pos,const Vec2 &pos2);
uint GameObject::MakeMask(const Vec2 &pos);
uint GameObject::MakeBoar(const Vec2 &pos);


uint GameObject::goCount = 0;

map<uint, unique_ptr<GameObject>> GameObject::entities;

//! A constructor.
    /*!
    This is a constructor method of GameObject class
    */

GameObject::GameObject():uid{goCount++} {
	components.fill(nullptr);
	entities[uid] = unique_ptr < GameObject > (this);
}

//! A constructor.
    /*!
    This is a constructor method of GameObject class
		@param position It's the object position into a referential
		@param rotation It's the rotation indices of object
		@param hotspot It's the hostspot of object,related to the boundaries
		of the object
		@param a
		@warning Method that requires review of comment
		*/

GameObject::GameObject (const Vec2 &position_,float rotation, Hotspot hotspot, \
  bool a):  uid{goCount++},
						pos{position_},
						rotation{rotation},
						hotspot{hotspot},
						anchored{a} {
  assert(&position_ != NULL);
  assert(rotation != NULL);
  assert(hotspot != NULL);
  assert(&a_ != NULL);

	components.fill(nullptr);
	entities[uid] = unique_ptr<GameObject>(this);
}

//! A constructor.
    /*!
    This is a constructor method of GameObject class
		@param rect It's a rectangulo, the space of the object displayed.
		@param r It's the rotation indices of object
		@param hs It's the hostspot of object,related to the boundaries
		of the object
		@param a
		@warning Method that requires review of comment
		*/

GameObject::GameObject (const Rect &rectangle,float rotation, \
  Hotspot hotspots, bool a):
						uid{goCount++},
						pos{rect.x,rect.y},
						size{rect.w,rect.h},
						rotation{r},
						hotspot{hs},
						anchored{a} {
  assert(&rectangle != NULL);
  assert(rotation != NULL);
  assert(hotspot != NULL);
  assert(&a_ != NULL);

	components.fill(nullptr);
	entities[uid] = unique_ptr<GameObject>(this);
}

//! A destructor.
    /*!
      This is a destructor method of GameObject class
    */

GameObject::~GameObject() {
	UnAttach();

	for (GameObject* obj:attachedObjs) {
		obj->dead = true;
	}

	FOR(i,Component::type::t_count) {
    //! TODO Error Handling
		if (HasComponent(i)) {
			delete components[i];
		}
		else {
			// Nothing to do
		}
	}
    //! TODO Error Handling
		if (Camera::GetFocus() == uid) {
			Camera::Unfollow();
		}
		else {
			// Nothing to do
		}

	entities.erase(uid);
}

/*!
	@fn void GameObject::Update(float time)
	@brief Method that updates the view status of an object
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void GameObject::update(float time) {
	 LOG_METHOD_START("GameObject::update");
	 LOG_VARIABLE("time: ", time);
   assert(time != NULL);

	 remove = false // Initializing the variabel remove

  //! TODO Error Handling
	if (IsDead()) {
		remove = true;
		// for (auto i=Component::type::t_first+1;i!=Component::type::t_count;i++) {
		FOR(i,Component::type::t_count) {
			//! If there is a component
			if (HasComponent(i)) {
				if (components[i]->Die(time)) {
					RemoveComponent((Component::type)i);
				}
				// else {
				// 	remove = false;
				// }
			}
			else {
				//! Nothing to do
			}
		}
	}

  //! TODO Error Handling
	//! Reset move
	if (HasComponent(Component::type::t_movement)) {
		COMPMOVEp(this)->move = 0.0f;
	}
	else {
		//! Nothing to do.
	}

	//! Process input control and ai first
  //! TODO Error Handling
	if (HasComponent(Component::type::t_input_control)) {
		COMPINPUTCONTp(this)->Update(time);
	}
	else {
		//! Nothing to do.
	}

	//! Move update
  //! TODO Error Handling
	if (HasComponent(Component::type::t_ai)) {
		COMPAIp(this)->Update(time);
	}
	else {
		//! Nothing to do.
	}

	//! Then set move
  //! TODO Error Handling
	if (HasComponent(Component::type::t_movement)) {
	    COMPMOVEp(this)->move += COMPMOVEp(this)->speed*time;
	}
	else {
		//! Nothing to do.
	}

	//! And then do the rest
	FOR2(i, Component::type::t__+1, Component::type::t_count) {
		if (HasComponent(i)) {
      //! TODO Error Handling
			components[i]->Update(time);
		}
		else {
			//! Nothing to do.
		}
	}
}

/*!
	@fn void GameObject::Render()
	@brief Method that allows to render a component of an object
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void GameObject::Render() {
	LOG_METHOD_START("GameObject::Render");

  //! TODO Error Handling
	if (components[i]->kills_component(time)) {
		RemoveComponent((Component::type)i);
	}
	else {
		remove = false;
	}

	// Reset move
  //! TODO Error Handling
	if (HasComponent(Component::type::t_movement)) {
		COMPMOVEp(this)->move = 0.0f;
	}
	else {
		// Nothing to do
	}
	// Process input control and ai first
  //! TODO Error Handling
	if (HasComponent(Component::type::t_input_control)) {
		COMPINPUTCONTp(this)->update(time);
	}
	else {
		// Nothing to do
	}
  //! TODO Error Handling
	if (HasComponent(Component::type::t_ai)) {
		COMPAIp(this)->update(time);
  }
	else {
		// Nothing to do
	}
	// Then set move
  //! TODO Error Handling
	if (HasComponent(Component::type::t_movement)) {
		COMPMOVEp(this)->move += COMPMOVEp(this)->speed*time;
	}
	else {
		// Nothing to do
	}
	// And then do the rest
	FOR2(i,Component::type::t__+1,Component::type::t_count) {
    //! TODO Error Handling
		if (HasComponent(i)) {
			components[i]->update(time);
		}
		else {
			// Nothing to do
		}
	}
}

void GameObject::render() {
	LOG_METHOD_START("GameObject::render()");

	FOR(i, Component::type::t_count) {
		//! Render a component
    //! TODO Error Handling
		if (HasComponent(i)) {
			components[i]->render();
		}
		else {
			// Nothing to do
		}
	}
}

/*!
	@fn void GameObject::AddComponent(Component* component)
	@brief Method that add component if it doesn't exist.
	@param component
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void GameObject::AddComponent(Component* component) {
	LOG_METHOD_START("GameObject::AddComponent");
	LOG_VARIABLE("component: ", component);
  assert(component != NULL);

	auto t = component->GetType();
	//! If the component is read, then it's add with the others components
  //! TODO Error Handling
	if (HasComponent(t)) {
		cerr << "Error, adding component " << t
		cerr << " to a GameObject that already has it" << endl;
	}
	else {
		//! Nothing to do.
	}

	components[t] = component;
	component->Own(this);
}

/*!
	@fn void GameObject::ReplaceComponent(Component* component)
	@brief Method that replaces a component of an object
	@param component
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void GameObject::ReplaceComponent(Component* component) {
	LOG_METHOD_START("GameObject::ReplaceComponent");
	LOG_VARIABLE("component: ", component);
  assert(component != NULL);

	auto t = component->GetType();
	//! if the component doesn't have a type, then it is deleted.
  //! TODO Error Handling
	if (!HasComponent(t)) {
		cerr << "Error, replacing component " << t
		cerr << " on a GameObject that doesnt have it" << endl;
	}
	else {
		delete components[t];
	}

	components[t] = component;
	component->Own(this);
}

/*!
	@fn void GameObject::RemoveComponent(Component::type t)
	@brief Method that removes a component of an object
	@param t A type of a component
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void GameObject::RemoveComponent(Component::type t) {
	LOG_METHOD_START("GameObject::RemoveComponent");
	LOG_VARIABLE("type t: ", t);
  assert(t != NULL);

	if (!HasComponent(t)) {
		cerr << "Error, removing component " << t
		cerr << " on a GameObject that doesnt have it" << endl;
	}
	else {
		delete components[t];
		components[t] = nullptr;
	}
}

/*!
	@fn void GameObject::SetComponent(Component::type t,Component* component)
	@brief Method that sets a component with it type of an object
	@param t A type of a component
	@param component
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void GameObject::SetComponent(Component::type t,Component* component) {
	LOG_METHOD_START("GameObject::SetComponent");
	LOG_VARIABLE("type t: ", t);
	LOG_VARIABLE("component: ", component);
  assert(t != NULL);
  assert(component != NULL);

	components[t] = component;
	component->own(this);
}

/*!
	@fn void GameObject::SetComponent(Component::type t,Component* component)
	@brief Method that verify the vality of a component's size of an object
	@param t A size of a component
	@return The execution of this method returns a bool, if a component exists.
	@warning Method that requires review of comment
*/

bool GameObject::HasComponent(size_t t) const {
	LOG_METHOD_START("GameObject::HasComponent");
	LOG_VARIABLE("size t: ", t);
  assert(t != NULL);
	LOG_METHOD_CLOSE("GameObject::HasComponent", components[t]);

	return (components[t] != nullptr);
}

/*!
	@fn void GameObject::AttachObj(GameObject* obj)
	@brief Method that verify the vality of a component's size of an object
	@param obj A object GameObject
	@return The execution of this method returns no value.
	@warning Method that requires review of comment
*/
void GameObject::AttachObj(GameObject* obj) {
	LOG_METHOD_START("GameObject::AttachObj");
  LOG_VARIABLE("obj: ", obj);
  assert(obj != NULL);

	//! If the end of object was finded, then it's attach
  //! TODO Error Handling
	if (find(attachedObjs.begin(),attachedObjs.end(),obj) == attachedObjs.end()) {
		attachedObjs.push_back(obj);
		obj->AttachTo(this);
	}
	else {
		//! Nothing to do.
	}
}

/*!
	@fn void GameObject::AttachTo(GameObject* obj)
	@brief Method that verifys the contact between objects, if an object touched
	an other object.
	@param obj A object GameObject
	@return The execution of this method returns no value.
	@warning Method that requires review of comment
*/

void GameObject::AttachTo(GameObject* obj) {
	LOG_METHOD_START("GameObject::AttachTo");

	LOG_VARIABLE("obj: ", obj);
  assert(obj != NULL);

	//! If the object is a null pointer
	if (attachedTo == nullptr) {
    //! TODO Error Handling
		attachedTo = obj;
		obj->AttachObj(this);
	} //! if the object attach a object, then the object is attached.
	else if (attachedTo != obj) {
		UnAttach();
		AttachTo(obj);
	}
}

/*!
	@fn void GameObject::UnAttachObj(GameObject* obj)
	@brief Method that verifys the contact between objects, if an object
	touched other
	@param obj A object GameObject
	@return The execution of this method returns no value.
	@warning Method that requires review of comment
*/

void GameObject::UnAttachObj(GameObject* obj) {
	LOG_METHOD_START("GameObject::UnAttachObj");

	LOG_VARIABLE("obj: ", obj);
  assert(obj != NULL);

	//! "it" is the object's point.
	auto it = find(attachedObjs.begin(), attachedObjs.end(),obj);
	//! If it is the object's end then it is erased, then the object isn't attach.
  //! TODO Error Handling
  if (it != attachedObjs.end()) {
		attachedObjs.erase(it);
		obj->UnAttach();
	}
}

/*!
	@fn void GameObject::UnAttachObj(GameObject* obj)
	@brief Method that verifys the contact between objects, if an object
	touched other
	@return The execution of this method returns no value.
	@warning Method that requires review of comment
*/

void GameObject::UnAttach() {
	LOG_METHOD_START("GameObject::UnAttach");

	//! If the attach exists, then the object is UnAttach
  //! TODO Error Handling
	if (attachedTo != nullptr) {
		auto temp = attachedTo;
		attachedTo = nullptr;
		temp->UnAttachObj(this);
	}
	else {
		//! Nothing to do
	}
}

/*!
	@fn bool GameObject::IsDead()
	@brief Method that verifys the contact between objects, if an object
	touched other
	@param obj A object GameObject
	@return The execution of this method returns a bool.
	@warning Method that requires review of comment
*/

bool GameObject::IsDead() const {
	LOG_METHOD_START("GameObject::IsDead");
	LOG_METHOD_CLOSE("GameObject::IsDead", dead);
	return dead;
}

/*!
	@fn bool GameObject::Remove()
	@brief Method that removes an object
	@return The execution of this method returns a bool.
	@warning Method that requires review of comment
*/

bool GameObject::Remove() const {
	LOG_METHOD_START("GameObject::Remove");
	LOG_METHOD_CLOSE("GameObject::Remove", remove);
	return remove;
}

/*!
	@fn Rect GameObject::Box()
	@brief Method that wrappes the region of object with
	cordinates x and y, in cartesian plan, weight w and high h from the
	rotation r and position p.
	@return The execution of this method returns a Rect with hotspot and weight
	and high
	@warning Method that requires review of comment
*/

Rect GameObject::Box() const {
	LOG_METHOD_START("GameObject::Box");

	Rect r{pos,size}; // Vector r(rotation) with parameters position pos and size

	r.x += curPos.x * r.w; // x - cordinate in axis x. w - weight
	r.y += curPos.y * r.h; // y - cordinate in axis y. h - height
	r.w *= curSize.x; // w - it's the object weight
	r.h *= curSize.y; // h - it's the object height in game


	LOG_METHOD_CLOSE("GameObject::Box", Rect{r.hotspot(hotspot),Vec2{r.w,r.h}});
	return Rect{r.hotspot(hotspot),Vec2{r.w,r.h}};
}

/*!
	@fn Rect GameObject::Box()
	@brief Method that wrappes the region of object with
	cordinates x and y, in cartesian plan, weight w and high h from the
	rotation r and position p.
	@return The execution of this method returns a Rect with hotspot and weight
	and high
	@warning Method that requires review of comment
*/

Rect GameObject::Box(const Vec2& p,const Vec2 &sz) const {
	LOG_METHOD_START("GameObject::Box(params)");

	LOG_VARIABLE("p: ", p);
	LOG_VARIABLE("sz: ", sz);
  assert(p != NULL);
  assert(sz != NULL);

	Rect r{pos,size}; // Vector r(rotation) with parameters position pos and size

	r.x += p.x * r.w; // x - cordinate in axis x. w - weight
	r.y += p.y * r.h; // y - cordinate in axis y. h - height
	r.w *= sz.x; // w - it's the object weight
	r.h *= sz.y; // h - it's the objects height

	LOG_METHOD_CLOSE("GameObject::Box(params)", \
	                 Rect{r.hotspot(hotspot),Vec2{r.w,r.h}});

	return Rect{r.hotspot(hotspot),Vec2{r.w,r.h}};
}

/*!
	@fn Rect GameObject::FullBox()
	@brief Method that wrappes the region of object using
	position pos and size.
	@return The execution of this method returns a Rect with hotspot and size of
	the region of object displayed.
	@warning Method that requires review of comment
*/

Rect GameObject::FullBox() const {
	LOG_METHOD_START("GameObject::FullBox()");

	Rect r{pos,size};

	LOG_METHOD_CLOSE("GameObject::FullBox()", Rect{r.hotspot(hotspot),size});
	return Rect{r.hotspot(hotspot),size};
}

/*!
	@fn template<int atkDist,int seeDist,
	         int id> void HostileAIfunc(CompAI* ai,float time)
	@brief Method that wrappes the region of object using
	position pos and size.
	@param ai
	@param time Time
	@return The execution of this method returns no value
	@warning Method that requires review of comment and refactor this method
*/

template<int atkDist,int seeDist,
         int id> void HostileAIfunc(CompAI* ai,float time) {
	LOG_METHOD_START("HostileAIfunc");

	LOG_VARIABLE("ai: ", ai);
	LOG_VARIABLE("time: ", time);
  assert(ai != NULL);
  assert(time != NULL);

	Sound music = null; // Initializing the variable music

	CompAnimControl *ac = COMPANIMCONTp(GO(ai->entity)); // ac - Animation Control
	CompMemory *mem = COMPMEMORYp(GO(ai->entity)); // mem - among component memory

	int &state = mem->ints["state"]; // State of object
	int &attacked = mem->ints["attacked"]; // Attacked indicates the attack
	GameObject* target = GO(mem->ints["target"]);

	Timer &cd = mem->timers["cooldown"]; // there is lost of time to play
	Timer &al = mem->timers["alerted"]; // time is ending

  //! If there is a hit, then the ai is restart.
  //! TODO Error Handling
	if (mem->ints["hit"]) {
		mem->ints["hit"] = 0;
		al.Restart();
	}
	else {
		//! Nothing to do
	}

	bool alerted = (al.Get() < 5);  // Alert state of object,when alert less then 5

	//! If state of object is idling
  //! TODO Error Handling
	if (state == CompAI::state::idling) { // State of velocity object
    //! If the object is touched
    //! TODO Error Handling
		if ((alerted || cd.Get() > 3) && target != nullptr) {
			state = CompAI::state::looking;
			cd.Restart();
			return;
		}
		else {
			//! Nothing to do
		}
	}
	else if (target == nullptr) {
		state = CompAI::state::idling;
		ac->change_current("idle");
		cd.Restart();
		return;
	}
	//!If the object is just looking
	else if (state == CompAI::state::looking) {
		//! If the time is 10
		if (al.Get() > 10 && cd.Get() > 5) {
			state = CompAI::state::idling;
			cd.Restart();
			return;
		}
    //! TODO Error Handling
		else {
			//! Nothing to do
		}
		//TODO: make line of sight component
		//! Distance of the object
		float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;

    //! TODO Error Handling
		if ((alerted && dist < (seeDist*2)) || dist < seeDist) {
      //! TODO Error Handling
			if (dist < atkDist) {
                state = CompAI::state::attacking;
                //! TODO Error Handling
                if (id == 1) { // Mike
                    music.open_music_file("audio/mike-hit-chao.wav");
                    music.play_music(1);
                } else { // Mask
                    music.open_music_file("audio/alma-firebal.wav");
                    music.play_music(1);
                }
			} else {
                state = CompAI::state::walking;
                ac->change_current("walk");
                //! TODO Error Handling
                if (id == 1) { // Mike
                    music.open_music_file("audio/mike-arrastando-clava.wav");
                    music.play_music(1);
                }
								else {
									// Nothing to do
								}
			}

			cd.Restart();

			return;
		}
	}
	else if (state == CompAI::state::walking) {
		CompMovement *movement = COMPMOVEp(GO(ai->entity));
    //! TODO Error Handling
		if (id == 1) {// Mike
			music.open_music_file("audio/mike-arrastando-clava.wav");
		}
		else {
			// Nothing to do
		}
    //! TODO Error Handling
		if (al.Get() > 10 && cd.Get() > 5) {
			state = CompAI::state::looking;
			movement->speed.x = 0;

			ac->ChangeCur("idle"); // Control is idle
			cd.Restart(); // Restart the timer

			return;
		}
		else {
			float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;

			//TODO: make line of sight component
      //! TODO Error Handling
			if (dist > (seeDist*2) || (!alerted && dist > seeDist)) {

				state = CompAI::state::looking;
				movement->speed.x = 0; // the object is idle
				ac->ChangeCur("idle");

				cd.Restart();
				return;
			}
			//!
      //! TODO Error Handling
			else if (dist < atkDist+abs(movement->speed.x)*time) {
				//!
        //! TODO Error Handling
				if (GO(ai->entity)->Box().x < target->Box().x) {
					movement->move = dist-atkDist;
				}
				else {
					movement->move =- dist + atkDist;
				}

				state = CompAI::state::attacking; // State of attack
        //! TODO Error Handling
				if (id == 1) { // Mike
                    music.open_music_file("audio/mike-hit-chao.wav");
                    music.play_music(1);
                } else { // Mask
                    music.open_music_file("audio/alma-firebal.wav");
                    music.play_music(1);
                }
				movement->speed.x = 0;
				ac->change_current("idle");
				cd.Restart();
				return;
			}
			//! If the object doesn't touched
			else if (GO(ai->entity)->Box().x < target->Box().x) {
				GO(ai->entity)->flipped = true;
				movement->speed.x = 100.0f;
			}
      //! TODO Error Handling
			else {
				GO(ai->entity)->flipped = false;
				movement->speed.x = -100.0f;
			}
		}
	}
	//! State of object in attack
	else if (state == CompAI::state::attacking) {
    //! TODO Error Handling
		if (!alerted && attacked > 3) {
			state = CompAI::state::idling;
			attacked = 0;
			ac->change_current("idle");
			cd.Restart();
			return;
		}

		//! If the object wasn't attacked
		else if (ac->GetCurName() != "attack") {
			float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;
			//!
			if (dist > atkDist) {

				state = CompAI::state::looking;
				attacked = 0;
				ac->ChangeCur("idle");

				cd.Restart();
				return;
			}
			else ac->change_current("attack",false);
		}
		else{
      //! TODO Error Handling
			if (target->Box().x > GO(ai->entity)->Box().x && !GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = true;
			}
			else {
				//! Nothing to do
			}
      //! TODO Error Handling
			if (target->Box().x < GO(ai->entity)->Box().x &&  GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = false;
		}
		else {
			//! Nothing to do
		}
	}
}
}

/*!
	@fn void PassiveAIfunc(CompAI* ai,float time)
	@brief Method that movies the object in the same place. It's continues idle.
	@param ai
	@param time Time
	@return The execution of this method returns no value
	@warning Method that requires review of comment and refactor this method
*/

void PassiveAIfunc(CompAI* ai,float time) {
  LOG_METHOD_START("GameObject::PassiveAIfunc");
  assert(ai != NULL);
  assert(time != NULL);
	LOG_VARIABLE("ai: ", ai);
	LOG_VARIABLE("time: ", time);

	Sound music = null; // Initializing variable mucsic,  a media audio
	CompAnimControl *ac = COMPANIMCONTp(GO(ai->entity)); // Control animation
	CompMemory *mem = COMPMEMORYp(GO(ai->entity)); // memory of component

	int &state = mem->ints["state"];  // State of object in game
	int &next = mem->ints["nextPos"]; // Next position of object
	int &posCount = mem->ints["posCount"];

	Timer &cd = mem->timers["cooldown"]; // Timer cooldown

	//! If the object is idle.
  //! TODO Error Handling
	if (state == CompAI::state::idling) {
    //! TODO Error Handling
		if (cd.Get() > 0.5f) {
			state = CompAI::state::walking;  // The object is in movie
			music.open_music_file("audio/banshee-vozes-1.wav");
            music.play_music(1);
			ac->change_current("walk");
		}
		else {
			//! Nothing to do
		}
	}
	//! The object is in movie
	else if (state == CompAI::state::walking) {
		Vec2 pos{mem->floats["pos" + to_string(next) + "x"], /
		         mem->floats["pos" + to_string(next) + "y"]};
		Vec2 dist = pos - GO(ai->entity)->pos;
		CompMovement *movement = COMPMOVEp(GO(ai->entity));

		//! If there is time and space to walkie
    //! TODO Error Handling
		if (dist.len() < movement->speed.len() * time) {
			movement->speed = Vec2{};
			movement->move = dist;

			state = CompAI::state::idling;
			cd.Restart();
			next = (next+1) % posCount;
			ac->ChangeCur("idle");
		}
		else {
			movement->speed = dist.unit() * 100.0f;
			GO(ai->entity)->flipped = (movement->speed.x > 0);
		}
	}
}

/*!
	@fn template<int atkDist,int seeDist,int stCD,int atkCount,int stompCount>
	                               void PumbaAiFunc(CompAI* ai,float time)
	@brief Method that controls the boar moviments and songs.
	@param ai
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment and refactor this method
*/

template<int atkDist,int seeDist,int stCD,int atkCount,int stompCount >
                               void PumbaAiFunc(CompAI* ai,float time) {
	LOG_METHOD_START("GameObject::PumbaAiFunc");
  assert(ai != NULL);
  assert(time != NULL);
	LOG_VARIABLE("ai: ", ai);
	LOG_VARIABLE("time: ", time);

	Sound music = null; // Initializing variable music
	Music music2 = null; // Initializing variable music2
	CompAnimControl *ac = COMPANIMCONTp(GO(ai->entity)); // Component Control
	CompMemory *mem = COMPMEMORYp(GO(ai->entity));
	//CompHP *hp = COMPHPp(GO(ai->entity)); // Power of boar. Commented

	int &state = mem->ints["state"]; // State of boar
	int &attacked = mem->ints["attacked"]; // State if boar is attacked
	GameObject* target = GO(mem->ints["target"]); // Target from game

	Timer &cd = mem->timers["cooldown"]; // Timer
	Timer &al = mem->timers["alerted"]; // Level of alert
	Timer &stompCD = mem->timers["stomp"];

	// bool enraged = hp->current < hp->total/2;
	// if (enraged && !mem->ints["enraged"]) {
	// 	CompCollider *coll = COMPANIMCONTPOINTER(GO(ai->entity))->get_current().colliders[0];
	// 	CompAnimControl *animControl = new CompAnimControl{"porco_rage",coll};
	// 	GO(ai->entity)->RemoveComponent(Component::type::t_animation_control);
	// 	GO(ai->entity)->AddComponent(animControl);
	// }

	string &curAnim = ac->GetCurName(); // Current animation
	//! If the name of animation starts with _r

  //! TODO Error Handling
	if (curAnim.substr(curAnim.size()-2) == "_r") {
		//! If the entity cant't flipped
    //! TODO Error Handling
		if (!GO(ai->entity)->flipped) {

			int frame = ac->GetCur().GetCurFrame();
			curAnim = curAnim.substr(0,curAnim.size()-2);
			ac->GetCur().SetCurFrame(frame);
		}
		else {
			// Nothing to do
		}
	}
	//! If the entity cans flipped
  //! TODO Error Handling
	else if (GO(ai->entity)->flipped) {
		int frame = ac->get_current().get_current_frame();
		curAnim = curAnim+"_r";
		ac->get_current().set_current_frame(frame);
	}
	else {
		// Nothing to do
	}

  //! TODO Error Handling
	if (mem->ints["hit"]) {
		mem->ints["hit"] = 0;
		al.Restart();
	}
	else {
		//! Nothing to do
	}

	bool alerted = (al.Get() < 5);

	//! If the state of character is idle
  //! TODO Error Handling
	if (state == CompAI::state::idling) {
		//! If is time of game
    //! TODO Error Handling
		if ((alerted || cd.Get() > 3) && target != nullptr) {
			state = CompAI::state::looking;
			music.open_music_file("audio/porco-grunhido-3.wav");
			music.play_music(1);
			cd.Restart();

			return;
		}
		else{
			//! Nothing to do
		}
	}

	//! If the game ends
  //! TODO Error Handling
	else if (target == nullptr) {
		state = CompAI::state::idling;
		ac->change_current("idle");
		cd.Restart();

		return;
	}
	//! If character is on state of looking
	else if (state == CompAI::state::looking) {
		//!  If the alert is bigger and timer is bigger than 5
		if (al.Get() > 10 && cd.Get() > 5) {
			state = CompAI::state::idling;
			cd.Restart();
			return;
		}
		//TODO: make line of sight component
		float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;

    //! TODO Error Handling
		if ((alerted && dist < (seeDist*2)) || dist < seeDist) {
			//!
      //! TODO Error Handling
			if (dist < 2*atkDist && stompCD.Get() > stCD) {
				state = CompAI::state::stomping;
				ac->change_current("stomp");
				music.open_music_file("audio/porco-pisada.wav");
				music.play_music(1);
			}
			//! If the distance of attack is far than object
			else if (dist < atkDist) {
				state = CompAI::state::attacking;
			}
			else {
         state = CompAI::state::walking; // The object walks
         ac->change_current("walk");
         music.open_music_file("audio/porco-walking-grunhido.wav");
         music.play_music(1);
			}
			cd.Restart(); // Restart the timer
			return;
		}
	}
	//! If the object is walking
  //! TODO Error Handling
	else if (state == CompAI::state::walking) {
		CompMovement *move = COMPMOVEp(GO(ai->entity));
		//! If alert is big and timer is bigger than 5
		if (al.Get() > 10 && cd.Get() > 5) {
			state = CompAI::state::looking;
			move->speed.x = 0;
			ac->change_current("idle");
			cd.Restart();

			return;
		}
		else {
			float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;

			//TODO: make line of sight component
      //! TODO Error Handling
			if (dist > (seeDist*2) || (!alerted && dist > seeDist)) {
				state = CompAI::state::looking;
				move->speed.x = 0;
				ac->change_current("idle");
				cd.Restart();

				return;
			}

			else if (dist < 2 * atkDist + abs(move->speed.x) * time &&
								cd.Get() < 1.5 && stompCD.Get() > stCD) {
				//! If the object not matched the target yet
				if (GO(ai->entity)->Box().x < target->Box().x) {
					move->move = dist - (2*atkDist);
				}
				else {
					move->move= -dist + (2*atkDist);
				}

				state = CompAI::state::stomping; // Object is in stomp
				move->speed.x = 0;
				ac->change_current("stomp");

				music.open_music_file("audio/porco-pisada.wav");
				music.play_music(1);
				cd.Restart();
			}
      //! TODO Error Handling
			else if (dist < atkDist + abs(move->speed.x)*time) {
				//! If the character not matched the target yet
        //! TODO Error Handling
				if (GO(ai->entity)->Box().x < target->Box().x) {
					move->move = dist - atkDist;
				}
        //! TODO Error Handling
				else {
					move->move = -dist + atkDist;
				}

				if (cd.Get() < 1.5) {
          state = CompAI::state::attacking;
          music.open_music_file("audio/porco-investida-1.wav");
          music.play_music(1);
          ac->change_current("idle");
				}
        //! TODO Error Handling
				else {
					state = CompAI::state::charging, ac->change_current("charge",false); // State of charging
				}
				move->speed.x = 0; // The object is idle
				cd.Restart(); // Timer is restart
				return; // @warning Refactor this
			}
			else if (GO(ai->entity)->Box().x < target->Box().x) {
				GO(ai->entity)->flipped = true;
				move->speed.x = 350.0f;
			}
      //! TODO Error Handling
			else {
				GO(ai->entity)->flipped = false;
				move->speed.x = -350.0f;
			}
		}
	}
}
	//! The object is in attack.
	else if (state == CompAI::state::attacking) {
    //! TODO Error Handling
		if (!alerted && attacked > 3) {
			state = CompAI::state::idling;
			attacked = 0;
			ac->change_current("idle");

			cd.Restart();
			return;
		}
		else if (ac->get_current_name() != "attack" && ac->get_current_name() != "attack_r") {
			float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;
      //! TODO Error Handling
			if (dist > atkDist) {
				state = CompAI::state::looking; // State of object is looking
				music.open_music_file("audio/porco-grunhido-3.wav");
                music.play_music(1);
				attacked = 0;
				ac->change_current("idle");
				cd.Restart();

				return;
			}
			else ac->change_current("attack",false);
		}
		else{
			if (target->Box().x > GO(ai->entity)->Box().x && !GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = true;
			}
			else {
				//! Nothing to do
			}
			if (target->Box().x < GO(ai->entity)->Box().x &&  GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = false;
		}
		else {
			// Nothing to do
		}
	}
	//! The state of character is close to boar
	else if (state == CompAI::state::stomping) {
		if (attacked > stompCount) {
			state = CompAI::state::attacking;
			music.open_music_file("audio/porco-investida-1.wav");
            music.play_music(1);
			attacked = 0;
			ac->change_current("idle");
			cd.Restart();
			return; // @warning Refactor this
		}
		else if (ac->get_current_name() != "stomp" && ac->get_current_name() != "stomp_r") {
			float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;
			//! Distance of character is bigger than the double
      //! TODO Error Handling
			if (dist > atkDist*2) {

				state = CompAI::state::looking; // Character is observing
				attacked = 0;
				ac->change_current("idle");
				music.open_music_file("audio/porco-grunhido-3.wav");
        music.play_music(1);
				cd.Restart();

				return;
			}
			else {
        ac->change_current("stomp",false);
      }
		}
		else {
      //! TODO Error Handling
			if (target->Box().x > GO(ai->entity)->Box().x && !GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = true;
			}
			else {
				//! Nothing to do
			}
      //! TODO Error Handling
			if (target->Box().x < GO(ai->entity)->Box().x &&  GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = false;
		}
		else {
			//! Nothing to do
		}
	}
}
  //! TODO Error Handling
	else if (state == CompAI::state::charging) {
		if (ac->get_current_name() != "charge" && ac->get_current_name() != "charge_r") {
			state = CompAI::state::looking;
			attacked = 0;
			ac->change_current("idle");

			cd.Restart();

			return;
		}
		else {
			//! Nothing to do
		}
	}
	//! State of character is walking
  //! TODO Error Handling
	else if (state == CompAI::state::walking) {
		CompMovement *move = COMPMOVEp(GO(ai->entity));

    //! TODO Error Handling
		if (cd.Get() > 5) {
			cd.Restart();
			state = CompAI::state::idling;
			move->speed = move->move = 0.0f;
			ac->change_current("idle");
		}
		else {
			float dist = GO(ai->entity)->Box().distEdge(target->Box()).x;
			//TODO: make line of sight component
			//! If distance between character and boar doesn't complete in display
			if (dist > seeDist) {
				cd.Restart();
				state = CompAI::state::looking; //! Character is looking
				ac->change_current("idle");
				music.open_music_file("audio/porco-grunhido-3.wav");
        music.play_music(1);
			}
			else if (dist < 2*atkDist + abs(move->speed.x)*time && cd.Get() < 1.5
			          && stompCD.Get() > stCD) {

				move->speed.x = 0;

        //! TODO Error Handling
				if (GO(ai->entity)->Box().x < target->Box().x) {
					move->move=dist-(2*atkDist);
				}
				else {
					move->move = -dist + (2 * atkDist);
				}

				state = CompAI::state::stomping;
				cd.Restart();
				ac->change_current("stomp");
				music.open_music_file("audio/porco-pisada.wav");
				music.play_music(1);
			}
      //! TODO Error Handling
			else if (dist < atkDist+abs(move->speed.x)*time) {
				move->speed.x = 0; // The object is idle
				if (GO(ai->entity)->Box().x < target->Box().x) {
					move->move = dist-atkDist;
				}
				else {
					move->move = -dist + atkDist;
				}

				cd.Restart();
				if (cd.Get() < 1.5) {
            state = CompAI::state::attacking;
            music.open_music_file("audio/porco-grunhido-3.wav");
            music.play_music(1);

            ac->change_current("idle");
        //! TODO Error Handling
				} else {
					 state = CompAI::state::charging, ac->ChangeCur("charge");
				}
			}
			else if (GO(ai->entity)->pos.x < target->pos.x) {
				GO(ai->entity)->flipped = true;
				move->speed.x = 100.0f;
			}
      //! TODO Error Handling
			else {
				GO(ai->entity)->flipped = false;
				move->speed.x = -100.0f;
			}
		}
	}
	else if (state == CompAI::state::attacking) {
    //! TODO Error Handling
		if (GO(ai->entity)->Box().distEdge(target->Box()).x > atkDist) {
			attacked = 0;
			cd.Restart();

			state = CompAI::state::looking;
			ac->change_current("idle");

			music.open_music_file("audio/porco-grunhido-3.wav");
      music.play_music(1);

			return;
		}
		else {
			if (target->Box().x > GO(ai->entity)->Box().x && !GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = true;
			}
      //! TODO Error Handling
			else {
				//! Nothing to do
			}
			if (target->Box().x < GO(ai->entity)->Box().x &&  GO(ai->entity)->flipped) {
				GO(ai->entity)->flipped = false;
			}
      //! TODO Error Handling
			else {
				//! Nothing to do
			}
			if (attacked >= atkCount) {
				attacked = 0;
				cd.Restart();
				state = CompAI::state::idling;
				ac->change_current("idle");
			}
		}
	}
	else if (state == CompAI::state::stomping) {
		if (attacked >= stompCount) {
			attacked = 0;
			cd.Restart();
			stompCD.Restart();
			state = CompAI::state::looking; //! Object is looking
			ac->change_current("idle");

			music.open_music_file("audio/porco-grunhido-3.wav");
            music.play_music(1);
		}
	}
	else if (state == CompAI::state::charging) {
		if (attacked >= 1) {
			attacked = 0;
			cd.Restart();
			state = CompAI::state::idling;
			ac->change_current("idle");
		}
	}
}

/*!
	@fn void PlayerControlFunc(GameObject* go, float time)
	@brief Method that controls the player functions.
	@param go - moviment of game
	@param time
	@return The execution of this method returns no value
	@warning Method that requires review of comment and refactor this method
*/

void PlayerControlFunc(GameObject* go, float time) {
	UNUSED(time);

	LOG_METHOD_START("GameObject::PlayerControlFunc");
  assert(*go != NULL);
  assert(time != NULL);
	LOG_VARIABLE("go: ", go);
	LOG_VARIABLE("time: ", time);

	CompAnimControl *ac = COMPANIMCONTPOINTER(go);
	CompMemory *mem = COMPMEMORYp(go);
	CompMovement *mv = COMPMOVEp(go);

	const string &curAnim = ac->get_current_name();
	int &arrowReady = mem->ints["arrowReady"];
	Vec2 &speed = mv->speed;

	//TODO: stun
	// if (mem->ints["hit"]) {
	// 	mem->timers["stunned"].Restart();
	// 	mem->ints["hit"]=0;
	// }
	// if (mem->timers["stunned"].Get() < 0.5)return;
	//! Kick, fire and fire2 are types of current animation
	if (curAnim == "kick" || curAnim == "fire" || curAnim == "fire2") {
		return;
	}
  //! TODO Error Handling
	else {
		//! Nothing to do
	}

	if (arrowReady && INPUT.key_is_down(KEY(a)) && curAnim == "idle") {
		ac->ChangeCur("fire", false);
	}
	else if (arrowReady && INPUT.key_is_down(KEY(s)) && curAnim == "idle") {
		ac->change_current("fire2",false);
	}
  //! TODO Error Handling
	else {
		if (!mem->ints["onAir"]) {
			mem->ints["doubleJump"] = 0;
		}
		else {
			//! Nothing to do
		}

		if (INPUT.key_pressed(KEY_UP) && !mem->ints["doubleJump"]) {
			if (!mem->ints["onAir"]) {
        speed.y = -1000.0f;
			}
      //! TODO Error Handling
      else {
        speed.y = -750.0f;
      }
			mem->ints["doubleJump"] = mem->ints["onAir"];
			mem->ints["onAir"] = 1;
			//ac->change_current("jump");
		}

		if (INPUT.key_is_down(KEY_LEFT) && !INPUT.key_is_down(KEY_RIGHT))
			speed.x = -400.0f;
		else if (INPUT.key_is_down(KEY_RIGHT) && !INPUT.key_is_down(KEY_LEFT))
			speed.x = 400.0f;
      //! TODO Error Handling
		else speed.x = 0.0f;
	}


	if (equals(speed.x,0)) {
		if (curAnim == "walk") {
			ac->change_current("idle");
		}
    //! TODO Error Handling
		else {
			// Nothing to do
		}
	}
	else {
		if (curAnim == "idle") {
			ac->change_current("walk");
		}
    //! TODO Error Handling
		else {
			// Nothing to do
		}
		if ((speed.x < 0 && go->flipped) || (speed.x > 0 && !go->flipped)) {
			go->flipped = !go->flipped;
			// ac->change_current("flipped",false);
		}
    //! TODO Error Handling
		else {
			// Nothing to do
		}
	}
}

void PlayerMonsterCollision(const CompCollider::Coll &a,const CompCollider::Coll &b) {
	LOG_METHOD_START("GameObject::PlayerMonsterCollision");
  assert(&a != NULL);
  assert(&b != NULL);
	LOG_VARIABLE("Collider a: ", a);
	LOG_VARIABLE("Collider b: ", b);

	Vec2 &speed = COMPMOVEp(GO(a.entity))->speed;

	if (speed == Vec2{}) {
		return;
	}
  //! TODO Error Handling
	else {
		// Nothing to do
	}

	Vec2 &totMove = COMPMOVEp(GO(a.entity))->move;
	Vec2 move = a.Collides(b,totMove);

	if (move != totMove) {
		COMPHPp(GO(a.entity))->Damage(1);
	}
  //! TODO Error Handling
	else {
		// Nothing to do
	}
}

void PlayerBlockCollision(const CompCollider::Coll &a,const CompCollider::Coll &b) {
	LOG_METHOD_START("GameObject::PlayerBlockCollision");
  assert(&a != NULL);
  assert(&b != NULL);
	LOG_VARIABLE("Coll a: ", a);
	LOG_VARIABLE("Coll b: ", b);

	CompMovement *compMove = COMPMOVEp(GO(a.entity));
	CompMemory *mem = COMPMEMORYp(GO(a.entity));

	Vec2 &speed = compMove->speed;
	Vec2 &totMove = compMove->move;
	Vec2 move = null; // Initializing variable move

	if (totMove == Vec2{}) {
		return;
	}
  //! TODO Error Handling
	else {
		// Nothing to do
	}

	move.x = a.Collides(b,{totMove.x,0.0f},move).x;
	if (move.x != totMove.x) {
		speed.x = 0.0f;
	}
  //! TODO Error Handling
	else {
		// Nothing to do
	}
	move.y = a.Collides(b,{0.0f,totMove.y},move).y;
	if (move.y != totMove.y) {
		speed.y = 0.0f;
		if (totMove.y > 0) {
			mem->ints["onAir"] = 0;
		}
    //! TODO Error Handling
		else {
			// Nothing to do
		}
	}
	else if (equals(totMove.y,0.0f) && equals(a.Collides(b,{0.0f,10},move).y,0.0f)) {
		mem->ints["onAir"] = 0;
	}
	totMove = move;
}

/*!
	@fn void EmptyCollision(const CompCollider::Coll &a,const CompCollider::Coll &b)
	@brief Method that empty colisions.
	@param &a
	@param &b
	@return The execution of this method returns no value
	@warning Method that requires review of comment and refactor this method
*/
void EmptyCollision(const CompCollider::Coll &a,const CompCollider::Coll &b) {
	LOG_METHOD_START("GameObject::EmptyCollision");
  assert(&a != NULL);
  assert(&b != NULL);
	LOG_VARIABLE("Coll a: ", a);
	LOG_VARIABLE("Coll b ", b);

	UNUSED(a);
	UNUSED(b);
}

/*!
	@fn uint GameObject::MakePlayer(const Vec2 &pos)
	@brief Method that creates the players.
	@param &pos - Position of object
	@return The execution of this method returns a undefined integer
	@warning Method that requires review of comment and refactor this method
*/

uint GameObject::MakePlayer(const Vec2 &pos) {
	LOG_METHOD_START("GameObject::MakePlayer");
  assert(&pos != NULL);
	LOG_VARIABLE("pos: ", pos);

	GameObject* player = new GameObject{pos,0.0f,Hotspot::BOTTOM};

	CompCollider coll{CompCollider::collType::t_player};
	coll.colls[0].useDefault[CompCollider::collType::t_bullet] = EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_monster] = PlayerMonsterCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_any] = PlayerBlockCollision;

	CompAnimControl* animControl = new CompAnimControl{"player", &coll};
	Vec2 size{(float)animControl->get_current().sp.GetWidth(), (float)animControl->get_current().sp.GetHeight()};
	player->AddComponent(animControl);


	player->AddComponent(new CompInputControl{PlayerControlFunc});
	player->AddComponent(new CompMovement{});
	player->AddComponent(new CompGravity{2500.0f});
	player->AddComponent(new CompHP{100,100,true,false,0.75f});

	CompMemory *mem = new CompMemory;
	mem->ints["arrowReady"] = 1;
	mem->ints["onAir"] = 1;
	mem->ints["doubleJump"] = 0;
	player->AddComponent(mem);

	player->flipped = true;
	player->team = Team::player;
	player->size = size;

	LOG_METHOD_CLOSE("GameObject::MakePlayer", player->uid);
	return player->uid;
}

/*!
	@fn uint GameObject::Create(const string& blueprint, const Vec2& pos,
	                                                    const Vec2& aux)
	@brief Method that creates the monster of game, Mike, banshee, mask and "porco"
	a boar.
	@param blueprint
	@param pos
	@param aux
	@return The execution of this method returns a undefined integer
	@warning Method that requires review of comment and refactor this method
*/

uint GameObject::Create(const string& blueprint, const Vec2& pos, const Vec2& aux) {
	LOG_METHOD_START("GameObject::Create");
  assert(&blueprint != NULL);
  assert(&pos != NULL);
  assert(&aux != NULL);

	LOG_VARIABLE("blueprint: ", blueprint);
	LOG_VARIABLE("pos: ", pos);
	LOG_VARIABLE("aux: ", aux);

	if (blueprint == "mike") {
		return MakeMike(pos);
	}
  //! TODO Refactor
	else {
		// Nothing to do
	}

	if (blueprint == "banshee") {
		return MakeBanshee(pos,aux);
	}
	else {
		// Nothing to do
	}
	if (blueprint == "mask") {
		return MakeMask(pos);
	}
	else {
		// Nothing to do
	}
	if (blueprint == "porco") {
		return MakeBoar(pos);
	}
  //! TODO Error Handling
	else {
		// Nothing to do
	}

	GameObject* obj = new GameObject{pos};
	CompStaticRender* img = new CompStaticRender{Sprite{blueprint}};
	Vec2 size{(float)img->sp.GetWidth(),(float)img->sp.GetHeight()};
	obj->AddComponent(img);
	obj->size = size;

	LOG_METHOD_CLOSE("GameObject::Create", obj->uid);
	return obj->uid;
	/*vector<string> components = Resources::game_get_blueprint(blueprint);
	stringstream comp;
	string compType;
	for (auto& i:components) {
		comp.str(i);
		comp >> compType;
		if (compType == "movement")
	}*/
}

/*!
	@fn uint GameObject::MakeTarget(const Vec2 &pos)
	@brief Method that creates the target of game.
	@param &pos
	@return The execution of this method returns a undefined integer
	@warning Method that requires review of comment and refactor this method
*/

uint GameObject::MakeTarget(const Vec2 &pos) {
	LOG_METHOD_START("GameObject::MakeTarget");
  assert(&pos != NULL);

	LOG_VARIABLE("pos", pos);

	GameObject* target = new GameObject{pos,0.0f,Hotspot::BOTTOM};

	CompStaticRender* img = new CompStaticRender{Sprite{"img/target.png"},Vec2{}};
	Vec2 size{(float)img->sp.GetWidth(),(float)img->sp.GetHeight()};
	target->AddComponent(img);
	target->AddComponent(new CompCollider{CompCollider::collType::t_solid});
	target->AddComponent(new CompHP{100, 100, true, false});
	target->team = Team::other;
	target->size = size;

	LOG_METHOD_CLOSE("GameObject::MakeTarget", target->uid);
	return target->uid;
}

/*!
	@fn uint GameObject::MakeMike(const Vec2 &pos)
	@brief Method that creates the monster Mike.
	@param blueprint
	@param pos
	@param aux
	@return The execution of this method returns a undefined integer
	@warning Method that requires review of comment and refactor this method
*/

uint GameObject::MakeMike(const Vec2 &pos) {
	LOG_METHOD_START("GameObject::MakeMike");
  assert(&pos != NULL);
	LOG_VARIABLE("pos", pos);

	GameObject* mike = new GameObject{pos, 0.0f, Hotspot::BOTTOM};

	CompCollider coll{CompCollider::collType::t_monster};
	coll.colls[0].useDefault[CompCollider::collType::t_bullet] = EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_player]=EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_monster]=EmptyCollision;

	CompAnimControl* animControl = new CompAnimControl{"mike",&coll};
	Vec2 size{(float)animControl->get_current().sp.GetWidth(),(float)animControl->get_current().sp.GetHeight()};
	mike->AddComponent(animControl);

	mike->AddComponent(new CompMovement{});
	mike->AddComponent(new CompGravity{2500.0f});
	mike->AddComponent(new CompHP{100,100,true,false});
	mike->AddComponent(new CompAI{HostileAIfunc < 5, 500, 1 > });

	CompMemory *memory = new CompMemory{};
	memory->ints["state"] = CompAI::state::idling;
	memory->ints["target"] = PLAYER_UID;
	mike->AddComponent(memory);

	mike->team = Team::enemy;
	mike->size = size;

	LOG_METHOD_CLOSE("GameObject::MakeMike", mike->uid);
	return mike->uid;
}

/*!
	@fn uint GameObject::MakeBanshee(const Vec2 &pos,const Vec2 &pos2)
	@brief Method that creates the monster Banshee.
	@param &pos
	@param &pos2
	@return The execution of this method returns a undefined integer
	@warning Method that requires review of comment and refactor this method
*/

uint GameObject::MakeBanshee(const Vec2 &pos,const Vec2 &pos2) {
	LOG_METHOD_START("GameObject::MakeBanshee");
  assert(&pos != NULL);
  assert(&pos2 != NULL);
	LOG_VARIABLE("pos", pos);
	LOG_VARIABLE("pos2", pos2);

	GameObject* banshee = new GameObject{pos,0.0f,Hotspot::BOTTOM};

	CompCollider coll{CompCollider::collType::t_monster};
	coll.colls[0].useDefault[CompCollider::collType::t_ground] = EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_bullet] = EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_player] = EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_monster] = EmptyCollision;

	CompAnimControl* animControl = new CompAnimControl{"banshee",&coll};
	Vec2 size{(float)animControl->get_current().sp.GetWidth(), (float)animControl->get_current().sp.GetHeight()};
	banshee->AddComponent(animControl);
	banshee->AddComponent(new CompMovement{});
	banshee->AddComponent(new CompGravity{250.0f});
	// banshee->AddComponent(new CompHP{100,100,true,false});
	banshee->AddComponent(new CompAI{PassiveAIfunc});

	CompMemory *memory = new CompMemory{};
	memory->floats["pos0x"] = pos.x; // position in axis x
	memory->floats["pos0y"] = pos.y; // position in axis y
	memory->floats["pos1x"] = pos2.x; // Second position in axis x
	memory->floats["pos1y"] = pos2.y; //// position in axis x
	memory->ints["state"] = CompAI::state::idling;
	memory->ints["nextPos"] = 0;
	memory->ints["posCount"] = 2;
	banshee->AddComponent(memory);
	banshee->team = Team::enemy;
	banshee->size = size;

	LOG_METHOD_CLOSE("GameObject::MakeMike", banshee->uid);
	return banshee->uid;
}

/*!
	@fn uint GameObject::MakeMask(const Vec2 &pos)
	@brief Method that creates the monster MakeMask.
	@param &pos
	@return The execution of this method returns a undefined integer
	@warning Method that requires review of comment and refactor this method
*/

uint GameObject::MakeMask(const Vec2 &pos) {
	LOG_METHOD_START("GameObject::MakeMask");
  assert(&pos != NULL);
	LOG_VARIABLE("pos", pos);

	GameObject* mask = new GameObject{pos,0.0f,Hotspot::BOTTOM};

	CompCollider coll{CompCollider::collType::t_monster};
	coll.colls[0].useDefault[CompCollider::collType::t_bullet] = EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_player] = EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_monster] = EmptyCollision;

	CompAnimControl* animControl = new CompAnimControl{"mascara", &coll};
	Vec2 size{(float)animControl->get_current().sp.GetWidth(),(float)animControl->get_current().sp.GetHeight()};
	mask->AddComponent(animControl);

	mask->AddComponent(new CompMovement{});
	// mask->AddComponent(new CompGravity{2500.0f});
	mask->AddComponent(new CompHP{50,50,true,false});
	mask->AddComponent(new CompAI{HostileAIfunc<500,1000,2>});

	CompMemory *memory = new CompMemory{};
	memory->ints["target"] = PLAYER_UID;
	mask->AddComponent(memory);
	mask->team = Team::enemy;
	mask->size = size;

	LOG_METHOD_CLOSE("GameObject::MakeMask", mask->uid);
	return mask->uid;
}

/*!
	@fn uint GameObject::MakeBoar(const Vec2 &pos)
	@brief Method that creates the monster "Porco", a boar.
	@param &pos
	@return The execution of this method returns a undefined integer
	@warning Method that requires review of comment and refactor this method
*/
uint GameObject::MakeBoar(const Vec2 &pos) {
	LOG_METHOD_START("GameObject::MakeBoar");
  assert(&pos != NULL);
	LOG_VARIABLE("pos", pos);

	GameObject* pumba = new GameObject{pos,0.0f,Hotspot::BOTTOM};

	CompCollider coll{CompCollider::collType::t_monster};
	coll.colls[0].useDefault[CompCollider::collType::t_bullet]=EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_player]=EmptyCollision;
	coll.colls[0].useDefault[CompCollider::collType::t_monster]=EmptyCollision;

	CompAnimControl* animControl = new CompAnimControl{"porco",&coll};
	Vec2 size{(float)animControl->get_current().sp.GetWidth(),(float)animControl->get_current().sp.GetHeight()};
	pumba->AddComponent(animControl);

	pumba->AddComponent(new CompMovement{});
	pumba->AddComponent(new CompGravity{2500.0f});
	pumba->AddComponent(new CompHP{100,100,true,false});
	pumba->AddComponent(new CompAI{PumbaAiFunc<8,800,2,3,1>});

	CompMemory *memory = new CompMemory{};
	memory->ints["state"] = CompAI::state::idling;
	memory->ints["target"] = PLAYER_UID;
	pumba->AddComponent(memory);

	pumba->team = Team::enemy;
	pumba->size = size;

	LOG_METHOD_CLOSE("GameObject::MakeBoar", pumba->uid);
	return pumba->uid;
}
