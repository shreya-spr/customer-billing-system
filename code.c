#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<aclui.h>
#include<unistd.h>
#include<conio.h>

struct item
{
	int productno;
	char productname[100];
	int quantity;
	int price;
}
item;
struct customer
{
	int productno;
	char productname[100];
	int quantity;
	int price;
	int amount;
}
cst[100];
struct temporary
{
	int productno;
	char productname[100];
	int quantity;
	int price;
	int amount;
}
cstr[100];
int t=0;
int maxrecords=0; //used in Quantity and Records.txt
int k=0;
int ba=0;
int ti=0;
void create()
{
    
    int i;
    
    printf("Enter the Number of Records:");
	scanf("%d",&maxrecords);

    FILE* fp;
    fp = fopen("Records.txt", "w");
    if(fp==NULL)
    {
        printf("Error\n");
    }
    else{
    printf("File is opened\n");
    fprintf(fp, "|Product_Number\t|Product_Name\t|Quantity\t|Price\t\n");
    
    for(i=0; i<maxrecords; i++)
    
    {
        printf("Enter the product number:\n");
        scanf("%d", &item.productno);
        
        printf("Enter the product name:\n");
        scanf("%s", &item.productname);
        // to convert them to uppercase
        for (int j = 0; item.productname[j]!='\0'; j++) {
        if(item.productname[j] >= 'a' && item.productname[j] <= 'z') {
         item.productname[j] = item.productname[j] -32;
        }
        }

        printf("Enter quantity:\n");
        scanf("%d", &item.quantity);
       
        printf("Enter the price:\n");
        scanf("%d", &item.price);

        
        fprintf(fp, "%14d\t%10s\t%8d\t%d\n", item.productno, item.productname, item.quantity, item.price);
        
    }
    }
    fclose(fp);
    printf("***Records are created***\n");
}
void bill()
{
	int na=0;  //used for product number in scanf function
	int a=0;	/**/
	int cont=0;
	int k=0;
	int r=0;
	int w=0;
	int ch=0;
	int l=0;	/**/
	int bi=0;
	int ln=0;
    printf("\t");
	a3 : printf("Enter the Product Number:");
	scanf("%d",&na);
	printf("\n");
	FILE *fp;
	fp=fopen("Records.txt","w");
	FILE *fptr;
	fptr=fopen("temp.txt","w");
	while(!(feof(fp)))
	{
		l++;
		fscanf(fp,"%d",&item.productno);
		fscanf(fp,"%s",item.productname);
		fscanf(fp,"%d",&item.quantity);
		fscanf(fp,"%d",&item.price);
		if(item.productno == na)
		{
			ln++;
			if(ln==2)
			break;
			printf("Enter the Quantity:");
			scanf("%d",&a);
			if(a <= item.quantity)
			{
				cst[ti].productno=item.productno;
				strcpy(cst[ti].productname,item.productname);
				cst[ti].quantity=a;
				cst[ti].price=item.price;
				item.quantity=item.quantity-a;
				ti++;
				//goto l1;
			}
			else
			{
				printf("Sorry Out of Stock\n");
				bi++;
				//goto l1;
			}
		}
		else
		{
			cont++;
			fprintf(fptr,"%d\t",item.productno);
			fprintf(fptr,"%s\t",item.productname);
			fprintf(fptr,"%d\t",item.quantity);
			fprintf(fptr,"%d\t",item.price);
			continue;
		}
		fprintf(fptr,"%d\t",item.productno);
		fprintf(fptr,"%s\t",item.productname);
		fprintf(fptr,"%d\t",item.quantity);
		fprintf(fptr,"%d\t",item.price);
	}
	if(l==cont)
	printf("Error:Choose Properly\n");
	fclose(fptr);
	fclose(fp);
	remove("Records.txt");
	rename("temp.txt","Records.txt");
	ln=0;
	printf("Do you Want to Shop More:\nPress 1 for More\nPress 2 to Exit");
	scanf("%d",&k);
	if(k==1)
	goto a3;
}

void display()
{

    FILE* fp = fopen("Records.txt", "r");
    if(fp==NULL)
    {
        printf("Error in opening file\n");
    }
    else {
        
    char    *text;
    int    numbytes;
     
    fseek(fp, 0, SEEK_END);   // sets stream file position to the end of the file
    numbytes = ftell(fp);      // tells where the fp is wrt beginning of file
    fseek(fp, 0, SEEK_SET);  // sets the stream's internal file position to 0,
 
    text = (char*)calloc(numbytes, sizeof(char));   
    if(text == NULL)
        printf("Nothing to see here...");
    else{
    fread(text, sizeof(char), numbytes, fp);
    fclose(fp);
    printf("==============================================================\n");
    printf(text);
    printf("==============================================================\n");
    free(text);
    fclose(fp);
    }
  }
}
void edit()
{
	FILE *fp;
	FILE *fptr;
	FILE *fpk;
	int h;              // pno to delete
	int found=0;
	int ka=0;
	int p;
	fp=fopen("Records.txt","r");
	fptr=fopen("temp1.txt","w");
	fpk=fopen("temp2.txt","w");
	printf("\t");
	printf("Enter the Product Number to Delete: ");
	scanf("%d",&h);
	printf("\n");
	p=maxrecords;
	while(!(ka==p))
	{
		ka++;
		fscanf(fp,"%d",&item.productno);
		if(item.productno==h)
		{
			found=1;
			fscanf(fp,"%s",item.productname);
			fscanf(fp,"%d",&item.quantity);
			fscanf(fp,"%d",&item.price);
			maxrecords--;
			printf("\t");
			printf("Product has been Successfully Deleted\n");
		}
		else
		{
			fscanf(fp,"%s",item.productname);
			fscanf(fp,"%d",&item.quantity);
			fscanf(fp,"%d",&item.price);
			fprintf(fptr,"%d\t%s\t%d\t%d\t",item.productno,item.productname,item.quantity,item.price);
		}
	}
	fprintf(fpk,"%d",maxrecords);
	fclose(fpk);                // close temp1.txt
	fclose(fptr);               // close temp2.txt
	fclose(fp);                 // close Records.txt
	if(found==0)
	{
	    printf("\t");
		printf("Product not Found");
		printf("\n");
		printf("\n");
	}
	remove("Quantity.txt");
	rename("temp2.txt","Quantity.txt");
	remove("Records.txt");
	rename("temp1.txt","Records.txt");
}
void invoice()
{
	int j;
	int o;
	float gt=0;

	if(ti==0)
	{
		printf("There are No Products in your Cart");
		printf("\n");
	}

	FILE *fpntr;
	fpntr = fopen("invoice.txt", "w");
	if(fpntr==NULL)
	{
		printf("Error in opening file\n");
	}
	else{
	fprintf(fpntr, "\n\n");
	fprintf(fpntr, "****************************INVOICE**************************");
	fprintf(fpntr, "\n\n");
	fprintf(fpntr, "product_number\t| product_name\t| price\t| quantity\t| amount\t|\n");
	fprintf(fpntr, "*************************************************************\n");
	for(o=0;o<ti;o++)
	{
		cst[o].amount=0;
		cst[o].amount=((cst[o].price)*(cst[o].quantity));
		gt=gt+cst[o].amount;
	}
	for(j=0;j<ti;j++)
	{
		fprintf(fpntr, "%6d\t       |%9s   \t  | %3d\t|%3d\t        |   %3d\n",cst[j].productno,cst[j].productname,cst[j].price,cst[j].quantity,cst[j].amount);
	}
	fprintf(fpntr, "\nAmount Payable:%f",gt);
	fprintf(fpntr, "\n");
	fprintf(fpntr, "Thank you for Shopping");
	fprintf(fpntr, "\n");
	fprintf(fpntr, "Visit Again");
	fprintf(fpntr, "\n");
	}
	fclose(fpntr);
	printf("Invoice file has been generated!\n");
}
void mdelete()
{
	int i=0;
	int j=0;
	int f=0;
	int g=0;
	int ag=0;
	int aj=0;
	char ab[100];
	FILE *fw;
	FILE *fq;
	printf("\t");
	printf("Enter the Product Number to be Deleted:");
	scanf("%d",&f);
	printf("\n");
	for(i=0;i<ti;i++)
	{
		if(cst[ti].productno==f)
		{
			aj=cst[i].quantity;
			printf("\t");
			printf("Product Deleted Successfully");
			printf("\n");
		}
		continue;
		cstr[g].productno=cst[i].productno;
	  	strcpy(cstr[g].productname,cst[i].productname);
	  	cstr[g].quantity=cst[i].quantity;
	  	cstr[g].price=cst[i].price;
	  	g++;
	}
	for(j=0;j<g;j++)
	{
		cst[j].productno=cstr[j].productno;
 	 	strcpy(cst[j].productname,cstr[j].productname);
	  	cst[j].quantity=cstr[j].quantity;
	  	cst[j].price=cstr[j].price;
	}
	ti=g;
	printf("\n%d",aj);
	fq=fopen("shop.txt","r");
	fw=fopen("temp4.txt","w");
	for(j=0;j<maxrecords;j++)
	{
		fscanf(fq,"%d",&item.productno);
		fscanf(fq,"%s",item.productname);
		fscanf(fq,"%d",&item.quantity);
		fscanf(fq,"%d",&item.price);
		if(item.productno==f)
		{
		    ag=aj+item.quantity;
            fprintf(fw,"%d\t%s\t%d\t%d\t",item.productno,item.productname,ag,item.price);
        }
        else
        {
        	fprintf(fw,"%d\t%s\t%d\t%d\t",item.productno,item.productname,item.quantity,item.price);
        }
	}
	fclose(fq);
	fclose(fw);
	remove("Records.txt");
	rename("temp4.txt","Records.txt");
}
void mdisplay()
{
	int i;
	int j;
	int o;
	printf("================================================================================\n");
	printf("product_number\t|product_name\t|quantity\t|price\t\n");
	printf("================================================================================\n");
	for(o=0;o<ti;o++)
	{
		printf("%14d\t|%12s\t|%6d\t|%6d\n",cst[o].productno,cst[o].productname,cst[o].quantity,cst[o].price);
	}
}

int main()
{
	char ch,password[10],q[10]="admin";
	int s=0;
	int y=0;
	int w=1;
	int i;
	FILE *fpe;
	fpe=fopen("Quantity.txt","r");
	fscanf(fpe,"%d",&maxrecords);
	fclose(fpe);
	printf("\n");
    q: printf("\n\t");
    printf("****************************");
    printf("\n");
    printf("\t");
    printf("Please Select an Option: ");
    printf("\n");
    printf("\t");
    printf("****************************");
    printf("\n");
    printf("\t");
	printf("01. ADMINISTRATOR");
	printf("\n\t");
	printf("02. CUSTOMER");
	printf("\n\t");
	printf("03. EXIT");
	printf("\n");
	printf("\n\t");
	printf("Please Enter an Option: ");
	scanf("%d",&s);

	switch(s)
	{
	          case 1: printf("\tEnter Password:\t");
              for(i=0;i<5;i++)
              {
              ch = getch();
              password[i] = ch;
              ch = '*' ;
               printf("%c",ch);
              }
              password[i]='\0';
              if(strcmp(password,q))
              {
                  printf("\n\t");
              printf("Wrong Password Please Try Again");
              printf("\n\n");
              goto q;
             }
               else
               goto l3;
               l3: printf("\n\t");
               printf("Access Granted\n");
               printf("\n\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("Please Select an Option: ");
               printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n");
		       printf("\t01.CREATE");
		       printf("\n\t");
		       printf("02.DELETE/MODIFY");
		       printf("\n\t");
		       printf("03.DISPLAY");
		       printf("\n\t");
		       printf("04.MAIN MENU");
		       printf("\n");
		       printf("\n");
		       printf("\t");
		       printf("Please Enter an Option: ");
		        scanf("%d",&y);
		        switch(y)
		        {
        			case 1:create();
        			      goto q;
  			      case 2:edit();
  			             goto q;
                  case 3:display();
                         goto q;
                  case 4: goto q;
                  default : printf("error\n");
				  goto q;
        		}
		         break;

       case 2: printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("Please Select an Option: ");
               printf("\n");
               printf("\t");
               printf("****************************");
               printf("\n");
               printf("\t");
               printf("01.BILL");
               printf("\n\t");
               printf("02.INVOICE");
               printf("\n\t");
               printf("03.DISPLAY");
               printf("\n\t");
               printf("04.MYCART");
               printf("\n\t");
               printf("05.MAIN MENU");
               printf("\n\t");
               printf("06.DELETE ITEMS IN CART\n");
               printf("\n\t");
               printf("Please Enter an Option: ");
               scanf("%d",&y);
               printf("\n");
               switch(y)
		        {
                    case 1 : bill();
        			         goto q;

                    case 2 : invoice();
                             goto q;

                    case 3 : display();
                             goto q;

                    case 4 : mdisplay();        
                             goto q;

                    case 5 : goto q;

                    case 6 : mdelete();         
                             goto q;

                    default : printf("Error\n");
                              goto q;
        		}
		         break;
      case 3: printf("\tExiting...\n");
            puts("\n\nClosing Program:");         
			printf("\n\t");
			int i=0;
			while(i<4){
				printf("* ");
				sleep(3);
				i++;
			}
			exit(0);
      break;
      default : printf("error\n");
      break;
	}
}
