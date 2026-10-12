#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>

#include "Resource.h"
#include "Reservation.h"
#include "ReservationManager.h"

using namespace std;


vector<Resource> loadResources(string filename)
{
    vector<Resource> resources;

    ifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        cout << "Error: Could not open " << filename << endl;
        return resources;
    }

    string line;

    while (getline(inputFile, line))
    {
        stringstream ss(line);

        string id;
        string name;
        string type;
        string status;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status, '|');

        if (id.empty() || name.empty() || type.empty()
            || (status != "Available" && status != "Unavailable")){
            cout << "Skipping invalid resource record." << endl;
            continue;
        }
        Resource newResource(id, name, type, status);
        resources.push_back(newResource);
    }

    inputFile.close();

    return resources;
}


void viewResources(vector<Resource>& resources)
{
    cout << endl;
    cout << "===== Resources =====" << endl;

    if (resources.empty())
    {
        cout << "No resources available." << endl;
        return;
    }

    cout << endl;
    cout << "Resource ID | Resource Name | Resource Type | Availability" << endl;
    cout << "----------------------------------------------------------" << endl;

    for (size_t i = 0; i < resources.size(); i++)
    {
        resources[i].displayResource();
    }
}


//assure correct inputs 
bool readNumber(int& number)
{
    string line;
    if (!getline(cin, line)){
        return false;
    }
    stringstream ss(line);
    char extra;
    if (!(ss >> number) || (ss >> extra)){
        cout << "Invalid number." << endl;
        return false;
    }
    return true;
}

bool validDate(string date)
{
    if (date.size() != 10 || date[2] != '/' || date[5] != '/'){
        return false;
    }
    for (int i = 0; i < 10; i++){
        if (i != 2 && i != 5 && (date[i] < '0' || date[i] > '9')){
            return false;
        }
    }
    int month = stoi(date.substr(0, 2));
    int day = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));
    if (month < 1 || month > 12 || year < 1){
        return false;
    }
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)){
        days[1] = 29;
    }
    return day >= 1 && day <= days[month - 1];
}

// Linear search for a resource ID.
int findResource(vector<Resource>& resources, string id)
{
    for (size_t i = 0; i < resources.size(); i++){
        if (resources[i].getresourceID() == id){
            return (int)i;
        }
    }
    return -1;
}

string sortValue(Resource& resource, int choice)
{
    if (choice == 1){
        return resource.getresourceID();
    }
    else if (choice == 2){
        return resource.getresourceName();
    }
    else if (choice == 3){
        return resource.getresourceType();
    }
    return resource.getavailabilityStatus();
}



void mergeResources(vector<Resource>& resources, int left, int middle, int right, int choice)
{
    vector<Resource> merged;
    int i = left;
    int j = middle + 1;
    while (i <= middle && j <= right){
        if (sortValue(resources[i], choice) <= sortValue(resources[j], choice)){
            merged.push_back(resources[i]);
            i++;
        }
        else{
            merged.push_back(resources[j]);
            j++;
        }
    }
    while (i <= middle){
        merged.push_back(resources[i]);
        i++;
    }
    while (j <= right){
        merged.push_back(resources[j]);
        j++;
    }
    for (size_t k = 0; k < merged.size(); k++){
        resources[left + k] = merged[k];
    }

}

void mergeSort(vector<Resource>& resources, int left, int right, int choice)
{
    if (left >= right){
        return;
    }
    int middle = left + (right - left) / 2;
    mergeSort(resources, left, middle, choice);
    mergeSort(resources, middle + 1, right, choice);
    mergeResources(resources, left, middle, right, choice);
}



void generateReport(vector<Resource>& resources, ReservationList& reservations,
                    WaitingList& waitingList)
{
    cout << "===== Active Reservations =====" << endl;
    reservations.displayReservations();

    cout << "\n===== Resource Utilization =====" << endl;
    int mostRequests = 0;
    for (size_t i = 0; i < resources.size(); i++){
        string id = resources[i].getresourceID();
        int count = reservations.countReservations(id);
        cout << id << " | " << resources[i].getresourceName()
             << " | Reservations: " << count << endl;
        int requests = count + waitingList.countWaiting(id);
        if (requests > mostRequests){
            mostRequests = requests;
        }
    }

    cout << "\n===== Most Requested Resources =====" << endl;
    cout << "Based on current reservations plus waiting requests." << endl;
    if (mostRequests == 0){
        cout << "No requests." << endl;
    }
    else{
        for (size_t i = 0; i < resources.size(); i++){
            string id = resources[i].getresourceID();
            int requests = reservations.countReservations(id) + waitingList.countWaiting(id);
            if (requests == mostRequests){
                cout << id << " | " << resources[i].getresourceName()
                     << " | Requests: " << requests << endl;
            }
        }
    }


    cout << "\n===== Waiting-List Statistics =====" << endl;
    for (size_t i = 0; i < resources.size(); i++){
        string id = resources[i].getresourceID();
        cout << id << " | " << resources[i].getresourceName()
             << " | Students waiting: " << waitingList.countWaiting(id) << endl;
    }
}


void sortResources(vector<Resource>& resources)
{
    int sortChoice;

    cout << endl;
    cout << "===== Sort Resources =====" << endl;
    cout << "1. Sort by Resource ID" << endl;
    cout << "2. Sort by Resource Name" << endl;
    cout << "3. Sort by Resource Type" << endl;
    cout << "4. Sort by Availability Status" << endl;
    cout << "5. Return to Main Menu" << endl;

    cout << endl;
    cout << "Enter Choice: ";

    if (!readNumber(sortChoice)){
        return;
    }

    
    if (sortChoice == 1)
    {
        mergeSort(resources, 0, (int)resources.size() - 1, 1);

        cout << endl;
        cout << "Resources sorted by Resource ID." << endl;
        viewResources(resources);
    }
    else if (sortChoice == 2)
    {
        mergeSort(resources, 0, (int)resources.size() - 1, 2);

        cout << endl;
        cout << "Resources sorted by Resource Name." << endl;
        viewResources(resources);
    }
    else if (sortChoice == 3)
    {
        mergeSort(resources, 0, (int)resources.size() - 1, 3);

        cout << endl;
        cout << "Resources sorted by Resource Type." << endl;
        viewResources(resources);
    }
    else if (sortChoice == 4)
    {
        mergeSort(resources, 0, (int)resources.size() - 1, 4);

        cout << endl;
        cout << "Resources sorted by Availability Status." << endl;
        viewResources(resources);
    }
    else if (sortChoice == 5)
    {
        return;
    }
    else
    {
        cout << endl;
        cout << "Invalid choice." << endl;
    }
}


void displayMenu()
{
    cout << endl;
    cout << "============================================" << endl;
    cout << "    Campus Resource Reservation System" << endl;
    cout << "============================================" << endl;

    cout << endl;
    cout << "1. View Resources" << endl;
    cout << "2. Create Reservation" << endl;
    cout << "3. Cancel Reservation" << endl;
    cout << "4. View Waiting Lists" << endl;
    cout << "5. Undo Cancellation" << endl;
    cout << "6. Search Reservations" << endl;
    cout << "7. Sort Resources" << endl;
    cout << "8. Generate Report" << endl;
    cout << "9. Exit" << endl;

    cout << endl;
    cout << "Enter Choice: ";
}

int main()
{
    vector<Resource> resources = loadResources("data/resources.txt");
    ReservationList CampusReservations;
    WaitingList CampusWaitingList;

    loadReservations("data/reservations.txt", CampusReservations);

    int choice = 0;

    do
    {
        displayMenu();

        if (cin.eof()){
            break;
        }
        if (!readNumber(choice))
        {
            cout << endl;
            cout << "Invalid input. Please enter a number from 1-9." << endl;

            continue;
        }

        if (choice == 1)
        {
            viewResources(resources);
        }
        else if (choice == 2)
        {
            int studentID;
            string name;
            string resID;
            string date;

            cout << endl;
            cout <<"Enter your Student ID: ";
            if (!readNumber(studentID) || studentID <= 0){
                cout << "Student ID must be a positive number." << endl;
                continue;
            }
            cout << "Enter your Name: ";
            getline (cin >> ws, name);
            cout << "Enter the Resource ID you want to reserve: ";
            cin >> resID;
            cout << "Enter the date of your reservation (MM/DD/YYYY): ";
            cin >> date;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            int resourceIndex = findResource(resources, resID);
            if (resourceIndex == -1){
                cout << "Resource ID not found." << endl;
            }
            else if (!validDate(date)){
                cout << "Invalid date!! Use MM/DD/YYYY." << endl;
            }
            //make sure its available and good to be reserved 
            else if (resources[resourceIndex].getavailabilityStatus() != "Available"
                     || CampusReservations.isReserved(resID, date)){
                CampusWaitingList.addStudent(to_string(studentID), name, resID);
                cout << "Resource unavailable. Added to waiting list." << endl;
            }
            else{
                CampusReservations.addReservation(studentID, name, resID, date);
            }



        }
        else if (choice == 3)
        {
            string name;

            cout << "Please enter the student name of the reservation you wish to cancel: ";
            getline(cin >> ws, name);

            CampusReservations.cancelReservation(name);

            cout << endl;
        }

        else if (choice == 4)
        {
            cout << endl;
            CampusWaitingList.displayWaitingList();
        }
        else if (choice == 5)
        {
            cout << endl;
            cout << "Undo Cancellation functionality will be added by the reservation team." << endl;
        }
        else if (choice == 6)
        {
            cout << endl;
            int studentID;
            cout << "Enter the Student ID to search: ";
            if (readNumber(studentID) && studentID > 0){
                CampusReservations.searchReservations(studentID);
            }
            else{
                cout << "Student ID must be a positive number." << endl;
            }
        }
        else if (choice == 7)
        {
            sortResources(resources);
        }
        else if (choice == 8)
        {
            cout << endl;
            generateReport(resources, CampusReservations, CampusWaitingList);
        }
        else if (choice == 9)
        {
            cout << endl;
            cout << "Exiting Campus Resource Reservation System..." << endl;
        }
        else
        {
            cout << endl;
            cout << "Invalid choice. Please select 1-9." << endl;
        }

    } while (choice != 9);

    return 0;
}

