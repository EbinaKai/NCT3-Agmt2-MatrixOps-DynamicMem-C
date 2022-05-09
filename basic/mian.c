// IT3 08 蝦名海 2022/04/15 行列の積の計算 -basic-
#include <stdio.h>
#include <stdlib.h>

double **dma(int row,int col);  // dynamic memory allocation
void getMatrix(double **matrix, int row, int col);
void calProduct(double **a, double **b, double **z, int l, int m, int n);
void printMatrix(double **matrix, int n, int l);
void freeMatrix(double **matrix, int row);

int main (void) {
    int l, m, n;
    double **a, **b, **z;  // 行列A, B, Z
    
    // 行列のサイズを入力
    printf("行列Aの行の数を入力してください: ");
    scanf("%d", &l);
    printf("行列Aの列,行列Bの行の数を入力してください: ");
    scanf("%d", &m);
    printf("行列Bの列の数を入力してください: ");
    scanf("%d", &n);

    // 動的メモリ確保
    a = dma(l, m);  // 行列A
    b = dma(m, n);  // 行列B
    z = dma(l, n);  // 行列Z

    // 入力
    printf("行列Aを入力してください\n");
    getMatrix(a, l, m);
    
    printf("行列Bを入力してください\n");
    getMatrix(b, m, n);

    // 行列の積：Z = A * B
    calProduct(a, b, z, l, m, n);

    // 出力
    printf("A * B = \n"); 
    printMatrix(z, n, l);

    // 領域の解放
    freeMatrix(a, m);
    freeMatrix(b, n);
    freeMatrix(z, l);
    
    return 0;
}

double **dma(int row, int col) {
    // 行の確保：ポインタ配列
    double **matrix;
    matrix = (double **)malloc(row * sizeof(double *));

    // 列の確保
    for (int i = 0; i < row; i++) {
        matrix[i] = (double *)malloc(col * sizeof(double));
    }

    return matrix;
}

void getMatrix(double **matrix, int row, int col){
    for (int j = 0; j < row; j++) {
        for (int i = 0; i < col; i++) {
            printf("[%d][%d] = ", j, i);
            scanf("%lf", &matrix[j][i]);
        }
    }
}

void calProduct(double **a, double **b, double **z, int l, int m, int n) {
    for (int j = 0; j < n;j ++) {
        for (int i = 0; i < l;i ++) {
            // 出力関数の初期化
            z[i][j] = 0;
            for (int k = 0; k < m;k ++) {
                z[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void printMatrix(double **matrix, int n, int l) {
    for (int j = 0; j < l; j++) {
        for (int i = 0; i < n; i++) {
            printf("%5.2f ", matrix[j][i]);
        }
        printf("\n");
    }
}

void freeMatrix(double **matrix, int row) {
    for (int j = 0; j < row; j++) {
        free(matrix[j]);
    }
    free(matrix);
}
