#include <iostream>

void selection_sort(int* num, int tam){
    int i, j, min, aux;
    for(i = 0; i < (tam-1); i++){
        min = i;
        for(j = (i+1); j < tam; j++){
            if(num[j] < num[min]){
                min = j;
            }
        }
        if (i != min){
            aux = num[i];
            num[i] = num[min];
            num[min] = aux;
        }
    }
}

