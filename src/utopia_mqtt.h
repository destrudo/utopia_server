#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"

//MAX_HOSTNAME_LEN
#define MAX_TOPIC_LEN 512
#define MAX_TYPE_LEN 64
#define MAX_XTOPIC_LEN 128
#define MAX_MESSAGE_LEN 128

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "MQTT Examples"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

/*
 *
 * This is the text only message structure
 */
struct utopia_mqtt_message_tol_t {
    char topic[MAX_TOPIC_LEN];

    uint8_t qos;

    char message[MAX_MESSAGE_LEN];
}

struct utopia_mqtt_message_t {
    char hnid[MAX_HOSTNAME_LEN]; //This is the hostname or uuid converted to characters.
    char zone[MAX_ZONE_NAME_LEN];
    char type[MAX_TYPE_LEN];
    uint64_t id;
    char post_type[]
    char xtopic[MAX_XTOPIC_LEN];

    uint8_t qos;

    char message[MAX_MESSAGE_LEN];
}

struct utopia_mqtt_subscription_t {
    
}


int main(int argc, char* argv[])
{
    MQTTClient client;
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    int rc;

    MQTTClient_create(&client, ADDRESS, CLIENTID,
        MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    pubmsg.payload = PAYLOAD;
    pubmsg.payloadlen = strlen(PAYLOAD);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
    printf("Waiting for up to %d seconds for publication of %s\n"
            "on topic %s for client with ClientID: %s\n",
            (int)(TIMEOUT/1000), PAYLOAD, TOPIC, CLIENTID);
    rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("Message with delivery token %d delivered\n", token);
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}