# TODO

from cs50 import get_float

def main():
    # Ask how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 0.25
    cents = float(f"{cents:.2f}")

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 0.10
    cents = float(f"{cents:.2f}")

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 0.05
    cents = float(f"{cents:.2f}")

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 0.01
    cents = float(f"{cents:.2f}")

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(f"{coins}")


def get_cents():
    while True:
        x = get_float("Change owed: ")
        if x>0:
            break
    return x

def calculate_quarters(x):
    i = int(x/0.25)
    return i

def calculate_dimes(x):
    i = int(x/0.10)
    return i

def calculate_nickels(x):
    i = int(x/0.05)
    return i

def calculate_pennies(x):
    i = int(x/0.01)
    return i

main()
