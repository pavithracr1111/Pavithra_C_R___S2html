#ifndef S2HTML_EVENT_H
#define S2HTML_EVENT_H

/* event data properties */
#define USER_HEADER_FILE		1   // Property for user-defined header files
#define STD_HEADER_FILE			2   // Property for standard header files
#define RES_KEYWORD_DATA		3   // Property for reserved keywords related to data types
#define RES_KEYWORD_NON_DATA	4   // Property for reserved keywords not related to data types

#define PEVENT_DATA_SIZE	1024  // Maximum size of event data

typedef enum
{
	PEVENT_NULL,  // Null event
	PEVENT_PREPROCESSOR_DIRECTIVE,  // Preprocessor directive event
	PEVENT_RESERVE_KEYWORD,  // Reserved keyword event
	PEVENT_NUMERIC_CONSTANT,  // Numeric constant event
	PEVENT_STRING,  // String literal event
	PEVENT_HEADER_FILE,  // Header file event
	PEVENT_REGULAR_EXP,  // Regular expression event
	PEVENT_SINGLE_LINE_COMMENT,  // Single-line comment event
	PEVENT_MULTI_LINE_COMMENT,  // Multi-line comment event
	PEVENT_ASCII_CHAR,  // ASCII character event
	PEVENT_EOF  // End of file event
}pevent_e;

typedef struct
{
	pevent_e type;  // Event type (from enum pevent_e)
	int property;  // Property associated with the data (e.g., user or standard header file)
	int length;  // Length of the data string
	char data[PEVENT_DATA_SIZE];  // Parsed string data (up to 1024 characters)
}pevent_t;

/********** function prototypes **********/

pevent_t *get_parser_event(FILE *fp);  // Function to get the next parser event from a file

#endif
/**** End of file ****/
