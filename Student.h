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
	int getNumSkips() const;
	int getNumExcept() const;
	int getNumSatis() const;
	int getNumUnsatis() const;
	void addRating(int selection);
	std::string getFullName() const;
	std::string getFirstName() const;
	std::string getLastName() const;

};

