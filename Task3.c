#include <stdio.h>
void reverseArray(int array[], int firstIndex, int secondIndex)
{
    for (int i = firstIndex; i < (secondIndex + firstIndex + 1)/2; i++)
    {
        
        array[i] = array[i] + array[secondIndex + firstIndex - i];
        array[secondIndex + firstIndex - i] = array[i] - array[secondIndex + firstIndex - i];
        array[i] = array[i] - array[secondIndex + firstIndex - i];
    }
}
int main()
{  
    int m;
    int n;
    printf("Enter m: ");
    scanf("%d", &m);
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter array: ");
    int array[1000] = {0};
    for (int i = 0; i < m + n; i++)
        scanf("%d", &array[i]);
    reverseArray(array, 0, m - 1); 
    reverseArray(array, m, m + n - 1);
    reverseArray(array, 0, m + n - 1);
    printf("New array: ");
    for (int i = 0; i < m + n; i++)
        printf("%d ", array[i]);
}