#pragma once

#define MAX_STRING_SIZE 64
#define LESS_OR_EQUAL '0'
#define GREATER_OR_EQUAL '1'

#include <stdbool.h>

enum attribute_condition {
	MORE = '>',
	LESS = '<',
	EQUAL = '=',
	NEG = '!',
	GOQ = GREATER_OR_EQUAL,
	LOQ = LESS_OR_EQUAL
};

enum bool_condition {
	AND = '&',
	OR = '|',
	NOT = '!'
};

struct attribute {
	char* field;
	char* value;
	enum attribute_condition condition;
	enum bool_condition bool_condition;
	struct attribute* composite_attribute;
	struct attribute* next;
};

struct tuple {
	char* name;
	struct attribute* attribute_list;
	struct tuple* next;
};

struct request {
	char operation;
	struct tuple* tuple_list;
};
