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

@app.route("/Q1", methods=['POST','GET'])
def Q1():
    return """
    <!DOCTYPE html>
	<html lang="en">
	<head>
	  <meta charset="utf-8">
	  <title>Question1</title>
	</head>
	<body>
	<form method="POST" action="/process1">
	  <label for="username">Please enter the hashtag: </label>
	  <input type="text" name="expr"><br>
	  <input type="submit" value="SEND">
	</form>
	</body>
	</html>
	""",300

@app.route('/process1', methods=['POST','GET'])
def process1():
    _username = request.form.get('expr')  # get(attr) returns None if attr is not present
    print(str(_username))
    print("Hello....checking")
    if _username:
    	cluster = Cluster()
    	session = cluster.connect()
    	session.execute('use de')
    	list_of_rows=session.execute('select count(*) as count,hashtag,location from Q1 where hashtag=\''+_username+'\'group by hashtag,location allow filtering')
    	# for row in list_of_rows:
    	# 	print(str(row.date_time)+"\t\t\t"+str(row.tid)+"\t\t\t"+str(row.lang)+"\t\t\t"+str(row.author))
    	# 	print("hello")
    	# print(str(rows.tid)+"hhh")
    	return render_template('a.html',rows1=list_of_rows)# observe here we have used a.html for showing our final result
    else:
        return 'Please go back and enter your name...', 400  # 400 Bad Request

 
if __name__ == "__main__":
    app.run()

# {% for i in rows: %}
# 	{% if(i.date_time): %} 
#     	{{i.date_time}}
#     {% endif %}
# {%endfor%}

# file1 = open("./file1.csv","w")
# file2 = open("./file2.csv","w")
# for row in one :
#     x = row.hashtag+","+row.mention+","+str(row.count1)+"\n"
#     file1.write(x)
# for row in two:
#     x=str(row.date)+","+row.hashtag+","+row.location.replace(",","")+","+str(row.count1)+"\n"
#     print x