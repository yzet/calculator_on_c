#include "lib.h"

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
    //"((7+3)^2)^3+4"
    //"(((2+2)*(3-5))^3)+4"
    //((((2+2)*(2+7-3))*(7-3+5/5))*3)+2;
    
    while ( true )
    {
        char input[255];
        scanf("%s", input);
        if (input[0] == 'q')
            break;
        else
        {
            double result = calculate_expression(input);
            printf("%s%f%c", " = ", result, '\n');
        }
        
    }

    return 0;
}