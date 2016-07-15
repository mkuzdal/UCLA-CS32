// main.cpp

#include <iostream>
#include <string>
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


class String
{
public:
    String(const char* value);      // CONSTRUCTOR
    String(const String& other);    // COPY CONSTRUCTOR
    ~String();                      // DECONSTRUCTOR
    String& operator=(const String& rhs);
    void swap(String& other);
private:
    int m_len;
    char* m_text;
};

String::String(const char* value)
{
    if (value == nullptr)
        value = "";
    m_len = strlen(value);
    m_text = new char[m_len+1];
    strcpy(m_text, value);
}

String::String(const String& other) // <--- COPY CONSTRUCTOR (MUST BE PASSED BY CONST REFERENCE)
{
    m_len = other.m_len;    // a public member function can access data members of that type
                            // for any object of that type.
    m_text  = new char[m_len+1];
    strcpy(m_text, other.m_text);
}

String& String::operator=(const String& rhs)   // <--- USED WHEN ONE STRING = ANOTHER STRING
{                                              // PROTECTS FROM ALIASING
    String temp(rhs);
    this->swap(temp);       // checking if they are the same is optional in this scenario
    return *this;
    
    /** if (this != &rhs)
    { */
     
    /** if (*this != rhs) */
    /** if(strcmp(m_text, this.m_text) != 0) */     // not necessary, costs just as much if not
                                                    // more time than it saves
    /** delete [] m_text;
        m_len = rhs.m_len;
        m_text = new char[m_len+1];
        strcpy(m_text, rhs.m_text);
        return *this;
    }
    else
        return *this; */
}

String::~String()
{
    delete [] m_text;   // if m_text is an array, this is the proper way to delete it;
    // delete m_text;  <-- however, had m_text been a single object, this is how it is deleted.
}

void String::swap(String& other)
{
    char* tempC = this->m_text;     // swap the text
    this->m_text = other.m_text;
    other.m_text = tempC;
    int tempI = this-> m_len;       // swap the length
    this->m_len = other.m_len;
    other.m_len = tempI;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


struct Employee
{
    string name;        // when an employee is deleted, only the string's destructor is called.
    double salary;      // the other data members are left unchanged
    int age;
};


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/** 
void f(int a, int b = 42, double c = 3.7); // if you declare a default value for b,
                                           // everything after b must have a default value.
void g(int a = 1, int b = 2);

void g(int x);

int main()
{
    String s("Hello");
    f(10, 20, 343.67); // -> calls f(a=10, b=20, c=343.67)
    f(10, 20);         // -> calls f(a=10, b=20, c=3.7)
    f(10);             // -> calls f(a=10, b=42, c=3.7)
    
    // f(10,,343.67);     -> WONT COMPILE!
    
    g(10, 20);         // -> calls g(a=10, b=20)
    g();               // -> calls g(a=1, b=2)
    
    // g(10)              -> WONT COMPILE! (it's too ambigous)
} */


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


/**
void f(string t)
{
    string u("wow");
    u = t;                      // CANT BE COPIED BECAUSE U IS ALREADY DEFINED
} */

/**
string s3(s);       // <-----+
string s3 = s;      // <----THESE TWO ARE THE SAME
*/

int m(7);           // int m = 7;




















