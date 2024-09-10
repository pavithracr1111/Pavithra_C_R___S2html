#include <stdio.h>
#include "s2html_event.h"
#include "s2html_conv.h"

/* start_or_end_conv function definition */
void html_begin(FILE* dest_fp, int type) /* type => not used, but can be used to add different HTML tags */
{
	/* Add HTML beginning tags into destination file */
	fprintf(dest_fp, "<!DOCTYPE html>\n");
	fprintf(dest_fp, "<html lang=\"en-US\">\n");
	fprintf(dest_fp, "<head>\n");
	fprintf(dest_fp, "<title>%s</title>\n", "sode2html");  // Title of the HTML document
	fprintf(dest_fp, "<meta charset=\"UTF-8\">\n");  // Set charset to UTF-8
	fprintf(dest_fp, "<link rel=\"stylesheet\" href=\"styles.css\">\n");  // Link to external CSS
	fprintf(dest_fp, "</head>\n");
	fprintf(dest_fp, "<body style=\"background-color:lightgrey;\">\n");  // Set background color of the body
	fprintf(dest_fp, "<pre>\n");  // Begin preformatted text block
}
void html_end(FILE* dest_fp, int type) /* type => not used, but can be used to add different HTML tags */
{
	/* Add HTML closing tags into destination file */
	fprintf(dest_fp, "</pre>\n");  // End preformatted text block
	fprintf(dest_fp, "</body>\n");  // End body section
	fprintf(dest_fp, "</html>\n");  // End HTML document
}

/* source_to_html function definition */
void source_to_html(FILE* fp, pevent_t *event)
{
#ifdef DEBUG
	printf("%s", event->data);  // Debugging output for event data
#endif
	switch(event->type)
	{
		case PEVENT_PREPROCESSOR_DIRECTIVE:
			fprintf(fp,"<span class=\"preprocess_dir\">%s</span>",event->data);  // Wrap preprocessor directives in HTML span
			break;
		case PEVENT_MULTI_LINE_COMMENT:
		case PEVENT_SINGLE_LINE_COMMENT:
			fprintf(fp,"<span class=\"comment\">%s</span>",event->data);  // Wrap comments in HTML span
			break;
		case PEVENT_STRING:
			fprintf(fp,"<span class=\"string\">%s</span>",event->data);  // Wrap strings in HTML span
			break;
		case PEVENT_HEADER_FILE:
			/* Write header files to HTML */
			if(event->property == USER_HEADER_FILE)
				fprintf(fp,"<span class=\"header_file\">%s</span>",event->data);  // User-defined header file
			else
				fprintf(fp,"<span class=\"header_file\">&lt;%s&gt;</span>",event->data);  // Standard header file wrapped in <>
			break;
		case PEVENT_REGULAR_EXP:
		case PEVENT_EOF:
			fprintf(fp,"%s",event->data);  // Write regular text or EOF to HTML
			break;
		case PEVENT_NUMERIC_CONSTANT:
			fprintf(fp,"<span class=\"numeric_constant\">%s</span>",event->data);  // Wrap numeric constants in HTML span
			break;
		case PEVENT_RESERVE_KEYWORD:
			if(event->property == RES_KEYWORD_DATA)
			{
				fprintf(fp,"<span class=\"reserved_key1\">%s</span>",event->data);  // Data-type reserved keyword
			}
			else
			{
				fprintf(fp,"<span class=\"reserved_key2\">%s</span>",event->data);  // Non-data-type reserved keyword
			}
			break;
		case PEVENT_ASCII_CHAR:
			fprintf(fp,"<span class=\"ascii_char\">%s</span>",event->data);  // Wrap ASCII characters in HTML span
			break;
		default :
			printf("Unknown event\n");  // Handle unknown events
			break;
	}
}
