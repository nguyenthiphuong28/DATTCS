from twttr import shorten


def test_lowercase():
    assert shorten("twitter") == "twttr"


def test_uppercase():
    assert shorten("HELLO") == "HLL"


def test_mixedcase():
    assert shorten("TwItTeR") == "TwtTR"


def test_with_numbers():
    assert shorten("CS50") == "CS50"


def test_with_symbols():
    assert shorten("H@ppy!") == "H@ppy!"


def test_only_vowels():
    assert shorten("aeiouAEIOU") == ""


def test_empty_string():
    assert shorten("") == ""
