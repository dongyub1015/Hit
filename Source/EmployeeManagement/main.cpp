
#include<iostream>
#include "IOChecker.h"
#include "InputInterpreter.h"
#include "OutputBuilder.h"
using namespace std;

int runAllCommand(string inputFile, string outputFile) {

	IOChecker* ioChecker = new IOChecker();
	if (ioChecker->isValidFileName(inputFile) == false || ioChecker->isValidFileName(outputFile) == false)
		return false;
	InputInterpreter* inputInterpreter = new InputInterpreter(inputFile);
	OutputBuilder* outputBuilder = new OutputBuilder(outputFile);

	vector<string> inputStrAll = inputInterpreter->readFile();
	vector<string> outputStrAll;

	for (auto inputStr : inputStrAll) {
		if (inputStr.length() == 0) break;
		
		// Todo : interface to Command Module
		// vector<string> queryResult = Command.makeResult(string "SCH,-p,-d, ,birthday,04")

		vector<string> queryResult = { "SCH,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV ", "..."};
		for (string line : queryResult) outputStrAll.push_back(line);
	}
	outputBuilder->writeFile(outputStrAll);

	return 0;
}

int main(int argc, char* argv[]) {

	if (argc != 3) exit(1);
	//runAllCommand(argv[1], argv[2]);
	//runAllCommand("input_20_20.txt", "output_20_20.txt");

	return 0;
}


