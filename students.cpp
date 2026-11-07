#include "students.h"

#include <algorithm>
#include <fstream>
#include <sstream>

double averageScore(const std::vector<Student> &students)
{
    if (students.empty()){
        return 0.0;
    }
    int total = 0;
    for (const auto &student : students){
        total += student.score;
    }
    return static_cast<double>(total) / students.size();
}

std::vector<std::string> passingNames(const std::vector<Student> &students, int passMark)
{
    std::vector<std::string> names;
    for (const auto &student : students){
        if (student.score >= passMark){
            names.push_back(student.name);
        }
    }
    return names;
}

std::vector<Student> rankStudents(std::vector<Student> students)
{
    std::sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        if (a.score != b.score){
            return a.score > b.score;  // higher score first
        }
        return a.name < b.name;  // alphabetical order for ties
    });
    return students;
}

std::vector<Student> loadStudents(const std::string &path)
{
    std::vector<Student> students;

    std::ifstream file(path);
    if (!file.is_open()){
        return students;  // return empty vector if file cannot be opened
    }
    std::string line;
    while (std::getline(file, line)){
        std::istringstream iss(line);
        std::string name;
        int score;
        if (iss >> name >> score){
            students.push_back({name, score});
        }
    }

    return students;
}
 