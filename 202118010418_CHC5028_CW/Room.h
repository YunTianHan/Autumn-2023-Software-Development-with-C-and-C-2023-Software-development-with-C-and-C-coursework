


#ifndef TEXTADV_ROOM_H
#define TEXTADV_ROOM_H

#include "GameObject.h"
#include <list>
#include <string>
#include <map>
#include <iostream>

using namespace std;

/**
 * Represents a room (accessible location in the game).
 */
class Room {
    /**
     * Short name used as a header.
     */
    const string* name;
    /**
     * Full description of the room.
     */
    const string* description;
    /**
     * Pointer to room that is north of this one.
     */
    Room* north;
    /*
     * Pointer to room that is east of this one.
     * */
    Room* east;
    /*
     * Pointer to room that is south of this one.
     * */
    Room* south;
    /*
     * Pointer to room that is west of this one.
     * */
    Room* west;

    map<string, Room*> exits;

public:
    /**
     * Constructs a new Room.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    Room(const string *_name, const string *_desc);

    /**
     * Removes a destroyed room from the global list if it's there.
     */
    ~Room();

    /**
     * Outputs the name and description of the room
     * in standard format.
     */
    void describe() const;

    /**
     * List storing all rooms that have been registered via addRoom().
     */
    static list<Room*> rooms;

    /**
     * Creates a new Room with the given parameters and register it with the static list.
     * @param _name Name of the room.
     * @param _desc Description of the room.
     */
    static Room* addRoom(const string* _name, const string* _desc);
    static void addRoom(Room* room);


    Room* getNorth() const;
    void setNorth(Room* _north);

    Room* getEast() const;
    void setEast(Room* _east);

    Room* getSouth() const;
    void setSouth(Room* _south);

    Room* getWest() const;
    void setWest(Room* _west);

    Room* getExit(const string& direction) const;
    void setExit(const string& direction, Room* room);

    void addObject(GameObject *object);
    void removeObject(GameObject *object);

    GameObject *getObject(string secondWord) const;
    bool hasObject(string secondWord) const;

    list<GameObject *> getObjects() const;

    const string *getName() const;

/*
 * Modify the Room class so that each Room includes a list of GameObjects in the room.
 * */
list<GameObject*> objects;
};

#endif //TEXTADV_ROOM_H
