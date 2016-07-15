/** @file: landmark.cpp */

#include <iostream>
#include <string>
using namespace std;

// Abstract Class Landmark:
class Landmark
{
private:
    string m_name;
    
public:
    Landmark(string name) : m_name(name) {}
    virtual ~Landmark() {}
    string name() const { return m_name; }
    virtual string color() const { return "yellow"; }
    virtual string icon() const = 0;
    
}; // end Landmark

// ************************************************* //

class Hotel : public Landmark
{
private:
    
public:
    Hotel(string name) : Landmark(name) {}
    virtual ~Hotel() { cout << "Destroying the hotel " << name() << "." << endl; }
    virtual string icon() const { return "bed"; }
    
}; // end Hotel

// ************************************************* //

class Restaurant : public Landmark
{
private:
    int m_capacity;

public:
    Restaurant(string name, int capacity): Landmark(name), m_capacity(capacity) {}
    virtual ~Restaurant() { cout << "Destroying the restaurant " << name() << "." << endl; }
    virtual string icon() const
    {
        if (m_capacity < 40)
            return "small knife/fork";
        else
            return "large knife/fork";
    } // end icon
    
}; // end Restaurant

// ************************************************* //

class Hospital : public Landmark
{
private:

public:
    Hospital(string name) : Landmark(name) {}
    virtual ~Hospital() { cout << "Destroying the hospital " << name() << "." << endl; }
    virtual string color() const { return "blue"; }
    virtual string icon() const {return "H"; }
    
}; // end Hospital

// ************************************************* //
