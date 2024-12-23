#include "DataCenter.h"
#include <cstring>
#include "../Level.h"
#include "../Character.h"
#include "../Player.h"
#include "../Fruit.h"
#include "../Watermelon.h"
#include "../Banana.h"
#include "../Wall.h"
#include "../Wall2.h"
#include "../Rem.h"
#include "../monsters/Monster.h"
#include "../enemies/Enemy.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"

// fixed settings
namespace DataSetting {
	constexpr double FPS = 60;
	constexpr int window_width = 1000;
	constexpr int window_height = 800;
	constexpr int game_field_length = 800;
}

DataCenter::DataCenter() {
	this->FPS = DataSetting::FPS;
	this->window_width = DataSetting::window_width;
	this->window_height = DataSetting::window_height;
	this->game_field_length = DataSetting::game_field_length;
	memset(key_state, false, sizeof(key_state));
	memset(prev_key_state, false, sizeof(prev_key_state));
	mouse = Point(0, 0);
	memset(mouse_state, false, sizeof(mouse_state));
	memset(prev_mouse_state, false, sizeof(prev_mouse_state));
	player = new Player();
	level = new Level();
	character = new Character();
	rem = new Rem(Point(70, 400));
}

DataCenter::~DataCenter() {
	delete player;
	delete level;
	delete rem;
	for(Wall *&w : walls){
		delete w;
	}
	for(Wall2 *&w : walls2){
		delete w;
	}
	for(Monster *&m : monsters) {
		delete m;
	}
	for(Enemy *&e : enemies) {
		delete e;
	}
	for(Tower *&t : towers) {
		delete t;
	}
	for(Bullet *&b : towerBullets) {
		delete b;
	}
	for(Fruit *&f : fruits){
		delete f;
	}
	for(Banana *&b : bananas){
		delete b;
	}
	for(Watermelon *&w : watermelons){
		delete w;
	}
}
