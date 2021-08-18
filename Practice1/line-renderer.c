#include<stdio.h> 
#include<math.h>

struct point
{
    float x, y; 
}; 

typedef struct point point; 

int main()
{
    point start, end; 
    int matrix[101][101]; 

    for(int i = 0; i < 101; i++) 
        for(int j = 0; j < 101; j++) 
            matrix[i][j] = 0; 

    scanf("%f", &start.x);
    scanf("%f", &start.y); 
    scanf("%f", &end.x); 
    scanf("%f", &end.y); 

    float x_diff = fabs(start.x - end.x) + 1; 
    float y_diff = fabs(start.y - end.y) + 1; 
    
    int large = x_diff > y_diff ? 0 : 1; 

    float max_diff = fmax(x_diff, y_diff); 
    float min_diff = fmin(x_diff, y_diff); 
    
    float div = max_diff/min_diff; 
    int div_i = max_diff/min_diff; 

    float dec_part = div - div_i; 
    int cnt = dec_part*min_diff; 
    
    printf("%d", div_i); 

    if(large == 1) 
    {
        
    }


    return 0; 
}
