#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

int** createMatrix_r(size_t row, size_t col, int down, int up)
{

    int **ptrM = (int**)calloc(row, sizeof(int*));

    int val = down;
    for (size_t i = 0; i < row; i++)
    {
        ptrM[i] = (int*)calloc(col, sizeof(int));

        for (size_t j = 0; j < col; j++)
        {
            ptrM[i][j] = val;
            val++;

            if (val > up)
            {
                val = down;
            }
        }
    }

    return ptrM;

}

int main()
{
    
    int **d_Mat = createMatrix_r(3, 3, 0, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", d_Mat[i][j]);
        }
        printf("\n");

        free(d_Mat[i]);
    }

    free(d_Mat);

    return 0;
}
