#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>
#include<math.h>
#include <fstream>
#include <sstream> 
#include <memory>
using namespace std;


using namespace std;

class Figure {
public:

    //virtual void Notify(const string& message) const = 0;
    virtual string Name() const = 0;
    virtual double Perimeter() const = 0;
    virtual double Area() const = 0;
    
};

class Triangle : public Figure {
public:
    Triangle() {
        a = 0;
        b = 0;
        c = 0;
        //type = "TRIANGLE";
    }
    Triangle(double aa, double bb, double cc) {
        a = aa;
        b = bb;
        c = cc;
        //type = "TRIANGLE";
    }
    string Name() const override {
        return type;
    }
    double Perimeter() const override {
        return a + b + c;
    }
    double Area() const override {
        double p = (a + b + c) / 2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }

private:
    const string type = "TRIANGLE";
    double a, b, c;

};


class Rect : public Figure {
public:
    Rect() {
        a = 0;
        b = 0;
        
        //type = "TRIANGLE";
    }
    Rect(double aa, double bb) {
        a = aa;
        b = bb;
        
        //type = "TRIANGLE";
    }
    string Name() const override {
        return type;
    }
    double Perimeter() const override {
        return 2*(a + b);
    }
    double Area() const override {
        
        return a*b;
    }

private:
    const string type = "RECT";
    double a, b;

};

const double pi = 3.14;

class Circle : public Figure {
public:
    Circle() {
        r = 0;  
    }
    Circle(double rr) {
        r = rr;
    }
    string Name() const override {
        return type;
    }
    double Perimeter() const override {
        return 2 * pi * r;
    }
    double Area() const override {

        return pi * r * r;
    }

private:
    const string type = "CIRCLE";
    double r;

};

shared_ptr<Figure> CreateFigure(istream& stream) {
    string str;
    stream >> str;

    shared_ptr <Figure > fig;
    if (str == "TRIANGLE") {
        double a, b, c;
        stream >> a;
        stream.ignore(1);
        stream >> b;
        stream.ignore(1);
        stream >> c;
        fig = make_shared <Triangle>(a, b, c);
    }
    
    if (str == "RECT") {
        double a, b;
        stream >> a;
        stream.ignore(1);
        stream >> b;
        
        fig = make_shared <Rect>(a, b);
    }
    if (str == "CIRCLE") {
        double r;
        stream >> r;
        
        fig = make_shared <Circle>(r);
    }

    return fig;
}

int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}



/*

ADD RECT 2 3

ADD TRIANGLE 3 4 5

ADD RECT 10 20

ADD CIRCLE 5

PRINT


*/
