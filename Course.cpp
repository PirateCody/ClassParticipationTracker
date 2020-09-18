#include "Course.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Course::loadStudents()
{
    string line;
    ifstream myfile("example.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            //studentList.push_back(Student());

            
        }
        myfile.close();
    }

    else cout << "Unable to open file";
}

std::string Course::getName() const
{
    return name;
}

Course::Course(std::string courseName)
{
    name = courseName;
}
