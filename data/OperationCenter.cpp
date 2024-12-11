#include "OperationCenter.h"
#include "DataCenter.h"
#include "../monsters/Monster.h"
#include "../towers/Tower.h"
#include "../towers/Bullet.h"
#include "../Player.h"
#include "../Character.h"
#include "../Fruit.h"
#include "../Wall.h"
#include "../Wall2.h"
#include <iostream>
using namespace std;
void OperationCenter::update() {
	// Update walls.
	_update_wall();
	cout<<"_update_wall();"<<endl;
	// Update walls.
	_update_wall2();
	cout<<"_update_wall2();"<<endl;
	// Update monsters.
	_update_monster();
	cout<<"_update_monster();"<<endl;
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
	_update_fruit_character();
	cout<<"_update_fruit_character();"<<endl;
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
void OperationCenter::_update_fruit_character() {
    DataCenter *DC = DataCenter::get_instance();
    Player *&player = DC->player;
    std::unique_ptr<Fruit>& fruit = DC->fruit; // No need for a reference to raw pointer
	cout<<"before if"<<endl;
	if (!fruit) {
    cout << "Fruit is nullptr, skipping update." << endl;
    return;
	}
    if (fruit->shape->overlap(*(DC->character->shape))) {
		cout<<"overlap"<<endl;
        player->coin += 50;
		player->fruit+= 1;
		cout<<"player->coin += 50;"<<endl;
		std::cout << "Fruit deleted!" << std::endl;

		fruit = nullptr; // 防止后续对已删除对象的访问
		std::cout << "fruit = nullptr;" << std::endl;
		cout<<"overlap finished"<<endl;
    }
}

void OperationCenter::draw() {
	_draw_wall();
	_draw_wall2();
	_draw_monster();
	_draw_tower();
	_draw_towerBullet();
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
