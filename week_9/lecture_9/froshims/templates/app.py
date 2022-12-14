from flask import Flask, render_template, request, redirect

app = Flask(__name__)

SPORTS = [
    "Basketball",
    "Soccer",
    "Football",
    "Ultimate Frisbee"
]

REGISTRANTS = dict()

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/register", methods=["POST"])
def register():
    # Validate sport
    name = request.form.get("name")
    if not name:
        return render_template("register.html", message="Missing name")

    # Validate sport
    sport = request.form.get("sport")
    if not sport:
        return render_template("register.html", message="Missing sport")

    if sport not in SPORTS:
        return render_template("register.html", message="Invalid sport")

    # Remember registrant
    REGISTRANTS[name] = sport

    # Confirm registration
    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    return render_template("registrants.html", registrants=REGISTRANTS)

