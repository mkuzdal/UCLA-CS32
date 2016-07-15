class circle
{
public:
    
    //CONSTRUCTOR:
    circle(double x, double y, double r);
    
    //ACCESSORS:
    double x() const;
    double y() const;
    double radius() const;
    void draw() const;
    
    //MUTATORS:
    bool scale(double factor);
    
private:
    //DATA MEMBERS:
    //Class invariant:   m_radius > 0
    
    double m_centerX;
    double m_centerY;
    double m_radius;
    
};