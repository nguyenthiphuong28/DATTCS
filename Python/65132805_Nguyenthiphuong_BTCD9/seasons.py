from datetime import date
import sys
import inflect

def main():
    # Nhận ngày sinh từ người dùng
    birth_date_str = input("Date of Birth: ")
    
    # Kiểm tra định dạng và chuyển đổi
    birth_date = parse_date(birth_date_str)
    if birth_date is None:
        sys.exit("Invalid date format")
    
    # Tính số phút
    minutes = calculate_minutes(birth_date)
    
    # Chuyển đổi sang từ tiếng Anh
    words = number_to_words(minutes)
    
    # In kết quả
    print(words)

def parse_date(date_str):
    """Phân tích chuỗi ngày và trả về đối tượng date"""
    try:
        year, month, day = map(int, date_str.split('-'))
        return date(year, month, day)
    except (ValueError, AttributeError):
        return None

def calculate_minutes(birth_date):
    """Tính số phút từ lúc sinh đến hiện tại (giả sử cả hai đều là nửa đêm)"""
    today = date.today()
    
    # Tính số ngày
    days_difference = (today - birth_date).days
    
    # Chuyển đổi sang phút
    minutes = days_difference * 24 * 60
    
    return minutes

def number_to_words(number):
    """Chuyển số thành từ tiếng Anh"""
    p = inflect.engine()
    words = p.number_to_words(number, andword="")
    
    # Viết hoa chữ cái đầu và thêm "minutes"
    return words.capitalize() + " minutes"

if __name__ == "__main__":
    main()