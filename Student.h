#pragma once
#include <string>
class Student
{
private:
	std::string firstName;
	std::string lastName;
	int numSkips;
	int numExcept;
	int numSatis;
	int numUnsatis;
	int numQuestions;
public:
	Student(std::string fname, std::string lname);
	int getNumQuestions() const;
	void addRating(int selection);

};

