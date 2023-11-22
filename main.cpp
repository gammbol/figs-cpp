#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <iostream>

class Figure {
public:
    int radius, a, b, c, figType;
    double figArea, figVolume, density;

    virtual double Area()
    {
        return 0;
    };
    virtual double Volume()
    {
        return 0;
    };
    virtual std::string Print()
    {
        return "";
    }
};

class Ball : public Figure
{
public:
    double Area() override { return 4 * M_PI * pow(radius, 2); }
    double Volume() override { return 4/3 * M_PI * pow(radius, 3); }

    Ball(int radius, float density)
    {
        this->radius = radius;
        this->figArea = Area();
        this->figVolume = Volume();
        this->density = density;
        this->figType = 1;
    }

    std::string Print() override
    {
        return "Figure: Ball\n"
               "Radius: " + std::to_string(this->radius) + "\n"
               "Area: " + std::to_string(this->figArea) + "\n"
               "Volume: " + std::to_string(this->figVolume) + "\n"
               "Density: " + std::to_string(this->density) + "\n\n";
    }
};

class Parallelepiped : public Figure
{
public:
    double Area() override { return 2 * (a * b + b * c + c * a); }
    double Volume() override { return a * b * c; }

    Parallelepiped(int a, int b, int c, float density)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->figArea = Area();
        this->figVolume = Volume();
        this->density = density;
        this->figType = 2;
    }

    std::string Print() override
    {
        return "Figure: Parallelepiped\n"
               "Size: " + std::to_string(this->a) + "x" + std::to_string(this->b) + "x" + std::to_string(this->c) + "\n"
               "Area: " + std::to_string(this->figArea) + "\n"
               "Volume: " + std::to_string(this->figVolume) + "\n"
               "Density: " + std::to_string(this->density) + "\n\n";
    }
};

class RegularTetrahedron : public Figure
{
public:
    double Area() override { return pow(a, 2) * pow((double)3/4, (double)1/2); }
    double Volume() override { return (double)1/12 * pow(a, 3) * pow(2, 0.5); }

    RegularTetrahedron(int a, float density)
    {
        this->a = a;
        this->figArea = Area();
        this->figVolume = Volume();
        this->density = density;
        this->figType = 3;
    }

    std::string Print() override
    {
        return "Figure: Regular Tetrahedron\n"
               "Size: " + std::to_string(this->a) + "\n"
               "Area: " + std::to_string(this->figArea) + "\n"
               "Volume: " + std::to_string(this->figVolume) + "\n"
               "Density: " + std::to_string(this->density) + "\n\n";
    }
};

int findSmallest(std::vector<Figure*>* figs)
{
    auto smallest = (*figs)[0];
    int smallest_index = 0;
    for (int i = 0; i < figs->size(); i++)
    {
        if ((*figs)[i]->figArea < smallest->figArea)
        {
            smallest = (*figs)[i];
            smallest_index = i;
        }
    }
    return smallest_index;
}

void straightSelection(std::vector<Figure*>* figs, std::vector<Figure*>* sortedFigs)
{
    for (int i = 0; i < (*figs).size(); i++)
    {
        int smallest_index = findSmallest(figs);
        sortedFigs->push_back((*figs)[smallest_index]);
        auto it = figs->begin()+smallest_index;
        figs->erase(it);
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Figure*> figs;

    std::string line;
    int lineCount = 0, fig, a, b, c;
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
                line.erase(0, line.find(',')+2);
                c = stoi(line);
                line.erase(0, line.find(',')+2);
                density = stof(line);
                figs.push_back(new Parallelepiped(a, b, c, density));
            }
            else if (fig == 3)
            {
                a = stoi(line.substr(0, line.find(',')));
                line.erase(0, line.find(',')+2);
                density = stof(line);
                figs.push_back(new RegularTetrahedron(a, density));
            }
        }
    }
    in.close();

    std::vector<Figure*> sortedFigs;
    straightSelection(&figs, &sortedFigs);

    std::ofstream out;
    out.open(std::filesystem::current_path() / "../output.txt");
    if (out.is_open())
    {
        for (auto sortedFig : sortedFigs)
        {
            out << sortedFig->Print();
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << duration.count() << std::endl;

    return EXIT_SUCCESS;
}