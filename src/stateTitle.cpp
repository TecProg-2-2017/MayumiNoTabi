/*!
*  @file File stateTitle.cpp
*  @brief Implementation of the class StateTitle
*
*  Auxiliary documentation
*  @sa stateTitle.hpp
*/
#include <stateTitle.hpp>
#include <camera.hpp>
#include <complib.hpp>
#include <game.hpp>
#include <inputManager.hpp>
#include <stateStage.hpp>
#include <stateEditor.hpp>
#include <assert.h>

#define BACKGROUND "img/tela-inicio2.png"
#define INSTRUCTION_TEXT "IDJ-Projeto\n\nPress [Space] to continue\n[E] Level Editor\n"

/*!
	@class StateTitle
	@brief This class provides the title states

*/

//! A constructor.
    /*!
    *	This is a constructor method of StateTitle
		*/
StateTitle::StateTitle():State::State(), bg{Sprite(BACKGROUND)},
																				bt1{"img/botao-editor.png", 2},
																				bt2{"img/botao-inicio.png", 2}{
	LOG_METHOD_START("StateTitle::StateTitle");
	LoadAssets();

	bg.StretchToFit(WINSIZE);
	LOG_METHOD_CLOSE("StateTitle::StateTitle","constructor");
}

//! A destructor.
    /*!
      This is a destructor method of StateTitle class
    */
StateTitle::~StateTitle() {
	LOG_METHOD_START("StateTitle::~StateTitle");
	LOG_METHOD_CLOSE("StateTitle::~StateTitle","destructor");
}

/*!
	@fn void StateTitle::LoadAssets()
	@brief Virtual method that loads assets
	@return The execution of this method returns no value
*/
void StateTitle::LoadAssets() {
	LOG_METHOD_START("StateTitle::LoadAssets");
	LOG_METHOD_CLOSE("StateTitle::LoadAssets","void");
}

/*!
	@fn void StateTitle::LoadGUI()
	@brief Virtual method that loads GUI
	@return The execution of this method returns no value
*/
void StateTitle::LoadGUI() {
	LOG_METHOD_START("StateTitle::LoadGUI()");
	LOG_METHOD_CLOSE("StateTitle::LoadGUI()","void");
}

/*!
	@fn void StateTitle::Begin()
	@brief Virtual method that represents the Begin title state
	@return The execution of this method returns no value
*/
void StateTitle::Begin() {
	LOG_METHOD_START("StateTitle::Begin");
	//! Defines the GameObject
	//! @var text
	GameObject* text = new GameObject{Rect{(WINSIZE.x / 2), (WINSIZE.y / 2), 0,
																					0}};//!< A GameObject with the informations of the game
	text->AddComponent(new CompText{INSTRUCTION_TEXT, 36, SDL_COLOR_WHITE,
											Hotspot::CENTER});
	AddObject(text->uid);
	LOG_METHOD_CLOSE("StateTitle::Begin","void");
}

/*!
	@fn void StateTitle::Update(float time)
	@brief Virtual method that updates the title state
	@param time
	@brief a positive float, the represents the game time
	@return The execution of this method returns no value
*/
void StateTitle::update(float time) {
	LOG_METHOD_START("StateTitle::update");
	assert(time >= 0);
	LOG_VARIABLE("time",time);
	//! Checks if the user tried to quit
	if (INPUT.QuitRequested() || INPUT.KeyPress(KEY_ESC)){
		quitRequested = true;
	}

	//! Checks if the user pressed the space key
	if (INPUT.KeyPress(KEY_SPACE)) {
		bt2.set_frame(1);
		GAMEINST.Push(new StateStage{"level_0"});
	}
	//! Checks if the user pressed the 'e' key
	if (INPUT.KeyPress(KEY(e))) {

	if (INPUT.get_quit_requested() || INPUT.key_pressed(KEY_ESC)) quit_requested=true;

	if (INPUT.key_pressed(KEY_SPACE)) {
		bt2.set_frame(1);
		GAMEINST.Push(new StateStage{"level_0"});
	}
	if (INPUT.key_pressed(KEY(e))) {

		bt1.set_frame(1);
		GAMEINST.Push(new StateEditor{});
	}
	UpdateArray(time);

	LOG_METHOD_CLOSE("StateTitle::update","void");
}

/*!
	@fn void StateTitle::render()
	@brief Virtual method that renders the title images
	@return The execution of this method returns no value
*/

void StateTitle::render() {
	LOG_METHOD_START("StateTitle::render");
	bg.render(0,0);
	bt1.render(500,300);
	bt2.render(100,300);
	// RenderArray();
	LOG_METHOD_CLOSE("StateTitle::render","void");
}

/*!
	@fn void StateTitle::Pause()
	@brief Virtual method that represents the Pause title state
	@return The execution of this method returns no value
*/
void StateTitle::Pause() {
	LOG_METHOD_START("StateTitle::Pause");
	LOG_METHOD_CLOSE("StateTitle::Pause","void");
}

/*!
	@fn void StateTitle::Resume()
	@brief Virtual method that represents the Resume title state
	@return The execution of this method returns no value
*/
void StateTitle::Resume() {
	LOG_METHOD_START("StateTitle::Resume");
	CAMERA.x=CAMERA.y=0;
	LOG_METHOD_CLOSE("StateTitle::Resume","void");
}
