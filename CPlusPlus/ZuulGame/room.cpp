#include <iostream>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

struct item{
    char* name;
    item(char* newname){
        name = new char[21];
        strncpy(name,newname,20);
        name[20]='\0';
    }
    ~item(){
        delete[] name;
    }
};

class room{
  public:
    //constructors and destructors
    room(char* newlongdesc, char* newshortdesc){
        delete[] longDesc;
        longDesc = new char[251];
        strncpy(longDesc,newlongdesc, 250);
        longDesc[250]= '\0';
        delete[] shortDesc;
        shortDesc = new char [21];
        strncpy(shortDesc,newshortdesc, 20);
        shortDesc[20]= '\0';
    }
    
    //don't think I'll ever call this but better safe than sorry.
    ~room(){
        delete[] longDesc;
        delete[] shortDesc;
        map<char*, room*, memCompare>::iterator it = exits.begin();
        // Iterate through the map and delete everything
        while (it != exits.end()) {
            delete[] it->first;
            delete it->second;
            ++it;
        }
        vector<item*>::iterator it2 = roomInventory.begin();
        // List every item in the vector
        while (it2 != roomInventory.end()) {
            delete[] (*it2)->name;
            ++it;
        }
    }
    
    //getters and setters
    void setLongDesc(char* newlongdesc){
        strncpy(longDesc,newlongdesc, 250);
        longDesc[250]= '\0';
    }
    //for description.
    void printLongDesc(){
        for(int i=0; i<250; i++){
            cout<<longDesc[i];
        }
        cout<<endl;
    }
    //for setup.
    void printShortDesc(){
        for(int i=0; i<20; i++){
            cout<<shortDesc[i];
        }
        cout<<endl;
    }
    //for setup.
    void setShortDesc(char* newshortdesc){
        strncpy(shortDesc,newshortdesc, 20);
        shortDesc[20]= '\0';
    }
    //for setup.
    void setExit(char* newfromdir, room* newexitto){
        char* fromdir = new char[21];
        strncpy(fromdir,newfromdir, 20);
        exits[fromdir] = newexitto;
    }
    //this is the eqivalent of the hashMap in the java version of this.
    room* getExit(char* fromdir){
        map<char*, room*, memCompare>::iterator it = exits.begin();
        // Check if the exit is in the array
        while (it != exits.end()) {
            if (strcmp((it->first),fromdir)==0){
                return exits[fromdir];
            }
            ++it;
        }
        return nullptr;
    }
    //this lists the exits in every room.
    void printExits(){
        cout<<"EXITS:"<<endl;
        map<char*, room*, memCompare>::iterator it = exits.begin();
        // Iterate through the map and print the elements
        while (it != exits.end()) {
            cout << "Direction: " << it->first << ", Room: " << it->second->shortDesc << endl;
            ++it;
        }
    }
    //room inventory lister.
    void printItems(){
        if(!(roomInventory.empty())){
            cout<<"ITEMS IN ROOM:"<<endl;
            vector<item*>::iterator it = roomInventory.begin();
            // List every item in the vector
            while (it != roomInventory.end()) {
                cout << (*it)->name << endl;
                ++it;
            }
        }else{
            //can't print ITEMS: then just have nothing after. it looks bad.
            cout<<"Nothing of interest is laying about."<<endl;
        }
    }
    //makes a new item in the room.
    void addItem(char* newItem){
        item* bufferItem = new item(newItem);
        roomInventory.push_back(bufferItem);
    }
    //for inventory purposes. note: Removes item if found!
    item* getItem(char* soughtName){
        vector<item*>::iterator it = roomInventory.begin();
        // meant to work similarly to 'pop_back' but for any item in the array.
        while (it != roomInventory.end()) {
            if (strcmp(((*it)->name),soughtName)==0){
                item* returnitem= new item((*it)->name);
                roomInventory.erase(it);
                return returnitem;
            }
            ++it;
        }
        return nullptr;
    }
    
    //I got the idea for this from chatGPT which means it's explaining time
    //the operator() function allows memCompare to be used as a comparison operator for char*s
    //I need it because without it the map would compare the pointers, not their contents.
    //the <0 is due to maps needing to keep things in a specific order, and using an == would prevent that from occuring.
    //the consts are to make absolutely certain that nothing is changed in the process of comparison.
    struct memCompare{
        bool operator()(const char* lockkey, const char* key) const{
            return strcmp(lockkey,key) < 0;
        }
    };
    
    //exit map and item vector
    map<char*, room*, memCompare> exits;
    vector<item*> roomInventory;
    char* longDesc;
    char* shortDesc;
};
