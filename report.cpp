#include <iostream>
#include <iomanip>     // std::setw, std::fixed, std::setprecision: formatting
#include <string>
#include <vector>
#include <cassert>
#include "students.h"

void printReport(const std::vector<Student> &students, int passMark)
{
    std::cout << "Student Report\n";
    std::cout << "--------------\n";
    std::cout << std::left << std::setw(10) << "Name" << "Score\n";
    std::cout << "--------------\n";

    auto ranked = rankStudents(students);
    for (const auto &student : ranked){
        std::cout << std::left << std::setw(10) << student.name
                  << student.score
                  << (student.score >= passMark ? " (Pass)" : " (Fail)") << "\n";
    }

    double avg = averageScore(students);
    std::cout << "\nAverage Score: " << std::fixed << std::setprecision(2) << avg << "\n";

    auto passing = passingNames(students, passMark);
    std::cout << "Passing Students: ";
    if (passing.empty()){
        std::cout << "None";
    } else {
        for (size_t i = 0; i < passing.size(); ++i){
            std::cout << passing[i];
            if (i < passing.size() - 1){
                std::cout << ", ";
            }
        }
    }
    std::cout << "\n";
}

int main()
{
    auto students = loadStudents("students.txt");

    assert(students.size() == 5);
    assert(students[0].name == "Maya" && students[0].score == 85);
    assert(students[3].name == "Sam" && students[3].score == 92);
    assert(students[4].name == "Zoe" && students[4].score == 59);   // the valid Zoe line

    assert(loadStudents("does_not_exist.txt").empty());

    std::cout << "All tests passed!\n\n";

    printReport(students, 70);
    return 0;
}