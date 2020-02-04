from flask import Flask
from config import Config
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_login import LoginManager

app = Flask(__name__)

# load configuration options from Config class in config.py
app.config.from_object(Config)
db = SQLAlchemy(app) # database instance
migrate = Migrate(app, db) # instance for the migration engine
login = LoginManager(app) # login instance
login.login_view = 'login' # view function that handles logins, 'login' is the endpt.

from app import routes, models
