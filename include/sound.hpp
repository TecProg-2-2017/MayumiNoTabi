#ifndef SOUNDHPP
#define SOUNDHPP

#include <common.hpp>

class Sound{
	int channel;
	shared_ptr<Mix_Chunk> chunk;
public:
	Sound();
	Sound(string file);

	void play_music(int times);
	void Stop();
	void open_music_file(string file);
	bool IsOpen();
};

#endif//SOUNDHPP
