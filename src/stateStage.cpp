/*!
*  @file File stateStage.cpp
*  @brief Implementation of the class StateStage
*
*  Auxiliary documentation
*  @sa stateStage.hpp
*/
#include <stateStage.hpp>
#include <common.hpp>
#include <camera.hpp>
#include <resources.hpp>
#include <music.hpp>
#include <game.hpp>
#include <gameObject.hpp>
#include <complib.hpp>
#include <assert.h>

/*!
	@class StateStage
	@brief This class provides the stage states

*/

#define PLAYER_POSITION_AXIS_X 550.0f
#define PLAYER_POSITION_AXIS_Y 430.0f
#define BOAR_POSITION_AXIS_X 2000.0f
#define BOAR_POSITION_AXIS_Y -100.0f
#define MIKE_POSITION_AXIS_X 850.0f
#define MIKE_POSITION_AXIS_Y -100.0f
#define BANSHEE_START_POSITION_AXIS_x 850.0f
#define BANSHEE_END_POSITION_AXIS_x 230.0f
#define BANSHEE_START_POSITION_AXIS_Y -100.0f
#define BANSHEE_END_POSITION_AXIS_Y -200.0f
#define MASK_POSITION_AXIS_X 850.0f
#define MASK_POSITION_AXIS_Y -100.0f
#define FLOREST_BACKGROUND_SIZE 4032



//! A constructor.
    /*!
    *	This is a constructor method of StateStage
		* \param lvl
		* \brief A string, that represents the name of the current level
		*/
StateStage::StateStage(string lvl):levelName{lvl},
	// floresta_bg1{"img/jogotela-campo-1-away.png"},
	florest_bg2{"img/floresta-away.png"},
	florest_bg3{"img/jogotela-ponte-away.png"}
	{
	LOG_METHOD_START("StateStage::StateStage");
	LoadAssets();
	LOG_METHOD_CLOSE("StateStage::StateStage","constructor");
}

//! A destructor.
    /*!
      This is a destructor method of StateStage class
    */
StateStage::~StateStage() {
	LOG_METHOD_START("StateStage::~StateStage");
	LOG_METHOD_CLOSE("StateStage::~StateStage","destructor");
}

/*!
	@fn void StateStage::Begin()
	@brief Virtual method that represents the Begin stage state
	@return The execution of this method returns no value
*/
void StateStage::Begin() {
	LOG_METHOD_START("StateStage::Begin");
	//! Loads the level and the player
	level.load_level_from_file(levelName);
	player = GameObject::MakePlayer(Vec2{PLAYER_POSITION_AXIS_X,
																				PLAYER_POSITION_AXIS_Y});
	AddObject(player);
	Camera::follow(player);
	level.load_level_objects();
	LOG_METHOD_CLOSE("StateStage::Begin","void");
}

/*!
	@fn void StateStage::update(float time)
	@brief Virtual method that updates the stage state
	@param time
	@brief a positive float, the represents the game time
	@return The execution of this method returns no value
*/
void StateStage::update(float time) {
	LOG_METHOD_START("StateStage::update");
	LOG_VARIABLE("time",time);
	Camera::update_camera(time);
	//! Checks if the player requested to quit
	if (INPUT.get_quit_requested()){
		quit_requested = true;
	}
	else{
		// do nothing
	}

	//! Checks if the player pressed the key 'ESC'
	if (INPUT.key_pressed(KEY_ESC)){
		popRequested=true;
	}
	else{
		// do nothing
	}

	//! @var pos
	//!< A Vec2, that represents the player position
	Vec2 pos = GO(PLAYER_UID)->pos;

	//! Checks if the player pressed the key 'u'
	if (INPUT.key_pressed(KEY(u))){
		AddObject(GameObject::MakePorco(pos+Vec2{BOAR_POSITION_AXIS_X,
																							BOAR_POSITION_AXIS_Y}));
	}
	else{
		// do nothing
	}

	//! Checks if the player pressed the key 'p'
	if (INPUT.key_pressed(KEY(p))){
		AddObject(GameObject::MakeMike(pos+Vec2{MIKE_POSITION_AXIS_X,
																						MIKE_POSITION_AXIS_Y}));
	}
	else{
		// do nothing
	}

	//! Checks if the player pressed the key 'o'
	if (INPUT.key_pressed(KEY(o))){
		AddObject(GameObject::MakeBanshee(pos+Vec2{BANSHEE_START_POSITION_AXIS_x,
																								BANSHEE_START_POSITION_AXIS_Y},
																			pos+Vec2{BANSHEE_END_POSITION_AXIS_x,
																								BANSHEE_END_POSITION_AXIS_Y}));
	}
	else{
		// do nothing
	}

	//! Checks if the player pressed the key 'i'
	if (INPUT.key_pressed(KEY(i))){
		AddObject(GameObject::MakeMask(pos+Vec2{MASK_POSITION_AXIS_X,
																						MASK_POSITION_AXIS_Y}));
	}
	else{
		// do nothing
	}

	//! Checks if the player pressed the key 'y'
	if (INPUT.key_pressed(KEY(y))){
		GO(player)->dead=true;
	}
	else{
		// do nothing
	}

	//! Checks if the player pressed the key 'n'
	if (INPUT.key_pressed(KEY(n))){
		SETTINGS.showHP = !SETTINGS.showHP;
	}
	else{
		// do nothing
	}

	//! Checks if the player pressed the key 'm'
	if (INPUT.key_pressed(KEY(m))){
		 SETTINGS.showCollision = !SETTINGS.showCollision;
	}
	else{
		// do nothing
	}

	UpdateArray(time);

	LOG_METHOD_CLOSE("StateStage::update","void");
}



/*!
	@fn void StateStage::render()
	@brief Virtual method that renders the stage background
	@return The execution of this method returns no value
*/

void StateStage::render() {
	LOG_METHOD_START("StateStage::render");
	level.background_sprite.render(0, 0);
	// floresta_bg1.render(RENDERPOS(Vec2(0,0)));
	// floresta_bg2.render(RENDERPOS(Vec2(4433,0)));
	// floresta_bg3.render(RENDERPOS(Vec2(8465,0)));
	florest_bg2.render(RENDERPOS(Vec2(0,0)));
	florest_bg2.render(RENDERPOS(Vec2(FLOREST_BACKGROUND_SIZE*1,0)));
	florest_bg2.render(RENDERPOS(Vec2(FLOREST_BACKGROUND_SIZE*2,0)));
	florest_bg2.render(RENDERPOS(Vec2(FLOREST_BACKGROUND_SIZE*3,0)));
	florest_bg2.render(RENDERPOS(Vec2(FLOREST_BACKGROUND_SIZE*4,0)));
	florest_bg2.render(RENDERPOS(Vec2(FLOREST_BACKGROUND_SIZE*5,0)));
	florest_bg3.render(RENDERPOS(Vec2(FLOREST_BACKGROUND_SIZE*6,0)));
	level.level_tile_map.render();
	RenderArray();
	LOG_METHOD_CLOSE("StateStage::render","void");
}

/*!
	@fn void StateStage::Pause()
	@brief Virtual method that represents the Pause stage state
	@return The execution of this method returns no value
*/
void StateStage::Pause() {
	LOG_METHOD_START("StateStage::Pause");
	Camera::unfollow();
	LOG_METHOD_CLOSE("StateStage::Pause","void");
}

/*!
	@fn void StateStage::Pause()
	@brief Virtual method that represents the Resume stage state
	@return The execution of this method returns no value
*/
void StateStage::Resume() {
	LOG_METHOD_START("StateStage::Resume");
	Camera::follow(PLAYER_UID);
	LOG_METHOD_CLOSE("StateStage::Resume","void");
}

/*!
	@fn void StateStage::LoadAssets()
	@brief Virtual method that loads teh stage images
	@return The execution of this method returns no value
*/
void StateStage::LoadAssets() {
	LOG_METHOD_START("StateStage::LoadAssets");
	Resources::game_get_image("img/porco/porco-chifrada.png");
	Resources::game_get_image("img/porco/porco-correndo.png");
	Resources::game_get_image("img/porco/porco-idle.png");
	Resources::game_get_image("img/porco/porco-morte.png");
	Resources::game_get_image("img/porco/porco-stun.png");
	Resources::game_get_image("img/porco/porco-virando.png");
	Resources::game_get_image("img/porco/porco-chifrada-virado.png");
	Resources::game_get_image("img/porco/porco-correndo-virado.png");
	Resources::game_get_image("img/porco/porco-idle-virado.png");
	Resources::game_get_image("img/porco/porco-morte-virado.png");
	Resources::game_get_image("img/porco/porco-stun-virado.png");
	Resources::game_get_image("img/porco/porco-virando-virado.png");
	Resources::game_get_image("img/porco/rage/porco-chifrada.png");
	Resources::game_get_image("img/porco/rage/porco-correndo.png");
	Resources::game_get_image("img/porco/rage/porco-idle.png");
	Resources::game_get_image("img/porco/rage/porco-morte.png");
	Resources::game_get_image("img/porco/rage/porco-stun.png");
	Resources::game_get_image("img/porco/rage/porco-virando.png");
	Resources::game_get_image("img/porco/rage/porco-chifrada-virado.png");
	Resources::game_get_image("img/porco/rage/porco-correndo-virado.png");
	Resources::game_get_image("img/porco/rage/porco-idle-virado.png");
	Resources::game_get_image("img/porco/rage/porco-morte-virado.png");
	Resources::game_get_image("img/porco/rage/porco-stun-virado.png");
	Resources::game_get_image("img/porco/rage/porco-virando-virado.png");
	LOG_METHOD_CLOSE("StateStage::LoadAssets","void");
}

/*!
	@fn void StateStage::LoadGUI()
	@brief Virtual method that loads GUI
	@return The execution of this method returns no value
*/
void StateStage::LoadGUI() {
	LOG_METHOD_START("StateStage::LoadGUI");
	LOG_METHOD_CLOSE("StateStage::LoadGUI","void");
}
