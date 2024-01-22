#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"define.h"

void store(product_records PRODUCT[]){
    // we dont need to create a struct, we have already defined a struct in define.h file

    FILE *f = fopen("productdatabase.bin", "wb");
    if (f==NULL){
        printf("file not found");
    }

    for(int i=0; i<100; i++){
        


        fwrite(&PRODUCT[i], sizeof(PRODUCT[i]), (size_t) 1, f);
//we dont need to fwrite all the components of the struct individually in four different fwrite statements
//we simply use the struct variable name , without its members, read its complete size instead of individual members
//otherwise the new element gets overwritten on the first produvt struct

       // fwrite(&PRODUCT[i].product_name, sizeof(char[100]), (size_t) 1, f);
       // fwrite(&PRODUCT[i].price, sizeof(int), (size_t) 1, f);
       // fwrite(&PRODUCT[i].quantity, sizeof(int), (size_t) 1, f);
    }
    fclose(f);
}

void print(product_records PRODUCT[]){
int count = 0;
for (int i =0; i<sizeof(PRODUCT[100])/sizeof(PRODUCT[0]); i++){
while (PRODUCT[count].product_ID!='\0'){
    printf("\n\nPRODUCT %d\n-------------", count+1);

    printf("\n productID %d", PRODUCT[count].product_ID);

    printf("\n product name %s", PRODUCT[count].product_name);

    printf("\n product price %d", PRODUCT[count].price);
   
    printf("\n product quantity %d", PRODUCT[count].quantity);

    /*printf("\n\n");
    */
count++;
if (PRODUCT[count].product_ID=='\0'){   
break;
}
}
    

}
}

void add_new_record(){

FILE *f = fopen("productdatabase.bin", "r");
if (f==NULL) {
    printf("file not found");
}

int productID[100]; //only this is needed, cause if a struct has no productID, this directly means there is no product
//and the struct is empty {0, 0, 0, 0}
product_records PRODUCT[100];
//char productname[100];
//int (*price)[100];
//int (*quantity)[100];

int count=0;
//for(int i =0; i < 5; i++) --instead of '5';...... the entire total elements in array of pdct
for(int i =0; i < 100; i++){
/*
for(int i =0; i < sizeof(PRODUCT[100])/sizeof(PRODUCT[0]); i++){ ❌
RETURNS ERROR - ❗
1
100    0                   

LOOKS LIKE      sizeof(PRODUCT[100])/sizeof(PRODUCT[0]))  does not
return an integer, and hence the loop doesn't iterate, it is stuck to the intial value
'0' and returns only the value at index '0'

only when we use

for(int i =0; i < 100; i++){ , all registered products are shown--
100    0    PRODUCT NO.1
102    1    PRODUCT NO.2
108    2    PRODUCT NO.3
104    3    PRODUCT NO.4
106    4    PRODUCT NO.5

*/



//not 'count', otherwise count declared above will be ignored
fread(&PRODUCT[i], sizeof(PRODUCT[i]), (size_t) 1, f);
while(PRODUCT[count].product_ID!='\0'){
productID[count]=PRODUCT[count].product_ID;
printf("%d    %d\n", productID[count], count);
count++;
if (PRODUCT[count].product_ID=='\0'){   
break;
}
}
}
// and then here, the values will be allocated based on count=0 declared on line 59
//because you declared anouther int count inside for loop, and the while loop nested 
//inside the for loop did not get to iterate the count declared on line 59
//and the 'count' stayed the same and was taken for as it is
//for allocation of new values and since that count = 0; it ended up
//overwriting on the struct at index 0,
printf("TO ADD A NEW PRDUCT RECORD......");
    printf("\nENTER THE PRODUCT ID\n");
    scanf("%d", &PRODUCT[count].product_ID);
    printf("\nENTER THE PRODUCt NAME\n");
    scanf("%s", PRODUCT[count].product_name);
    printf("\nENTER PRODUCT PRICE\n");
    scanf("%d", &PRODUCT[count].price);
    printf("\nENTER PRODUCT QUANTITY\n");
    scanf("%d", &PRODUCT[count].quantity);

//checking , is it getting allocated at the correct index or not
printf("%d  %d  check\n", PRODUCT[count].product_ID, count);
printf("%s  %d  check\n", &PRODUCT[count].product_name, count);
printf("%d  %d  check\n", PRODUCT[count].price, count);
printf("%d  %d  check\n", PRODUCT[count].quantity, count);

print(PRODUCT);
store(PRODUCT);
fclose(f);
}

/*void modify_record(product_records PRODUCT[]){
    //access the file, access which product, then modify(user input), put it at that index, 
    //store the UPDATED file, check if the file has been updated or not

    FILE *f = fopen("productdababase.bin", "rb");
    if (f == NULL) {
        printf("file not found");
    }
int (*productID)[100];
for (int i =0; i <100; i++){
    *productID[i] = PRODUCT[i].product_ID;//pointer that will read the value
    // keep in mind it just needs to read the 
}
    for(int count = 0; count<5; count){
        fread(&productID[count], sizeof(int), (size_t) 1, f);
        printf("%d   %d check\n", productID[count], count);
        //if (productID[count] == '\0')
        //break;
    }


}*/

void main () {
    product_records PRODUCT[100] = { {100, "A", 10, 20}, {101, "B", 15, 25}, {102, "C", 20, 30}}; 
    int a;
    int i;

    printf("welcome to product databse");
    printf("\nto add a new product enter: 1\n to delete a product record enter 2\n, to modify a product enter 3 ");
    scanf("%d", &a);
    printf("%d\n", a);

    while (a != 1 && 2 && 3) {
        printf("error! input not identified \n please enter elements again");
        printf("\nto add a new product enter:1\nto delete a product record enter 2\nto modify a product enter 3");
        scanf("\n %s \n", &a);
    }

    if(a == 1){
        add_new_record();
    }

    /*if(a == 2){
        delete_record(product_records);
    }*/

    /*if(a == 3){
        modify_record(PRODUCT);
    }*/

}