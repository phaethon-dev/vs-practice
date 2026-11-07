#pragma once

#include <memory>
#include <string>
#include <vector>


class Shape{
    public:
        virtual ~Shape() = default;

        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual std::string name() const = 0;
};

class Circle : public Shape{
    public:
        explicit Circle(double radius);
        double area() const override;
        double perimeter() const override;
        std::string name() const override;

    private:
        double radius_;
};

class Rectangle : public Shape{
    public:
        Rectangle(double width, double height);
        double area() const override;
        double perimeter() const override;
        std::string name() const override;

    private:
        double width_;
        double height_;
};

class Square : public Rectangle{
    public:
        explicit Square(double side);
        std::string name() const override;
};

class Triangle : public Shape{
    public:
        Triangle(double a, double b, double c);
        double area() const override;
        double perimeter() const override;
        std::string name() const override;

    private:
        double a_;
        double b_;
        double c_;
};

double totalArea(const std::vector<std::unique_ptr<Shape>> &shapes);
const Shape *largest(const std::vector<std::unique_ptr<Shape>> &shapes);