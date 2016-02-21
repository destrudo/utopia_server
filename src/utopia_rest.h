#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/queue.h>
#include <pthread.h>

#include <string>
#include <vector>


#include "utopia.h"
#include <mongoose.h>

#ifndef UTOPIA_REST_H
#define UTOPIA_REST_H


#define DEFAULT_REST_PORT		"9666"
#define REST_EDL				"yes" /* This enables directory listing, should be disabled in production */
#define REST_AUTH				".htpasswd"

#define DEFAULT_REST_ROOT		"."

#define URCERR(errstr)			fprintf(stderr, "ERROR: utopia_rest.%s\n", errstr)

enum request_type { NONE, DEVICE, SERVER };

/* We aren't going to use these at first... */
struct r_device_request_tailq_t {
	struct utopia_device_request_t * data;
	TAILQ_ENTRY(r_device_request_tailq_t) entries;
};

struct r_server_request_tailq_t {
	struct utopia_server_request_t * data;
	TAILQ_ENTRY(r_server_request_tailq_t) entries;
};

/* Instead, we'll use this. */
struct r_request_t {
	enum request_type type;
	struct utopia_device_request_t * r_devreq;
	struct utopia_server_request_t * r_srvreq;
};



struct utopia_rest_part_t {
	utopia_part_t part;
	std::string url; /* part's relative URL */
};

struct utopia_device_rest_t {
	std::string root; /* This is the device's root path [ideally 'api/(devicehostname|deviceuuid)' */
	std::vector<utopia_rest_part_t> parts; /* Set of all of the parts and by design, the url's for em' */
};

struct utopia_rest_thread_t {
	pthread_t thread_id;
	int       thread_num;
};

static pthread_mutex_t * r_mutex_dev; /* Device request mutex */
static pthread_mutex_t * r_mutex_srv; /* Server request mutex */

static pthread_mutex_t * r_mutex_answ; /* request response mutex */

static pthread_mutex_t * r_mutex_control; /* Control mutex */

static struct r_request_t * r_request;

static struct mg_serve_http_opts * http_server_opts;
static char rest_port[6];

static uint64_t r_request_ident = 0; /* This gets added as each of the requests goes into the queue so that when the response comes back, it's to the right place */

static int r_service = 0;

static struct mg_mgr * r_manager;
static struct mg_connection * r_connection;

/* This method should take an xml node or in-place memory xml, and output formatted html */
int prepare_html_from_xml(const char *xmlin, const char *htmlout);

/* Generics required for... things */
int mg_startswith(const struct mg_str *pre, const char *str);

//FIXME, SSL Data needs to get added to this
int r_config(char * hostname, char * rest_root, char * acl,  char * rest_port);

static void r_event_handler(struct mg_connection *nc, int ev, void *ev_data);

/* If we get a MG_EV_HTTP_REQUEST, call this */
int r_manage_message(struct mg_connection * nc, int ev, http_message * hm);

int r_set_request_message(struct mg_connection * nc, int ev, http_message * hm);
int r_get_request_message(struct mg_connection * nc, int ev, http_message * hm);

static void r_prepare_device_request_xml(struct utopia_device_request_t * r_l_devreq);
static void r_prepare_server_request_xml(struct utopia_server_request_t * r_l_srvreq);

/* This needs to be an extern to talk to pthread_create. */
extern void * rest_start(void * arg);

int r_stop();

#endif /* UTOPIA_REST_H */