#pragma once
#include <string>
#include <vector>
#include "Student.h"
class Course
{
private:
	std::string name;
	std::vector<Student> studentList;
	void checkForDuplicates();
public:
	Student getRandomStudent();
	void loadStudents();

};

