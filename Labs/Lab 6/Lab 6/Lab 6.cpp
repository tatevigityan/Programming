#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
#include <stdio.h>
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																		
using namespace std;

void InsertData(ofstream& file, int page, int pageWidth) {
	file.put('\n');

	if (page % 2 == 1)
		file.width(pageWidth - 2);

	file << page++ << '\n' << char(12) << '\n';
}

void FormatFile(const string filePath, const string tempFilePath, string text, int pageWidth, int rowsNumber) {
	ifstream file(filePath, ios_base::in);
	ofstream tempFile(tempFilePath, ios_base::in);

	if (!file.is_open()) {
		printf("Не удалось открыть файл");
		exit(0);
	}

	cout << "Введите количество строк на странице: ";
	cin >> rowsNumber;

	int page = 1, symbols = 0, addedRows = 0;
	string readedLine;

	while (getline(file, readedLine)) {
		tempFile << readedLine;

		if (++addedRows == rowsNumber) {
			InsertData(tempFile, page++, pageWidth);
			addedRows = 0;
		}
		else
			tempFile.put('\n');

	}

	InsertData(tempFile, page, pageWidth);

	file.close();
	tempFile.close();
}

void AnalyseFile(const string filePath, string& text, int& pageWidth, int& rowsNumber) {
	ifstream file(filePath, ios_base::out);
	string readedLine;

	while (getline(file, readedLine)) {
		if ((int)readedLine.length() > pageWidth)
			pageWidth = (int)readedLine.length();
	}

	file.close();
}

int main() {   
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int pageWidth = 0, rowsNumber = 0;
	const string filePath = "C:\\Lab 6\\Lab.txt", tempFilePath = "C:\\Lab 6\\Temp.txt";
	string text;

	AnalyseFile(filePath, text, pageWidth, rowsNumber);
	FormatFile(filePath, tempFilePath, text, pageWidth, rowsNumber);
} 
