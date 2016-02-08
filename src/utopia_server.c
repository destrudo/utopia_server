#include "utopia.h"

void usage(char * cmdline)
{
	fprintf(stderr, "%s - utopia daemon\n\n", cmdline);
	fprintf(stderr, "usage:");
	fprintf(stderr, "\tEat and egg.");
}

int main(int argc, char * argv[])
{

	/* call getopts and make sure any flags have been handled */

	/* Load config file, make sure everything is a-ok and populate vars */

	/* Ensure all required keys for the mqtt broker exist */
	/* Ensure all other files can be made or exist */

	/* Fire up management stuff */ /* Should make sure it can bind and all that other nice stuff */


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
		/* if data in zookeeper */

		/* if data in mqtt */

		/* If data in REST device req queue */ /* Note, this will first be a var */
		if (r_devreq != NULL)
		{
			//Acquire r_mutex_answ
			//Answer the request.
			//Release r_mutex_answ
		}

		/* if data in REST server req queue */ /* Note, this will first be a var */
		if (r_srvreq != NULL)
		{
			//Acquire r_mutex_answ
			//Answer the request.
			//Release r_mutex_answ
		}

	}

}