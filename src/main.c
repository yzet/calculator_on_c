#include "lib.h"
#include <stdio.h>

int main()
{  
    // double result = calculate_expression("232+22*2^2^2"); // firstly doing 2^(2^2)?
    // result = calculate_expression("24+22*2"); 
    // result = calculate_expression("((24+22)*2)*2"); 
    // result = calculate_expression("((24+22)*2)*(2+2)");
    // result = calculate_expression("24.2+3");
    // result = calculate_expression("2*(2+2)"); 
    // result = calculate_expression("333^2");
    // result = calculate_expression("((24.25+22)*-0.3)*(2.1+2.09)");
    // result = calculate_expression("((7+3)^2)^3+4");
    // result = calculate_expression("(((2+2)*(3-5))^3)+4");
    // result = calculate_expression("((((2+2)*(2+7-3))*(7-3+5/5))*3)+2");
    // //result = calculate_expression("((((9+8)*0.7568)^(8*4)/12))"); // double with e, dont work
    // result = calculate_expression("5^-2");
    
    while ( true )
    {
        char input[257];
        char extra_symbols[257];
        
        fgets(input, 256, stdin);

        if (strlen(input) == 255)
        {
            printf("String is too long\n");
            while ( fgets(extra_symbols, 256, stdin) )
            {
                size_t extra_symbols_length = strlen(extra_symbols);
                if (extra_symbols[extra_symbols_length - 1] == '\n')
                {
                    break;
                }
            }
        }
        else
        {
            if (input[0] == 'q')
            break;
            else
            {
                double result = calculate_expression(input);
                printf("%s%f%c", " = ", result, '\n');
            }
        }
    }

    return 0;
}