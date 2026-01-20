def main():
    text = input("Input: ")
    print("Output:", shorten(text))

def shorten(text):
    vowels = "aeiouAEIOU"
    result = ""
    for char in text:
        if char not in vowels:
            result += char
    return result
if __name__ == "__main__":
    main()