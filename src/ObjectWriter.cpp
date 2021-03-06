//
// Created by Tarek on 5/6/2016.
//

#include "ObjectWriter.h"

ObjectWriter::ObjectWriter(string fileName) {
	out.open(fileName);
}

void ObjectWriter::writeHeader(string start, string programName, string programLength) {
	while (programName.length() < 6) {
		programName = programName + ' ';
	}
	while (start.length() < 6) {
		start = '0' + start;
	}
	while (programLength.length() < 6) {
		programLength = '0' + programLength;
	}
	out << "H^" << programName << "^" << start << "^" << programLength << "\n";
	cout << "H^" << programName << "^" << start << "^" << programLength << "\n";
	startAddress = start;
	currentRecord = "";
}

void ObjectWriter::writeTextRecord(string opCode, string flags, string address) {
	int answer = autalities::hexToInteger(opCode);
	answer <<= 4;
	answer |= autalities::binToInteger(flags);
	string result = autalities::toHex(answer);
	result = result.substr(result.size()-3);
	result += address;
	writeTextRecord(result);
}

void ObjectWriter::writeTextRecord(string start, string opCode, string flags, string address) {
    startNewRecord(start);
    writeTextRecord(opCode, flags, address);
}

void ObjectWriter::writeTextRecord(string start, string filed) {
    startNewRecord(start);
    writeTextRecord(filed);
}

void ObjectWriter::writeEnd(string start) {
	startNewRecord("");
	out << "E^" << start << "\n";
	cout << "E^" << start << "\n";
	out.close();
}

void ObjectWriter::writeTextRecord(string field) {
	if (currentRecord.length() + field.size() > MAX_RECORD_LENGTH) {
        // write record
        out << "T^" << startAddress << "^" << autalities::toByte(currentRecord.length()) << "^";
        cout << "T^" << startAddress << "^" << autalities::toByte(currentRecord.length()) << "^";
        out << currentRecord << "\n";
        cout << currentRecord << "\n";
        int previousStart = autalities::hexToInteger(startAddress);
        startAddress = autalities::toWord(currentRecord.length() + previousStart);
        currentRecord = "";
	}
	currentRecord += field;
}

void ObjectWriter::startNewRecord(string start) {
	//write record
	if (currentRecord.length() > 0) {
		out << "T^" << startAddress << "^" << autalities::toByte(currentRecord.length()) << "^";
		cout << "T^" << startAddress << "^" << autalities::toByte(currentRecord.length()) << "^";
        out << currentRecord << "\n";
        cout << currentRecord << "\n";
        currentRecord = "";
	}
	startAddress = start;
}

string ObjectWriter::opCodeToHex(string opCode) {
	int number = autalities::toInteger(opCode);
	string temp = autalities::toHex(number);
	temp.pop_back();
	temp.pop_back();
	return temp;
}



