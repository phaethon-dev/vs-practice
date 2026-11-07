#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "students.h"

int main()
{
    const std::vector<Student> cls = {
        {"Maya", 85},
        {"Leo", 92},
        {"Ava", 70},
        {"Sam", 92},
        {"Zoe", 59},
    };

    // 1. Average
    assert(averageScore(cls) == 79.6);   // (85 + 92 + 70 + 92 + 59) / 5
    assert(averageScore({}) == 0.0);
    const std::vector<Student> pair = {{"Ana", 90}, {"Ben", 85}};
    assert(averageScore(pair) == 87.5);

    // 2. Passing
    assert(passingNames(cls, 70) == (std::vector<std::string>{"Maya", "Leo", "Ava", "Sam"}));
    assert(passingNames(cls, 100).empty());
    assert(passingNames({}, 50).empty());

    // 3. Ranking
    auto ranked = rankStudents(cls);
    assert(ranked.size() == 5);
    assert(ranked[0].name == "Leo");   // 92, and "Leo" comes before "Sam"
    assert(ranked[1].name == "Sam");   // 92
    assert(ranked[2].name == "Maya");  // 85
    assert(ranked[3].name == "Ava");   // 70
    assert(ranked[4].name == "Zoe");   // 59

    // The original list must be unchanged
    assert(cls[0].name == "Maya");

    std::cout << "All tests passed!\n";
    return 0;
}