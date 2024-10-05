//
// Created by 76878 on 2023/12/18.
//

#include <iostream>
#include "FoodObject.h"

FoodObject::FoodObject(const string *_name, const string *_desc, const string *_keyword,const int _energy) :
        GameObject(_name, _desc, _keyword), energy(_energy) {
    if ( energy > 10 ) {
        energy = 10;
    }
    if ( energy < 0 ) {
        energy = 0;
    }
}

FoodObject::~FoodObject() {
    std::cout << "Food is being deleted" << std::endl;
}

int FoodObject::getEnergy() {
    return energy;
}

bool FoodObject::isFood() {
    return true;
}
