#include <stdio.h>
int main()
{
    int total_elements, element;
    printf("Enter number of elements: ");
    scanf("%d", &total_elements);
    int arr[total_elements];
    printf("Enter the elements: ");
    for(int i=0; i<total_elements; i++)
    {
        scanf("%d", &element);
        arr[i] = element;
    }
    printf("Printing the array elements:\n ");

    for(int j=0; j<total_elements; j++)
    {
        printf("%d ", arr[j]);
    }
    return 0;
}

