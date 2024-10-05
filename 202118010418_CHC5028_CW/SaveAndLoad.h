//
// Created by 76878 on 2023/12/18.
//

#ifndef TEXTADV_SAVEANDLOAD_H
#define TEXTADV_SAVEANDLOAD_H


#include "State.h"
#include <vector>
using namespace std;

class SaveAndLoad
{
public:
    void save(State* currentState, std::list<Room*>& rooms);
    void load(State* currentState, std::list<Room*>& rooms);
    vector<GameObject*> mGameObjects;
};


#endif //TEXTADV_SAVEANDLOAD_H
