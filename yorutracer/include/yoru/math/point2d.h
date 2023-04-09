#ifndef POINT2D_H
#define POINT2D_H

class Point2d
{
public:
	Point2d();
	Point2d(int x, int y);
	~Point2d();

	int getX() const;
	int getY() const;

private:
	int x, y;
};

#endif
