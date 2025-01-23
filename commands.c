#include "commands.h"

// setpasswd

const char* APPLICATION_PASSWORD = "nopassword";

bool validate_set_password_command(int total_operand_count, char* password_input){

    /*if(total_operand_count != 3){

        printf("error: there can be only one operand supplied after the 'setpasswd' command: total of %d operands have been passed after 'setpasswd'\n", total_operand_count - 2);

        return false;

    }*/

    int len = strlen(password_input);

    if(len > 16) { // Max password length is 16

        printf("error: password cannot be longer than 16 characters: total of %d characters was given\n", len);

        return false;

    }

    // Index 0 is the executable name, 1 is the 'setpasswd' command and 2 is the password to set

    return true;

}

int execute_set_password_command(char* password_input){

    APPLICATION_PASSWORD = password_input;

    printf("New Password: %s\n", APPLICATION_PASSWORD);

    return 0;

}

const char* get_connection_password(){

    return APPLICATION_PASSWORD;

}

bool is_password_correct(char* password){

    return (strcmp(APPLICATION_PASSWORD, password) == 0);

}

// listen

unsigned short VALIDATED_PORT = 0;

bool validate_listen_command(int total_operand_count, char* validate_port) {

    int len = strlen(validate_port);

    if(len > 5){

        printf("error: given port has to be at most 4 digits long: given port was %d digitas long", len);

        return false;

    }

    int port_in_validation = 0;

    for(int i = 0; i < len; i++){

        int character = (int)validate_port[i];

        port_in_validation += (character * (10 ^ (len - i - 1)));

    }

    if(port_in_validation < 0 || port_in_validation >= (unsigned short)-1){

        printf("error: given port was outside of the range 0 - 65535: given port was %d", port_in_validation);

        return false;

    }

    VALIDATED_PORT = (short)port_in_validation;

    return true;

}

int execute_listen_command() {

    // Listen on an TCP connection

}

// connect

bool validate_connect_command(int total_operand_count, char* ip_and_port) {

    

}

int execute_connect_command(char* ip_and_port) {



}