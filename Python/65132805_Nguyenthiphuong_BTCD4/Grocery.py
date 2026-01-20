grocery_list = {}
print("Nhap cac mat hang(Nhan ctrl+D de ket thuc):")

while True:
    try:
        item = input().strip().lower()
        if item:
            grocery_list[item] = grocery_list.get(item, 0) + 1
    except EOFError:
        break
for item in sorted(grocery_list):
    print(f"{grocery_list[item]} {item.upper()}")