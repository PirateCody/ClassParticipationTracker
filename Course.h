#pragma once
#include <string>
#include <vector>
#include "Student.h"
class Course
{
private:
	std::string name;
	std::vector<Student> studentList;
	bool checkForDuplicates();
	bool comp(const Student &name1, const Student &name2);
public:
	Student* getRandomStudent();
	void loadStudents(std::string fileName);
	void listStudents();
	void saveTrackingSession();
	void addStudent(std::string fname, std::string lname);
	void saveCourse();
	int getNumStudents() const;
	std::string getName() const;
	Course(std::string courseName);

};

