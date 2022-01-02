using namespace std;

#include <iostream>
#include <vector>

// first, we need to tell the program which animals can eat which other animals

bool canEat(string animal1, string animal2) {
    
    if (animal1 == "antelope") {
        if (animal2 == "grass") {
            return true;
        }
    }

    else if (animal1 == "big-fish") {
        if (animal2 == "little-fish") {
            return true;
        }
    }

    else if (animal1 == "bug") {
        if (animal2 == "bug" || animal2 == "leaves") {
            return true;
        }
    }

    else if (animal1 == "bear") {
        if (animal2 == "big-fish" || animal2 == "bug" || animal2 == "chicken" || animal2 == "cow" || animal2 == "leaves" || animal2 == "sheep") {
            return true;
        }
    }

    else if (animal1 == "chicken") {
        if (animal2 == "bug") {
            return true;
        }
    }

    else if (animal1 == "cow") {
        if (animal2 == "grass") {
            return true;
        }
    }

    else if (animal1 == "fox") {
        if (animal2 == "chicken" || animal2 == "sheep") {
            return true;
        }
    }

    else if (animal1 == "giraffe") {
        if (animal2 == "leaves") {
            return true;
        }
    }

    else if (animal1 == "lion") {
        if (animal2 == "antelope" || animal2 == "cow") {
            return true;
        }
    }

    else if (animal1 == "panda") {
        if (animal2 == "leaves") {
            return true;
        }
    }

    else if (animal1 == "sheep") {
        if (animal2 == "grass") {
            return true;
        }
    }

    return false;
}

// next, we create "eat" messages for each pair of animals
// if animal1 can eat animal2, we say "animal1 eats animal2"
// otherwise, indicate that animal1 does not eat animal2

string eat(string animal1, string animal2) {
    if (canEat(animal1, animal2) == true) {
        return animal1 + " eats " + animal2;
    }

    else {
        return animal1 + " does not eat " + animal2;
    }
}

// define a method that converts a string to a vector of strings, delimited by a provided token
vector<string> stringToVec(string str, string token, vector<string> accumulator = {}) {
    // if the token does not occur in the string...
    if (str.find(token) == string::npos) {
        // simply return a size-1 vector containing the input string
        accumulator.push_back(str);
        return accumulator;
    }

    // otherwise, push every character before the first occurrence of the token to the vector...
    accumulator.push_back(str.substr(0, str.find(token)));

    // remove every character up to the first occurence of the token from the original string...
    str = str.substr(str.find(token) + 1);

    // begin the process again using the updated string and accumulator vector
    return stringToVec(str, token, accumulator);
}

// and define a method of converting a vector of strings back to a comma-sepparated string
string vecToString(vector<string> list) {
    string newString = "";                  // instatntiate an empty string

    // for each successive element of the vector...
    for (int i = 0; i < list.size(); i++) {
        // if we are at the last element...
        if (i == list.size() - 1) {
            // concatenate the i'th element to newString
            newString = newString + list[i];
        }

        else {
            // otherwise, do the same, but also add a comma
            newString = newString + list[i] + ",";
        }
    }

    // return the string
    return newString;
}

// now we define the driver function for the zoo disaster
// zooDisaster returns void, and takes a string called animals consisting of animal names separated by commas...
// an unsigned int called index that determines which animal in the simulation we are concerned with...
// and an accumulator vector of strings that contains all of the necessary messages for the requirements of the simulation...
// at any given time
// when the simulation finishes, we output every message in accumulator

void zooDisaster (string animals, unsigned int index, vector<string> accumulator) {

    // first, append the original string of animals to our accumulator

    if (accumulator.size() == 0) {
        accumulator.push_back(animals);
    }

    // next, convert the string to a vector

    vector<string> listOfAnimals = stringToVec(animals, ",");

    // if the list has only one animal, nothing happens
    if (listOfAnimals.size() == 1) {
        accumulator.push_back(animals);
        for (int i = 0; i < accumulator.size(); i++) {
            cout << accumulator[i] << endl;
        }
        return;     // exit the simulation
    }

    // now, determine which animal we are looking at
    // if we are looking at the first animal...

    if (index == 0) {
        // if that animal can it the animal to its right...
        if (canEat(listOfAnimals[0], listOfAnimals[1])) {
            // push the "eats" message to the accumulator...
            accumulator.push_back(eat(listOfAnimals[0], listOfAnimals[1]));
            // remove the eaten animal from the list...
            listOfAnimals.erase(listOfAnimals.begin() + 1);
            // convert the updated list back to a string, and start the process over again with the updated accumulator
            zooDisaster(vecToString(listOfAnimals), 0, accumulator);
        }
        // if that animal cannot eat the animal to its right...
        else {
            // move down the list; do not update the string or accumulator
            zooDisaster(animals, 1, accumulator);
        }
    }

    // if we are looking at the last animal...

    else if (index == listOfAnimals.size() - 1) {
        // if that animal can eat the one to its left...
        if (canEat(listOfAnimals[listOfAnimals.size() - 1], listOfAnimals[listOfAnimals.size() - 2])) {
            // push the "eats" message to the accumulator...
            accumulator.push_back(eat(listOfAnimals[listOfAnimals.size() - 1], listOfAnimals[listOfAnimals.size() - 2]));
            // remove the eaten animal from the list...
            listOfAnimals.erase(listOfAnimals.begin() + listOfAnimals.size() - 2);
            // conver the updated list back to a string, and start the process again with the updated accumulator
            zooDisaster(vecToString(listOfAnimals), 0, accumulator);
        }

        // if that animal cannot eat the one to its left...
        else {
            // the process must be complete! push the final string to the accumulator, and output the accumulated messages...
            accumulator.push_back(animals);
            
            for (int i = 0; i < accumulator.size(); i++) {
                cout << accumulator[i] << endl;
            }

            return; // exit the simulation
        }
    }

    // if our animal is somewhere in the middle

    else {
        // if that animal can eat the one to its left...
        if (canEat(listOfAnimals[index], listOfAnimals[index - 1])) {
            // push the eats message to the accumulator...
            accumulator.push_back(eat(listOfAnimals[index], listOfAnimals[index - 1]));
            // remove the eaten animal from the list
            listOfAnimals.erase(listOfAnimals.begin() + index - 1);
            // convert the updated list back to a string, and start the process again with the updated accumulator
            zooDisaster(vecToString(listOfAnimals), 0, accumulator);
        }

        // if it cannot eat the one to its left, check if it can eat the one to its right...
        else if (canEat(listOfAnimals[index], listOfAnimals[index + 1])) {
            // push the eats message to the accumulator...
            accumulator.push_back(eat(listOfAnimals[index], listOfAnimals[index + 1]));
            // remove the eaten animal from the list
            listOfAnimals.erase(listOfAnimals.begin() + index + 1);
            // convert the updated list back to a string, and start the process again with the updated accumulator
            zooDisaster(vecToString(listOfAnimals), 0, accumulator);
        }

        // if it cannot eat either...
        else {
            // do nothing to the string or accumulator; move on to the next animal...
            zooDisaster(animals, index + 1, accumulator);
        }
    }
    
}


int main()
{
    // start the disaster with a provided string of animals...
    // initialize index at 0 so that we work strictly left-to-right...
    // and initialize the accumulator as empty; no animals have eaten each other yet
    zooDisaster("fox,bug,chicken,grass,sheep", 0, {});
    
}
