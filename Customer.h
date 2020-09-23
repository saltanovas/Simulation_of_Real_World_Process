#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED
#include <stdio.h>
#include <math.h>
#include "Queue.h"
#include "PriorityQueue.h"

struct Customer
{
    double loanAmount;
    int term;
    double interestRate;
    double penaltyRate;

    double payment;
    struct Queue* principal;
    struct Queue* interest;
    struct Queue* debtQueue;
    PQueue* debtPQueue;
};

void input(struct Customer *c)
{
    printf("Iveskite paskolos suma: ");
    scanf("%lf", &c->loanAmount);

    printf("Iveskite paskolos termina menesiais: ");
    scanf("%d", &c->term);

    printf("Iveskite metini palukanu procenta: ");
    scanf("%lf", &c->interestRate);

    printf("Iveskite delspinigiu procenta: ");
    scanf("%lf", &c->penaltyRate);
}

struct Customer* make()
{
    struct Customer* customer;
    customer = (struct Customer*) malloc(sizeof(struct Customer));
    customer -> principal = createQueue();
    customer -> interest = createQueue();
    customer -> debtQueue = createQueue();
    customer -> debtPQueue = Sukurti();
    return customer;
}

void createLoanSchedule(struct Customer* c)
{
    printf("\nMenuo\tPaskolos dalis\tPalukanos\tImoka\t\tKredito likutis\n");
    double interest = c->interestRate / 12 / 100;
    double coefficient = (interest * pow((1+interest), c->term)) / (pow((1+interest), c->term) - 1 );
    c->payment = c->loanAmount * coefficient;

    for(int i = 0; i<c->term; i++)
    {
        interest = c->loanAmount * (c->interestRate / 100 / 12);
        double principal = c->payment - interest;
        c->loanAmount = c->loanAmount - principal;

        enqueue(c->interest, interest);
        enqueue(c->principal, principal);

        if(i==c->term-1)
            c->loanAmount=0;

        printf("%d\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\n", i+1, principal, interest, c->payment, c->loanAmount);
    }
    printf("\n");
}

double getMonthlyPayment(int month, struct Customer *c)
{
    double monthlyPayment;
    printf("\nMetas sumoketi %d menesio imoka. Iveskite savo suma: ", month);
    scanf("%lf", &monthlyPayment);
    return monthlyPayment;
}

void firstCheckDebts(double monthlyPayment, struct Customer *c)
{
    double balance = monthlyPayment - c->payment;
    while(!isEmpty(c->debtQueue) && balance >= firstElement(c->debtQueue))
    {
        printf("\nSekmingai padengete ir savo tureta skola: %.2lf", firstElement(c->debtQueue));
        balance = balance - firstElement(c->debtQueue);
        dequeue(c->debtQueue);
    }
}

void firstAddDebts(struct Customer *c)
{
    double penalty = c->payment * c->penaltyRate / 100;
    enqueue(c->debtQueue, c->payment + penalty);
}

void secondCheckDebts(double monthlyPayment, struct Customer *c)
{
    double balance = monthlyPayment - c->payment;
    while(!arTuscia(c->debtPQueue) && balance >= paziuretiDidziausia(c->debtPQueue))
    {
        printf("\nSekmingai padengete ir savo tureta skola: %.2lf", paziuretiDidziausia(c->debtPQueue));
        balance = balance - paziuretiDidziausia(c->debtPQueue);
        IstrintiElementa(c->debtPQueue);
    }
	dequeue(c->principal);
	dequeue(c->interest);
}

void secondAddDebts(struct Customer *c)
{
    double penalty = c->payment * c->penaltyRate / 100;
    idetiElementa(c->debtPQueue, firstElement(c->principal), 3);
    idetiElementa(c->debtPQueue, firstElement(c->interest), 2);
    idetiElementa(c->debtPQueue, penalty, 1);
    dequeue(c->principal);
    dequeue(c->interest);
}

double firstCountDebts(struct Customer *c)
{
    double sum = 0;
    while(!arTuscia(c->debtPQueue))
    {
        sum = sum + paziuretiDidziausia(c->debtPQueue);
        IstrintiElementa(c->debtPQueue);
    }
    istrintiPrioEile(c->debtPQueue);

    return sum;
}

double secondCountDebts(struct Customer *c)
{
    double sum = 0;
    while(!isEmpty(c->debtQueue))
    {
        sum = sum + firstElement(c->debtQueue);
        dequeue(c->debtQueue);
    }
    removeQueue(c->debtQueue);

    return sum;
}

void printAllDebts(struct Customer *c)
{
	if(!isEmpty(c->debtQueue))
	{
		printf("\nPagal pirma strategija: ");
		outputQueue(c->debtQueue);
	}

    if(!arTuscia(c->debtPQueue))
	{
		printf("Pagal antra strategija:");
		spausdintiPrioEile(c->debtPQueue);
	}
}

void payMonthlyPayment(double monthlyPayment, struct Customer *c)
{
    if(monthlyPayment > c->payment)
    {
        firstCheckDebts(monthlyPayment, c);
        secondCheckDebts(monthlyPayment, c);
    }

    else if (monthlyPayment < c->payment)
    {
        printf("\nNeuztenka pinigu, todel turite sias skolas: ");
        firstAddDebts(c);
        secondAddDebts(c);
    }
    printAllDebts(c);
}

void outputConclusion(struct Customer *c)
{
    double sum1 = firstCountDebts(c);
    double sum2 = secondCountDebts(c);

    if(sum1 > sum2)
    {
        printf("\nPirma strategija siuo atveju butu geresne, kadangi turite mazesne skola\n");
    }
    else if(sum1 < sum2)
    {
        printf("\nAntra strategija siuo atveju butu geresne, kadangi turite mazesne skola\n");
    }
    else
    {
        printf("\nSkirtumo tarp strategiju nera, kadangi skolos suma yra vienoda\n");
    }
}


#endif
