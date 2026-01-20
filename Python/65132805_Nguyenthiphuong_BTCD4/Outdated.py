months = ["January", "February", "March", "April", "May", "June",
          "July", "August", "September", "October", "November", "December"]
while True:
    date = input("Date: ").strip()
    try:
        if "/" in date:
            month, day, year = date.split("/")
        elif "," in date:
            month, day_year = date.split(" ", 1)
            dy, year = day_year.replace(",", "").split(" ")
            day = int(day)
            month = months.index(month) + 1
        else:
            raise ValueError
        if not(1 <= int(month) <= 12 and 1 <= int(day) <= 31):
            raise ValueError
        print(f"{int(year):04}-{int(month):02}-{int(day):02}")
        break
    except (ValueError, IndexError):
        pass