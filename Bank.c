#include <stdio.h>
#include "Customer.h"

int main(int argc, char* argv[])
{
    struct Customer *customer = make();
    input(customer);
    createLoanSchedule(customer);
    for(int i=0; i<customer->term; i++)
    {
        double monthlyPayment = getMonthlyPayment(i+1, customer);
        payMonthlyPayment(monthlyPayment, customer);
    }
    outputConclusion(customer);
}
