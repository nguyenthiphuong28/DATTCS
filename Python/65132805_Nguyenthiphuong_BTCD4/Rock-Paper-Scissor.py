import random
choices = ["keo", "bua", "bao"]
print ("== Tro choi oan tu ti ==")
print ("Nhap keo, bua, bao de choi")
player_score = 0
computer_score = 0
while player_score < 3 and computer_score < 3:
    player = input("Ban chon (keo, bua, bao): ").strip().lower()
    if player not in choices:
        print("Lua chon khong hop le. Vui long chon lai.")
        continue
    computer = random.choice(choices)
    print(f"May chon: {computer}")
    if player == computer:
        print("Hoa!")
    elif (player == "keo" and computer == "bao") or \
         (player == "bua" and computer == "keo") or \
         (player == "bao" and computer == "bua"):
        print("Ban thang!")
        player_score += 1
    else:
        print("May thang!")
        computer_score += 1
    print(f"Diem cua ban: {player_score}, Diem cua may: {computer_score}")
if player_score == 3:
    print("Chuc mung! Ban da thang tro choi.")
else:
    print("May da thang tro choi. Chuc ban may manh!")