#include <stdio.h>

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <json.h> /* We'll be using json-c for all of the json stuff */

#define DEFAULT_ENCODING			"UTF-8"
#define DEFAULT_BUFFER_SIZE			512

/* Method redefinitions */
#define UDBCERR(errstr)				fprintf(stderr, "ERROR: utopia_db.%s\n", errstr)

/*
 *
 * This method accepts a db entry and fills an XML string from a valid document.
 *  It then populates str with the completed data.
 */
static void prepare_device_xml_from_json(char * str_out, char * json_in)
{
	struct json_object * root;

	/* Since mongodb isn't gonna give us a json_object :( */
	root = json_tokener_parse(json_in);

}

static void prepare_device_json_from_xml(char * xml_in, char * json_out)
{
	/* xml_in must be complete xml document */
	/* use xml2json to convert string to json_out buffer */
	/* Done. */
}