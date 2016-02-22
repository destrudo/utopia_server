#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/queue.h>


#include <string>
#include <vector>

#include <mongoose.h>
#include "utopia.h"
#include "utopia_rest.h"

/* Global carryovers. Nuke in the future by making r_config() take initialized queues and mutexes. */
pthread_mutex_t * r_mutex_answ;
// struct r_request_tailq_t * r_request; /* This needs to go away. */
struct r_request_head_tq r_request_head_head;

/* MONGOOSE DEBUG METHODS */
static void http_message_debug(struct http_message *hm, char * source) {
  printf("##############################DEBUG################################\n");
  printf("Source: %s", source);
  if (hm->message.p != NULL)
    printf("\n\nhm->message = '%s'\n\n", (const char *)hm->message.p);
  if (hm->uri.p != NULL)
    printf("\n\nhm->uri = '%s'\n\n", (const char *)hm->uri.p);
  if (hm->method.p != NULL)
    printf("\n\nhm->method = '%s'\n\n", (const char *)hm->method.p);
  if (hm->body.p != NULL)
    printf("\n\nhm->body = '%s'\n\n", (const char *)hm->body.p);
  if (hm->proto.p != NULL)
    printf("\n\nhm->proto = '%s'\n\n", (const char *)hm->proto.p);
  if (hm->query_string.p != NULL)
    printf("\n\nhm->query_string = '%s'\n\n", (const char *)hm->query_string.p);
  printf("###################################################################\n");
}



int mg_startswith(const struct mg_str *pre, const char *str)
{
	printf("startswith: mg_str len: %lu, data: '%s'\n", pre->len, (char *)pre->p);
	return strlen(str) > pre->len ? 0 : strncmp(pre->p, str, pre->len) == 0;
}

int r_config(char * hostname, char * rest_root, char * acl, char * rest_port)
{
	/* Allocate the server option stuff */
	//http_server_opts = (mg_serve_http_opts*)calloc(1, sizeof(mg_serve_http_opts));
	http_server_opts = new mg_serve_http_opts;
	
	// r_request = NULL;

	/* And our lovely mutexs */
	//r_mutex_dev = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));
	//r_mutex_srv = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));
	// r_mutex_answ = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));
	// r_mutex_control = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));
	r_mutex_answ = new pthread_mutex_t;
	r_mutex_control = new pthread_mutex_t;
	pthread_mutex_init(r_mutex_answ, NULL);
	pthread_mutex_init(r_mutex_control, NULL);


	//r_manager = (mg_mgr *)calloc(1, sizeof(mg_mgr));
	r_manager = new mg_mgr;

	mg_mgr_init(r_manager, NULL);


	if (rest_port == NULL)
	{
		rest_port = new char[sizeof(DEFAULT_REST_PORT) + 1];
		strncpy(rest_port,DEFAULT_REST_PORT, sizeof(DEFAULT_REST_PORT));
	}

	if (rest_root == NULL)
		http_server_opts->document_root = DEFAULT_REST_PORT;
	else
		http_server_opts->document_root = rest_root;

	if (hostname == NULL)
		http_server_opts->auth_domain = "localhost"; //FIXME
	else
		http_server_opts->auth_domain = hostname;

	if (acl)
		http_server_opts->ip_acl = acl;

	http_server_opts->enable_directory_listing = REST_EDL; //FIXME, change in the future.

	/* Prime the connection */
	r_connection = mg_bind(r_manager, rest_port, r_event_handler);
	mg_set_protocol_http_websocket(r_connection);

	return 0;
}

int r_server_message(struct mg_connection * nc, int ev, http_message * hm)
{
/* supported commands */
	//List known utopia servers
	//List known mqtt servers
	//List known db servers
	//Dump settings
	//Get specific settings
	//Export statistics


	return 0;
}

int r_set_request_message(struct mg_connection * nc, int ev, http_message * hm)
{
	/* Generate a utopia_device_request_t with a unique id for this device */

	/* Acquire the device request semaphore */

	/* set r_devreq to it */


	/* Attempt to acquire the r_mutex_answ mutex */

	// if (r_request->r_devreq->request <= 0)
	// {
		/* Post bad data response */
	// }
	// else
	// {
		/* Post data response */
	// }

	/* Release r_mutex_answ */

	// free(r_request->r_devreq);
	// r_request->r_devreq = NULL;

	/* Release the device request semaphore */
	return 0;
}

int r_get_request_message(struct mg_connection * nc, int ev, http_message * hm)
{

}

int r_manage_message(struct mg_connection * nc, int ev, http_message * hm)
{
	bool done = false;

	printf("rmm: entered.\n");
	/* Just for a little good measure, we wanna support device and dev */
	/* This is for REST devices (Devices that use REST to communicate.) */
	if ( (mg_startswith(&hm->uri, "/api/v1/dev/")) || (mg_startswith(&hm->uri, "/api/v1/device/")) )
	{
		printf("rmm: startswith /api/v1/dev\n");
		/* Dump data from devices that comply with the name following the get/ */
		// r_get_request_message(nc, ev, hm);
	}
	/* Server to server rest data */
	else if (mg_startswith(&hm->uri, "/api/v1/server/"))
	{
		printf("rmm: startswith /api/v1/server\n");
		/* Server specific command message */
		// r_server_message(nc, ev, hm);
	}
	/* Client interface requests */
	else if (mg_startswith(&hm->uri, "api/v1/client/"))
	{

	}
	else
	{
		while(!done) {
			printf("rmm: in rmm loop.\n");
			/* Serve static content [whatever it may be.] */

			/* WE SHOULD DO A TRY-TO-ACQUIRE HERE */

			if(pthread_mutex_lock(r_mutex_answ)) {
				URCERR(".rmm() mutex lock failed.");
				return -1;
			}

			/* This is wrong, but it's funny. */
			if (1) {
				printf("r_request not null.\n");
				fflush(stdout);
				sleep(1);
				if(pthread_mutex_unlock(r_mutex_answ)) {
					URCERR(".rmm() mutex unlock notnull failed.");
					return -1;
				}

				continue;
			}

			printf("rmm: ALLOCATING!\n");
			// r_request = new r_request_t;
			// r_request->type = SERVER;
			// r_request->data = hm->message.p;
			// printf("rmm: data set: '%s'\n", r_request->data);


			if(pthread_mutex_unlock(r_mutex_answ)) {
				URCERR(".rmm() mutex unlock failed.");
				return -1;
			}

			done = true;

			mg_serve_http(nc, hm, *http_server_opts);
		}

	}

	//mg_serve_http(nc, hm, *http_server_opts);

	return 0;
}

static void r_event_handler(struct mg_connection *nc, int ev, void *ev_data)
{
	struct http_message * hm = (struct http_message *) ev_data;

	switch(ev)
	{
		case MG_EV_HTTP_REQUEST:
			r_manage_message(nc, ev, hm);
		 break;

		default:
			printf("Unknown message.\n");
		 break;
	}
}

/* 
 * 
 * Converts raw data that hasn't yet been formatted to XML
 */
static void r_prepare_device_request_xml(struct utopia_device_request_t * r_l_devreq)
{

}

/* 
 * 
 * Converts raw data that hasn't yet been formatted to XML
 */
static void r_prepare_server_request_xml(struct utopia_server_request_t * r_l_srvreq)
{

}

extern void * rest_start(void * arg)
{
	int * garbage = (int *)arg;
	r_service = 1;

	printf("Started.\n");

	while (r_service > 0)
	{
		printf("Started loop.\n");
		if(pthread_mutex_lock(r_mutex_control)) {
			URCERR(".start() thread mutex lock failed.");
			return NULL;
		}

		mg_mgr_poll(r_manager, 1000);
		//sleep(1);

		if(pthread_mutex_unlock(r_mutex_control)) {
			URCERR(".start() thread mutex unlock failed.");
			return NULL;
		}
		printf("Finished loop.\n");

		/* This is used to offset the time between unlocking and locking for much faster response. */
		sleep(0.5);
	}

	mg_mgr_free(r_manager);


	URCERR(".start() stopped!");

	return NULL;
}

int r_stop()
{
	printf("**STOP() CALLED**\n");
	if(pthread_mutex_lock(r_mutex_control)) {
		URCERR(".stop() mutex lock failed.");
		return -1;
	}
	printf("**STOP() LOCKED r_mutex_control**\n");

	r_service = 0;

	printf("**STOP() SET r_service**\n");

	if(pthread_mutex_unlock(r_mutex_control)) {
		URCERR(".stop() mutex unlock failed.");
		return -2;
	}

	printf("**STOP() UNLOCKED r_mutex_control**\n");
}



/* NEW STUFF */

/*
 *
 * This takes an XML tree and formats the data out to pretty html (With applicable JS to make calls)
 */
// int xml_node_to_html(xml_node * node, std::string & html_out)
// {
	// html_out = xml_node_to_html_traverse(node);

	/* Print debug here */
// }

/* FIXME, consider adding nice lil defs for all of this stuff, it kinda looks nasty.
 *
 * This is the actual recursive traversal stuff for xml_node_to_html
 */
// static std::string xml_node_to_html_traverse(xml_node * node)
// {
	// std::string lbuf;

	// lbuf += "<div ";

	//for attribute data in node
		// if attribute data applicable to html
			// Add attribute data
			// lbuf += attributename + "=\"" + attributevalue + "\" ";

	// lbuf += ">"; //End the div.

/* I THINK THIS SHOULD BE AN EITHER/OR THING.  Don't think entries with text data can have child elements! */
	// for children in node
		//lbuf += xml_node_to_html_traverse(child)

	//if text data in node
	// lbuf += "<p>" + textelementdata + "</p>\n";

	// lbuf += "</div>\n";
// }

/* FIXME, don't know if we need this, we haven't even decided on what it'd look like in the templates.
 *
 * Fill out an existing XML entry's js `formatting url` entry to a valid url for making a rest request.
 */
static std::string xml_entry_js_url_expansion(utopia_device_t * data, std::string & relative_root, std::string & js_in)
{
	// if js_in does not have a valid formatting entry we can replace
		// return js_in; /* We don't need to do a thing */

	// for each formatting_entry
	// 	if formatting_entry == ""
}


static int populate_rest_part(utopia_rest_part_t & part)
{
	/* IF we want to care about overwriting the part url that might have been set in the past, add it here. */

	// part.url = part.part.name + "/" + std::string(part.part.id);
}