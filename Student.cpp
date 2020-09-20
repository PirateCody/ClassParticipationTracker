#include "Student.h"
#include "Rating.h"
#include <iostream>

using namespace std;

Student::Student(string fname, string lname)
{
	firstName = fname;
	lastName = lname;
	numQuestions = 0;
	numExcept = 0;
	numSatis = 0;
	numUnsatis = 0;
	numSkips = 0;
}

int Student::getNumQuestions() const
{
	return numQuestions;
}

int Student::getNumSkips() const
{
	return numSkips;
}

int Student::getNumExcept() const
{
	return numExcept;
}

int Student::getNumSatis() const
{
	return numSatis;
}

int Student::getNumUnsatis() const
{
	return numUnsatis;
}

void Student::addRating(int selection) {
	switch (selection)
	{
	case ratings::EXCEPTIONAL: numExcept++; numQuestions++; break;
	case ratings::SATISFACTORY: numSatis++; numQuestions++; break;
	case ratings::UNSATISFACTORY: numUnsatis++; numQuestions++; break;
	case ratings::SKIPPED: numSkips++; break;

	default:
		std::cerr << "Invalid selection: " << selection << endl; break;
	}
}

std::string Student::getFirstName() const
{
	return firstName;
}

std::string Student::getLastName() const
{
	return lastName;
}

string Student::getFullName() const
{
	return firstName + " " + lastName;
}

