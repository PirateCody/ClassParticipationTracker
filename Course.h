/*
Author: Cody Gentz
Date: 9/20/2020
Purpose: This file contains the member variable and function signatures for the Course class. 
The Course class contains a course name, a list of students, and behaviors to access and manipulate this data. 

*/

#pragma once
#include <string>
#include <vector>
#include "Student.h"
class Course
{
private:

	/* Name of the course */
	std::string name;

	/* A vector of student objects that serves as the list of students in the course */
	std::vector<Student> studentList;

	/*
	Purpose: This function determines if there are duplicate students in a course
	Return: true if there are duplicates, false if there are not
	*/
	bool checkForDuplicates();

public:
	/*
	Purpose: Constructor that creates a course object
	Param: string courseName is the desired name of the course
	*/
	Course(std::string courseName);

	/*
	Purpose: Randomly picks a student from the list of students in the course
	Return: returns a pointer to the student object that was randomly selected
	*/
	Student* getRandomStudent();

	/*
	Purpose: Loads a comma delimited file of names into a course, creating a student object for each name in the list of students
	*/
	void loadStudents(std::string fileName);

	/*
	Purpose: prints the names of all of the students in a course to the screen
	*/
	void listStudents();

	/*
	Purpose: Saves the data from a participation tracking session to a file. Specifically, the Student names, and the number of skips and number of ratings
	*/
	void saveTrackingSession();

	/*
	Purpose: Adds a student to the student list
	Param: string fname is the first name, string lname is the last name
	*/
	void addStudent(std::string fname, std::string lname);

	/*
	Purpose: Saves the course information (name and student names) to a file called "courses.txt". The program reads this file in on start up so that classes persist
	*/
	void saveCourse();

	/*
	Purpose: retrieve the number of students in a course
	Return: number of students in studentList
	*/
	int getNumStudents() const;

	/*
	Purpose: retrieve the name of the course
	Return: name of the course
	*/
	std::string getName() const;

	/* Maximum number of students in a course */
	const int MAX_STUDENTS_PER_COURSE = 50;

	/* A marker for use in the save files that denotes when a new course is being described */
	static const std::string COURSE_START_MARKER;
};

