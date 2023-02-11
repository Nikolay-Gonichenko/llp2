#include "../include/parser.h"

/**
* Remove one char from request
*/
static void remove_char(int* size, char** request) {
	(*size)--;
	(*request)++;
}

/**
* Parse the tuple frome request
*/
static void parse_tuple(char** request_path, int* path_size, struct tuple* cur_tuple) {

	char* name = malloc(sizeof(char)*MAX_STRING_SIZE);

	int iter = 0;
	while ((*request_path[0]) != '/' && *path_size != 0 && (*request_path[0]) != '[') {
		name[iter++] = (*request_path)[0];
		remove_char(path_size, request_path);
	}
	cur_tuple->name = name;

}

/**
* Parse the attribute frome request
*/
static void parse_attribute(char** request_path, int* path_size, struct attribute** cur_attr) {

	char* field = malloc(sizeof(char) * MAX_STRING_SIZE);
	char* value = malloc(sizeof(char) * MAX_STRING_SIZE);
	
	int iter = 0;
	while ((*request_path[0]) != '/' && *path_size > 0 && (*request_path[0]) != '[') {
		if (path_size != 0 && (*request_path[0]) == ']') {
			(*cur_attr)->value = value;
			remove_char(path_size, request_path);


			if ((*request_path[0]) == '[') {
				struct attribute* next_attribute = malloc(sizeof(struct attribute));
				remove_char(path_size, request_path);
				parse_attribute(request_path, path_size, &next_attribute);
				(*cur_attr)->next = next_attribute;
			}
			
			break;
		} else if ((*request_path[0]) == '>' || (*request_path[0]) == '<' || (*request_path[0]) == '=' || (*request_path[0]) == '!') {
			iter = 0;
			(*cur_attr)->field = field;
			
			if ((*request_path)[1] == '=') {
				if ((*request_path[0]) == '>')
					(*cur_attr)->condition = GREATER_OR_EQUAL;
				if ((*request_path[0]) == '<')
					(*cur_attr)->condition = LESS_OR_EQUAL;
				remove_char(path_size, request_path);
			} else {
				(*cur_attr)->condition = (*request_path[0]);
			}
		} else if ((*request_path[0]) == '&' || (*request_path[0]) == '|') {
			(*cur_attr)->value = value;
			(*cur_attr)->bool_condition = (*request_path[0]);
			struct attribute* next_attribute = malloc(sizeof(struct attribute));
			remove_char(path_size, request_path);
			parse_attribute(request_path, path_size, &next_attribute);
			(*cur_attr)->composite_attribute = next_attribute;
		} else {
			if ((*cur_attr)->condition == NULL) {
				field[iter++] = (*request_path)[0];
			} else {
				value[iter++] = (*request_path)[0];
			}
		}
		remove_char(path_size, request_path);
	}

}

/**
* Check structure of request
* return true if structure is correct
*/
static bool check_path(char* request, int path_size) {
	int bracket = 0;
	for (size_t i = 0; i < path_size; i++){
		if (request[i] == '[')
			bracket++;
		if (request[i] == ']')
			bracket--;
	}
	if (bracket != 0)
		return false;
	return true;
}

struct request* parse_request(char* request, int size) {
	if(!check_path(request, size))
		return NULL;
	struct request* req = malloc(sizeof(struct request*));
	req->tuple_list = NULL;
	

	char operation = request[0];
	if( operation == '+' || operation == '-' || operation == '?' || operation == '=' ) {
		req->operation = operation;
	} else {
		return NULL;
	}
	
	remove_char(&size, &request);

	while (size > 0){
		if (request[0] == '/') {
			remove_char(&size, &request);

			struct tuple* cur_tuple = malloc(sizeof(struct tuple*));
			cur_tuple->attribute_list = NULL;
			parse_tuple(&request, &size, cur_tuple);

			cur_tuple->next = NULL;
			if (req->tuple_list == NULL) {
				req->tuple_list = cur_tuple;
			} else {
				struct tuple* prom_tuple = req->tuple_list;
				while (prom_tuple->next != NULL)
					prom_tuple = prom_tuple->next;
				prom_tuple->next = cur_tuple;
			}
		} else if (request[0] == '[') {
			remove_char(&size, &request);

			struct attribute* cur_attr = malloc(sizeof(struct attribute));
			parse_attribute(&request, &size, &cur_attr);

			struct tuple* prom_tuple = req->tuple_list;
			while (prom_tuple->next != NULL)
				prom_tuple = prom_tuple->next;
			prom_tuple->attribute_list = cur_attr;
			
		} else {
			return NULL;
		}
	}

	return req;

}
