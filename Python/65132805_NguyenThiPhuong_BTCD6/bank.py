
def main():
    s = input().strip()
    print(value(s))


def value(greeting: str) -> int:
    """Trả về:
    - 0 nếu greeting bắt đầu bằng "hello" (không phân biệt hoa thường),
    - 20 nếu greeting bắt đầu bằng chữ 'h' (nhưng không phải "hello"),
    - 100 trong các trường hợp còn lại.

    Giả sử greeting không có khoảng trắng ở đầu.
    """
    if not isinstance(greeting, str):
        greeting = str(greeting)
    g = greeting.lower()
    if g.startswith("hello"):
        return 0
    if g.startswith("h"):
        return 20
    return 100


if __name__ == "__main__":
    main()
# test_bank.py
from bank import value


def test_starts_with_hello_lowercase():
    assert value("hello") == 0


def test_starts_with_hello_mixed_case():
    assert value("HeLLo there") == 0


def test_starts_with_h_not_hello_lowercase():
    assert value("hi") == 20


def test_starts_with_h_not_hello_uppercase():
    assert value("How are you") == 20


def test_other_greeting():
    assert value("good morning") == 100


def test_non_string_input():
    # Nếu vô ý truyền vào không phải str, hàm vẫn nên xử lý bằng cách chuyển thành str
    assert value(12345) == 100
