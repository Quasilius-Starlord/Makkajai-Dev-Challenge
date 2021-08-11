#include <iostream>
#include <string>
#include "World.cpp"

int main(){
    //block pattern
    std::vector<std::vector<int>> blockstore={{1,1},{1,2},{2,1},{2,2}};
    World block(blockstore);
    std::cout << "Input A\nBlock Pattern\n";
    block.tict();
    block.printcoords("Output A");

    //boat pattern
    std::vector<std::vector<int>> boatstore={{0,1},{1,0},{2,1},{0,2},{1,2}};
    World boat(boatstore);
    boat.tict();
    boat.printcoords("Output B");
    
    //blinker pattern
    std::vector<std::vector<int>> blinkerstore={{1,1},{1,0},{1,2}};
    World blinker(blinkerstore);
    std::cout << "Input C\nBlinker Pattern\n";
    blinker.tict();
    blinker.printcoords("Output C");
    
    std::vector<std::vector<int>> toadstore={{1,1},{1,2},{1,3},{2,2},{2,3},{2,4}};
    World toad(toadstore);
    std::cout << "Input D\ntoad Pattern\n";
    toad.tict();
    toad.printcoords("Output D");
}