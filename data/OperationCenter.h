#ifndef OPERATIONCENTER_H_INCLUDED
#define OPERATIONCENTER_H_INCLUDED

/**
 * @brief Class that defines functions for all object operations.
 * @details Object self-update, draw, and object-to-object interact functions are defined here.
 */
class OperationCenter
{
public:
	static OperationCenter *get_instance() {
		static OperationCenter OC;
		return &OC;
	}
	/**
	 * @brief Highest level update function.
	 * @details Calls all other update functions.
	 */
	void update();
	/**
	 * @brief Highest level draw function.
	 * @details Calls all other draw functions.
	 */
	void draw();
private:
	OperationCenter() {}
private:
	void _update_rem();
	void _update_watermelon();
	void _update_banana();
	void _update_fruit();
	void _update_wall();
	void _update_wall2();
	void _update_monster();
	void _update_enemy();
	void _update_tower();
	void _update_towerBullet();
	void _update_monster_towerBullet();
	void _update_monster_player();
	//void _update_fruit_character();
private:
	void _draw_rem();
	void _draw_watermelon();
	void _draw_banana();
	void _draw_fruit();
	void _draw_wall();
	void _draw_wall2();
	void _draw_monster();
	void _draw_enemy();
	void _draw_tower();
	void _draw_towerBullet();
};

#endif
