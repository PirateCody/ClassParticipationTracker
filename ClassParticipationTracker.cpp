#include <iostream>
#include <string>
#include <vector>

#include "Course.h"

using namespace std;

int main()
{
    //Course course1;
    //course1.loadStudents();

    string command;
    string commandInput = "create ";
    string prefix = "Default> ";
    vector<Course> courses;
    Course* scope = nullptr;

    // read in courses

    while (true) {
        cout << prefix;
        getline(cin, commandInput);
        command = commandInput.substr(0, commandInput.find(" "));

        if (command.compare("create") == 0) {

            string courseName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
            courses.push_back(Course(courseName));

            prefix = courseName + "> ";

            scope = &courses.back();

            //cout << "Scope Get Name: " << scope->getName();
            cin.clear();


        }
        else if (command.compare("exit") == 0) {

            cout << "Exiting";
            return 0;

        }
        else if (command.compare("select") == 0) {
            string courseName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
            bool found = false;

            for (int i = 0; i < courses.size(); i++) {
                if (courses[i].getName().compare(courseName) == 0) {
                    scope = &courses[i];
                    prefix = scope->getName() + "> ";
                    found = true;
                }
            }

            if (found == false) {
                cout << courseName << " does not exist." << endl;
            }

        }
        else {
            cout << command << " is an invalid command" << endl;
        }
        cin.clear();
    }

}

