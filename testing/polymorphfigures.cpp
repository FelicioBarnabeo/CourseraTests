#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <math.h>

using namespace std;

const double Pi = 3.14;

class Figure
{
public:
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
};

class Triangle : public Figure
{
public:
    Triangle(int a, int b, int c) : m_a(a), m_b(b), m_c(c){}
    string Name() const { return "TRIANGLE" ;}
    double Perimeter() const { return m_a+m_b+m_c;}
    double Area() const
    {
        double p = (m_a+m_b+m_c)/2.0;
        return sqrt(p*(p-m_a)*(p-m_b)*(p-m_c));
    }
private:
    int m_a, m_b, m_c;
};

class Rect : public Figure
{
public:
    Rect(int a, int b): m_a(a), m_b(b) {}
    string Name() const { return "RECT"; }
    double Perimeter() const { return 2*(m_a+m_b); }
    double Area() const { return m_a*m_b; }
private:
    int m_a, m_b;
};

class Circle : public Figure
{
public:
    Circle(int r) : m_radius(r) {}
    string Name() const { return "CIRCLE"; }
    double Perimeter() const { return 2*Pi*m_radius; }
    double Area() const { return Pi*m_radius*m_radius; }
private:
    int m_radius;
};

shared_ptr<Figure> CreateFigure(istringstream & is)
{
    string typeFigure;
    is >> typeFigure;
    int a, b, c, r;
    if(typeFigure == "TRIANGLE")
    {
        is >> a >> b >> c;
        return make_shared<Triangle>(a,b,c);
    }
    if(typeFigure == "RECT")
    {
        is >> a >> b;
        return make_shared<Rect>(a,b);
    }
    if(typeFigure == "CIRCLE")
    {
        is >> r;
        return make_shared<Circle>(r);
    }
    return shared_ptr<Figure>(); // Not correct! never execute
}

//int main() {
//    vector<shared_ptr<Figure>> figures;
//    for (string line; getline(cin, line); ) {
//    istringstream is(line);

//    string command;
//    is >> command;
//    if (command == "ADD") {
//      figures.push_back(CreateFigure(is));
//    } else if (command == "PRINT") {
//      for (const auto& current_figure : figures) {
//        cout << fixed << setprecision(3)
//             << current_figure->Name() << " "
//             << current_figure->Perimeter() << " "
//             << current_figure->Area() << endl;
//      }
//    }
//    }
//    return 0;
//}

//ADD RECT 2 3
//ADD TRIANGLE 3 4 5
//ADD RECT 10 20
//ADD CIRCLE 5
//PRINT

//RECT 10.000 6.000
//TRIANGLE 12.000 6.000
//RECT 60.000 200.000
//CIRCLE 31.400 78.500
