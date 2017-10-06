/*
*  File: componentCollider.cpp
*
*  Description:  Implements CompCollider class
*/

#include <componentCollider.hpp>
#include <componentMovement.hpp>
#include <gameObject.hpp>
#include <game.hpp>

/*!
  *  @fn CompCollider::CompCollider()
  *  @brief No params constructor method
*/

CompCollider::CompCollider() {
}

/*!
  * @fn CompCollider::CompCollider(collType t,const Rect &r)
  * @brief Constructor Method for component collider
  * @param Generic component and positioning values
*/

CompCollider::CompCollider(collType t,const Rect &r) {
	colls.emplace_back(entity,t,r);
}

/*!
  * @fn CompCollider::CompCollider(collType t,const Vec2 &p,const Vec2 &sz)
  * @brief Constructor Method for component collider
  * @param Generic component, positioning values for 3D elements
*/

CompCollider::CompCollider(collType t,const Vec2 &p,const Vec2 &sz) {
	colls.emplace_back(entity,t,p,sz);
}

/*!
  * @fn CompCollider::CollisionCheck(CompCollider *other)
  * @brief Checks if components has suffered an collision
  * @param An collidable component
*/

void CompCollider::CollisionCheck(CompCollider *other) {
	//! TODO: simplify decision structure
	//! Verifies if the the element is in the 'dead' state
	if(GO(entity)->dead || GO(other->entity)->dead)return;
}
	//! If the element is 'dead' it checks checks if the collision are enabled
	for(Coll &collA:colls)for(Coll &collB:other->colls)collA.CollisionCheck(collB);

/*!
  * @fn CompCollider::update(float time)
	* @brief Updates the collision
  * @param float time
*/

void CompCollider::update(float time) {
	UNUSED(time);
	//! Iterates throughout the collisons to update its range of verification
	for(Coll &coll:colls) {
		if(coll.active) {
			int x1 = coll.Box().x-10;
			int x2 = coll.Box().x2()+10;
			set<uint> ent = GAMESTATE.GetEntitiesInRange(x1,x2);
			//! Iterates throughout the screen elements to check if there has been collisions
			FOR(uint go:ent) {
			//! Checks if the object in analysis is an collidable component
				if(go != entity && GO(go)->HasComponent(Component::type::t_collider)) {
					CollisionCheck(COMPCOLLIDERp(GO(go)));
				}
			}
		}
	}
}

/*!
* @fn CompCollider::Render()
* @brief Render graphics in order to display collisions
* @param No params
*/

void CompCollider::render() {
	if (SETTINGS.showCollision)
		
		//! Iterates throughout the Collision objects in order to update the rendering
			for (Coll coll:colls) {
      //! TODO: Refactorate decision structures
			if     (coll.cType==CompCollider::collType::t_player) SET_COLOR4(255,0,0,100);
			else if (coll.cType==CompCollider::collType::t_monster)SET_COLOR4(0,255,0,100);
			else if (coll.cType==CompCollider::collType::t_bullet) SET_COLOR4(0,0,255,100);
			else if (coll.cType==CompCollider::collType::t_ground) SET_COLOR4(255,255,0,100);
			else SET_COLOR4(255,255,255,100);
			SDL_Rect r = (coll.Box().renderBox().sdlRect());
			FILL_RECT(&r);
		}
};

/*!
  * @fn CompCollider::own()
	* @brief Verifies if an Object has an collision associated to it
	* @param GameObject *go
*/

void CompCollider::own(GameObject *go) {
	entity = go->uid;
  //! Verifies if the element is empty or not
	if(go != nullptr) {
		//! Verifies the size of the collisions
		if(colls.size()) {

			Rect r{};
			//! Verifies if the element size is equal to the collisions size
			for(Coll coll:colls)r = r.sum(Rect{coll.pos,coll.size});
			go->curPos = r.corner();
			go->curSize = r.size();
		}
		else { //! If collision has no size it gives 'zero' values to it
			go->curPos = Vec2{};
			go->curSize = Vec2{0.0f,0.0f};
		}
	}
}

/*!
  * @fn CompCollider::Die()
	* @brief Checks if the component has died in the game, has time of death as a param
	* @param float time
*/

bool CompCollider::kills_component(float time) {
	UNUSED(time);
  //! Checks if the component has a type associated to it
	if(GO(entity)->HasComponent(Component::type::t_animation))return true;
	if(GO(entity)->HasComponent(Component::type::t_animation_control))return true;
	return false;
}

/*!
  * @fn Component::type CompCollider::get_type() const{
	* @brief Returns the component assigned type
  * @param No params
*/

Component::type CompCollider::get_type() const{
	return Component::type::t_collider;
}

/*!
* @param const uint &e,collType t,const Rect &r
  * @fn CompCollider::Coll::Coll(const uint &e,collType t,const Rect &r)
	* @brief TODO : Comment this structure
*/

CompCollider::Coll::Coll(const uint &e,collType t,const Rect &r):
	entity{e},pos{r.corner()},size{r.size()},cType{t} {
	}

/*!
  * @fn CompCollider::Coll::Coll(const uint &e,collType t,const Vec2 &p,const Vec2 &sz)
	* @brief TODO : Comment this structure
  * @param const uint &e,collType t,const Vec2 &p,const Vec2 &sz
*/

CompCollider::Coll::Coll(const uint &e,collType t,const Vec2 &p,const Vec2 &sz):
	entity{e},pos{p},size{sz},cType{t} {
	}

/*!
  * @fn CompCollider::Coll::Box()
	* @brief TODO : Comment this structure
  * @param No param
*/

Rect CompCollider::Coll::Box() const {
	Rect r = GO(entity)->Box(pos,size);
	return r;
}

/*!
	* @fn CompCollider::Coll::CollisionCheck(const CompCollider::Coll &other)
	* @brief Checks if components has suffered an collision, generic type of element as a param
	* @param CompCollider::Coll &other
*/

void CompCollider::Coll::CollisionCheck(const CompCollider::Coll &other) {
	//! Verifies the collision type and if is whether
	//! TODO: Refactorate decision structures
	if(useDefault.count(other.cType))useDefault[other.cType](*this,other);
	else if(useDefault.count(collType::t_any))useDefault[collType::t_any](*this,other);
	else if(GO(entity)->HasComponent(Component::type::t_movement)) {

		CompMovement *compMove = COMPMOVEp(GO(entity));

		Vec2 &speed=compMove->speed;
		Vec2 &totMove=compMove->move;
		Vec2 move;

		//! TODO : Comment this structure
		if(totMove == Vec2{}) return;

		move.x = Collides(other,{totMove.x,0.0f},move).x;

		//! Verifies if object in x axis has collided
		if(move.x != totMove.x) {
			speed.x=0.0f;
		}

		move.y = Collides(other,{0.0f,totMove.y},move).y;

		//! Verifies if object in y axis has collided
		if(move.y != totMove.y) {
			speed.y=0.0f;
		}
		totMove=move;
	}
}

/*!
	* @fn CompCollider::Coll::Collides(const Coll &other,const Vec2 &move,const Vec2 &moved)
	* @brief Defines an collision field range, has generic elements and 'rangeable' screen spaces params
	* @param Coll &other,const Vec2 &move,const Vec2 &moved
*/

Vec2 CompCollider::Coll::Collides(const Coll &other,const Vec2 &move,const Vec2 &moved) const {
	const int precision = 100;
	Rect box1 = Box()+moved;
	Rect box2 = other.Box();
	Vec2 moveSafe,move100=move/precision,moveTry;

	//! Iterates throughout the 'rangeable' variables to identify collision
	for(i,precision+1) {
		moveTry = move100*i;
		//! Checks if a collision has happened
		//! TODO: Refactorate decision structure
		if((box1+moveTry).collides(box2))return moveSafe;
		moveSafe = moveTry;
	}
	return move;
}
