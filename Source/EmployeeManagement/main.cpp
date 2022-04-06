
#include<iostream>
#include "IOChecker.h"
#include "InputInterpreter.h"
#include "OutputBuilder.h"
#include "Command.h"
using namespace std;

bool runAllCommand(const string inputFile, const string outputFile) {
	IOChecker* ioChecker = new IOChecker();
	if (ioChecker->isValidFileName(inputFile) == false || ioChecker->isValidFileName(outputFile) == false)
		return false;

	InputInterpreter* inputInterpreter = new InputInterpreter(inputFile);
	OutputBuilder* outputBuilder = new OutputBuilder(outputFile);
	EmployeeManagement* EM = new EmployeeManagement();
	Command* command = new Command();
	vector<string> inputStrAll = inputInterpreter->readFile();
	vector<string> outputStrAll;

	for (const auto inputStr : inputStrAll) {
		if (inputStr.length() == 0) break;
		vector<string> queryResult = command->makeResult(EM, inputStr);
		for (string line : queryResult) outputStrAll.push_back(line);
	}
	outputBuilder->writeFile(outputStrAll);

	return true;
}

int main(int argc, char* argv[]) {

	if (argc != 3) exit(1);
	runAllCommand(argv[1], argv[2]);

	return 0;
}


