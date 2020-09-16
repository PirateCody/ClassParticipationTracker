#include "Student.h"
#include "Rating.h"
#include <iostream>

using namespace std;

Student::Student(string fname, string lname)
{
	firstName = fname;
	lastName = lname;
}

int Student::getNumQuestions() const
{
	return numQuestions;
}

void Student::addRating(int selection) {
	switch (selection)
	{
	case ratings::EXCEPTIONAL: numExcept++; numQuestions++; break;
	case ratings::SATISFACTORY: numSatis++; numQuestions++; break;
	case ratings::UNSATISFACTORY: numUnsatis++; numQuestions++; break;
	case ratings::SKIPPED: numSkips++; numQuestions++; break;

	default:
		std::cerr << "Invalid selection: " << selection; break;
	}
}
