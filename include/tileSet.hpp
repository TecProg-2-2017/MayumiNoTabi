#ifndef TILESETHPP
#define TILESETHPP

#include <common.hpp>

#include <sprite.hpp>

class TileSet{
	Sprite tileSet;

	int rows = 0;
	int columns = 0;

	int tile_width = 0;
	int tile_height = 0;
public:
	TileSet();
	TileSet(int  width = 0,int height = 0,string file_path);

	void load(int width = 0, int height = 0, string file_path);

	void render(unsigned int index,float position_x,float position_y, float extended_scale = 1.0f);

	int get_width();
	int get_height();
	int get_tile_count();
};

#endif//TILESETHPP
