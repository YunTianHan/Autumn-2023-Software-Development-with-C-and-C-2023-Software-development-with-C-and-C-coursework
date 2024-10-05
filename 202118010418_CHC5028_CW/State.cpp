

#include "State.h"
#include "Room.h"


/**
 * Current state of the game.
 */

/**
 * Display the description of the room the player is in. */

void State::announceLoc() const {
    this->currentRoom->describe();
}

/**
 * Constructor.
 * @param startRoom Pointer to the room to start in.
 */
State::State(Room *startRoom) : currentRoom(startRoom) {};

/**
 * Move to a specified room and print its description.
 * @param target Pointer to the room to move to.
 */
void State::goTo(Room *target) {
    this->currentRoom = target;
    this->announceLoc();
}

/**
 * Return a pointer to the current room.
 * @return Pointer to the current room.
 */
Room* State::getCurrentRoom() const {
    return this->currentRoom;
}

/**
 * Add an object to the player's inventory.
 * Print it already adding
 * @param object Pointer to the object to add.
 */
void State::addObject(GameObject *object) {
    this->inventory.push_back(object);
}

/**
 * Remove an object from the player's inventory.
 * @param object Pointer to the object to remove.
 */
void State::removeObject(GameObject *object) {
    this->inventory.remove(object);
}

/**
 * Check if the player has an object in their inventory.
 * @param secondWord The object to check for.
 * @return True if the player has the object, false otherwise.
 */
GameObject *State::getObject(string secondWord) const{
    for (auto it = this->inventory.begin(); it != this->inventory.end(); ++it) {
        const string *keyword = (*it)->getKeyword();
        if (*keyword == secondWord) {
            return *it;
        }
    }
    return nullptr;
}

/**
 * Check if the inventory has a specific object by passing an external string argument keyword.
 * @param object Pointer to the object to check for.
 * @return True if the room has the object, false otherwise.
 */
bool State::hasObject(string secondWord) const {
    if (this->inventory.empty()) {
        return false;
    } else {
        for (auto it = this->inventory.begin(); it != this->inventory.end(); ++it) {
            const string *keyword = (*it)->getKeyword();
            if (*keyword == secondWord) {
                return true;
            }
        }
        return false;
    }
}


/**
 * Print the player's inventory.
 */
void State::printInventory() const {
    if (this->inventory.empty()) {
        cout << "You have nothing in your inventory." << endl;
    } else {
        cout << endl;
        cout << "You have the following items in your inventory:" << endl;
        for (auto it = this->inventory.begin(); it != this->inventory.end(); ++it) {
            cout << *((*it)->getName()) << "(" << *((*it)->getKeyword()) << ")" << endl;
        }
        cout << "_________" << endl;
    }
}

/**
 * Return the player's inventory.
 * @return The player's inventory.
 */
list<GameObject *> State::getInventory() const {
    return this->inventory;
}

/**
 * Return the player's strength.
 * @return The player's strength.
 */
int State::getStrength() const {
    return this->strength;
}

/**
 * Set the player's strength.
 * @param strength The player's strength.
 */
void State::setStrength(int strength) {
    this->strength = strength;
}

/**
 * Add to the player's strength.
 * @param strength The amount to add.
 */
void State::addStrength(int strength) {
    this->strength += strength;
}

/**
 * Print the player's strength.
 */
void State::printStrength() const {
    std::cout << "Your strength is " << this->strength << "." << std::endl;
}