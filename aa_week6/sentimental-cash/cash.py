import math


def main():
    cash = get_cash()
    quarters = calc_quarters(cash)
    cash = round(cash - 0.25 * quarters, 2)
    dimes = calc_dimes(cash)
    cash = round(cash - 0.1 * dimes, 2)
    nickles = calc_nickles(cash)
    cash = round(cash - 0.05 * nickles, 2)
    pennies = calc_pennies(cash)
    cash = round(cash - 0.01 * pennies, 2)
    coins = calc_coins(quarters, dimes, nickles, pennies)

    print(coins)


def calc_quarters(cash):
    quarters = math.trunc(cash / 0.25)
    return quarters


def calc_dimes(cash):
    dimes = math.trunc(cash / 0.1)
    return dimes


def calc_nickles(cash):
    nickles = math.trunc(cash / 0.05)
    return nickles


def calc_pennies(cash):
    pennies = math.trunc(cash / 0.01)
    return pennies


def calc_coins(quarters, dimes, nickles, pennies):
    return quarters + dimes + nickles + pennies


def get_cash():
    while True:
        try:
            cash = float(input("Cash: "))
            if cash > 0:
                return cash
        except ValueError:
            print("Not valid input")


main()