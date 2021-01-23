#include "lib.h"

double calculate_expression(char expresion[])
{
    char *expression_copy = (char *)calloc(255 + strlen(expresion) + 1, sizeof(char));
    strcpy(expression_copy, expresion);

    delete_brackets(expression_copy, -1, strlen(expression_copy));

    char *error;
    double result = strtod(expression_copy, &error);
    free(expression_copy);
    return result;
}

void delete_brackets(char expression[], int index_of_left_bracket, size_t index_of_right_bracket)
{
    size_t index_of_left_bracket_temp = 0;
    size_t index_of_right_bracket_temp = 0;
    int count_of_opening_brackets = 0;

    for (size_t index_of_symbol = index_of_left_bracket + 1; index_of_symbol < strlen(expression); index_of_symbol++)
    {
        if (expression[index_of_symbol] == '(')
        {
            if (count_of_opening_brackets == 0)
                index_of_left_bracket_temp = index_of_symbol;
            count_of_opening_brackets++;
        }
        else if (expression[index_of_symbol] == ')')
        {
            count_of_opening_brackets--;
            if (count_of_opening_brackets == 0)
            {
                index_of_right_bracket_temp = index_of_symbol;
                delete_brackets(expression, index_of_left_bracket_temp, index_of_right_bracket_temp);
                index_of_symbol = -1;
                count_of_opening_brackets = 0;
            }
        }
        if (index_of_symbol == index_of_right_bracket)
        {
            break;
        }
    }
    calculate_expression_without_brackets(expression, index_of_left_bracket, index_of_right_bracket);
}

void calculate_expression_without_brackets(char *original_expression, int index_of_left_bracket, size_t index_of_right_bracket)
{
    int last_action_index = -1;
    int last_action_priority = -2;
    int action_index = -1;
    int action_priority = -1;

    bool is_right_and_left_operands_freed = true;

    char *left_operand = (char *)calloc(0, sizeof(char));
    char *right_operand = (char *)calloc(0, sizeof(char));
    is_right_and_left_operands_freed = false;

    int left_index_of_left_operand = -1;
    size_t right_index_of_right_operand = strlen(original_expression) + 1;

    for (size_t i = index_of_left_bracket + 1; i < strlen(original_expression); i++)
    {
        if (!is_have_brackets(original_expression) && index_of_left_bracket != -1)
        {
            break;
        }
        if (i == index_of_right_bracket - 1)
            break;
        if (!is_have_next_action(original_expression, i - 1, index_of_right_bracket))
        {
            break;
        }
        if (is_action(original_expression[i]) && i != index_of_left_bracket + 1)
        {
            action_index = i;
            action_priority = get_action_priority(original_expression[action_index]);
            if (original_expression[i + 1] == '(' || original_expression[i + 1] == ')')
                break;
        }
        if (last_action_priority >= action_priority || !is_have_next_action(original_expression, i, index_of_right_bracket))
        {
            if (!(is_have_next_action(original_expression, i, index_of_right_bracket)) && last_action_priority < action_priority)
            {
                last_action_priority = action_priority;
                last_action_index = action_index;
            }
            if (last_action_index < 0)
            {
                break;
            }
            for (int k = last_action_index - 1; k >= 0; k--)
            {
                if (isdigit(original_expression[k]) || original_expression[k] == '.' || (original_expression[k] == '-' && k == index_of_left_bracket + 1))
                {
                    char *buff = (char *)calloc(strlen(left_operand) + 2, sizeof(char));
                    strcpy(buff, left_operand);
                    int len = strlen(buff);
                    if (len == 0)
                    {
                        buff[0] = original_expression[k];
                    }
                    else
                    {
                        *(buff + len) = original_expression[k];
                    }
                    free(left_operand);
                    left_operand = (char *)calloc(strlen(buff) + 1, sizeof(char));
                    strcpy(left_operand, buff);
                    left_index_of_left_operand = k;
                    free(buff);
                }
                else
                {
                    break;
                }
            }
            turn_over(left_operand);

            for (size_t k = last_action_index + 1; k < strlen(original_expression); k++)
            {
                if (isdigit(original_expression[k]) || original_expression[k] == '.' || (original_expression[k] == '-' && k == last_action_index + 1))
                {
                    char *buff = (char *)calloc(strlen(right_operand) + 2, sizeof(char));
                    strcpy(buff, right_operand);
                    int len = strlen(buff);
                    if (len == 0)
                    {
                        buff[0] = original_expression[k];
                    }
                    else
                    {
                        *(buff + len) = original_expression[k];
                    }
                    free(right_operand);
                    right_operand = (char *)calloc(strlen(buff) + 1, sizeof(char));
                    strcpy(right_operand, buff);
                    right_index_of_right_operand = k;
                    free(buff);
                }
                else
                {
                    break;
                }
            }
            double result = calculate_simple_expression(left_operand, right_operand, original_expression[last_action_index]);
            is_right_and_left_operands_freed = false;
            last_action_index = -1;
            last_action_priority = -2;
            i = index_of_left_bracket;
            action_index = -1;
            action_priority = -1;
            free(left_operand);
            free(right_operand);
            is_right_and_left_operands_freed = true;
            char *expression_with_result = *form_expression_with_result(&original_expression, result, left_index_of_left_operand, right_index_of_right_operand);
            strcpy(original_expression, expression_with_result);
            free(expression_with_result);
            if (index_of_left_bracket != -1)
            {
                break;
            }
            left_operand = (char *)(calloc(0, sizeof(char)));
            right_operand = (char *)(calloc(0, sizeof(char)));
            is_right_and_left_operands_freed = false;
        }
        else
        {
            if (is_action(original_expression[i]))
            {
                last_action_index = action_index;
                last_action_priority = action_priority;
                // test this?
                action_priority++;
            }
        }
    }
    if (!is_right_and_left_operands_freed)
    {
        free(left_operand);
        free(right_operand);
    }
}

bool is_action(char symbol)
{
    switch (symbol)
    {
    case '^':
    case '*':
    case '/':
    case '+':
    case '-':
        return true;
    default:
        return false;
    }
}

int get_action_priority(char action)
{
    switch (action)
    {
    case '^':
        return 2;
    case '*':
    case '/':
        return 1;
    case '+':
    case '-':
        return 0;
    default:
        return -1;
        break;
    }
}

double calculate_simple_expression(char left_operand[], char right_operand[], char action)
{
    char **end;
    double left_operand_d = strtod(left_operand, end); // may be error
    double right_operand_d = strtod(right_operand, end);

    switch (action)
    {
    case '^':
        return pow(left_operand_d, right_operand_d);
    case '*':
        return (left_operand_d * right_operand_d);
    case '/':
        return (left_operand_d / right_operand_d);
    case '+':
        return (left_operand_d + right_operand_d);
    case '-':
        return (left_operand_d - right_operand_d);
    default:
        break;
    }
}

char **form_expression_with_result(char **original_expression, double result, int left_index_of_left_operand, int right_index_of_right_operand)
{
    size_t count_of_numbers_after_decimal_point = 5;

    size_t number_length = get_number_length(result, count_of_numbers_after_decimal_point);

    char *result_str = (char *)calloc(number_length + 1, sizeof(char));

    double_to_str(result, result_str, count_of_numbers_after_decimal_point);

    size_t original_expression_length = strlen(*original_expression);

    size_t new_expression_length = original_expression_length - (right_index_of_right_operand - left_index_of_left_operand) + number_length;
    int index_for_copy_from_original_expression_delta = 0;
    if (is_delete_brackets_pair(*original_expression, left_index_of_left_operand, right_index_of_right_operand))
    {
        new_expression_length -= 2;
        index_for_copy_from_original_expression_delta = 1;
    }

    char *new_expression = (char *)calloc(new_expression_length, sizeof(char));

    size_t new_expression_last_index = 0;

    for (int i = 0; i < left_index_of_left_operand - index_for_copy_from_original_expression_delta; i++)
    {
        new_expression[new_expression_last_index] = *((*original_expression) + i);
        new_expression_last_index++;
    }
 
    for (int i = 0; i < number_length; i++)
    {
        new_expression[new_expression_last_index] = result_str[i];
        new_expression_last_index++;
    }

    for (int i = right_index_of_right_operand + 1 + index_for_copy_from_original_expression_delta; i < original_expression_length; i++)
    {
        new_expression[new_expression_last_index] = *((*original_expression) + i);
        new_expression_last_index++;
    }

    free(result_str);
    return (&new_expression);
}

size_t get_number_length(double number, size_t count_of_digits_after_decimal_point)
{
    size_t number_length = 0;
    if (number < 1.0)
    {
        number_length++;
        if (number < 0.0 && number > -1.0)
        {
            number_length++;
        }
        if (number < 0.0)
            number = -number;
    }
    size_t last_index_not_zero = count_of_digits_after_decimal_point - 1;

    double ten_power = (int)pow(10.0, (double)count_of_digits_after_decimal_point);

    int int_and_decimal_part = number * ten_power;
    int int_part = (int)number;

    int digits_of_decimal_part = int_and_decimal_part - int_part * ten_power;
    bool is_weight_zero = false;
    bool is_decimal_part_is_not_zero = (digits_of_decimal_part <= 0) ? false : true;

    while (digits_of_decimal_part != 0)
    {
        int digit = digits_of_decimal_part % 10;
        if (digit == 0 && !is_weight_zero)
        {
            last_index_not_zero--;
        }
        else if (digit != 0)
        {
            is_weight_zero = true;
        }
        digits_of_decimal_part /= 10;
    }
    if (is_decimal_part_is_not_zero)
        number_length += last_index_not_zero + 2;

    while (int_part != 0)
    {
        number_length++;
        int_part /= 10;
    }

    return number_length;
}

void double_to_str(double number, char *dist, size_t count_of_digits_after_decimal_point)
{
    size_t number_length = get_number_length(number, count_of_digits_after_decimal_point);
    size_t last_index_in_dist = 0;
    bool is_weight_zero = false;
    bool is_decimal_part_zero = true;
    size_t right_delta_in_dist = 1;

    if (number < 0.0)
    {
        dist[number_length - right_delta_in_dist] = '-';
        right_delta_in_dist++;
        number = -number;
    }

    int ten_power = pow(10, count_of_digits_after_decimal_point);

    long int int_part = (long int)number;
    if (int_part == 0)
    {
        dist[number_length - right_delta_in_dist] = '0';
    }
    long int int_and_decimal_part = number * ten_power;
    long int decimal_part = int_and_decimal_part - int_part * ten_power;

    size_t decimal_part_length = get_number_length((double)decimal_part, 0);
    int count_of_zero_to_decimal = 0;

    if (decimal_part != 0 && decimal_part_length != count_of_digits_after_decimal_point)
    {
        count_of_zero_to_decimal = count_of_digits_after_decimal_point - decimal_part_length;
    }

    while (decimal_part != 0)
    {
        is_decimal_part_zero = false;
        char digit = (decimal_part % 10) + '0';
        if (digit != '0')
        {
            dist[last_index_in_dist] = digit;
            is_weight_zero = true;
            last_index_in_dist++;
        }
        else
        {
            if (is_weight_zero)
            {
                dist[last_index_in_dist] = digit;
                last_index_in_dist++;
            }
        }
        decimal_part /= 10;
    }

    for (int i = 0; i < count_of_zero_to_decimal; i++)
    {
        dist[last_index_in_dist] = '0';
        last_index_in_dist++;
    }

    if (!is_decimal_part_zero)
    {
        dist[last_index_in_dist] = '.';
        last_index_in_dist++;
    }

    while (int_part != 0)
    {
        char digit = (int_part % 10) + '0';
        dist[last_index_in_dist] = digit;
        last_index_in_dist++;
        int_part /= 10;
    }

    turn_over(dist);
}

bool is_have_next_action(char expression[], int action_index, int right_bracket_index)
{
    size_t expression_length = strlen(expression);

    if (expression_length < right_bracket_index)
    {
        right_bracket_index = expression_length;
    }
    for (int i = action_index + 1; i < right_bracket_index; i++)
    {
        if (is_action(expression[i])) // временное решение
        {
            return true;
        }
    }
    return false;
}

bool is_delete_brackets_pair(char expression[], int left_index_of_left_operand, int right_index_of_right_operand)
{
    if (left_index_of_left_operand != -1 && left_index_of_left_operand != 0)
    {
        if (right_index_of_right_operand < strlen(expression) - 1)
        {
            if (*(expression + left_index_of_left_operand - 1) == '(' && *(expression + right_index_of_right_operand + 1) == ')')
            {
                return true;
            }
        }
    }

    return false;
}

void turn_over(char *str)
{
    char buffer;
    size_t str_len = strlen(str);
    for (int i = 0; i < str_len / 2; i++)
    {
        buffer = str[i];
        str[i] = str[str_len - i - 1];
        str[str_len - i - 1] = buffer;
    }
}

bool is_have_brackets(char *expression)
{
    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == '(')
        {
            return true;
        }
    }
    return false;
}