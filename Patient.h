// Jason Wang
// File: Patient.h
// Date: 11/01/2020
// Purpose: Define and implement the class Patient

#ifndef P3X_PATIENT_H
#define P3X_PATIENT_H
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

class Patient {
private:
    string name;            // patient's name
    int priorityCode;       // patient's priority code
    int arrivalOrder;       // patient's arrival order

public:
    Patient();
    // Constructor
    // Precondition: none
    // Postcondition: initialize name to null, and priorityCode and
    //                arrivalOrder to zero

    Patient (int, string &, string &);
    // Constructor
    // Precondition: receive int and two references of string
    // Postcondition: allocate parameters to local variable and transfer string
    //                priorityCode to int one

    bool operator > (const Patient &) const;
    // Overloaded >
    // Precondition: a reference of Class Patient
    // Postcondition: determine if local class is larger than the foreign

    bool operator < (const Patient &) const;
    // Overloaded <
    // Precondition: a reference of Class Patient
    // Postcondition: determine if local class is smaller than the foreign

    string getName();
    // Return a patient name
    // Precondition: none
    // Postcondition: return a patient name

    int getPriorityCode() const;
    // Return a priority priority code
    // Precondition: none
    // Postcondition: return a patient name

    int getArrivalOrder() const;
    // Return a arrival order
    // Precondition: none
    // Postcondition: return a patient name

    string to_string();
    // Return the string representation of the object in heap (or level) order
    // Precondition: none
    // Postcondition: Return the string representation of the object in heap
    //                (or level) order


    void setPriorityCode(int &);
    // Reset priority code
    // Precondition: a reference of int
    // Postcondition: reset priority code
};

Patient::Patient() {
    name = "";              // initialized name
    priorityCode = 0;       // initialized priorityCode to 0
    arrivalOrder = 0;       // initialized arrivalOrder to 0
}

Patient::Patient(int arrivalOrder, string &priorityCode, string &name) {
    this->name = name;
    this->arrivalOrder = arrivalOrder;

    // transfer string priorityCode to int priorityCode
    if (priorityCode == "immediate")
        this->priorityCode = 1;
    else if (priorityCode == "emergency")
        this->priorityCode = 2;
    else if (priorityCode == "urgent")
        this->priorityCode = 3;
    else
        this->priorityCode = 4;
}

bool Patient::operator > (const Patient &patient) const {
    if (priorityCode > patient.priorityCode) {
        return true;
    }
    else if(priorityCode == patient.priorityCode && arrivalOrder >
                                                    patient.arrivalOrder) {
        return true;
    }

    return false;
}

bool Patient::operator < (const Patient &patient) const {
    if(priorityCode < patient.priorityCode) {
        return true;
    }
    else if(priorityCode == patient.priorityCode && arrivalOrder <
                                                    patient.arrivalOrder) {
        return true;
    }

    return false;
}

string Patient::getName() {
    return name;
}

int Patient::getPriorityCode() const {
    return priorityCode;
}

int Patient::getArrivalOrder() const {
    return arrivalOrder;
}

void Patient::setPriorityCode(int & priority) {
    this->priorityCode = priority;
}

string Patient::to_string() {
    stringstream ss;            // to hold returned statement
    string priority;            // to hold string priority code

    // transfer int priorityCode to string priorityCode
    if (priorityCode == 1)
        priority = "immediate";
    else if (priorityCode == 2)
        priority = "emergency";
    else if (priorityCode == 3)
        priority = "urgent";
    else
        priority = "minimal";

    ss << setw(7) << arrivalOrder << "       " << left << setw(16)
       << priority << name << "\n";

    return ss.str();
}

#endif //P3X_PATIENT_H
