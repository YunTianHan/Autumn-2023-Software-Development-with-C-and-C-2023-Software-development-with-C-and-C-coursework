
#include <iostream>
#include <string>
#include <forward_list>
#include <list>
#include <map>
#include "wordwrap.h"
#include "Room.h"
/**
 * Stores a static list of all rooms.
 */
std::list<Room*> Room::rooms;

/**
 * Room default constructor.
 * @param _name Room's name.
 * @param _desc Room's description.
 */
Room::Room(const string* _name, const string *_desc) :
        name(_name), description(_desc), north(nullptr) {};

/**
 * Remove destroyed rooms from the static list.
 */
Room::~Room() {
    Room::rooms.remove(this);
}

/**
 * Prints the description of a room (the name and long description)
 * Modify the Room::describe() method to also print out the short names of all the
 * objects in the room, formatted as nicely as possible
 */
void Room::describe() const {
    cout << endl;
    wrapOut(this->name);
    wrapEndPara();
    wrapOut(this->description);
    wrapEndPara();
    if (!this->objects.empty()) {
        std::cout << "You see the following objects in the room:" << std::endl;
        for (auto &object : this->objects) {
            cout << *(object->getName()) << "(" << *(object->getKeyword()) <<")" << endl;
        }
    } else {
        std::cout << "There are no objects in the room." << std::endl;
    }
    cout << "_________" << endl;
}

/**
 * Statically creates a room and then adds it to the global list.
 * @param _name Name for the new room.
 * @param _desc Description for the new room.
 * @return A pointer to the newly created room.
 */
Room* Room::addRoom(const string* _name, const string *_desc) {
    auto *newRoom = new Room(_name, _desc);
    Room::rooms.push_back(newRoom);
    return newRoom;
}

/**
 * Adds an existing room to the static list.
 * @param room Pointer to the room to add.
 * @return
 */
void Room::addRoom(Room* room) {
    Room::rooms.push_back(room);
}

/**
 * Gets the north exit of a room.
 * @return The room that is north of this one, or NULL if there is no exit.
 */
Room* Room::getNorth() const {
    return this->north;
}

/**
 * Sets the north exit of a room.
 * @param _north Pointer to the room to be north of this one.
 */
void Room::setNorth(Room* _north) {
    this->north = _north;
}

/**
 * Gets the east exit of a room.
 * @return The room that is east of this one, or NULL if there is no exit.
 */
Room* Room::getEast() const {
    return this->east;
}

/**
 * Sets the east exit of a room.
 * @param _east Pointer to the room to be east of this one.
 */
void Room::setEast(Room* _east) {
    this->east = _east;
}

/**
 * Gets the south exit of a room.
 * @return The room that is south of this one, or NULL if there is no exit.
 */
Room* Room::getSouth() const {
    return this->south;
}

/**
 * Sets the south exit of a room.
 * @param _south Pointer to the room to be south of this one.
 */
void Room::setSouth(Room* _south) {
    this->south = _south;
}

/**
 * Gets the west exit of a room.
 * @return The room that is west of this one, or NULL if there is no exit.
 */
Room* Room::getWest() const {
    return this->west;
}

/**
 * Sets the west exit of a room.
 * @param _west Pointer to the room to be west of this one.
 */
void Room::setWest(Room* _west) {
    this->west = _west;
}

Room* Room::getExit(const string& direction) const {
    auto it = exits.find(direction);
    if (it != exits.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void Room::setExit(const string& direction, Room* room) {
    exits[direction] = room;
}

/**
 * Gets a GameObject from the room.
 * @param name Name of the object to get.
 * @return Pointer to the object, or NULL if it is not in the room.
 */
GameObject *Room::getObject(string secondWord) const {
    for (auto it = this->objects.begin(); it != this->objects.end(); ++it) {
        const string *keyword = (*it)->getKeyword();
        if (*keyword == secondWord) {
            return (*it);
        }
    }
    return nullptr;
}

/**
 * Adds a GameObject to the room.
 * @param object Pointer to the object to add.
 */
void Room::addObject(GameObject *object) {
    this->objects.push_back(object);
}

/**
 * Removes a GameObject from the room.
 * Print the object already removing
 * @param object Pointer to the object to remove.
 */
void Room::removeObject(GameObject *object) {
    this->objects.remove(object);
}

/**
 * Check if the room has a specific object by passing an external string argument keyword.
 * @param object Pointer to the object to check for.
 * @return True if the room has the object, false otherwise.
 */
bool Room::hasObject(string secondWord) const {
    if (this->objects.empty()) {
        return false;
    } else {
        for (auto it = this->objects.begin(); it != this->objects.end(); ++it) {
            const string *keyword = (*it)->getKeyword();
            if (*keyword == secondWord) {
                return true;
            }
        }
        return false;
    }
}

/**
 * Gets the name of the room.
 * @return The name of the room.
 */
const string *Room::getName() const {
    return name;
}

/**
 * Gets the list of GameObjects in the room.
 * @return The list of GameObjects in the room.
 */
list<GameObject *> Room::getObjects() const {
    return this->objects;
}
