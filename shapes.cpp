#include "shapes.h"

#include <cmath>

constexpr double PI = 3.14159265358979323846;

Circle::Circle(double radius) : radius_(radius) {}

double Circle::area() const {
    return PI * radius_ * radius_;
}

double Circle::perimeter() const {
    return 2 * PI * radius_;
}

std::string Circle::name() const {
    return "Circle";
}

Rectangle::Rectangle(double width, double height) : width_(width), height_(height) {}

double Rectangle::area() const {
    return width_ * height_;
}

double Rectangle::perimeter() const {
    return 2 * (width_ + height_);
}

std::string Rectangle::name() const {
    return "Rectangle";
}

Square::Square(double side) : Rectangle(side, side) {}

std::string Square::name() const {
    return "Square";
}

Triangle::Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}

double Triangle::area() const {
    double s = (a_ + b_ + c_) / 2;
    return std::sqrt(s * (s - a_) * (s - b_) * (s - c_));
}

double Triangle::perimeter() const {
    return a_ + b_ + c_;
}

std::string Triangle::name() const {
    return "Triangle";
}

double totalArea(const std::vector<std::unique_ptr<Shape>> &shapes) {
    double total = 0.0;
    for (const auto &shape : shapes) {
        total += shape->area();
    }
    return total;
}

const Shape *largest(const std::vector<std::unique_ptr<Shape>> &shapes) {
    if (shapes.empty()) {
        return nullptr;
    }

    const Shape *largestShape = shapes[0].get();
    for (const auto &shape : shapes) {
        if (shape->area() > largestShape->area()) {
            largestShape = shape.get();
        }
    }
    return largestShape;
}