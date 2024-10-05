
#include <iostream>
#include <cstdint>
#include <thread>
#include <mutex>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "FoodObject.h"
#include "GameObject.h"
#include "SaveAndLoad.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;
SaveAndLoad saveAndLoad;
/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Check if the second word of the command is an object.
 * @param secondWord The second word of the command.
 * @return True if the second word is an object, false otherwise.
 */
bool hasObject(string secondWord) {
    for (auto it = saveAndLoad.mGameObjects.begin(); it != saveAndLoad.mGameObjects.end(); ++it) {
        const string *keyword = (*it)->getKeyword();
        if (*keyword == secondWord) {
            return true;
        }
    }
    return false;
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r1 = new Room(&r1name, &r1desc);
    auto * r2 = new Room(&r2name, &r2desc);
    /*Room room3(&r3name,&r3desc);
    Room* r3=&room3;*/
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r5 = new Room(&r5name, &r5desc);
    auto * r6 = new Room(&r6name, &r6desc);
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);
    Room::addRoom(r6);

    /*
    r1->setExit("north", r2);
    r1->setExit("n", r2);
    r1->setExit("south", r3);
    r1->setExit("s", r3);

    r2->setExit("south", r1);
    r2->setExit("s", r1);
    r2->setExit("east", r4);
    r2->setExit("e", r4);

    r3->setExit("north", r1);
    r3->setExit("n", r1);
    r3->setExit("east", r5);
    r3->setExit("e", r5);

    r4->setExit("west", r2);
    r4->setExit("w", r2);
    r4->setExit("south", r6);
    r4->setExit("s", r6);

    r5->setExit("west", r3);
    r5->setExit("w", r3);
    r5->setExit("north", r6);
    r5->setExit("n", r6);

    r6->setExit("north", r4);
    r6->setExit("n", r4);
    r6->setExit("south", r5);
    r6->setExit("s", r5);
     */

    r1->setNorth(r2);
    r1->setSouth(r3);

    r2->setSouth(r1);
    r2->setEast(r4);

    r3->setNorth(r1);
    r3->setEast(r5);

    r4->setWest(r2);
    r4->setSouth(r6);

    r5->setWest(r3);
    r5->setNorth(r6);

    r6->setNorth(r4);
    r6->setSouth(r5);

    //Modify initRooms to create some GameObjects and FoodOjects and put them in the rooms.

    auto * object1 = new GameObject(&object1name, &object1desc, &object1keyword);
    auto * object2 = new GameObject(&object2name, &object2desc, &object2keyword);
    auto * object3 = new GameObject(&object3name, &object3desc, &object3keyword);
    FoodObject * F_object1 = new FoodObject(&F_object1name, &F_object1desc, &F_object1keyword, 50 );
    FoodObject * F_object2 = new FoodObject(&F_object2name, &F_object2desc, &F_object2keyword, 2);
    FoodObject * F_object3 = new FoodObject(&F_object3name, &F_object3desc, &F_object3keyword, 3);


    r1->addObject(object1);
    r1->addObject(F_object1);
    r2->addObject(object2);
    r3->addObject(object3);
    r4->addObject(F_object1);
    r5->addObject(F_object2);
    r6->addObject(F_object3);

    saveAndLoad.mGameObjects.push_back(object1);
    saveAndLoad.mGameObjects.push_back(object2);
    saveAndLoad.mGameObjects.push_back(object3);
    saveAndLoad.mGameObjects.push_back(F_object1);
    saveAndLoad.mGameObjects.push_back(F_object2);
    saveAndLoad.mGameObjects.push_back(F_object3);

}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}
/* 原始计时器入口 */
//auto last_Time = std::chrono::steady_clock::now();

/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver = false;

    std::mutex strengthMutex; // 创建互斥锁
    int strength = currentState->getStrength(); // 获取初始体力值,让两个循环共享一个体力值
    std::thread t([&gameOver, &strength, &strengthMutex]() { // 创建一个新线程来计时
                      while (!gameOver) {
                          std::this_thread::sleep_for(std::chrono::seconds(1)); // 线程休眠1秒
                          {
                              std::lock_guard<std::mutex> lock(strengthMutex); // 加锁
                              // 每秒体力值减30,测试自动终止
                              //strength -= 30;
                              // 正常减一
                              strength--;
                          } // 锁自动释放
                          if (strength <= 0) {
                              gameOver = true;
                              std::cout << "You have no strength left. Game over." << std::endl;
                              std::exit(0);
                          }
                      }
                  }
    ); // 创建一个新线程来计时


    while (!gameOver) {

        /*Modify the gameLoop method to reduce strength by 1 per minute, when
         * strength goes to 0, the program shall be terminated.
         * */
        /*if (currentState->getStrength() <= 0) {
            std::cout << "You have no strength left. Game over." << std::endl;
            gameOver = true;
        } else {
            // 获取当前时间
            auto current_Time = std::chrono::steady_clock::now();
            // 计算时间差
            int time_Sqan = std::chrono::duration_cast<std::chrono::seconds>(current_Time - last_Time).count();
            //
            int currentStrength = currentState->getStrength();
            currentState->setStrength(currentStrength - time_Sqan);
            last_Time = current_Time;
            // 打印当前力量值
            cout<<endl;
            std::cout << "Your strength is " << currentState->getStrength() << "." << std::endl;
        }*/

        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);

        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */
        auto endOfVerb = static_cast<uint8_t>(commandBuffer.find(' '));

        /* Modify the gameLoop method to pay attention to the second word of the command
         * the player enters, if there is one.
         * */
        if (endOfVerb != std::string::npos && endOfVerb < commandBuffer.length()) {
            auto endOfSecondWord = static_cast<uint8_t>(commandBuffer.find(' ', endOfVerb + 1));
            string secondWord = commandBuffer.substr(endOfVerb + 1, endOfSecondWord - endOfVerb - 1);

            /* Modify the gameLoop command to search through a) getObjects in the current room,
             * and b) getObjects in the inventory, for an object with a keyword matching the second
             * word of the command the player typed.
             * */
            bool objectHave = false;
            bool objectOK = false;
            if (!objectOK) {
                if (hasObject(secondWord)) {
                    objectHave = true;
                    Room *currentRoom = currentState->getCurrentRoom();
                    if (currentState->hasObject(secondWord) || currentRoom->hasObject(secondWord)) {
                        objectOK = true;
                    }
                }
            }

            /* Implement the player command get which, when typed with an object keyword, will
             * appropriate errors if the object is not in the room or the object is already in the
             * inventory or the object does not exist.
             * */
            if (commandBuffer.compare(0, endOfVerb, "get") == 0) {
                commandOk = true;
                if (!objectHave) {
                    cout << endl;
                    wrapOut(&noObject);
                    wrapEndPara();
                } else {
                    if (objectOK) {
                        Room *currentRoom = currentState->getCurrentRoom();
                        if (currentState->hasObject(secondWord) == false) {
                            GameObject *object = currentRoom->getObject(secondWord);
                            currentState->addObject(object);
                            currentRoom->removeObject(object);
                            cout << endl;
                            wrapOut(&getSuccess);
                            wrapEndPara();
                        } else {
                            cout << endl;
                            wrapOut(&getFail);
                            wrapEndPara();
                        }
                    } else {
                        cout << endl;
                        wrapOut(&badObject);
                        wrapEndPara();
                    }
                }
            }

            /*Implement the player command drop which, when typed with an object keyword,
             * will move that object from the inventory into the current room list. It should display
             * appropriate errors if the object is not in the inventory or already in the room, or does
             * not exist, etc.
             * */
            if (commandBuffer.compare(0, endOfVerb, "drop") == 0) {
                commandOk = true;
                if (!objectHave) {
                    cout << endl;
                    wrapOut(&noObject);
                    wrapEndPara();
                } else {
                    if (objectOK) {
                        Room *currentRoom = currentState->getCurrentRoom();
                        if (currentRoom->hasObject(secondWord) == false) {
                            GameObject *object = currentState->getObject(secondWord);
                            currentRoom->addObject(object);
                            currentState->removeObject(object);
                            cout << endl;
                            wrapOut(&dropSuccess);
                            wrapEndPara();
                        } else {
                            cout << endl;
                            wrapOut(&dropFail);
                            wrapEndPara();
                        }
                    } else {
                        cout << endl;
                        wrapOut(&badObject);
                        wrapEndPara();
                    }
                }
            }

            /* Implement the player command examine which, when typed with an object
             * keyword, will print out the long description of that object.
             * */
            if (commandBuffer.compare(0, endOfVerb, "examine") == 0) {
                commandOk = true;
                if (!objectHave) {
                    cout << endl;
                    wrapOut(&noObject);
                    wrapEndPara();
                } else {
                    if (objectOK) {
                        Room *currentRoom = currentState->getCurrentRoom();
                        if (currentState->hasObject(secondWord)) {
                            GameObject *object = currentState->getObject(secondWord);
                            cout << endl;
                            cout << "Name: " << *(object->getName()) << endl;
                            cout << "Description: " << *(object->getDescription()) << endl;
                            cout << "_________" << endl;
                        } else if (currentRoom->hasObject(secondWord)) {
                            GameObject *object = currentRoom->getObject(secondWord);
                            cout << endl;
                            cout << "Name: " << *(object->getName()) << endl;
                            cout << "Description: " << *(object->getDescription()) << endl;
                            cout << "_________" << endl;
                        }
                    } else {
                        cout << endl;
                        wrapOut(&badObject);
                        wrapEndPara();
                    }
                }
            }

            /* Implement the player command eat which, when typed with a food object
             * keyword, will print out the player’s strength after adding the energy of the
             * food object to the player’s strength, which should not exceed 100.
             * */
            if (commandBuffer.compare(0, endOfVerb, "eat") == 0) {
                commandOk = true;
                if (!objectHave) {
                    cout << endl;
                    wrapOut(&noObject);
                    wrapEndPara();
                } else {
                    Room *currentRoom = currentState->getCurrentRoom();
                    if (currentState->hasObject(secondWord)) {
                        auto *object = currentState->getObject(secondWord);
                        /*
                        if (object->isFood()) {
                        last_Time = std::chrono::steady_clock::now();
                        int energy = object->getEnergy();
                        int currentStrength = currentState->getStrength();
                        int newStrength = currentStrength + energy;
                        if (newStrength >= 100) {
                          currentState->setStrength(100);
                        } else {
                          currentState->setStrength(newStrength);
                        }
                        currentState->removeObject(object);
                        cout << "You have eaten the object." << endl;
                        cout << "Your strength is " << currentState->getStrength() << "." << endl;
                        } else {
                        cout << "This is not a food object." << endl;
                        }
                        */
                        if (object->isFood()) {
                            int energy = object->getEnergy();
                            {
                                std::lock_guard<std::mutex> lock(strengthMutex); // 加锁
                                int newStrength = strength + energy;
                                if (newStrength >= 100) {
                                    strength = 100;
                                } else {
                                    strength = newStrength;
                                }
                            } // 锁自动释放
                            currentState->removeObject(object);
                            cout << endl;
                            cout << "You have eaten the object." << endl;
                            cout << "_________" << endl;
                        } else {
                            cout << endl;
                            cout << "This is not a food object." << endl;
                            cout << "_________" << endl;
                        }
                    } else {
                        cout << endl;
                        cout << "You don't have this object." << endl;
                        cout << "_________" << endl;
                    }
                }
            }
        }


        /*We could copy the verb to another string but there's no reason to, we'll just compare it in place.
        Command to go north.*/
        if (((commandBuffer.compare(0, endOfVerb, "north") == 0) || (commandBuffer.compare(0, endOfVerb, "n") == 0))) {
            commandOk = true;  //Confirm command has been handled
            /*See if there's a north exit*/
            Room *northRoom = currentState->getCurrentRoom()->getNorth();
            if (northRoom == nullptr) {  //there isn't
                wrapOut(&badExit);       //Output the "can't go there" message
                wrapEndPara();
            } else {                     //There is
                currentState->goTo(northRoom);  //Update state to that room - this will also describe it
            }
        }

        /*Command to go east.*/
        if ((commandBuffer.compare(0, endOfVerb, "east") == 0) || (commandBuffer.compare(0, endOfVerb, "e") == 0)) {
            commandOk = true;  //Confirm command has been handled
            /*See if there's an east exit*/
            Room *eastRoom = currentState->getCurrentRoom()->getEast();
            if (eastRoom == nullptr) {  //there isn't
                wrapOut(&badExit);       //Output the "can't go there" message
                wrapEndPara();
            } else {                     //There is
                currentState->goTo(eastRoom);  //Update state to that room - this will also describe it
            }
        }

        /*Command to go south.*/
        if ((commandBuffer.compare(0, endOfVerb, "south") == 0) || (commandBuffer.compare(0, endOfVerb, "s") == 0)) {
            commandOk = true;  //Confirm command has been handled
            /*See if there's a south exit*/
            Room *southRoom = currentState->getCurrentRoom()->getSouth();
            if (southRoom == nullptr) {  //there isn't
                wrapEndPara();
            } else {                     //There is
                currentState->goTo(southRoom);  //Update state to that room - this will also describe it
            }
        }

        /*Command to go west.*/
        if ((commandBuffer.compare(0, endOfVerb, "west") == 0) || (commandBuffer.compare(0, endOfVerb, "w") == 0)) {
            commandOk = true;  //Confirm command has been handled
            /* See if there's a west exit */
            Room *westRoom = currentState->getCurrentRoom()->getWest();
            if (westRoom == nullptr) {  //there isn't
                wrapOut(&badExit);       //Output the "can't go there" message
                wrapEndPara();
            } else {                     //There is
                currentState->goTo(westRoom);  //Update state to that room - this will also describe it
            }
        }

        /*Implement the player command inventory which will print out the short names of
         * all the getObjects in the inventory.
         * */
        if (commandBuffer.compare(0, endOfVerb, "inventory") == 0) {
            commandOk = true;
            currentState->printInventory();
            cout << endl;
        }

        // Implement the player command save which will save the current game state to a file.
        if (commandBuffer.compare(0, endOfVerb, "save") == 0) {
            commandOk = true;
            saveAndLoad.save(currentState, Room::rooms);
        }

        // Implement the player command load which will load a saved game state from a file.
        if (commandBuffer.compare(0, endOfVerb, "load") == 0) {
            commandOk = true;
            saveAndLoad.load(currentState,Room::rooms);
        }

        /* Quit command */
        if ((commandBuffer.compare(0, endOfVerb, "quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if (!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }


        {
            std::lock_guard<std::mutex> lock(strengthMutex); // 加锁
            cout << "Your strength is " << strength << "." << endl;
            if (strength <= 50 && strength > 0) {
                cout << endl;
                std::cout << "You are hungry!" << std::endl;
                std::cout << "You need eat food!" << std::endl;
            }
        } // 锁自动释放

        /* map */
        /*if (commandBuffer.compare(0,endOfVerb,"quit") != 0) {
            string direction = commandBuffer.substr(0, endOfVerb);
            Room* currentRoom = currentState->getCurrentRoom();
            if (currentRoom->getExit(direction) != nullptr) {
                commandOk = true;
                Room* nextRoom = currentRoom->getExit(direction);
                currentState->goTo(nextRoom);
            } else {
                wrapOut(&badMapCommand);
                wrapEndPara();
            }
        }*/
    }
    t.join(); // 等待计时线程结束
}



int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}