#ifndef HEXAGON_HPP
#define HEXAGON_HPP

#include "figure.hpp"

class Hexagon : public Figure {
public:
    Hexagon() = default;

    Hexagon(std::pair<double, double>& center, double rad) : Figure(center), radius(rad) {}

    double Area() override {
        return pow(radius, 2) * 3 * sqrt(3) * 0.5;
    }

    void Print() override {
        std::cout << *this << std::endl;
        std::cout << "2. Area of figure: " << Area() << std::endl;
        auto center = GetCenter();
        std::cout << "3. Center: (" << center.first << "; " << center.second << ")" << std::endl;
    }

    void PrintToFile(std::ofstream& out) override {
        out << *this << std::endl;
        out << "2. Area of figure: " << Area() << std::endl;
        auto center = GetCenter();
        out << "3. Center: (" << center.first << "; " << center.second << ")" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& out, Hexagon& h);

private:
    double radius = 0;
};

std::ostream& operator<<(std::ostream& out, Hexagon& h) {
    out << "\nHexagon:\n";
    out << "1. Coordinates: ";
    double pi = acos(-1);
    for (int i = 0; i < 6; ++i) {
        double angle = pi * i / 3;
        out.precision(2);
        out << "(" << h.center.first + h.radius * cos(angle) << "; "
            << h.center.second + h.radius * sin(angle) << ")";
        if (i != 5) {
            out << ", ";
        }
    }
    return out;
}

#endif //HEXAGON_HPP