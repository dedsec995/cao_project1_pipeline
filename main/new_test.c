// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// /*
//  * This function read memory map and return the value at ith position 
//  */
// int
// load_the_memory(int num){
//     num = num/4;
//     char *filename = "../programs/memory_map.txt"; 
//     FILE *filePointer = fopen(filename, "r");
//     int county = 0;
//     int n;
//     if (filePointer == NULL)
//     {
//         printf("Error: could not open file %s", filename);
//     }
//     while (fscanf(filePointer, " %d", &n) == 1) {
//         if((num) == county){
//             fclose(filePointer);
//             return n;
//         }
//         county++;
//     }
//     fclose(filePointer);
//     return (-1);
// }
// int main(){
//     printf("%d\n",load_the_memory(2572));
//     return(0);
// }