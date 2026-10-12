#ifndef RESERVATIONMANAGER_H_
#define RESERVATIONMANAGER_H_

#include <queue>
#include <string>

using namespace std;

struct Reservation{
    int studentID;
    string studentName;
    string resourceID;
    string reservationID;
    string reservationDate;

    Reservation(int id, string name, string resID, string date);
    Reservation(string id, int student, string name, string resID, string date);
    Reservation* next;
};

class ReservationList{
private:
    Reservation* head;

public:
    ReservationList();
    void addReservation(int id, string name, string resourceID, string date);
    void addReservation(string id, int student, string name, string resID,
                        string date);
    void displayReservations();
    void cancelReservation(string name);
    void searchReservations(int studentID);
    int countReservations(string resourceID);
    bool isReserved(string resourceID, string date);
};

struct WaitingRequest{
    string resourceID;
    string studentID;
    string studentName;

    WaitingRequest();
    WaitingRequest(string id, string name, string resID);
};

class WaitingList{
private:
    queue<WaitingRequest> waitingQueue;

public:
    void addStudent(string studentID, string studentName, string resourceID);
    int countWaiting(string resourceID);
    WaitingRequest removeNextStudent();
    void displayWaitingList();
    bool isEmpty();
};

void loadReservations(string filename, ReservationList& reservations);

#endif
