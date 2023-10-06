#include <stdio.h>
#include <stdlib.h>


typedef struct PolynomialTerm {
    int coefficient;
    int exponent;
    struct PolynomialTerm* next;
} PolynomialTerm;


void insertTerm(PolynomialTerm** poly, int coef, int exp) {
    PolynomialTerm* newTerm = (PolynomialTerm*)malloc(sizeof(PolynomialTerm));
    if (newTerm == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newTerm->coefficient = coef;
    newTerm->exponent = exp;
    newTerm->next = *poly;
    *poly = newTerm;
}


PolynomialTerm* readPolynomial() {
    PolynomialTerm* poly = NULL;
    int coef, exp;
    char choice;

    do {
        printf("Enter coefficient and exponent (e.g., 2 3): ");
        scanf("%d %d", &coef, &exp);
        insertTerm(&poly, coef, exp);

        printf("Do you want to add another term? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');

    return poly;
}


PolynomialTerm* addPolynomials(PolynomialTerm* poly1, PolynomialTerm* poly2) {
    PolynomialTerm* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent > poly2->exponent) {
            insertTerm(&result, poly1->coefficient, poly1->exponent);
            poly1 = poly1->next;
        } else if (poly1->exponent < poly2->exponent) {
            insertTerm(&result, poly2->coefficient, poly2->exponent);
            poly2 = poly2->next;
        } else {
            int sum = poly1->coefficient + poly2->coefficient;
            if (sum != 0) {
                insertTerm(&result, sum, poly1->exponent);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertTerm(&result, poly1->coefficient, poly1->exponent);
        poly1 = poly1->next;
    }

    while (poly2 != NULL) {
        insertTerm(&result, poly2->coefficient, poly2->exponent);
        poly2 = poly2->next;
    }

    return result;
}


void displayPolynomial(PolynomialTerm* poly) {
    PolynomialTerm* current = poly;
    while (current != NULL) {
        printf("%dx^%d ", current->coefficient, current->exponent);
        if (current->next != NULL) {
            printf("+ ");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    printf("Enter the first polynomial:\n");
    PolynomialTerm* poly1 = readPolynomial();

    printf("Enter the second polynomial:\n");
    PolynomialTerm* poly2 = readPolynomial();

    PolynomialTerm* result = addPolynomials(poly1, poly2);

    printf("Resultant polynomial: ");
    displayPolynomial(result);


    free(poly1);
    free(poly2);
    free(result);

    return 0;
}
