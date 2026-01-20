def main():
    nhap = input("Nhap loi chao cua ban").strip().lower()
    """
    Hàm startswith() được dùng để kiểm tra xem một 
    chuỗi (string) có bắt đầu bằng một chuỗi con cụ thể 
    nào đó hay không."""
    if nhap. startswith("hello"):
        print("$0")
    elif nhap.startswith("h"):
        print("$20")
    else:
        print("$100")
main()
