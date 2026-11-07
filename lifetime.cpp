#include <iostream>
#include <memory>
#include <string>

class Tracer
{
public:
    explicit Tracer(const std::string &name) : name_(name)
    {
        std::cout << "construct " << name_ << "\n";
    }

    Tracer(const Tracer &other) : name_(other.name_ + "-copy")
    {
        std::cout << "copy " << name_ << "\n";
    }

    ~Tracer()
    {
        std::cout << "destroy " << name_ << "\n";
    }

private:
    std::string name_;
};

void byReference(const Tracer &t)
{
    std::cout << "inside byReference\n";
}

void byValue(Tracer t)
{
    std::cout << "inside byValue\n";
}

int main()
{
    Tracer a("A");

    {
        Tracer b("B");
        std::cout << "end of inner block\n";
    }

    Tracer c = a;

    byReference(a);
    byValue(a);

    auto p = std::make_unique<Tracer>("D");
    p.reset();     // destroys the owned object right now

    std::cout << "end of main\n";
    return 0;
}