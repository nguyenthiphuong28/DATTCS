def main():
    while True:
        try:
            fraction = input("Fraction: ").strip()
            X, Y = fraction.split("/")
            X = int(X)
            Y = int(Y)
            # Kiểm tra mẫu số khác 0 và tính tỉ lệ
            if Y == 0 or X > Y:
                raise ValueError
            percent = round((X / Y) * 100)
            if percent <= 1:
                print("E")
            elif percent >= 99:
                print("F")
            else:
                print(f"{percent}%")
            break
        except (ValueError, ZeroDivisionError):
            continue
if __name__ == "__main__":
    main()
            
