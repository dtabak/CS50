# TODO

from cs50 import get_int

height = get_int("Height:")

while height<1 or height>8:
    height = get_int("Height:")

x=height-1

for i in range(height):
    for k in range(x):
        print(" ", end = "")
    for j in range(height-x):
        print("#", end = "")
    print("")
    x -= 1



