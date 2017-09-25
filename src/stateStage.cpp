/*!
*  \file File stateStage.cpp
*  \brief Implementation of the class StateStage
*
*  Auxiliary documentation
*  \sa stateStage.hpp
*/
#include <stateStage.hpp>
#include <common.hpp>
#include <camera.hpp>
#include <resources.hpp>
#include <music.hpp>
#include <game.hpp>
#include <gameObject.hpp>
#include <complib.hpp>

/*!
	@class StateStage
	@brief This class provides the stage states

*/

//! A constructor.
    /*!
    *	This is a constructor method of StateStage
		* \param lvl
		* \brief A string, that represents the name of the current level
		*/
StateStage::StateStage(string lvl):levelName{lvl},
	// floresta_bg1{"img/jogotela-campo-1-away.png"},
	floresta_bg2{"img/floresta-away.png"},
	floresta_bg3{"img/jogotela-ponte-away.png"}
	{
	LoadAssets();
}

//! A destructor.
    /*!
      This is a destructor method of StateStage class
    */
StateStage::~StateStage() {}

/*!
	@fn void StateStage::Begin()
	@brief Virtual method that represents the Begin stage state
	@return The execution of this method returns no value
*/
void StateStage::Begin() {
	//! Loads the level and the player
	level.Load(levelName);
	player = GameObject::MakePlayer(Vec2{550.0f,430.0f});
	AddObject(player);
	Camera::Follow(player);
	level.LoadObjects();
}

/*!
	@fn void StateStage::Update(float time)
	@brief Virtual method that updates the stage state
	@param time
	@brief a positive float, the represents the game time
	@return The execution of this method returns no value
*/
void StateStage::Update(float time) {
	Camera::Update(time);
	//! Checks if the player requested to quit
	if (INPUT.QuitRequested()){
		quitRequested = true;
	}

	//! Checks if the player pressed the key 'ESC'
	if (INPUT.KeyPress(KEY_ESC)){
		popRequested=true;
	}

	//! @var pos
	Vec2 pos = GO(PLAYER_UID)->pos;//!< A Vec2, that represents the player position

	//! Checks if the player pressed the key 'u'
	if (INPUT.KeyPress(KEY(u))){
		AddObject(GameObject::MakePorco(pos+Vec2{2000.0f,-100.0f}));
	}

	//! Checks if the player pressed the key 'p'
	if (INPUT.KeyPress(KEY(p))){
		AddObject(GameObject::MakeMike(pos+Vec2{850.0f,-100.0f}));
	}

	//! Checks if the player pressed the key 'o'
	if (INPUT.KeyPress(KEY(o))){
		AddObject(GameObject::MakeBanshee(pos+Vec2{850.0f,-100.0f},pos+Vec2{230.0f,-200.0f}));
	}

	//! Checks if the player pressed the key 'i'
	if (INPUT.KeyPress(KEY(i))){
		AddObject(GameObject::MakeMask(pos+Vec2{850.0f,-100.0f}));
	}

	//! Checks if the player pressed the key 'y'
	if (INPUT.KeyPress(KEY(y))){
		GO(player)->dead=true;
	}

	//! Checks if the player pressed the key 'n'
	if (INPUT.KeyPress(KEY(n))){
		SETTINGS.showHP = !SETTINGS.showHP;
	}

	//! Checks if the player pressed the key 'm'
	if (INPUT.KeyPress(KEY(m))){
		 SETTINGS.showCollision = !SETTINGS.showCollision;
	}

	UpdateArray(time);
}

/*!
	@fn void StateStage::Render()
	@brief Virtual method that renders the stage background
	@return The execution of this method returns no value
*/
void StateStage::Render() {
	level.background.Render(0, 0);
	// floresta_bg1.Render(RENDERPOS(Vec2(0,0)));
	// floresta_bg2.Render(RENDERPOS(Vec2(4433,0)));
	// floresta_bg3.Render(RENDERPOS(Vec2(8465,0)));
	floresta_bg2.Render(RENDERPOS(Vec2(0,0)));
	floresta_bg2.Render(RENDERPOS(Vec2(4032*1,0)));
	floresta_bg2.Render(RENDERPOS(Vec2(4032*2,0)));
	floresta_bg2.Render(RENDERPOS(Vec2(4032*3,0)));
	floresta_bg2.Render(RENDERPOS(Vec2(4032*4,0)));
	floresta_bg2.Render(RENDERPOS(Vec2(4032*5,0)));
	floresta_bg3.Render(RENDERPOS(Vec2(4032*6,0)));
	level.tileMap.Render();
	RenderArray();
}

/*!
	@fn void StateStage::Pause()
	@brief Virtual method that represents the Pause stage state
	@return The execution of this method returns no value
*/
void StateStage::Pause() {
	Camera::Unfollow();
}

/*!
	@fn void StateStage::Pause()
	@brief Virtual method that represents the Resume stage state
	@return The execution of this method returns no value
*/
void StateStage::Resume() {
	Camera::Follow(PLAYER_UID);
}

/*!
	@fn void StateStage::LoadAssets()
	@brief Virtual method that loads teh stage images
	@return The execution of this method returns no value
*/
void StateStage::LoadAssets() {
	Resources::GetImage("img/porco/porco-chifrada.png");
	Resources::GetImage("img/porco/porco-correndo.png");
	Resources::GetImage("img/porco/porco-idle.png");
	Resources::GetImage("img/porco/porco-morte.png");
	Resources::GetImage("img/porco/porco-stun.png");
	Resources::GetImage("img/porco/porco-virando.png");
	Resources::GetImage("img/porco/porco-chifrada-virado.png");
	Resources::GetImage("img/porco/porco-correndo-virado.png");
	Resources::GetImage("img/porco/porco-idle-virado.png");
	Resources::GetImage("img/porco/porco-morte-virado.png");
	Resources::GetImage("img/porco/porco-stun-virado.png");
	Resources::GetImage("img/porco/porco-virando-virado.png");
	Resources::GetImage("img/porco/rage/porco-chifrada.png");
	Resources::GetImage("img/porco/rage/porco-correndo.png");
	Resources::GetImage("img/porco/rage/porco-idle.png");
	Resources::GetImage("img/porco/rage/porco-morte.png");
	Resources::GetImage("img/porco/rage/porco-stun.png");
	Resources::GetImage("img/porco/rage/porco-virando.png");
	Resources::GetImage("img/porco/rage/porco-chifrada-virado.png");
	Resources::GetImage("img/porco/rage/porco-correndo-virado.png");
	Resources::GetImage("img/porco/rage/porco-idle-virado.png");
	Resources::GetImage("img/porco/rage/porco-morte-virado.png");
	Resources::GetImage("img/porco/rage/porco-stun-virado.png");
	Resources::GetImage("img/porco/rage/porco-virando-virado.png");
}

/*!
	@fn void StateStage::LoadGUI()
	@brief Virtual method that loads GUI
	@return The execution of this method returns no value
*/
void StateStage::LoadGUI() {}
