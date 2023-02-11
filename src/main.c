#define _GNU_SOURCE
#define SIZE 2048

#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"
#include "../include/print.h"

int main() {

    char request_str[SIZE];
    puts("Enter request:");

    fgets(request_str, SIZE, stdin);

    size_t len = strlen(request_str);

    struct request* request = parse_request(request_str, len-1);
    if (request == NULL) {
	printf("Invalid request\n");
	return 1;
    }

    printf("\n");
    print_struct(request);

    return 0;
}
