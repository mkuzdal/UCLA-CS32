/** @file: Actor.h */

#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "StudentWorld.h"
#include "GameWorld.h"
#include "GameController.h"

/////////////////////////////////////////////////////////////////
//  ACTOR:
/////////////////////////////////////////////////////////////////

class Actor : public GraphObject
{
public:
    Actor(int ID, int x, int y, Direction dir, float size, unsigned int depth, bool isVisible, StudentWorld* world)
    : GraphObject(ID, x, y, dir, size, depth),
    m_isAlive(true), m_world(world) { setVisible(isVisible); }
    
    virtual void doSomething() = 0;
    
    bool isAlive() const                        {   return m_isAlive;           }
    StudentWorld* getWorld() const              {   return m_world;             }
    void setDead()                              {   m_isAlive = false;          }
    
private:
    bool m_isAlive;
    StudentWorld* m_world;
}; // end Actor

/////////////////////////////////////////////////////////////////
//  AGENT:
/////////////////////////////////////////////////////////////////

class Agent : public Actor
{
public:
    Agent(int ID, int x, int y, Direction dir, float size, unsigned int depth, int hp, StudentWorld* world)
    : Actor(ID, x, y, dir, 1.0, 0, true, world),
    m_hitpoints(hp) {}
    
    virtual void getAnnoyed(int n) = 0;
    
    int HP() const                              {   return m_hitpoints; }
    void loseHP(int n)                          {   m_hitpoints-=n;     }
    
private:
    int m_hitpoints;
}; // end Agent

/////////////////////////////////////////////////////////////////
//  GOODIE:
/////////////////////////////////////////////////////////////////

class Goodie : public Actor
{
public:
    Goodie(int ID, int x, int y, bool isTemporary, bool isVisible, bool isProtester, bool isFrackMan, StudentWorld* world)
    : Actor(ID, x, y, right, 1.0, 2, isVisible, world),
    m_isTemporary(isTemporary), m_initialTick(getWorld()->Tick()),
    m_isProtester(isProtester), m_isFrackMan(isFrackMan) {}
    
    void doSomething();
    
    void setLifeTime(int n)                     {   m_lifeTime = n;         }
    
private:
    bool m_isTemporary;
    int m_initialTick;
    bool m_isProtester;
    bool m_isFrackMan;
    int m_lifeTime;
}; // end Goodie

/////////////////////////////////////////////////////////////////
//  FRACKMAN:
/////////////////////////////////////////////////////////////////

class FrackMan : public Agent
{
public:
    FrackMan(StudentWorld* world)
    : Agent(IID_PLAYER, 30, 60, right, 1.0, 0, 10, world),
    m_nuggetCount(0), m_sonarCount(1), m_waterCount(5) {}
    
    virtual void doSomething();
    virtual void getAnnoyed(int n);
    
    int getNugget() const               {   return m_nuggetCount;   }
    int getSonar() const                {   return m_sonarCount;    }
    int getWater() const                {   return m_waterCount;    }
    void gotNugget()                    {   m_nuggetCount++;        }
    void gotSonar()                     {   m_sonarCount++;         }
    void gotWater()                     {   m_waterCount+=5;        }
    
private:
    int m_nuggetCount;
    int m_sonarCount;
    int m_waterCount;
}; // end FrackMan

/////////////////////////////////////////////////////////////////
//  PROTESTERS:
/////////////////////////////////////////////////////////////////

class Protester : public Agent
{
public:
    Protester(int ID, int hp, StudentWorld* world)
    : Agent(ID, 60, 60, left, 1.0, 0, hp, world), m_willLeave(false),
    m_numMoves(getWorld()->randInt(8, 60)),
    m_waitTime(getWorld()->max(0, 3 - getWorld()->getLevel()/4)),
    m_defaultWaitTime(m_waitTime),
    m_lastAction(getWorld()->Tick()),
    m_lastShout(-999), m_lastPerp(-999) {}
    
    virtual void doSomething();
    virtual void getAnnoyed(int n) = 0;
    virtual void gotNugget() = 0;
    virtual void chaseFrackMan() = 0;
    
    bool willLeave() const              {   return m_willLeave;         }
    int numMoves() const                {   return m_numMoves;          }
    int waitTime() const                {   return m_waitTime;          }
    int defaultWaitTime() const         {   return m_defaultWaitTime;   }
    int lastAction() const              {   return m_lastAction;        }
    int lastShout() const               {   return m_lastShout;         }
    int lastPerp() const                {   return m_lastPerp;          }
    void setWillLeave(bool b)           {   m_willLeave = b;            }
    void setNumMoves(int n)             {   m_numMoves = n;             }
    void setWaitTime(int n)             {   m_waitTime = n;             }
    void setLastAction(int n)           {   m_lastAction = n;           }
    void setLastShout(int n)            {   m_lastShout = n;            }
    void setLastPerp(int n)             {   m_lastPerp = n;             }
    
private:
    bool m_willLeave;
    int m_numMoves;
    int m_waitTime;
    int m_defaultWaitTime;
    int m_lastAction;
    int m_lastShout;
    int m_lastPerp;
}; // end Protester

class RegularProtester : public Protester
{
public:
    RegularProtester(int ID, StudentWorld* world)
    : Protester(ID, 5, world) {}
    
    virtual void getAnnoyed(int n);
    virtual void gotNugget();
    virtual void chaseFrackMan();
    
private:
}; // end RegularProtester

class HardcoreProtester : public Protester
{
public:
    HardcoreProtester(int ID, StudentWorld* world)
    : Protester(ID, 20, world) {}
    
    virtual void getAnnoyed(int n);
    virtual void gotNugget();
    virtual void chaseFrackMan();
    
private:
}; // end HardcoreProtester

/////////////////////////////////////////////////////////////////
//  ACTOR OBJECTS:
/////////////////////////////////////////////////////////////////

class Dirt : public Actor
{
public:
    Dirt(int x, int y, StudentWorld* world)
    : Actor(IID_DIRT, x, y, right, 0.25, 3, true, world) {}
    
    virtual void doSomething();
    
private:
}; // end Dirt

class Boulder : public Actor
{
public:
    Boulder(int x, int y, StudentWorld* world)
    : Actor(IID_BOULDER, x, y, down, 1.0, 1, true, world),
    m_isStable(true), m_isFalling(false), m_transitionTick(0) {}
    
    virtual void doSomething();
    
private:
    bool m_isStable;
    bool m_isFalling;
    int m_transitionTick;
}; // end Boulder

class Squirt : public Actor
{
public:
    Squirt(int x, int y, Direction dir, StudentWorld* world)
    : Actor(IID_WATER_SPURT, x, y, dir, 1.0, 1, true, world),
    m_travelDistance(4) {}
    
    virtual void doSomething();
    
private:
    int m_travelDistance;
}; // end Squirt

/////////////////////////////////////////////////////////////////
//  GOODIES:
/////////////////////////////////////////////////////////////////

class BarrelOfOil : public Goodie
{
public:
    BarrelOfOil(int x, int y, StudentWorld* world)
    : Goodie(IID_BARREL, x, y, false, false, false, true, world)
    { setLifeTime(-1); }
    
private:
}; // end BarrelOfOil

class GoldNugget : public Goodie
{
public:
    GoldNugget(int x, int y, bool isTemporary, bool isVisible, StudentWorld* world)
    : Goodie(IID_GOLD, x, y, isTemporary, isVisible, isTemporary, !isTemporary, world)
    { setLifeTime(100); }
    
private:
}; // end GoldNugget

class SonarKit : public Goodie
{
public:
    SonarKit(int x, int y, StudentWorld* world)
    : Goodie(IID_SONAR, x, y, true, true, false, true, world)
    { setLifeTime(getWorld()->max(100, 300 - 10*getWorld()->getLevel())); }

private:
}; // end SonarKit

class WaterPool : public Goodie
{
public:
    WaterPool(int x, int y, StudentWorld* world)
    : Goodie(IID_WATER_POOL, x, y, true, true, false, true, world)
    { setLifeTime(getWorld()->max(100, 300 - 10*getWorld()->getLevel())); }

private:
}; // end WaterPool


#endif // ACTOR_H_
