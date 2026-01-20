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
    # Nếu truyền vào không phải chuỗi, chương trình vẫn nên hoạt động bình thường
    assert value(12345) == 100


def test_edge_case_hello_inside_word():
    # "ahello" không bắt đầu bằng hello, nên phải trả 100
    assert value("ahello") == 100
