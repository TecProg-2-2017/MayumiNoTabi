/*!
 *  @file File game.cpp
 *  @brief Implementation of the class of game actions
 *
 *  The class implemented provides the flow of the game
 *
 *  @sa game.hpp
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


Game* Game::instance = NULL;

/*!
	@fn Game::Game(string title,int width,int height):frameStart{0},dt{0},winSize{(float)width,(float)height}
	@brief This is a constructor
	@param title
	@param width
	@param height
	@warning Method that requires review of comment
*/

Game::Game(string title,int width,int height):frameStart{0},deltatime{0},windowSize{(float)width,(float)height} {

	srand(time(NULL));

	if (instance) {
		cerr << "Erro, mais de uma instancia de 'Game' instanciada, o programa ira encerrar agora" << endl;
		exit(EXIT_FAILURE);
	}

	instance=this;

	bool success = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == 0;

	if (!success) {
		string error_msg(error_messege = SDL_GetError());
		error_messege = "Could not initialize SDL:\n" + error_messege;
		throw GameException(error_messege);
	}

	// Initialize image module and check if process went OK

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

	int res = IMAGE_Init(image_settings);

	/* Check the possibility initialize image library and return the error messege
	   for ever type
	 */

	if (image_settings != res) {
		string error_messege_main = SDL_GetError();
		string error_messege = "Could not initiazlie image libary for type:";
		for (auto format : image_formats)
			if ((format & res) == 0) {
				error_messege += code_name_map[format];
			}
		error_messege += "\n";
		error_messege = error_messege_main + error_messege;

		throw GameException(error_messege);
	}

	int audio_modules = MIX_INIT_OGG;
	res = Mix_Init(audio_modules);

	/* Check the possibility initiation of SDL audio and return a error messege
		 if its necessary
	 */

	if (res != audio_modules) {
		if ((MIX_INIT_OGG & res ) == 0 )cerr << "OGG flag not in res!" << endl;
		if ((MIX_INIT_MP3 & res ) == 0 )cerr << "MP3 flag not in res!" << endl;
		throw GameException("Problem when initiating SDL audio!");
	}

	res = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

	if (res != 0)throw GameException("Problem when initiating SDL audio!");

	res = TTF_Init();
	if (res != 0)cerr << "Could not initialize TTF module!" << endl;

	// Creating the window that will contain the game interface


	window = SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_FULLSCREEN);

	if (!window)throw GameException("Window nao foi carregada)!");

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if (!renderer)throw GameException("Erro ao instanciar renderizador da SDL!");

	storedState = nullptr;
	SDL_SetRenderDrawBlendMode(GAMERENDER, SDL_BLENDMODE_BLEND);
};

/*!
	@fn Game::~Game()
	@brief This is a destructor
	@warning Method that requires review of comment
*/

Game::~Game() {
	while (stateStack.size()) {
		delete stateStack.top().get();
		stateStack.pop();
	}
	if (storedState)delete storedState;
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
}

/*!
	@fn Game& Game::GetInstance()
	@brief Create a instance of class Game
	@return Returns a instance of Game
	@warning Method that requires review of comment
*/

Game& Game::GetInstance() {
	return (*instance);
}

/*!
	@fn State& Game::GetCurrentState()
	@brief Verify the current object state
	@return state
	@warning Method that requires review of comment
*/

State& Game::GetCurrentState() {
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
	if (storedState)delete storedState;
	storedState=state;
}

/*!
	@fn void Game::Run()
	@brief
	@param
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Game::Run() {

	if (storedState) {
		stateStack.push(unique_ptr<State>(storedState));
		storedState=nullptr;
		GetCurrentState().Begin();
	}
	while (!stateStack.empty()) {
		CalculateDeltaTime();
		INPUT.update(deltatime);
		//if (INPUT.KeyPress(KEY_F(11))) SwitchWindowMode();
		GetCurrentState().update(deltatime);
		GetCurrentState().render();

		SDL_RenderPresent(renderer);

		if (GetCurrentState().QuitRequested()) {
				break;
		}

		if (GetCurrentState().PopRequested()) {
			GetCurrentState().Pause();
			GetCurrentState().End();
			stateStack.pop();
			Resources::ClearImages();
			Resources::ClearMusics();
			Resources::ClearFonts();

			if (stateStack.size()) {
				GetCurrentState().Resume();
			}
		}

		if (storedState) {
			GetCurrentState().Pause();
			stateStack.push(unique_ptr<State>(storedState));
			storedState=nullptr;
			GetCurrentState().Begin();
		}

		SDL_Delay(17);
	}
	while (stateStack.size()) {
		GetCurrentState().End();
		stateStack.pop();
	}
}

float Game::GetDeltaTime() {
	return deltatime;
}

/*!
	@fn void Game::CalculateDeltaTime()
	@brief
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Game::CalculateDeltaTime() {
	unsigned int tmp = frameStart;
	frameStart = SDL_GetTicks();
	deltatime = max((frameStart - tmp) / 1000.0, 0.001);
}

/*!
	@fn void Game::SwitchWindowMode()
	@brief
	@return The execution of this method returns no value
	@warning Method that requires review of comment
*/

void Game::SwitchWindowMode() {
	// Method body its empty
}
