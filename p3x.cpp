// Jason Wang
// File: p3x.cpp
// Date: 11/01/2020
// Purpose: The program is a priority queue system for a hospital emergency
//          room. The triage nurse will determine the patient's priority based
//          on their injury or illness and enter the patient's full name along
//          with the urgency level based on the priority code to indicate the
//          priority.

#include "PatientPriorityQueuex.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueuex &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueuex &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueuex &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueuex &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueuex &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueuex &);
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

void changePriorityCode(string, PatientPriorityQueuex &);
// Change a patient's priority code

void savePatientList(string&, PatientPriorityQueuex &);
// Output patient list

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.

int main() {
    // declare variables
    string line;

    // welcome message
    welcome();

    // process commands
    PatientPriorityQueuex priQueue;
    do {
        cout << "\ntriage> ";
        getline(cin, line);
    } while (processLine(line, priQueue));

    // goodbye message
    goodbye();
}

bool processLine(string line, PatientPriorityQueuex &priQueue) {
    line = line + " ";      // avoid crash in changePriorityCode function

    // get command
    string cmd = delimitBySpace(line);
    if (cmd.length() == 0) {
        cout << "Error: no command given.";
        return false;
    }

    // process user input
    if (cmd == "help")
        help();
    else if (cmd == "add")
        addPatientCmd(line, priQueue);
    else if (cmd == "peek")
        peekNextCmd(priQueue);
    else if (cmd == "next")
        removePatientCmd(priQueue);
    else if (cmd == "list")
        showPatientListCmd(priQueue);
    else if (cmd == "load")
        execCommandsFromFileCmd(line, priQueue);
    else if(cmd == "change")
        changePriorityCode(line, priQueue);
    else if (cmd == "save")
        savePatientList(line,priQueue);
    else if (cmd == "quit")
        return false;
    else
        cout << "Error: unrecognized command: " << cmd << endl;

    return true;
}

void addPatientCmd(string line, PatientPriorityQueuex &priQueue) {
    string priority, name;
    int i = 0;

    // remove leading spaces
    while (isspace(line[i])){
        line = line.substr(i + 1);
    }

    // get priority and name
    priority = delimitBySpace(line);
    if (priority.length() == 0) {
        cout << "Error: no priority code given.\n";
        return;
    }

    // remove leading spaces
    while (isspace(line[i])){
        line = line.substr(i + 1);
    }

    // remove trailing spaces
    for (unsigned k = line.size() - 1; isspace(line[k]); k--)
        line = line.substr(0, k);

    name = line;
    if (name.length() == 0) {
        cout << "Error: no patient name given.\n";
        return;
    }

    if (priority == "immediate" || priority == "emergency" ||
        priority == "urgent" || priority == "minimal") {
        priQueue.add(priority, name);
        cout << "Added patient \"" << name <<"\" to the priority system\n";
    }
    else{
        cout << "Error: not a valid priority code.\n";
    }
}

void peekNextCmd(PatientPriorityQueuex &priQueue) {
    if (priQueue.size() != 0){
        cout << "Highest priority patient to be called next: "
             << priQueue.peek() << endl;
    } else
        cout << "There are no patients in the waiting area.\n";
}

void removePatientCmd(PatientPriorityQueuex &priQueue) {
    if(priQueue.size() != 0){
        cout << "This patient will now be seen: " << priQueue.remove() << endl;
    }
    else
        cout << "There are no patients in the waiting area.\n";

}

void showPatientListCmd(PatientPriorityQueuex &priQueue) {
    cout << "# patients waiting: " << priQueue.size() << endl << endl;
    cout << "  Arrival #   Priority Code   Patient Name\n"
         << "+-----------+---------------+--------------+\n";
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueuex &priQueue) {
    ifstream infile;
    string line;

    // remove trailing spaces
    for (unsigned k = filename.size() - 1; isspace(filename[k]); k--)
        filename = filename.substr(0, k);

    // open and read from file
    infile.open(filename);
    if (infile) {
        while (getline(infile, line)) {
            cout << "\ntriage> " << line << endl;
            // process file input
            processLine(line, priQueue);
        }
    } else {
        cout << "Error: could not open file.\n";
    }
    // close file
    infile.close();
}

void changePriorityCode(string line, PatientPriorityQueuex &priQueue){
    string priority, arrival;       // hold  priority code and arrival order
    int i = 0;                      // control variable

    // remove leading spaces
    while (isspace(line[i]))
        line = line.substr(i + 1);


    // get priority and name
    arrival = delimitBySpace(line);
    if (arrival.length() == 0) {
        cout << "Error: No patient id provided\n";
        return;
    }

    // convert arrival from string to int
    int numArrival = stoi(arrival);

    if(!priQueue.patientWithGivenNum(numArrival)){
        cout << "Error: no patient with the given id was found\n";
        return;
    }

    // remove leading spaces
    while (isspace(line[i]))
        line = line.substr(i + 1);

    priority = line;
    if (priority.length() == 0) {
        cout << "Error: No priority code given.\n";
        return;
    }

    // remove trailing spaces
    for (unsigned k = priority.size() - 1; isspace(priority[k]); k--)
        priority = priority.substr(0, k);

    // add priority code
    if (priority == "immediate" || priority == "emergency" ||
        priority == "urgent" || priority == "minimal") {
        cout << "Changed patient \"" <<
             priQueue.change(numArrival, priority) << "\"'s priority to "
             << priority << endl;
    }
    else{
        cout << "Error: not a valid priority code.\n";
    }
}

void savePatientList(string& file, PatientPriorityQueuex &priQueue){
    int i = 1;      // control variable

    // remove leading and trailing spaces
    while (isspace(file[i]))
        file = file.substr(i + 1);
    for (unsigned k = file.size() - 1; isspace(file[k]); k--)
        file = file.substr(0, k);

    ofstream outputFile (file);

    // output file
    if(outputFile.is_open()){
        outputFile << priQueue.save();
        cout << "Save " << priQueue.size() << " patient(s) to file "
             << file << endl;
    }else
        cout << "Unable to open file" << endl;

    // close outputFile
    outputFile.close();
}

string delimitBySpace(string &s) {
    unsigned pos = 0;
    char delimiter = ' ';
    string result = "";

    pos = s.find(delimiter);
    if (pos != string::npos) {
        result = s.substr(0, pos);
        s.erase(0, pos + 1);
    }
    return result;
}

void welcome() {
    cout << "Welcome to use priority queue system." << endl <<
    "The program is a priority queue system for a hospital emergency\n"
    "room. The triage nurse will determine the patient's priority based\n"
    "on their injury or illness and enter the patient's full name along\n"
    "with the urgency level based on the priority code to indicate the\n"
    "priority." << endl;
}

void goodbye() {
    cout << "\nThanks for using priority queue system." << endl;
}

void help() {
    cout << "add <priority-code> <patient-name>\n"
         << "            Adds the patient to the triage system.\n"
         << "            <priority-code> must be one of the 4 accepted priority"
            " codes:\n"
         << "                1. immediate 2. emergency 3. urgent 4. minimal\n"
         << "            <patient-name>: patient's full legal name (may contain"
            " spaces)\n"
         << "next        Announces the patient to be seen next. Takes into"
            " account the\n"
         << "            type of emergency and the patient's arrival order.\n"
         << "peek        Displays the patient that is next in line, but keeps"
            " in queue\n"
         << "list        Displays the list of all patients that are still"
            " waiting\n"
         << "            in the order that they have arrived.\n"
         << "load <file> Reads the file and executes the command on each"
            " line\n"
         << "help        Displays this menu\n"
         << "save        OutPut patient list\n"
         << "quit        Exits the program\n";
}