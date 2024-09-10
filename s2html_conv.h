#ifndef S2HTML_CONV_H
#define S2HTML_CONV_H

/* constants */

#define HTML_OPEN   1 // HTML opening tags identifier
#define HTML_CLOSE  0 // HTML closing tags identifier

/********** function prototypes **********/

void html_begin(FILE* dest_fp, int type); /* type => not used, but can be used to add different HTML tags */
void html_end(FILE* dest_fp, int type);   /* type => not used, but can be used to add different HTML tags */
void source_to_html(FILE* fp, pevent_t *event); // Converts source code to HTML format

#endif
