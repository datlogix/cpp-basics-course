// Module 7 Project, Part B: Rock-Paper-Scissors, refactored into functions
// See project/README.md for requirements.
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

int getComputerChoice() {
    // TODO: return rand() % 3
    return 0;
}

std::string choiceToString(int choice) {
    // TODO: 0 -> "rock", 1 -> "paper", 2 -> "scissors"
    return "";
}

int determineWinner(int playerChoice, int computerChoice) {
    // TODO: 1 = player wins, -1 = computer wins, 0 = tie
    return 0;
}

void updateScore(int result, int &playerScore, int &computerScore) {
    // TODO: increment the right score based on result
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int playerScore = 0;
    int computerScore = 0;

    // TODO: loop letting the player play multiple rounds, using every
    // function above, printing the score after each round.

    return 0;
}
