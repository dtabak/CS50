import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import date

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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]
    username = db.execute("SELECT username FROM users WHERE id = ?", user_id)[0]["username"]

    portfolio = db.execute("SELECT stock, SUM(share) AS share FROM portfolio WHERE username = ? GROUP BY username, stock", username)
    cash = round(db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]["cash"],2)

    i=0
    grand = cash
    dict=[]

    for row in portfolio:
        quote = lookup(row["stock"])
        #if not quote:
        #    continue
        price = quote["price"]
        dict.append({"symbol": row["stock"], "shares": row["share"], "price": price, "total": price*row["share"]})
        grand = round(grand + dict[i]["total"],2)
        i += 1

    return render_template("index.html", dict=dict, cash=cash, grand=grand)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        if request.form is None:
            return apology("no form", 400)
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not symbol:
            return apology("must provide symbol", 400)

        # Ensure shares was submitted and is a whole number
        elif not shares or not shares.isdigit():
            return apology("incorrect amount", 400)

        quote = lookup(symbol)

        # Ensure symbol is valid
        if quote is None:
            return apology("invalid symbol", 400)


        # Query cash for username
        if session is None:
            return apology("no session", 400)
        user_id = session["user_id"]
        userrow = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        if not userrow:
            return apology("user not found", 400)
        user = userrow[0]
        if not user:
            return apology("user not found", 400)
        username = user["username"]
        cash = user["cash"]

        # Ensure user can afford
        purchased = int(shares) * quote["price"]

        if cash < purchased:
            return apology("insufficient balance", 403)

        else:
            new_cash = cash - purchased
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)
            db.execute("INSERT INTO transactions (username, transaction_type, amount, transaction_date, symbol, share, price) VALUES (?,?,?,?,?,?,?)", username, 'buy', purchased, date.today(), symbol, int(shares), int(quote["price"]))
            db.execute("INSERT INTO portfolio (username, stock, share) VALUES (?,?,?)", username, symbol, int(shares))
            # Redirect user to home page
            return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query database for username
    user_id = session["user_id"]
    username = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]["username"]

    rows = db.execute("SELECT * FROM transactions WHERE username = ?", username)

    return render_template("history.html", rows = rows)

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

     # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure the symbol exists
        quote = lookup(request.form.get("symbol"))

        if not request.form.get("symbol") or not quote:
            return apology("Invalid symbol", 400)

     # Return stock information
        else:
            return render_template("quoted.html", quote=quote)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation password was submitted
        elif not request.form.get("confirmation") or request.form.get("password") != request.form.get("confirmation"):
            return apology("must provide confirmation", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username does not exist
        if len(rows) == 1:
            return apology("username already exists", 400)

        # Insert user to db
        password_hash = generate_password_hash(request.form.get("password"))
        db.execute("INSERT INTO users (username, hash) VALUES (?,?)", request.form.get("username"), password_hash)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] =  rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    user = db.execute("SELECT * FROM users WHERE id = ?", user_id)[0]
    username = user["username"]
    portfolio = db.execute("SELECT stock, SUM(share) AS share FROM portfolio WHERE username = ? GROUP BY username, stock HAVING SUM(share)>0", username)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        # Ensure correct amount of shares was submitted
        share = int(request.form.get("shares"))

        if not request.form.get("shares") or share<0:
            return apology("invalid shares", 400)

        # Check if the user has enough balance

        i = 0
        for row in portfolio:
            if request.form.get("symbol") == row["stock"]:
                if share <= row["share"]:
                    i += 1

        if i == 0:
            return apology("insufficient balance", 400)

        # Query current price of the stock
        quote = lookup(request.form.get("symbol"))

        if quote is None:
            return apology("invalid symbol", 400)

        #Update database
        sold = share * quote["price"]
        cash = user["cash"]
        new_cash = cash + sold

        db.execute("UPDATE users SET cash = ? WHERE username = ?", new_cash, username)
        db.execute("INSERT INTO transactions (username, transaction_type, amount, transaction_date, symbol, share, price) VALUES (?,?,?,?,?,?,?)", username, 'sell', sold, date.today(), quote["symbol"], int(request.form.get("shares")), int(quote["price"]))
        db.execute("INSERT INTO portfolio (username, stock, share) VALUES (?,?,?)", username, quote["symbol"], share * (-1))
        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", portfolio=portfolio)

