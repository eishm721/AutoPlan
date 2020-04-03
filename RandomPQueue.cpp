/*
 * Filename: RandomPQueue.h"
 *
 * implementation of RandomPQueue class
 * Stores collection of items which can be selected with pseudorandom ordered
 * Shuffling algorithms employed for ideal reallocation frequencies
 */
#include "RandomPQueue.h"
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

/* Helper functions to implement Stanford CPP library features */
int RandomPQueue::randomInt(int first, int second) const {
    unsigned seed = chrono::steady_clock::now().time_since_epoch().count();
    default_random_engine randEngine(seed);
    int size = second - first + 1;   // inclusive range
    return (randEngine() % size) + first;
}

string RandomPQueue::toLowerCase(const string& input) const {
    string result;
    for (char ch: input) {
        result += tolower(ch);
    }
    return result;
}


/* Private Helper functions: Reshuffling Algorithm Implementation */
int RandomPQueue::priorityFcn(bool isRare) {
    // rare foods are seen less frequently
    if (size() < 5 || isRare) {
        return size();
    // occasionally inserts at front half
    } else if (randomInt(0, 99) == 1) {
        return randomInt(1, size() / 2);
    // more frequently in last ~40
    } else {
        return randomInt(58 * size() / 100, size());
    }
}


/* Core functionality (Public implementation) */
int RandomPQueue::size() const {
    return elems.size();
}

bool RandomPQueue::isEmpty() const {
    return size() == 0;
}

bool RandomPQueue::contains(const string& input) const {
    for (Item elem: elems) {
        if (elem.name == toLowerCase(input)) {
            return true;
        }
    }
    return false;
}

void RandomPQueue::add(const string& input, bool isRare) {
    string inputName = toLowerCase(input);     // store as lowercase
    Item item = {inputName, isRare};
    if (inputName != "" && !contains(inputName)) {
        // inserts item at random index, depending on rarity
        int start;
        if (isRare) {
            start = size() / 2;
        } else {
            start = 0;
        }
        int priority = randomInt(start, size());
        elems.insert(elems.begin() + priority, item);
    }
}

void RandomPQueue::add(const string& input) {
    // overloaded to autoinitialize rarity as false if not specified
    add(input, false);
}

string RandomPQueue::get() {
    if (isEmpty()) throw "Queue is empty";

    Item item = elems.front();
    elems.erase(elems.begin());
    elems.insert(elems.begin() + priorityFcn(item.isRare), item);
    return item.name;
}

void RandomPQueue::deleteItem(const string& input) {
    if (isEmpty()) throw "Queue is empty";

    int index = 0;
    while (input != elems[index].name) {
        index++;
    }
    elems.erase(elems.begin() + index);
}

void RandomPQueue::printDebugInfo() const {
    for (int i = 0; i < size(); i++) {
        cout << "Index: " << i << ", Value: " << elems[i].name << endl;
    }
}
