#ifndef ui_H
#define ui_H
#include "stdint.h"

typedef __packed struct ext_client_custom_graphic_delete_t
{
uint8_t operate_tpye; 
uint8_t layer; 
}ext_client_custom_graphic_delete_t;

typedef __packed struct graphic_data_struct_t
{ 
	uint8_t graphic_name[3]; 
	uint32_t operate_tpye:3; 
	uint32_t graphic_tpye:3; 
	uint32_t layer:4; 
	uint32_t color:4; 
	uint32_t start_angle:9;
	uint32_t end_angle:9;
	uint32_t width:10; 
	uint32_t start_x:11; 
	uint32_t start_y:11; 
	uint32_t radius:10; 
	uint32_t end_x:11; 
	uint32_t end_y:11; 
}graphic_data_struct_t;

typedef __packed struct ext_client_custom_graphic_single_t
{
 graphic_data_struct_t grapic_data_struct;
} ext_client_custom_graphic_single_t;

typedef __packed struct ext_client_custom_character_t
{
graphic_data_struct_t grapic_data_struct;
uint8_t data[30];
} ext_client_custom_character_t;


#define RBID get_robot_id()
#define capUI_h 0


#endif
