/*
* FreeRTOS_Test1.c
*
* Created: 26/10/2016 13:55:41
* Author : IHA
*/

#include <avr/sfr_defs.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// FreeRTOS Includes
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>
#include <semphr.h>

//
#include <string.h>

#include "src/board/board.h"
#include "structs.h"
#include "src/tasks/joystick_task.h"
#include "src/tasks/logic_task.h"
#include "src/tasks/display_task.h"
#include "src/game/tictactoe.h"

#define tskJOYSTICK_PRIORITY 4
#define tskCOMMUNICATION_PRIORITY 3
#define tskLOGIC_PRIORITY 2
#define tskDISPLAY_PRIORITY 1

#define JOYSTICK_QUEUE_LENGTH 10




//Resources
static uint16_t frame_buf[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // frame_buf contains a bit pattern for each column in the display
static char tictactoe_array[9] = {'-', '-', '-', '-', '-', '-', '-', '-', '-'};
static QueueHandle_t joystick_input_queue = NULL;

static QueueHandle_t _x_com_received_chars_queue = NULL;


static const uint8_t _COM_RX_QUEUE_LENGTH = 30;
static SemaphoreHandle_t  mutex_tictactoe = NULL;


//-----------------------------------------
void communication_task(void *pvParameters)
{
	// The parameters are not used
	( void ) pvParameters;

	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 2 );
	#endif
	
	BaseType_t result = 0;
	uint8_t byte;
	
	//uint8_t selected_field = 0;
	char const * timeout = "TO\r\n";
	uint8_t timeoutlen = strlen(timeout);
	while(1)
	{
		result = xQueueReceive(_x_com_received_chars_queue, &byte, 1000L);
		
		if (result) {
			com_send_bytes(&byte, 1);
		}else {
			com_send_bytes((uint8_t*)timeout, timeoutlen);
		}

		vTaskDelay(100);
	}
}

//-----------------------------------------
void startup_task(void *pvParameters)
{
	// The parameters are not used
	( void ) pvParameters;

	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 1 );
	#endif

	_x_com_received_chars_queue = xQueueCreate( _COM_RX_QUEUE_LENGTH, ( unsigned portBASE_TYPE ) sizeof( uint8_t ) );
	init_com(_x_com_received_chars_queue);
	
	//Initialize queues
	joystick_input_queue  = xQueueCreate(JOYSTICK_QUEUE_LENGTH, sizeof(input_t *));

	// Initialize Mutex
	mutex_tictactoe = xSemaphoreCreateMutex();//1

	//
	task_parameters_t joystick_task_parameters = {.queue = joystick_input_queue};
	logic_task_parameters_t logic_task_parameters = {.joystick_input_queue = joystick_input_queue, .tictactoe_array = tictactoe_array, .mutex_tictactoe = mutex_tictactoe};
	display_task_parameters_t display_task_parameters = {.frame_buf = frame_buf, .tictactoe_array = tictactoe_array, .mutex_tictactoe = mutex_tictactoe};

	// Initialization of tasks etc. can be done here
	(void)xTaskCreate(communication_task, (const char *)"Communication", configMINIMAL_STACK_SIZE, (void *)NULL, tskIDLE_PRIORITY, NULL);
	(void)xTaskCreate(joystick_task, (const char *)"Joystick", configMINIMAL_STACK_SIZE, (void *)&joystick_task_parameters, tskJOYSTICK_PRIORITY, NULL);
	(void)xTaskCreate(logic_task, (const char *)"Logic", configMINIMAL_STACK_SIZE, (void *)&logic_task_parameters, tskLOGIC_PRIORITY, NULL);
	(void)xTaskCreate(display_task, (const char *)"Display", configMINIMAL_STACK_SIZE, (void *)&display_task_parameters, tskDISPLAY_PRIORITY, NULL);
	
	// Lets send a start message to the console
	com_send_bytes((uint8_t *)"Then we Start!\n", 15);
	
	while(1)
	{
		vTaskDelay( 1000 );
	}
}

// Prepare shift register setting SER = 1
void prepare_shiftregister()
{
	// Set SER to 1
	PORTD |= _BV(PORTD2);
}

// clock shift-register
void clock_shift_register_and_prepare_for_next_col()
{
	// one SCK pulse
	PORTD |= _BV(PORTD5);
	PORTD &= ~_BV(PORTD5);
	
	// one RCK pulse
	PORTD |= _BV(PORTD4);
	PORTD &= ~_BV(PORTD4);
	
	// Set SER to 0 - for next column
	PORTD &= ~_BV(PORTD2);
}

// Load column value for column to show
void load_col_value(uint16_t col_value)
{
	PORTA = ~(col_value & 0xFF);
	
	// Manipulate only with PB0 and PB1
	PORTB |= 0x03;
	PORTB &= ~((col_value >> 8) & 0x03);
}

//-----------------------------------------
void handle_display(void)
{
	static uint8_t col = 0;
	
	if (col == 0)
	{
		prepare_shiftregister();
	}
	
	load_col_value(frame_buf[col]);
	
	clock_shift_register_and_prepare_for_next_col();
	
	// count column up - prepare for next
	col++;
	if (col > 13)
	{
		col = 0;
	}
}

//-----------------------------------------
void vApplicationIdleHook( void )
{
	//
}

//-----------------------------------------
int main(void)
{
	
	init_board();
	
	// Shift register Enable output (G=0)
	PORTD &= ~_BV(PORTD6);
	
	//Create task to blink gpio
	(void)xTaskCreate(startup_task, (const char *)"Startup", configMINIMAL_STACK_SIZE, (void *)NULL, tskIDLE_PRIORITY, NULL);

	// Start the display handler timer
	init_display_timer(handle_display);
	
	sei();
	
	//Start the scheduler
	vTaskStartScheduler();
	
	//Should never reach here
	while (1)
	{
	}
}


