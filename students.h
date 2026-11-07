#pragma once

#include <string>
#include <vector>

struct Student
{
    std::string name;
    int score;
};

double averageScore(const std::vector<Student> &students);
std::vector<std::string> passingNames(const std::vector<Student> &students, int passMark);
std::vector<Student> rankStudents(std::vector<Student> students);
std::vector<Student> loadStudents(const std::string &path);