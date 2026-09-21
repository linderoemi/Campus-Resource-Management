#ifndef Resource_h
#define Resource_h

#include <string>
using namespace std;

class Resource {
private: 
        string resourceID;
        string resourceName;
        string resourceType;
        string availabilityStatus;
public:
    Resource();
    Resource(string id, string name, string type, string status);
    
    string getresourceID ();
    string getresourceName ();
    string getresourceType ();
    string getavailabilityStatus ();

    void setresourceID(string id);
    void setresourceName(string name);
    void setresourceType(string type);
    void setavailabilityStatus(string status);

    void displayResource() const;


};

#endif
