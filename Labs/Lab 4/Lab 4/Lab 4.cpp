#include <iostream>
#define N 999

float K[N][2];
int n;

void InputCoordinates() {
    printf("Введите количество материальных точек n: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("x%d = ", i + 1);
        scanf("%f", &K[i][0]);

        printf("y%d = ", i + 1);
        scanf("%f", &K[i][1]);

        printf("\n");
    }
}

float DistanceBetweenTwoPoints(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void PrintResults(int firstPoint, int secondPonit, float length) {
    printf("\nРасстояние между точками %d и %d максимальное и равно %.2f\n\n", firstPoint, secondPonit, length);
}

void Calculate() {
    float length = 0;
    int firstPoint, secondPoint;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > j) {
                if (DistanceBetweenTwoPoints(K[i][0], K[i][1], K[j][0], K[j][1]) > length) {
                    firstPoint = i + 1;
                    secondPoint = j + 1;
                    length = DistanceBetweenTwoPoints(K[i][0], K[i][1], K[j][0], K[j][1]);
                }
            }
        }       
    }

    PrintResults(firstPoint, secondPoint, length);
}

int main() {
    setlocale(LC_ALL, "ru");

    InputCoordinates();
    Calculate();

    system ("pause");
    return 0;
}
    