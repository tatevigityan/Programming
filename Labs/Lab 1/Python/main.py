print("Дана система:")
print("а11*x1+a12*x2=b1")
print("а21*x1+a22*x2=b2\n\n")

a11 = int(input("a11="))
a12 = int(input("a12="))
a21 = int(input("a21="))
a22 = int(input("a22="))
b1 = int(input("b1="))
b2 = int(input("b2="))

if a11 * a22 != a12 * a21:
    print("\n\n\nСистема имеет единственное решение\n")
    d = a11 * a22 - a21 * a12
    x1 = (b1 * a22 - b2 * a12) / d
    x2 = (a11 * b2 - a21 * b1) / d
    print(f"X1={x1} \nX2={x2}\n\n")
elif a11 * b2 == b1 * a21:
    print("\n\nСистема имеет бесконечное множество решений\n")
else:
    print("\n\nСистема не имеет решений\n")




