from py2neo import Graph
from py2neo import Node
from py2neo import Relationship
from py2neo import authenticate
import os
import json
import sys
import itertools
#"neo4j", "hari0404"
# Given    a    user
# (author_screen_name),    find    all    the    other    users 
# (author_screen_names)  who  have  replied  to  the  tweets  posted  by  the  given 
# user. Display the output on the basis of reply count per tweet.  Sort users in 
# decreasing  order  of  the  number  of  replies.  Your  output  sh
# ould  include  the 
# following :
# User1 
# Tweetid of tweet posted by user1 
# User replying to this tweet 
# Tweet
# id of the replies 
# (tweet_type : Reply) 
# Reply Count 
authenticate("localhost:7474","neo4j","hari0404")
graph = Graph("http://localhost:7474/db/data/")
# graph=Graph()
graph.cypher.execute("match (n) detach delete n")
graph.cypher.execute("create index on :Author(author_screen_name)")
graph.cypher.execute("create index on :Tweet(tid)")
graph.cypher.execute("create index on :HashTag(hashtag)")
graph.cypher.execute("create index on :Keyword(keyword)")
path = './workshop_dataset/'
cypher=graph.cypher
for filename in os.listdir(path):
	print(filename)
	data = json.load(open(path+filename))
	for j,x in enumerate(data):#None is not iterable
		if(data[x]["author_screen_name"]):#if author_screen_name is not null
			print("author screen name::"+data[x]["author_screen_name"])
			cypher.execute(		
				"merge(a:Author {author_screen_name:{a1}}) set a.tid={a2}", 
				a1=data[x]["author_screen_name"],a2=data[x]["tid"]
				)
		if(data[x]["tid"]):
			print("author tid::"+data[x]["tid"])
			cypher.execute(
				"merge(b:Tweet {tid:{b1}}) set b.tweet={b2}",
				b1=data[x]["tid"],b2=data[x]["tweet_text"]
				)
		####
		####
		#Tweets is the relationship 
		cypher.execute(
			"merge (a:Author {author_screen_name:{a1}}) merge (b:Tweet {tid:{b1}}) merge (a) - [:Tweets] -> (b) merge (a) <- [:Tweetedby] - (b)",
			a1=data[x]["author_screen_name"],b1=data[x]["tid"]
			)
		if(data[x]["replyto_source_id"]):
			print("replyto_source_id is::"+data[x]["replyto_source_id"])
			cypher.execute(
				"merge(a:Tweet {tid:{a1}}) merge(b:Tweet{tid:{b1}}) merge (a)-[:replied]->(b)",
				a1=data[x]["tid"],b1=data[x]["replyto_source_id"]
				)
# match (u1:Author)-[:Tweets]->(:Tweet)<-[:replied]-(:Tweet)<-[:Tweets]-(u2:Author) where u1.author_screen_name="moorlee" return u1.author_screen_name,u2.author_screen_name,count(*) order by count(*) desc
# match (u1:Author)-[:Tweets]->(t1:Tweet)<-[:replied]-(t2:Tweet)<-[:Tweets]-(u2:Author) where u1.author_screen_name="SanjayP44365097" return u1.author_screen_name,t1.tid,u2.author_screen_name,t2.tid,count(*) order by count(*) desc
		#mentions_relationship is the relationship
		if(data[x]["mentions"]):
			for i3,mention in enumerate(data[x]["mentions"]):
				if(mention != ""):
					print("mention is::"+mention)
					cypher.execute(
						"merge(b:Tweet {tid:{b1}}) merge (a:Author {author_screen_name:{a1}}) merge (b) - [:mentions] -> (a)",
						b1=data[x]["tid"],a1=data[x]["author_screen_name"]
						)
# match (h:Hashtag)<-[:hashtag_relationship]-(:Tweet)-[:mentions]->(u:Author) where h.hashtag="ThursdayThoughts" return h.hashtag,u.author_screen_name,count(*) order by count(*) DESC limit 20
# match (u1:Author)-[:Tweets]->(:Tweet)<-[:mentions]-(t2:Tweet)<-[:Tweets]-(u2:Author) where u1.author_screen_name="morlee" return u1.author_screen_name,u2.author_screen_name,t2.tid,count(*) as mention_count order by count(*) desc limit 2