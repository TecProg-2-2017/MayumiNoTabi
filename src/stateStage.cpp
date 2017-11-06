#include <stateStage.hpp>

#include <common.hpp>

#include <camera.hpp>
#include <resources.hpp>
#include <music.hpp>
#include <game.hpp>
#include <gameObject.hpp>
#include <complib.hpp>
StateStage::StateStage(string lvl):levelName{lvl},
	// floresta_bg1{"img/jogotela-campo-1-away.png"},
	floresta_bg2{"img/floresta-away.png"},
	floresta_bg3{"img/jogotela-ponte-away.png"}
	{
	LoadAssets();
}

StateStage::~StateStage() {}

void StateStage::Begin() {
	level.load_level_from_file(levelName);
	player = GameObject::MakePlayer(Vec2{550.0f,430.0f});
	AddObject(player);
	Camera::Follow(player);
	level.load_level_objects();
}

void StateStage::Update(float time) {
	Camera::update(time);
	if (INPUT.get_quit_requested())quit_requested=true;
	if (INPUT.key_pressed(KEY_ESC))popRequested=true;
	
	Vec2 pos = GO(PLAYER_UID)->pos;
	if (INPUT.key_pressed(KEY(u))) AddObject(GameObject::makeBoar(pos+Vec2{2000.0f,-100.0f}));
	if (INPUT.key_pressed(KEY(p))) AddObject(GameObject::MakeMike(pos+Vec2{850.0f,-100.0f}));
	if (INPUT.key_pressed(KEY(o))) AddObject(GameObject::MakeBanshee(pos+Vec2{850.0f,-100.0f},pos+Vec2{230.0f,-200.0f}));
	if (INPUT.key_pressed(KEY(i))) AddObject(GameObject::MakeMask(pos+Vec2{850.0f,-100.0f}));
	if (INPUT.key_pressed(KEY(y))) GO(player)->dead=true;

	if (INPUT.key_pressed(KEY(n))) SETTINGS.showHP = !SETTINGS.showHP;
	if (INPUT.key_pressed(KEY(m))) SETTINGS.showCollision = !SETTINGS.showCollision;

	UpdateArray(time);
}

void StateStage::render() {
	level.background.render(0, 0);
	// floresta_bg1.render(RENDERPOS(Vec2(0,0)));
	// floresta_bg2.render(RENDERPOS(Vec2(4433,0)));
	// floresta_bg3.render(RENDERPOS(Vec2(8465,0)));
	floresta_bg2.render(RENDERPOS(Vec2(0,0)));
	floresta_bg2.render(RENDERPOS(Vec2(4032*1,0)));
	floresta_bg2.render(RENDERPOS(Vec2(4032*2,0)));
	floresta_bg2.render(RENDERPOS(Vec2(4032*3,0)));
	floresta_bg2.render(RENDERPOS(Vec2(4032*4,0)));
	floresta_bg2.render(RENDERPOS(Vec2(4032*5,0)));
	floresta_bg3.render(RENDERPOS(Vec2(4032*6,0)));
	level.level_tile_map.render();
	RenderArray();
}

void StateStage::Pause() {
	Camera::Unfollow();
}
void StateStage::Resume() {
	Camera::Follow(PLAYER_UID);
}

void StateStage::LoadAssets() {
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
}
void StateStage::LoadGUI() {}
