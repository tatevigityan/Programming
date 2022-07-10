#include <iostream>

using namespace std;

int N, A[100]; // N - число для разложение на слагаемые. Слагаемые будем хранить в массиве A

// Алгоритм: будем добавлять очередное слагаемое и вызывать рекурсивно разложение оставшейся суммы

// sum - сумма для разложения
// prev - верхний предел для слагаемого
// i - индекс текущего слагаемого = количество предыдущих слагаемых
void findDecomposition(int sum, int prev, int i) {
    for (int x = min(sum, prev); x >= 1; --x) { // Перебираем x - значение текушего слагаемого
        A[i] = x; // Сохраняем слагаемое в массив (для печати)

        if (sum == x) { // Если оставш. сумма равна x, то разложение получено => печатаем его
            printf("%d = %d", N, A[0]); // Печатаем сумму
            for (int j = 1; j <= i; ++j) 
                printf(" + %d", A[j]);
            printf("\n");

        } else // Продолжаем раскладывать
            findDecomposition(sum - x, x, i + 1);
    }
}

int main() {
    setlocale(LC_ALL, "ru");

    printf("Введите натуральное число: ");
    scanf("%d", &N);

    findDecomposition(N, N - 1, 0);

    system("pause");
    return 0;
}