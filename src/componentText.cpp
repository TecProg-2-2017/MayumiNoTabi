#include <componentText.hpp>
#include <gameObject.hpp>
#include <camera.hpp>
//#include <game.hpp>
//#include <inputManager.hpp>

CompText::CompText(const Text &t,Hotspot h,Vec2 p):txt{t},pos{p}{
	txt.SetHotspot(h);
}
CompText::CompText(string text,int size,SDL_Color c,Hotspot h,Vec2 p):txt{text,size,c},pos{p}{
	txt.SetHotspot(h);
}
CompText::~CompText(){}


void CompText::Update(float time){
	UNUSED(time);
}
void CompText::Render(){
	Vec2 p=pos+entity->box.corner();
	txt.SetPos(p);
	
	if(entity->anchored) txt.Render();
	else txt.Render(CAMERA);
}
void CompText::Own(GameObject* go){
	entity=go;
}
Component::type CompText::GetType()const{
	return Component::type::t_text;
}
