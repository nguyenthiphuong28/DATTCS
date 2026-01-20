from fuel import convert, gauge
import pytest


def test_convert_valid():
    assert convert("1/2") == 50
    assert convert("3/4") == 75
    assert convert("1/100") == 1
    assert convert("99/100") == 99


def test_convert_invalid():
    with pytest.raises(ValueError):
        convert("2/1")  # X > Y không hợp lệ
    with pytest.raises(ValueError):
        convert("a/b")  # không phải số
    with pytest.raises(ZeroDivisionError):
        convert("1/0")  # chia cho 0


def test_gauge_E_and_F():
    assert gauge(0) == "E"
    assert gauge(1) == "E"
    assert gauge(99) == "F"
    assert gauge(100) == "F"


def test_gauge_percent():
    assert gauge(50) == "50%"
    assert gauge(25) == "25%"
    assert gauge(75) == "75%"
