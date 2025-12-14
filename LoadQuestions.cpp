#include "question.h"
#include <iostream>
#include <fstream>

using namespace std;

bool loadQuestions(
	string filename,
	string questions[MAXQ],
	string options[MAXQ][4],
	int answers[MAXQ],
	int& totalQuestions
) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Error opening file: " << filename << endl;
		return false;
	}

	totalQuestions = 0;

	while (totalQuestions < MAXQ) {
		string q;
		if (!getline(file, q)) break;
		if (q.empty()) continue;

		questions[totalQuestions] = q;

		for (int i = 0; i < 4; i++) {
			if (!getline(file, options[totalQuestions][i])) {
				file.close();
				return false;
			}
		}

		int ans;
		if (!(file >> ans)) {
			file.close();
			return false;
		}
		answers[totalQuestions] = ans;
		file.ignore();   // ignore newline

		totalQuestions++;
	}

	file.close();
	return true;
}
