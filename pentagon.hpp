#ifndef PENTAGON_HPP
#define PENTAGON_HPP

#include "figure.hpp"

class Pentagon : public Figure {
public:
    Pentagon() = default;

    Pentagon(std::pair<double, double>& center, double rad) : Figure(center), radius(rad) {}

    double Area() override {
        double pi = acos(-1);
        double side = radius * cos(13 * pi / 10) - radius * cos(17 * pi / 10);
        return sqrt(25 + 10 * sqrt(5)) * pow(side, 2) * 0.25;
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

    friend std::ostream& operator<<(std::ostream& out, Pentagon& p);

private:
    double radius = 0;
};

std::ostream& operator<<(std::ostream& out, Pentagon& p) {
    out << "\nPentagon:\n";
    out << "1. Coordinates: ";
    double pi = acos(-1);
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * pi * i / 5;
        out.precision(2);
        out << "(" << p.center.first + p.radius * cos(angle + pi / 10) << "; "
            << p.center.second + p.radius * sin(angle + pi / 10) << ")";
        if (i != 4) {
            out << ", ";
        }
    }
    return out;
}

#endif //PENTAGON_HPP