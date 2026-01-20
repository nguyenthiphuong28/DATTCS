
def main():
    # Đọc một chuỗi từ input và in ra phiên bản đã được rút gọn
    s = input().strip()
    print(shorten(s))


def shorten(word: str) -> str:
    """Trả về chuỗi word nhưng loại bỏ tất cả nguyên âm A, E, I, O, U (cả hoa lẫn thường)."""
    if not isinstance(word, str):
        # Nếu không phải str, cố gắng chuyển về str
        word = str(word)
    vowels = set("aeiouAEIOU")
    # Giữ lại những ký tự không phải nguyên âm
    return ''.join(ch for ch in word if ch not in vowels)


if __name__ == "__main__":
    main()

# test_twttr.py
# test_twttr.py
from twttr import shorten


def test_basic_lowercase():
    assert shorten("hello") == "hll"


def test_basic_uppercase():
    assert shorten("HELLO") == "HLL"


def test_mixed_case():
    assert shorten("HaNgMaN") == "HnGmN"


def test_empty_string():
    assert shorten("") == ""


def test_no_vowels():
    assert shorten("rhythm") == "rhythm"


def test_only_vowels():
    assert shorten("aeiouAEIOU") == ""


def test_punctuation_and_numbers():
    assert shorten("Th1s, th@t: 100%") == "Th1s, th@t: 100%".replace("", "").replace("", "")
    # above line intentionally keeps punctuation and numbers; let's assert directly
    assert shorten("Th1s, th@t: 100%") == "Th1s, th@t: 100%".translate({ord(c): None for c in []})


def test_sentence_spaces():
    assert shorten("This is a test sentence.") == "Ths s  tst sntnc."

