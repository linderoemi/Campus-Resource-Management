#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
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

    for (int i = 0; i < resources.size(); i++)
    {
        resources[i].displayResource();
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
    cin >> sortChoice;

    if (sortChoice == 1)
    {
        sort(resources.begin(), resources.end(),
            [](Resource& first, Resource& second)
            {
                return first.getresourceID() < second.getresourceID();
            });

        cout << endl;
        cout << "Resources sorted by Resource ID." << endl;
        viewResources(resources);
    }
    else if (sortChoice == 2)
    {
        sort(resources.begin(), resources.end(),
            [](Resource& first, Resource& second)
            {
                return first.getresourceName() < second.getresourceName();
            });

        cout << endl;
        cout << "Resources sorted by Resource Name." << endl;
        viewResources(resources);
    }
    else if (sortChoice == 3)
    {
        sort(resources.begin(), resources.end(),
            [](Resource& first, Resource& second)
            {
                return first.getresourceType() < second.getresourceType();
            });

        cout << endl;
        cout << "Resources sorted by Resource Type." << endl;
        viewResources(resources);
    }
    else if (sortChoice == 4)
    {
        sort(resources.begin(), resources.end(),
            [](Resource& first, Resource& second)
            {
                return first.getavailabilityStatus() <
                       second.getavailabilityStatus();
            });

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
    vector<Resource> resources = loadResources("resources.txt");
    ReservationList CampusReservations;

    int choice = 0;

    do
    {
        displayMenu();

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

            cout << endl;
            cout <<"Enter your Student ID: ";
            cin >> studentID;
            cout << "Enter your Name: " << endl;
            cin >> name;
            cout << "Enter the Resource ID you want to reserve: " << endl;
            cin >> resID;

            CampusReservations.addReservation(studentID, name, resID);

            cout << "Reservation created successfully!" << endl;



        }
        else if (choice == 3)
        {
            cout << endl;
            cout << "Canceling Reservations will be added by the reservation team." << endl;
        }
        else if (choice == 4)
        {
            cout << endl;
            cout << "Waiting List functionality will be added by the reservation team." << endl;
        }
        else if (choice == 5)
        {
            cout << endl;
            cout << "Undo Cancellation functionality will be added by the reservation team." << endl;
        }
        else if (choice == 6)
        {
            cout << endl;
            cout << "Search Reservations functionality will be added by the reservation team." << endl;
        }
        else if (choice == 7)
        {
            sortResources(resources);
        }
        else if (choice == 8)
        {
            cout << endl;
            cout << "Report functionality will be added by the reservation team." << endl;
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

