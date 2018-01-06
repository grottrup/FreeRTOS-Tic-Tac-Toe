/*
 * task_parameters.h
 *
 * Created: 30-05-2017 20:18:26
 *  Author: T420s
 */ 

#ifndef TASK_PARAMETERS_H_
#define TASK_PARAMETERS_H_

#include <queue.h>

typedef struct
{
	QueueHandle_t * queue;
} task_parameters_t;

typedef struct
{
	QueueHandle_t * joystick_input_queue;
	char * tictactoe_array;
	SemaphoreHandle_t mutex_tictactoe;
} logic_task_parameters_t;

typedef struct
{
	uint16_t * frame_buf;
	char * tictactoe_array;
	SemaphoreHandle_t mutex_tictactoe;
} display_task_parameters_t;

typedef struct
{
	uint8_t key;
} input_t;

#endif /* TASK_PARAMETERS_H_ */