/*
 *  File: componentAnimation.cpp
 *
 *  Description:  Implements CompAnim class
 */

#include <componentAnimation.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
#include <complib.hpp>
#include <game.hpp>
#include <stateStage.hpp>
#include <txtFuncs.hpp>
//#include <inputManager.hpp>

// No params constructor method
CompAnim::CompAnim() {

}

// Constructor Method for component animation
// Takes a file name and a CompCollider values as params
CompAnim::CompAnim(string file, CompCollider* tempColl) {

	// TODO: separate variable declarations
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

// Destructor method
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

// Returns current frame count as a integer
int CompAnim::GetFrameCount()const {
	return sp.GetFrameCount();
}

// Returns current frame as a integer
int CompAnim::GetCurFrame()const {
	return sp.GetCurFrame();
}

// Set current frame
// Recieves frame number and force option as params
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

// Returns if the animation is looped (true) or not (false)
bool CompAnim::Looped()const {
	return sp.Looped();
}

// Updates the animation
// Recieves a time value, in float format, as param. Range: unknown
void CompAnim::Update(float time) {
	int frame1 = GetCurFrame();

	// Checks if the animation has not been called and calls it
	if (!called) {

		// Iterates through frame
		for (auto &foo:frameFunc[frame1]) {
			foo(GO(entity));
		}

		called = true;
	}

	sp.Update(time);

	int frame2 = GetCurFrame();

	// Checks if current frames is the same as the next one, if they're not the
	// next frame is set
	if (frame1 != frame2) {
		called = false;
		SetCurFrame(frame2, true);
	}
}

// Renders the component animation
void CompAnim::Render() {
	Vec2 pos = GO(entity)->FullBox().corner().renderPos();

	sp.SetFlipH(GO(entity)->flipped);
	sp.Render(pos, GO(entity)->rotation, Camera::zoom);
}

// Sets ownage of a animation to a game object
// Recieves a game object as param
void CompAnim::Own(GameObject *go) {
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

// Returns type of the animation as a constant value
Component::type CompAnim::GetType()const {
	return Component::type::t_animation;
}
