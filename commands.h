#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// setpasswd

bool validate_set_password_command(int total_operand_count, char* password_input);
int execute_set_password_command(char* password_input);
const char* get_connection_password();
bool is_password_correct(char* password);

// listen

bool validate_listen_command(int total_operand_count, char* validate_port);
int execute_listen_command();

// connect

bool validate_connect_command(int total_operand_count, char* ip_and_port);
int execute_connect_command(char* ip_and_port);