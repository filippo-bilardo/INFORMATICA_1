#include "stdio.h"

/**
 * Trovare l'elemento unico in un vettore di interi, se esiste. 
 * Gli altri elementi si ripetono un numero pari di volte.
 * Non possono essere presenti più di un elemento unico.
 */

int singleNumber(int* nums, int numsSize){
    int res = 0;
    for (int i = 0; i < numsSize; i++) {
        res ^= nums[i];
        printf("%x\n", res);
        //stampo in formato binario la variabile res


    }
    return res;
}
int main() {
    int nums1[] = {2, 5, 4, 3, 2, 2, 2}; //Errore tre elementi unici: 5, 4, 3
    int nums2[] = {2, 5, 2, 3, 2, 5, 2}; //Elemento unico: 3
    int numsSize = 7;
    printf("%d\n", singleNumber(nums1, numsSize));
    printf("\n");
    printf("%d\n", singleNumber(nums2, numsSize));
    return 0;
}