SPEC.md

#db structure (Must be nosql due to the complexity and variability of device data)

	#devices
		# host 			(string)
		# unique id 	(32 bit integer or uuid in string form)
		# device class	(Device class)
		# topic focus	(topic path to the device itself, usually something like `/hostname/uuid/class`)
		# device zone	(Zone used by the device.  Usually the AP for wireless devices, the last router in a traceroute or the vlan)
		# data 			(Don't care what goes into here.  Could be a single integer, could be some detailed tree of data.)
		# commands		(Commands sent to this device)
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

	#nosql servers [directory of servers ever used.]
		#

	#stats
		# id 				(unique id as in devices/fellows.)
		# type				(Type for this stats row, type+id should equal a unique pair)
		# used				(This should be a list of use timestamps)
			#timestamp  	(unix epoch)
			#command 		(Paired to devices table entry)

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

#Zookeeper requirements
	#Manageable server weight
	#Zone weight when selecting responder
	#Should be able to provide string data to the clients (Passing the ip of new fellows or db locations)



#Server requirements
	#configuration:
		#Needs to support dynamic architecture data for devices via xml "configs"
		#The server daemon should regularly check for new files, update valid ones and disregard invalid ones.
		#The XML for the configs must follow predefined xml schema's

		#Base configuration should use libconfig.  The base config should be limited to core things such as permissions, base directory paths
		*Note, all things noted/applied in the faux config file in /etc/utopiad.conf are required.

		#Zookeeper should not be required for execution based on the local configuration (/etc/utopia/utopiad.conf)
		#If ZK is enabled, the user should be able to configure multiple "Core" servers in a list so that if one is down, they can still access all data.

	#Operation
		#Database access
			# DB access libs should be modular enough to support multiple nosql types without too much effort.  Compilation controls to switch different db types on and off will be required.
			# Provided that the service can talk to the zookeeper clients, it should be able to send out a request for a list of currently active db servers.


		#Zookeeper
			#Should not be required, compilation controls to not compile it would be ideal.
			# Need to be able to acquire from the other zookeeper clients (Directly or from the server)
			  #MQTT specific
				#Hostnames/ip's of all other utopia servers
				#unique identifiers for the mqtt subscription to use
				*After confirming the above data, it can move to the `#MQTT utopia server specific` stuff

			  #DB specific
				#

			#Certain commands will need to be acknowledged through the zookeeper cluster

		#MQTT
			# We will want to support a minimum of two MQTT bridges so that we can have one for the server and another for client operations

			#MQTT utopia server specific (Transferrence data so that we can send more detailed messages to the server without bogging down zookeeper.)
				***It is required that the MQTT portion of Zookeeper be handled already before these subscriptions will occur.
				#After data from zookeeper acquired, a few subs will occur for each unique utopia_server (QoS 2):
					/${clustername}/${hostname} # This is the default-to-use path, however if the correct server is not acknowledging messages, it will fallback to...
					/${clustername}/${unique_id} # The fallback path (A much more unique UUID based construct)


			#Immediate subscription data
				#For every unique server using the zookeeper service
			#MQTT Response data (Data to be sent per a previous request over mqtt)

			#Service reponse data (Data to be sent per a previous request over $x), where $x is a service, a client, or some other such software that can perform an action against a utipia server instance