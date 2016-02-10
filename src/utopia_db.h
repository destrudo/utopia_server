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

static void json_from_xml_recursive(xmlNode * node, struct json_object * json_obj)
{
	xmlNode *cur_node = NULL;
	struct json_object * next_base;
	struct json_object * obj_child;
	struct json_object * child_base; /* This is the base key, ala: <meow id="1" >cupcake</meow>, 'meow' would be the base. */
	struct json_object * attr_array; /* This is the attribute array of key:value pairs, in the above, it'd contain { 'id':1 } */
	struct json_object * value_string; /* This is the value string, in the above it would be "cupcake", if the attribute array was used, child_base would have an object name of "value" pointing to this value. */
	struct json_object * tmp, tmp_kv;

	int tmp_int;
	char buf[DEFAULT_BUFFER_SIZE]; /* This is lazy. */

	/* This might become an array, I'm not sure yet. */
	next_base = json_object_new_object();

	for (cur_node = a_node; cur_node; cur_node = cur_node->next)
	{
		obj_child = NULL;		/* Dump 	 They 		*/
		child_base = NULL;		/* the 		 are 		*/
		attr_array = NULL;		/* pointers  trashing	*/
		value_string = NULL;	/* out 		 us			*/

		if (cur_node->type == XML_ELEMENT_NODE)
		{
			obj_child = json_object_new_object()
			
			/* If attributes */
				attr_array = json_object_new_array();
				/* For each attribute */
					tmp = NULL; /* Point the pointer somewhere else */
					tmp_kv = NULL; /* This one too. */

					tmp_kv = json_object_new_object();
					/* Pull off the attribute */
					buf = attribute->name;

					/* if value isint() */
						tmp_int = strtoi(value);
						tmp = json_object_new_int(tmp_int);

						json_object_object_add(attributeName, tmp_int)
					/* else if value ishexint() */
						tmp_int = hexstrtoi(value); /* lol */
						tmp = json_object_new_int(tmp_int);

					/* else */
						tmp = json_object_new_string(atrribute->value);

					json_object_object_add(tmp_kv, buf, )
					json_object_array_add(attr_array, tmpkv);

					/* Clear the memories */
					memset(buf, 0, DEFAULT_BUFFER_SIZE * sizeof(char));

			value_string = json_object_new_string(cur_node->value);
			/* If we set the attribute array at all, we need to prepare child_base as an array */
			if (attr_array != NULL)
			{
				child_base = json_object_new_object();

				json_object_object_add(child_base, "attributes", attr_array);
				json_object_object_add(child_base, "data", value_string);
			}
			else
			{
				child_base = value_string; /* Just point the pointer. */
			}

			json_object_object_add(obj_child,cur_node->name,child_base);
			
		}
	}

	json_from_xml_recursive(cur_node->children);
}

static void prepare_device_json_from_xml(char * xml_in, char * json_out)
{
	struct json_object * root;

    xmlNode root_element = NULL;
    xmlDtdPtr dtd = NULL; /* I don't think we need this. */
	xmlDocPtr doc; /* the resulting document tree */

	/* At some point, if the string exceeds DEFAULT_BUFFER_SIZE, it'll increment
     * bufc, then perform a realloc of (DEFAULT_BUFFER_SIZE * bufc).
     */
    int bufc = 1;
    char * buf;

    /* Sanity checks. */

    if (xml_in == NULL)
    {
    	UDBCERR("prepare_device_json_from_xml(), xml_in empty.");
   		return;
    }

    if (json_out != NULL)
    {
    	UDBCERR("prepare_device_json_from_xml(), json_out not null, will free memory.");
    	free(json_out);
    	json_out = NULL;
    }


    buf = (char *)calloc(DEFAULT_BUFFER_SIZE, sizeof(char)); /* alloc initial buffer. */

    /* For the use of noname.xml, look at the libxml2 example 'parse3.c' */
    doc = xmlReadMemory(xml_in, strlen(xml_in), "noname.xml", NULL, 0);
    if (doc == NULL)
    {
    	UDBCERR("prepare_device_json_from_xml(), failed to parse input data, dumping:");
    	fprintf(stderr, "\n%s\n\n\n", xml_in);
    	return;
    }

	root_element = xmlDocGetRootElement(doc);


    

    


}