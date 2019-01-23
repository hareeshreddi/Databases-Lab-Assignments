from flask import Flask,render_template, json, request
# from pprint import pprint
# from cassandra.cluster import Cluster
# from cassandra.policies import DCAwareRoundRobinPolicy
# cluster = Cluster(load_balancing_policy=DCAwareRoundRobinPolicy())
from py2neo import Graph
from py2neo import Node
from py2neo import Relationship
from py2neo import authenticate
import os
import json
import sys
import itertools
#"neo4j", "hari0404"
authenticate("localhost:7474","neo4j","hari0404")
graph = Graph("http://localhost:7474/db/data/")
cypher=graph.cypher
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
	  <label for="username">Please enter the Username: </label>
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
    	# list_of_rows=session.execute('select count(*) as count,hashtag,location from Q1 where hashtag=\''+_username+'\'group by hashtag,location allow filtering')
    	# for row in list_of_rows:
    	# 	print(str(row.date_time)+"\t\t\t"+str(row.tid)+"\t\t\t"+str(row.lang)+"\t\t\t"+str(row.author))
    	# 	print("hello")
    	# print(str(rows.tid)+"hhh")#-[:Tweets]->(:Tweet)
        print(_username)
        list_of_rows=cypher.execute('match (u2:Author)-[:Tweets]->(t2:Tweet)-[:mentions]->(u1:Author) where u1.author_screen_name=\''+_username +'\' return u1.author_screen_name,u2.author_screen_name,collect(t2.tid) as tids,count(*) as mention_count order by mention_count desc limit 2')
        # u1:Author)<-[:mentions]-(t2:Tweet)<-[:Tweets]-(u2:Author)

        print(list_of_rows)
        # for row in list_of_rows:
        #     print(str(row['u1.author_screen_name']))
    	return render_template('a.html',rows1=list_of_rows)
    else:
        return 'Please go back and enter your name...', 400  # 400 Bad Request

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
      <label for="username">Please enter the Username: </label>
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
        # list_of_rows=session.execute('select count(*) as count,date,hashtag,location from Q2 where date=\''+_username+'\'group by date,hashtag,location allow filtering')
        # for row in list_of_rows:
        #   print(str(row.date_time)+"\t\t\t"+str(row.tid)+"\t\t\t"+str(row.lang)+"\t\t\t"+str(row.author))
        #   print("hello")
        # print(str(rows.tid)+"hhh")
        list_of_rows=cypher.execute('match (u1:Author)-[:Tweets]->(t1:Tweet)<-[:replied]-(t2:Tweet)<-[:Tweets]-(u2:Author) where u1.author_screen_name=\''+_username+'\' return u1.author_screen_name,t1.tid,u2.author_screen_name,t2.tid,count(*) as count order by count(*) desc')
        return render_template('b.html',rows1=list_of_rows)
    else:
        return 'Please go back and enter your name...', 400  # 400 Bad Request
 
if __name__ == "__main__":
    app.run()