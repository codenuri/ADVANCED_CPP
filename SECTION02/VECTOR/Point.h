// 	핵심 : default 생성자가 없다.

class Point
{
	int x = 0, y = 0;
public:
	//	Point() = default;

	Point(int x, int y) : x(x), y(y) {}
};
