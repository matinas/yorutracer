#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d
{
public:
	Vector2d();
	Vector2d(float x, float y);
	~Vector2d();

	float getX();
	float getY();

private:
	float x, y;
};

#endif
