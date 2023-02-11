#include "../include/print.h"

/**
* Print operation of request
*/
static void print_operation(char operation) {
	switch (operation) {
	case '-':
		printf("Remove operation\n");
		break;
	case '+':
		printf("Add operation\n");
		break;
	case '?':
		printf("Get operation\n");
		break;
	case '=':
		printf("Update operation\n");
		break;
	}
}

/**
* Print condition of request
*/
static void print_combined_condition(char condition) {
	printf("Condition: ");
	switch (condition){
	case '=':
		printf("= : equally\n");
		break;
	case '>':
		printf("> : more\n");
		break;
	case '<':
		printf("< : less\n");
		break;
	case '1':
		printf(">= : greater than or equal to\n");
		break;
	case '0':
		printf("<= : less than or equal to\n");
		break;
	case '!':
		printf("! : not\n");
		break;

	}
}

/**
* Print tuple name
*/
static void print_tuple_name(char* name) {
	if (name[0] == '*')
		printf("* - For all tuples\n");
	else
		printf("Where tuple name = %s\n", name);
}

/**
* Print attribute
*/
static void print_attribute(struct attribute* cur_attr, bool combined) {
	printf("Field name: %s\n", cur_attr->field);
	print_combined_condition(cur_attr->condition);
	printf("Value: %s\n", cur_attr->value);

	if (combined) {
		while (cur_attr->bool_condition != NULL){
				printf("Condition: %c\n", cur_attr->bool_condition);

				print_attribute(cur_attr->composite_attribute, false);
				cur_attr = cur_attr->composite_attribute;
		}
	}
}

void print_struct(struct request* request) {
	bool check = true;
	int level = 1;
	
	print_operation(request->operation);
	printf("\n");

	struct tuple* cur_tuple = request->tuple_list;

	while (check) {
		if (cur_tuple->next == NULL)
			check = false;

		printf("Deep: %d\n", level);

		print_tuple_name(cur_tuple->name);
		
		if (cur_tuple->attribute_list != NULL){
			print_attribute(cur_tuple->attribute_list, true);
			if (cur_tuple->attribute_list->next != NULL)
				print_attribute(cur_tuple->attribute_list->next, true);
		}
		
		cur_tuple = cur_tuple->next;
		printf("\n");
		level++;
	}

}
