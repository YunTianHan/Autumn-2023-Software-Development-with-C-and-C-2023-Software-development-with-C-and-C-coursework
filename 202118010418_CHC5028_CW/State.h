

#ifndef TEXTADV_STATE_H
#define TEXTADV_STATE_H

#include "Room.h"
#include "GameObject.h"


class State {
    Room *currentRoom;
    // Modify the State class to include a representation of the player’s physical strength, called strength, which is initiated as 100.
    int strength = 100;
public:
    explicit State(Room *startRoom);
    void goTo(Room *target);
    void announceLoc() const;
    Room* getCurrentRoom() const;

    void addObject(GameObject *object);
    void removeObject(GameObject *object);

    bool hasObject(string secondWord) const;
    GameObject *getObject(string secondWord) const;

    void printInventory() const;

    list<GameObject *> getInventory() const;

    void setStrength(int strength);
    int getStrength() const;
    void addStrength(int strength);
    void removeStrength(int strength);
    void printStrength() const;



// Modify the State class to include a representation of a list of GameObjects the player is carrying, called inventory.
list<GameObject*> inventory;
};


#endif //TEXTADV_STATE_H
