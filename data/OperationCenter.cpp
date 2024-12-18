#include "OperationCenter.h"
#include "DataCenter.h"
#include "../monsters/Monster.h"
#include "../enemies/Enemy.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
#include "../Player.h"
#include "../Character.h"
#include "../Rem.h"
#include "../Fruit.h"
#include "../Watermelon.h"
#include "../Banana.h"
#include "../Wall.h"
#include "../Wall2.h"
#include <iostream>
using namespace std;
void OperationCenter::update() {
	// Update watermelons.
	_update_watermelon();
	cout<<"_update_watermelon();"<<endl;
	// Update bananas.
	_update_rem();
	cout<<"_update_rem();"<<endl;
	// Update bananas.
	_update_banana();
	cout<<"_update_banana();"<<endl;
	// Update fruits.
	_update_fruit();
	cout<<"_update_fruit();"<<endl;
	// Update walls.
	_update_wall();
	cout<<"_update_wall();"<<endl;
	// Update walls.
	_update_wall2();
	cout<<"_update_wall2();"<<endl;
	// Update monsters.
	_update_monster();
	cout<<"_update_enemy();"<<endl;
	// Update enemies.
	_update_enemy();
	cout<<"_update_enemy();"<<endl;
	// Update towers.
	_update_tower();
	cout<<"_update_tower();"<<endl;
	// Update tower bullets.
	_update_towerBullet();
	cout<<"_update_towerBullet();"<<endl;
	// If any bullet overlaps with any monster, we delete the bullet, reduce the HP of the monster, and delete the monster if necessary.
	_update_monster_towerBullet();
	cout<<"_update_monster_towerBullet();"<<endl;
	// If any monster reaches the end, hurt the player and delete the monster.
	_update_monster_player();
	cout<<"_update_monster_player();"<<endl;
	//_update_fruit_character();
	//cout<<"_update_fruit_character();"<<endl;
}

void OperationCenter::_update_rem() {
	auto r = DataCenter::get_instance()->rem;
	r->update();
} 

void OperationCenter::_update_watermelon() {
	std::vector<Watermelon*> &watermelons = DataCenter::get_instance()->watermelons;
	for(Watermelon *watermelon : watermelons)
		watermelon->update();
} 

void OperationCenter::_update_banana() {
	std::vector<Banana*> &bananas = DataCenter::get_instance()->bananas;
	for(Banana *banana : bananas)
		banana->update();
} 

void OperationCenter::_update_fruit() {
	std::vector<Fruit*> &fruits = DataCenter::get_instance()->fruits;
	for(Fruit *fruit : fruits)
		fruit->update();
}

void OperationCenter::_update_wall() {
	std::vector<Wall*> &walls = DataCenter::get_instance()->walls;
	for(Wall *wall : walls)
		wall->update();
}

void OperationCenter::_update_wall2() {
	std::vector<Wall2*> &walls2 = DataCenter::get_instance()->walls2;
	for(Wall2 *wall2 : walls2)
		wall2->update();
}

void OperationCenter::_update_monster() {
	std::vector<Monster*> &monsters = DataCenter::get_instance()->monsters;
	for(Monster *monster : monsters)
		monster->update();
}

void OperationCenter::_update_enemy() {
	std::vector<Enemy*> &enemies = DataCenter::get_instance()->enemies;
	for(Enemy *enemy : enemies)
		enemy->update();
}

void OperationCenter::_update_tower() {
	std::vector<Tower*> &towers = DataCenter::get_instance()->towers;
	for(Tower *tower : towers)
		tower->update();
}

void OperationCenter::_update_towerBullet() {
	std::vector<Bullet*> &towerBullets = DataCenter::get_instance()->towerBullets;
	for(Bullet *towerBullet : towerBullets)
		towerBullet->update();
	// Detect if a bullet flies too far (exceeds its fly distance limit), which means the bullet lifecycle has ended.
	for(size_t i = 0; i < towerBullets.size(); ++i) {
		if(towerBullets[i]->get_fly_dist() <= 0) {
			towerBullets.erase(towerBullets.begin()+i);
			--i;
		}
	}
}

void OperationCenter::_update_monster_towerBullet() {
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Monster*> &monsters = DC->monsters;
	std::vector<Bullet*> &towerBullets = DC->towerBullets;
	for(size_t i = 0; i < monsters.size(); ++i) {
		for(size_t j = 0; j < towerBullets.size(); ++j) {
			// Check if the bullet overlaps with the monster.
			if(monsters[i]->shape->overlap(*(towerBullets[j]->shape))) {
				// Reduce the HP of the monster. Delete the bullet.
				monsters[i]->HP -= towerBullets[j]->get_dmg();
				towerBullets.erase(towerBullets.begin()+j);
				--j;
			}
		}
	}
}



void OperationCenter::_update_monster_player() {
	DataCenter *DC = DataCenter::get_instance();
	std::vector<Monster*> &monsters = DC->monsters;
	Player *&player = DC->player;
	for(size_t i = 0; i < monsters.size(); ++i) {
		// Check if the monster is killed.
		if(monsters[i]->HP <= 0) {
			// Monster gets killed. Player receives money.
			player->coin += monsters[i]->get_money();
			monsters.erase(monsters.begin()+i);
			--i;
			// Since the current monsster is killed, we can directly proceed to next monster.
			break;
		}
		// Check if the monster reaches the end.
		if(monsters[i]->get_path().empty()) {
			monsters.erase(monsters.begin()+i);
			player->HP--;
			--i;
		}
	}
}

void OperationCenter::draw() {
	_draw_rem();
	_draw_watermelon();
	_draw_banana();
	_draw_fruit();
	_draw_wall();
	_draw_wall2();
	_draw_monster();
	_draw_enemy();
	_draw_tower();
	_draw_towerBullet();
}

void OperationCenter::_draw_rem() {
	auto r = DataCenter::get_instance()->rem;
	r->draw();
} 

void OperationCenter::_draw_watermelon() {
	std::vector<Watermelon*> &watermelons = DataCenter::get_instance()->watermelons;
	for(Watermelon *watermelon : watermelons)
		watermelon->draw();
}

void OperationCenter::_draw_banana() {
	std::vector<Banana*> &bananas = DataCenter::get_instance()->bananas;
	for(Banana *banana : bananas)
		banana->draw();
}

void OperationCenter::_draw_fruit() {
	std::vector<Fruit*> &fruits = DataCenter::get_instance()->fruits;
	for(Fruit *fruit : fruits)
		fruit->draw();
}

void OperationCenter::_draw_wall() {
	std::vector<Wall*> &walls = DataCenter::get_instance()->walls;
	for(Wall *wall : walls)
		wall->draw();
}

void OperationCenter::_draw_wall2() {
	std::vector<Wall2*> &walls2 = DataCenter::get_instance()->walls2;
	for(Wall2 *wall2 : walls2)
		wall2->draw();
}

void OperationCenter::_draw_monster() {
	std::vector<Monster*> &monsters = DataCenter::get_instance()->monsters;
	for(Monster *monster : monsters)
		monster->draw();
}

void OperationCenter::_draw_enemy() {
	std::vector<Enemy*> &enemies = DataCenter::get_instance()->enemies;
	for(Enemy *enemy : enemies)
		enemy->draw();
}

void OperationCenter::_draw_tower() {
	std::vector<Tower*> &towers = DataCenter::get_instance()->towers;
	for(Tower *tower : towers)
		tower->draw();
}

void OperationCenter::_draw_towerBullet() {
	std::vector<Bullet*> &towerBullets = DataCenter::get_instance()->towerBullets;
	for(Bullet *towerBullet : towerBullets)
		towerBullet->draw();
}

