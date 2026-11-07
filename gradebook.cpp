#include "gradebook.h"

Gradebook::Gradebook(int passMark) : passMark_(passMark)
{
}

// Adds a student if the name is non-empty and the score is 0-100.
// Returns true if added, false if rejected.
bool Gradebook::addStudent(const std::string &name, int score)
{
    if (name.empty() || score < 0 || score > 100)
    {
        return false;
    }
    students_.push_back({name, score});
    return true;
}

int Gradebook::size() const
{
    return static_cast<int>(students_.size());
}

double Gradebook::average() const
{
    return averageScore(students_);
}

std::vector<std::string> Gradebook::passingNames() const
{
    return ::passingNames(students_, passMark_);
}

std::vector<Student> Gradebook::ranked() const
{
    return ::rankStudents(students_);
}
