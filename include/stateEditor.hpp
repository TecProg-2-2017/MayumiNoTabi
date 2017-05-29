#ifndef STATEEDITORHPP
#define STATEEDITORHPP

#include <common.hpp>

#include <level.hpp>
#include <state.hpp>
#include <text.hpp>

class StateEditor: public State{
	Level level;
	
	int tileIndex;
	bool showGrid;
	bool showHelp;
	Text helpText;
	Text statusText;
public:
	StateEditor();
	~StateEditor();

	virtual void Update(float time);
	virtual void Render();

	virtual void Pause();
	virtual void Resume();

	virtual void LoadAssets();
	
	void RenderBackground();
	void RenderGrid(int x, int y, int w, int h);
	void RenderBorder();
	void RenderCursor();
	
	Vec2 GetCurrentTile();
};

#endif//STATEEDITORHPP
