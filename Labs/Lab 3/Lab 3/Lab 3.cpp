#include <iostream>
#define N 999

int main() {
	setlocale(LC_ALL, "ru");

	float x = 0, y = 0, z = 0, pSum = 0;
	float materialPoint[N][4];
	int n;

	printf("Введите количество материальных точек n: ");
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		printf("x%d = ", i + 1);
		scanf("%f", &materialPoint[i][0]);

		printf("y%d = ", i + 1);
		scanf("%f", &materialPoint[i][1]);

		printf("z%d = ", i + 1);
		scanf("%f", &materialPoint[i][2]);

		printf("p%d = ", i + 1);
		scanf("%f", &materialPoint[i][3]);

		printf("\n");

		x += materialPoint[i][0] * materialPoint[i][3];
		y += materialPoint[i][1] * materialPoint[i][3];
		z += materialPoint[i][2] * materialPoint[i][3];
		pSum += materialPoint[i][3];
				
	}
	
	printf("\nКоординаты центра тяжести:\n");
	printf("x = %f \n", x / pSum);
	printf("y = %f \n", y / pSum);
	printf("z = %f \n", z / pSum);

	system("pause");
	return 0;
}