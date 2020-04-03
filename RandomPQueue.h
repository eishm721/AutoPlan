/*
 * Filename: RandomPQueue.h"
 *
 * Header file for interface of RandomPQueue class
 */

#ifndef RandomPQueue_Included
#define RandomPQueue_Included

#include <string>
#include <vector>

class RandomPQueue {
public:
    /**
     * Returns size of a RP queue
     */
    int size() const;

    /**
     * Returns if a RP queue is empty
     */
    bool isEmpty() const;

    /**
     * Returns if a RP queue contains a given item
     */
    bool contains(const std::string& item) const;

    /**
     * Randomly inserts an item into a RP queue, autoinitializes rarity as false
     */
    void add(const std::string& item);

    /**
     * Randomly inserts adds an item to a RP queue given if the item is rare or not
     */
    void add(const std::string& item, bool isRare);

    /**
     * Psuedurandomly selects an item and reinserts it back into RP queue
     * Implements custom reshuffling algorithm tailored for ideal reallocation frequency
     */
    std::string get();

    /**
     * Deletes an item from a food queue
     */
    void deleteItem(const std::string& item);

    /**
     * FOR TESTING PURPOSES
     * Prints all the elements of a RP queue in order
     */
    void printDebugInfo() const;

private:
    struct Item {
        std::string name;
        bool isRare;
    };
    std::vector<Item> elems;    // queue of items
    std::string toLowerCase(const std::string& input) const;   // makes string lowercase

    /**
     * Reshuffling algorithm that outputs the priority in which a given element
     * should be drawn given its rarity
     */
    int priorityFcn(bool isRare) const;

    /**
     * Uses default random engine to output a random integer btwn two numbers INCLUSIVELY
     */
    int randomInt(int first, int second) const;
};

#endif
