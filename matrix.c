#include<stdio.h>
#define max_rows 100
#define max_cols 100
void read_matrix(int matrix[max_rows][max_cols], int *rows, int *cols){
    printf("enter no of rows and cols ");
    scanf("%d  %d", rows, cols);
    printf("enter elements\n");
    for(int i=0;i<*rows;i++){
        for(int j=0; j<*cols; j++){
             scanf("%d", &matrix[i][j]);
        }
    }

}
void print_matrix(int matrix[max_rows][max_cols], int rows, int cols){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            printf(" %d ", matrix[i][j]);
        }
        printf("\n");
    }
}
void transpose_matrix(int matrix[max_rows][max_cols], int transpose[max_cols][max_rows],int rows , int cols){
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
}
int main(){
    int rows, cols;
    int matrix[max_rows][max_cols];
    int transpose[max_rows][max_cols];
    read_matrix(matrix, &rows, &cols);
    printf("\n");
    print_matrix(matrix, rows, cols);
    transpose_matrix(matrix, transpose, rows, cols);
    printf("\n");
    print_matrix(transpose, cols, rows);
    return 0;
}