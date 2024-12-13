#ifndef ENEMYGHOST_H_INCLUDED
#define ENEMYGHOST_H_INCLUDED

#include "Enemy.h"

// fixed settings: MonsterCaveMan attributes
class EnemyGhost : public Enemy
{
public:
	EnemyGhost(Point p) : Enemy{EnemyType::GHOST, p} {
		speed = 2;
		path = "./assets/image/enemy/Ghost/UP_0.png";
	}
};

#endif
