#ifndef TILESETHPP
#define TILESETHPP

#include <common.hpp>

#include <sprite.hpp>

class TileSet{
	Sprite tileSet;

	int rows;
	int columns;

	int tile_width;
	int tile_height;
public:
	TileSet();
	TileSet(int  width,int height,string file_path);

	void load(int width, int height, string file_path);

	void render(unsigned int index,float position_x,float position_y, float extended_scale = 1.0f);

	int get_width();
	int get_height();
	int get_tile_count();
};

#endif//TILESETHPP
