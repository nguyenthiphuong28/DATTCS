from fpdf import FPDF

def main():
    name = input("Name: ")

    pdf = FPDF(orientation="P", unit="mm", format="A4")
    pdf.add_page()

    # Tiêu đề
    pdf.set_font("Helvetica", "B", 32)
    pdf.cell(0, 30, "CS50 Shirtificate", ln=True, align="C")

    # Chèn ảnh áo (tự điều chỉnh vị trí)
    pdf.image("shirtificate.png", x=10, y=50, w=pdf.w - 20)

    # Viết tên người dùng trên áo
    pdf.set_font("Helvetica", "B", 28)
    pdf.set_text_color(255, 255, 255)       # chữ màu trắng
    pdf.set_xy(0, 150)                      # điều chỉnh để chữ nằm trên áo
    pdf.cell(210, 20, name, align="C")      # căn giữa theo chiều ngang

    # Xuất file PDF
    pdf.output("shirtificate.pdf")
    print("Đã tạo shirtificate.pdf!")

if __name__ == "__main__":
    main()
