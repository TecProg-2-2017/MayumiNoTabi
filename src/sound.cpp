/*
*  File: sound.cpp
*
*  Description: Implements Sound Class
*/

#include <sound.hpp>
#include <resources.hpp>


Sound::Sound():channel{-1},chunk{shared_ptr<Mix_Chunk>(nullptr)}{}

/*!
* @fn Sound::Sound(string file)
* @brief Constructor Method for sound component
* @param string file
*/

Sound::Sound(string file) {
	Open(file);
}

/*!
* @fn Sound::Play(int times)
* @brief Counts how many times the sound has been executed?
* @param int times
*/

void Sound::Play(int times) {
	channel = Mix_PlayChannel(-1,chunk.get(),times);
}

/*!
* @fn Sound::Stop()
* @brief Method to stop the sound
* @param No params
*/

void Sound::Stop() {
	//! TODO:Refactorate decision structure
	if (channel!=-1) {
		Mix_HaltChannel(channel);
		channel=-1;
	}
}

/*!
* @fn Sound::Open(string file)
* @brief Recovers sound from Resources class
* @param string file
*/

void Sound::Open(string file) {
	chunk=Resources::game_get_sound(file);
}

/*!
* @fn Sound::IsOpen()
* @brief Verifies if sound has recovered the correct sound file
* @param No params
*/

bool Sound::IsOpen() {
	return (chunk.get()!=nullptr);
}
