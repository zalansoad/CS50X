greeting = input("Greeting: ")

if greeting.casefold().split()[0].replace(",", "") == "hello":
    print("$0")
elif greeting.casefold()[0] == 'h':
    print("$20")
else:
    print("$100")