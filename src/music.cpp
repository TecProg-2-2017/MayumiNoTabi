/*!
 *  File: music.cpp
 *
 *  Description: Handle music of the game
 */

#include <music.hpp>
#include <resources.hpp>

#define FADETIME 1000//ms

/*!
 *  @fn Music::Music():music{shared_ptr<Mix_Music>(nullptr)}
 *  @brief Constructor method of Music
 *  @return A Music object
 */
Music::Music():music{shared_ptr<Mix_Music>(nullptr)} {

}

/*!
 *  @fn Music::Music(string file)
 *  @brief Constructor method of Music using a file
 *  @param string file
 *  @return A Music object
 */
Music::Music(string file) {
    open_music_file(file);
}

/*!
 *  @fn Music::play_music(int times)
 *  @brief Play the music
 *  @param int times
 *  @return The method returns no param
 */
void Music::play_music(int times) {
    Mix_PlayMusic(music.get(),times);
}

/*!
 *  @fn Music::stop_music()
 *  @brief Stop the music
 *  @return The method returns no param
 */
void Music::stop_music() {
    Mix_FadeOutMusic(FADETIME);
}

/*!
 *  @fn Music::open_music_file(string file)
 *  @brief Open the music file
 *  @param string file
 *  @return The method returns no param
 */
void Music::open_music_file(string file) {
    music=Resources::game_get_music(file);
}

/*!
 *  @fn Music::music_is_open()
 *  @brief Check if music file is open
 *  @return True or false
 */
bool Music::music_is_open() {
    return (music.get()!=nullptr);
}
