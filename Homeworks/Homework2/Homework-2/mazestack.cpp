/** @file: mazestack.cpp */

#include <stack>
#include <iostream>
using namespace std;

class Coord
{
private:
    
    int m_r;
    int m_c;
    
public:
    
    // Creates a new coord with values rr and cc.
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    
    
    // Returns the row of the coord.
    int r() const { return m_r; }
    
    
    // Returns the column of the coord.
    int c() const { return m_c; }
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    Coord c(sr, sc);
    coordStack.push(c); // push the starting point onto the stack.
    maze[sr][sc] = '!'; // set the starting position to a dummy character (!).
    while(!coordStack.empty())
    {
        // get the top coord from the stack...
        Coord n = coordStack.top();
        coordStack.pop();
        
        // if that coordinate is equal to the end...
        if (n.r() == er && n.c() == ec)
            // the end was found.
            return true;
        
        // if the spot above the coord is not a wall (i.e., it is traversable)...
        if (maze[(n.r() - 1)][n.c()] == '.')
        {
            //  push this new coordinate onto the stack and update the
            //  position with the dummy character
            
            Coord N(n.r()-1, n.c());
            coordStack.push(N);
            maze[N.r()][N.c()] = '!';
            
        } // end if
        
        // Repeat this checking the other 3 directions surrounding the coordinate
        
        if (maze[n.r()][(n.c() + 1)] == '.')
        {
            Coord E(n.r(), n.c()+1);
            coordStack.push(E);
            maze[E.r()][E.c()] = '!';
            
        } // end if
        
        if (maze[(n.r() + 1)][n.c()] == '.')
        {
            Coord S(n.r()+1, n.c());
            coordStack.push(S);
            maze[S.r()][S.c()] = '!';
            
        } // end if
        
        if (maze[n.r()][(n.c() - 1)] == '.')
        {
            Coord W(n.r(), n.c()-1);
            coordStack.push(W);
            maze[W.r()][W.c()] = '!';
            
        } // end if
        
    } // end while
    
    // If there was never a time where a current coordinate was equal to the finish,
    // then there must be no route to get to the end.
    return false;
    
} // end pathExists

