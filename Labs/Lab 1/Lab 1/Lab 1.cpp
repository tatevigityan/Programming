﻿#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");

	float a11, a12, a21, a22, b1, b2, x1, x2;

	// Ввод данных
	printf("Дана система:\n");
	printf("а11*x1+a12*x2=b1\n");
	printf("а21*x1+a22*x2=b2\n\n\n");

	printf("а11=");
	scanf("%f", &a11);

	printf("а12=");
	scanf("%f", &a12);

	printf("а21=");
	scanf("%f", &a21);

	printf("а22=");
	scanf("%f", &a22);

	printf("b1=");
	scanf("%f", &b1);

	printf("b2=");
	scanf("%f", &b2);

	if (a11 * a22 != a12 * a21) { // Коэффиценты уравнений не пропорциональны
		printf("\n\n\nСистема имеет единственное решение\n");

		// Определитель матрицы
		float d = a11 * a22 - a21 * a12;

		// Находим неизвестные методом Крамера
		x1 = (b1 * a22 - b2 * a12) / d;
		x2 = (a11 * b2 - a21 * b1) / d;

		// Вывод результата, 3 значения после запятой
		printf("X1=%.3f \nX2=%.3f\n\n", x1, x2);
	}
	else { // Пропорциональны коэффиценты и свободные члены
		if (a11 * b2 == b1 * a21)
			printf("\n\n\nСистема имеет бесконечное множество решений\n\n");
		else // Коэффиценты пропорциональны, а свободные члены нет
			printf("\n\n\nСистема не имеет решений\n\n");
	}

	system("pause");
	return 0;
}
