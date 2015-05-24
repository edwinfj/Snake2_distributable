#pragma once

enum BulletType
{
	B_NORMAL_BULLET = 0,
	B_FIRE_BULLET   = 1,
	B_ICE_BULLET    = 2,
	B_NO_BULLET     = 3
};
typedef BulletType BulletBox;

enum Direction
{
	DIR_STAY	   = 0,
	DIR_UP         = 1,
	DIR_DOWN       = 2,
	DIR_LEFT       = 3,
	DIR_RIGHT      = 4
};

enum BodyMorphism
{
	BODY_NORMAL    = 0,
	BODY_FROZEN    = 1,
	BODY_FIRE	   = 2
};

struct Coord
{
	int x;
	int y;
};

typedef Coord Body;
typedef Coord Position;

