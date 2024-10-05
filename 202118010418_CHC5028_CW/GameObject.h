//
// Created by 76878 on 2023/12/18.
//

#ifndef TEXTADV_GAMEOBJECT_H
#define TEXTADV_GAMEOBJECT_H

#include <list>
#include <string>

using namespace std;

class GameObject {
    // It should contain at least a short name, a long description, and a keyword (for the player to use when typing commands).
    const string* name;
    const string* description;
public:
    GameObject(const string *_name, const string *_desc, const string *_keyword);
    ~GameObject();
    const string* getName() const;
    const string* getDescription() const;
    const string* getKeyword() const;

    virtual bool isFood();
    virtual int getEnergy();

    const string* keyword;
};


#endif //TEXTADV_GAMEOBJECT_H
