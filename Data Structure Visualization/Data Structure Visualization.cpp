#include "program.h"

int main() {
    Program program;
    program.run();

    return 0;
}

//void insertStepByStep(int key, sf::RenderWindow& window) {
//    int hashValue = hashFunction(key);
//
//    while (hashTable[hashValue] != -1) {
//        drawHashTable(window);
//        sf::sleep(sf::seconds(1)); // Dừng lại 1 giây để quan sát
//        hashValue = (hashValue + 1) % TABLE_SIZE;
//    }
//
//    hashTable[hashValue] = key;
//    drawHashTable(window);
//    sf::sleep(sf::seconds(1)); // Dừng lại 1 giây để quan sát
//}
