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
int mqtt_thread(utopia_server_t * localsrv, int pipe_in, int pipe_out) //We need more options!
{
	int threadStop = 0; //This will obviously need to change to something that mqtt_thread_stop can control.
	int poll_rdy;
	struct pollfd *poll_fd;
	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	MQTTClient_message publisher = MQTTClient_message_initializer;

	/* We're making this dynamic alloc so that in the future it'll be easy to allow for multiple pipes */
	poll_fd = calloc(1, sizeof(struct pollfd));

	MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

	poll_fd.fd = pipe_in;
	poll_fd.events = POLLIN;

	if (poll_fd == NULL)
	{
		fprintf(stderr, "utopia_mqtt.mqtt_thread, failed to allocate poll_fd\n");
		exit(-1);
	}

	while (!threadStop)
	{
		poll_rdy = poll(poll_fd, 1, POLL_WAIT);
		if (poll_rdy < 0)
		{
			/* We need a way nicer way to handle a failure of the core pipe */
			fprintf(stderr, "utopia_mqtt.mqtt_thread, failed to poll pipe\n");
			exit(-2);
		}


	}
}

/*
 *
 * Starts the mqtt thread
 */
int mqtt_thread_start(utopia_server_t * localsrv)
{

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