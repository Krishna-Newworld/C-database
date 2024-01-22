#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "define.h"  //to include the struct that has been defined

//--------------------------------------------------------------------------------------------
void takesquantity(int *quantities){
printf("\nto edit PRODUCT QUANTITY enter 1, else enter 2\n");
int selectprodquantity;
scanf("%d", &selectprodquantity);
if (selectprodquantity == 1){
    int stock;
    printf("\nENTER A NEW PRODUCT QUANTITY\n");
    scanf("%d", &stock);
    *quantities = stock;
}
else if (selectprodquantity == 2){
    printf("\nTHANK YOU\n");    
}
//else { ----- WRONG 
else { // ----- RIGHT
while(selectprodquantity != 1 && selectprodquantity != 2){  //here '||'->wrong; '&&'->right
    printf("\ninput not indentified\n");
    takesquantity(quantities);
}
}
}

void takesprice(int *prices){
    //PRODUCT PRICE
printf("\nto edit PRODUCT PRICE enter 1, else enter 2\n");
int selectprodprice;
    scanf("%d", &selectprodprice);
if (selectprodprice==1){
    int pricex;
    printf("\nENTER A NEW PRODUCT PRICE\n");
    scanf("%d", &pricex);
    *prices = pricex;
}
else if (selectprodprice == 2){
    printf("\nto edit PRODUCT QUANTITY enter 1, else enter 2\n");
}
else {
while(selectprodprice != 1 && selectprodprice != 2){
    printf("\ninput not indentified\n");
    takesprice(prices);
}
}
}

//I think i might have to perform recursion on it
void takesname(char *editname){
    printf("\nto edit PRODUCT NAME press 1, else press 2\n");
int selectprodname;
    scanf("%d", &selectprodname);
if(selectprodname == 1){
    printf("\nENTER A NEW PRODUCT NAME\n");
    scanf("%s", editname);
    //--we used the edit conversion tool %[^\n]s 
}
else if(selectprodname == 2){
    printf("\nto edit PRODUCT PRICE enter 1, else enter 2\n");
}
else {
while(selectprodname != 1 && selectprodname != 2){
    printf("\ninput not indentified\n");
    takesname(editname);
}
}   
}

void takesID(int *identity){
//PRODUCT ID
printf("\nto edit PRODUCT ID press 1, else press 2\n");
int selectprodID;
    scanf("%d", &selectprodID);
if(selectprodID == 1){
    int numberID;
    printf("\nenter a new product ID\n");
    scanf("%d", &numberID);
    *identity = numberID;
}
else if (selectprodID == 2){
    printf("\nto edit PRODUCT NAME press 1, else press 2\n");
}
else {
while(selectprodID != 1 && selectprodID != 2){
    printf("\ninput not identified\n");
    takesID(identity);

}
}
}

//-------------------------------------------------------------------------------------------------

int main(){
product_records PRODUCT[100]; //i declare 100 PRODUCTS STRUCTS of type product records

    FILE *f = fopen("productdatabase.bin", "r");
    if (f == NULL) {
        printf("file not found");
    }
int productID[100];
int i = 0;
//this i is the index value 
for(int count = 0; count<100; count++){
//100 because the array of products size 100
//and if we use '5', then it only shows 5 product values, even when there are more
//that 5 was only used, until we were developing the code, now its not needed.
    fread(&PRODUCT[count], sizeof(PRODUCT[count]), (size_t) 1, f);
    productID[count] = PRODUCT[count].product_ID;
       
//to identify the number of products
while (productID[i] !='\0'){
    printf("%d    %d    PRODUCT NO.%d\n", productID[i], i, i+1); //checking
    i++;
if (productID[i] =='\0')   
    break;
} 
}

printf("\n%d PRODUCTS AVAILABLE\n", i);
printf("FOR MODIFICATION OF PRODUCT DETAILS ENTER THE PRODUCT NUMBER ->     ");
int num;//the number of the product = input - 1, since index starts from 0.
scanf("%d", &num);

printf("\nTHE CONTENTS OF PRODUCT %d\n", num);
printf("\nPRODUCT ID :       %d", PRODUCT[num-1].product_ID);
printf("\nPRODUCT NAME :     %s", &PRODUCT[num-1].product_name);
printf("\nPRODUCT PRICE :    %d", PRODUCT[num-1].price);
printf("\nPRODUCT QUANTITY : %d", PRODUCT[num-1].quantity);



//the goal is to without even changing anything, just access the members of a particular struct and 
//write new data to them and save it

int editedproductID;
char editedproductname[100];
int editedprice;
int editedquantity;

/*int *ID = &editedproductID;
int *Dollar = &editedprice;
int *STOCK = &editedquantity;
*/

takesID(&editedproductID);
takesname(editedproductname);
takesprice(&editedprice);
takesquantity(&editedquantity);

/*to take value from user and
bring a value from outside of the main function to inside the main function
declare a pointer to the variable in the argument of the function outside "main"

void function(type(int,char etc) *pointer)

then define a variable in that function to store the value
int variable;
scanf("%d", &variable), then assign the variable to the pointer
*pointer = variable; --->this will make 'variable' point to the address at which 
the '*pointer' is pointing at. which in this case is......
//                                                       |
inside the main function,                                |
function(&originalvariable)----------<-------------HERE<--
*/



printf("\n%d  check", editedproductID); //currently this has 0 value
printf("\n%s check", &editedproductname); //this has the updated "SEXYABABE"
printf("\n%d check", editedprice); //This has '0' value
printf("\n%d check", editedquantity); // this has '32758' buffer value


//the problem is that in both call by value and call by reference
/* we took the value of the variable from the user........in the 'main' function and
then just used the 'swap' function to swap the values, using the arguments declared in the
'swap' function as decoy containers

however here the difference is that we are taking the value of the variable from
the 'void' function, and using it in 'main', HOW to do that?

*/
PRODUCT[num-1].product_ID = editedproductID;
strcpy(PRODUCT[num-1].product_name, editedproductname);
PRODUCT[num-1].price = editedprice;
PRODUCT[num-1].quantity = editedquantity;

FILE *fp = fopen("productdatabase.bin", "rb+");
if (fp == NULL){
    printf("file not found");
    return 1;
}
// all buffer values mapped
fseek(fp, sizeof(PRODUCT[0])*(num-1), SEEK_SET);
/*WORKING
fseek(file pointer, bytes offset, start/current/end of file)

bytes to offset = how many bytes should the pointer offset/skip
we used - sizeof(PRODUCT[0])*(num-1)      
which means size of 1 PRODUCT STRUCT [index 0](all individual product structs are of equal size 
in bytes,so it doesn't matter whether you take index 0, or index 1, or index 500, 
all are same size)
multiplied...... by PRODUCT_NO/num - 1, 
so if product number is 4 then num - 1 = 3,
hence fseek would skip bytes equivalent to the size of 3 structs...from the start(SEEK_SET)
=> means...struct at index 0, 1, 2, (PRODUCT 1,2,3)will be skipped and File pointer will
be placed at PRODUCT 4/index 3, and will modify values of product 4  */

int nstructswritten = 0;
nstructswritten = fwrite(&PRODUCT[num-1], sizeof(PRODUCT[num-1]), (size_t) 1, fp);
printf("%d structs written\n", nstructswritten);
fclose(fp);
return 0;

//its all the fault in the mode of the file opened,
//cause in all modes, file pointer is either placed at the beginning or at the last
// and you cant really put anything in 'between' in the contents of a file
//for that you need to poistion the file pointer with
//fseek()

//Test
printf("\nTHE UPDATED VALUES OF PRODUCT NO.%d ARE:", num);
printf("\nPRODUCT ID : %d    %d", PRODUCT[num-1].product_ID, num-1);
printf("\nPRODUCT NAME : %s     %d", &PRODUCT[num-1].product_name, num-1);
printf("\nPRODUCT PRICE : %d     %d", PRODUCT[num-1].price, num-1);
printf("\nPRODUCT QUANTITY : %d    %d", PRODUCT[num-1].quantity, num-1);

fclose(f);
}

/* NOW we have another problem
the updated values are not being overwritten at the specified index 'num-1',
instead they are being overwritten on the 0th index


108    0    PRODUCT NO.1  ------ERROR! INCORRECT INDEX(STRUCT) BEING UPDATED
101    1    PRODUCT NO.2
102    2    PRODUCT NO.3
288    3    PRODUCT NO.4
*/

