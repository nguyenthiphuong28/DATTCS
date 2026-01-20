def main():
    nhap = input("Nhập biểu thức: ")
    x,y, z = nhap.split()
    x = int(x)
    z = int(z)
    if y == "+":
        result = x + z
    elif y == "-":
        result = x - z
    elif y == "*":
        result = x * z
    elif y == "/":
        result = x / z
    else:
        print ("Biểu thức không hợp lệ")
        return
    print(f"{result:1f}")
if __name__ == "__main__":
    main()
