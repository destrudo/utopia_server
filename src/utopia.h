
#include <uuid/uuid.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef UTOPIA_H
#define UTOPIA_H

#define MAX_HOSTNAME_LEN 128
#define MAX_ZONE_NAME_LEN 64
#define MAX_DEVICE_REQ_TOPIC_LEN 256
#define MAX_DEVICE_REQ_DATA_LEN 128
#define MAX_DEVICE_REQ_XML_LEN 4096


enum template_classification {
	SENSOR_ENTRY, 	/* Ex "Neopixel" */
	SENSOR_CLASS, 	/* Ex "RGB Led", which might be part of SENSOR_ENTRY */
	DEVICE_CLASS, 	/* Ex identification-level formatting for devices, which may include things that do not contain DEVICE_DATA template data. */
	DEVICE_DATA, 	/* Client data (Extension of DEVICE_CLASS) */
	SERVER_DATA,	/* Unique, only applies to utopia server template data for formatting */
};

/* These have nothing to do with control, these are simply for templates and ease-of-classification */
enum part_classification {
	NOT_INIT,
	/* Start with the outputs */
	/* LED/light stuff */
	LED,
	PWM_LED, /* pwm outputs */
	PWM_RGB_LED,

	/* Relay */
	RELAY,
	SSRELAY, /* If you want to pulse a solid state one */

	/* Speaker */
	SPEAKER, /* More likely, a buzzer */

	/* INPUT types */
	ANALOG_SENSOR, /* Generic analog sensor */
	PHOTOSENSOR,
	GPS,
	ACCELEROMETER,

	/* Bidirectional stuff (MUST CONTAIN THE SAME DATA IN BOTH DIRECTIONS!!!!) */
	B_PWM_RGB_LED, /* Neopixels fall into this category */
};

/* FIXME, do we need a translator method for the above enum? */


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

/*
 *
 * Parts are sensors and lights and speakers, things that are 'input' and 'output' that devices need to provide information to us.
 */
struct utopia_part_t {
	std::string name; /* Name must correspond to a created template */
	int id; /* Part ID, should just increment */
	//int part_class;
	enum part_classification part_class;
	utopia_part_t ** children;
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

	std::string * topic; /* mqtt topic */
	std::string * message; /* mqtt message */
	std::string * xml_data; /* Formatted data */
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
};

/*
 * This method will return a string containing the path to the template
 *
 */
// std::string get_template(std::string * name, int classification)
// {

// }

/* Returns bool value based on whether or not the name 'name' has an XML template that can be filled.
 */
// static bool request_has_template(std::string * name, int classification)
// {

// }

// /*
//  *
//  * This method accepts a db entry and fills an XML string from a valid document.
//  *  It then populates str with the completed data.
//  *
//  * returns negative when fail, 0 when ok, greater than zero for each entry that could not be classified
//  */
// static int prepare_device_request_data(std::string * name, int classification, std::string * json_in, std::string * xml_out)
// {
// 	/* Open template */
// }

// /*
//  * 
//  * Does the same as above, but for server-specific db data that has an XML template.
//  */
// static int prepare_server_request_data(std::string * name, int classification, std::string * json_in, std::string * xml_out)
// {

// }


// /* FIXME, confirm if necessary
//  *
//  * Prepares completed XML template from mqtt data 
//  */
// static int prepare_xml_data_from_mqtt_device(utopia_device_request_t * in, std::string * xml_out)
// {

// }

#endif /* UTOPIA_H */