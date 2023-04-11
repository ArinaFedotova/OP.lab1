#ifndef OPERATIONS_H
#define OPERATIONS_H
#define ERROR_NUM 12345e-99

struct operators{
    double num1;
    double num2;
    char* operation;
};

double execute(struct operators operators);


#endif // OPERATIONS_H
