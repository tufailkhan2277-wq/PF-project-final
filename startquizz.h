#ifndef STARTQUIZ_H
#define STARTQUIZ_H
#include <string>
using namespace std;

void shuffleQuestions(string questions[], string options[][4], int answers[], int total);
void saveRecord(string player, int score, int timeTaken, int diff);
void loadTopRecords(string names[], int scores[], int times[], string dateTime[], int& count);
void saveTopRecords(string names[], int scores[], int times[], string dateTime[], int count);
void saveHighScore(string name, int score, int timeTaken);
void startquiz(string questions[],
	string options[][4],
	int answers[],
	int totalQuestions,
	int correctPoints,
	int wrongPoints,
	int diff);

#endif