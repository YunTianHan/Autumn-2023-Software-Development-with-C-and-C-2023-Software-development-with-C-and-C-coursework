

#ifndef TEXTADV_STRINGS_H
#define TEXTADV_STRINGS_H


#include <string>

const std::string r1name = "room 1";
const std::string r1desc = "You are in room 1. It's really quite boring, but then, it's just for testing really. There's a passage to the north or south.";
const std::string r2name = "Blue Room";
const std::string r2desc = "You are the blue room. You know because it's blue. That's about all though. There's a passage to the south or east.";
const std::string r3name = "Red Room";
const std::string r3desc = "You are the red room. You know because it's red. That's about all though. There's a passage to the north or east.";
const std::string r4name = "Wind Room";
const std::string r4desc = "You are the wind room. You know because you get the power of wind. That's about all though. There's a passage to the south or west.";
const std::string r5name = "Fire Room";
const std::string r5desc = "You are the fire room. You know because you get the power of fire. That's about all though. There's a passage to the north or west.";
const std::string r6name = "Water Room";
const std::string r6desc = "You are the water room. You know because you get the power of water. That's about all though. There's a passage to the north or south.";

const std::string object1name = "Backpack";
const std::string object1desc = "A backpack. It's empty now.";
const std::string object1keyword = "B";

const std::string object2name = "Sword";
const std::string object2desc = "A sword. It's sharp,you feel a little familiar.";
const std::string object2keyword = "S";

const std::string object3name = "Mystery ring";
const std::string object3desc = "A ring. There are faint soul fluctuations.";
const std::string object3keyword = "R";

const std::string F_object1name = "Apple";
const std::string F_object1desc = "A apple. It's sweet.";
const std::string F_object1keyword = "Apple";

const std::string F_object2name = "Bread";
const std::string F_object2desc = "A bread. It's soft.";
const std::string F_object2keyword = "Bread";

const std::string F_object3name = "Meat";
const std::string F_object3desc = "A meat. It's delicious.";
const std::string F_object3keyword = "Meat";

const std::string badExit = "You can't go that way.";
const std::string badCommand = "I don't understand that, this is an invalid command!";
const std::string badMapCommand = "You hit the wall, man. This room has no exit in this direction!.";
const std::string noObject = "The object do not exist.";
const std::string badObject = "You can not command it because there is no the object in the current room or in your inventory.";
const std::string getSuccess = "You get the object.";
const std::string getFail = "You can't get the object,it's already in your inventory or not in the room.";
const std::string dropSuccess = "You drop the object.";
const std::string dropFail = "You can't drop the object,it's already in current room or not in the inventory.";


#endif //TEXTADV_STRINGS_H
