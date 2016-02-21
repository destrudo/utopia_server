#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"
#include "utopia.h"
#include "utopia_mqtt.h"

/*
 *
 *
 */
int mqtt_thread(utopia_server_t * localsrv, int * pipe_mqtt_in, int * pipe_mqtt_out, int * pipe_command_in, int * pipe_command_out) //We need more options!
{
	int threadStop = 0; //This will obviously need to change to something that mqtt_thread_stop can control.
	int poll_rdy;
	struct pollfd *poll_mqtt_fd, * poll_cmd_fd;
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_message publisher = MQTTClient_message_initializer;

	/* We're making this dynamic alloc so that in the future it'll be easy to allow for multiple pipes */
	poll_mqtt_fd = calloc(1, sizeof(struct pollfd));
	poll_cmd_fd = calloc(1, sizeof(struct pollfd));

	MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

	poll_mqtt_fd->fd = *pipe_mqtt_in;
	poll_mqtt_fd->events = POLLIN;

	poll_cmd_fd->fd = *pipe_cmd_in;
	poll_cmd_fd->events = POLLIN;

	if (poll_fd == NULL)
	{
		fprintf(stderr, "utopia_mqtt.mqtt_thread, failed to allocate poll_fd\n");
		exit(-1);
	}

	while (!threadStop)
	{
		/* Command pipe in */
		poll_rdy = poll(poll_cmd_fd, 1, POLL_WAIT);
		if (poll_rdy < 0)
		{
			fprintf(stderr, "utopia_mqtt.mqtt_thread, failed to poll command pipe\n");
			exit(-2);
		}

//This needs to:
		//Regularly ping the parent so that it knows its alive (If not parent will kill and restart)
		//Shutdown self
		//Force reconnect
		if (poll_cmd_fd->revents & POLLIN)
		{
			//Perform operation in response to new command message from the parent
		}

//This needs to be able to:
		//Subscribe to new clients
		//Subscribe to zone
		//Subscribe to server (hostname/uuid)
		//Subscribe to everything (With special handler) **If possible!

		//publish arbitrary data to arbitrary topic

		/* Data pipe in */
		poll_rdy = poll(poll_mqtt_fd, 1, POLL_WAIT);
		if (poll_rdy < 0)
		{
			/* We need a way nicer way to handle a failure of the core pipe */
			fprintf(stderr, "utopia_mqtt.mqtt_thread, failed to poll mqtt pipe\n");
			exit(-2);
		}

		if (poll_mqtt_fd->revents & POLLIN)
		{
			//Perform operations in response to a new mqtt message from the parent
		}


//

	}
}

/*
 *
 * Starts the mqtt thread
 */
int mqtt_thread_start(utopia_server_t * localsrv)
{
	int pipe_mqtt_in[2], pipe_mqtt_out[2], pipe_cmd_in[2], pipe_cmd_out[2];
	pid_t threadpid;

	pipe(pipe_mqtt_in);
	pipe(pipe_mqtt_out);
	pipe(pipe_cmd_in); /* I don't really think we need or should want these extra pipes since we need to perform checks anyways */
	pipe(pipe_cmd_out);

	

}

/*
 *
 * Stops the mqtt thread
 */
int mqtt_thread_stop()
{

}

int mqtt_message_handler(void *context, char *topicName, int topicLen, MQTTClient_message *message)
{

}

/*
 *
 * Sends a utopia style message from the thread
 */
int mqtt_thread_send(utopia_mqtt_message_t * msg)
{

}

/* 
 *
 * Sends a text only message from the thread
 */
int mqtt_thread_send_tol(utopia_mqtt_message_tol_t * msg)
{

}


/*
 *
 * Retrieves a utopia style message from the mqtt thread
 */
int mqtt_thread_receive(utopia_mqtt_message_t * msg)
{

}

/*
 *
 * Retrieves a text only message from the mqtt thread
 */
int mqtt_thread_receive_tol(utopia_mqtt_message_tol_t * msg)
{
	
}





/*
 *
 * Add a server subscription to our mqtt thread.
 */
int server_subscription_add(utopia_server_t * srv)
{

}

/*
 *
 * modify a server subscription to our mqtt thread.
 */
int server_subscription_modify(utopia_server_t * osrv, utopia_server_t * nsrv)
{

}

/*
 *
 * remove a server subscription from our mqtt thread.
 */
int server_subscription_remove(utopia_server_t * srv)
{

}


/*
 *
 * Add a device subscription to our mqtt thread.
 */
int device_subscription_add(utopia_device_t * device)
{

}

/*
 *
 * modify a device subscription to our mqtt thread.
 */
int device_subscription_modify(utopia_device_t * odevice, utopia_device_t * ndevice)
{
	
}


/*
 *
 * Remove a device subscription from our mqtt thread.
 */
int device_subscription_remove(utopia_device_t * device)
{
	
}