purchases_id = db.execute("SELECT purchases.id "
"FROM purchases "
"JOIN users ON users.id = purchases.user_id " 
"JOIN stocks ON stocks.id = purchases.stock_id " 
"WHERE users.id = ? AND stocks.symbol = ?", session["user_id"], symbol)

SELECT stocks.name, transactions.price, transactions.shares
FROM purchases
JOIN users ON users.id = purchases.user_id
JOIN transactions ON transactions.id = purchases.transaction_id
JOIN stocks ON stocks.id = transactions.stock_id
WHERE purchases.user_id = 2 

SELECT stocks.name
FROM purchases
JOIN users ON users.id = purchases.user_id
JOIN stocks ON stocks.id = purchases.stock_id
JOIN transactions ON stocks.id = transactions.stock_id
WHERE purchases.user_id = 3

SELECT stocks.name
FROM purchases
JOIN users ON users.id = purchases.user_id
JOIN stocks ON stocks.id = purchases.stock_id AND stocks.id = transactions.stock_id
WHERE purchases.user_id = 3

SELECT stocks.name
FROM purchases 
JOIN users ON users.id = purchases.user_id 
JOIN stocks ON stocks.id = purchases.stock_id 
JOIN transactions ON users.id = transactions.user_id AND stocks.id = transactions.stock_id
WHERE purchases.user_id = 3

CREATE TABLE purchases (
	user_id INTEGER NOT NULL,
	stock_id INTEGER NOT NULL,
	FOREIGN KEY(user_id) REFERENCES users(id),
	FOREIGN KEY(stock_id) REFERENCES stocks(id)
)

CREATE TABLE transactions (
	id INTEGER NOT NULL,
	purchase_id INTEGER NOT NULL,
	price NUMERIC NOT NULL,
	shares INTEGER NOT NULL,
	FOREIGN KEY(purchase_id) REFERENCES (id),
	FOREIGN KEY(stock_id) REFERENCES stocks(id),
	FOREIGN KEY(user_id) REFERENCES users(id),
	PRIMARY KEY(id)
)

SELECT stocks.name
FROM purchases 
JOIN users ON users.id = purchases.user_id
JOIN stocks ON stocks.id = purchases.stock_id
WHERE users.id = 3