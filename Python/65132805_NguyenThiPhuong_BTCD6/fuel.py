def main():
    """
    Chương trình chính: yêu cầu người dùng nhập phân số X/Y,
    sau đó hiển thị mức nhiên liệu dưới dạng phần trăm hoặc ký hiệu E/F.
    """
    while True:
        fraction = input("Fraction: ")
        try:
            percent = convert(fraction)
            print(gauge(percent))
            break
        except (ValueError, ZeroDivisionError):
            # Nếu nhập sai (chia 0, ký tự không hợp lệ, X > Y) thì nhập lại
            continue


def convert(fraction):
    """
    Nhận vào chuỗi dạng 'X/Y'.
    - Trả về giá trị phần trăm (0–100) làm tròn.
    - Nếu X > Y, Y = 0, hoặc dữ liệu không hợp lệ → ném lỗi (raise).
    """
    X, Y = fraction.split("/")
    X = int(X)
    Y = int(Y)
    if Y == 0:
        raise ZeroDivisionError
    if X > Y:
        raise ValueError
    return round((X / Y) * 100)


def gauge(percentage):
    """
    Nhận vào phần trăm (0–100):
    - Nếu <= 1%  → trả về 'E' (Empty)
    - Nếu >= 99% → trả về 'F' (Full)
    - Ngược lại   → trả về '{n}%'
    """
    if percentage <= 1:
        return "E"
    elif percentage >= 99:
        return "F"
    else:
        return f"{percentage}%"


if __name__ == "__main__":
    main()
