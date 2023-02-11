#pragma once
#include "model.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Parse the request
* return request in struct request
*/
struct request* parse_request(char* request, int path_size);
