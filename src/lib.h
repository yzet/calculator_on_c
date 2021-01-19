#ifndef INT_CALCULATOR_HEADER
#define INT_CALCULATOR_HEADER

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

double calculate_expression(char expresion[]);
void delete_brackets(char expression[], int index_of_left_bracket, size_t index_of_right_bracket);
void calculate_expression_without_brackets(char original_expression[], int index_of_left_bracket, size_t index_of_right_bracket);
double calculate_simple_expression(char left_operand[], char right_operand[], char action);
char ** form_expression_with_result(char **original_expression, double result, int left_index_of_left_operand, int right_index_of_right_operand);
bool is_have_next_action(char expression[], int action_index, int right_bracket_index);
bool is_delete_brackets_pair(char expression[], int left_index_of_left_operand, int right_index_of_right_operand);

size_t get_number_length(double number, size_t count_of_digits_after_decimal_point);
size_t get_index_of_decimal_point(double number);
void double_to_str(double number, char* dist, size_t count_of_digits_after_decimal_point);


bool is_action(char symbol);
int get_action_priority(char action);

bool is_have_brackets(char *expression);

void turn_over(char str[]);
void app_end_to_str(char **str, char symbol);

// log functions

void print_log(char message[]);
#endif