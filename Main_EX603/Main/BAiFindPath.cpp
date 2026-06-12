#include "StdAfx.h"
#include "BAiFindPath.h"
#include <iostream>
#include <queue>
#include <vector>

BAiFindPath gBAiFindPath;

BAiFindPath::BAiFindPath()
{
}


BAiFindPath::~BAiFindPath()
{
	BAiFindPath::Clear();
}
void BAiFindPath::Clear()
{
	BAiFindPath::pathTimDuongDi.clear();
	BAiFindPath::ViTriCanDenX = -1;
	BAiFindPath::ViTriCanDenY = -1;
}
const int ROW = 255;
const int COL = 255;

bool isValid(int x, int y) {
	return (x >= 0 && x < ROW && y >= 0 && y < COL);
}


bool isObstacle(int x, int y)
{
	WORD* TerrainWall = (WORD*)0x82C6AA0;
	int iTerrainIndex = ((int(__cdecl*)(int x, int y)) 0x005D66F0)(x, y);
	if (!(TerrainWall[iTerrainIndex] & (0x0004)))
	{
		return 0;
	}
	return 1;
}
double BAiFindPath::BBdistance(int x, int y, int x2, int y2)
{
	double dx = x - x2;
	double dy = y - y2;
	return std::sqrt(dx * dx + dy * dy);
}

vector<BAIPoint> findPath(BAIPoint start, BAIPoint end)
{

	queue<BAIPoint> q;
	bool visited[ROW][COL] = { false };

	vector<BAIPoint> path;


	BAIPoint prev[ROW][COL];


	visited[start.x][start.y] = true;
	q.push(start);


	while (!q.empty()) {

		BAIPoint current = q.front();
		q.pop();


		if (current.x == end.x && current.y == end.y) {

			BAIPoint p = end;
			while (p.x != start.x || p.y != start.y) {
				path.push_back(p);
				p = prev[p.x][p.y];
			}
			path.push_back(start);
			reverse(path.begin(), path.end());
			return path;
		}
		int dx[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
		int dy[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
		for (int i = 0; i < 8; i++) {
			int nextX = current.x + dx[i];
			int nextY = current.y + dy[i];
			BAIPoint pB(nextX, nextY);

			if (nextX >= 0 && nextX < ROW && nextY >= 0 && nextY < COL && visited[nextX][nextY] == false && !isObstacle(nextX, nextY))
			{
				visited[nextX][nextY] = true;
				prev[nextX][nextY] = current;
				q.push(BAIPoint(nextX, nextY));
			}
		}
	}

	return path;
}
#include "User.h"
#include "MiniMap.h"
#include "Import.h"
// Example usage
bool BAiFindPath::TimDuongDi(int x, int y, int xx, int yy)
{
	//g_Console.AddMessage(1, "TimDuongDi (%d/%d) -> (%d/%d)", x, y, xx, yy);
	BAiFindPath::pathTimDuongDi.clear();
	BAIPoint start(x, y);
	BAIPoint end(xx, yy);
	vector<BAIPoint> path = findPath(start, end);
	int mX = 0;
	int mY = 0;
	double phamvi = 0;
	double Aphamvi = BAiFindPath::BBdistance(x, y, xx, yy);
	if (path.empty())
	{
		

		goto Exit;
	}
	if (BAiFindPath::BBdistance(x, y, path[path.size() - 1].x, path[path.size() - 1].y) > 7)
	{
		for (int n = 0; n < path.size(); n++)
		{
			if (mX != 0 && mY != 0 && Aphamvi > 7)
			{
				phamvi = BAiFindPath::BBdistance(mX, mY, path[n].x, path[n].y);
				if (phamvi < 7) continue;
			}

			mX = path[n].x;
			mY = path[n].y;

			BAiFindPath::pathTimDuongDi.push_back(path[n]);
		}
	}
	else
	{
		BAiFindPath::pathTimDuongDi.push_back(BAIPoint(x, y));
		BAiFindPath::pathTimDuongDi.push_back(BAIPoint(xx, yy));
	}
	if (BAiFindPath::pathTimDuongDi.size() > 1)
	{
		BAiFindPath::ViTriCanDenX = xx;
		BAiFindPath::ViTriCanDenY = yy;
		//POINT BCoord;
		//BCoord.x = gBAiFindPath.pathTimDuongDi[1].x;
		//BCoord.y = gBAiFindPath.pathTimDuongDi[1].y;
		//SendCoord = BCoord;
		//MoveCoordSend(BCoord.x, BCoord.y);
		//====Debug===//
		*(DWORD*)0x81C038C = (float)(gBAiFindPath.pathTimDuongDi[1].x);
		*(DWORD*)0x81C0388 = (float)(gBAiFindPath.pathTimDuongDi[1].y);
		gObjUser.MoveToX = *(DWORD*)0x81C038C;
		gObjUser.MoveToY = *(DWORD*)0x81C0388;
		gObjUser.IsSendMove = 5;
		gObjUser.AutoMoveCheckMap = pMapNumber;
		gRenderMap.CGAutoMove(1);
		return 1;
	}
Exit:
	BAiFindPath::Clear();
	return 0;
}