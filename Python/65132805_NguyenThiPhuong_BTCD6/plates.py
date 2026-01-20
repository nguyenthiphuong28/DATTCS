def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


def is_valid(s):
    # Kiểm tra độ dài
    if len(s) < 2 or len(s) > 6:
        return False

    # Phải bắt đầu bằng ít nhất hai chữ cái
    if not s[0:2].isalpha():
        return False

    # Không được có dấu chấm, dấu cách hoặc ký tự đặc biệt
    if not s.isalnum():
        return False

    # Không được có số ở giữa (chỉ cuối cùng mới có)
    for i, ch in enumerate(s):
        if ch.isdigit():
            # Số đầu tiên không được là '0'
            if ch == '0':
                return False
            # Phần sau số phải toàn số
            if not s[i:].isdigit():
                return False
            break  # Dừng sau khi bắt đầu phần số

    return True


if __name__ == "__main__":
    main()
