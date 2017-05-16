#include <gameObject.hpp>

set<GameObject*> *GameObject::entities=nullptr;

set<GameObject*> GameObject::GetEntitiesInRange(const float &x1,const float &x2){
	set<GameObject*> s;
	for(GameObject *go:(*entities))if(go->box.x>=x1 && (go->box.x + go->box.w)<=x2)s.insert(go);
	return s;
}

GameObject::GameObject(){
	entities->insert(this);
}
GameObject::GameObject(const Rect &rec,float r):box{rec},rotation{r}{
	entities->insert(this);
}
GameObject::~GameObject(){
	FOR(i,Component::type::t_count)if(hasComponent[i])delete components[i];
}

void GameObject::Update(float time){
	FOR(i,Component::type::t_count)if(hasComponent[i])components[hasComponent[i]]->Update(time);
}

void GameObject::Render(){
	FOR(i,Component::type::t_count)if(hasComponent[i])components[hasComponent[i]]->Render();
}

void GameObject::AddComponent(Component* component){
	auto t=component->GetType();
	if(hasComponent[t])cout << "Error, adding component " << t << " to a GameObject that already has it" << endl;
	hasComponent[t]=true;
	components[t]=component;
	component->entity=this;
}

void GameObject::ReplaceComponent(Component* component){
	auto t=component->GetType();
	if(!hasComponent[t]){
		cout << "Error, replacing component " << t << " on a GameObject that doesnt have it" << endl;
		hasComponent[t]=true;
	}
	else delete components[t];
	components[t]=component;
	component->entity=this;
}

void GameObject::RemoveComponent(Component::type t){
	if(!hasComponent[t])cout << "Error, removing component " << t << " on a GameObject that doesnt have it" << endl;
	else{
		delete components[t];
		components[t]=nullptr;
		hasComponent[t]=false;
	}
}

bool GameObject::IsDead()const{
	return false;
}