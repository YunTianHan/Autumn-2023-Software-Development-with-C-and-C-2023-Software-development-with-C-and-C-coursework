//
// Created by 76878 on 2023/12/18.
//

#include <string>
#include "GameObject.h"

GameObject::GameObject(const string *_name, const string *_desc, const string *_keyword) :
        name(_name), description(_desc), keyword(_keyword) {
};

GameObject::~GameObject() {
}

const string* GameObject::getName() const {
    return name;
}

const string* GameObject::getDescription() const {
    return description;
}

const string* GameObject::getKeyword() const{
    return keyword;
}

bool GameObject::isFood() {
    return false;
}

int GameObject::getEnergy() {
    return 0;
}
