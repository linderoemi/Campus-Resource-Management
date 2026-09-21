#include "Resource.h"
#include <iostream>
using namespace std;



Resource::Resource(){
    resourceID = "";
    resourceName = "";
    resourceType = "";
    availabilityStatus = "";
}


Resource::Resource(string id, string name, string type, string status){
    resourceID = id;
    resourceName = name;
    resourceType = type;
    availabilityStatus = status;
}

string Resource::getresourceID(){
    return resourceID;
}


string Resource::getresourceName(){
    return resourceName;
}

string Resource::getresourceType(){
    return resourceType;
}

string Resource::getavailabilityStatus(){
    return availabilityStatus;
}

void Resource::setresourceID(string id){
    resourceID = id;
}

void Resource::setresourceName(string name){
    resourceName = name;
}

void Resource::setresourceType(string type){
    resourceType = type;
}

void Resource::setavailabilityStatus(string status){
    availabilityStatus = status;
}

void Resource::displayResource() const{
    cout << resourceID << " | "
         << resourceName << " | "
         << resourceType << " | "
         << availabilityStatus << endl;
}



