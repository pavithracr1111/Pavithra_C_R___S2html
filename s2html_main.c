#include <stdio.h>
#include "s2html_event.h"
#include "s2html_conv.h"
#include "s2html_conv.c"
#include "s2html_event.c"

/********** main **********/

int main (int argc, char *argv[])
{
	FILE * sfp, *dfp; // source and destination file descriptors 
	pevent_t *event;
	char dest_file[100]; // buffer for destination file name

	if(argc < 2)
	{
		// Error if file name is not provided
		printf("\nError! please enter file name and mode\n");
		printf("Usage: <executable> <file name> \n");
		printf("Example : ./a.out test.c\n\n");
		return 1;
	}
#ifdef DEBUG
	printf("File to be opened: %s\n", argv[1]); // Debug print of file to be opened
#endif

	/* open the file */
	if(NULL == (sfp = fopen(argv[1], "r"))) // open source file in read mode
	{
		// Error if file could not be opened
		printf("Error! File %s could not be opened\n", argv[1]);
		return 2;
	}
	/* Check for output file and convert the [ .txt/.c ] file to [ .txt.html / .c.html ] */
	if (argc > 2)
	{
		sprintf(dest_file, "%s.html", argv[2]); // Set output file name based on user input
	}
	else
	{
		sprintf(dest_file, "%s.html", argv[1]); // Default output file name
	}
	/* open destination file */
	if (NULL == (dfp = fopen(dest_file, "w"))) // open destination file in write mode
	{
		// Error if destination file could not be created
		printf("Error! could not create %s output file\n", dest_file);
		return 3;
	}

	/* write HTML starting tags */
	html_begin(dfp, HTML_OPEN); // Add beginning HTML tags

	/* Read from source file, convert to HTML, and write to destination file */
	do
	{
		event = get_parser_event(sfp); // Get the next event from the source file
		/* call source_to_html */
		source_to_html(dfp, event); // Convert the event to HTML and write to destination
//		printf("In main: Event = %d\n", event);
	} while (event->type != PEVENT_EOF); // Loop until End of File event

	/* Call start_or_end_conv function for ending the conversion */
	html_end(dfp, HTML_CLOSE); // Add closing HTML tags
	
	printf("\nOutput file %s generated\n", dest_file); // Print success message

	/* close files */
	fclose(sfp); // Close source file
	fclose(dfp); // Close destination file

	return 0; // Successful execution
}
