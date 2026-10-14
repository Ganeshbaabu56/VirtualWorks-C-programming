#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int generate_random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void play_game() {
    const int MIN = 1;
    const int MAX = 100;
    int secret_num = generate_random_number(MIN, MAX);
    int user_guess;
    int attempts = 0;

    cout << "Welcome to the Number Guessing Game!\n";

    while (true) {
        cout << "\nEnter your guess between 1 and 100: ";
        cin >> user_guess;
        attempts++;

        if (user_guess == secret_num) {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts.\n";
            break;
        } else if (user_guess < secret_num) {
            cout << "Too Low. Try again.\n";
        } else {
            cout << "Too High. Try again.\n";
        }
    }
}

int main() {
    srand(time(0)); // Seed the random number generator
    play_game();
    return 0;
}
