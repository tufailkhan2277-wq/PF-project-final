#include "timer.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <conio.h>
using namespace std;

char getAnswerWithTimer(int totalSeconds) {
	char opt = 'X';
	auto start = chrono::steady_clock::now();
	int lastShown = -1;

	cout << "Enter option (A-D or L for lifeline). You have " << totalSeconds << " seconds.\n";

	while (true) {
		if (_kbhit()) {
			opt = toupper(_getch());
			cout << "\n" << opt << endl;
			if ((opt >= 'A' && opt <= 'D') || opt == 'L')
				return opt;
			else
				cout << "Invalid! Enter A-D or L for lifeline!\n";
		}

		auto now = chrono::steady_clock::now();
		int elapsed = static_cast<int>(chrono::duration_cast<chrono::seconds>(now - start).count()); // cast to int
		int remaining = totalSeconds - elapsed;

		if (remaining != lastShown && remaining >= 0) {
			cout << "\rTime left: " << remaining << " seconds   " << flush;
			lastShown = remaining;
		}

		if (remaining <= 0) {
			cout << "\nTime up!\n";
			return 'X';
		}

		this_thread::sleep_for(chrono::milliseconds(100));
	}
}
