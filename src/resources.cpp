/*!
 *  File: main.cpp
 *
 *  Description: Main game file 
 */ 

#include <resources.hpp>
#include <game.hpp>
#include <assert.h>

unordered_map<string,shared_ptr<SDL_Texture>> Resources::game_image_table;
unordered_map<string,shared_ptr<Mix_Music>> Resources::game_music_table;
unordered_map<string,shared_ptr<Mix_Chunk>> Resources::game_sound_table;
unordered_map<string,shared_ptr<TTF_Font>> Resources::game_font_table;
map<string,vector<string>> Resources::game_blueprint_table;

/*!
 *  @fn shared_ptr<SDL_Texture> Resources::game_get_image(const string& file) 
 *  @brief Load texture 
 *  @param cons string& file 
 *  @return shared_ptr<SDL_Texture> 
 */
shared_ptr<SDL_Texture> Resources::game_get_image(const string& file) {
    assert(file != NULL);

    if (game_image_table.count(file)) {
        return game_image_table[file];
    }
    else {
        // Do nothing
    }

    //! Load texture of the file 
    SDL_Texture* texture = IMG_LoadTexture(GAMERENDER,file.c_str());

    //! Exit game if texture does not load 
    if (!texture) {
        cerr << "Erro ao carregar textura \"" << file << "\":" << endl;
        sdl_error(); 
    }
    else {
        // Do nothing
    }

    auto func = [](SDL_Texture* texture) {SDL_DestroyTexture(texture);};

    return game_image_table[file] = shared_ptr<SDL_Texture>(texture,func);
}

/*!
 *  @fn shared_ptr<Mix_Music> Resources::game_get_music(const string& file) 
 *  @brief Get music resources 
 *  @return shared_ptr<Mix_Music> 
 */
shared_ptr<Mix_Music> Resources::game_get_music(const string& file) {
    assert(file != NULL);

    if (game_music_table.count(file)) {
        return game_music_table[file];
    }
    else {
        // Do nothing
    }

    //! Load music from the file 
    Mix_Music* music = Mix_LoadMUS(file.c_str());

    //! Exit if there's an error with the music load
    if (!music) {
        cerr << "Erro ao carregar musica \"" << file << "\":" << endl;

        sdl_error();
    }
    else {
        // Do nothing
    }

    auto func = [](Mix_Music* music) {Mix_FreeMusic(music);};

    return game_music_table[file] = shared_ptr<Mix_Music>(music,func);
}

/*!
 *  @fn shared_ptr<Mix_Chunk> Resources::game_get_sound(const string& file) 
 *  @brief Get sound resources 
 *  @return shared_ptr<Mix_Chunk> 
 */
shared_ptr<Mix_Chunk> Resources::game_get_sound(const string& file) {
    assert(file != NULL);

    if (game_sound_table.count(file)) {
        return game_sound_table[file];
    }
    else {
        // Do nothing
    }

    //! Load sound from the file 
    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());

    //! Exit if there's an error with the sound load
    if (!sound) {
        cerr << "Erro ao carregar som \"" << file << "\":" << endl;

        sdl_error();
    }
    else {
        // Do nothing
    }

    auto func = [](Mix_Chunk* sound) {Mix_FreeChunk(sound);};

    return game_sound_table[file] = shared_ptr<Mix_Chunk>(sound,func);
}

/*!
 *  @fn shared_ptr<TTF_Font> Resources::game_get_font(const string& file,int ptsize)
 *  @brief Get text font resources 
 *  @param const string& file, int ptsize
 *  @return shared_ptr<TTF_Font>
 */
shared_ptr<TTF_Font> Resources::game_get_font(const string& file,int ptsize) {
    assert(file != NULL);

    string key = file+std::to_string(ptsize);

    if (game_font_table.count(key)) {
        return game_font_table[key];
    }
    else {
        // Do nothing
    }

    //! Load fonts from the file 
    TTF_Font* font = TTF_OpenFont(file.c_str(),ptsize);

    //! Exit if there's an error with the font load
    if (!font) {
        cerr << "Erro ao carregar fonte \"" << file << "\":" << endl;

        sdl_error();
    }
    else {
        // Do nothing
    }

    auto func = [](TTF_Font* font) {TTF_CloseFont(font);};

    return game_font_table[key] = shared_ptr<TTF_Font>(font,func);
}

/*!
*  @fn const vector<string>& Resources::game_get_blueprint(const string& file) 
*  @brief Get blueprint resources 
*  @param const string& file
*  @return const vector<string>&
*/
const vector<string>& Resources::game_get_blueprint(const string& file) {

    if (game_blueprint_table.count(file)) {
        return game_blueprint_table[file];
    }
    
    ifstream file_input; //! <Receive input from blueprint file
    file_input.open(BLUEPRINT_PATH + file + ".txt");
    
    //! Check if file is open 
    is_file_open(file_input, file);
    
    file_input.close();
    return game_blueprint_table[file];
}

/*!
 *  @fn void Resources::add_blueprint_to_table(ifstream& file_input) 
 *  @brief Add blueprint read from to file to the table  
 *  @param ifstream& file_input
 *  @return The method returns no param
 */
void Resources::add_blueprint_to_table(ifstream& file_input) {
    assert(file_input != NULL);

    //! Iterate through the file adding blueprint to the game_blueprint_table 
    for (string component;getline(file_input, component);) {
        game_blueprint_table[file_input].push_back(component);
    }
}

/*!
 *  @fn void Resources::game_clear_images() 
 *  @brief Clear texture images 
 *  @return The method returns no param
 */
void Resources::game_clear_images() {

    //! Iterate through images from game_image_table
    for (auto i=game_image_table.begin();i!=game_image_table.end();) {

        //! Erase image
        if (i->second.unique()) {
            i=game_image_table.erase(i);
        }
        else {
            i++;
        }
    }
}

/*!
 *  @fn void Resources::game_clear_musics() 
 *  @brief Clear load music 
 *  @return The method returns no param
 */
void Resources::game_clear_musics() {

    //! Iterate through musics from game_music_table
    for (auto i=game_music_table.begin();i!=game_music_table.end();) {

        //! Erase music
        if (i->second.use_count()==1) {
            i=game_music_table.erase(i);
        }
        else {
             i++;
        }
    }
}

/*!
 *  @fn void Resources::game_clear_sounds() 
 *  @brief Clear load sound 
 *  @return The method returns no param
 */
void Resources::game_clear_sounds() {

    //! Iterate through sounds from game_sound_table 
    for (auto i=game_sound_table.begin();i!=game_sound_table.end();) {

        //! Erase sound 
        if (i->second.use_count()==1) {
            i=game_sound_table.erase(i);
        }
        else {
            i++;
        }
    }
}
   
/*!
 *  @fn void Resources::game_clear_fonts() 
 *  @brief Clear load fonts 
 *  @return The method returns no param
 */
void Resources::game_clear_fonts() {

    //! Iterate through fonts from game_font_table 
    for (auto i=game_font_table.begin();i!=game_font_table.end();) {

        //! Erase font 
        if (i->second.use_count()==1) {
            i=game_font_table.erase(i);
        }
        else {
            i++;
        }
    }
}

/*!
 *  @fn void Resources::is_file_open(ifstream& file_input, const string& file)
 *  @brief Check if file is open and exit the game if it is not 
 *  @param ifstream& file_input, const string& file
 *  @return The method returns no param
 */
void Resources::is_file_open(ifstream& file_input, const string& file) {
    
    //! Get an error while opening the file
    if (!file_input.is_open()) {
        cerr << "Erro ao abrir o arquivo \"" << file << "\", o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        // Do nothing
    }
}

/*!
 *  @fn void Resources::sdl_error()
 *  @brief Get sdl error and exit the game
 *  @return The method returns no param
 */
void Resources::sdl_error() {
    string error=SDL_GetError();

    cerr << error << endl << "o programa ira encerrar agora" << endl;

    exit(EXIT_FAILURE);
}
