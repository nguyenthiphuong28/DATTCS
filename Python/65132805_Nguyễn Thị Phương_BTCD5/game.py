import random

# Hàm nhập level hợp lệ
while True:
    try:
        level = int(input("Level: "))
        if level > 0:
            break
    except ValueError:
        pass  # Nếu nhập không phải số, bỏ qua
    # Nếu nhập <= 0 hoặc lỗi, lặp lại

# Sinh số ngẫu nhiên trong khoảng 1 đến level
number = random.randint(1, level)

# Vòng lặp đoán
while True:
    try:
        guess = int(input("Guess: "))
        if guess <= 0:
            continue  # chỉ nhận số nguyên dương
        if guess < number:
            print("Too small!")
        elif guess > number:
            print("Too large!")
        else:
            print("Just right!")
            break
    except ValueError:
        pass  # nếu nhập không phải số, bỏ qua
