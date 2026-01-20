import inflect

# Tạo đối tượng inflect engine
p = inflect.engine()

# Tạo danh sách lưu tên
names = []

# Nhập từng tên cho đến khi nhấn Ctrl+D (Mac/Linux) hoặc Ctrl+Z (Windows)
while True:
    try:
        name = input("Name: ")
        names.append(name)
    except EOFError:
        print()  # Xuống dòng sau khi người dùng kết thúc nhập
        break

# Dùng inflect để nối danh sách tên thành chuỗi có and, dấu phẩy đúng ngữ pháp
output = p.join(names)

# In kết quả
print(f"Adieu, adieu, to {output}")
