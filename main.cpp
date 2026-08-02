#include "eniesLobby.h"
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
    string inputFile = "sample_input"; 
    if (argc > 1) {
        inputFile = argv[1];
    }
    EniesLobbyBattle battle(inputFile);
    battle.runBattle();
    cout << battle.getResult() << endl; 

    return 0;
}