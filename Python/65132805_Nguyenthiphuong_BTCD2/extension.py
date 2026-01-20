def main():
    filename = input("File name: ").strip().lower()
    if "." in filename:
        #rsplit: tách chuỗi thành các phần tử trong danh sách từ phải sang trái
        #[-1] lấy phần tử cuối cùng trong danh sách
        ext = filename.rsplit(".", 1)[-1]
    else:
        ext = ""
    match ext:
        case "gif":
            print("image/gif")
        case "jpg" | "jpeg":
            print("image/jpeg")
        case "png":
            print("image/png")
        case "pdf":
            print("application/pdf")
        case "txt":
            print("text/plain")
        case "zip":
            print("application/zip")
        case _:
            print("application/octet-stream")
main()
    