from flask import Flask
from config import Config
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_login import LoginManager
import logging
from logging.handlers import SMTPHandler, RotatingFileHandler
import os

app = Flask(__name__)

# load configuration options from Config class in config.py
app.config.from_object(Config)
db = SQLAlchemy(app)  # database instance
migrate = Migrate(app, db)  # instance for the migration engine
login = LoginManager(app)  # login instance
login.login_view = 'login'  # view function that handles logins, 'login' is the endpt.

# circular imports
from app import routes, models, errors

# Logging will be used only when not in debug mode
if not app.debug:
    ###################################################
    #             Email Logger Code
    ###################################################
    if app.config['MAIL_SERVER']:
        # authentication tuple of (username, password)
        auth = None
        # will be a 0 element tuple to use TLS without providing
        # a certificate and private key
        secure = None
        if app.config['MAIL_USERNAME'] or app.config['MAIL_PASSWORD']:
            auth = (app.config['MAIL_USERNAME'], app.config['MAIL_PASSWORD'])
        if app.config['MAIL_USE_TLS']:
            secure = ()
        mail_handler = SMTPHandler(
            mailhost=(app.config['MAIL_SERVER'], app.config['MAIL_PORT']),
            fromaddr='no-reply@' + app.config['MAIL_SERVER'],
            toaddrs=app.config['ADMINS'], subject='Microblog Failure',
            credentials=auth, secure=secure)
        mail_handler.setLevel(logging.ERROR)
        app.logger.addHandler(mail_handler)

    ###################################################
    #               Log File Code
    ###################################################
    if not os.path.exists('logs'):
        os.mkdir('logs')
    file_handler = RotatingFileHandler('logs/microblog.log', maxBytes=10240,
                                       backupCount=10)
    
    # custom formatting of log entries
    file_handler.setFormatter(logging.Formatter(
        '%(asctime)s %(levelname)s: %(message)s [in %(pathname)s:%(lineno)d]'))
    
    # log level set to 'INFO'
    file_handler.setLevel(logging.INFO)

    app.logger.addHandler(file_handler)
    app.logger.setLevel(logging.INFO)
    app.logger.info('Microblog startup')
