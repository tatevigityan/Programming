N = 100
x = y = z = 0
pSum = 0
materialPoint = [[0] * 4 for i in range(N)]

n = int(input("Введите количество материальных точек n: "))

for i in range(0, n):
    materialPoint[i][0] = int(input(f"x{i + 1} = "))
    materialPoint[i][1] = int(input(f"y{i + 1} = "))
    materialPoint[i][2] = int(input(f"z{i + 1} = "))
    materialPoint[i][3] = int(input(f"p{i + 1} = "))
    print("\n")

for i in range(0, n):
    pSum += materialPoint[i][3]

for i in range(0, n):
    x += (materialPoint[i][0] * materialPoint[i][3]) / (pSum)
    y += (materialPoint[i][1] * materialPoint[i][3]) / (pSum)
    z += (materialPoint[i][2] * materialPoint[i][3]) / (pSum)


print("\nКоординаты центра тяжести")
print(f"x = {x}")
print(f"y = {y}")
print(f"z = {z}")
