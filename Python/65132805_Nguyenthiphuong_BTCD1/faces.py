def convert(text: str) -> str:
    """
    Thay thế biểu tượng cảm xúc trong chuỗi:
    - :) thành 🙂
    - :( thành 🙁
    """
    return text.replace(":)", "🙂").replace(":(", "🙁")


def main():
    s = input("Nhập văn bản: ")
    print(convert(s))


if __name__ == "__main__":
    main()
