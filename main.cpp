// AI Disclaimer: This code was written with minimal AI assistance.
// Used AI for: debugging and input validation improvements.
// Core logic and problem-solving approach are my own work.
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>
#include <iomanip>

#include "Shape.h"
#include "Shape.cpp" // temporary workaround

void printAllAreas(const std::vector<std::unique_ptr<Shape>>& shapes) {
    for (const auto& shape : shapes) {
        shape->display();

        double area = shape->getArea();

        if (area == static_cast<int>(area)) {
            std::cout << "Area: " << static_cast<int>(area) << "\n\n";
        } else {
            std::cout << std::fixed << std::setprecision(4);
            std::cout << "Area: " << area << "\n\n";
        }
    }
}

int main() {
    std::ifstream file("shapes.txt");

    if (!file) {
        std::cerr << "Error: Could not open shapes.txt\n";
        return 1;
    }

    std::vector<std::unique_ptr<Shape>> shapes;

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;
        std::stringstream ss(line);

        std::string type;
        ss >> type;

        if (type == "rectangle") {
            double w, h;
            if (ss >> w >> h) {
                shapes.push_back(std::make_unique<Rectangle>(w, h));
            } else {
                std::cerr << "Error on line " << lineNumber << ": Invalid rectangle data\n";
            }
        }
        else if (type == "circle") {
            double r;
            if (ss >> r) {
                shapes.push_back(std::make_unique<Circle>(r));
            } else {
                std::cerr << "Error on line " << lineNumber << ": Invalid circle data\n";
            }
        }
        else {
            std::cerr << "Error on line " << lineNumber << ": Unknown shape type\n";
        }
    }

    printAllAreas(shapes);

    return 0;
}