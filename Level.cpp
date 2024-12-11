#include "Level.h"
#include <string>
#include "Utils.h"
#include "monsters/Monster.h"
#include "data/DataCenter.h"
#include <allegro5/allegro_primitives.h>
#include "shapes/Point.h"
#include "shapes/Rectangle.h"
#include <array>
#include "Wall2.h"
#include "Wall.h"

using namespace std;

// fixed settings
namespace LevelSetting {
	constexpr char level_path_format[] = "./assets/level/LEVEL%d.txt";
	//! @brief Grid size for each level.
	constexpr array<int, 4> grid_size = {
		40, 40, 40, 40
	};
	constexpr int monster_spawn_rate = 90;
};

void
Level::init() {
	level = -1;
	grid_w = -1;
	grid_h = -1;
	monster_spawn_counter = 0;
}

/**
 * @brief Loads level data from input file. The input file is required to follow the format.
 * @param lvl level index. The path format is a fixed setting in code.
 * @details The content of the input file should be formatted as follows:
 *          * Total number of monsters.
 *          * Number of each different number of monsters. The order and number follows the definition of MonsterType.
 *          * Indefinite number of Point (x, y), represented in grid format.
 * @see level_path_format
 * @see MonsterType
 */
void
Level::load_level(int lvl) {
	DataCenter *DC = DataCenter::get_instance();

	char buffer[50];
	sprintf(buffer, LevelSetting::level_path_format, lvl);
	FILE *f = fopen(buffer, "r");
	GAME_ASSERT(f != nullptr, "cannot find level.");
	level = lvl;
	grid_w = DC->game_field_length / LevelSetting::grid_size[lvl];
	grid_h = DC->game_field_length / LevelSetting::grid_size[lvl];
	num_of_monsters.clear();
	road_path.clear();

	int num;
	// read total number of monsters & number of each monsters
	fscanf(f, "%d", &num);
	for(size_t i = 0; i < static_cast<size_t>(MonsterType::MONSTERTYPE_MAX); ++i) {
		fscanf(f, "%d", &num);
		num_of_monsters.emplace_back(num);
	}

	//read road path
	while(fscanf(f, "%d", &num) != EOF) {
		int w = num % grid_w;
		int h = num / grid_h;
		road_path.emplace_back(w, h);
	}

	// wall
	std::vector<Point> wall_positions = {
        Point(125, 175), Point(125, 275), Point(125, 375), Point(125, 475), Point(125, 575), Point(125, 675),

		Point(275, 125), Point(275, 225), Point(275, 325), Point(275, 425), Point(275, 525), Point(275, 625), 

		Point(675, 175), Point(675, 275), Point(675, 375), Point(675, 475), Point(675, 575), Point(675, 675),

		Point(525, 125), Point(525, 225), Point(525, 325), Point(525, 425), Point(525, 525), Point(525, 625), 

    };

	// wall
	std::vector<Point> wall2_positions = {
        Point(25, 25), Point(25, 75), Point(25, 125), Point(25, 175), Point(25, 225), Point(25, 275), Point(25, 325), Point(25, 375), Point(25, 425), Point(25, 475), Point(25, 525), Point(25, 575), Point(25, 625), Point(25, 675), Point(25, 725), Point(25, 775),
		
		Point(775, 25), Point(775, 75), Point(775, 125), Point(775, 175), Point(775, 225), Point(775, 275), Point(775, 325), Point(775, 375), Point(775, 425), Point(775, 475), Point(775, 525), Point(775, 575), Point(775, 625), Point(775, 675), Point(775, 725), Point(775, 775),

		Point(75, 25), Point(125, 25), Point(175, 25), Point(225, 25), Point(275, 25), Point(325, 25), Point(375, 25), Point(425, 25), Point(475, 25), Point(525, 25), Point(575, 25), Point(625, 25), Point(675, 25), Point(725, 25),

		Point(75, 775), Point(125, 775), Point(175, 775), Point(225, 775), Point(275, 775), Point(325, 775), Point(375, 775), Point(425, 775), Point(475, 775), Point(525, 775), Point(575, 775), Point(625, 775), Point(675, 775), Point(725, 775),

		Point(125, 125), Point(125, 225), Point(125, 325), Point(125, 425), Point(125, 525), Point(125, 625),  

		Point(675, 125), Point(675, 225), Point(675, 325), Point(675, 425), Point(675, 525), Point(675, 625), 

		Point(525, 175), Point(525, 275), Point(525, 375), Point(525, 475), Point(525, 575), Point(525, 675),

		Point(275, 175), Point(275, 275), Point(275, 375), Point(275, 475), Point(275, 575), Point(275, 675),

    };

	for (const Point &pos : wall_positions) {
        Wall *wall = new Wall(pos, "./assets/image/Wall.jpg");
        DC->walls.push_back(wall);
    }

    for (const Point &pos : wall2_positions) {
        Wall2 *wall2 = new Wall2(pos, "./assets/image/Wall2.jpg");
        DC->walls2.push_back(wall2);
    }

	debug_log("<Level> load level %d.\n", lvl);

	
}

/**
 * @brief Updates monster_spawn_counter and create monster if needed.
*/
void
Level::update() {
	if(monster_spawn_counter) {
		monster_spawn_counter--;
		return;
	}
	// DataCenter *DC = DataCenter::get_instance();

	// for(size_t i = 0; i < num_of_monsters.size(); ++i) {
	// 	if(num_of_monsters[i] == 0) continue;
	// 	DC->monsters.emplace_back(Monster::create_monster(static_cast<MonsterType>(i), DC->level->get_road_path()));
	// 	num_of_monsters[i]--;
	// 	break;
	// }
	monster_spawn_counter = LevelSetting::monster_spawn_rate;
}

void
Level::draw() {
	if(level == -1) return;
	for(auto &[i, j] : road_path) {
		int x1 = i * LevelSetting::grid_size[level];
		int y1 = j * LevelSetting::grid_size[level];
		int x2 = x1 + LevelSetting::grid_size[level];
		int y2 = y1 + LevelSetting::grid_size[level];
		//al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(255, 244, 173));
	}
}

bool
Level::is_onroad(const Rectangle &region) {
	for(const Point &grid : road_path) {
		if(grid_to_region(grid).overlap(region))
			return true;
	}
	return false;
}

Rectangle
Level::grid_to_region(const Point &grid) const {
	int x1 = grid.x * LevelSetting::grid_size[level];
	int y1 = grid.y * LevelSetting::grid_size[level];
	int x2 = x1 + LevelSetting::grid_size[level];
	int y2 = y1 + LevelSetting::grid_size[level];
	return Rectangle{x1, y1, x2, y2};
}
