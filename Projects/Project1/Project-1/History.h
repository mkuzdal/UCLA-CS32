// History.h

#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
{
public:
    // Constructor
    History(int nRows, int nCols);
    
    bool record(int r, int c);
    void display() const;
    
private:
    int   m_rows;
    int   m_cols;
    char  m_historyGrid[MAXROWS][MAXCOLS];
};

#endif // HISTORY_INCLUDED
