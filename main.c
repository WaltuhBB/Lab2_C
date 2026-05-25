#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <malloc.h>

//Создание матрицы и заполнение значениями из диапазона
int** createMatrix_r(size_t row, size_t col, int down, int up)
{
    int **ptrM = NULL;
    
    if (row && col)
    {
        ptrM = (int**)calloc(row, sizeof(int*));

        if (ptrM)
        {
            int val = down;
            bool flagN = false;
            
            for (size_t i = 0; i < row && !flagN; i++)
            {
                ptrM[i] = (int*)calloc(col, sizeof(int));

                if (ptrM[i])
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
                        ptrM[k] = NULL;
                    }
                    free(ptrM);
                    ptrM = NULL;
                    
                    flagN = true;
                }
            }
        }
    }

    return ptrM;
}

//Очистка памяти динамической матрицы
void clearMemory(int*** ptrM, size_t row)
{
    if (ptrM && *ptrM)
    {
        for (size_t i = 0; i < row; i++)
        {
            free((*ptrM)[i]);
            (*ptrM)[i] = NULL;
        }

        free(*ptrM);
        *ptrM = NULL;
    }
}

//Вывод матрицы в консоль
bool printMatrix(int** ptrM, size_t row, size_t col)
{
    bool res = false;

    if (ptrM != NULL)
    {
        for (size_t i = 0; i < row; i++)
        {
            if (ptrM[i])
            {
                for (size_t j = 0; j < col; j++)
                {
                    printf("%d ", ptrM[i][j]);
                }
                printf("\n");
            }
            else
            {
                printf("NULL\n");
            }
        }

        res = true;
    }

    return res;
}

int main()
{
    
    size_t row = 10;
    size_t col = 10;

    //Нулевой указатель на первую строку матрицы
    //int **d_Mat = NULL;

    //динамическая матрица со значениями из дипазона
    int **d_Mat = createMatrix_r(row, col, 0, 3);

    //получение разреженной матрицы
    if (d_Mat)
    {
        free(d_Mat[1]);
        d_Mat[1] = NULL;
    }

    bool checkN = printMatrix(d_Mat, row, col);
    if (!checkN)
    {
        printf("Memory was never allocated ");
    }

    clearMemory(&d_Mat, row);

    return 0;

}
