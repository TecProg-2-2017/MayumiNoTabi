/*!
 *  File: main.cpp
 *
 *  Description: Main game file 
 */ 

#include <resources.hpp>
#include <game.hpp>

unordered_map<string,shared_ptr<SDL_Texture>> Resources::imageTable;
unordered_map<string,shared_ptr<Mix_Music>> Resources::musicTable;
unordered_map<string,shared_ptr<Mix_Chunk>> Resources::soundTable;
unordered_map<string,shared_ptr<TTF_Font>> Resources::fontTable;
map<string,vector<string>> Resources::blueprintTable;


/*!
 *  @fn shared_ptr<SDL_Texture> Resources::GetImage(const string& file) 
 *  @brief Load texture 
 *  @param cons string& file 
 *  @return shared_ptr<SDL_Texture> 
 */
shared_ptr<SDL_Texture> Resources::GetImage(const string& file) {

    //! TODO: Insert else to do nothing
    if (imageTable.count(file)) {
        return imageTable[file];
    }

    //! Load texture of the file 
    SDL_Texture* texture = IMG_LoadTexture(GAMERENDER,file.c_str());

    //! Exit game if texture does not load 
    //! TODO: Insert else to do nothing
    if (!texture) {
        cerr << "Erro ao carregar textura \"" << file << "\":" << endl;
        string s=SDL_GetError();
        cerr << s << endl << "o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }

    auto func = [](SDL_Texture* texture) {SDL_DestroyTexture(texture);};
    return imageTable[file] = shared_ptr<SDL_Texture>(texture,func);
}

/*!
 *  @fn void Resources::ClearImages() 
 *  @brief Clear texture images 
 *  @return The method returns no param
 */
void Resources::ClearImages() {

    //! Iterate through images from imageTable
    for (auto i=imageTable.begin();i!=imageTable.end();) {

        //! Erase image
        if (i->second.unique()) {
            i=imageTable.erase(i);
        }
        else {
            i++;
        }
    }
}

/*!
 *  @fn shared_ptr<Mix_Music> Resources::GetMusic(const string& file) 
 *  @brief Get music resources 
 *  @return shared_ptr<Mix_Music> 
 */
shared_ptr<Mix_Music> Resources::GetMusic(const string& file) {

    //! TODO: Insert else to do nothing
    if (musicTable.count(file)) {
        return musicTable[file];
    }

    //! Load music from the file 
    Mix_Music* music = Mix_LoadMUS(file.c_str());

    //! Exit if there's an error with the music load
    //! TODO: Insert else to do nothing
    if (!music) {
        cerr << "Erro ao carregar musica \"" << file << "\":" << endl;
        string s=SDL_GetError();
        cerr << s << endl << "o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }

    auto func = [](Mix_Music* music) {Mix_FreeMusic(music);};
    return musicTable[file] = shared_ptr<Mix_Music>(music,func);
}

/*!
 *  @fn void Resources::ClearMusic() 
 *  @brief Clear load music 
 *  @return The method returns no param
 */
void Resources::ClearMusics() {

    //! Iterate through musics from musicTable
    for (auto i=musicTable.begin();i!=musicTable.end();) {

        //! Erase music
        if (i->second.use_count()==1) {
            i=musicTable.erase(i);
        }
        else {
             i++;
        }
    }
}

/*!
 *  @fn shared_ptr<Mix_Chunk> Resources::GetSound(const string& file) 
 *  @brief Get sound resources 
 *  @return shared_ptr<Mix_Chunk> 
 */
shared_ptr<Mix_Chunk> Resources::GetSound(const string& file) {

    //! TODO: Insert else to do nothing
    if (soundTable.count(file)) {
        return soundTable[file];
    }

    //! Load sound from the file 
    Mix_Chunk* sound = Mix_LoadWAV(file.c_str());

    //! Exit if there's an error with the sound load
    //! TODO: Insert else to do nothing
    if (!sound) {
        cerr << "Erro ao carregar som \"" << file << "\":" << endl;
        string s=SDL_GetError();
        cerr << s << endl << "o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }

    auto func = [](Mix_Chunk* sound) {Mix_FreeChunk(sound);};
    return soundTable[file] = shared_ptr<Mix_Chunk>(sound,func);
}

/*!
 *  @fn void Resources::ClearSounds() 
 *  @brief Clear load sound 
 *  @return The method returns no param
 */
void Resources::ClearSounds() {

    //! Iterate through sounds from soundTable 
    for (auto i=soundTable.begin();i!=soundTable.end();) {

        //! Erase sound 
        if (i->second.use_count()==1) {
            i=soundTable.erase(i);
        }
        else {
            i++;
        }
    }
}

/*!
 *  @fn shared_ptr<TTF_Font> Resources::GetFont(const string& file,int ptsize)
 *  @brief Get text font resources 
 *  @param const string& file, int ptsize
 *  @return shared_ptr<TTF_Font>
 */
shared_ptr<TTF_Font> Resources::GetFont(const string& file,int ptsize) {

    string key = file+std::to_string(ptsize);

    //! TODO: Insert else to do nothing
    if (fontTable.count(key)) {
        return fontTable[key];
    }

    //! Load fonts from the file 
    TTF_Font* font = TTF_OpenFont(file.c_str(),ptsize);

    //! Exit if there's an error with the font load
    //! TODO: Insert else to do nothing
    if (!font) {
        cerr << "Erro ao carregar fonte \"" << file << "\":" << endl;
        string s=SDL_GetError();
        cerr << s << endl << "o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }

    auto func = [](TTF_Font* font) {TTF_CloseFont(font);};
    return fontTable[key] = shared_ptr<TTF_Font>(font,func);
}
    
/*!
 *  @fn void Resources::ClearFonts() 
 *  @brief Clear load fonts 
 *  @return The method returns no param
 */
void Resources::ClearFonts() {

    //! Iterate through fonts from fontTable 
    for (auto i=fontTable.begin();i!=fontTable.end();) {

        //! Erase font 
        if (i->second.use_count()==1) {
            i=fontTable.erase(i);
        }
        else {
            i++;
        }
    }
}

/*!
 *  @fn const vector<string>& Resources::GetBlueprint(const string& file) 
 *  @brief Get blueprint resources 
 *  @param const string& file
 *  @return const vector<string>&
 */
const vector<string>& Resources::GetBlueprint(const string& file) {

    if (blueprintTable.count(file)) {
        return blueprintTable[file];
    }
    
    ifstream in; //! <Receive input from blueprint file
    in.open(BLUEPRINT_PATH + file + ".txt");

    //! Get an error while opening the file
    //! TODO: Insert else to do nothing
    if (!in.is_open()) {
        cerr << "Erro ao abrir o arquivo \"" << file << "\", o programa ira encerrar agora" << endl;
        exit(EXIT_FAILURE);
    }

    //! Iterate through the file adding blueprint to the blueprintTable 
    for (string component;getline(in, component);) {
        blueprintTable[file].push_back(component);
    }

    in.close();
    return blueprintTable[file];
}
