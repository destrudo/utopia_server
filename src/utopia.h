
#include <uuid/uuid.h>

#define MAX_HOSTNAME_LEN 128
#define MAX_ZONE_NAME_LEN 64
#define MAX_DEVICE_REQ_TOPIC_LEN 256
#define MAX_DEVICE_REQ_DATA_LEN 128
#define MAX_DEVICE_REQ_XML_LEN 4096

/* utopia_zone_t structure
 *
 * This holds generic zone data
 */
struct utopia_zone_t {
	char name[MAX_ZONE_NAME_LEN];
	uuid_t uuid;
	uint64_t id;
	uint64_t servers; // Current server count using this zone (Might be unimportant)
};

/* utopia_server_t structure
 *
 * This holds generic server data
 */
struct utopia_server_t {
	char hostname[MAX_HOSTNAME_LEN];

	uuid_t uuid;

	in_addr address;

	uint64_t id; //This is a silly ID that is for nothing more than counting the order which it was created.  It will probably go unused.

	float global_weight; //This should include manual adjustments as well as the default weight.

	float zone_weight;

	utopia_zone_t zone; /* The zone.  Note: in the future we want this to be a list of zones used */

	time_t uptime; /* This has been running since */
};

/* utopia_device_t structure
 *
 * This contains the most basic things for any client which connects and posts to the mqtt broker.
 */
struct utopia_device_t {
	char hostname[MAX_HOSTNAME_LEN];
	uuid_t uuid;
	uint64_t id;
	in_addr address;
	utopia_zone_t zone;
};

/*
 *
 * This contains the rest (for now) client response data.
 */
struct utopia_device_request_t {
	struct utopia_device_t * dev;
	uint64_t id; //This is the ID used by the request.

	int request; //This tells the thing at the other end the status result of the var

	uint16_t reqd; /* This is the request data, each bit will denote data to fill */

	char * topic; /* mqtt topic */
	char * message; /* mqtt message */
	char * xml_data; /* Formatted data */
};


/*
 *
 * This contains the rest (for now) service response data.
 */
struct utopia_server_request_t {
	struct utopia_server_t * srv;
	uint64_t id; //This is the ID used by the request

	int request;

	char * data;
	char * xml_data;

	/* struct utopia_server_stats_t * stats; */ /* We don't wanna use this just yet */
};

/* FIXME, finish later. */
/* Each one of these is in the form of a minute */
struct utopia_server_stats_t {
	double load;

	uint64_t mqtt_requests_in;
	uint64_t mqtt_requests_out;
	uint64_t rest_requests;
	uint64_t zk_requests;

	struct utopia_server_stats_t * next; //The previous minute.
}

