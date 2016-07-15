/** @file: StudentWorld.cpp */

#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "GameWorld.h"
#include <string>
#include <vector>
#include <queue>

GameWorld* createStudentWorld(std::string assetDir)
{
	return new StudentWorld(assetDir);
} // end createStudentWorld

StudentWorld::StudentWorld(std::string assetDir)
: GameWorld(assetDir), m_tickCount(0), m_tickSinceLastProtester(1), m_oilCount(0)
{
    // set the player to null
    m_player = nullptr;
    
    // fill the array of dirt with nullptrs
    for (int i = 0; i < VIEW_HEIGHT; i++)
         for (int j = 0; j < VIEW_WIDTH; j++)
             m_dirtField[i][j] = nullptr;
    
} // end constructor

StudentWorld::~StudentWorld()
{
    // delete the player
    delete m_player;
    m_player = nullptr;
    
    // delete all of the dirt objects
    for (int i = 0; i < VIEW_HEIGHT; i++)
        for (int j = 0; j < VIEW_WIDTH; j++)
        {
            delete m_dirtField[i][j];
            m_dirtField[i][j] = nullptr;
        } // end for
    
    
    // delete all of the actors
    std::vector<Actor*>::iterator a = m_actors.begin();
    for(int i = 0; i < m_actors.size(); )
    {
        delete m_actors[i];
        m_actors.erase(a+i);
    } // end for
    
    // delete all of the protesters
    std::vector<Protester*>::iterator p = m_protesters.begin();
    for(int i = 0; i < m_protesters.size();)
    {
        delete m_protesters[i];
        m_protesters.erase(p+i);
    } // end for
    
} // end destructor

int StudentWorld::init()
{
    // fill in dirt over the entire 59 x 64 grid
    for (int i = 0; i < 64; i++)
    {
        for (int j = 0; j < 60; j++)
        {
            // leaving the mineshaft open
            if ((i < 30 || i > 33) || j < 4)
                m_dirtField[i][j] = new Dirt(i, j, this);
        } // end for
    } // end for
    
    // create the FrackMan
    m_player = new FrackMan(this);
    
    // calculate the number of nuggets, barrels, and boulders
    int B = min(GameWorld::getLevel() / 2 + 2, 6);
    int G = max(5-GameWorld::getLevel() / 2, 2);
    int L = min(2 + GameWorld::getLevel(), 20);
    
    m_oilCount = L;
    
    // add in the boulders...
    for (int i = 0; i < B; i++)
    {
        int tempX, tempY;
        // calculate random integers until they are not within a 6 radius and are in the shaft
        do
        {
            tempX = randInt(0, 60);
            tempY = randInt(20, 56);
        } while (isActorWithin(tempX, tempY, 6.0) || (tempX >= 27 && tempX <= 33));
        // add the boulder
        m_actors.push_back(new Boulder(tempX, tempY, this));
    } // end for
    
    // do the same for the nuggets...
    for (int i = 0; i < G; i++)
    {
        int tempX, tempY;
        do
        {
            tempX = randInt(0, 60);
            tempY = randInt(20, 56);
        } while (isActorWithin(tempX, tempY, 6.0) || (tempX >= 27 && tempX <= 33));
        m_actors.push_back(new GoldNugget(tempX, tempY, false, false, this));
    } // end for
    
    // as well as for the oil...
    for (int i = 0; i < L; i++)
    {
        int tempX, tempY;
        do
        {
            tempX = randInt(0, 60);
            tempY = randInt(20, 56);
        } while (isActorWithin(tempX, tempY, 6.0) || (tempX >= 27 && tempX <= 33));
        m_actors.push_back(new BarrelOfOil(tempX, tempY, this));
    } // end for
    
    // now remove the dirt surrounding each boulder...
    for (int i = 0; i < B; i++)
    {
        int tempX = m_actors[i]->GraphObject::getX();
        int tempY = m_actors[i]->GraphObject::getY();
        
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
            {
                delete m_dirtField[tempX+j][tempY+k];
                m_dirtField[tempX+j][tempY+k] = nullptr;
            } // end for
    } // end for
    
    return GWSTATUS_CONTINUE_GAME;
    
} // end init

int StudentWorld::move()
{
    // increment the tick count
    m_tickCount++;
    
    // clean the paths
    cleanPath();
    
    // let each actor do something
    for (int i = 0; i < m_actors.size(); i++)
    {
        if (m_actors[i]->isAlive())
        {
            m_actors[i]->doSomething();
            if (!m_player->isAlive())
            {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            } // end if
            if (m_oilCount == 0)
            {
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            } // end if
        } // end if
    } // end for
    
    // let the player do something
    m_player->doSomething();
    
    // set up the paths
    setPathToExit();
    setPathToFrackMan();
    
    // let each protester do something
    for (int i = 0; i < m_protesters.size(); i++)
    {
        if (m_protesters[i]->isAlive())
        {
            m_protesters[i]->doSomething();
            if (!m_player->isAlive())
            {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            } // end if
            if (m_oilCount == 0)
            {
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            } // end if
        } // end if
    } // end for
    
    // add goodies
    int G = (GameWorld::getLevel() * 25 + 300);
    int rand1 = randInt(1, G);
    if (rand1 == G)
    {
        int rand2 = randInt(1, 5);
        if (rand2 == 1)
        {
            m_actors.push_back(new SonarKit(0, 60, this));
        } // end if
        else
        {
            int randX, randY;
            do
            {
                randX = randInt(0, 60);
                randY = randInt(0, 56);
            } while(hasDirt(randX, randY, GraphObject::none));
            m_actors.push_back(new WaterPool(randX, randY, this));
        } // end else
    } // end if
        
    // add protestors
    int probabilityOfHardcore = min(90, GameWorld::getLevel() * 10 + 30);
    int T = max(25, 200 - GameWorld::getLevel());
    int maxProtesters = min(15, 2 + GameWorld::getLevel() * 1.5);
    if (m_tickCount == 1)
    {
        int tempRand = randInt(1, 100);
        if (tempRand <= probabilityOfHardcore)
        {
            m_protesters.push_back(new HardcoreProtester(IID_HARD_CORE_PROTESTER, this));
            m_tickSinceLastProtester = m_tickCount;
        } // end if
        else
        {
            m_protesters.push_back(new RegularProtester(IID_PROTESTER, this));
            m_tickSinceLastProtester = m_tickCount;
        } // end else
    } // end if
    else if (m_tickCount > T + m_tickSinceLastProtester && m_protesters.size() < maxProtesters)
    {
        int tempRand = randInt(1, 100);
        if (tempRand <= probabilityOfHardcore)
        {
            m_protesters.push_back(new HardcoreProtester(IID_HARD_CORE_PROTESTER, this));
            m_tickSinceLastProtester = m_tickCount;
        } // end if
        else
        {
            m_protesters.push_back(new RegularProtester(IID_PROTESTER, this));
            m_tickSinceLastProtester = m_tickCount;
        } // end else
    } // end else if
        
    // delete all dead actors
    std::vector<Actor*>::iterator n = m_actors.begin();
    for (int i = 0; i < m_actors.size();)
    {
        if (!m_actors[i]->isAlive())
        {
            delete m_actors[i];
            m_actors[i] = nullptr;
            m_actors.erase(n+i);
        } // end if
        else
            i++;
    } // end for
        
    // delete all dead protesters
    std::vector<Protester*>::iterator p = m_protesters.begin();
    for (int i = 0; i < m_protesters.size();)
    {
        if (!m_protesters[i]->isAlive())
        {
            delete m_protesters[i];
            m_protesters[i] = nullptr;
            m_protesters.erase(p+i);
        } // end if
        else
            i++;
    } // end for
    
    // update the statistics
    int Scr, Lvl, Lives, Hlth, Water, Gld, Sonar, OilLeft;
    Scr = GameWorld::getScore();
    Lvl = GameWorld::getLevel();
    Lives = GameWorld::getLives();
    Hlth = m_player->HP();
    Water = m_player->getWater();
    Gld = m_player->getNugget();
    Sonar = m_player->getSonar();
    OilLeft = m_oilCount;
    std::string stats = toStats(Scr, Lvl, Lives, Hlth, Water, Gld, Sonar, OilLeft);
    setGameStatText(stats);
    
    // check if the player is still alive
    if (!m_player->isAlive())
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    } // end if
    if (m_oilCount == 0)
    {
        playSound(SOUND_FINISHED_LEVEL);
        return GWSTATUS_FINISHED_LEVEL;
    } // end if
    
    // continue the game
    return GWSTATUS_CONTINUE_GAME;
    
} // end move

void StudentWorld::cleanUp()
{
    // delete the player
    delete m_player;
    m_player = nullptr;
    
    // delete all dirt objects
    for (int i = 0; i < VIEW_HEIGHT; i++)
        for (int j = 0; j < VIEW_WIDTH; j++)
        {
            delete m_dirtField[i][j];
            m_dirtField[i][j] = nullptr;
        } // end for
    
    // delete all the actors
    std::vector<Actor*>::iterator a = m_actors.begin();
    for(int i = 0; i < m_actors.size(); )
    {
        delete m_actors[i];
        m_actors.erase(a+i);
    } // end for
    
    // delete all the protesters
    std::vector<Protester*>::iterator p = m_protesters.begin();
    for(int i = 0; i < m_protesters.size();)
    {
        delete m_protesters[i];
        m_protesters.erase(p+i);
    } // end for
    
    // reset all of the world statistics
    m_tickCount = 0;
    m_tickSinceLastProtester = 1;
    m_oilCount = 0;
    
} // end cleanUp

int StudentWorld::Tick() const
{
    return m_tickCount;
} // end Tick

int StudentWorld::min(int a, int b) const
{
    if (a > b) return b;
    else return a;
} // end min

int StudentWorld::max(int a, int b) const
{
    if (a > b) return a;
    else return b;
} // end max

int StudentWorld::randInt(int min, int max) const
{
    if (max < min) std::swap(max, min);
    return min + (rand() % (max - min + 1));
} // end randInt

int StudentWorld::numPerpendicular(int x, int y, GraphObject::Direction dir) const
{
    int toReturn = 0;
    // if the object is facing in a vertical direction...
    if(dir == GraphObject::up || dir == GraphObject::down)
    {
        // if the left is valid add 1 to the return
        if(isValidPosition(x, y, GraphObject::left))
            toReturn++;
        // same for the right
        if(isValidPosition(x, y, GraphObject::right))
            toReturn++;
    } // end if
    
    // repeat the process if the object is instead facing a horizontal direction
    else
    {
        if(isValidPosition(x, y, GraphObject::up))
            toReturn++;
        if(isValidPosition(x, y, GraphObject::down))
            toReturn++;
    } // end else
    return toReturn;
    
} // end numPerpendicular

bool StudentWorld::isFrackManWithin(int x, int y, double r) const
{
    // if the distance between the player and the x and y is less than r...
    if(distBetween(m_player->getX(), m_player->getY(), x, y) <= r)
        return true;
    return false;
} // end isFrackManWithin

bool StudentWorld::isBoulderWithin(int x, int y, double r) const
{
    // go through the actors...
    for (int i = 0; i < m_actors.size(); i++)
        // if one of them is a boulder...
        if(m_actors[i]->getID() == IID_BOULDER)
            // check its distance
            if(distBetween(m_actors[i]->getX(), m_actors[i]->getY(), x, y) <= r)
                return true;
    return false;
} // end isBoulderWithin

bool StudentWorld::isBoulderWithin(int x, int y, int x_B, int y_B, double r) const
{
    // overloaded function that also passes in a reference to the current boulder
    // (this is used to make sure a boulder that is falling will not think that itself
    // will get in the way of its movement)
    for (int i = 0; i < m_actors.size(); i++)
        if(m_actors[i]->getID() == IID_BOULDER)
            if(distBetween(m_actors[i]->getX(), m_actors[i]->getY(), x, y) <= r && m_actors[i]->getX() != x_B && m_actors[i]->getY() != y_B)
                return true;
    return false;
} // end isBoulderWithin

bool StudentWorld::isProtesterWithin(int x, int y, double r) const
{
    // go through the protesters...
    for (int i = 0; i < m_protesters.size(); i++)
        // if one of them is within the radius and is NOT in a will leave the oil state...
        if(distBetween(m_protesters[i]->getX(), m_protesters[i]->getY(), x, y) <= r &&
           !m_protesters[i]->willLeave())
            return true;
    return false;
} // end isProtesterWithin

bool StudentWorld::hasDirt(int x, int y, GraphObject::Direction dir) const
{
    // check each direction for dirt blocks...
    switch(dir)
    {
            // if the object wants to move up...
        case GraphObject::up:
            // then there must be no dirt in the 1 x 4 rectangle above the object
            for (int i = x; i < x+4; i++)
                    if(m_dirtField[i][y+4] != nullptr)
                        return true;
            return false;
            // repeat this for the other 3 directions
        case GraphObject::right:
            for (int i = y; i < y+4; i++)
                if(m_dirtField[x+4][i] != nullptr)
                    return true;
            return false;
            
        case GraphObject::down:
            for (int i = x; i < x+4; i++)
                if(m_dirtField[i][y-1] != nullptr)
                    return true;
            return false;
            
        case GraphObject::left:
            for (int i = y; i < y+4; i++)
                if(m_dirtField[x-1][i] != nullptr)
                    return true;
            return false;
            
            // when passed in none, the function will return based on whether or not the
            // 4 x 4 square at x, y has any dirt in it
        case GraphObject::none:
            for (int i = x; i < x+4; i++)
                for (int j = y; j < y+4; j++)
                    if(m_dirtField[i][j] != nullptr)
                        return true;
            return false;
            
        default:
            return false;
    } // end switch
} // end hasDirt

bool StudentWorld::isValidPosition(int x, int y, GraphObject::Direction dir) const
{
    switch(dir)
    {
            // check to make sure there is no dirt in that direction,
            // there is not a boulder within a radius of 3
            // and the the object does not run out of bounds
        case GraphObject::up:
            if (!hasDirt(x, y, dir) && !isBoulderWithin(x, y+1, 3.0) && y < 60)
                return true;
            else return false;
            // repeat for each direction...
        case GraphObject::right:
            if (!hasDirt(x, y, dir) && !isBoulderWithin(x+1, y, 3.0) && x < 60)
                return true;
            else return false;
        case GraphObject::down:
            if (!hasDirt(x, y, dir) && !isBoulderWithin(x, y-1, 3.0) && y > 0)
                return true;
            else return false;
        case GraphObject::left:
            if (!hasDirt(x, y, dir) && !isBoulderWithin(x+1, y, 3.0) && x > 0)
                return true;
            else return false;
        default:
            return false;
    } // end switch
} // end isValidPosition

bool StudentWorld::isFacingFrackMan(int x, int y, GraphObject::Direction dir) const
{
    double DU, DR, DD, DL;
    switch(dir)
    {
            // if the protester is faceing up:
        case GraphObject::up:
            // if the protester is above the frackman...
            if (y > m_player->getY())
                // then there is no way it can be facing him
                return false;
            // if he is below the frackman, find the distance between them
            DU = distBetween(m_player->getX(), m_player->getY(), m_player->getX(), y);
            // if the frackman is + or - the distance between them to the right or left...
            if (x >= m_player->getX() - DU && x <= m_player->getX() + DU)
                // he is facing the frackman
                return true;
            return false;
            // repeat for each of the other directions...
        case GraphObject::right:
            if (x > m_player->getX())
                return false;
            DR = distBetween(m_player->getX(), m_player->getY(), x, m_player->getY());
            if (y >= m_player->getY() - DR && y <= m_player->getY() + DR)
                return true;
            return false;
        case GraphObject::down:
            if (y < m_player->getY())
                return false;
            DD = distBetween(m_player->getX(), m_player->getY(), m_player->getX(), y);
            if (x >= m_player->getX() - DD && x <= m_player->getX() + DD)
                return true;
            return false;
        case GraphObject::left:
            if (x < m_player->getX())
                return false;
            DL = distBetween(m_player->getX(), m_player->getY(), x, m_player->getY());
            if (y >= m_player->getY() - DL && y <= m_player->getY() + DL)
                return true;
            return false;
            
        default:
            return false;
    } // end switch
} // end isFacingFrackMan

bool StudentWorld::isFrackManInLOS(int x, int y) const
{
    bool toReturn = false;
    // check the horizontal:
    if (y == m_player->getY())
    {
        // if the protester is to the right of the frackman...
        if(x > m_player->getX())
            // start at the player and check each position to the right and make sure it is valid
            for (int i = m_player->getX(); i < x; i++)
            {
                if (!isValidPosition(i, y, GraphObject::right))
                {
                    toReturn = false;
                    break;
                } // end if
                toReturn = true;
            } // end for
        // if the protester is to the left of the frackman...
        else
            // perform the same seach, but instead start at the protester
            for (int i = x; i < m_player->getX(); i++)
            {
                if (!isValidPosition(i, y, GraphObject::right))
                {
                    toReturn = false;
                    break;
                } // end if
                toReturn = true;
            } // end for
    } // end if
    
    // check the vertical similarly:
    else if (x == m_player->getX())
    {
        if(y > m_player->getY())
            for (int i = m_player->getY(); i < y; i++)
            {
                if (!isValidPosition(x, i, GraphObject::up))
                {
                    toReturn = false;
                    break;
                } // end if
                toReturn = true;
            } // end for
        else
            for (int i = y; i < m_player->getY(); i++)
            {
                if (!isValidPosition(x, i, GraphObject::up))
                {
                    toReturn = false;
                    break;
                } // end if
                toReturn = true;
            } // end for
    } // end else if
    
    return toReturn;
} // end isFrackManInLOS

bool StudentWorld::isNMovesAway(int x, int y, int N) const
{
    int count = 0;
    int i = x;
    int j = y;
    for(;;)
    {
        // if there is ever a time where the number of steps taken is too large...
        if (count > N)
            // return false
            return false;
        
        // otherwise follow the path to the frackman at the given x and y
        switch(m_frack[i][j])
        {
            case GraphObject::up:
                count++;
                j++;
                if(m_player->getX() == i && m_player->getY() == j)
                    return true;
                break;
            case GraphObject::right:
                count++;
                i++;
                if(m_player->getX() == i && m_player->getY() == j)
                    return true;
                break;
            case GraphObject::down:
                count++;
                j--;
                if(m_player->getX() == i && m_player->getY() == j)
                    return true;
                break;
            case GraphObject::left:
                count++;
                i--;
                if(m_player->getX() == i && m_player->getY() == j)
                    return true;
                break;
            default:
                count++;
                break;
        } // end switch
    } // end for
} // end isNMovesAway

GraphObject::Direction StudentWorld::getPerpendicular(int x, int y, GraphObject::Direction dir) const
{
    // NOTE: this function will only be called if there is a single perpendicular direction to
    // travel
    // if the object is facing in the vertical direction
    if(dir == GraphObject::up || dir == GraphObject::down)
    {
        // its perp must be left...
        if(isValidPosition(x, y, GraphObject::left))
            return GraphObject::left;
        // or right.
        if(isValidPosition(x, y, GraphObject::right))
            return GraphObject::right;
    } // end if
    // and similarly if the object is facing in the horizontal direction
    else
    {
        if(isValidPosition(x, y, GraphObject::up))
            return GraphObject::up;
        if(isValidPosition(x, y, GraphObject::down))
            return GraphObject::down;
    } // end else
    return GraphObject::none;
} // end getPerpendicular

GraphObject::Direction StudentWorld::getDirectionToExit(int x, int y) const
{
    return m_exit[x][y];
} // end getDirectionToExit

GraphObject::Direction StudentWorld::getDirectionToFrackMan(int x, int y) const
{
    return m_frack[x][y];
} // end getDirectionToFrackMan

void StudentWorld::gotGoodie(int ID)
{
    // check the ID of the goodie...
    switch(ID)
    {
            // perform the proper actions depending on the type of goodie
        case IID_BARREL:
            playSound(SOUND_FOUND_OIL);
            increaseScore(1000);
            m_oilCount--;
            break;
        case IID_GOLD:
            playSound(SOUND_GOT_GOODIE);
            increaseScore(10);
            m_player->gotNugget();
            break;
        case IID_SONAR:
            playSound(SOUND_GOT_GOODIE);
            increaseScore(75);
            m_player->gotSonar();
        case IID_WATER_POOL:
            playSound(SOUND_GOT_GOODIE);
            increaseScore(100);
            m_player->gotWater();
            break;
        default:
            break;
    } // end switch
} // end gotGoodie

void StudentWorld::annoyPlayer(int n)
{
    m_player->getAnnoyed(n);
} // end annoyPlayer

void StudentWorld::clearDirt(int x, int y)
{
    for (int i = x; i < x+4; i++)
        for (int j = y; j < y+4; j++)
            if(m_dirtField[i][j] != nullptr)
            {
                delete m_dirtField[i][j];
                m_dirtField[i][j] = nullptr;
            } // end if
} // end clearDirt

void StudentWorld::dropNugget(int x, int y)
{
    m_actors.push_back(new GoldNugget(x, y, true, true, this));
} // end dropNugget

void StudentWorld::shootSquirt(int x, int y, GraphObject::Direction dir)
{
    // standard procedure here: check the directions and then create a new squirt object
    switch (dir)
    {
        case GraphObject::up:
            if(hasDirt(x, y+4, GraphObject::none) || isBoulderWithin(x, y+4, 3.0) ||
               y+7 >= VIEW_HEIGHT)
                return;
            m_actors.push_back(new Squirt(x, y+3, dir, this));
            return;
            
        case GraphObject::right:
            if(hasDirt(x+4, y, GraphObject::none) || isBoulderWithin(x+4, y, 3.0) ||
               x+7 >= VIEW_WIDTH)
                return;
            m_actors.push_back(new Squirt(x+3, y, dir, this));
            return;
            
        case GraphObject::down:
            if(hasDirt(x, y-4, GraphObject::none) || isBoulderWithin(x, y-4, 3.0) ||
               x - 3 < 0)
                return;
            m_actors.push_back(new Squirt(x, y-3, dir, this));
            return;
            
        case GraphObject::left:
            if(hasDirt(x-4, y, GraphObject::none) || isBoulderWithin(x-4, y, 3.0) ||
               y - 3 < 0)
                return;
            m_actors.push_back(new Squirt(x-3, y, dir, this));
            return;
            
        default:
            return;
    } // end switch
} // end shootSquirt

void StudentWorld::activateRadar(int x, int y, double r)
{
    // go through the actors...
    for (int i = 0; i < m_actors.size(); i++)
        // if they are within the players potision...
        if(distBetween(m_actors[i]->getX(), m_actors[i]->getY(), x, y) <= r)
            // make them visible
            m_actors[i]->setVisible(true);
} // end activateRadar

void StudentWorld::annoyProtesters(int x, int y, double r, int dmg)
{
    // go through the protesters...
    for (int i = 0; i < m_protesters.size(); i++)
        // if any of them are in range of the call...
        if(distBetween(m_protesters[i]->getX(), m_protesters[i]->getY(), x, y) <= r)
            // annoy them
            m_protesters[i]->getAnnoyed(dmg);
} // end annoyProtesters

void StudentWorld::protesterGotNugget(int x, int y, double r)
{
    // go through the protesters...
    for (int i = 0; i < m_protesters.size(); i++)
        // the first one in range of the nugget will pick it up.
        if(distBetween(m_protesters[i]->getX(), m_protesters[i]->getY(), x, y) <= r)
        {
            m_protesters[i]->gotNugget();
            return;
        } // end if
} // end protesterGotNugget

/////////////////////////////////////////////////////////////////
//  HELPER FUNCTION IMPLEMENTATIONS:
/////////////////////////////////////////////////////////////////

double StudentWorld::distBetween(int x1, int y1, int x2, int y2) const
{
    return sqrt((x2 - x1)*(x2-x1) + (y2-y1)*(y2-y1));
} // end distBetween

std::string StudentWorld::toStats(int Scr, int Lvl, int Lives, int Hlth, int Water, int Gld, int Sonar, int OilLeft) const
{
    std::ostringstream Stats;
    Stats << "Scr: " << std::setfill('0') << std::setw(6) << Scr;
    Stats << "  Lvl: " << std::setfill(' ') << std::setw(2) << Lvl << "  Lives: " << Lives
    << "  Hlth: " << std::setw(3) << 10*Hlth << "%  Wtr: " << std::setw(2) << Water
    << "  Gld: " << std::setw(2) << Gld << "  Sonar: " << std::setw(2) << Sonar
    << "  Oil Left: " << std::setw(2) << OilLeft;
    return Stats.str();
} // end toStats

bool StudentWorld::isActorWithin(int x, int y, double r) const
{
    for (int i = 0; i < m_actors.size(); i++)
        if(distBetween(m_actors[i]->getX(), m_actors[i]->getY(), x, y) <= r)
            return true;
    return false;
} // end isActorWithin

void StudentWorld::setPathToExit()
{
    class Coord
    {
    public:
        Coord(int x, int y) : m_x(x), m_y(y) {}
        int X() const {   return m_x; }
        int Y() const {   return m_y; }
    private:
        int m_x;
        int m_y;
    };
    
    // create a queue and push the ENDING position onto the queue
    std::queue<Coord> q;
    Coord C(60, 60);
    q.push(C);
    m_exit[60][60] = GraphObject::right;
    
    // repeat until there are no more paths...
    while (!q.empty())
    {
        // get the first item
        Coord temp = q.front();
        q.pop();
        
        // for each valid direction next to the top item of the queue, push that coordinate onto the stack
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::up) && m_exit[temp.X()][temp.Y()+1] == GraphObject::none)
        {
            Coord N(temp.X(), temp.Y()+1);
            q.push(N);
            m_exit[N.X()][N.Y()] = GraphObject::down;
        } // end if
        
        // repeat  for all directions...
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::right) && m_exit[temp.X()+1][temp.Y()] == GraphObject::none)
        {
            Coord N(temp.X()+1, temp.Y());
            q.push(N);
            m_exit[N.X()][N.Y()] = GraphObject::left;
        } // end if
        
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::down) && m_exit[temp.X()][temp.Y()-1] == GraphObject::none)
        {
            Coord N(temp.X(), temp.Y()-1);
            q.push(N);
            m_exit[N.X()][N.Y()] = GraphObject::up;
        } // end if
        
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::left) && m_exit[temp.X()-1][temp.Y()] == GraphObject::none)
        {
            Coord N(temp.X()-1, temp.Y());
            q.push(N);
            m_exit[N.X()][N.Y()] = GraphObject::right;
        } // end if
    } // end while
} // end setPathToExit

void StudentWorld::setPathToFrackMan()
{
    class Coord
    {
    public:
        Coord(int x, int y) : m_x(x), m_y(y) {}
        int X() const {   return m_x; }
        int Y() const {   return m_y; }
    private:
        int m_x;
        int m_y;
    };
    
    // same as path to exit, but now using the FrackMans coordinates as the end point
    std::queue<Coord> q;
    Coord C(m_player->getX(), m_player->getY());
    q.push(C);
    m_frack[m_player->getX()][m_player->getY()] = GraphObject::right;
    
    while (!q.empty())
    {
        Coord temp = q.front();
        q.pop();
        
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::up) && m_frack[temp.X()][temp.Y()+1] == GraphObject::none)
        {
            Coord N(temp.X(), temp.Y()+1);
            q.push(N);
            m_frack[N.X()][N.Y()] = GraphObject::down;
        } // end if
        
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::right) && m_frack[temp.X()+1][temp.Y()] == GraphObject::none)
        {
            Coord N(temp.X()+1, temp.Y());
            q.push(N);
            m_frack[N.X()][N.Y()] = GraphObject::left;
        } // end if
        
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::down) && m_frack[temp.X()][temp.Y()-1] == GraphObject::none)
        {
            Coord N(temp.X(), temp.Y()-1);
            q.push(N);
            m_frack[N.X()][N.Y()] = GraphObject::up;
        } // end if
        
        if(isValidPosition(temp.X(), temp.Y(), GraphObject::left) && m_frack[temp.X()-1][temp.Y()] == GraphObject::none)
        {
            Coord N(temp.X()-1, temp.Y());
            q.push(N);
            m_frack[N.X()][N.Y()] = GraphObject::right;
        } // end if
    } // end while
} // end setPathToFrackMan

void StudentWorld::cleanPath()
{
    // set all of the directions in the direction grids to none for the next tick
    for (int i = 0; i < VIEW_WIDTH-3; i++)
        for(int j = 0; j < VIEW_HEIGHT-3; j++)
        {
            m_exit[i][j] = GraphObject::none;
            m_frack[i][j] = GraphObject::none;
        } // end for
} // end cleanExit

