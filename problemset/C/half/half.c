// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    float half;
    half = bill_amount + (bill_amount * (tax_percent / 100));
    half = half + (half * ((float)tip_percent / 100));
    half = half / 2;


    printf("You will owe $%.2f each!\n", half);
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    return 0.0;
}