#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mongoose.h"


int mg_startswith(const struct mg_str *pre, const char *str)
{
	return strlen(str) < pre->len ? 0 : strncmp(pre->p, str->p, pre->len) == 0;
}

int r_config(char * hostname, char * rest-root, char * acl, char * rest_port_i = DEFAULT_REST_PORT)
{
	/* Allocate the server option stuff */
	http_server_opts = (mg_serv_http_opts*)calloc(1, sizeof(mg_serv_http_opts));
	
	/* And our lovely mutext */
	r_mutex_dev = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));
	r_mutex_srv = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));
	r_mutex_answ = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));
	r_mutex_control = (pthread_mutex_t*)calloc(1, sizeof(pthread_mutex_t));

	r_manager = (mg_mgr *)calloc(1, sizeof(mg_mgr));

	if (rest_port == NULL)
	{
		CERR("config(), rest_port");
		return -1;
	}

	if (rest-root == NULL)
		http_server_opts->document_root = DEFAULT_REST_PORT;
	else
		http_server_opts->document_root = rest-root;

	if (hostname == NULL)
		http_server_opts->auth_domain = "DILLY"; //FIXME
	else
		http_server_opts->hostname;

	if (acl)
		http_server_opts->ip_acl = acl;

	http_server_opts->enable_directory_listing = REST_EDL; //FIXME, change in the future.

	/* Prime the connection */
	r_connection = mg_bind(r_manager, rest_port_i, r_event_handler);

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

	if (r_devreq->request <= 0)
	{
		/* Post bad data response */
	}
	else
	{
		/* Post data response */
	}

	/* Release r_mutex_answ */

	free(r_devreq);
	r_devreq = NULL;

	/* Release the device request semaphore */
	return 0;
}

int r_get_request_message(struct mg_connection * nc, int ev, http_message * hm)
{

}

int r_manage_message(struct mg_connection * nc, int ev, http_message * hm)
{
	if (mg_startswith(&hm->uri, "/api/v1/get/"))
	{
		/* Dump data from devices that comply with the name following the get/ */
		r_get_request_message(nc, ev, hm);
	}
	else if (mg_startswith(&hm->uri, "/api/v1/set/"))
	{
		/* Send command  to devices that comply with the name following the set/ */
		r_set_request_message(nc, ev, hm);
	}
	else if (mg_startswith(&hm->uri, "/api/v1/server"))
	{
		/* Server specific command message */
		r_server_message(nc, ev, hm);
	}
	else
	{
		/* Serve static content [whatever it may be.] */
		mg_serve_http(nc, hm, s_http_server_opts);
	}

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

int r_start()
{
	r_service = 1;

	while (r_service > 0)
	{
		if(pthread_mutex_lock(r_mutex_control)) {
			CERR(".start() thread mutex lock failed.");
			return -1;
		}

		mg_mgr_poll(&mgr, 1000);

		if(pthread_mutex_lock(r_mutex_control)) {
			CERR(".start() thread mutex unlock failed.");
			return -2;
		}
	}

	/* I don't think we'll need this, keeping it as disabled for now */
	/*
	pthread_mutex_unlock(r_mutex_control);
	*/

	mg_mgr_free(&mgr);
}

int r_stop()
{
	if(pthread_mutex_lock(r_mutex_control)) {
		CERR(".stop() mutex lock failed.");
		return -1;
	}

	r_service = 0;

	if(pthread_mutex_unlock(r_mutex_control)) {
		CERR(".stop() mutex unlock failed.");
		return -2;
	}
}