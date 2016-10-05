#include "WallManager.h"

WallManager::WallManager()
{

}

WallManager::~WallManager()
{
	cleanUp();	
}

//this basically sets up the inital walls. A bit sloppy but does the trick
void WallManager::init()
{
	mWallList.push_back(new Wall(0, 0, 50, 768)); //left wall
	mWallList.push_back(new Wall(0, 0, 1024, 50)); //top wall
	mWallList.push_back(new Wall(0, 768, 1024, 718)); //bottom wall
	mWallList.push_back(new Wall(974, 768, 1024, 0)); //right wall
}

void WallManager::update()
{
	for (auto iter : mWallList)
	{
		iter->draw();
	}
}

void WallManager::cleanUp()
{
	for (auto iter : mWallList)
	{
		delete iter;
	}

	mWallList.clear();
}

Wall* WallManager::getWall(int index)
{
	return mWallList[index];
}