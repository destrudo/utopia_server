SPEC.md

#db structure (Must be nosql due to the complexity and variability of device data)

	#devices
		# host 			(string)
		# unique id 	(32 bit integer or uuid in string form)
		# device class	(Device class)
		# topic focus	(topic path to the device itself, usually something like `/hostname/uuid/class`)
		# device zone	(Zone used by the device.  Usually the AP for wireless devices, the last router in a traceroute or the vlan)
		# data 			(Don't care what goes into here.  Could be a single integer, could be some detailed tree of data.)
		# stats			(Point to stats row)

	#zones
		# zone id
		# nodes			(list/hash of nodes in this zone)


	#fellows [other utopia servers]
		# host
		# unique id
		# active
		# lastactive 		(timestamp)
		# state 			(master/slave)
		# stats

	#stats
		# id 				(unique id as in devices/fellows.)
		# type				(Type for this stats row, type+id should equal a unique pair)
		# today attempts
		# daily attempts	(Average daily attempts)
		# weekly attempts	(Average weekly attempts)
		# monthly attempts	(Average monthly attempts)
		# yearly attempts	(Averate yearly attempts)

		# today failures
		# daily failures	(avg daily failures)
		# weekly failures
		# monthly failures
		# yearly failures


#Libraries to utilize
	-Mongodb, storing data
	-Zookeeper, controlling server handling of events

https://docs.mongodb.org/master/MongoDB-data-models-guide-master.pdf
https://zookeeper.apache.org/doc/r3.5.1-alpha/zookeeperOver.html
https://zookeeper.apache.org/doc/r3.4.6/zookeeperProgrammers.html
http://www.eclipse.org/paho/files/mqttdoc/Cclient/