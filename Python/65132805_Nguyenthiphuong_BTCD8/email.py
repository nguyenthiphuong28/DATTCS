import re 

def is_valid_ntu_email(email):# Kiểm tra định dạng email NTU
    pattern = r'^[a-zA-Z0-9._%+-]+@ntu\.edu\.vn$'
    return re.match(pattern, email) is not None

# Nhap email từ người dùng
email = input("Nhập địa chỉ email: ").strip()

# gọi hàm kiểm tra và in kết quả
if is_valid_ntu_email(email):
    print(" Email hợp lệ theo định dạng NTU.")
else:
    print(" Email KHÔNG hợp lệ theo định dạng NTU.")
