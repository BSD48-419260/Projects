#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "room.cpp"
using namespace std;

void getStringFromInput(char* &);
void moveroom(room* &,vector<item*>);
void describe(room*,vector<item*>);
void takeitem(room*,vector<item*>&);
void dropitem(room*,vector<item*>&);
void useFunction(room*, vector<item*>&, bool&);
void listInventory(vector<item*>);
void addItem(vector<item*>&,char*);
item* getItem(char*,vector<item*>&);

int main()
{
    //Setup. 
    room* currentroom;
    vector<item*> inventory;
    //this determines the ending of the game. Yay!
    bool wearingsuit=false;
    //opening scrawl.
    cout<<"==============================="<<endl;
    cout<<"Welcome to:"<<endl;
    cout<<"           ________     ____ "<<endl;
    cout<<"           \\____  /    / __ \\"<<endl;
    cout<<"               / /    /_/  \\ |"<<endl;
    cout<<"              / /       ___/ / "<<endl;
    cout<<"             / /       |___ |"<<endl;
    cout<<"            / /       __   \\ \\"<<endl;
    cout<<"           / /___     \\ \\__/ |"<<endl;
    cout<<"Elliott's /______\\ uul \\____/ : "<<endl;
    cout<<"FLEE THE MARKET!"<<endl;
    
    cout<<"Your name is Market Fleer, Terible Person, Mass Murderer, Racist Robot, and Wanted Criminal. You are curerntly in the megastation"<<endl;
    cout<<"G1A-И7-FL34-M4ЯK-E7"<<endl;
    cout<<"You and your...  'group of friends' have been trying to secure transport off-station for the last few months."<<endl; 
    cout<<"thankfully, your 'group' has finally accquired a spaceship from a family doing a reunion who won't be using it anymore."<<endl;
    cout<<"Unfortunately, station security has a few issues with some of the finer points, and after a hearty chase, you're stuck in a single market hallway. "<<endl;
    cout<<"At one end, the a shut door leads to constantly-patroling security officers. you've sabotaged the door to jam, which bought you a few hours. they may not be able to get in, but you can't go out that way."<<endl;
    cout<<"At the other, sweet freedom. unfortunately behind a jammed former exterior airlock door. if you can get a suit on and through the door, you can radio your 'friends' to pick you up, then finally get out of this place."<<endl;
    cout<<"You digitally grimmace. you only carried in your porta-radio, and most stall owners are too wary for you to steal anything. you're low on opitions, but you've managed to wriggle your way out of worse before."<<endl;
    cout<<"And without further ado, We begin."<<endl;
    
    //all the charpointers and deletes below are to prevent memory leaks.
    
    //room setup
    char* roomlong = new char[251];
    char* roomshort = new char[21];
    //strncpy(roomlong,, 250);
    //strncpy(roomshort,, 20);
    //roomlong[250]='\0';
    //roomshort[20]='\0';
    //room* NO = new room(roomlong,roomshort);
    
    strncpy(roomlong,"Before you stands a lithoid manning a desk hawking electronics. It's translator squaks:\nD I D Y O U G E T M Y L E A D ?\nYou remember that your 'group' agreed to exchange it some lead dust for a curious gyroscope. \0", 250);
    strncpy(roomshort,"Electronics Stand\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* a1 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"A sickly Tox-mod nods at you from a stand covered in cheese.\n it takes it's rebreather off for a few seconds-All it\'s modifications will allow-and coughs out\n\"Cheese for Fluorine Crytals?\"\0", 250);
    strncpy(roomshort,"Cheese Stand", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* a2 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"\"Spice Melange!\" cries the creature behind this stand\n\"Care to try some Spice Melange? Balances your Humors, cures your ills!\"\nit waves a bag of greyish powder at you.\n...you're pretty sure that's lead dust.\0", 250);
    strncpy(roomshort,"\'Spice\' Dealer", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* a3 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"Through a disused storage hatch, you find an entire stall space covered floor-to-ceiling with merchandise for... Some insectoid celebrity, you guess.\n your universal translator gives their name as 'Queen Larvasqueak'\0", 250);
    strncpy(roomshort,"Alien Collection", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* a4 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"A tall reptilian nods at you.\nA space suit sits behind it, but it shakes it's head.\n\"Sorry. Lunch break. Can't legally sell anything until I eat.\"\0", 250);
    strncpy(roomshort,"Clothing Store", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* a5 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"You're at what was formerly the exterior door of the airlock.\nfunny to think the only thing that stands between you and freedom is a single integrated circuit.\0", 250);
    strncpy(roomshort,"Airlock Door\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* b1 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"You're a few steps away from the exterior door, ignoring a rodentoid street performer playing some kind of string instrument.\n you resist the urge to punch it\0", 250);
    strncpy(roomshort,"Dusty Passageway\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* b2 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"You're in about the middle of the passageway.\nYou step over a puddle of vomit and glance around\nNo sign of the thing that hucked it up.\nCould the ugly waterbags not be bothered to make it to a tashcan before they spew their fluids everywhere?\0", 250);
    strncpy(roomshort,"Middle Passageway\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* b3 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"The lights of this passageway buzz and flicker. A loose wire dangles from above.\nIdiot matinence fleshbags. always slacking off...\0", 250);
    strncpy(roomshort,"Darkened Passageway\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* b4 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"The interior door of this airlock sparks slightly, as the metal you bent to prevent it's opening strains to keep it shut.\nYou virtually smile. Thank goodness for augmented muscles.\0", 250);
    strncpy(roomshort,"Locked Door\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* b5 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"A Library sits strangely in the hall.\nIt's one of the few places in this airlock manned by an android, albeit a simple one.\nYou can easily trick it into handing over the little stock it has left.\0", 250);
    strncpy(roomshort,"Library\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* c1 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"An insectoid beset with jewels waves to you as you walk to his stand. \n\'jEWELs fOr sALe!\'\nYou check your pockets, but you have no cash on you.", 250);
    strncpy(roomshort,"Jeweler's stand\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* c2 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"You walk into a restraunt full of meatbags, and almost shut off your receptors in disgust.\nA gang of bare-chested \'British\' football \'ooligans seem to be planning an attack on the irish two spaces over.\nOne nods to you.\"Ere Tah \'elp ush aincha?\"\0", 250);
    strncpy(roomshort,"Racist Bri\'ish KFC\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* c3 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"You walk to the curio stall, and stare at the table\nIt's the integrated circuit you'd need to open the exterior door!\nThe old man behind the counter nods at you.\n\"Hullo. Care for some curios? I thought you androids hated 'junk' like mine.\"\0", 250);
    strncpy(roomshort,"Curio store\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* c4 = new room(roomlong,roomshort);
    
    strncpy(roomlong,"A group of heavily muscled men in kilts nod at you as you enter the stall\n\"Sorry, can't sell anything now. Need to plan the defense against the football \'ooligans. now where\'s my dang cheese...\"\0", 250);
    strncpy(roomshort,"Bagpipe Store\0", 20);
    roomlong[250]='\0';
    roomshort[20]='\0';
    room* c5 = new room(roomlong,roomshort);
    
    delete[] roomlong;
    delete[] roomshort;
    
    //exits
    char* exitDirection = new char[21];
    //strncpy(exitDirection,, 20);
    
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    a1->setExit(exitDirection,b1);
    
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    a2->setExit(exitDirection,b2);
    
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    a3->setExit(exitDirection,b3);
    
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    a4->setExit(exitDirection,b4);
    
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    a5->setExit(exitDirection,b5);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    b1->setExit(exitDirection,a1);
    strncpy(exitDirection,"STARBOARD", 20);
    exitDirection[20]='\0';
    b1->setExit(exitDirection,b2);
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    b1->setExit(exitDirection,c1);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    b2->setExit(exitDirection,a2);
    strncpy(exitDirection,"PORT", 20);
    exitDirection[20]='\0';
    b2->setExit(exitDirection,b1);
    strncpy(exitDirection,"STARBOARD", 20);
    exitDirection[20]='\0';
    b2->setExit(exitDirection,b3);
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    b2->setExit(exitDirection,c2);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    b3->setExit(exitDirection,a3);
    strncpy(exitDirection,"PORT", 20);
    exitDirection[20]='\0';
    b3->setExit(exitDirection,b2);
    strncpy(exitDirection,"STARBOARD", 20);
    exitDirection[20]='\0';
    b3->setExit(exitDirection,b4);
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    b3->setExit(exitDirection,c3);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    b4->setExit(exitDirection,a4);
    strncpy(exitDirection,"PORT", 20);
    exitDirection[20]='\0';
    b4->setExit(exitDirection,b3);
    strncpy(exitDirection,"STARBOARD", 20);
    exitDirection[20]='\0';
    b4->setExit(exitDirection,b5);
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    b4->setExit(exitDirection,c4);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    b5->setExit(exitDirection,a5);
    strncpy(exitDirection,"PORT", 20);
    exitDirection[20]='\0';
    b5->setExit(exitDirection,b4);
    strncpy(exitDirection,"AFT", 20);
    exitDirection[20]='\0';
    b5->setExit(exitDirection,c5);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    c1->setExit(exitDirection,b1);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    c2->setExit(exitDirection,b2);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    c3->setExit(exitDirection,b3);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    c4->setExit(exitDirection,b4);
    
    strncpy(exitDirection,"FORE", 20);
    exitDirection[20]='\0';
    c5->setExit(exitDirection,b5);
    
    delete[] exitDirection;
    
    //adding items
    char* itemName = new char[21];
    //strncpy(itemName,, 20);
    
    strncpy(itemName,"Larvasqueak Poster", 20);
    a4->addItem(itemName);
    
    strncpy(itemName,"Deflated Bagpipes", 20);
    b1->addItem(itemName);
    
    strncpy(itemName,"\'Dune\'", 20);
    c1->addItem(itemName);
    
    strncpy(itemName,"\'Twice-Dead King\'", 20);
    c1->addItem(itemName);
    
    strncpy(itemName,"\'Ender\'s Game\'", 20);
    c1->addItem(itemName);
    
    delete[] itemName;
    
    currentroom = b5;
    //main game
    bool notQuit=true;
    char*input = new char[21];
    while(notQuit){
        //command handler.
        cout<<"Please Input Command (GO, LOOK, TAKE, DROP, USE, SURRENDER(meaning Quit.))"<<endl;
        getStringFromInput(input);
        cout<<"Function got: "<<endl;
        for(int i=0; i<21; i++){
            cout<<input[i];
        }
        cout<<endl;
        if(strcmp(input,"GO")==0){
            moveroom(currentroom,inventory);  
        }else if(strcmp(input,"LOOK")==0){
            describe(currentroom,inventory);
        }else if(strcmp(input,"TAKE")==0){
            takeitem(currentroom, inventory);
        }else if(strcmp(input,"DROP")==0){
            dropitem(currentroom, inventory);
        }else if(strcmp(input,"USE")==0){
            useFunction(currentroom, inventory, wearingsuit);
        }else if(strcmp(input,"SURRENDER")==0){
            cout<<"You radio in to your 'group' that you're stuck, and they'll have to go on without you."<<endl;
            cout<<"Slowly, you walk through the door at the end of the hall, right into the line of sight of twenty-eight seprate station security officers."<<endl;
            cout<<"You put your hands behind your back, and get on your knees. you begin to speak \"I surrend-"<<endl;
            cout<<"You are immediately tackled by at least five security personel, and are executed via disassembly within the hour."<<endl;
            cout<<"What did you expect? you're a mass-mudering psychopath robot who killed an entire family reunion's worth of people to steal their ship, and in broad lamplight no less!"<<endl;
            notQuit=false;
        }else{
            cout<<"Invalid Command."<<endl;
        }
    }
    //cleaning up 
    delete[] input;
    return 0;
}

//string handler. I am going to reuse this so many times.
void getStringFromInput(char* & inpstring){
    char bufferarray [21];
    //make sure it works
    bool acin=false;
    for(int i=0;i<21;i++){
        bufferarray[i]='\0';
    }
    while(acin==false){
        cout<<">>";
        cin.getline(bufferarray, sizeof(bufferarray),'\n');
        //Error handling.
        if(cin.fail()){
            cout<<"ERROR! Invalid input. please try again. (20 chars or less)"<<endl;
            cout<<"(it is recomended that you press the enter key at least once before retyping your command.)"<<endl;
            cin.clear();
            cin.ignore(100000,'\n');
        }else{
            acin=true;
        }
    }
    strncpy(inpstring, bufferarray, 20);
    inpstring[20]='\0';
    cout<<endl;
    return;
}

//uses the exit class to move between rooms.
void moveroom(room* & currentroom, vector<item*> inventory){
    char*input = new char[21];
    //command handler.
    currentroom->printExits();
    cout<<"Which Direction?"<<endl;
    getStringFromInput(input);
    cout<<"Function got: "<<endl;
    for(int i=0; i<21; i++){
        cout<<input[i];
    }
    cout<<endl;
    room* moveto=currentroom->getExit(input);
    if(moveto==nullptr){
        cout<<"There is no exit that way."<<endl;
    }else{
        currentroom = moveto;
    }
    describe(currentroom,inventory);
    delete[] input;
}

//description of whatever room you're in.
void describe(room* currentroom,vector<item*> inventory){
    cout<<"You are in: ";
    currentroom->printShortDesc();
    currentroom->printLongDesc();
    currentroom->printExits();
    currentroom->printItems();
}

//take item  function
void takeitem(room* currentroom, vector<item*>& inventory){
    listInventory(inventory);
    currentroom->printItems();
    char * input = new char[21];
    cout<<"Which Item?"<<endl;
    getStringFromInput(input);
    cout<<"Function got: "<<endl;
    for(int i=0; i<21; i++){
        cout<<input[i];
    }
    cout<<endl;
    item* gottenitem=currentroom->getItem(input);
    if(gottenitem==nullptr){
        cout<<"There is no item by that name."<<endl;
    }else{
        cout<<"You have picked up the "<<gottenitem->name<<endl;
        inventory.push_back(gottenitem);
    }
    delete[] input;
}

//drop item function
void dropitem(room* currentroom, vector<item*>& inventory){
    listInventory(inventory);
    currentroom->printItems();
    char * input = new char[21];
    cout<<"Which Item?"<<endl;
    getStringFromInput(input);
    cout<<"Function got: "<<endl;
    for(int i=0; i<21; i++){
        cout<<input[i];
    }
    cout<<endl;
    item* gottenitem=getItem(input, inventory);
    if(gottenitem==nullptr){
        cout<<"There is no item by that name."<<endl;
    }else{
        cout<<"You have dropped the "<<gottenitem->name<<endl;
        currentroom->roomInventory.push_back(gottenitem);
    }
    delete[] input;
}

//use/trade item function.
void useFunction(room* currentroom,vector<item*> & inventory, bool & wearingsuit){
    listInventory(inventory);
    char * input = new char[21];
    cout<<"Which Item?"<<endl;
    getStringFromInput(input);
    cout<<"Function got: "<<endl;
    for(int i=0; i<21; i++){
        cout<<input[i];
    }
    cout<<endl;
    item* gottenitem=getItem(input, inventory);
    if(gottenitem==nullptr){
        cout<<"There is no item by that name."<<endl;
    }else{
        
        //use in a room code:
        //else if(strcmp(currentroom->shortDesc,"")==0){
        //    if(strcmp(gottenitem->name,"")==0){
        //        cout<<""<<endl;
        //        delete gottenitem;
        //        addItem(inventory,"");
        //        worked=true;
        //    }
        //}
        //various trades
        bool worked=false;
        if(strcmp(gottenitem->name,"Deflated Bagpipes")==0){
            cout<<"You try to play the pipes, but they've been pierced."<<endl;
            cout<<"Your chem receptors indicate it's released some kind of scent. Analysis indicates... bagels?"<<endl;
            inventory.push_back(gottenitem);
            worked=true;
        }else if(strcmp(gottenitem->name,"Space Suit")==0){
            cout<<"You zip yourself into the spacesuit.\nnot technically needed for androids like yourself, but it'll prevent the station defenses from recognizing you and blasting you into oblivion."<<endl;
            wearingsuit=true;
            worked=true;
        }else if(strcmp(currentroom->shortDesc,"Jeweler's stand")==0){
            if(strcmp(gottenitem->name,"Larvasqueak Poster")==0){
                cout<<"The insectoid glances at the poster and smiles\nthe fleshbag seems to like it.\nYou hand it over, and the insectoid hands you a small rough torus of crystal in exchange."<<endl;
                delete gottenitem;
                addItem(inventory,"Fluoride Gem");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"Cheese Stand")==0){
            if(strcmp(gottenitem->name,"Fluoride Gem")==0){
                cout<<"The tox-mod smiles, though it's hard to tell behind it's mask.\nIt puts the gem in a box behind it, then hands you a wheel of cheese"<<endl;
                delete gottenitem;
                addItem(inventory,"Cheese");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"Bagpipe Store")==0){
            if(strcmp(gottenitem->name,"Cheese")==0){
                cout<<"One of the heavily muscled men in a kilt sees the cheese you handed him, nods, and says\n\"Listen here, we have a plan but we need help to do it.\nPlease, just hand these faked defensive plans to the \'ooligans. they\'ll probably reward you, then attack us.\""<<endl;
                delete gottenitem;
                addItem(inventory,"Fake Battle Plans");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"Racist Bri\'ish KFC")==0){
            if(strcmp(gottenitem->name,"Fake Battle Plans")==0){
                cout<<"One of the 'ooligans sees you walk in, and reads the words \"Defi\'nle r\'al battl\' plans\" on the paper you're holding.\nHe grabs the paper out of your hand and cheers \"'AVE GOT THEMS' BATTL\' PLANS RIGHT \'ERE\"\nThey all cheer, and start guzzling down copious quantities of alcohol and in all the confusion, one of the \'ooligans hands you a KFC bucket for you're trouble.\n...It's full of meat pies."<<endl;
                delete gottenitem;
                addItem(inventory,"Bri\'ish KFC");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"Clothing Store")==0){
            if(strcmp(gottenitem->name,"Bri\'ish KFC")==0){
                cout<<"\"Finally!\" the reptilian cries.\n\"I've been waiting for hours!\"\nThe reptilian digs into the bucket of meat pies.\nAfter some discussion, it hands you the space suit."<<endl;
                delete gottenitem;
                addItem(inventory,"Space Suit");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"\'Spice\' Dealer")==0){
            if(strcmp(gottenitem->name,"\'Dune\'")==0){
                cout<<"The \'Spice\' dealer\'s eyes widen as you hand it the book \'Dune\'.\nIt begins to thank you profusely, and hands you a bag of... spice melange?\nNow that you've gotten you're hands on it, you're certain:\nIt\'s lead dust."<<endl;
                delete gottenitem;
                addItem(inventory,"Lead Dust");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"Electronics Stand")==0){
            if(strcmp(gottenitem->name,"Lead Dust")==0){
                cout<<"The lithoid cautiously snatches the bag out of your hands.\nIt sticks a stony finger inside, and then brings it to it\'s face.\nIt nods to you, sticks it\'s bag in it\'s pocket, then hands you the gyroscope."<<endl;
                delete gottenitem;
                addItem(inventory,"Gyroscope");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"Curio store")==0){
            if(strcmp(gottenitem->name,"Gyroscope")==0){
                cout<<"The old man behind the counter picks up the gyroscope, and inspects it for a moment.\nWordlessly, it puts it down and picks up the circuit, then hands it to you.\nIt looks you in the occular, then something seems to change behind it\'s eyes.\nIt states plainly.\n\"You won\'t make it far. Even if you survive what comes next, I\'ll be waiting for you.\"\n\nIs that?\n\nWhatever changed behind the old man\'s eyes is gone now."<<endl;
                delete gottenitem;
                addItem(inventory,"Airlock Circuit");
                worked=true;
            }
        }else if(strcmp(currentroom->shortDesc,"Airlock Door")==0){
            //winning scrawl
            if(strcmp(gottenitem->name,"Airlock Circuit")==0){
                cout<<"You finally plug the little integrated circuit chip into the door.\nYou stick your finger into a port on the door, and begin the opening process.\nYou ignore a meatbag as it walks up behind you, and asks: \"Hey, what are you-\"\n\nBang.\n\nAnd with that, you're floating outside the airlock."<<endl;
                cout<<"The entire contents of the airlock are spilled into the space outside it.\n a few dozen bodies float alognside celebrety mechandise, foodstuffs, and general junk.\nThe only things still moving are the ever-confused librarian bot and the half-alive tox-mod choking on it's rebreather. \n all you need to do is wait for your friends to come pick you up."<<endl;
                cout<<"Hang on, is that the curio vender?\nIt looks like it's trying to laugh.\nWhat's so funny?"<<endl;
                if(wearingsuit==true){
                    cout<<"Well, it looks like you'll never know now, seeing as your \'friends\' are here.\nYou broadcast your location, and the tractor beam of your \'friends\' ship picks you up.\nYou make your way up to the bridge of the ship, and enter a charging-bed. you've had a long day at the market, and have earned some rest"<<endl;
                }else{
                    cout<<"The thing points down at the station, and you turn your head to look. you see...\n\nThe barrel of one of the station's point defense cannons, pointed directly at you\n\nJust before the destructor beam atomizes you, You realize that the station security could recognize you from the cameras, and decided that if you\'d already killed a few dozen people, your death would be no great loss."<<endl;
                }
                cout<<"You win! Thank you for playing Elliott\'s Zuul 3: FLEE THE MARKET!"<<endl;
                cout<<"\n\n...Somehow, Somewhere, an old man is laughing...";
                delete gottenitem;
                exit(0);
            }
        }
        //this is called if the item is useless.
        if(worked==false){
            cout<<"It doesn't work."<<endl;
            inventory.push_back(gottenitem);
        }
    }
    delete[] input;
}

//lists whatever's in your inventory
void listInventory(vector<item*> inventory){
    if(!(inventory.empty())){
        cout<<"ITEMS IN INVENTORY:"<<endl;
        //not technically an item but it fits the fluff.
        cout<<"Porta-Radio (You are unwilling to part with)"<<endl;
        vector<item*>::iterator it = inventory.begin();
        // List every item in the vector
        while (it != inventory.end()) {
            cout << (*it)->name << endl;
            ++it;
        }
    }else{
        //Not technically an item, just a bit of fluff.
        cout<<"The only thing in your pockets is your porta-radio, which you're unwilling to part with."<<endl;
    }
}

//this is for adding items
void addItem(vector<item*>& inventory,char* newItem){
    item* bufferItem = new item(newItem);
    inventory.push_back(bufferItem);
}

//this is for dropping items.
item* getItem(char* soughtName, vector<item*> & inventory){
    vector<item*>::iterator it = inventory.begin();
    // meant to work similarly to 'pop_back' but for any item in the array.
    while (it != inventory.end()) {
        if (strcmp(((*it)->name),soughtName)==0){
            item* returnitem= new item((*it)->name);
            inventory.erase(it);
            return returnitem;
        }
        ++it;
    }
    return nullptr;
}
