# TODO
import cs50


height = 0
while height > 8 or height < 1:
    height = cs50.get_int("What should be the height? \n")

for i in range(height):
    for k in range(height - (i + 1)):
        print(" ", end="")
    for j in range(i + 1):
        print("#", end="")
    print()
