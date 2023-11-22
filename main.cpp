#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>

class Figure {};

class Ball : Figure
{
public:
    int radius;
    double figArea, figVolume, density;

    double Area() { return 4 * M_PI * pow(radius, 2); }
    double Volume() { return 4/3 * M_PI * pow(radius, 3); }

    Ball(int radius, float density)
    {
        this->radius = radius;
        this->figArea = Area();
        this->figVolume = Volume();
        this->density = density;
    }
};

class Parallelepiped : Figure
{
public:
    int a, b, c;
    double figArea, figVolume, density;

    double Area() { return 2 * (a * b + b * c + c * a); }
    double Volume() { return a * b * c; }

    Parallelepiped(int a, int b, int c, float density)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->figArea = Area();
        this->figVolume = Volume();
        this->density = density;
    }
};

class RegularTetrahedron : Figure
{
public:
    int a;
    double figArea, figVolume, density;

    double Area() { return pow(a, 2) * pow((double)3/4, (double)1/2); }
    double Volume() { return (double)1/12 * pow(a, 3) * pow(2, 0.5); }

    RegularTetrahedron(int a, float density)
    {
        this->a = a;
        this->figArea = Area();
        this->figVolume = Volume();
        this->density = density;
    }
};

std::ostream& operator << (std::ostream& os, const Ball &ball)
{
    return os << "Figure: Ball\n" << "Radius: " << ball.radius << "\nArea: " << ball.figArea <<
              "\nVolume: " << ball.figVolume << "\nDensity: " << ball.density;
}
std::ostream& operator << (std::ostream& os, const Parallelepiped &p)
{
    return os << "Figure: Parallelepiped\n" << "Size: " << p.a << "x" << p.b << "x" << p.c <<
              "\nArea: " << p.figArea << "\nVolume: " << p.figVolume <<
              "\nDensity: " << p.density;
}
std::ostream& operator << (std::ostream& os, const RegularTetrahedron &rt)
{
    return os << "Figure: Regular Tetrahedron\n" << "Size: " << rt.a << "\nArea: " << rt.figArea <<
              "\nVolume: " << rt.figVolume << "\nDensity: " << rt.density;
}

int main()
{
    std::vector<Figure> figs;

    std::string line;
    int fig, a, b, c;
    float density;

    std::ifstream in(std::filesystem::current_path() / "../input.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            fig = stoi(line.substr(0, 1));
            line.erase(0, 3);
            if (fig == 1)
            {
                a = stoi(line.substr(0, line.find(',')));
                line.erase(0, line.find(',')+2);
                density = stof(line);
                figs.push_back(new Ball(a, density));
            }
            else if (fig == 2)
            {
                a = stoi(line.substr(0, line.find(',')));
                line.erase(0, line.find(',')+2);
                b = stoi(line);
            }
        }
    }
    in.close();

    return EXIT_SUCCESS;
}