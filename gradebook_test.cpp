#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "gradebook.h"

int main()
{
    Gradebook gb(70);

    // Starts empty
    assert(gb.size() == 0);
    assert(gb.average() == 0.0);

    // Valid students
    assert(gb.addStudent("Maya", 85));
    assert(gb.addStudent("Leo", 92));
    assert(gb.addStudent("Ava", 70));
    assert(gb.addStudent("Sam", 92));
    assert(gb.addStudent("Zoe", 59));
    assert(gb.size() == 5);

    // Invalid students are rejected and NOT added
    assert(!gb.addStudent("Max", 101));
    assert(!gb.addStudent("Neg", -1));
    assert(!gb.addStudent("", 80));
    assert(gb.size() == 5);

    // Boundaries are valid
    Gradebook edges(50);
    assert(edges.addStudent("Low", 0));
    assert(edges.addStudent("High", 100));

    // Results
    assert(gb.average() == 79.6);
    assert(gb.passingNames() == (std::vector<std::string>{"Maya", "Leo", "Ava", "Sam"}));
    auto r = gb.ranked();
    assert(r[0].name == "Leo" && r[1].name == "Sam" && r[4].name == "Zoe");

    // const correctness: this only compiles if those functions are marked const
    const Gradebook &view = gb;
    assert(view.size() == 5);
    assert(view.average() == 79.6);

    // Encapsulation: uncomment this line, try to compile, read the error, then comment it out again
    //gb.students_.push_back({"Hacker", 1000});

    std::cout << "All tests passed!\n";
    return 0;
}