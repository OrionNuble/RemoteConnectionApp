#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "commands.h"

#define NO_ERROR_RETURN 0
#define INVALID_COMMAND -1
#define TOO_FEW_OR_TOO_MANY_OPERANDS -2
#define LONE_TARGET_OR_COMMAND -3

void print_help_message(){

    printf("Help!!!\n");

}

int main(int argc, char** argv){

    if (argc == 1){

        // Print help
    
        print_help_message();

        return NO_ERROR_RETURN;

    }
    else if(argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "help") == 0)){

        // Print help

        print_help_message();

        return NO_ERROR_RETURN;

    }
    else if(argc == 2){

        printf("error: lone target or command was specified with no operands: target or command might or might not be valid: target or command: %s\n", argv[1]);

        return LONE_TARGET_OR_COMMAND;

    }

    // Check if the command is a valid command and the enough operands are supplied

    bool is_command_with_target = false;

    int seek_command_index = -1;

    if(strcmp(argv[1], "local") == 0 || strcmp(argv[1], "remote") == 0) {

        is_command_with_target = true;
        seek_command_index = 2;

    }
    else{

        is_command_with_target = false;
        seek_command_index = 1;

    }

    int valid_command_index = -1;


    // Command info, if valid

    char* command = "";
    char* operands[10] = {""}; // Max operand size
    size_t actual_operand_size = 0;

    // Possible commands

    char* commands_with_no_targets[3] = {"setpasswd", "listen", "connect"};
    char* commands_with_targets[8] = {"cd", "fetch", "send", "cp", "mv", "rm", "cat", "ls"};

    size_t no_target_commands_operand_required_length[11] = {1, 1, 2};
    size_t target_commands_operand_required_length[11] = {1, 2, 2, 2, 2, 1, 1, 1};

    if(is_command_with_target){

        for(size_t i = 0; i < 8; i++){

            if(strcmp(argv[seek_command_index], commands_with_targets[i]) == 0){

                // Sure, the command is valid, but are enough operands supplied?

                if((argc - (seek_command_index + 1)) != target_commands_operand_required_length[i]) { // Nope!

                    printf("error: command is valid, but either too few or too many operands passed: total operands passed was %d, but %zu are required\n", (argc - (seek_command_index + 1)), target_commands_operand_required_length[i]);

                    return TOO_FEW_OR_TOO_MANY_OPERANDS;

                }

                // Yeyyy!!

                valid_command_index = i;
                command = commands_with_targets[i];

            }

        }

    }
    else {

        for(size_t i = 0; i < 3; i++){

            if(strcmp(argv[seek_command_index], commands_with_no_targets[i]) == 0){

                // Sure, the command is valid, but are enough operands supplied?

                if((argc - (seek_command_index + 1)) != no_target_commands_operand_required_length[i]) { // Nope!

                    printf("error: command is valid, but either too few or too many operands passed: total operands passed was %d, but %zu are required\n", (argc - (seek_command_index + 1)), no_target_commands_operand_required_length[i]);

                    return TOO_FEW_OR_TOO_MANY_OPERANDS;

                }

                // Yeyyy!!

                valid_command_index = i;
                command = commands_with_no_targets[i];

            }

        }

    }

    if(valid_command_index == -1) { // If didn't find a valid command yet, error out

        printf("error: invalid command: %s\n", argv[1]);

        return INVALID_COMMAND;

    }

    // Now, let's parse this input and make sure that the given command and operands actually match

    if(strcmp(command, "setpasswd") == 0){

        bool is_valid = validate_set_password_command(argc, argv[seek_command_index + 1]);

        if(is_valid){

            int execution_result = execute_set_password_command(argv[seek_command_index + 1]);

            return execution_result;

        }
        else{
            return INVALID_COMMAND;
        }

    }
    else if(strcmp(command, "listen") == 0){

        bool is_valid = validate_listen_command(argc, argv[seek_command_index + 1]);

        if(is_valid){

            int execution_result = execute_listen_command();

            return execution_result;

        }
        else{
            return INVALID_COMMAND;
        }

    }
    else if(strcmp(command, "connect") == 0){

        bool is_valid = validate_connect_command(argc, argv[seek_command_index + 1]);

        if(is_valid){

            int execution_result = execute_connect_command(argv[seek_command_index + 1]);

            return execution_result;

        }
        else{
            return INVALID_COMMAND;
        }

    }

}