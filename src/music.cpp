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
    Open(file);
}

/*!
 *  @fn Music::Play(int times)
 *  @brief Play the music 
 *  @param int times 
 *  @return The method returns no param
 */
void Music::Play(int times) {
    Mix_PlayMusic(music.get(),times);
}

/*!
 *  @fn Music::Stop()
 *  @brief Stop the music 
 *  @return The method returns no param
 */
void Music::Stop() {
    Mix_FadeOutMusic(FADETIME);
}

/*!
 *  @fn Music::Open(string file)
 *  @brief Open the music file 
 *  @param string file
 *  @return The method returns no param
 */
void Music::Open(string file) {
    music=Resources::GetMusic(file);
}

/*!
 *  @fn Music::IsOpen()
 *  @brief Check if music file is open 
 *  @return True or false 
 */
bool Music::IsOpen() {
    return (music.get()!=nullptr);
}
