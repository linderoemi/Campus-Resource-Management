#include<iostream>
#include <string>
#include "ReservationManager.h"
using namespace std;

Reservation::Reservation(int id, string name, string resID) {
    studentID = id;
    studentName = name;
    resourceID = resID;
    next = nullptr;
}

ReservationList::ReservationList(){
    head = nullptr;
}

void ReservationList::addReservation(int id, string name, string resID){
    Reservation* newReservation = new Reservation(id, name, resID);
    if(head == nullptr){
        head = newReservation;
    }
    else{
        Reservation* temp = head;
        while(temp->next != nullptr){
            temp = temp->next;
        }
        temp->next = newReservation;
    }

}

void ReservationList::displayReservations(){
    Reservation* temp = head;
    if(temp == nullptr){
        cout << "There are no reservations." << endl;
    }
    else{
        cout << "Reservations: " << endl;
        while(temp != nullptr){
            cout << "Student ID: " << temp->studentID << "| Student Name: " << temp->studentName << "| Resource ID: " << temp->resourceID << endl;
            temp = temp->next;
        }
    }
}