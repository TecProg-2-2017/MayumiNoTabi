#ifndef TILEMAPHPP
#define TILEMAPHPP

#include <common.hpp>

#include <geometry.hpp>

#define EMPTY_TILE -1

class TileSet;
class GameObject;

class TileMap{
	vector<int> tile_matrix;
	TileSet* tile_set;
	int map_width = 0;
	int map_height = 0;
	int map_depth = 0;
public:
	TileMap(int width, int height, TileSet* tile_set);
	TileMap(TileSet* tile_set);

	void load(ifstream& input_file);
	void save(stringstream& output_file);

	void set_tile_set(TileSet* tile_set);

	int& at(int position_x,int position_y,int position_z);
	int  at(int position_x,int position_y,int position_z) const;

	void define_corners(int *firstX, int *firstY, int *lastX, int *lastY,
											int width, int height,int position_x,int position_y);
	void render(Vec2 position = {0,0});
	void render_layer(int layer,int position_x=0,int position_y=0);

	int get_width() const;
	int get_height() const;
	int get_depth() const;
	void change_size(int new_width,int new_height);
};

#endif//TILEMAPHPP
