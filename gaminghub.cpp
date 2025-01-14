#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <limits>
#include <string>
using namespace std;

// Function Prototypes
void showMainMenu();
void showGameMenu();
void showLeaderboard();
void loadingUser();
void savingUser();
void userAccount();
void ChessGame();
void WordleGame();
void FlashcardGame();
void updateLeaderboard(const string& player, int score);
void selectAccount();
bool singlePlayer(const string& user);
bool twoPlayer();
void Wordle();
bool flashCard();

// Global Variables
fstream UserData;
fstream UserScore;

const int MAX_USERS = 10;
string players[MAX_USERS];
string User;
int scores[MAX_USERS] = { 0 };
bool Win = false;
int wordleWin = 0;
bool isCorrect = false;

int main() {
    loadingUser();
    cout << "=== Welcome to GameHub! Start gaming now. ===" << endl;
    try {
        showMainMenu();
    } catch (const runtime_error& e) {
        cout << "Exception Caught: " << e.what() << endl;
    } catch (...) {
        cout << "Unknown exception detected!" << endl;
    }
    cout << "Saving..." << endl;
    atexit(savingUser);
    return 0;
}

void showMainMenu() {
    int choice;
    do {
        cout << "=== Game Hub Main Menu ===" << endl;
        cout << "User: [ " << User << " ]" << endl;
        cout << "1. Account" << endl;
        cout << "2. Games" << endl;
        cout << "3. Leaderboard" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Type mismatch.");
        }
        system("cls");
        switch (choice) {
        case 1: userAccount(); break;
        case 2: showGameMenu(); break;
        case 3: showLeaderboard(); break;
        case 4: savingUser(); cout << "Exiting Game Hub..." << endl; exit(0); break;
        default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

void userAccount() {
    int choice;
    do {
        cout << "=== Account ===" << endl;
        cout << "1. Select Account" << endl;
        cout << "2. New Account" << endl;
        cout << "3. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Type mismatch.");
        }
        system("cls");
        switch (choice) {
        case 1: selectAccount(); break;
        case 2: 
            cout << "Enter Username: "; 
            cin >> User; 
            updateLeaderboard(User, 0); 
            savingUser(); 
            return;
        case 3: return;
        default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 3);
}

void showGameMenu() {
    int choice;
    do {
        cout << "=== Game Menu ===" << endl;
        cout << "1. Flashcard" << endl;
        cout << "2. Chess" << endl;
        cout << "3. Wordle" << endl;
        cout << "4. Return to Main Menu" << endl;
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Type mismatch.");
        }
        system("cls");
        switch (choice) {
        case 1: FlashcardGame(); break;
        case 2: ChessGame(); break;
        case 3: WordleGame(); break;
        case 4: return;
        default: cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
}

void showLeaderboard() {
    cout << "=== Leaderboard ===" << endl;
    for (int i = 0; i < MAX_USERS; ++i) {
        for (int j = 0; j < MAX_USERS - 1 - i; ++j) {
            if (scores[j] < scores[j + 1]) {
                swap(scores[j], scores[j + 1]);
                swap(players[j], players[j + 1]);
            }
        }
    }
    for (int i = 0; i < MAX_USERS; ++i) {
        if (!players[i].empty()) {
            cout << players[i] << ": " << scores[i] << endl;
        }
    }
    cout << endl;
}

void updateLeaderboard(const string& player, int score) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (players[i] == player) {
            scores[i] += score;
            return;
        }
        if (players[i].empty()) {
            players[i] = player;
            scores[i] = score;
            return;
        }
    }
}

void savingUser() {
    UserData.open("UserData.txt", ios::out);
    UserScore.open("UserScore.txt", ios::out);
    if (UserData.is_open() && UserScore.is_open()) {
        for (int i = 0; i < MAX_USERS; ++i) {
            UserData << players[i] << endl;
            UserScore << scores[i] << endl;
        }
        UserData.close();
        UserScore.close();
        cout << "Saved." << endl;
    } else {
        cout << "Error: Unable to open the save file." << endl;
    }
}

void loadingUser() {
    UserData.open("UserData.txt", ios::in);
    UserScore.open("UserScore.txt", ios::in);
    if (UserData.is_open() && UserScore.is_open()) {
        for (int i = 0; getline(UserData, players[i]) && i < MAX_USERS; ++i);
        for (int i = 0; UserScore >> scores[i] && i < MAX_USERS; ++i);
        UserData.close();
        UserScore.close();
    } else {
        cout << "Files not found. Initializing empty user data." << endl;
    }
}

void selectAccount() {
    int choice;
    for (int i = 0; i < MAX_USERS; ++i) {
        if (!players[i].empty()) {
            cout << i << ": " << players[i] << endl;
        }
    }
    cout << "Enter your choice: ";
    if (!(cin >> choice) || choice < 0 || choice >= MAX_USERS || players[choice].empty()) {
        cout << "Invalid choice. Try again." << endl;
        return;
    }
    User = players[choice];
    system("cls");
}

void ChessGame() {
    if (User.empty()) {
        cout << "User account selection is required!" << endl;
        return;
    }
    Win = singlePlayer(User);  // Replace with actual logic
    if (Win) updateLeaderboard(User, 100);
}

void WordleGame() {
    if (User.empty()) {
        cout << "User account selection is required!" << endl;
        return;
    }
    Wordle();  // Placeholder function
    if (wordleWin) updateLeaderboard(User, wordleWin);
}

void FlashcardGame() {
    if (User.empty()) {
        cout << "User account selection is required!" << endl;
        return;
    }
    isCorrect = flashCard();  // Placeholder function
    if (isCorrect) updateLeaderboard(User, 100);
}

// Placeholder Function Definitions
bool singlePlayer(const string& user) { return true; }
bool twoPlayer() { return true; }
void Wordle() { wordleWin = 100; }
bool flashCard() { return true; }
