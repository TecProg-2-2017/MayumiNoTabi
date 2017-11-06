/*!
 *  @file File game.cpp
 *  @brief Implementation of the class of game actions
 *
 *  The class implemented provides the flow of the game
 *
 *  @sa game.hpp
 *
 *  @warning All variables are initialized
 */


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include <game.hpp>
#include <gameException.hpp>
#include <inputManager.hpp>
#include <resources.hpp>
#include <state.hpp>

#include <assert.h>


Game* Game::instance = 0;

/*!
	@fn Game::Game(string title,int width,int height):frameStart{0},dt{0},winSize{(float)width,(float)height}
	@brief This is a constructor
	@param title
	@param width
	@param height
	@warning Method that requires review of comment
*/

Game::Game(string title, int width, int height):frameStart{0},deltatime{0},windowSize{
																												(float)width,(float)height} {
		LOG_METHOD_START('Game::Game');
		LOG_VARIABLE("Game::Game", "title","width","height");

		assert(title != "");
		assert(width > 0);
		assert(height > 0);

	  srand(time(NULL));

	// Check if a instance was create
		checkInstance();

	// Check all SDL outputs and if can't be initialize display a error messege
  	checkSDLOutputs();

		int res = IMAGE_Init(image_settings);
	// Initialize Audio, Image and TTF modules
		initializeModules(res);

	// Creating the window that will contain the game interface
		windowCreate();

		SDL_SetRenderDrawBlendMode(GAMERENDER, SDL_BLENDMODE_BLEND);

		LOG_METHOD_CLOSE('Game::Game', "constructor");

};

/*!
	@fn Game::~Game()
	@brief This is a destructor
	@warning Method that requires review of comment
*/

Game::~Game() {

	LOG_METHOD_START('Game::Game', "destructor");

	checkStackState();

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearFonts();

	TTF_Quit();

	Mix_CloseAudio();
	Mix_Quit();

	IMAGE_Quit();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	LOG_METHOD_CLOSE('Game::Game', "destructor");

}

/*!
	@fn Game& Game::GetInstance()
	@brief Create a instance of class Game
	@return Returns a instance of Game
	@warning Method that requires review of comment
*/

Game& Game::GetInstance() {

	LOG_METHOD_START('Game::GetInstance');
	LOG_METHOD_CLOSE('Game::GetInstance');

	return (*instance);

}

/*!
	@fn State& Game::GetCurrentState()
	@brief Verify the current object state
	@return state
	@warning Method that requires review of comment
*/

State& Game::GetCurrentState() {

	LOG_METHOD_START('Game::GetCurrentState');
	LOG_METHOD_CLOSE('Game::GetCurrentState');

	return (*stateStack.top());

}

/*!
	@fn void Game::Run()
	@brief
	@param
	@return
	@warning Method that requires review of comment
*/

SDL_Renderer* Game::GetRenderer() {

	LOG_METHOD_START('Game::GetRenderer');
	LOG_METHOD_CLOSE('Game::GetRenderer');

	return renderer;

}

/*!
	@fn void Game::Push(State* state)
	@brief Swapping the object state
	@param state
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Game::Push(State* state) {

	LOG_METHOD_START('Game::Push');
	LOG_VARIABLE("Game::Push", "state");

	checkStoredState();

	assert(state != NULL);

	if (storedState){
		delete storedState;
	}
	storedState=state;

	LOG_METHOD_CLOSE('Game::Push',"void");
}

/*!
	@fn void Game::Run()
	@brief
	@param
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Game::Run() {

	LOG_METHOD_START('Game::Run');

	if (storedState) {

		stateStack.push(unique_ptr<State>(storedState));
		storedState=nullptr;

		GetCurrentState().Begin();
	}
	else {
		//Nothing to do
	}

	while (!stateStack.empty()) {
		CalculateDeltaTime();

		// Update the state of the game elements and set it

		INPUT.input_event_handler(deltatime);
		//if (INPUT.KeyPress(KEY_F(11))) SwitchWindowMode();

		GetCurrentState().update(deltatime);
		GetCurrentState().render();

		SDL_RenderPresent(renderer);

		/* If the user press Pause button the system change the status to paused
			or press End button stop the game and reset
			*/
			pauseOrEndGame();

		SDL_Delay(17);
	}

	while (stateStack.size()) {
		GetCurrentState().End();
		stateStack.pop();
	}

	LOG_METHOD_CLOSE('Game::Run');

}

float Game::GetDeltaTime() {

	LOG_METHOD_START('Game::GetDeltaTime');
	LOG_METHOD_CLOSE('Game::GetDeltaTime',"float");

	return deltatime;
}

/*!
	@fn void Game::CalculateDeltaTime()
	@brief
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Game::CalculateDeltaTime() {

	LOG_METHOD_START('Game::CalculateDeltaTime');

	unsigned int tmp = frameStart;

	//Define the response time of a frame
	frameStart = SDL_GetTicks();
	deltatime = max((frameStart - tmp) / 1000.0, 0.001);

	LOG_METHOD_CLOSE('Game::CalculateDeltaTime',"void");
}

/*!
	@fn void Game::SwitchWindowMode()
	@brief
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

//! Functions to be called by the methods in order to perform actions

void Game::SwitchWindowMode() {

	LOG_METHOD_START('Game::SwitchWindowMode');
	LOG_METHOD_CLOSE('Game::SwitchWindowMode',"void");
	// Method body its empty
}

void checkInstance(){

	LOG_METHOD_START('checkInstance');
	LOG_VARIABLE("checkInstance", "title","width","height");
	assert(title != "");
	assert(width > 0);
	assert(height > 0);

	if (instance) {

		cerr << "Erro, mais de uma instancia de 'Game' instanciada, o programa ira encerrar agora" << endl;

		exit(EXIT_FAILURE);
	}
	else {

		instance = this;

	}

	LOG_METHOD_CLOSE('checkInstance',"void");

}

void checkSDLOutputs(){

	LOG_METHOD_START('checkSDLOutputs');

	bool success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == 0;

	if (!success) {

		string error_msg(error_messege = SDL_GetError());
		error_messege = "Could not initialize SDL:\n" + error_messege;

		throw GameException(error_messege);
	}
	else {
		//Nothing to do
	}

	LOG_METHOD_START('checkSDLOutputs',"void");
}

void initializeImageLibrary(int image_settings, int res){

	/* Check the possibility initiation of SDL audio and return a error messege
		 if its necessary
	 */

	LOG_METHOD_START('initializeImageLibrary');
	LOG_VARIABLE("initializeImageLibrary", "image_settings","res");
	assert (image_settings >= 0);
	assert (res >=0);

	if (image_settings != res) {

		string error_messege_main = SDL_GetError();
		string error_messege = "Could not initiazlie image libary for type:";

		for (auto format : image_formats) {
			if ((format & res) == 0) {
				error_messege += code_name_map[format];
			}
			else {
				//Nothing to do
			}

		}

		error_messege += "\n";
		error_messege = error_messege_main + error_messege;

		throw GameException(error_messege);
	}
	else {
		//Nothing to do
	}

	LOG_METHOD_CLOSE('initializeImageLibrary',"void");

}

void initializeImageModule(int res) {

	LOG_METHOD_START('initializeImageModule');
	LOG_VARIABLE("initializeImageModule", "res");
	assert (res >=0);

	map<int, string> code_name_map = {{IMAGE_INIT_TIF, "tif"},
									  {IMAGE_INIT_JPG, "jpg"},
									  {IMAGE_INIT_PNG, "png"}};

	vector<int> image_formats{IMAGE_INIT_TIF, IMAGE_INIT_JPG, IMAGE_INIT_PNG};

	// Initialize image module or between all desired formats

	int image_settings = accumulate(image_formats.begin(),
									image_formats.end(),
									0,
									[](const int &a, const int &b) {
										return a | b;
									}
	);

	initializeImageLibrary(image_settings, res);

	LOG_METHOD_CLOSE('initializeImageModule',"void");

}

void initializeAudioModule(int res, int audio_modules){

	LOG_METHOD_START('initializeAudioModule');
	LOG_VARIABLE("initializeAudioModule", "res","audio_modules");
	assert (res >=0);
	assert (audio_modules >= 0);

	if (res != audio_modules) {

		throw GameException("Problem when initiating SDL audio!");

		if ((MIX_INIT_OGG & res ) == 0 ){
			cerr << "OGG flag not in res!" << endl;
		}
		else if ((MIX_INIT_MP3 & res ) == 0 ) {
			cerr << "MP3 flag not in res!" << endl;
		}
		else {
			//Nothing to do
		}

	}

	LOG_METHOD_CLOSE('initializeAudioModule',"void");

}

void installSDLAudio(int res){

	LOG_METHOD_START('installSDLAudio');
	LOG_VARIABLE("installSDLAudio", "res");
	assert (res >=0);

	if (res != 0){
		throw GameException("Problem when initiating SDL audio!");
	}
	else {
		//Nothing to do
	}

	LOG_METHOD_CLOSE('installSDLAudio', "void");
}

void initializeTTFModule(int res){

	LOG_METHOD_START('initializeTTFModule');
	LOG_VARIABLE("initializeTTFModule", "res");
	assert (res >=0);

	if (res != 0){
		cerr << "Could not initialize TTF module!" << endl;
	}
	else {
		//Nothing to do
	}

	LOG_METHOD_START('initializeTTFModule',"void");

}

void initializeModules(int res){

	LOG_METHOD_START('initializeModules');
	LOG_VARIABLE("initializeModules", "res");
	assert (res >=0);

	// Initialize image module and check if process went OK

 		initializeImageModule()

	// Initialize audio module
		int audio_modules = MIX_INIT_OGG;
		res = Mix_Init(audio_modules);

	/* Check the possibility initiation of SDL audio and return a error messege
		 if its necessary
	 */

		initializeAudioModule(res, audio_modules);
		res = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
		installSDLAudio(res);

		// Initialize TTF module
	 	res = TTF_Init();
	 	initializeTTFModule(int res);

		LOG_METHOD_CLOSE('initializeModules',"void");

}

void windowCreate(){

	LOG_METHOD_START('windowCreate');

	window = SDL_CreateWindow(title.c_str(),
														SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
														width, height, SDL_WINDOW_FULLSCREEN);

	if (!window){
		throw GameException("Window nao foi carregada)!");
	}
	else {
		//Nothing to do
	}

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	if (!renderer){
		throw GameException("Erro ao instanciar renderizador da SDL!");
	}
	else {
		//Nothing to do
	}

	storedState = nullptr;

	LOG_METHOD_CLOSE('windowCreate');
}

void checkStoredState(){

	LOG_METHOD_START('checkStoredState');

	if (storedState) {
		delete storedState;
	}
	else{
		//Nothing to do
	}

	LOG_METHOD_CLOSE('checkStoredState', "void");

}

void checkStackState(){

LOG_METHOD_START('checkStackState');

	while (stateStack.size()) {
		delete stateStack.top().get();
		stateStack.pop();
	}

	checkStoredState();

}

void pauseOrEndGame(){
	if (GetCurrentState().get_quit_requested()) {
		GetCurrentState().Pause();
			break;
	}
	else if (GetCurrentState().PopRequested()) {
		GetCurrentState().End();
		stateStack.pop();

		Resources::game_clear_images();
		Resources::game_clear_musics();
		Resources::game_clear_fonts();

		if (stateStack.size()) {
			GetCurrentState().Resume();
		}

	}
	else {
		//Nothing to do
	}

	if (storedState) {
		GetCurrentState().Pause();
		stateStack.push(unique_ptr<State>(storedState));
		storedState=nullptr;
		GetCurrentState().Begin();
	}
	else {
		//Nothing to do
	}

	LOG_METHOD_CLOSE('checkStackState',"void");

}
