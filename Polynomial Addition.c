#define _CRT_SECURE_NO_WARNINGS /* To use scanf function instead of scanf_s */
#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 100 /* Bound the the number of the terms with 100 */
#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1 )
typedef struct {
	float coef;
	int expon;
} poly;
poly terms[MAX_TERM];
int avail = 0, startA, endA, startB, endB, startC, endC, i;
void padd(int startA, int endA, int startB, int endB);
void attach(float coefficient, int exponent);

int main(void) {

	/* Scan the first polynomial A(x) */

	printf("첫번째 다항식을 입력하세요.\n");
	float *parr = NULL; /* An array that will temporarily store values for the terms from users */
	int count = 0, s = 2;
	i = 0;
	parr = (float *)malloc(s * sizeof(float));
	while (1) {
		++count;
		if (count > 2) {
			s += 2;
			parr = (float*)realloc(parr, s * sizeof(float));
			count = 1;
		} /* Everytime the user enters more numbers than the size of array, add two more spaces for a coefficient and an exponent */
		scanf("%f", &parr[i]);
		if (parr[i] == 0 && (i % 2) == 1) break; /* If the user enters an exponent which is value of 0, end the process */
		i++;
	}
	startA = avail;

	if (parr[s - 2] == 0 && parr[s - 1] == 0) { /*Checing whether the last input is '0 0' If so, discard it*/
		avail = avail + ((s - 2) / 2);
		if (avail >= MAX_TERM) {
			fprintf(stderr, "최대 입력 범위 초과\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		avail = avail + (s / 2);
		if (avail >= MAX_TERM) {
			fprintf(stderr, "최대 입력 범위 초과\n");
			exit(EXIT_FAILURE);
		}
		terms[(s - 2) / 2 + startA].coef = parr[s - 2];
		terms[(s - 1) / 2 + startA].expon = (int)parr[s - 1]
	}

	for (i = 0; i <= s - 3; i++) /* In parr, coefficients are stored in indices with even number and exponents with odd number */
	{
		if (i % 2 == 0) {
			terms[(i / 2) + startA].coef = parr[i];
		}
		if (i % 2 == 1) {
			terms[(i / 2) + startA].expon = (int)parr[i];
		}
	}

	fflush(stdin);
	free(parr);
	endA = avail - 1;
	/* End of scanning polynomial A(x) */


	/* Scan the second polynomial B(x) */
	printf("두번째 다항식을 입력하세요.\n");

	count = 0, s = 2, i = 0;
	parr = (float *)malloc(s * sizeof(float));
	while (1) {
		++count;
		if (count > 2) {
			s += 2;
			parr = (float*)realloc(parr, s * sizeof(float));
			count = 1;
		}
		scanf("%f", &parr[i]);
		if (parr[i] == 0 && (i % 2) == 1) break;
		i++;
	}
	startB = avail;

	if (parr[s - 2] == 0 && parr[s - 1] == 0) {
		avail = avail + ((s - 2) / 2);
		if (avail >= MAX_TERM) {
			fprintf(stderr, "최대 입력 범위 초과\n");
			exit(EXIT_FAILURE);
		}
	}
	else {
		avail = avail + (s / 2);
		if (avail >= MAX_TERM) {
			fprintf(stderr, "최대 입력 범위 초과\n");
			exit(EXIT_FAILURE);
		}
		terms[(s - 2) / 2 + startB].coef = parr[s - 2];
		terms[(s - 1) / 2 + startB].expon = (int)parr[s - 1]
	}

	for (i = 0; i <= s - 3; i++)
	{
		if (i % 2 == 0) {
			terms[(i / 2) + startB].coef = parr[i];
		}
		if (i % 2 == 1) {
			terms[(i / 2) + startB].expon = (int)parr[i];
		}
	}

	fflush(stdin);
	free(parr);
	endB = avail - 1;

	/* End of scanning polynomial B(x) */

	padd(startA, endA, startB, endB); /* Add A(x) and B(x) */

	/* Print the first term of C(x) */
	printf("%.3fx^%d ", terms[startC].coef, terms[startC].expon);
	/*Print normal terms of C(x)*/
	for (i = startC + 1; i < avail - 1; i++) {
		if (terms[i].coef < 0) {
			printf("- %.3fx^%d ", -(terms[i].coef), terms[i].expon);
		}
		else printf("+ %.3fx^%d ", terms[i].coef, terms[i].expon);
	}

	/*Print the last term of C(x)*/
	if (terms.[avail - 1].expon = !0) {
		if (terms[i].coef < 0) {
			printf("- %.3fx^%d ", -(terms[i].coef), terms[i].expon);
		}
		else printf("+ %.3fx^%d ", terms[i].coef, terms[i].expon);
	}
	else if (terms.[avail - 1].expon == 0) {
		if (terms[i].coef < 0) {
			printf("- %.3f ", -(terms[i].coef));
		}
		else printf("+ %.3f ", terms[i].coef);
	}
	return 0;
}

void padd(int startA, int endA, int startB, int endB)
{ /* Add A(x) and B(x) to obtain C(x) */
	float coefficient;
	startC = avail;
	while (startA <= endA && startB <= endB)
		switch (COMPARE(terms[startA].expon, terms[startB].expon))
		{
		case -1: /* A expon < B expon */
			attach(terms[startB].coef, terms[startB].expon);
			startB++;
			break;
		case 0: /* Equal exponents */
			coefficient = terms[startA].coef + terms[startB].coef;
			if (cefficient) {
				attach(coefficient, terms[startA].expon);
			}
			startA++;
			startB++;
			break;
		case 1: /* A expon > B expon */
			attach(terms[startA].coef, terms[startA].expon);
			startA++;
		} /* End of switch */
	/* Add in remaining terms of A(x) */
	for (; startA <= endA; startA++)
	{
		attach(terms[startA].coef, terms[startA].expon);
	}
	/* Add in remaining terms of B(x) */
	for (; startB <= endB; startB++)
	{
		attach(terms[startB].coef, terms[startB].expon);
	}
	endC = avail - 1;

}

void attach(float coefficient, int exponent)
{
	/* Add a new term to the polynomial */
	if (avail >= MAX_TERM)
	{
		fprintf(stderr, "최대 입력 범위 초과\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}