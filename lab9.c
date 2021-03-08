#include <stdio.h>
#include <stdlib.h>

#define LENGTH 3

typedef int matrix[3][3];

void input_matrix(int ** a, char name);
void matrix_multiply (int ** a, int ** b, int ** result);
void output_matrix (int ** m, char name);

int main (void) {
    matrix a;
    matrix b;
    matrix c;

    printf("Spaces denote the seperation of numbers in a row.\n");

    input_matrix((int **)a, 'A');
    input_matrix((int **)b, 'B');

    output_matrix((int **)a, 'A');
    output_matrix((int **)b, 'B');
    printf("If C = AB, then ");
    matrix_multiply((int **)a, (int **)b, (int **)c);
    output_matrix((int **)c, 'C');

    return 0;
}

void input_matrix(int ** a, char name) {
    int i;
    for (i = 0; i < 3; i++) {
        *(a + i) = (int *)malloc(3 * sizeof(int));
        printf("Enter row %d of matrix %c: ", i + 1, name);
        scanf("%d %d %d", (*(a+i)), (*(a+i)+1), (*(a+i)+2));
    }
    printf("\n");
}

void matrix_multiply (int ** a, int ** b, int ** result) {
    int i, j, k, sum;
    int m, n;
    for (i = 0; i < 3; i++) {
        *(result + i) = (int *)malloc(3 * sizeof(int));
        for (j = 0; j < 3; j++) {
            sum = 0;
            for (k = 0; k < 3; k++) {
                m = *(*(a+i)+k);
                n = *(*(b+k)+j);
                sum += (n * m);
            }
            *(*(result + i) + j) = sum;
        }
    }
}

void output_matrix (int ** m, char name) {
    int i, j;
    printf("matrix %c is:\n", name);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d\t", *(*(m+i)+j));
        }
        printf("\n");
    }
}
