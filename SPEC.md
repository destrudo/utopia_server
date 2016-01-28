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

	#xmlconfigurations [XML uploaded during a volatile configuration refresh which contained new data]
		# name
		# type 				(Config | schema)
		# hash
		# version
		# data 				(Actual XML data)

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

#MQTT broker requirements:
	#Must support 3.1 nice big pretty SSL bridging (Like mosquitto)




#Server requirements
	#configuration:
		#Needs to support dynamic architecture data for devices via xml "configs"
		#The server daemon should regularly check for new files, update valid ones and disregard invalid ones.
		#The XML for the configs must follow predefined xml schema's

		#Base configuration should use libconfig.  The base config should be limited to core things such as permissions, base directory paths
		*Note, all things noted/applied in the faux config file in /etc/utopiad.conf are required.

		#Zookeeper should not be required for execution based on the local configuration (/etc/utopia/utopiad.conf)
		#If ZK is enabled, the user should be able to configure multiple "Core" servers in a list so that if one is down, they can still access all data.

	#Operational guidelines
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
				#MQTT server hostname/ip and port pairs which are valid to the networked data

			  #DB specific
				#Hostname/ip of currently-known-as-alive db servers in a set with the port number and db type (eg. 10.0.0.3:12345:mongodb)

			#Certain mqtt commands will need to be acknowledged through the zookeeper cluster
			# The zookeeper service should be able to manage server weights based on:
				# Manual weighting
				# current load
				# zone information
				# configuration weighting (Separate from current load and zone information weighting), this is used to determine which configuration to apply if there have been multiple updates on the same version/device class across multiple servers.

		#MQTT
			#Topic layout:

				/${hostname|uuid}/${zone}/${type}/${id}/${post_type}/${data}
					# ${type} defines the kind of device it is.
					# ${id}, might not be applicable to most devices, but cannot be ignored.  A good example of software that uses it is `py_aumh`, since it can interface with more than one arduino_uart_mh device per service
					# ${post_type} defines what sort of data it's publishing.  This part of the topic is directly aligned to the xml configuration data, so the names should be consistent.
						#If the post_type is unknown, the service should be able to populate a nosql entry by dropping each piece of ${data}/* as a dictionary-like thing.

					# ${data} denotes whatever data is there. this is extremely device specific.  Everything above ${post_type} is considered device data
				

			# We will want to support a minimum of two MQTT bridges so that we can have one for the server and another for client operations (By design, they'd be on separate servers)

			# Those bridges must support SSL (Certain clients will only support SSL, but it should support ALL FORMS of authentication (Even none!) )

			#MQTT utopia server specific (Transferrence data so that we can send more detailed messages to the server without bogging down zookeeper.)
				***It is required that the MQTT portion of Zookeeper be handled already before these subscriptions will occur.
				#After data from zookeeper acquired, a few subs will occur for each unique utopia_server (QoS 2):
					/${clustername}/${remoteServerHostname}/${utopia_server_hostname}/recv # This is the default-to-use path, however if the correct server is not acknowledging messages, it will fallback to...
					/${clustername}/${remoteServerUnique_id}/${utopia_server_unique_id}/recv # The fallback path (A much more unique UUID based construct)
					# Where the utopia_server_X is the CURRENT RUNNING utopia server daemon's hostname/unique_id.

					#Note: When the local utopia server publishes, it will push out to /clustername/remotserverwhatever/mywhatever/send, with an extended topic that will of course vary


				#Immediate subscription data (After the service starts successfully and contacts the mqtt service server bridge, it will sub to these)
					/${clustername}/${utopia_server_hostname} # Where utopia_server_X is the CURRENT RUNNING utopia server daemon's data.
					/${clustername}/${utopia_server_unique_id}

				#The immediately above two combined allow for the local server sort out the source of a request or new data, as well as send data to the appropriate place.




			#MQTT Response data (Data to be sent per a previous (subbed) request over mqtt)

			#Service reponse data (Data to be sent per a previous request over $x), where $x is a service, a client, or some other such software that can perform an action against a utipia server instance

			#MQTT subscription data
				#Previously subscribed data point (This is a device already known to the server, to which the server is currently subscribed to the root of this device)
					#If we don't have a topic hash
						#generate topic hash (sha-something big and unique)

					#If we intend to respond to it
						#Send a zookeeper message (This hash) in order to determine which server will respond

					#wait for zookeeper to tell us which server is going to respond

					#If we're not going to respond
						#stop the thread

					#Update database data

					#If response required
						#prepare response message (However required)
						#send response message

				#Zone subscription data (New device in zone sub!)
					#Generate topic hash
					#Send request to zookeeper (this hash) in order to determine which server will respond
					#Create new DB entry with device type
					#Goto `previously subscribed data point` methods above.



				#When Utopia server 'opts' to subscribe to a post point root

		#Volatile configuration synchronization
			#If a server performs a configuration update and realizes it has a new config, it should automatically push it out to the DB
				Process:
					#send updated config message with XML version tag and type

					#Wait for other cluster members see if they get the same tag/type pair

					#If they do, extend tag/type to hash of raw xml

					#If others are getting different hash values, the one with the highest `configuration weight` wins (NEed to include the ratio of changing systems with the matching hash).  All the ones with nonmatching hashes will be replacing their configuration/schema files in the next few steps

					#The others will enter a polling state on the zookeeper server, waiting for the update to occur (hash will still need to be stored as a var until validation complete)

					#Create a new db xmlconfiguration entry containing the raw data, the hash, the version, the config type, and the name

					#Issue update command to the cluster
						#all other systems will then grab the data from the DB
						#They will perform a hash on the raw entry data
						#if nonmatching config
							#Warning to log
							#Wait and try again (Max loop time needs to be set)
							#On total failure (All loops return bad hash), the service needs to mark all responses to this type of service as "to be ignored", and set an additional warning over zookeeper, as well as another local log entry (Since it's likely a seriously failing system, or the local DB is having some horrible issue)

							#System which set this in motion should attempt to connect to that db server, and read the data off of it.
							#If it can connect
								# Needs to get the entry
								# If the hash matches
									# Issue a clean restart to the service which failed
								# if it does not
									# attempt to write the correct data to that server and then verify.
									# if verification fails
										# DB gets tagged as problematic, message should go out to all servers which states that it should not use that DB for now (DB will need to be manually re-added to the db table)
									# else
										# All good, restart service which failed
							#if it can't connect
								#Issue warning about what happened in local log

						#if matching config
							#good, update and be done.
					