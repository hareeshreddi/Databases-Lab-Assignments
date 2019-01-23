from flask import Flask,render_template, json, request
import json
import sys
import os
from pprint import pprint
from cassandra.cluster import Cluster
from cassandra.policies import DCAwareRoundRobinPolicy
cluster = Cluster(load_balancing_policy=DCAwareRoundRobinPolicy())
app = Flask(__name__)
 
@app.route("/")
def index():
    return "Index!"
@app.route("/hello")
def hello():
    return "Hello World!"
@app.route("/members/<string:name>/")
def getMember(name):
    return name

@app.route("/Q2", methods=['POST','GET'])
def Q2():
    return """
    <!DOCTYPE html>
	<html lang="en">
	<head>
	  <meta charset="utf-8">
	  <title>QUESTION02</title>
	</head>
	<body>
	<form method="POST" action="/process2">
	  <label for="username">Please enter the Date: </label>
	  <input type="text" name="expr"><br>
	  <input type="submit" value="SEND">
	</form>
	</body>
	</html>
	""",301

@app.route('/process2', methods=['POST','GET'])
def process2():
    _username = request.form.get('expr')  # get(attr) returns None if attr is not present
    print(str(_username))
    print("Hello....checking")
    if _username:
    	cluster = Cluster()
    	session = cluster.connect()
    	session.execute('use de1')
    	list_of_rows=session.execute('select count(*) as count,date,hashtag,location from Q2 where date=\''+_username+'\'group by date,hashtag,location allow filtering')
    	# for row in list_of_rows:
    	# 	print(str(row.date_time)+"\t\t\t"+str(row.tid)+"\t\t\t"+str(row.lang)+"\t\t\t"+str(row.author))
    	# 	print("hello")
    	# print(str(rows.tid)+"hhh")
    	return render_template('b.html',rows1=list_of_rows)
    else:
        return 'Please go back and enter your name...', 400  # 400 Bad Request
 
if __name__ == "__main__":
    app.run()

# {% for i in rows: %}
# 	{% if(i.date_time): %} 
#     	{{i.date_time}}
#     {% endif %}
# {%endfor%}