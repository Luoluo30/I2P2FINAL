#ifndef ENEMYNEZUKO_H_INCLUDED
#define ENEMYGHOST_H_INCLUDED

#include "Enemy.h"

// fixed settings: MonsterCaveMan attributes
class EnemyNezuko : public Enemy
{
public:
	EnemyNezuko(Point p) : Enemy{EnemyType::NEZUKO, p} {
		speed = 3;
		path = "./assets/image/enemy/Nezuko/UP_0.png";
	}
};

#endif
