import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
@login_required
def index():
    """Show portfolio of stocks"""
    # This is my addition to the finance problem set, I wanted a way to see how much you have gained or lost base on the current market rate.
    # Additionally I added a way to see your investment success or failiure based on your account size, and how much you started with

    try:
        # query database for user info, then fetch new market prices using api, calc assets
        id = session["user_id"]
        portfolio = db.execute("SELECT * FROM portfolio WHERE user_id == ? ORDER BY id ASC", id)
        market_price = []
        assets = 0

        # loops through dictionary we got from db.execute
        for i in range(len(portfolio)):
            symbol = portfolio[i]['symbol']
            price = lookup(symbol)
            market_price.append(price)
            assets += portfolio[i]['quantity'] * price['price']

        user_info = db. execute("SELECT initial_deposit, cash FROM users WHERE id == ?", id)
        assets += user_info[0]['cash']

        return render_template("index.html", portfolio=portfolio, market_price=market_price, user_info=user_info, assets=assets)
    
    except:

        # if failed go back to login page
        return redirect("/login")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Initialize values for buys
        id = session["user_id"]
        action = "Buy"
        symbol = request.form.get("symbol")
        symbol = symbol.upper()
        amount = request.form.get("shares")
        cash = db.execute("SELECT cash FROM users WHERE id = ?", id)

        # Catch errors & do calcs
        try:
            price = lookup(symbol)
            price = price['price']
        except:
            return apology("Transaction failed")
        try:
            amount = int(amount)
        except ValueError:
            return apology("Transaction failed")

        if amount < 0:
            return apology("INVALID SHARES")

        total_amount = float(amount) * price
        display_amount = usd(total_amount)

        if total_amount > cash[0]['cash']:
            return apology("Not enough cash in account")

        new_cash = float(cash[0]['cash']) - total_amount
        time = datetime.datetime.now()

        # data base executions
        db.execute("INSERT INTO portfolio (user_id, symbol, quantity, price) VALUES (?, ?, ?, ?)", id, symbol, amount, price)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, id)
        db.execute("INSERT INTO history (user_id, symbol, quantity, action, price, time) VALUES (?, ?, ?, ?, ?, ?)", id, symbol, amount, action, price, time)
        current_balance = db.execute("SELECT cash FROM users WHERE id = ?", id)

        current_balance = usd(current_balance[0]['cash'])
        outcome = "Success, bought " + str(amount) + " of " + symbol + " for " + str(total_amount)

        # display values and outcomes
        return render_template("buy.html", outcome=outcome, display_amount=display_amount, current_balance=current_balance)
    else:
        return render_template("buy.html")



@app.route("/history", methods=["GET"])
@login_required
def history():
    """Show history of transactions"""
    # Send history dictionary from database to history.html template
    id = session["user_id"]
    history = db.execute("SELECT * FROM history WHERE user_id == ?", id)
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method =="POST":

        # Initialize values
        symbol = request.form.get("symbol")

        # Catch empty value of symbol
        if not symbol:
            return apology("Error")

        # Api call if failed return error
        info = lookup(symbol)
        if not info:
            return apology("Symbol not found")

        # Send info to template
        return render_template("quote.html", info=info)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # Initilize values and check for errors
        username = request.form.get("username")
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) != 0:
            return apology("Username already exists")

        if not username:
            return apology("Error")

        password = request.form.get("password")

        hash = generate_password_hash(password)
        if not password:
            return apology("Error")

        confirmation = request.form.get("confirmation")
        if not confirmation:
            return apology("Error")

        deposit = request.form.get("deposit")

        #----------------
        # had to eliminate this becasuse of check50, but uncomment this line to make deposit on register mandatory)
        #if int(deposit or 0) < 0:
            #return apology("deposit cannot be negative")

        # And comment the if statement bellow to unset the default deposit value

        if not deposit:
            deposit = 10000

        #----------------

        # Password matching?
        if password != confirmation:
            return apology("password not matched")

        # Increment ID (can be done automatically, but this seemed more interesting)
        id = db.execute("SELECT id FROM users ORDER BY id DESC LIMIT 1")
        try:
            id = int(id[0]['id'] or 0) + 1
        except:
            # If its the first value in the database set to 1
            id = 1

        # Insert inital values to the database for the user and set current session to that users id
        db.execute("INSERT OR IGNORE INTO users (id, username, hash, cash, initial_deposit) VALUES (?, ?, ?, ?, ?)", id, username, hash, deposit, deposit)

        session["user_id"] = id

        # Redirect to index page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # We set id, and call database to see which symbols the user owns for input for the drop down menu
    id = session["user_id"]
    owned_symbols = db.execute("SELECT symbol FROM portfolio WHERE user_id = ?", id)

    if request.method == "POST":

        # Initialize values and call database for info on user
        action = "Sell"
        symbol = request.form.get("symbol")
        amount = int(request.form.get("shares"))
        initial_amount = amount
        cash = db.execute("SELECT cash FROM users WHERE id = ?", id)
        number_rows = db.execute("SELECT COUNT(*) FROM portfolio WHERE user_id = ? AND symbol = ?", id, symbol)
        amount_portfolio = db.execute("SELECT SUM(quantity) FROM portfolio WHERE user_id = ? AND symbol = ?", id, symbol)
        amount_portfolio = amount_portfolio[0]['SUM(quantity)']

        # Error catching
        try:
            price = lookup(symbol)
            price = price['price']
        except:
            return apology("Symbol does not exist")
        if number_rows == 0:
            return apology("You do not own any stock with that symbol")
        if amount_portfolio < amount:
            return apology("Slow down, you dont have that many shares")

        total_amount = float(amount) * price
        display_amount = usd(total_amount)

        if total_amount > cash[0]['cash']:
            return apology("Not enough shares in account")

        new_cash = float(cash[0]['cash']) + total_amount
        current_balance = usd(new_cash)
        time = datetime.datetime.now()

        # Why this While loop? On /buy i decided that it was not an option to add buys of sotcks of the same symbol to the same row in the database,
        # because the buy price can be different if a user buys AAPL at $30 and then 1 hour later at $28. This while loop sells the oldest shares of the user.
        # We can input any number of shares as long as the user's sum of all the shares of the symbol are greater or equal to the amount they want to sell. Likewise
        # the user doesnt need to bother with inputing a exact number of shares because it will all be unpdated responively.

        while amount > 0:
            stock_q = db.execute("SELECT quantity FROM portfolio WHERE user_id = ? AND symbol = ? ORDER BY id ASC LIMIT 1", id, symbol)
            stock_q = int(stock_q[0]['quantity'])
            print(stock_q)
            if amount < stock_q:
                new_stock_q = stock_q - amount
                amount = 0
                db.execute("UPDATE portfolio SET quantity = ? WHERE user_id = ? AND symbol = ? ORDER BY id ASC LIMIT 1", new_stock_q, id, symbol)
            if amount >= stock_q:
                db.execute("DELETE FROM portfolio WHERE user_id = ? AND symbol = ? ORDER BY id ASC LIMIT 1", id, symbol)
                amount = amount - stock_q

        # Query database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, id)
        db.execute("INSERT INTO history (user_id, symbol, quantity, action, price, time) VALUES (?, ?, ?, ?, ?, ?)", id, symbol, amount, action, price, time)

        outcome = "Success, sold " + str(initial_amount) + " of " + symbol + " for " + str(total_amount)

        # send values to template
        return render_template("sell.html", outcome=outcome, symbols=owned_symbols, display_amount=display_amount, current_balance=current_balance)
    else:
        return render_template("sell.html", symbols=owned_symbols)

