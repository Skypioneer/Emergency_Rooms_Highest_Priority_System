// Jason Wang
// File: PatientPriorityQueuex.h
// Date: 11/01/2020
// Purpose: Define and implement the class PatientPriorityQueuex

#ifndef P3X_PATIENTPRIORITYQUEUEX_H
#define P3X_PATIENTPRIORITYQUEUEX_H
#include "Patient.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class PatientPriorityQueuex {

private:
    vector<Patient> patient;        // hold Class patient
    int nextPatientNumber;          // keep track of the last patient

    struct less_than_key {
        bool operator() (const Patient &obj1, const Patient &obj2 ){
            return (obj1.getArrivalOrder() < obj2.getArrivalOrder());
        }
    };

    void siftUp(unsigned);
    // Heapify up
    // Precondition: vectorSize
    // Postcondition: heapify up

    void siftDown(int);
    // Heapify down
    // Precondition: vectorSize
    // Postcondition: heapify down

    bool empty() const;
    // Check if vector is empty
    // Precondition: none
    // Postcondition: return boolean

    static int getParent(int);
    // Return parent index
    // Precondition: index
    // Postcondition: return parent index

    static int getLeftChild(int);
    // Return left kid index
    // Precondition: index
    // Postcondition: return left kid index

    static int getRightChild(int);
    // Return right kid index
    // Precondition: index
    // Postcondition: return right kid index

public:
    PatientPriorityQueuex();
    // Constructor
    // Precondition: none
    // Postcondition: initialize nextPatientNumber to 1

    void add(string &, string &);
    // Add the patient to the priority queue
    // Precondition: two references of string
    // Postcondition: add the patient to the priority queue

    string peek();
    // Returns the highest priority patient without removing it
    // Precondition: none
    // Postcondition: returns the highest priority patient without removing it

    string remove();
    // Return the highest priority patient from the queue and returns it
    // and then remove it.
    // Precondition: none
    // Postcondition: return the highest priority patient from the queue and
    //                returns it and then remove it.

    string change(int &, string &);
    // Return the patient's name whose priority code is changed
    // Precondition: two references of int and string
    // Postcondition: return the patient's name whose priority code is changed

    string save();
    // Return the string representation of the output patient list
    // Precondition: none
    // Postcondition: Return the string representation of the output
    //                patient list

    bool patientWithGivenNum(int &);
    // Return
    // Precondition: none
    // Postcondition:

    int size() const;
    // Return vectorSize
    // Precondition: none
    // Postcondition: return vectorSize

    string to_string();
    // Returns the string representation of the object in heap (or level) order
    // Precondition: none
    // Postcondition: Returns the string representation of the object in heap
    //                (or level) order
};

PatientPriorityQueuex::PatientPriorityQueuex() {
    nextPatientNumber = 1;
}

void PatientPriorityQueuex::add (string &priorityCode, string &name) {
    patient.push_back(Patient(nextPatientNumber, priorityCode, name));
    nextPatientNumber++;

    siftUp(patient.size() - 1);
}

string PatientPriorityQueuex::peek() {
    return patient[0].getName();
}

string PatientPriorityQueuex::remove() {
    //assert(!empty());
    if (empty())
        return "";

    string name = patient[0].getName();
    patient[0] = patient[patient.size() - 1];
    patient.pop_back();
    if (patient.size() > 1)
        siftDown(0);

    return name;
}

string PatientPriorityQueuex::change(int &arrival, string &newPriority) {
    int priorityNum, arrivalID = 0;     // hold new priority number and the
                                        // place where arrival order is in
                                        // the vector
    string patientName;                 // hold patient name

    while (patient[arrivalID].getArrivalOrder() != arrival){
        arrivalID++;
    }

    patientName = patient[arrivalID].getName();

    // transfer string priorityCode to int priorityCode
    if (newPriority == "immediate")
        priorityNum = 1;
    else if (newPriority == "emergency")
        priorityNum = 2;
    else if (newPriority == "urgent")
        priorityNum = 3;
    else
        priorityNum = 4;

    if (patient[arrivalID].getPriorityCode() > priorityNum) {
        patient[arrivalID].setPriorityCode(priorityNum);
        siftUp(arrivalID);
    }

    if (patient[arrivalID].getPriorityCode() < priorityNum) {
        patient[arrivalID].setPriorityCode(priorityNum);
        siftDown(0);
    }

    return patientName;
}

bool PatientPriorityQueuex::patientWithGivenNum(int & newArrival) {
    for (auto & i : patient){
        if (i.getArrivalOrder() == newArrival)
            return true;
    }

    return false;
}

string PatientPriorityQueuex::save() {
    stringstream ss;
    string priority;

    sort(patient.begin(),patient.end(),less_than_key());

    // transfer int priorityCode to string priorityCode
    for (auto & i : patient){
        if (i.getPriorityCode() == 1)
            priority = "immediate";
        else if (i.getPriorityCode() == 2)
            priority = "emergency";
        else if (i.getPriorityCode() == 3)
            priority = "urgent";
        else
            priority = "minimal";

        ss << "add " << priority << " " << i.getName() << endl;
    }

    return ss.str();
}

int PatientPriorityQueuex::size() const{
    return patient.size();
}

string PatientPriorityQueuex::to_string() {
    stringstream ss;            // hold representation of the object in heap

    for (auto & i : patient){
        ss << i.to_string();
    }
    return ss.str();
}

void PatientPriorityQueuex::siftUp(unsigned index) {
    int parentIdx;      // parent's index
    Patient tmp;        // temporary Class Patient

    // swap?
    if (index != 0) {
        parentIdx = getParent(index);
        if (patient[parentIdx] > patient[index]) {
            tmp = patient[parentIdx];
            patient[parentIdx] = patient[index];
            patient[index] = tmp;
            siftUp(parentIdx);
        }
    }
}

void PatientPriorityQueuex::siftDown(int index) {
    Patient tmp;                                // temporary Class Patient
    unsigned leftIdx, rightIdx, minIdx;         // indexes of left and right
    // kids and the min
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    // find minIdx
    if (rightIdx >= patient.size()) {
        if (leftIdx >= patient.size())
            return;
        else
            minIdx = leftIdx;
    } else {
        if (patient[leftIdx] < patient[rightIdx])
            minIdx = leftIdx;
        else
            minIdx = rightIdx;
    }

    // swap?
    if (patient[index] > patient[minIdx]) {
        tmp = patient[minIdx];
        patient[minIdx] = patient[index];
        patient[index] = tmp;
        siftDown(minIdx);
    }
}

bool PatientPriorityQueuex::empty() const {
    return patient.empty();
}

int PatientPriorityQueuex::getParent(int index) {
    return (index - 1) / 2;
}

int PatientPriorityQueuex::getLeftChild(int index) {
    return 2 * index + 1;
}

int PatientPriorityQueuex::getRightChild(int index) {
    return 2 * index + 2;
}

#endif //P3X_PATIENTPRIORITYQUEUE_H
