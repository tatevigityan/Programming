// Простые делители. Дано натуральное число n. Получить все простые делители этого числа

#include <stdio.h>;
#include <math.h>;
#include <iostream>;

int main() {
	setlocale(LC_ALL, "Russian");

	int n, last = 0;

	printf("Введите число: ");
	scanf("%d", &n);

	printf("\nПростые делители:\n");

	// Вывод делителей 2-ек
	while (n % 2 == 0) {
		if (last != 2) {
			printf("%d ", 2);
			last = 2;
		}
		n = n / 2;
	}

	if (n > 1) { // если не дошли до конца
		// n нечетное число на данном шаге. Перешагиваем через 1 элемент
		for (int i = 3; i <= sqrt(n); i += 2) {
			while (n % i == 0) {
				if (last != i) {
					printf("%d ", i);
					last = i;
				}
				n /= i;
			}
		}
	}

	// Случай, когда 1 простой делитель (сам n)
	if (n > 2)
		printf("%d ", n);

	system("pause");
	return 0;
}