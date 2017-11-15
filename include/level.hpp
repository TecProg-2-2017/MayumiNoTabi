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

	void load_read_file(ifstream& file_input, const string& file);
	void load_write_file(ofstream& file_output, const string& file);

	void load_tile_set(ifstream& file_input, string& file_parameters);

	void load_level_from_file(const string& file);
	string save_level_to_file(const string& file="");

	void map_level_area(uint& uid, map<int,pair<Rect,int>>& mp,
	        int& level_tile_width, int& level_tile_height);

	void map_collision_layer_and_groups(map<int,pair<Rect,int>>& mp,
		int& level_tile_width, int& level_tile_height);

	void create_level_objects(uint& uid);
	void save_collision_layer(stringstream& level_stream_out);

	void load_level_objects(bool collisors=true);
	void save_level_objects(const vector<pair<ii,ii>>& grouped);

	bool operator==(Level& level);
};
#endif //LEVELHPP
