//defining the struct
#include<stdio.h>
#include<string.h>

typedef struct record { 
    int product_ID;
    char product_name[100];
    int price;
    int quantity;
}product_records;
// we are gonna use this definition to read to a struct when its stored in binary file