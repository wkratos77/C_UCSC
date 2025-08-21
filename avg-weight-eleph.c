#include <stdio.h>

int main() {
    FILE *file;
    int weight;
    double sum = 0.0;
    int count = 0;
    file = fopen("elephant_seal_data.txt", "r"); 
    if (file == NULL) 
    {
        printf("Error \n");
        return 1;
    }
    while (fscanf(file, "%d", &weight) == 1){
        sum += weight;
        count++;
    }
    fclose(file);
    if (count == 0)
    {
        printf("empty file\n");
        return 1;
    }

    double average = sum / count;
    printf("Number of elephant seals: %d\n", count);
    printf("Average weight: %.2f\n", average);

    return 0;
}