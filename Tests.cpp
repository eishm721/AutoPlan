/*
 * Filename: Tests.cpp
 *
 * Includes a collection of tests for optimizing RandomPQueue data structure
 * Uses simulations to model long-term allocation frequencies
 */
#include "console.h"
#include "RandomPQueue.h"
#include <unordered_map>

using namespace std;

/* Premade breakfast food sets for testing */
const string rareItem = "9";
const vector<string> potentialFoods = {"1", "2", "3", "4", "5", "6", "7", "8", rareItem};


/* Helper Functions to preprocess data */
class HelperFcns {
public:
    // Builds a vector of size n with unique, nonempty string elements
    vector<string> buildUniqueVectorSizeN(int n) {
        vector<string> elems;
        for (int i = 1 ; i <= n; i++) {
            string temp;
            for (int j = 0; j < i; j++) {
                temp += 'a';
            }
            elems.push_back(temp);
        }
        return elems;
    }

    // Computes average of a vector of ints
    double avg(const vector<int>& elems) {
        double sum = 0;
        for (int elem: elems) {
            sum += elem;
        }
        return sum / elems.size();
    }

    // checks if a data structure contains a target string input
    template <typename T>
    bool contains(const T& elems, const string& target) {
        for (const string& elem: elems) {
            if (elem == target) return true;
        }
        return false;
    }

    // builds a RP queue from a set of  options
    RandomPQueue buildQueue(const vector<string>& options) {
        RandomPQueue items;
        for (const string& item: options) {
            // special casing for rare items
            if (item == rareItem) {
                items.add(item, true);
            } else {
                items.add(item);
            }
        }
        return items;
    }

    // prints out schedules
    void generateSchedules(const vector<string>& options) {
        // print the queue
        RandomPQueue elems = buildQueue(options);
        cout << "Your current queue: " << endl;
        elems.printDebugInfo();
        cout << endl;

        // generate a day-by-day schedule based on user input
        cout << "Number of items to choose from: " << elems.size() << endl;
        cout << "How many days of options?: ";
        int days;
        cin >> days;
        cout << endl;
        for (int i = 1; i <= days; i++) {
            cout << "Day " << i << ": ";
            if (i < 10) {
                cout << " ";   // formating
            }
            cout << elems.get() << endl;
        }
        cout << endl;
    }
};


/* Simulation Tests */
class ReallocationGapTest: public HelperFcns {
public:
    // Finds average number of days before a item is seen again */
    double avgGapBtwn(const vector<string>& options) {
        RandomPQueue elems = buildQueue(options);   // queue
        vector<int> gaps;    // set of all gaps

        // Creates a vector of all the gap sizes */
        vector<string> curr;              // current set of items seen
        int gapSize = 0;                  // current gap size
        for (int i = 0; i < 100000; i++) {
            string item = elems.get();
            // if the item has been recently seen, keeps track of the gapSize
            if (contains(curr, item)) {
                gaps.push_back(gapSize);
                gapSize = 0;
                curr.clear();
            // otherwise keeps incrementing temp gap size
            } else {
                curr.push_back(item);
                gapSize++;
            }
        }
        return avg(gaps);
    }

    // Finds avg number of days until an item is repeated for various RP queue sizes
    void runAvgReallocationGap() {
        for (int i = 4; i < 15; i++) {
            vector<string> elems = buildUniqueVectorSizeN(i);
            cout << i << ", " << avgGapBtwn(elems) << endl;
        }
        cout << endl;
    }
};

class RareItemTests: public HelperFcns {
public:
    // avg freq of rare item
    void rareItemExpFreqTest() {
        // builds map of how many times all items appear in O(n)
        RandomPQueue elems = buildQueue(potentialFoods);
        unordered_map<string, int> freq;
        double totalCalls = 100000;
        for (int i = 0; i < totalCalls; i++) {
            freq[elems.get()]++;
        }
        // process data and output
        double newFreq = freq[rareItem] / totalCalls;
        double randFreq = freq[randomNonRareItem(elems)] / totalCalls;
        cout << "Actual Freq of a NORMAL item:   " << randFreq << endl;
        cout << "Actual freq of a RARE item:     " << newFreq << endl;
        cout << "Percent reducton in freqency:   " << -100 * ((newFreq - randFreq) / (randFreq)) << "%"  << endl;
        cout << endl;
    }

    // avg gap between rare items
    void rareItemAvgGapTest() {
        RandomPQueue elems = buildQueue(potentialFoods);
        vector<int> gaps;
        int currGap = 0;
        // keeps track of the gaps between a recurrence of a rare item
        for (int i = 0; i < 100000; i++) {
            string item = elems.get();
            if (item != rareItem) {
                currGap++;
            } else {
                gaps.push_back(currGap);
                currGap = 0;
            }
        }
        // processing and output
        ReallocationGapTest realloc;
        cout << "Expected gap btwn RARE items:    " << elems.size() << endl;
        cout << "Average gap btwn RARE items:     " << avg(gaps) << endl;
        cout << "Average gap btwn NORMAL items:   " << realloc.avgGapBtwn(potentialFoods);
        cout << endl;
    }

    // Tests optimizations for rare items
    void rareAllTests() {
        rareItemExpFreqTest();
        rareItemAvgGapTest();
    }

private:
    // gets a random nonrare item from a queue
    string randomNonRareItem(RandomPQueue elems) {
        string random = elems.get();
        while (random == rareItem) {
            random = elems.get();
        }
        return random;
    }
};

class FullTest: public HelperFcns {
public:
    // Test a full, realistic foodqueue implementation for breakfast
    void fullTest() {
        generateSchedules(potentialFoods);
    }
};

int main() {
    return 0;
}
