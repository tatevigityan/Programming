#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
#pragma warning(disable : 4996)

FILE *file;
int count = 0;
const char* fileProductsName = "Products.dat";
const char* fileOperationsName = "Operations.dat";

struct Product {
	int article, quantity;
	char name[30], measurement[30];
}pr;

struct Operation {
	int productArticle, productQuantity;
	boolean type; // true - поступление, false - отпуск
	char date[30], measurement[30];
}op;

// Ввод данных
int inputData(bool inputType, const char* fileName) {
	int count;
	char sym;
	file = fopen(fileName, "rb+"); 

	if (file) {
		system("cls");
		printf("Файл существует. Выберите действие:\n");
		printf("1 | создавать новый файл\n");
		printf("2 | добавить дальше в существующий\n");
		printf("0 | выйти из операции ввода\n\n");

		while (getchar() != '\n');
		sym = getchar();

		switch (sym) {
			case '1':
				file = fopen(fileName, "wb+");
				break;
			case '2':
				file = fopen(fileName, "ab");
				break;
			case '0':
				return 0;
		}
	}
	else {
		file = fopen(fileName, "wb");
		count = 0;
	}

	system("cls");

	if (inputType) { // Ввод продукции
		do {
			printf("Артикул: ");
			scanf("%d", &pr.article);

			printf("Наименование: ");
			getchar();
			gets_s(pr.name);

			printf("Количество: ");
			scanf("%d", &pr.quantity);

			printf("Eдиницы измерения: ");
			getchar();
			gets_s(pr.measurement);

			fwrite(&pr, sizeof(pr), 1, file); // Запись в файл

			sym = getchar();
		} while (sym != 'н' && sym != 'Н');
	} else { // Ввод операций
		do {
			printf("Артикул продукта: ");
			scanf("%d", &op.productArticle);

			printf("Тип операции: ");
			scanf("%d", &op.type);

			printf("Eдиницы измерения: ");
			getchar();
			gets_s(op.measurement);

			printf("Количество продукта: ");
			scanf("%d", &op.productQuantity);

			printf("Дата операции: ");
			getchar();
			gets_s(op.date);

			fwrite(&op, sizeof(op), 1, file);

			sym = getchar();
		} while (sym != 'н' && sym != 'Н');
	}

	printf("\n\n");
	fclose(file);
	return 0;
}

// Просмотр данных
void viewData(bool inputType, const char* fileName) {
	file = fopen(fileName, "rb");

	if (!file) {
		printf("Файл не найден!");
		system("pause");
	}
	else {
		int count = 0;
		system("cls");

		if (inputType) { // Просмотр продукции
			printf("\t\tПродукция\n\n");

			while (fread(&pr, sizeof(pr), 1, file)) { // пока есть данные для чтения
				printf("Артикул: %-20d\n", pr.article);
				printf("Наименование: %-40s\n", pr.name);
				printf("Количество: %-10d\n", pr.quantity);
				printf("Eдиницы измерения: %-20s\n", pr.measurement);
				printf("\n");
				count++;
			}
		} else { // Просмотр операций
			printf("\t\tОперации\n\n");

			while (fread(&op, sizeof(op), 1, file)) {
				printf("Артикул продукта: %-20d\n", op.productArticle);
				printf("Тип операции: %-1d\n", op.type);
				printf("Количество продукта: %-10d\n", op.productQuantity);
				printf("Eдиницы измерения: %-20s\n", op.measurement);
				printf("Дата: %-20s\n", op.date);
				printf("\n");
				count++;
			}
		}

		fclose(file);

		if (!count)
			printf("Нет данных!");

		system("pause");
	}
}

// Обновление продукции
void refreshProducts() {
	FILE *fileProducts, *fileOperations;
	fileOperations = fopen(fileOperationsName, "rb");
	fileProducts = fopen(fileProductsName, "rb");

	if (!fileProducts || !fileOperations) {
		printf("Файл не найден!");
		system("pause");
	} else {
		FILE* tempFile; // Вспомогательный файл
		tempFile = fopen("Temp.dat", "wb+");

		while (fread(&pr, sizeof(pr), 1, fileProducts)) { // Проход по продукции
			while (fread(&op, sizeof(op), 1, fileOperations)) { // Проход по операциям
				if (pr.article == op.productArticle) { // Если артикулы совпадают
					if (strcmp(pr.measurement, op.measurement) == 0) { // Если единицы измерения совпадают
						if (op.type) // Если это привоз, то складываем
							pr.quantity += op.productQuantity;
						else
							if (pr.quantity > op.productQuantity)
								pr.quantity -= op.productQuantity;
					}
				}
			}

			fwrite(&pr, sizeof(pr), 1, tempFile); // Записываем обновленый продукт во вспомогательный файл
			fseek(fileOperations, 0L, SEEK_SET); // Сдвигаем указатель файла операций в начало
		}

		// Закрываем все файлы
		fclose(tempFile);
		fclose(fileProducts);
		fclose(fileOperations);


		remove("Products.dat");
		rename("Temp.dat", "Products.dat");
		rename("Operations.dat", "ArchiveOperations.dat");

		system("pause");
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char menuNumber;
	do {
		system("cls");
		printf("Выберите действие:\n\n");
		printf("1 | Ввод данных о продукции\n");
		printf("2 | Просмотр данных о продукции\n");
		printf("3 | Дополнение информации об операциях\n");
		printf("4 | Просмотр операций\n");
		printf("5 | Обновить инвентарные данные на основе данных об операциях\n\n");
		scanf("%c", &menuNumber);

		switch (menuNumber) {
			case '1': // Ввод продукции
				inputData(true, fileProductsName); 
				break;
			case '2': // Просмотр продукции
				viewData(true, fileProductsName); 
				break;
			case '3': // Ввод операций
				inputData(false, fileOperationsName); 
				break;
			case '4': // Просмотр операций 
				viewData(false, fileOperationsName); 
				break;
			case '5': // Обновление продукции
				refreshProducts();
				break;
		} while (getchar() != '\n');
	} while (menuNumber != '0');

	system("pause");
	return 0;
}
