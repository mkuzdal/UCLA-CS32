/** @file: list.cpp */

void listAll(const Class* c, string path)  // two-parameter overload
{
    // Base case
    if(path == "")
    {
        cout << c->name() << endl;
        listAll(c, c->name() + "=>");
        return;
    } // end if
    
    for(int i=0; i<c->subclasses().size(); i++)
    {
        Class* temp=c->subclasses().at(i);
        cout << path + temp->name() << endl;
        listAll(temp, path+ temp->name() + "=>");
    } // end for
    
} // end listAll
