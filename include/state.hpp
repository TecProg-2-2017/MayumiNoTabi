#ifndef STATEHPP
#define STATEHPP

#include <common.hpp>

#include <gameObject.hpp>
#include <guiManager.hpp>
#include <sound.hpp>


class State{
protected:

	bool popRequested=false;
	bool quit_requested=false;
	uint lastGO=-1;

	virtual void UpdateArray(float time);
	virtual void RenderArray();
public:
	GUIManager gui;
	
	set<uint> entities_;
	map<ii,set<uint>> group;

	State();
	virtual ~State() {}

	virtual void update(float time)=0;
	virtual void render()=0;

	virtual void Begin()=0;
	virtual void End();
	virtual void Pause()=0;
	virtual void Resume()=0;

	virtual void LoadAssets()=0;
	virtual void LoadGUI()=0;

	virtual void AddObject(uint uid, int layer=0, int area=0);
	virtual void ClearObjects();
	GameObject* GetLastObject();

	void AddSound(string file,int times);

	virtual bool PopRequested();
	virtual bool QuitRequested();
	
	set<uint> GetEntitiesInRange(const float &x1,const float &x2);
};

#endif//STATEHPP
