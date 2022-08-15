import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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
    empty = False
    grandTotal = 0

    purchases = db.execute("SELECT stocks.name, stocks.symbol, "
    "purchases.shares, purchases.price "
    "FROM purchases "
    "JOIN users ON users.id = purchases.user_id "
    "JOIN stocks ON stocks.id = purchases.stock_id "
    "WHERE users.id = ?", session["user_id"])

    # Calculate total price amount to display to user 
    for purchase in purchases:
        purchase["total"] = purchase["shares"] * purchase["price"]

    # General total
    for purchase in purchases:
        grandTotal = grandTotal + purchase["total"]

    user = db.execute("SELECT username, cash FROM users WHERE id = ?", session["user_id"])

    if len(purchases) == 0:
        empty = True

    return render_template("index.html", purchases=purchases, user=user, grandTotal=grandTotal, empty=empty)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Get user input
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if int(shares) < 1:
            return apology("Incorect value. Enter positive number of shares") 

        # Get API data
        stock = lookup(symbol)

        if stock == None:
            return apology("Invalid symbol")

        # Check if user has enough cash to buy stock
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        totalPriceSum = stock["price"] * int(shares)

        updatedCash = cash[0]["cash"] - totalPriceSum

        if updatedCash <= 0:
            return apology("You have not enough cash")

        # Update user cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedCash, session["user_id"])

        # Check if database already have stock name and symbol
        if len(db.execute("SELECT symbol FROM stocks WHERE symbol = ?", stock["symbol"])) == 0:
            db.execute("INSERT INTO stocks (name, symbol) VALUES(?, ?)", stock["name"], stock["symbol"])

        stock_id = db.execute("SELECT id FROM stocks WHERE name = ?", stock["name"])

        # Add stock into transactions table
        db.execute("INSERT INTO transactions (stock_id, user_id, price, shares) VALUES(?, ?, ?, ?)", 
                    stock_id[0]["id"], session["user_id"], stock["price"], shares)

        purchase = db.execute("SELECT stocks.id, purchases.shares, purchases.price "
        "FROM purchases "
        "JOIN users ON users.id = purchases.user_id "
        "JOIN stocks ON stocks.id = purchases.stock_id "
        "WHERE users.id = ? AND stocks.symbol = ?", session["user_id"], stock["symbol"])

        # Add or update stock into purchases table
        if len(purchase) == 0:
            db.execute("INSERT INTO purchases (stock_id, user_id, price, shares) VALUES(?, ?, ?, ?)", 
                        stock_id[0]["id"], session["user_id"], stock["price"], shares)
        else:
            price = stock["price"] + purchase[0]["price"]
            shares = int(shares) + purchase[0]["shares"]
            db.execute("UPDATE purchases SET price = ?, shares = ? WHERE user_id = ? AND stock_id = ?",  
                        price, shares, session["user_id"], purchase[0]["id"])

        flash('Bought')
    return render_template("buy.html")


@app.route("/history", methods=["GET", "POST"])
@login_required
def history():
    """Show history of transactions"""
    empty = False

    if request.method == "POST":
        if request.form.get("deleteRequest") == 'true':
            db.execute("DELETE FROM transactions WHERE user_id = ?", session["user_id"])
            flash('History was cleared')

    transactions = db.execute("SELECT stocks.name, stocks.symbol, "
    "transactions.shares, transactions.price, transactions.timestamp "
    "FROM transactions "
    "JOIN users ON users.id = transactions.user_id "
    "JOIN stocks ON stocks.id = transactions.stock_id "
    "WHERE users.id = ?", session["user_id"])

    if len(transactions) == 0:
        empty = True

    return render_template("history.html", transactions=transactions, empty=empty)


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
        flash('You were successfully logged in')
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
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if quote == None:
            return apology("Invalid symbol")

        return render_template("quote.html", requestMethod='post', quote=quote)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Validate user input
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("You must provide username", 403)
        
        elif not request.form.get("password"):
            return apology("You must provide password", 403)

        elif not request.form.get("confirmPassword"):
            return apology("You must confirm password", 403)

        # Check if database already have user with that username
        username = request.form.get("username")
        user = db.execute("SELECT username FROM users WHERE username = ?", username)

        if len(user) != 0:
            return apology("Sorry, username is already taken")

        # Get user password and repeated password
        password = request.form.get("password")
        confirmPassword = request.form.get("confirmPassword")

        # Check if passwords match
        if password != confirmPassword:
            return apology("Passwords don't match", 403)

        # Hash password and add to database
        hashedPassword = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hashedPassword)
        return redirect("/login")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Get API data
        stock = lookup(symbol)

        purchaseShares = db.execute("SELECT shares FROM purchases WHERE stock_id = "
        "(SELECT id FROM stocks WHERE symbol = ?)", symbol)

        if int(shares) > purchaseShares[0]["shares"]:
            return apology("Too many shares")
        elif int(shares) <= 0:
            return apology("Invalid value. Enter positive number")
        elif int(shares) == purchaseShares[0]["shares"]:
            db.execute("DELETE FROM purchases WHERE stock_id = "
            "(SELECT id FROM stocks WHERE symbol = ?)", symbol)
        else:
            updatedShares = purchaseShares[0]["shares"] - int(shares)
            db.execute("UPDATE purchases SET shares = ?", updatedShares)

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        updatedCash = cash[0]["cash"] + (stock["price"] * int(shares)) 

        db.execute("UPDATE users SET cash = ? WHERE id = ?", updatedCash, session["user_id"])

        shares = '-' + shares

        stock_id = db.execute("SELECT id FROM stocks WHERE name = ?", stock["name"])

        # Add stock into transactions table
        db.execute("INSERT INTO transactions (stock_id, user_id, price, shares) VALUES(?, ?, ?, ?)", 
                    stock_id[0]["id"], session["user_id"], stock["price"], shares)

        flash('Sold')

    symbols = db.execute("SELECT stocks.symbol "
    "FROM purchases "
    "JOIN users ON users.id = purchases.user_id "
    "JOIN stocks ON stocks.id = purchases.stock_id "  
    "WHERE users.id = ?", session["user_id"])

    return render_template("sell.html", symbols=symbols)
