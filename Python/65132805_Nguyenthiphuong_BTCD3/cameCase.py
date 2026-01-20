def main():
    camel = input("camelCase: ")
    snake = ""
    for char in camel:
        if char.isupper():
            snake += "_" + char.lower()
        else:
            snake += char
    print("snake_case:", snake)
if __name__ == "__main__":
    main()