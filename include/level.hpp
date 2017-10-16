#ifndef LEVELHPP
#define LEVELHPP

#include <common.hpp>

#include <sprite.hpp>
#include <tileMap.hpp>
#include <tileSet.hpp>

class Level {
	string level_tile_set_filename;
	string background_file_name;
	vector<string> level_object_list;
	vector<int> level_collision_groups;
public:
	Sprite background_sprite;
	TileSet level_tile_set;
	TileMap level_tile_map;
	vector<int> level_collision_layer;
	
	Level();
	Level(string file);
	~Level();
	
	void load_level_from_file(const string& file);
	string save_level_to_file(const string& file="");
	
	void load_level_objects(bool collisors=true);
	void save_level_objects(const vector<pair<ii,ii>>& grouped);
	
	bool operator==(Level& level);
};
#endif //LEVELHPP
