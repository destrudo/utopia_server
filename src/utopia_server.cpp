#include <stdio.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <sys/select.h>
#include <sys/queue.h>



#include "utopia.h"
#include "utopia_rest.h"

extern pthread_mutex_t * r_mutex_answ;
extern struct r_request_tailq_t * r_request;
// extern TAILQ_HEAD(tailhead, r_request_tailq_t) r_request_head;
struct r_request_head_tq r_request_head;



void usage(char * cmdline)
{
	fprintf(stderr, "%s - utopia daemon\n\n", cmdline);
	fprintf(stderr, "usage:");
	fprintf(stderr, "\tEat and egg.");
	exit(1);
}

int main(int argc, char * argv[])
{
	const char * hostname = "localhost";
	const char * rest_root = "/home/destrudo/Projects/utopia_server/html";
	//char * rest_root = ".";
	pthread_attr_t attr;
	pthread_t rest_thread;
	int attr_ret;
	int garbage = 0;
	struct r_request_t * rest_queue_data;
	int n;
	bool b;
	fd_set readSet;

	
	struct timeval tv = {1, 0};

	TAILQ_INIT(&r_request_head);


	/* call getopts and make sure any flags have been handled */

	/* Load config file, make sure everything is a-ok and populate vars */

	/* Ensure all required keys for the mqtt broker exist */
	/* Ensure all other files can be made or exist */

	/* Fire up management stuff */ /* Should make sure it can bind and all that other nice stuff */
	r_config((char *)hostname, (char *)rest_root, NULL, NULL);
	attr_ret = pthread_attr_init(&attr);
	if (attr_ret != 0)
		exit(2);

	pthread_create(&rest_thread, &attr, rest_start, &garbage);
	//rest_start(&garbage);



	/* If in clustered mode (zookeeper enabled) */
		/* Start up zookeeper */
		/* While not connected */
			/* post data to log mentioning the delay ~once a minute */


	/* Start up database connection thread */
	/* While not connected */
		/* post data to log mentioning the delay ~once a minute */

	/* Start up mqtt thread */
	/* While not connected */
		/* post data to log mentioning the delay ~once a minute */

	/* Start up REST api controller thread */

	/* While true */
	while (1)
	{
		printf("main: In main thread.\n");
		// if (r_mutex_answ == NULL) {
		// 	continue;
		// }

		/* if data in zookeeper */

		/* if data in mqtt */

		/* if data in REST server req queue */ /* Note, this will first be a var */
		//Acquire r_mutex_answ
		if(pthread_mutex_lock(r_mutex_answ)) {
			printf("main: Error acquiring r_mutex_answ.\n");
			continue;
		}
		if (1)
		{
			

			//Answer the request.
			// printf("\nmain: Data inside request: '%s'\n\n", (char *) r_request->data);

			// delete r_request;
			// r_request = NULL;

			//Release r_mutex_answ
		}
		else
		{
			printf("main: r_request is NULL\n");
		}

		if(pthread_mutex_unlock(r_mutex_answ)) {
			printf("main: Error releasing r_mutex_answ.\n");
			continue;
		}

		FD_ZERO(&readSet);
		FD_SET(STDIN_FILENO, &readSet);
		if (select(STDIN_FILENO+1, &readSet, NULL, NULL, &tv) < 0)
			perror("main: select");

		b = (FD_ISSET(STDIN_FILENO, &readSet)) ? (std::cin>>n) : false;

		if (b) {
			if(r_stop()) {
				printf("main: Issue getting lock or unlocking.\n");
				continue;
			}
			printf("main: Ending.\n");
			break;
		}

		sleep(1);
	}

	pthread_join(rest_thread, NULL);

}