//
// Created by 76878 on 2023/12/18.
//

#include "SaveAndLoad.h"
#include <iostream>
#include <fstream>

/* Save the game to a file.
 * */
void SaveAndLoad::save(State* currentState, list<Room*>& rooms)
{
    string saveFileName;
    cout << endl;
    cout << "Enter the save file: ";
    getline(cin, saveFileName);
    ofstream saveFile;
    saveFile.open(saveFileName, ios::binary|ios::out);

    Room* currentRoom = currentState->getCurrentRoom();
    int currentRoom_Index = 0;
    for (auto it = Room::rooms.begin(); it != Room::rooms.end(); it++)
    {
        const string *roomName = (*it)->getName();
        if (*roomName == *(currentRoom->getName()))
        {
            currentRoom_Index = distance(Room::rooms.begin(), it);
            break;
        }
    }
    saveFile.write((char*)&currentRoom_Index, sizeof(currentRoom_Index));

    // Room Objects
    for (auto it = Room::rooms.begin(); it != Room::rooms.end(); it++)
    {
        int objListSize = (*it)->objects.size();
        saveFile.write((char*)&objListSize, sizeof(objListSize));
        for (auto& obj : (*it)->objects)
        {
            int index = 0;
            for (int i = 0; i < mGameObjects.size(); i++)
            {
                auto& mObjKeyWord = mGameObjects[i]->keyword;
                if (*mObjKeyWord == *(obj->keyword))
                {
                    index = i;
                    break;
                }
            }
            saveFile.write((char*)&index, sizeof(index));
        }
    }

    // Inventory
    int inventory_Size = currentState->inventory.size();
    saveFile.write((char*)&inventory_Size, sizeof(inventory_Size));
    for (auto& obj : currentState->inventory)
    {
        int index = 0;
        for (int i = 0; i < mGameObjects.size(); i++)
        {
            auto& mObjKeyWord = mGameObjects[i]->keyword;
            if (*mObjKeyWord == *(obj->keyword))
            {
                index = i;
                break;
            }
        }
        saveFile.write((char*)&index, sizeof(index));
    }
    saveFile.close();
    cout << endl;
    cout << "Save successfully!" << endl;
    cout << "---------" << endl;
}

/* Load the game from a file.
 * */
void SaveAndLoad::load(State* currentState, list<Room*>& rooms)
{
    string saveFileName;
    cout << endl;
    cout << "Enter the save file: ";
    getline(cin, saveFileName);
    ifstream loadFile;
    loadFile.open(saveFileName, ios::binary|ios::in);
    if (!loadFile.is_open())
    {
        cout << endl;
        cout << "Open failed!" << endl;
        cout << "---------" << endl;
    } else
    {
        cout << endl;
        cout << "Load successfully!" << endl;
        cout << "---------" << endl;
    }

    Room* currentRoom = nullptr;
    int currentRoomIndex = 0;
    loadFile.read((char*)&currentRoomIndex, sizeof(currentRoomIndex));
    for (auto it = Room::rooms.begin(); it != Room::rooms.end(); it++)
    {
        int index = distance(Room::rooms.begin(), it);
        if (index == currentRoomIndex)
        {
            currentRoom = (*it);
            break;
        }
    }

    for (auto it = Room::rooms.begin(); it != Room::rooms.end(); it++)
    {
        int objects_Size = 0;
        loadFile.read((char*)&objects_Size, sizeof(objects_Size));
        (*it)->objects.clear();
        for (int i = 0; i < objects_Size; i++)
        {
            int index = 0;
            loadFile.read((char*)&index, sizeof(index));

            (*it)->objects.push_back(mGameObjects[index]);
        }
    }

    currentState->inventory.clear();
    int inventory_Size = 0;
    loadFile.read((char*)&inventory_Size, sizeof(inventory_Size));
    for (int i = 0; i < inventory_Size; i++)
    {
        int index = 0;
        loadFile.read((char*)&index, sizeof(index));
        currentState->inventory.push_back(mGameObjects[index]);
    }
    loadFile.close();
    cout << endl;
    currentState->goTo(currentRoom);
}

