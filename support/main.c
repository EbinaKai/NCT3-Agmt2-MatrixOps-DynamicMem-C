// IT3 08 蝦名海 2022/04/15 行列の積の計算 -support-
#include <stdio.h>
#include <stdlib.h>

int main (void) {
    int l, m, n;
    double **a, **b, **z;  // 行列A, B, Z
    int i, j, k;
    
    printf("行列Aの行の数を入力してください: ");
    scanf("%d", &l);
    printf("行列Aの列,行列Bの行の数を入力してください: ");
    scanf("%d", &m);
    printf("行列Bの列の数を入力してください: ");
    scanf("%d", &n);

    // 行列A
    // 行の確保：ポインタ配列
    a = (double **)malloc(l * sizeof(double *)); 
    // 列の確保
    for (j = 0; j < l; j++) {
        a[j] = (double *)malloc(m * sizeof(double));
    }

    // 行列B
    // 行の確保：ポインタ配列
    b = (double **)malloc(m * sizeof(double *));
    // 列の確保
    for (j = 0; j < m; j++) {
        b[j] = (double *)malloc(n * sizeof(double));
    }

    // 行列Z
    // 行の確保：ポインタ配列
    z = (double **)malloc(l * sizeof(double *));
    // 列の確保
    for (j = 0; j < l; j++) {
        z[j] = (double *)malloc(n * sizeof(double));
    }

    // 入力
    printf("行列Aを入力してください\n");
    for (j = 0; j < l; j++) {
        for (i = 0; i < m; i++) {
            printf("a[%d][%d] = ", j, i);
            scanf("%lf", &a[j][i]);
        }
    }
    printf("行列Bを入力してください\n");
    for (j = 0; j < m; j++) {
        for (i = 0; i < n; i++) {
            printf("b[%d][%d] = ", j, i);
            scanf("%lf", &b[j][i]);
        }
    }

    // 行列の積：Z = A * B
    for (j = 0; j < n;j ++) {
        for (i = 0; i < l;i ++) {
            // 出力関数の初期化
            z[i][j] = 0;
            for (k = 0; k < m;k ++) {
                z[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    // 出力
    printf("A * B = \n"); 
    for (j = 0; j < l; j++) {
        for (i = 0; i < n; i++) {
            printf("%5.2f ", z[j][i]);
        }
        printf("\n");
    }

    // 領域の解放
    for (j = 0; j < m; j++) {
        free(a[j]);
    }
    free(a);
    for (j = 0; j < n; j++) {
        free(b[j]);
    }
    free(b);
    for (j = 0; j < n; j++) {
        free(z[j]);
    }
    free(z);
    
    return 0;
}
