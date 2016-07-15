// History.cpp

#include "History.h"

#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
: m_rows(nRows), m_cols(nCols)
{
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
        {
            m_historyGrid[i][j] = '.';
        }
}

bool History::record(int r, int c)
{
    if (r > m_rows || r < 1 || c > m_cols || c < 1)
        return false;
    if (m_historyGrid[r-1][c-1] == '.')
    {
        m_historyGrid[r-1][c-1] = 'A';
        return true;
    }
    else if (m_historyGrid[r-1][c-1] == 'Z')
        return true;
    else
    {
        m_historyGrid[r-1][c-1]++;
        return true;
    }
}

void History::display() const
{
    clearScreen();
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            cout << m_historyGrid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}
