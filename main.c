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

//Перемножение матриц
int** mulMatrix(int** Mat_1, int** Mat_2, size_t row_1, size_t col_1, size_t row_2, size_t col_2)
{
    int **res = NULL;

    if (Mat_1 && Mat_2 && (col_1 == row_2))
    {
        res = (int**)calloc(row_1, sizeof(int*));

        if (res)
        {
            bool flagN = false;
            size_t i;

            for (i = 0; i < row_1 && !flagN; i++)
            {
                res[i] = (int*)calloc(col_2, sizeof(int));

                if (res[i])
                {
                    for (size_t j = 0; j < col_2; j++)
                    {
                        for (size_t k = 0; k < col_1; k++)
                        {
                            if (!(Mat_1[i]) || !(Mat_2[k]))
                            {
                                res[i][j] += 0;
                            }
                            else
                            {
                                res[i][j] += Mat_1[i][k] * Mat_2[k][j];
                            }
                        }
                    }
                }
                else
                {
                    flagN = true;
                }
            }

            if (flagN)
            {
                for (size_t l = 0; l < i; l++)
                {
                    free(res[l]);
                    res[l] = NULL;
                }

                free(res);
                res = NULL;
            }
        }
    }

    return res;
}

//Транспонирование матрицы
int** transMatrix(int** Mat, size_t row, size_t col)
{
    int **res = NULL;

    if (Mat)
    {
        res = (int**)calloc(col, sizeof(int*));

        if (res)
        {
            bool flagN = false;
            size_t i;

            for (i = 0; i < col; i++)
            {
                res[i] = (int*)calloc(row, sizeof(int));

                if (res[i])
                {
                    for (size_t j = 0; j < row; j++)
                    {
                        res[i][j] = Mat[j][i];
                    }
                }
                else
                {
                    flagN = true;
                }
            }

            if (flagN)
            {
                for (size_t k = 0; k < i; k++)
                {
                    free(res[k]);
                    res[k] = NULL;
                }

                free(res);
                res = NULL;
            }
        }
    }

    return res;
}

int main()
{
    size_t row = 10;
    size_t col = 10;

// Тесты для первой части

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

    printf("\n");

// Тесты для второй части
// Перемножение матриц

    size_t row_1 = 3;
    size_t col_1 = 5;

    size_t row_2 = col_1;
    size_t col_2 = 3;

    int **Mat_A = createMatrix_r(row_1, col_1, 2, 5);
    int **Mat_B = createMatrix_r(row_2, col_2, -2, 3);
    
    if (Mat_A && Mat_B)
    {
        int **Mat_C = mulMatrix(Mat_A, Mat_B, row_1, col_1, row_2, col_2);
        //int **Mat_C = mulMatrix(NULL, NULL, row_1, col_1, row_2, col_2);

        printMatrix(Mat_A, row_1, col_1);
        printf("*\n");
        printMatrix(Mat_B, row_2, col_2);
        
        printf("\n");

        checkN = printMatrix(Mat_C, row_1, col_2);
        if (!checkN)
        {
            printf("an error occurred during calculation ");
        }

        clearMemory(&Mat_C, row_1);
    }

    clearMemory(&Mat_A, row_1);
    clearMemory(&Mat_B, row_2);

    printf("\n\n");


    row_1 = 3;
    col_1 = 5;

    row_2 = col_1 + 1;
    col_2 = 3;

    Mat_A = createMatrix_r(row_1, col_1, 2, 5);
    Mat_B = createMatrix_r(row_2, col_2, -2, 3);
    
    if (Mat_A && Mat_B)
    {
        int **Mat_C = mulMatrix(Mat_A, Mat_B, row_1, col_1, row_2, col_2);

        printMatrix(Mat_A, row_1, col_1);
        printf("*\n");
        printMatrix(Mat_B, row_2, col_2);
        
        printf("\n");

        checkN = printMatrix(Mat_C, row_1, col_2);
        if (!checkN)
        {
            printf("an error occurred during calculation ");
        }

        clearMemory(&Mat_C, row_1);
    }

    clearMemory(&Mat_A, row_1);
    clearMemory(&Mat_B, row_2);

    printf("\n\n");


    row_1 = 4;
    col_1 = 5;

    row_2 = col_1;
    col_2 = 2;

    Mat_A = createMatrix_r(row_1, col_1, 2, 5);
    Mat_B = createMatrix_r(row_2, col_2, -2, 3);
    
    if (Mat_A && Mat_B)
    {
        int **Mat_C = mulMatrix(Mat_A, Mat_B, row_1, col_1, row_2, col_2);

        printMatrix(Mat_A, row_1, col_1);
        printf("*\n");
        printMatrix(Mat_B, row_2, col_2);
        
        printf("\n");

        checkN = printMatrix(Mat_C, row_1, col_2);
        if (!checkN)
        {
            printf("an error occurred during calculation ");
        }

        clearMemory(&Mat_C, row_1);
    }

    clearMemory(&Mat_A, row_1);
    clearMemory(&Mat_B, row_2);

    printf("\n\n");

//Перемножение разряженных матриц
    
    row_1 = 4;
    col_1 = 5;

    row_2 = col_1;
    col_2 = 2;

    Mat_A = createMatrix_r(row_1, col_1, 2, 5);
    Mat_B = createMatrix_r(row_2, col_2, -2, 3);
    
    if (Mat_A && Mat_B)
    {
        free(Mat_A[2]);
        Mat_A[2] = NULL;

        free(Mat_B[1]);
        Mat_B[1] = NULL;
        
        int **Mat_C = mulMatrix(Mat_A, Mat_B, row_1, col_1, row_2, col_2);

        printMatrix(Mat_A, row_1, col_1);
        printf("*\n");
        printMatrix(Mat_B, row_2, col_2);
        
        printf("\n");

        checkN = printMatrix(Mat_C, row_1, col_2);
        if (!checkN)
        {
            printf("an error occurred during calculation ");
        }

        clearMemory(&Mat_C, row_1);
    }

    clearMemory(&Mat_A, row_1);
    clearMemory(&Mat_B, row_2);

    printf("\n\n");

//Транспонирование матрицы

    size_t row_3 = 4;
    size_t col_3 = 3;

    int **UnTMat = createMatrix_r(row_3, col_3, 1, 3);

    if (UnTMat)
    {
        int **TMat = transMatrix(UnTMat, row_3, col_3);

        printMatrix(UnTMat, row_3, col_3);

        printf("\n");

        checkN = printMatrix(TMat, col_3, row_3);
        if (!checkN)
        {
            printf("Memory was never allocated ");
        }

        clearMemory(&TMat, col_3);
    }

    clearMemory(&UnTMat, row_3);

    printf("\n\n");

    row_3 = 3;
    col_3 = 4;

    UnTMat = createMatrix_r(row_3, col_3, 1, 3);

    if (UnTMat)
    {
        int **TMat = transMatrix(UnTMat, row_3, col_3);

        printMatrix(UnTMat, row_3, col_3);

        printf("\n");

        checkN = printMatrix(TMat, col_3, row_3);
        if (!checkN)
        {
            printf("Memory was never allocated ");
        }

        clearMemory(&TMat, col_3);
    }

    clearMemory(&UnTMat, row_3);

    return 0;
}