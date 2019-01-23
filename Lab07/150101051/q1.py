import json
import sys
import os
from pprint import pprint
from cassandra.cluster import Cluster
from cassandra.policies import DCAwareRoundRobinPolicy
cluster = Cluster(load_balancing_policy=DCAwareRoundRobinPolicy())
session = cluster.connect()
session.execute('drop keyspace if exists de')
session.execute(
    """
    CREATE KEYSPACE IF NOT EXISTS de WITH REPLICATION = {
        'class' : 'SimpleStrategy',
        'replication_factor' : 1
    }
    """
)
path = './workshop_dataset1/'
session.set_keyspace('de')
# session.execute('use de')
session.execute('drop table if exists de')
session.execute(
	"""
	create table Q1(
		tid text, 
		location text, 
		hashtag text,
		primary key(hashtag,location,tid) 
	)with clustering order by(location desc, tid desc);
	"""
)
for filename in os.listdir(path):
	print(filename)
	data = json.load(open(path+filename))
	for x in data:#None is not iterable
		if(data[x]["hashtags"] and data[x]["location"]):
			for y in data[x]["hashtags"]:
				if(y):
					print(y)
					session.execute(
						"""
						insert into Q1(tid,location,hashtag)
						values (%(tid)s,%(location)s,%(hashtag)s)
						""",
						{
						'tid':data[x]["tid"],
						'location':data[x]["location"],
						'hashtag':y,
						}
						)
hashtag1 = input("Question 1 : Enter hashtag name::\n")
list_of_rows = session.execute('select count(*) as count,hashtag,location from Q1 where hashtag=\''+hashtag1+'\'group by hashtag,location allow filtering')
#print(type(list_of_rows))
file1=open("file1.csv","w");
for row in list_of_rows:
	x=str(row.hashtag)+";"+str(row.location)+";"+str(row.count)+"\n"
	print(str(row.hashtag)+"\t\t\t"+str(row.location)+"\t\t\t"+str(row.count))
	file1.write(x)