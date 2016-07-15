/** @file: StudentWorld.h */

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "GameController.h"
#include <string>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

class Actor;
class Protester;
class FrackMan;
class Dirt;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    int Tick() const;
    int min(int a, int b) const;
    int max(int a, int b) const;
    int randInt(int min, int max) const;
    int numPerpendicular(int x, int y, GraphObject::Direction dir) const;
    bool isFrackManWithin(int x, int y, double r) const;
    bool isBoulderWithin(int x, int y, double r) const;
    bool isBoulderWithin(int x, int y, int x_B, int y_B, double r) const;
    bool isProtesterWithin(int x, int y, double r) const;
    bool hasDirt(int x, int y, GraphObject::Direction dir) const;
    bool isValidPosition(int x, int y, GraphObject::Direction dir) const;
    bool isFacingFrackMan(int x, int y, GraphObject::Direction dir) const;
    bool isFrackManInLOS(int x, int y) const;
    bool isNMovesAway(int x, int y, int N) const;
    GraphObject::Direction getPerpendicular(int x, int y, GraphObject::Direction dir) const;
    GraphObject::Direction getDirectionToExit(int x, int y) const;
    GraphObject::Direction getDirectionToFrackMan(int x, int y) const;
    
    void gotGoodie(int ID);
    void annoyPlayer(int n);
    void clearDirt(int x, int y);
    void dropNugget(int x, int y);
    void shootSquirt(int x, int y, GraphObject::Direction dir);
    void activateRadar(int x, int y, double r);
    void annoyProtesters(int x, int y, double r, int dmg);
    void protesterGotNugget(int x, int y, double r);

private:
    std::vector<Actor*> m_actors;
    std::vector<Protester*> m_protesters;
    Dirt* m_dirtField[VIEW_WIDTH][VIEW_HEIGHT];
    GraphObject::Direction m_frack[VIEW_WIDTH-3][VIEW_HEIGHT-3];
    GraphObject::Direction m_exit[VIEW_WIDTH-3][VIEW_HEIGHT-3];
    FrackMan* m_player;
    int m_oilCount;
    int m_tickCount;
    int m_tickSinceLastProtester;
    
    // Helper Functions:
    double distBetween(int x1, int y1, int x2, int y2) const;
    std::string toStats(int Scr, int Lvl, int Lives, int Hlth, int Water, int Gld, int Sonar, int OilLeft) const;
    bool isActorWithin(int x, int y, double r) const;
    void setPathToExit();
    void setPathToFrackMan();
    void cleanPath();
}; // end StudentWorld

#endif // STUDENTWORLD_H_
