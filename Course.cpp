/*
TODO
1) Add more input protections/validation (esp. on load command)
2) Comment files with author, date, purpose, etc
3) Comment every method with purpose, params, etc
4) Comment the logic of every method & elsewhere
5) Fix styling
6) Verify everything is working to the spec & check rubric



*/












#define _CRT_SECURE_NO_WARNINGS
#include "Course.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <map>

using namespace std;

bool Course::checkForDuplicates()
{

    std::map<string, int> frequencyTable;

    for (int i = 0; i < studentList.size(); i++) {


        auto result = frequencyTable.insert(pair<string, int>(studentList[i].getFullName(), 1));
        if (result.second == false) {
            return true;
        }


    }
    return false;
}

Student* Course::getRandomStudent()
{

    int randomIndex = rand() % studentList.size();

    return &studentList[randomIndex];
}

void Course::loadStudents(string fileName)
{
    int counter = 0;
    string line;
    ifstream infile;
    infile.open(fileName);
    if (infile.is_open())
    {
        while (getline(infile, line))
        {

            string fname = line.substr(0, line.find(","));
            string lname = line.substr(line.find(",")+1, line.length());

            studentList.push_back(Student(fname, lname));
            counter++;

            if (counter > 50) {
                studentList.clear();
                cout << "Class list exceeds maximum number of students (50). " << endl;
                infile.close();
                break;
            }
            
        }
        infile.close();

        if (counter <= 50 && !checkForDuplicates()) {
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

    time_t currentTime = time(0);
    tm* localTime = localtime(&currentTime);

    ofstream outfile;
    outfile.open(name + "_" + to_string((1900 + localTime->tm_year)) + "_" + to_string(localTime->tm_mon) + "_" + to_string(localTime->tm_mday) +".txt");

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
    ofstream outfile;
    outfile.open("courses.txt", std::ios_base::app);

    if (outfile.is_open()) {
        outfile << "###" << endl << name << endl;

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
