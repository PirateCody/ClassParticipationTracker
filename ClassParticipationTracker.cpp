#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>

#include "Course.h"

using namespace std;

void setPrefix(string pPrefix);

string command;
string commandInput = "";
string prefix = "Default> ";
vector<Course> courses;
Course* scope = nullptr;

void commandCreate() {
    string courseName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
    courses.push_back(Course(courseName));

    setPrefix(courseName);

    scope = &courses.back();

    //cout << "Scope Get Name: " << scope->getName();
    cin.clear();
}

void commandSelect() {
    string courseName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
    bool found = false;

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

void commandLoad() {
    if (scope != nullptr) {
        string fileName = commandInput.substr(commandInput.find(" ") + 1, commandInput.length());
        scope->loadStudents(fileName);
    }
    else {
        cout << "Must be configuring a class. Use 'select' or 'create' command." << endl;
    }
}

void commandList() {
    if (scope != nullptr) {
        scope->listStudents();
    }
    else {
        cout << "Must be configuring a class. Use 'select' or 'create' command." << endl;
    }
}

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
        if (stoi(ratingInput) == 4) {
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


int main()
{
    
    //load in courses that were created in a previous session
    string line;
    ifstream infile;
    infile.open("courses.txt");
    if (infile.is_open()) {
        while (getline(infile, line)) {
            if (line.compare("###") == 0) {
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

    while (true) {


        cout << prefix;
        getline(cin, commandInput);


        if (commandInput.find(" ")) {
            command = commandInput.substr(0, commandInput.find(" "));
        }
        else {
            command = commandInput;
        }


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

void setPrefix(string pPrefix) {
    prefix = pPrefix + "> ";
}
