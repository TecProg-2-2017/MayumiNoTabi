/*!
 *  \file File componentAnimation.cpp
 *  \brief Implementation of CompAnim class
 *
 *  This file has the implementation of CompAnim class
 *
 *  \sa componentAnimation.hpp
 */

#include <componentAnimation.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <complib.hpp>
#include <game.hpp>
#include <stateStage.hpp>
#include <txtFuncs.hpp>
//#include <inputManager.hpp>

//! A constructor.
  /*!
  This is a constructor method of CompAnim class
  */

// Constructor method with no params
CompAnim::CompAnim() {

}

//! A constructor.
  /*!
   This is a constructor method of CompAnim class
  */

  CompAnim::CompAnim(string file, CompCollider* tempColl) {

  // TODO: separate variable declarations and comment them all 
	string name, imgFile, func, animFile, type;

	int fCount,fCountX,fCountY,collCount,funcCount;

	float fTime,x,y,w,h,r;

	ifstream in(ANIMATION_PATH + file + ".txt");

	// Treats possible file opening error
	if (!in.is_open()) {
		cerr << "Erro ao abrir arquivo de animação '" << file << "'" << endl;
	}
	else {
		in >> imgFile >> fCount >> fCountX >> fCountY >> fTime;

		sp.Open(imgFile,fCountX,fCountY,fTime,fCount);

		colliders.resize(fCount,nullptr);

		for (i,fCount) {
			in >> collCount;

			if (collCount) {
				colliders[i] = new CompCollider{};
				colliders[i]->entity = entity;

				for (j, collCount) {
					//TODO: use rotation
					//TODO: different collider types for each coll
					in >> x >> y >> w >> h >> r;

					colliders[i]->colls.emplace_back(entity, tempColl->colls[0].cType,
																						Rect{x,y,w,h});

					colliders[i]->colls[j].useDefault = tempColl->colls[0].useDefault;

					colliders[i]->colls[j].active = tempColl->colls[0].active;
				}
			}

			in >> funcCount;

			for (funcI, funcCount) {
				in >> func;

				if (txtFuncsF.count(func)) {
					frameFunc[i].push_back(txtFuncsF[func](in));
				}
			}
		}

		in.close();
	}

	// Changes called value to false if frameFunc has no elements in it
	if (frameFunc.count(0)) {
		called = false
	};
}

//! A destructor.
  /*!
  This is a destructor method of CompAnim class
  */

CompAnim::~CompAnim() {
	// Iterates through coliders
	for (i, colliders.size()) {

		// Ignores deletion if current collider equals current frame
		if (i == GetCurFrame()) {
			continue
		};

		delete colliders[i];
	}
}

/*!
	@fn       int CompAnim::GetFrameCount()const
	@brief    Returns current frame count as a integer
	@param    none
	@return   int value of frame count
	@warning  none
*/
// Returns current frame count as a integer
int CompAnim::GetFrameCount()const {
	return sp.GetFrameCount();
}

/*!
	@fn       int CompAnim::GetCurFrame()const
	@brief    Returns current frame as a integer
	@param    none
	@return   int with the number of the current frame
	@warning  none
*/

int CompAnim::GetCurFrame()const {
	return sp.GetCurFrame();
}

/*!
	@fn       void CompAnim::SetCurFrame(int frame, bool force)
	@brief    Sets the current frame
	@param    int frame, bool force
	@return   void
	@warning  TOD: some of the decision structure must be rewritten
*/

void CompAnim::SetCurFrame(int frame,		// range: unknown
													 bool force) {// true to force current frame

	// Set frame as current if it isn't already
	if (frame != GetCurFrame()) {
		sp.SetFrame(frame);

		for (auto &foo:frameFunc[frame]) {
			foo(GO(entity));
		}

		called = true;
		force = true;
	}

	// TODO: else (do nothing)
	// Sets current frame by force
	if (force) {

		// proceeds if frame exists or sets as null
		if (colliders[frame] != nullptr) {
			GO(entity)->SetComponent(Component::type::t_collider,colliders[frame]);
		}
		else if (GO(entity)->HasComponent(Component::type::t_collider)) {
			GO(entity)->components[Component::type::t_collider] = nullptr;
		}
	}
}

/*!
	@fn       bool CompAnim::Looped()const
	@brief    Returns if the animation is looped (true) or not (false)
	@param    none
	@return   bool velue defining if animation is looped or not
	@warning  none
*/

bool CompAnim::Looped()const {
	return sp.Looped();
}

/*!
	@fn       void CompAnim::Update(float time)
	@brief    Updates the animation
	@param    float time
	@return   void
	@warning  none
*/

void CompAnim::Update(float time) {
	int frame1 = GetCurFrame(); //!< Used later for comparrison with next frame

	// Checks if the animation has not been called and calls it
	if (!called) {

		// Iterates through frame
		for (auto &foo:frameFunc[frame1]) {
			foo(GO(entity));
		}

		called = true;
	}

	sp.Update(time);

  int frame2 = GetCurFrame(); //!< Assigns the new frame to this variable for
                              //!< comparing with the previous one

  // Checks if current frames is the same as the next one, if they're not the
	// next frame is set
	if (frame1 != frame2) {
		called = false;
		SetCurFrame(frame2, true);
	}
}

/*!
	@fn       void CompAnim::Render()
	@brief    Renders current animation
	@param    none
	@return   void
	@warning  none
*/

void CompAnim::Render() {

  Vec2 pos = GO(entity)->FullBox().corner().renderPos(); //!< Used to save the
                                                         //!< position to render

  sp.SetFlipH(GO(entity)->flipped);
	sp.Render(pos, GO(entity)->rotation, Camera::zoom);
}

/*!
	@fn       void CompAnim::Own(GameObject* go)
	@brief    Sets ownage of a animation to a game object
	@param    GameObject* go
	@return   void
	@warning  none
*/

void CompAnim::Own(GameObject* go) {
	entity = go->uid;

	// Iterates through the colliders and defines its ownage if they're not null
	for (CompCollider *coll:colliders) {
		if (coll != nullptr) {
			coll->Own(go);
		}
	}

  int frame = GetCurFrame();

  SetCurFrame(frame, true);
}

/*!
	@fn       Component::type CompAnim::GetType()const
	@brief    Returns type of the animation as a constant value
	@param    none
	@return   Component::type type of the animation
	@warning  none
*/

Component::type CompAnim::GetType()const {
	return Component::type::t_animation;
}
