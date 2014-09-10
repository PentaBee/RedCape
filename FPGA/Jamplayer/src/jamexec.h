/****************************************************************************/
/*																			*/
/*	Module:			jamexec.h												*/
/*																			*/
/*					Copyright (C) Altera Corporation 1997					*/
/*																			*/
/*	Description:	Prototypes for statement execution functions			*/
/*																			*/
/****************************************************************************/

#ifndef INC_JAMEXEC_H
#define INC_JAMEXEC_H

/****************************************************************************/
/*																			*/
/*	Global variables														*/
/*																			*/
/****************************************************************************/

extern long jam_current_file_position;

extern long jam_current_statement_position;

extern long jam_next_statement_position;

extern unsigned int jam_statement_buffer_size;

/****************************************************************************/
/*																			*/
/*	Function Prototypes														*/
/*																			*/
/****************************************************************************/

JAM_RETURN_TYPE jam_init_statement_buffer
(
	char **statement_buffer,
	unsigned int *statement_buffer_size
);

void jam_free_statement_buffer
(
	char **statement_buffer,
	unsigned int *statement_buffer_size
);

JAM_RETURN_TYPE jam_get_statement
(
	char *statement_buffer,
	char *label_buffer
);

long jam_get_line_of_position
(
	long position
);

JAME_INSTRUCTION jam_get_instruction
(
	char *statement_buffer
);

int jam_skip_instruction_name
(
	char *statement_buffer
);

#endif /* INC_JAMEXEC_H */
