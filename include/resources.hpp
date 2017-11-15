#ifndef RESOURCESHPP
#define RESOURCESHPP

#include <common.hpp>

class Resources{
	static unordered_map<string,shared_ptr<SDL_Texture>> game_image_table;
	static unordered_map<string,shared_ptr<Mix_Music>> game_music_table;
	static unordered_map<string,shared_ptr<Mix_Chunk>> game_sound_table;
	static unordered_map<string,shared_ptr<TTF_Font>> game_font_table;
	static map<string,vector<string>> game_blueprint_table;
public:
	static shared_ptr<SDL_Texture> game_get_image(const string& file);
	static void game_clear_images();

	static shared_ptr<Mix_Music> game_get_music(const string& file);
	static void game_clear_musics();

	static shared_ptr<Mix_Chunk> game_get_sound(const string& file);
	static void game_clear_sounds();

	static shared_ptr<TTF_Font> game_get_font(const string& file,int ptsize);
	static void game_clear_fonts();

	static const vector<string>& game_get_blueprint(const string& file);

};

#endif//RESOURCESHPP
