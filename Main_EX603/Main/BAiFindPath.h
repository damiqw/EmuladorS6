#pragma once
#include "stdafx.h"
using namespace std;

struct BAIPoint {
	int x, y;
	BAIPoint(int _x, int _y) : x(_x), y(_y) {}
	BAIPoint() : x(0), y(0) {}
};




class BAiFindPath
{
public:
	BAiFindPath();
	virtual ~BAiFindPath();
	bool TimDuongDi(int x, int y, int xx, int yy);
	int ViTriCanDenX;
	int ViTriCanDenY;
	std::vector<BAIPoint> pathTimDuongDi;
	double BBdistance(int x, int y, int x2, int y2);
	void BAiFindPath::Clear();

};

extern BAiFindPath gBAiFindPath;