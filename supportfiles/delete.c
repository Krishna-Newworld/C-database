#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//this is the file for deleting a particular struct
// we will know about how anything is "deleted"
#include"define.h"
int delete(int num){
    //to delete
    //access the array of structs in the binary file
    //how?
    //open the file, and map the struct members to buffervariables
    //perform the overwrite operation on the buffer variables
    //fwrite the new array to the file
    //overwrite it at the index of the selected struct with the next structs

    FILE *f = fopen("productdatabase.bin", "rb+");
//a buffer struct 
product_records PRODUCTDELETE[100];

int productid[100];
char productname[100][100];
int productprice[100];
int productstock[100];

int i = 0;
for (int count = 0; count < 100; count++){
    fread(&PRODUCTDELETE[count], sizeof(PRODUCTDELETE[count]), (size_t) 1, f);
    /*productid[i] = PRODUCTDELETE[i].product_ID;
    strcpy(productname[i],PRODUCTDELETE[i].product_name);
    productprice[i] = PRODUCTDELETE[i].price;
    productstock[i] = PRODUCTDELETE[i].quantity;*/
while (PRODUCTDELETE[i].product_ID != '\0'){
    printf("\nPRODUCT ID : %d", PRODUCTDELETE[i].product_ID);
    printf("\nPRODUCT NAME: %s", &PRODUCTDELETE[i].product_name);
    printf("\nPRODUCT PRICE : %d", PRODUCTDELETE[i].price);
    printf("\nPRODUCT QUANTITY: %d", PRODUCTDELETE[i].quantity);
    i++;
    if (PRODUCTDELETE[i].product_ID == '\0')
    break;
}
}


    fseek(f, sizeof(PRODUCTDELETE[0])*(num-1), SEEK_SET);
for (int count = num; count < 100; count++){
while(PRODUCTDELETE[count-1].product_ID != '\0'){
    PRODUCTDELETE[count-1] = PRODUCTDELETE[count];
    fwrite(&PRODUCTDELETE[count-1], sizeof(PRODUCTDELETE[count-1]), (size_t) 1, f);
    count++;
    if (PRODUCTDELETE[count-1].product_ID == '\0'){
    break;    
    }
}
}

} 


int main(){
product_records PRODUCT[100];
int i = 0;
FILE *fp = fopen("productdatabase.bin", "rb+");
if (fp ==NULL){
    printf("file not found");
    return 1;
}
int productID[100];
int count = 0;
for(int count = 0; count< 100; count++){
//for(int count = 0; count< 5; count++){ --it only showed 5 products, even if there were more
//
    fread(&PRODUCT[count], sizeof(PRODUCT[count]), (size_t) 1, fp);//read the file
    productID[count] = PRODUCT[count].product_ID; 
    if(PRODUCT[count].product_ID=='\0'){
    break;}
    //how to stop mapping buffer values to the products?
//if there is a buffervalue then break
//if there is a null value '\0' then break
    //stop mapping the value if there is none, otherwise bufferoverflow will be mapped
    /*
100   0   PRODUCT NO.1
101   1   PRODUCT NO.2
102   2   PRODUCT NO.3
1379994125   3   PRODUCT NO.4---------------------buffer like this
1836214630   4   PRODUCT NO.5
*/
    //map the values to buffer variables
    //only print till the last ID available and if it is another
}
while(productID[i]!= '\0'){
printf("%d   %d   PRODUCT NO.%d\n", productID[i], i, i+1);
i++;
if(productID[i] == '\0'){
break;
}
}
//TILL HERE CORRECT

printf("\n%d PRODUCTS IN THE DATABASE", i);

int num;
printf("\n CHOOSE A PRODUCT TO DELETE\n");
scanf("%d", &num);
/*since products are market by index starting from zero,
and product number starts from 1, so product with product no. n, will have index n -1*/
printf("\nARE YOU SURE YOU WANT TO DELETE PRODUCT %d\n", num);
printf("\npress 1 to confirm, and 2 cancel\n");
int confirm;
scanf("%d", &confirm);
if (confirm == 1){
    delete(num);
}
else if (confirm == 2){
    printf("\nTHANK YOU\n");
}
else if(confirm != 1 && 2){
    printf("\ninput not identified\n");
}

fclose(fp); //TILL HERE IS CORRECT
}