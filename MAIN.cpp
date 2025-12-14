#include <iostream>
#include <fstream>
#include <string>
#include "question.h"
#include "startquizz.h"

using namespace std;

int main() {
	char playAgain = 'y';

	while (playAgain == 'y' || playAgain == 'Y') {

		cout << "========== QUIZ GAME ==========\n";
		cout << "1. Start Game\n";
		cout << "2. Show Top 5 High Scores\n";
		cout << "3. Quit\n";
		cout << "Enter choice: ";

		int menuChoice;
		cin >> menuChoice;

		if (menuChoice == 2) {
			ifstream file("high_scores.txt");
			string line;
			int count = 0;

			cout << "\n------ TOP 5 HIGH SCORES ------\n";
			while (getline(file, line) && count < 5) {
				cout << line << endl;
				count++;
			}

			cout << "\nPress y to go back to menu: ";
			cin >> playAgain;
			continue;
		}

		if (menuChoice == 3) {
			cout << "Thank you for playing!\n";
			return 0;
		}

		if (menuChoice != 1) {
			cout << "Invalid choice.\n";
			continue;
		}
		string questions[MAXQ];
		string options[MAXQ][4];
		int answers[MAXQ];
		int totalQuestions = 0;

		cout << "\nChoose Quiz Category:\n";
		cout << "1. Science\n2. Sports\n3. History\n4. General Knowledge\n5. Maths\n";
		int cat;
		cin >> cat;

		string base;
		switch (cat) {
		case 1: base = "science"; break;
		case 2: base = "sports"; break;
		case 3: base = "history"; break;
		case 4: base = "gk"; break;
		case 5: base = "math"; break;
		default:
			cout << "Invalid category.\n";
			continue;
		}

		cout << "\nChoose Difficulty:\n1. Easy\n2. Medium\n3. Hard\n";
		int diff;
		cin >> diff;

		string filename;
		int correctPoints = 1;
		int wrongPoints = -2;

		if (diff == 1) filename = base + ".txt";
		else if (diff == 2) { filename = base + "medium.txt"; wrongPoints = -3; }
		else if (diff == 3) { filename = base + "hard.txt"; wrongPoints = -5; }
		else {
			cout << "Invalid difficulty.\n";
			continue;
		}

		if (!loadQuestions(filename, questions, options, answers, totalQuestions)) {
			cout << "Failed to load questions.\n";
			continue;
		}

		startquiz(
			questions,
			options,
			answers,
			totalQuestions,
			correctPoints,
			wrongPoints,
			diff
		);

		cout << "\nGo back to main menu? (y/n): ";
		cin >> playAgain;
	}

	cout << "Thank you for playing!\n";
	return 0;
}
