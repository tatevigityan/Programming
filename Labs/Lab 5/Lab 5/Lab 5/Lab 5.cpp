#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

void Code(string& text, int k, int* pattern) {
	while (text.length() % k != 0)
		text.push_back(' ');

	string result;

	for (int i = 0; i < (int)text.length(); i += k)
		for (int j = 0; j < k; j++)
			result.push_back(text[i + pattern[j]]);

	text = result;
}

void Decode(string& text, int k, int* pattern) {
	string result(text.length(), ' ');

	for (int i = 0; i < (int)text.length(); i += k)
		for (int j = 0; j < k; j++)
			result[i + pattern[j]] = text[i + j];

	text = result;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int* pattern, k;
	string text;

	cout << "Введите количество символов в маске: "; 
	cin >> k;
	cin.clear();
	cin.ignore();

	pattern = new int[k];
	cout << "Введите маску шифрования: ";
	for (int i = 0; i < k; i++) {
		scanf_s("%d", &pattern[i]);
		pattern[i]--;
	}

	cout << "Введите текст для шифрования: ";
	cin.clear();
	cin.ignore();
	getline(cin, text);

	Code(text, k, pattern);
	cout << "\n\tЗашифрованный текст:\n" << text << endl;

	Decode(text, k, pattern);
	cout << "\n\tРасшифрованный текст:\n" << text << endl;

	delete[] pattern;

	return 0;
}
