#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
using namespace std;
#pragma warning(disable : 4996)

struct Product {
	int article, quantity;
	char name[30], measurement[30];
}pr;

struct Operation {
	int productArticle, productQuantity;
	boolean type; // true - поступление, false - отпуск
	char date[30], measurement[30];
}op;

struct Root {
	Product product;
	Root* left, * right;
}*root = NULL;

FILE* file;
int count = 0;
const char* fileProductsName = "Products.dat";
const char* fileOperationsName = "Operations.dat";

int lengthGroup = 1, fileLength, productsNumber;
Product* bufferProducts = new Product[productsNumber];   // Массив для временного хранения продуктов на каждом шаге
Product products[50], buffer;  // Массив продуктов, переменная для временного храрения продукта

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
	}
	else { // Ввод операций
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
			printf("\t _________________________________________________________\n");
			printf("\t|\t\t        Продукция                         |\n");
			printf("\t|_________________________________________________________|\n");
			printf("\t| Наименование | Артикул | Количество | Единицы измерения |\n");
			printf("\t|______________|_________|____________|___________________|\n");

			while (fread(&pr, sizeof(pr), 1, file)) { // пока есть данные для чтения
				printf("\t| %-13s", pr.name);
				printf("| %-8d", pr.article);
				printf("| %-11d", pr.quantity);
				printf("| %-5s\t\t  |", pr.measurement);
				printf("\n");
				count++;
			}

			printf("\t|______________|_________|____________|___________________|\n");
			printf("\n\n");
		}
		else { // Просмотр операций
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
	FILE* fileProducts, * fileOperations;
	fileOperations = fopen(fileOperationsName, "rb");
	fileProducts = fopen(fileProductsName, "rb");

	if (!fileProducts || !fileOperations) {
		printf("Файл не найден!");
		system("pause");
	}
	else {
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

// Сортировка продукции по наименованиями (слияниями)
void sortProducts() {
	file = fopen(fileProductsName, "rb+");
	fseek(file, 0, SEEK_END);
	fileLength = ftell(file);

	productsNumber = fileLength / sizeof(pr);
	fseek(file, 0, SEEK_SET);
	fread(products, sizeof(pr), productsNumber, file);
	fclose(file);

	while (lengthGroup < productsNumber) {   // Пока количество элементов в подпоследовательности меньше количества элементов
		int i = 0, ik;
		int j, jk;
		int ibuf = 0;

		while (ibuf < productsNumber) {  // Пока количество элементов в буфере меньше количества продуктов
			ik = i + lengthGroup - 1;

			if (ik >= productsNumber)
				ik = productsNumber - 1;

			j = i + lengthGroup;
			jk = j + lengthGroup - 1;

			if (jk >= productsNumber)
				jk = productsNumber - 1;

			while ((i <= ik && j <= jk)) {
				if ((strcmp(products[i].name, products[j].name) < 0)) {    // Сравниваем 2 соседних подпоследовательности
					bufferProducts[ibuf] = products[i];  // Записываем i-й в буффер
					i++;
				}
				else {
					bufferProducts[ibuf] = products[j];  // Записываем j-й в буффер
					j++;
				}

				ibuf++;
			}

			while (i <= ik) {
				bufferProducts[ibuf] = products[i];
				i++;
				ibuf++;
			}

			while (j <= jk) {
				bufferProducts[ibuf] = products[j];
				j++;
				ibuf++;
			}

			i = jk + 1;
		}

		lengthGroup *= 2;
		memcpy(products, bufferProducts, productsNumber * sizeof(pr));
	}

	file = fopen(fileProductsName, "wb+");
	for (int i = 0; i < productsNumber; i++) {
		fwrite(&products[i], sizeof(pr), 1, file);
	}
	fclose(file);
}

void addElementToBinaryTree(Root** currentRoot, Product product) {   // добавление в дерево,текущий корень(от которого 2 ветки пойдут)
	if (!(*currentRoot)) {
		*currentRoot = new Root;
		(*currentRoot)->left = NULL; 
		(*currentRoot)->right = NULL; // 1
		(*currentRoot)->product = product; // 2 
	} else {   // currentroot(дерева) нет,то добавляем новое слева nul ,справа nul 
		if (product.article == (*currentRoot)->product.article) { // если currentRoot пустой,то ему присваиваем продукт абрикос,
			//слева ветка nul,справа nul / а если нет,то если он меньше артикула то идем влево,иначе вправо
			(*currentRoot)->product.quantity = product.quantity;
		} else {
			if (product.article < (*currentRoot)->product.article)
				addElementToBinaryTree(&(*currentRoot)->left, product);
			else
				addElementToBinaryTree(&(*currentRoot)->right, product);
		}
	}
}

int createBinaryTree(Root** root) {  // каждый берет из файла  все продкуты и кидает в дерево   ( в дереве  все продукты из файла)
	file = fopen(fileProductsName, "rb"); 
	if (!file) 
		return 1;
	else {
		while (fread(&pr, sizeof(Product), 1, file)) { 
			addElementToBinaryTree(&(*root), pr); 
		}

		fclose(file);
		return 0;
	}
}  // создание дерева

void viewBinaryTree(Root* root) {
	if (root) {
		viewBinaryTree(root->left);

		printf("\t| %-8d", root->product.article);
		printf("| %-13s", root->product.name);
		printf("| %-11d", root->product.quantity);
		printf("| %-5s\t\t  |", root->product.measurement);
		printf("\n");

		viewBinaryTree(root->right);
	}
}  // добавление элемента в дерево

void viewProducts(Root* root) {// создается таблица
	system("cls");
	printf("\t _________________________________________________________\n");
	printf("\t|\t\t        Продукция                         |\n");
	printf("\t|_________________________________________________________|\n");
	printf("\t| Артикул | Наименование | Количество | Единицы измерения |\n");
	printf("\t|_________|______________|____________|___________________|\n");

	viewBinaryTree(root); 

	printf("\t|_________|______________|____________|___________________|\n");
	printf("\n\n");
} //просмотр дерева

void addProductToBinaryTree() {  // добавить элмент дерева
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

	addElementToBinaryTree(&root, pr);
	viewProducts(root);
} // чешуя 

void updateBinaryTree() {
	FILE* fileProducts, * fileOperations; // создается два файла,файл продуктов,файл операции
	fileOperations = fopen(fileOperationsName, "rb"); // проход по продуктам и операциям
	fileProducts = fopen(fileProductsName, "rb");

	if (!fileProducts || !fileOperations) { // если привоз,то кол-во продуктов увеличиваем,иначе убавляем
		printf("Файл не найден!");
		system("pause");
	} else {
		while (fread(&pr, sizeof(pr), 1, fileProducts)) { // Проход по продукции
			while (fread(&op, sizeof(op), 1, fileOperations)) { // Проход по операциям
				if (pr.article == op.productArticle) { // Если артикулы совпадают
					if (strcmp(pr.measurement, op.measurement) == 0) { // Если единицы измерения совпадают
						if (op.type) // Если это привоз, то складываем
							pr.quantity += op.productQuantity;
						else
							if (pr.quantity > op.productQuantity)
								pr.quantity -= op.productQuantity;

						addElementToBinaryTree(&root, pr);
					}
				}
			}

			fseek(fileOperations, 0L, SEEK_SET); // Сдвигаем указатель файла операций в начало
		}

		// Закрываем все файлы
		fclose(fileProducts);
		fclose(fileOperations);

		viewProducts(root);

		system("pause");
	}
}

void binaryTree() {
	char menuNumber;

	system("cls");
	printf("\t\tВыберите действие:\n\n");
	printf("1 | Просмотр бинарного дерева\n");
	printf("2 | Добавить элемент в дерево\n");
	printf("3 | Обновить дерево на основе операций\n\n");
	getchar();
	scanf("%c", &menuNumber);

	if (menuNumber == '1') {
		system("cls");
		createBinaryTree(&root);
		viewProducts(root);
	}

	if (menuNumber == '2') {
		system("cls"); 
		addProductToBinaryTree();
	}

	if (menuNumber == '3') {
		system("cls");
		updateBinaryTree();
	}

	system("pause");
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	char menuNumber;
	do {
		system("cls");
		printf("\t\tВыберите действие:\n\n");
		printf("1 | Ввод данных о продукции\n");
		printf("2 | Просмотр данных о продукции\n");
		printf("3 | Дополнение информации об операциях\n");
		printf("4 | Просмотр операций\n");
		printf("5 | Обновить инвентарные данные на основе данных об операциях\n");
		printf("6 | Отсортировать продукцию по наименованию\n");
		printf("7 | Работа с бинарным деревом\n\n");
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
			case '6': // Сортировка продукции
				sortProducts();
				break;
			case '7': // Работа с бинарным деревом
				binaryTree();
				break;
		} while (getchar() != '\n');
	} while (menuNumber != '0');

	system("pause");
	return 0;
}
