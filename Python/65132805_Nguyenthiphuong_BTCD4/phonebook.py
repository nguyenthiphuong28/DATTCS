def them_danh_ba(phonebook):
    name = input("Nhap ten:").strip()
    if name in phonebook:
        print("Ten da ton tai.")
        return
    phone = input("Nhap so dien thoai:").strip()
    phonebook[name] = phone
    print ("Da them danh ba thanh cong!\n")

def tim_danh_ba(phonebook):
    name = input("Nhap ten can tim:").strip()
    if name in phonebook:
        print(f"{name}: {phonebook[name]}\n")
    else:
        print("Khong tim thay danh ba.\n")

def xoa(phonebook):
    name = input("Nhap ten can xoa:").strip()
    if name in phonebook:
        del phonebook[name]
        print("Da xoa danh ba thanh cong!\n")
    else:
        print("Khong tim thay danh ba.\n")

def sua(phonebook):
    name = input("Nhap ten can sua:").strip()
    if name in phonebook:
        phone = input("Nhap so dien thoai moi:").strip()
        phonebook[name] = phone
        print("Da sua danh ba thanh cong!\n")
    else:
        print("Khong tim thay danh ba.\n")

def hien_thi(phonebook):
    if not phonebook:
        print("Danh ba trong.\n")
        return
    print("Danh ba:")
    for name in sorted(phonebook):
        print(f"{name}: {phonebook[name]}")
    print()

def main():
    phonebook = {}
    while True:
        print("Menu:")
        print("1. Them danh ba")
        print("2. Tim danh ba")
        print("3. Xoa danh ba")
        print("4. Sua danh ba")
        print("5. Hien thi danh ba")
        print("6. Thoat")
        choice = input("Chon mot tuy chon (1-6): ").strip()
        if choice == '1':
            them_danh_ba(phonebook)
        elif choice == '2':
            tim_danh_ba(phonebook)
        elif choice == '3':
            xoa(phonebook)
        elif choice == '4':
            sua(phonebook)
        elif choice == '5':
            hien_thi(phonebook)
        elif choice == '6':
            print("Thoat chuong trinh.")
            break
        else:
            print("Lua chon khong hop le. Vui long chon lai.\n")
if __name__ == "__main__":
    main()