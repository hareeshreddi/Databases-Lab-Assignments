# Date 
# -
# (hashtag
# -
# location) 
# -
# Number of times the hashtag
# -
# location pair is co
# -
# occurring on this date
# At the end, display the total number of such rows obtained
import json
import sys
import os
from pprint import pprint
from cassandra.cluster import Cluster
from cassandra.policies import DCAwareRoundRobinPolicy
cluster = Cluster(load_balancing_policy=DCAwareRoundRobinPolicy())
session = cluster.connect()
session.execute('drop keyspace if exists de1')
session.execute(
    """
    CREATE KEYSPACE IF NOT EXISTS de1 WITH REPLICATION = {
        'class' : 'SimpleStrategy',
        'replication_factor' : 1
    }
    """
)
path = './workshop_dataset1/'#workshop_dataset1
session.set_keyspace('de1')
# session.execute('use de1')
session.execute('drop table if exists de1')
session.execute(
	"""
	create table Q2(
	date text,
	hashtag text,
	location text,
	tid text,
	primary key(date,hashtag,location,tid)
	)with clustering order by(hashtag desc, location desc, tid asc);
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
						insert into Q2(date,hashtag,location,tid)
						values (%(date)s,%(hashtag)s,%(location)s,%(tid)s)
						""",
						{
						'date':data[x]["date"],
						'hashtag':y,
						'location':data[x]["location"],
						'tid':data[x]["tid"]
						}
						)
date1 = input("Question 1 : Enter Date::\n")
list_of_rows = session.execute('select count(*) as count,date,hashtag,location,tid from Q2 where date=\''+date1+'\'group by date,hashtag,location allow filtering')
file2=open("file2.csv","w");
for row in list_of_rows:
	x=str(row.date)+";"+str(row.hashtag)+";"+str(row.location)+";"+str(row.count)+"\n"
	print(str(row.date)+"\t\t\t"+str(row.hashtag)+"\t\t\t"+str(row.location)+"\t\t\t"+str(row.count))
	file2.write(x)