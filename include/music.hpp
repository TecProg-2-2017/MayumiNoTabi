#ifndef MUSICHPP
#define MUSICHPP

#include <common.hpp>

class Music{
	shared_ptr<Mix_Music> music;
public:
	Music();
	Music(string file);

	void play_music(int times);
	void stop_music();
	void open_music_file(string file);
	bool music_is_open();
};

#endif//MUSICHPP
