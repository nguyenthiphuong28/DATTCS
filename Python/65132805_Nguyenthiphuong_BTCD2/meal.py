def main():
    time = input("what time is it")
    time_in_hours = convert(time)
    if 7 <= time_in_hours <= 8:
        print("breakfast time")
    elif 12 <= time_in_hours <= 13:
        print("lunch time")
    elif 18 <= time_in_hours <= 19:
        print("dinner time")
    
def convert(time):
    hours, minutes = time.split(":")
    hours = float(hours)
    minutes = float(minutes)
    return hours + minutes / 60
if __name__ == "__main__":
    main()