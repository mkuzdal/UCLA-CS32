/** @file: maze.cpp */

#include <iostream>
#include <string>
using namespace std;


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // if at any point, the start is equal to the end, the end was found
    // (base case 1):
    if (sr == er && sc == ec)
        return true;
    
    maze[sr][sc] = '!'; // set the starting position to the dummy character (!).
    
    // Check north:
    if (maze[sr-1][sc] == '.')
    {
        // If a path exists from the north dir to the end, return true
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    } // end if
    
    // Check east:
    if (maze[sr][sc+1] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;
    } // end if
    
    // Check south:
    if (maze[sr+1][sc] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    } // end if
    
    // Check west:
    if (maze[sr][sc-1] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    } // end if
    
    // There was no path (base case 2), so return false.
    return false;
    
} // end pathExists

