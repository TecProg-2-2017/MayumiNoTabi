#ifndef STATESTAGEHPP
#define STATESTAGEHPP

#include <common.hpp>

#include <level.hpp>
#include <music.hpp>
#include <state.hpp>
#include <game.hpp>


#define STATESTAGE ((StateStage*)&GAMESTATE)
#define PLAYER_UID (STATESTAGE->player)
#define PLAYER (GAMESTATE.entities[PLAYER_UID].get())

class StateStage: public State{
	string level_name = "";
	Level level;
public:
	uint player;

	StateStage(string level = "");
	~StateStage();

	virtual void update(float time = "");
	virtual void render();

	virtual void Begin();
	virtual void Pause();
	virtual void Resume();

	virtual void LoadAssets();
	virtual void LoadGUI();

	Sprite florest_bg1;
	Sprite florest_bg2;
	Sprite florest_bg3;
};

#endif//STATESTAGEHPP
