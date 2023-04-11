#include "operations.h"
#include <iostream>
#include <cmath>

double do_operat(struct operators operators);

double do_trig_operat(struct operators operators);

double do_exponent_operat(struct operators operators);

double execute(struct operators operators){
    double result = 0;
    std::string operate = operators.operation;
    if (operate == "+" || operate == "-" || operate == "x" || operate == "/" ){
        result = do_operat(operators);
    }else if (operate == "sin" || operate == "cos" || operate == "tg" || operate == "ctg"){
        result = do_trig_operat(operators);
    }else
        result = do_exponent_operat(operators);
    return result;
}

double do_operat(struct operators operators){
    double result = 0;
    std::string operate = operators.operation;
    if (operate == "+")
        result = operators.num1 + operators.num2;
    else if (operate == "-")
        result = operators.num1 - operators.num2;
    else if (operate == "x")
        result = operators.num1 * operators.num2;
    else if (operate == "/"){
        if (operators.num2 == 0)
            result = ERROR_NUM;
        else
            result = operators.num1 / operators.num2;
    }
    return result;
}

double do_trig_operat(struct operators operators){
    double result = 0;
    std::string operate = operators.operation;
    if (operate == "sin")
        result = sin(operators.num1);
    else if (operate == "cos")
        result = cos(operators.num1);
    else if (operate == "tg")
        if (cos(operators.num1) == 0)
            result = ERROR_NUM;
        else
            result = tan(operators.num1);
    else if (operate == "ctg"){
        if (operators.num1 != 0)
            result = 1/tan(operators.num1);
        else
            result = ERROR_NUM;
    }
    return result;
}

double do_exponent_operat(struct operators operators){
    double result = 0;
    std::string operate = operators.operation;

    if (operate == "x^2")
        result = operators.num1 * operators.num1;
    else if (operate == "sqrt") {
        if (operators.num1 < 0)
            result = ERROR_NUM;
        else
            result = pow(operators.num1, 0.5);
    }
    return result;
}
