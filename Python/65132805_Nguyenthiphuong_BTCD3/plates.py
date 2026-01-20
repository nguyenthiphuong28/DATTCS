def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")
    
def is_valid(s):
    #kiem tra do dai
    if not (2 <= len(s) <= 6):
        return False
    #kiem tra ky tu dau tien phai la chu cai
    if not s[0].isalpha() and not s[1].isalpha():
        return False
    #khong chua dau cach, dau cham hoac ky tu dac biet
    if not s.isalnum():
        return False
    #kiem tra so co phai nam o cuoi khong
    number_found = False
    for i, c in enumerate(s):
        if c.isdigit():
            if not number_started:
                number_started = True
                if c == '0':
                    return False
            
        elif number_started:
            return False
    return True 
if __name__ == "__main__":
    main()