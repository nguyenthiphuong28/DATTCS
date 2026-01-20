def main():
    amount_due = 50
    while amount_due > 0:
        print("Amount due:", amount_due)
        coin = int(input("Insert coin: "))
        if coin in [1, 5, 10, 25]:
            amount_due -= coin
    change_owed = abs(amount_due)
    print("Change owed:", change_owed)
if __name__ == "__main__":
    main()