#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>

//Создание матрицы и заполнение значениями из диапазона
int** createMatrix_r(size_t row, size_t col, int down, int up)
{
    int **ptrM = (int**)calloc(row, sizeof(int*));

    if (ptrM != NULL)
    {
        int val = down;
        bool flagN = false;
        
        for (size_t i = 0; i < row && !flagN; i++)
        {
            ptrM[i] = (int*)calloc(col, sizeof(int));

            if (ptrM[i] != NULL)
            {
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
            else
            {
                for (size_t k = 0; k < i; k++)
                {
                    free(ptrM[k]);
                }
                free(ptrM);
                ptrM = NULL;
                
                flagN = true;
            }
        }

    }

    return ptrM;
}

//Очистка памяти динамической матрицы
bool clearMemory(int** ptrM, size_t row)
{
    bool res = false;

    if (ptrM != NULL)
    {
        for (size_t i = 0; i < row; i++)
        {
            free(ptrM[i]);
        }

        free(ptrM);
        res = true;
    }

    return res;
}

//Вывод матрицы в консоль
bool printMatrix(int** ptrM, size_t row, size_t col)
{
    bool res = false;

    if (ptrM != NULL)
    {
        for (size_t i = 0; i < row; i++)
        {
            if (ptrM[i] != NULL)
            {
                for (size_t j = 0; j < col; j++)
                {
                    printf("%d ", ptrM[i][j]);
                }
                printf("\n");
            }
            else
            {
                printf("NULL ");
                printf("\n");
            }
        }

        res = true;
    }

    return res;
}

int main()
{
    
    size_t row = 3;
    size_t col = 3;

    int **d_Mat = createMatrix_r(row, col, 0, 3);

    bool checkN = printMatrix(d_Mat, row, col);
    if (!checkN)
    {
        printf("Memory was never allocated ");
    }

    clearMemory(d_Mat, row);

    return 0;

}
