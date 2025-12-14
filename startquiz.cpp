#define _CRT_SECURE_NO_WARNINGS
#include "question.h"
#include "timer.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <cstring> 
using namespace std;
// SAVE TOP 5 scores
void saveTopRecords(string names[], int scores[], int times[], string dateTime[], int count) {
	ofstream file("results.txt");
	for (int i = 0; i < count; i++) {
		file << names[i] << " " << scores[i] << " " << times[i] << " " << dateTime[i] << endl;
	}
}
// LOAD TOP 5 records from saved file 
void loadTopRecords(string names[], int scores[], int times[], string dateTime[], int& count) {
	ifstream file("results.txt");
	count = 0;
	string name, dt;
	int score, t;
	while (file >> name >> score >> t) {
		getline(file, dt);
		if (count < 5) {
			names[count] = name;
			scores[count] = score;
			times[count] = t;
			dateTime[count] = dt;
			count++;
		}
	}
}
void saveRecord(string player, int score, int timeTaken, int diff)
{
	ofstream file("results.txt", ios::app);
	auto now = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(now);
	char buffer[26];
	ctime_s(buffer, sizeof(buffer), &t);
	buffer[strcspn(buffer, "\n")] = '\0';
	string difficulty;
	if (diff == 1) difficulty = "Easy";
	else if (diff == 2) difficulty = "Medium";
	else if (diff == 3) difficulty = "Hard";
	else difficulty = "Unknown";
	file << player << "," << score << "," << timeTaken
		<< "," << difficulty << "," << buffer << endl;
}
void shuffleQuestions(string questions[], string options[][4], int answers[], int total) {
	srand(static_cast<unsigned int>(time(nullptr)));
	for (int i = 0; i < total; i++) {
		int r = rand() % total;
		swap(questions[i], questions[r]);
		swap(answers[i], answers[r]);
		for (int j = 0; j < 4; j++)
			swap(options[i][j], options[r][j]);
	}
}
void saveHighScore(string name, int score, int timeTaken, int diff)
{
	ofstream file("high_scores.txt", ios::app);
	auto now = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(now);
	char buffer[26];
	ctime_s(buffer, sizeof(buffer), &t);
	buffer[strcspn(buffer, "\n")] = '\0';
	string difficulty;
	if (diff == 1) difficulty = "Easy";
	else if (diff == 2) difficulty = "Medium";
	else if (diff == 3) difficulty = "Hard";
	else difficulty = "Unknown";
	file << name << "," << score << "," << timeTaken << "," << difficulty << "," << buffer << endl;
	file.close();
}
// MAIN QUIZ FUNCTION
void startquiz(string questions[], string options[][4], int answers[],
	int totalQuestions, int correctPoints, int wrongPoints, int diff)
{
	string player;
	cout << "Enter player name: ";
	cin >> player;
	auto quizStart = chrono::steady_clock::now();
	char opt;
	int p = 0, counter = 0, wrong = 0;
	int consec = 0;   // consecutive correct answers
	bool used5050 = false, usedSkip = false, usedSwap = false, usedTimeExt = false;
	for (int q = 0; q < totalQuestions; q++) {
		string currentOptions[4];
		for (int i = 0; i < 4; ++i)
			currentOptions[i] = options[q][i];
		cout << "Question " << q + 1 << ": " << questions[q] << "\n";
		for (int i = 0; i < 4; i++)
			cout << char('A' + i) << ") " << currentOptions[i] << "\n";
		cout << "Available Lifelines: ";
		if (!used5050) cout << "50/50 ";
		if (!usedSkip) cout << "Skip ";
		if (!usedSwap) cout << "Swap ";
		if (!usedTimeExt) cout << "+10s ";
		cout << "\nPress L to use lifeline or answer (A-D)\n";
		bool answered = false;
		while (!answered) {
			cout << "Enter option (A-D) or L: ";
			opt = getAnswerWithTimer(10);
			opt = toupper(opt);
			if (opt == 'L') {
				cout << "\nChoose Lifeline:\n";
				if (!used5050) cout << "1. 50/50\n";
				if (!usedSkip) cout << "2. Skip Question\n";
				if (!usedSwap) cout << "3. Swap Question\n";
				if (!usedTimeExt) cout << "4. Add 10 Seconds\n";
				char lifelineChoice = _getch();
				cout << lifelineChoice << endl;
				if (lifelineChoice == '1' && !used5050) {
					used5050 = true;
					int removed = 0;
					while (removed < 2) {
						int r = rand() % 4;
						if (r != answers[q] && currentOptions[r] != "------") {
							currentOptions[r] = "------";
							removed++;
						}
					}
					cout << "\nUpdated Options:\n";
					for (int i = 0; i < 4; i++)
						cout << char('A' + i) << ") " << currentOptions[i] << "\n";
					continue;
				}
			else if (lifelineChoice == '2' && !usedSkip) {
					usedSkip = true;
					consec = 0;         
					answered = true;    
					goto next_question;
				}
				else if (lifelineChoice == '3' && !usedSwap) {
					usedSwap = true;
					int rnd;
					do {
						rnd = rand() % totalQuestions;
					} while (rnd == q);   

					swap(questions[q], questions[rnd]);
					swap(answers[q], answers[rnd]);
					for (int i = 0; i < 4; i++)
						swap(options[q][i], options[rnd][i]);
					answered = true;    
					q--;                 
					goto next_question;
				}
				else if (lifelineChoice == '4' && !usedTimeExt) {
					usedTimeExt = true;
					opt = getAnswerWithTimer(20);
					opt = toupper(opt);
				}
				else {
					continue;
				}
			}
			if (opt >= 'A' && opt <= 'D') {
				int userIndex = opt - 'A';
				if (currentOptions[userIndex] == "------") continue;
				if (userIndex == answers[q]) {
					consec++;
					counter++;
					cout << "Correct! +" << correctPoints << "\n";
					if (consec == 3) {
						cout << " Bonus! 3 consecutive correct (+5)\n";
						p += 5;

					}
					else if (consec == 5) {
						cout << " Super Bonus! 5 consecutive correct (+15)\n";
						p += 15;
						consec = 0;

					}
					else if (consec < 3 || consec == 4) {
						p += correctPoints;

					}
					else
						p += correctPoints;

				}
				else {
					cout << "Wrong! Correct is: " << char('A' + answers[q]) << "\n";
					p += wrongPoints;
					wrong++;
					consec = 0;

				}
				answered = true;
			}
		}
	next_question:
		cout << "\n";
	}
	cout << "Total score = " << p << endl;
	auto quizEnd = chrono::steady_clock::now();
	int timeTaken = (int)chrono::duration_cast<chrono::seconds>(quizEnd - quizStart).count();
	saveRecord(player, p, timeTaken, diff);
	saveHighScore(player, p, timeTaken, diff);
	cout << "Correct answers: " << counter << endl;
	cout << "Wrong answers: " << wrong << endl;
	system("pause");
}
