#include <state.hpp>

State::State() {}

set<uint> State::GetEntitiesInRange(const float &x1,const float &x2) {
	//TODO: change this to just iterate trought the areas
	set<uint> s;

	for (uint uid:entities_) {
		if (GO(uid)==nullptr) {
            continue;
        }
        else {
            // Do nothing
        }

		Rect box = GO(uid)->Box();

		if (box.x<=x2 || box.x2()>=x1) {
            s.insert(uid);
        }
        else {
            // Do nothing
        }
	}
	return s;
}

void State::End() {
	ClearObjects();
}

void State::AddObject(uint uid, int layer, int area) {
	ii key(layer,area);

	group[key].insert(uid);
	entities_.insert(uid);

	lastGO = uid;
}

void State::ClearObjects() {
	for (uint uid:entities_) {
		if (!isGO(uid)) {
            continue;
        }
        else {
            // Do nothing
        }

		GameObject::entities.erase(uid);
	}
	group.clear();
}

GameObject* State::GetLastObject() {
	return GO(lastGO);
}


bool State::PopRequested() {
	return popRequested;
}
bool State::QuitRequested() {
	return quit_requested;
}

void State::UpdateArray(float time) {
	for (uint uid:entities_) {
		if (!isGO(uid)) {
            continue;
        }
        else {
            // Do nothing
        }
        
		if (GO(uid)==nullptr) {
			GameObject::entities.erase(uid);
			continue;
		}
        else {
            // Do nothing
        }

		GO(uid)->update(time);

		if (GO(uid)->Remove()) {
			// cout << "Removing go " << uid << endl;
			GameObject::entities.erase(uid);
			entities_.erase(uid);
		}
        else {
            // Do nothing
        }
	}
}
void State::RenderArray() {
	for (uint uid:entities_) {
		if (!isGO(uid)) {
            continue;
        }
        else {
            // Do nothing
        }
		if (GO(uid)==nullptr) {
			GameObject::entities.erase(uid);
			continue;
		}
        else {
            // Do nothing
        }

		GO(uid)->render();
	}
}
