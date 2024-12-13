#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "../Object.h"
#include "../shapes/Point.h"
#include "../shapes/Rectangle.h"
#include <vector>
#include <queue>

enum class Dir;

// fixed settings
enum class EnemyType {
	GHOST, ENEMYTYPE_MAX
};

class Enemy : public Object
{
public:
	static Enemy *create_enemy(EnemyType type, Point p);
public:
	Enemy(EnemyType type, Point p);
	void update();
	void draw();
	void change_direction();
	void fix_position(Point &current_position);
protected:
	int speed;
	const char *path;
private:
	EnemyType type;
	Dir dir;
	double rotation_angle;
};

#endif
