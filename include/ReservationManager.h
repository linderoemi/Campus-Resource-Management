#ifndef RESERVATIONMANAGER_H_
#define RESERVATIONMANAGER_H_

//single reservation node
struct Reservation{
    int studentID;
    string studentName;
    string resourceID;

    Reservation(int id, string name, string resID);
    Reservation* next;

};

//Linked list to store all reservations
class ReservationList{
    private:
        Reservation* head;
    
    public:
        ReservationList();
        void addReservation(int id, string name, string resID);
        void displayReservations();
};

#endif
