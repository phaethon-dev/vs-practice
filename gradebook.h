#pragma once

#include <string>
#include <vector>
#include "students.h"

class Gradebook
{
public:
    explicit Gradebook(int passMark);

    // Adds a student if the name is non-empty and the score is 0-100.
    // Returns true if added, false if rejected.
    bool addStudent(const std::string &name, int score);

    int size() const;
    double average() const;
    std::vector<std::string> passingNames() const;
    std::vector<Student> ranked() const;

private:
    int passMark_;
    std::vector<Student> students_;
};