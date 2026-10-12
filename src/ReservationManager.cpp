#include "ReservationManager.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

Reservation::Reservation(int id, string name, string resID, string date){
    studentID = id;
    studentName = name;
    resourceID = resID;
    reservationID = "";
    reservationDate = date;
    next = nullptr;
}

Reservation::Reservation(string id, int student, string name, string resID,
                         string date){
    reservationID = id;
    studentID = student;
    studentName = name;
    resourceID = resID;
    reservationDate = date;
    next = nullptr;
}

ReservationList::ReservationList(){
    head = nullptr;
}

void ReservationList::addReservation(int id, string name, string resourceID, string date){
    Reservation* newReservation = new Reservation(id, name, resourceID, date);

    if (head == nullptr){
        head = newReservation;
    }
    else{
        Reservation* temp = head;

        while (temp->next != nullptr){
            temp = temp->next;
        }

        temp->next = newReservation;
    }

    cout << "Reservation added successfully." << endl;
}

void ReservationList::addReservation(string id, int student, string name,
                                     string resID, string date){
    Reservation* newReservation =
        new Reservation(id, student, name, resID, date);

    if (head == nullptr){
        head = newReservation;
    }
    else{
        Reservation* temp = head;

        while (temp->next != nullptr){
            temp = temp->next;
        }

        temp->next = newReservation;
    }
}

void ReservationList::displayReservations(){
    Reservation* temp = head;

    if (temp == nullptr){
        cout << "There are no reservations." << endl;
    }
    else{
        cout << "Reservations:" << endl;

        while (temp != nullptr){
            cout << temp->reservationID << " | "
                 << temp->studentID << " | "
                 << temp->studentName << " | "
                 << temp->resourceID << " | "
                 << temp->reservationDate << endl;

            temp = temp->next;
        }
    }
}

void ReservationList::cancelReservation(string name){
    if (head == nullptr){
        cout << "Reservation list is empty." << endl;
        return;
    }
    
    if (head->studentName == name){
        Reservation* temp = head;
        head = head->next;
        delete temp;
        cout << "Reservation cancelled successfully." << endl;
        return;
    }

    Reservation* current = head;
    Reservation* previous = nullptr;

    while (current!=nullptr && current->studentName!=name){
        previous = current;
        current = current->next;
    }

    if (current==nullptr){
        cout << "Reservation under that name not found." << endl;
        return;
    }

    previous->next = current->next;
    delete current;
    cout << "Reservation cancelled successfully." << endl;
}

void loadReservations(string filename, ReservationList& reservations){
    ifstream inputFile(filename);

    if (!inputFile.is_open()){
        cout << "Error: Could not open " << filename << endl;
        return;
    }

    string line;

    while (getline(inputFile, line)){
        stringstream ss(line);
        string reservationID;
        string studentID;
        string studentName;
        string resourceID;
        string reservationDate;

        getline(ss, reservationID, '|');
        getline(ss, studentID, '|');
        getline(ss, studentName, '|');
        getline(ss, resourceID, '|');
        getline(ss, reservationDate);

        reservations.addReservation(
            reservationID,
            stoi(studentID),
            studentName,
            resourceID,
            reservationDate
        );
    }

    inputFile.close();
}

WaitingRequest::WaitingRequest(){
    studentID = "";
    studentName = "";
}

WaitingRequest::WaitingRequest(string id, string name){
    studentID = id;
    studentName = name;
}

void WaitingList::addStudent(string studentID, string studentName){
    WaitingRequest request(studentID, studentName);
    waitingQueue.push(request);
}

WaitingRequest WaitingList::removeNextStudent(){
    if (waitingQueue.empty()){
        cout << "Waiting list is empty." << endl;
        return WaitingRequest();
    }

    WaitingRequest student = waitingQueue.front();
    waitingQueue.pop();
    return student;
}

void WaitingList::displayWaitingList(){
    if (waitingQueue.empty()){
        cout << "Waiting list is empty." << endl;
        return;
    }

    queue<WaitingRequest> remainingRequests = waitingQueue;
    int position = 1;

    while (!remainingRequests.empty()){
        WaitingRequest student = remainingRequests.front();

        cout << position << ". "
             << student.studentName
             << " ("
             << student.studentID
             << ")"
             << endl;

        remainingRequests.pop();
        position++;
    }
}

bool WaitingList::isEmpty(){
    return waitingQueue.empty();
}
