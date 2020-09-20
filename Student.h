/*
Author: Cody Gentz
Date: 9/20/2020
Purpose: This file contains the member variable and function signatures for the Student class. 
The Student class contains the student's first and last names, the number of ratings of each kind (exceptional, etc), 
the number of skips, and the number of questions (not including skipped questions). The behaviors for this class are
mainly data access functions and a function to add a rating.

*/

#pragma once
#include <string>
class Student
{
private:

	/* Student's first name */
	std::string firstName;

	/* Student's last name*/
	std::string lastName;

	/* Number of times the student has been skipped */
	int numSkips;

	/* Number of exceptional ratings */
	int numExcept;

	/* Number of satisfactory ratings */
	int numSatis;

	/* Number of unsatisfactory ratings */
	int numUnsatis;

	/* Number of questions, not including skips */
	int numQuestions;

public:

	/*
	Purpose: Constructor for student
	Param: string fname is students first name, string lname is students last name
	*/
	Student(std::string fname, std::string lname);

	/*
	Purpose: get the number of questions
	Return: int numQuestions
	*/
	int getNumQuestions() const;

	/*
	Purpose: get the number of skips
	Return: int numSkips
	*/
	int getNumSkips() const;

	/*
	Purpose: get the number of exceptional ratings
	Return: int numExcept
	*/
	int getNumExcept() const;

	/*
	Purpose: get the number of satisfactory ratings
	Return: int numSatis
	*/
	int getNumSatis() const;

	/*
	Purpose: get the number of unsatisfactory ratings
	Return: int numUnsatis
	*/
	int getNumUnsatis() const;

	/*
	Purpose: add a rating to a student
	Param: int selection is an int 0-3 to determine which rating to give
	*/
	void addRating(int selection);

	/*
	Purpose: get the full name of the student
	Return: string consisting of the First and Last name of the student with a space in between
	*/
	std::string getFullName() const;

	/*
	Purpose: get the first name of the student
	Return: string firstName
	*/
	std::string getFirstName() const;

	/*
	Purpose: get the last name of the student
	Return: string lastName
	*/
	std::string getLastName() const;

};

