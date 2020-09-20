/*
Author: Cody Gentz
Date: 9/20/2020
Purpose: This file contains function definitions for the Course class. 

*/

#define _CRT_SECURE_NO_WARNINGS
#include "Course.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <map>

using namespace std;

const string Course::COURSE_START_MARKER = "###";

bool Course::checkForDuplicates()
{
    // a map is used to allow the program to check if a second instance of a name is in a list
    std::map<string, int> frequencyTable;

    // loops through the list of students
    for (int i = 0; i < studentList.size(); i++) {

        // result.second will return true if a name has been inserted a second time, meaning there is a duplicate
        auto result = frequencyTable.insert(pair<string, int>(studentList[i].getFullName(), 1));
        if (result.second == false) {
            return true;
        }


    }
    return false;
}

Student* Course::getRandomStudent()
{
    // gets a random number between 0 and the size of the list
    int randomIndex = rand() % studentList.size();

    return &studentList[randomIndex];
}

void Course::loadStudents(string fileName)
{
    int counter = 0; // a counter to make sure there aren't more than 50 students

    //line holds the line of input text
    string line;
    ifstream infile;
    infile.open(fileName);
    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            // because the file is formatted Firstname,Lastname the first name will be from the 0 index to the comma
            // and the last name will be from just after the comma (+1) to the end
            string fname = line.substr(0, line.find(","));
            string lname = line.substr(line.find(",")+1, line.length());

            studentList.push_back(Student(fname, lname));
            counter++;

            // resets the list and notifies the user if there are too many names
            if (counter > MAX_STUDENTS_PER_COURSE) {
                studentList.clear();
                cout << "Class list exceeds maximum number of students (50). " << endl;
                infile.close();
                break;
            }
            
        }
        infile.close();

        // checks that the list wasnt cleared & runs checkForDuplicates 
        // notifies the user and saves the course so it persists if the checkForDuplicates passes
        if (counter <= MAX_STUDENTS_PER_COURSE && !checkForDuplicates()) {
            cout << "Students loaded successfully!" << endl;
            saveCourse();
        }
        else {
            studentList.clear();
            cout << "Duplicates found" << endl;
        }
    }

    else cout << "Unable to open file" << endl;

    

}

void Course::listStudents()
{
    for (int i = 0; i < studentList.size(); i++) {
        cout << studentList[i].getFullName() << endl;
    }
}

void Course::saveTrackingSession()
{
    // time objects to get the current system date
    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);

    // the output file for the session of tracking
    // localTime variable gives the year since 1900, so we need to add 1900 to get the current year
    ofstream outfile;
    outfile.open(name + "_" + to_string((1900 + localTime->tm_year)) + "_" + to_string(localTime->tm_mon+1) + "_" + to_string(localTime->tm_mday) +".txt");

    // loops through the list of students and prints their name, the number of skips, and the various ratings
    if (outfile.is_open()) {
        outfile << name << endl;
        for (int i = 0; i < studentList.size(); i++) {
            outfile << studentList[i].getFirstName() << "," << studentList[i].getLastName() << ",";
            outfile << studentList[i].getNumSkips() << "," << studentList[i].getNumSatis() << "," << 
                studentList[i].getNumUnsatis() << "," << studentList[i].getNumExcept() << endl;
        }
    }

    outfile.close();

}

void Course::addStudent(string fname, string lname)
{
    studentList.push_back(Student(fname, lname));
}

void Course::saveCourse() {

    // the output file is called "courses.txt" and is opened in append mode
    // this is so new courses can be added to the end of the file and wont overwrite 
    // courses that already exist
    ofstream outfile;
    outfile.open("courses.txt", std::ios_base::app);

    if (outfile.is_open()) {

        // ### is an arbitrarily chosen marker to signify the beginning of a new course in the save file
        outfile << COURSE_START_MARKER << endl << name << endl;

        for (int i = 0; i < studentList.size(); i++) {
            outfile << studentList[i].getFirstName() << "," << studentList[i].getLastName() << endl;
        }

        outfile.close();
    }
}

int Course::getNumStudents() const
{
    return studentList.size();
}

std::string Course::getName() const
{
    return name;
}

Course::Course(std::string courseName)
{
    name = courseName;
}
