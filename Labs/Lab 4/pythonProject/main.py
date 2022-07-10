from math import sqrt

N = 999
K = [[0] * 2 for i in range(N)]
n = 0


def DistanceBetweenTwoPoints(x1, y1, x2, y2):
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2))


def PrintResults(firstPoint, secondPoint, length):
    print(f"Расстояние между точками {firstPoint} и {secondPoint} максимальное и равно {length}")


def InputCoordinates(n):
    n = int(input("Введите количество материальных точек n: "))
    for i in range(0, n):
        K[i][0] = int(input(f"x{i + 1} = "))
        K[i][1] = int(input(f"y{i + 1} = "))
        print("\n")
    return n


def Calculate():
    length = firstPoint = secondPoint = 0
    for i in range(0, n):
        for j in range(0, n):
            if i > j:
                if DistanceBetweenTwoPoints(K[i][0], K[i][1], K[j][0], K[j][1]) > length:
                    firstPoint = i + 1
                    secondPoint = j + 1
                    length = DistanceBetweenTwoPoints(K[i][0], K[i][1], K[j][0], K[j][1])

    PrintResults(firstPoint, secondPoint, length)


n = InputCoordinates(n)
Calculate()
