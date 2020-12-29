#ifndef RHOMBUS_HPP
#define RHOMBUS_HPP

#include "figure.hpp"

class Rhombus : public Figure {
public:
    Rhombus() = default;

    Rhombus(std::pair<double, double>& center, double d1, double d2) : Figure(center), diag1(d1), diag2(d2) {}

    double Area() override {
        return diag1 * diag2 * 0.5;
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

    friend std::ostream& operator<<(std::ostream& out, Rhombus& r);

private:
    double diag1 = 0;
    double diag2 = 0;
};

std::ostream& operator<<(std::ostream& out, Rhombus& r) {
    out << "\nRhombus:\n";
    out << "1. Coordinates: (";
    out << r.center.first + r.diag1 * 0.5 << "; " << r.center.second << "), (";
    out << r.center.first << "; " << r.center.second + r.diag2 * 0.5 << "), (";
    out << r.center.first - r.diag1 * 0.5 << "; " << r.center.second << "), (";
    out << r.center.first << "; " << r.center.second - r.diag2 * 0.5 << ")";
    return out;
}

#endif //RHOMBUS_HPP