import sys

def main():
    # Kiểm tra đối số dòng lệnh
    if len(sys.argv) != 2:
        sys.exit("Missing command-line argument")

    try:
        n = float(sys.argv[1])
    except ValueError:
        sys.exit("Command-line argument is not a number")

    # Giá Bitcoin giả định (có thể thay đổi nếu muốn)
    rate = 38761.0833

    total = n * rate
    print(f"${total:,.4f}")

if __name__ == "__main__":
    main()