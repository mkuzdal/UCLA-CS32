/** @file: Actor.cpp */

#include "Actor.h"
#include "StudentWorld.h"
#include "GameController.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "GameWorld.h"

////////////////////////////////////////////////////////////////////
//  FRACKMAN IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void FrackMan::doSomething()
{
    // if the player is dead, do nothing
    if(!isAlive())
        return;
    
    // if there is dirt where the player is...
    if(getWorld()->hasDirt(getX(), getY(), none))
    {
        // destroy it
        getWorld()->clearDirt(getX(), getY());
        getWorld()->playSound(SOUND_DIG);
    } // end if
    
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
        // user hit a key this tick
        switch (ch)
        {
            case KEY_PRESS_ESCAPE:
                setDead();
                break;
            case KEY_PRESS_SPACE:
                if (m_waterCount > 0)
                {
                    m_waterCount--;
                    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
                    getWorld()->shootSquirt(getX(), getY(), getDirection());
                } // end if
                break;
            case KEY_PRESS_TAB:
                if (m_nuggetCount > 0)
                {
                    m_nuggetCount--;
                    getWorld()->dropNugget(getX(), getY());
                } // end if
                break;
            case KEY_PRESS_UP:
                if (getDirection() != up)
                    setDirection(up);
                else
                {
                    if(getY()+4 >= VIEW_HEIGHT)
                        moveTo(getX(), getY());
                    else if(!getWorld()->isBoulderWithin(getX(), getY()+1, 3.0))
                        moveTo(getX(), getY()+1);
                } // end else
                break;
            case KEY_PRESS_RIGHT:
                if (getDirection() != right)
                    setDirection(right);
                else
                {
                    if(getX()+4 >= VIEW_WIDTH)
                        moveTo(getX(), getY());
                    else if(!getWorld()->isBoulderWithin(getX()+1, getY(), 3.0))
                        moveTo(getX()+1, getY());
                } // end else
                break;
            case KEY_PRESS_DOWN:
                if (getDirection() != down)
                    setDirection(down);
                else
                {
                    if(getY() <= 0)
                        moveTo(getX(), getY());
                    else if(!getWorld()->isBoulderWithin(getX(), getY()-1, 3.0))
                        moveTo(getX(), getY()-1);
                } // end else
                break;
            case KEY_PRESS_LEFT:
                if (getDirection() != left)
                    setDirection(left);
                else
                {
                    if(getX() <= 0)
                        moveTo(getX(), getY());
                    else if(!getWorld()->isBoulderWithin(getX()-1, getY(), 3.0))
                        moveTo(getX()-1, getY());
                } // end else
                break;
            case 'z':
            case 'Z':
                if(m_sonarCount > 0)
                {
                    m_sonarCount--;
                    getWorld()->playSound(SOUND_SONAR);
                    getWorld()->activateRadar(getX(), getY(), 12.0);
                } // end if
                break;
            default:
                moveTo(getX(), getY());
                break;
        } // end switch
    } // end if
} // end doSomething

void FrackMan::getAnnoyed(int n)
{
    loseHP(n);
    if (HP()<=0)
    {
        setDead();
        getWorld()->playSound(SOUND_PLAYER_GIVE_UP);
    } // end if
} // end getAnnoyed

////////////////////////////////////////////////////////////////////
//  PROTESTER IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void Protester::doSomething()
{
    if(!isAlive())
        return;
    
    if(getWorld()->Tick() - lastAction() < waitTime())
        return;
    
    if(willLeave())
    {
        if(getX() == 60 && getY() == 60)
            setDead();
        else
            switch(getWorld()->getDirectionToExit(getX(), getY()))
        {
            case up:
                setDirection(up);
                moveTo(getX(), getY()+1);
                break;
            case right:
                setDirection(right);
                moveTo(getX()+1, getY());
                break;
            case down:
                setDirection(down);
                moveTo(getX(), getY()-1);
                break;
            case left:
                setDirection(left);
                moveTo(getX()-1, getY());
                break;
            default:
                break;
        } // end switch
        setLastAction(getWorld()->Tick());
        return;
    } // end if
    
    setWaitTime(defaultWaitTime());
    if(getWorld()->isFrackManWithin(getX(), getY(), 4.0) && getWorld()->isFacingFrackMan(getX(), getY(), getDirection()) &&
            getWorld()->Tick() - lastShout() >= defaultWaitTime()*16)
    {
        getWorld()->playSound(SOUND_PROTESTER_YELL);
        getWorld()->annoyPlayer(2);
        setLastShout(getWorld()->Tick());
        setLastAction(getWorld()->Tick());
        setWaitTime((defaultWaitTime()*16));
        return;
    } // end else if
    
    int N = 16 + getWorld()->getLevel() * 2;
    if(getID() == IID_HARD_CORE_PROTESTER && getWorld()->isNMovesAway(getX(), getY(), N))
    {
        chaseFrackMan();
        return;
    }
    
    if(getWorld()->isFrackManInLOS(getX(), getY()) && !getWorld()->isFrackManWithin(getX(), getY(), 4.0))
    {
        setDirection(getWorld()->getDirectionToFrackMan(getX(), getY()));
        switch(getDirection())
        {
            case up:
                moveTo(getX(), getY()+1);
                break;
            case right:
                moveTo(getX()+1, getY());
                break;
            case down:
                moveTo(getX(), getY()-1);
                break;
            case left:
                moveTo(getX()-1, getY());
                break;
            default:
                break;
        } // end switch
        setNumMoves(0);
        setLastAction(getWorld()->Tick());
        return;
    } // end else if
    
    setNumMoves(numMoves()-1);
    int n = getWorld()->numPerpendicular(getX(), getY(), getDirection());
    if(numMoves() <= 0)
    {
        bool isValid = false;
        do
        {
            int temp = getWorld()->randInt(1, 4);
            switch(temp)
            {
                case 1:
                    if(getWorld()->isValidPosition(getX(), getY(), up))
                    {
                        isValid = true;
                        setDirection(up);
                    } // end if
                    break;
                case 2:
                    if(getWorld()->isValidPosition(getX(), getY(), right))
                    {
                        isValid = true;
                        setDirection(right);
                    } // end if
                    break;
                case 3:
                    if(getWorld()->isValidPosition(getX(), getY(), down))
                    {
                        isValid = true;
                        setDirection(down);
                    } // end if
                    break;
                case 4:
                    if(getWorld()->isValidPosition(getX(), getY(), left))
                    {
                        isValid = true;
                        setDirection(left);
                    } // end if
                    break;
                default:
                    break;
            } // end switch
        } while (!isValid);
        setNumMoves(getWorld()->randInt(8, 60));
    } // end if

    else if(n > 0 && getWorld()->Tick() - lastPerp() >= defaultWaitTime()*200)
    {
        if(n == 1)
            setDirection(getWorld()->getPerpendicular(getX(), getY(), getDirection()));
        else
        {
            int temp = getWorld()->randInt(1, 2);
            if(getDirection() == right || getDirection() == left)
            {
                if(temp == 1)
                    setDirection(up);
                else setDirection(down);
            } // end if
            else
            {
                if(temp == 1)
                    setDirection(right);
                else setDirection(left);
            } // end else
        } // end else
        setNumMoves(getWorld()->randInt(8, 60));
        setLastPerp(getWorld()->Tick());
    } // end else if
    
    switch(getDirection())
    {
        case up:
            if (!getWorld()->isValidPosition(getX(), getY(), up))
                setNumMoves(0);
            else moveTo(getX(), getY()+1);
            break;
        case right:
            if (!getWorld()->isValidPosition(getX(), getY(), right))
                setNumMoves(0);
            else moveTo(getX()+1, getY());
            break;
        case down:
            if (!getWorld()->isValidPosition(getX(), getY(), down))
                setNumMoves(0);
            else moveTo(getX(), getY()-1);
            break;
        case left:
            if (!getWorld()->isValidPosition(getX(), getY(), left))
                setNumMoves(0);
            else moveTo(getX()-1, getY());
            break;
        default:
            break;
    } // end switch
    setLastAction(getWorld()->Tick());
    
} // end doSomething

////////////////////////////////////////////////////////////////////
//  REGULAR PROTESTER IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void RegularProtester::getAnnoyed(int n)
{
    if (willLeave())
        return;
    
    loseHP(n);
    
    if (HP() > 0)
    {
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        setWaitTime(defaultWaitTime()+(getWorld()->max(50, 100 - getWorld()->getLevel() * 10)));
    } // end if
    else if (HP() <= 0)
    {
        setWillLeave(true);
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        setWaitTime(defaultWaitTime());
        getWorld()->increaseScore(100);
        if (HP() < -80)
            getWorld()->increaseScore(400);
    } // end else if
}

void RegularProtester::gotNugget()
{
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(25);
    setWillLeave(true);
    setWaitTime(defaultWaitTime());
} // end gotNugget

void RegularProtester::chaseFrackMan()
{
} // end chaseFrackMan

////////////////////////////////////////////////////////////////////
//  HARDCORE PROTESTER IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void HardcoreProtester::getAnnoyed(int n)
{
    if (willLeave())
        return;
    
    loseHP(n);
    
    if (HP() > 0)
    {
        getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
        setWaitTime(defaultWaitTime()+(getWorld()->max(50, 100 - getWorld()->getLevel() * 10)));
    } // end if
    else if (HP() <= 0)
    {
        setWillLeave(true);
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        setWaitTime(defaultWaitTime());
        getWorld()->increaseScore(250);
        if (HP() < -80)
            getWorld()->increaseScore(250);
    } // end else if
} // end getAnnoyed

void HardcoreProtester::gotNugget()
{
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    getWorld()->increaseScore(50);
    setWaitTime(defaultWaitTime()+(getWorld()->max(50, 100 - getWorld()->getLevel() * 10)));
} // end gotNugget

void HardcoreProtester::chaseFrackMan()
{
    if(!getWorld()->isFrackManWithin(getX(), getY(), 4.0))
    {
        int N = 16 + getWorld()->getLevel() * 2;
        if (getWorld()->isNMovesAway(getX(), getY(), N))
        {
            setDirection(getWorld()->getDirectionToFrackMan(getX(), getY()));
            switch(getDirection())
            {
                case up:
                    moveTo(getX(), getY()+1);
                    setLastAction(getWorld()->Tick());
                    break;
                case right:
                    moveTo(getX()+1, getY());
                    setLastAction(getWorld()->Tick());
                    break;
                case down:
                    moveTo(getX(), getY()-1);
                    setLastAction(getWorld()->Tick());
                    break;
                case left:
                    moveTo(getX()-1, getY());
                    setLastAction(getWorld()->Tick());
                    break;
                default:
                    break;
            } // end switch
            setLastAction(getWorld()->Tick());
            return;
        } // end if
    } // end if
} // end chaseFrackMan

////////////////////////////////////////////////////////////////////
//  DIRT IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void Dirt::doSomething()
{
} // end doSomething

////////////////////////////////////////////////////////////////////
//  BOULDER IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void Boulder::doSomething()
{
    if(!isAlive())
        return;
    
    else if(m_isStable)
    {
        if(!getWorld()->hasDirt(getX(), getY(), down))
        {
            m_isStable = false;
            m_transitionTick = getWorld()->Tick();
            return;
        } // end if
        else
            return;
    } // end else if
    
    else if(!m_isStable && !m_isFalling && (getWorld()->Tick()-m_transitionTick < 31))
        return;
    
    else if(!m_isStable && !m_isFalling)
    {
        m_isFalling = true;
        getWorld()->playSound(SOUND_FALLING_ROCK);
    } // end else if
    
    if (m_isFalling)
    {
        if(getWorld()->isBoulderWithin(getX(), getY()-1, getX(), getY(), 3.0) || getWorld()->hasDirt(getX(), getY(), down) || getY() == 0)
        {
               setDead();
               return;
        } // end if
        
        moveTo(getX(), getY()-1);
        
        if(getWorld()->isProtesterWithin(getX(), getY(), 3.0))
        {
            getWorld()->annoyProtesters(getX(), getY(), 3.0, 100);
        } // end if
        
        if(getWorld()->isFrackManWithin(getX(), getY(), 3.0))
        {
            for(int i = 0; i < 5; i++)
                getWorld()->annoyPlayer(100);
        } // end if
        
    } // end else if
    
} // end doSomething

////////////////////////////////////////////////////////////////////
//  SQUIRT IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void Squirt::doSomething()
{
    if(getWorld()->isProtesterWithin(getX(), getY(), 3.0))
    {
        getWorld()->annoyProtesters(getX(), getY(), 3.0, 2);
        setDead();
        return;
    } // end if
    
    if (m_travelDistance == 0)
    {
        setDead();
        return;
    } // end if
    
    switch(getDirection())
    {
        case up:
            if(!getWorld()->isValidPosition(getX(), getY(), up))
                setDead();
            else
            {
                moveTo(getX(), getY()+1);
                m_travelDistance--;
            } // end else
            return;
        case right:
            if(!getWorld()->isValidPosition(getX(), getY(), right))
                setDead();
            else
            {
                moveTo(getX()+1, getY());
                m_travelDistance--;
            } // end else
            return;
        case down:
            if(!getWorld()->isValidPosition(getX(), getY(), down))
                setDead();
            else
            {
                moveTo(getX(), getY()-1);
                m_travelDistance--;
            } // end else
            return;
        case left:
            if(!getWorld()->isValidPosition(getX(), getY(), left))
                setDead();
            else
            {
                moveTo(getX()-1, getY());
                m_travelDistance--;
            } // end else
            return;
            
        default:
            return;
    } // end switch
    
} // end doSomething

////////////////////////////////////////////////////////////////////
//  GOODIE IMPLEMENTATIONS:
////////////////////////////////////////////////////////////////////

void Goodie::doSomething()
{
    if(!isAlive())
        return;
    
    if(!isVisible() && getWorld()->isFrackManWithin(getX(), getY(), 4.0))
    {
        setVisible(true);
        return;
    } // end if
    
    else if(m_isFrackMan && getWorld()->isFrackManWithin(getX(), getY(), 3.0))
    {
        getWorld()->gotGoodie(getID());
        setDead();
        return;
    } // end else if
    
    else if(m_isProtester && getWorld()->isProtesterWithin(getX(), getY(), 3.0))
    {
        getWorld()->protesterGotNugget(getX(), getY(), 3.0);
        setDead();
        return;
    } // end else if
    
    else if (m_isTemporary && getWorld()->Tick() - m_initialTick >= m_lifeTime)
        setDead();
} // end doSomething

