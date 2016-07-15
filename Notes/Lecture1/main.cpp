#include "circle.h"
#include "globals.h"

#include <iostream>
using namespace std;

int main()
{
    circle blah(8, -3, 1.5);
    cout << "Center: (" << blah.x() << "," << blah.y() << ")" << endl;
    cout << "Radius: " << blah.radius() << endl;
    cout << area(blah) << endl;
}