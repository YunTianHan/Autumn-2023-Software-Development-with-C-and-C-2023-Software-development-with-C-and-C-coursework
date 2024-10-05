//
// Created by 76878 on 2023/12/18.
//

#ifndef TEXTADV_FOODOBJECT_H
#define TEXTADV_FOODOBJECT_H

/*
 * Create a derived class FoodObject of GameObject class, it should contain an
 * integer-type property named energy which should be limited in a range of 1-
 * 10.
 * */

#include "GameObject.h"

class FoodObject : public GameObject {
    int energy;
public:
    FoodObject(const string *_name, const string *_desc, const string *_keyword, int _energy);
    ~FoodObject();

    virtual int getEnergy() override;
    virtual bool isFood() override;
};


#endif //TEXTADV_FOODOBJECT_H
