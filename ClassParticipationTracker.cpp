/*
Author: Cody Gentz
Date: 9/20/2020
Purpose: This file contains ties the different classes together and contains the main program loop. 
The definitions of the behavior of the various commands are contained here, as well as the mechanism to load
classes on start up. 

*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Course.h"

using namespace std;

// string commandInput is the raw container for input from the command line
// string command is a container for just the first word aka the command
string command;
string commandInput = "";

// a prefix is printed before accepting input to tell the user what course they are modifying
string prefix = "Default> ";

// a list of the courses
vector<Course> courses;

// a course pointer that keeps track of what course is currently being modified
Course* scope = nullptr;

// an integer for use during participation tracking. will end the tracking session
const int END_TRACKING_INT = 4;

/*
Purpose: formats and sets the prefix
Param: string pPrefix is the text of the prefix
*/
void setPrefix(string pPrefix) {
    prefix = pPrefix + "> ";
}

/*
Purpose: Creates a course, adds it to the list, and updates the scope
Command format: "create [course name]"
*/
void commandCreate() {

    // the course name is the second work in the input, so the element after the space to the end of the line
    string courseName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
    courses.push_back(Course(courseName));

    setPrefix(courseName);

    scope = &courses.back();

    cin.clear();
}

/*
Purpose: Selects a course that already exists in the list
Command format: "select [course name]"
*/
void commandSelect() {
    string courseName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
    bool found = false;

    // loops through the courses to find the selection, set the scope, and set the prefix
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i].getName().compare(courseName) == 0) {
            scope = &courses[i];
            setPrefix(scope->getName());
            found = true;
        }
    }

    if (found == false) {
        cout << courseName << " does not exist." << endl;
    }
}

/*
Purpose: Checks that there's a course being edited and runs the loadStudents function
Command format: "load [filename.csv]"
*/
void commandLoad() {
    if (scope != nullptr) {
        string fileName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
        scope->loadStudents(fileName);
    }
    else {
        cout << "Must be configuring a class. Use 'select' or 'create' command." << endl;
    }
}

/*
Purpose: lists the students in the selected course
*/
void commandList() {
    if (scope != nullptr) {
        scope->listStudents();
    }
    else {
        cout << "Must be configuring a class. Use 'select' or 'create' command." << endl;
    }
}

/*
Purpose: Starts participation tracking
*/
void commandTrack() {

    if (scope == nullptr) {
        cout << "You must first select or create a course and load students before tracking" << endl;
        return;
    }
    else if (scope->getNumStudents() == 0) {
        cout << "List of students has not been loaded for " << scope->getName() << endl;
        return;
    }


    bool tracking = true;
    string ratingInput;

    while (tracking) {
        //set the prefix to show we are tracking participation
        setPrefix(scope->getName() + ">Tracking");

        //choose a student
        Student* student = scope->getRandomStudent();

        //display name + question num
        cout << student->getFullName() << endl;
        cout << "Number of Questions: " << student->getNumQuestions() << endl;

        //wait for response from prof
        cout << "How do you rate? 0 = Exceptional, 1 = Satisfactory, 2 = Unsatisfactory, 3 = Skip, 4 = End Participation Tracking" << endl;
        cout << prefix;
        getline(cin, ratingInput);

        //record rating
        if (stoi(ratingInput) == END_TRACKING_INT) {
            tracking = false;
            setPrefix(scope->getName());
            scope->saveTrackingSession();
        }
        else {
            student->addRating(stoi(ratingInput));
        }

        cin.clear();


    }
}

/*
Purpose: Display the help message
*/
void commandHelp() {

    cout << "Commands: " << endl;
    cout << "create [class name] - creates a class with the given name" << endl;
    cout << "select [class name] - selects a class with the name, if it exists" << endl;
    cout << "load [filename.extension] - loads a list of students into the selected course" << endl;
    cout << "list - lists the names of all students in the course" << endl;
    cout << "track - starts a participation tracking session for the selected course" << endl;
    cout << "help - displays this help message" << endl;
    cout << "exit - exits the program" << endl;

}

/*
Purpose: loads courses that were created in previous sessions
*/
void loadCourses() {
    //load in courses that were created in a previous session
    string line;
    ifstream infile;
    infile.open("courses.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {

            // looks for the ### tag, if it's found, it gets the next line and creates a course
            // after creating a course, it will proceed down the list and create students until it reaches the next course
            if (line.compare(Course::COURSE_START_MARKER) == 0) {
                getline(infile, line);
                courses.push_back(Course(line));
            }
            else {
                string fname = line.substr(0, line.find(","));
                string lname = line.substr(line.find(",") + 1, line.length());

                courses.back().addStudent(fname, lname);
            }
        }

        infile.close();

    }
}

int main()
{
    
    cout << "Class Participation Tracker for CS-358 by Cody Gentz" << endl << "Use command help for a list of commands" << endl;

    loadCourses();

    while (true) {

        cout << prefix;
        getline(cin, commandInput);

        // isolates the command, if there's more than 1 word in the input
        if (commandInput.find(" ")) {
            command = commandInput.substr(0, commandInput.find(" "));
        }
        else {
            command = commandInput;
        }

        // determines which command was entered and does the appropriate command
        if (command.compare("create") == 0) {
            commandCreate();
        }
        else if (command.compare("select") == 0) {
            commandSelect();
        }
        else if(command.compare("load") == 0) {
            commandLoad();
        }
        else if (command.compare("list") == 0) {
            commandList();
        }
        else if (command.compare("help") == 0) {
            commandHelp();
        }
        else if (command.compare("track") == 0) {
            commandTrack();
        }
        else if (command.compare("exit") == 0) {
            cout << "Exiting" << endl;;
            return 0;
        }
        else {
            cout << command << " is an invalid command" << endl;
        }

        cin.clear();
    }

}


