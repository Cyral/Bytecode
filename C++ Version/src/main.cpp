#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include "opcode.h"
#include "interpreter.h"

#include <Windows.h>

using namespace std;

vector<string> loadfile();

int main (int argc, char *argv[])
{
		cout << "Bytecode VM" << endl;

		// Read the file.
		auto lines = loadfile();

		LARGE_INTEGER freq, start, end;
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&start);

		// Run the interpreter.
		auto interpreter = bytecode::interpreter(lines);
		interpreter.run();
		QueryPerformanceCounter(&end);
		double duration = static_cast<double>(end.QuadPart - start.QuadPart) / freq.QuadPart;
		cout << endl << "Executed in " << round(duration * 1000) << "ms." << endl;
		return 0;
}

vector<string> loadfile()
{
		vector<string> lines;
		ifstream input("./il.txt");

		string line;
		while (getline(input, line))
		{
				if (line[0] != '/' && line.find_first_not_of(' ') != string::npos)
						lines.push_back(line);
		}
		return lines;
}
