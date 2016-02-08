#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

#include <sys/queue.h>

#include "utopia.h"
#include "mongoose.h"

#define DEFAULT_REST_PORT		"9666"
#define REST_EDL				"yes" /* This enables directory listing, should be disabled in production */
#define REST_AUTH				".htpasswd"

#define DEFAULT_REST_ROOT		"/var/lib/utopiad"

#define CERR(errstr)			fprintf(stderr, "utopia_rest.%s", errstr)

/* We aren't going to use these at first... */
struct r_device_request_tailq_t {
	struct utopia_device_request_t * data;
	TAILQ_ENTRY(r_device_request_tailq_t) entries;
}
struct r_server_request_tailq_t {
	struct utopia_server_request_t * data;
	TAILQ_ENTRY(r_server_request_tailq_t) entries;
}

/* Instead, we'll use these. */
struct utopia_device_request_t * r_devreq;
struct utopia_server_request_t * r_srvreq;

static pthread_mutex_t * r_mutex_dev; /* Device request mutex */
static pthread_mutex_t * r_mutex_srv; /* Server request mutex */

static pthread_mutex_t * r_mutex_answ; /* request response mutex */

static pthread_mutex_t * r_mutex_control; /* Control mutex */

static struct mg_serv_http_opts * http_server_opts;
static char rest_port[6];

static uint64_t r_request_ident = 0; /* This gets added as each of the requests goes into the queue so that when the response comes back, it's to the right place */

int r_service = 0;

static struct mg_mgr * r_manager;
static struct mg_connection * r_connection;


/* Generics required for... things */
int mg_startswith(const struct mg_str *pre, const char *str);

//FIXME, SSL Data needs to get added to this
int r_config(char * hostname, char * rest-root, char * acl,  char * rest_port = DEFAULT_REST_PORT);

static void r_event_handler(struct mg_connection *nc, int ev, void *ev_data);

/* If we get a MG_EV_HTTP_REQUEST, call this */
int r_manage_message(struct mg_connection * nc, int ev, http_message * hm);

int r_set_request_message(struct mg_connection * nc, int ev, http_message * hm);
int r_get_request_message(struct mg_connection * nc, int ev, http_message * hm);

static void r_prepare_device_request_xml(struct utopia_device_request_t * r_l_devreq);
static void r_prepare_server_request_xml(struct utopia_server_request_t * r_l_srvreq);

int r_start();
int r_stop();