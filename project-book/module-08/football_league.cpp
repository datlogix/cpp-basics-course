// C++ Foundations Project Book - Chapter 8, Activity 3: Football League Table
// Difficulty: CHALLENGE
//
// Use only: everything from Modules 1-7, plus classes with private member
// variables and public methods, constructors, getters and setters with
// validation, and this->.
// Not yet: inheritance (Part 2).
//
// Compile and run (from this folder):
//     g++ football_league.cpp -o football_league
//     ./football_league
#include <iostream>
#include <string>
#include <vector>

class Team {
private:
    std::string name;
    int played;
    int won;
    int drawn;
    int lost;
    int goalsFor;
    int goalsAgainst;

public:
    // TODO 1: A new team has played no matches - every number starts at 0.
    Team(std::string name) {
    }

    std::string getName() {
        return name;
    }

    // TODO 1: Update the team's numbers after ONE match.
    void recordResult(int scored, int conceded) {
    }

    // TODO 1: 3 points for a win, 1 for a draw.
    int points() {
        return 0;
    }

    int goalDifference() {
        return 0;
    }

    // TODO 3: Print one row of the table for this team.
    void printRow() {
    }
};

class League {
private:
    std::vector<Team> teams;

public:
    // TODO 2
    void addTeam(std::string name) {
    }

    // TODO 2: Update BOTH teams. Reject the match if a team name doesn't
    //         exist or a score is negative. Make sure you change the Team
    //         objects INSIDE the vector, not copies of them.
    void recordMatch(std::string home, int homeGoals, std::string away, int awayGoals) {
    }

    // TODO 3: Sort teams by points (highest first) with a selection sort
    //         or bubble sort you write yourself. When points are level,
    //         the better goal difference goes higher. Then print a header
    //         row and every team's row.
    void printTable() {
    }
};

int main() {
    League league;

    // TODO 4: Add at least four teams, record at least six matches, and
    //         print the table after each round.

    return 0;
}
