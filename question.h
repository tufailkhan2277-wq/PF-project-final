#ifndef QUESTION_H
#define QUESTION_H

#include <string>
using namespace std;

const int MAXQ = 100;

bool loadQuestions(
	string filename,
	string questions[MAXQ],
	string options[MAXQ][4],
	int answers[MAXQ],
	int& totalQuestions
);

#endif
