// IT3 08 蝦名海 2022/04/15 行列の積の計算 -develop-
#include <stdio.h>
#include <stdlib.h>

double **dma(int row,int col);  // dynamic memory allocation
void getMatrix(double **matrix, int row, int col);
void makeIdentityMatrix(double **matrix, int n);
int calcInverse(double **a, double **inverse, int n);   //正則ではない場合は0を返す
void printMatrix(double **matrix, int n, int l);
void freeMatrix(double **matrix, int row);

int main (void) {
    int n;
    double **a, **inverse;
    
    // 行列のサイズを入力
    do {
        printf("行列の次数を入力してください: ");
        scanf("%d", &n);
    } while(n < 0);

    // 動的メモリ確保
    a = dma(n, n);       // 行列A
    inverse = dma(n, n); // 行列Inverse

    // 入力
    printf("行列を入力してください\n");
    getMatrix(a, n, n);

    // 逆行列の計算
    if (calcInverse(a, inverse, n)) {
        printf("A^-1 = \n"); 
        printMatrix(inverse, n, n); // 出力
    } else {
        printf("入力された行列は正則ではありません。\n");
    }

    // 領域の解放
    freeMatrix(a, n);
    freeMatrix(inverse, n);
    
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
            // 入力
            printf("[%d][%d] = ", j, i);
            scanf("%lf", &matrix[j][i]);
        }
    }
}

void makeIdentityMatrix(double **matrix, int n) {
    for (int row=0; row<n; row++) {
        // 単位行列を作成
        for (int col=0; col<n; col++) {
            if (row == col) {
                matrix[row][col] = 1;
            } else {
                matrix[row][col] = 0;
            }
        }
    }
}

int calcInverse(double **a, double **inverse, int n) {
    double coef = 0;    //係数

    // 単位行列の作成
    makeIdentityMatrix(inverse, n);
    
    for (int j=0; j<n; j++) {
        // 対角成分が0の場合
        if (a[j][j] == 0) {
            for (int i=j; i<n; i++){
                if (a[j][i] == 0) {
                    // 行がすべて0の場合は正則ではない
                    if (i == n-1) return 0;
                    continue;
                }
                for (int k=0; k<n; k++) {
                    // 他の列を加算
                    inverse[k][j] += inverse[k][i];
                    a[k][j] += a[k][i];
                }
                break;
            }
        }

        // 対角成分を1に変換
        coef = a[j][j];
        for (int i=0; i<n; i++){
            inverse[j][i] /= coef;
            a[j][i] /= coef;
        }

        // 対角成分以外を0に変換
        for (int i=0; i<n; i++){
            if (i==j) continue;
            coef = a[i][j];
            for (int k=0; k<n; k++) {
                inverse[i][k] -= inverse[j][k] * coef;
                a[i][k] -= a[j][k] * coef;
            }
        }
    }
    return 1;   // 計算終了
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
