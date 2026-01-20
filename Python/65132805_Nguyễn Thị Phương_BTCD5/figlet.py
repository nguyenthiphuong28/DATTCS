import sys
import random
from pyfiglet import Figlet

def main():
    figlet = Figlet()
    fonts = figlet.getFonts()

    # Kiểm tra số lượng đối số
    if len(sys.argv) == 1:
        # Không có đối số -> font ngẫu nhiên
        font = random.choice(fonts)

    elif len(sys.argv) == 3 and sys.argv[1] in ['-f', '--font']:
        # Có 2 đối số -> font cụ thể
        font = sys.argv[2]
        if font not in fonts:
            sys.exit("Invalid usage")
    else:
        sys.exit("Invalid usage")

    # Đặt font và in
    figlet.setFont(font=font)
    text = input("Input: ")
    print("Output:")
    print(figlet.renderText(text))

if __name__ == "__main__":
    main()
