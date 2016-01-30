
#include <uuid/uuid.h>

#define MAX_HOSTNAME_LEN 128
#define MAX_ZONE_NAME_LEN 64

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
}

