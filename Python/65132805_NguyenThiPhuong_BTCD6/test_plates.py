from plates import is_valid

def test_valid_plates():
    assert is_valid("CS50")
    assert is_valid("HELLO")
    assert is_valid("AB123")
    assert is_valid("AAA222")
    assert is_valid("OUT123")

def test_invalid_too_short_or_long():
    assert not is_valid("A")
    assert not is_valid("ABCDEFG")

def test_invalid_start_with_digit():
    assert not is_valid("1ABC")
    assert not is_valid("11AA")

def test_invalid_zero_start():
    assert not is_valid("CS05")
    assert not is_valid("AA0")

def test_invalid_letter_after_number():
    assert not is_valid("AAA22A")
    assert not is_valid("AB12C")

def test_invalid_symbols_or_spaces():
    assert not is_valid("CS 50")
    assert not is_valid("HI!")
    assert not is_valid("A.B")
    assert not is_valid("AA-12")

def test_edge_cases():
    assert is_valid("AB")
    assert is_valid("AB999")
