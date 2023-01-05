//TMF1414 Group 09 Project  Members: Syafiq, Iffah, Neo       *Project due by 13th January 2021
//Functions with /*...*/ is still in development.
// Functions with ** is still under development too. 

#include <stdio.h>
#include <string.h> 
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void menu();          // Function for displaying menu
void addbill();       // Function for user to add customer bill
void displaybill();   // Function for user to display customer bill
void deletebill();    // Function for user to delete customer bill
void viewbill();      // Function for user to view all the customer bill
void quit();          // Function for user to quit the program
void calcbill();      // Function to calculate bill that redirects to either calclocal()/ calclong()/ calclinter()
void ranrecnum();     // Function to getting a random number from 001-999
void monthcr();       // Function to change the month from int form to string form
int calclocal();     // Function to calculate local rates
int calclong();      // Function to calculate long distance rates
int calcinter();     // Function to calculate international rates

struct custinfonbill       // This is the data structure for customer's input to their bill
{
	char name[30], type[15], range[15],month[12],day;    // name = customer name; type = call type; range = local/long distance/international
	int id, minute,recnum,dd,mm,yyyy;             // id = customer ID number; minute = duration of call in minutes; reccnum = receipt number
	float ttbill;                     //ttbill = total bill for customer
} custinfo;          

struct billrate      // This is the data structure for calculating customer's bill
{
	float total, rate, firstsum, secsum;
} billrate;

char choicecty, choicecr;

int main()           // Main function
{
	
	printf("Welcome to CCom Postpaid Billing System.\n\n");
	menu();
	return 0; 
	
	}

void menu()         // Menu display function
{
	char choice;
	
	printf("1 - Enter Customer Bill \n");
	printf("2 - Display Bill \n");
	printf("3 - Delete Bill \n");
	printf("4 - View All Customer Bills \n");	
	printf("5 - Quit \n\n");	
	
    printf("Please enter your choice...\n");
	choice=getch();
	
	switch(choice)
	{
		case '1':
			addbill(); break;
		case '2':
			displaybill();break;  
		case '3':
			deletebill(); break;
		case '4':
			viewbill(); break;
		case '5':
			quit(); break;
		default: 
		    printf("\nInput out of range.Please press 'any button' to try again...");
		    getch();
		    system("cls");
		    menu();
		    break;
	}
}
 
void addbill()      // Adding bill function
{
	system("cls");
	
	char back;     // This variable to prompt user after input their bills
	char choiceph, confirm;
	
	printf("\nPlease enter the information below.\n");
	printf("Name: ");
	scanf("%[^\n]", &custinfo.name);
	printf("\nDate\n");
	printf("Day (dd) : ");
	do{
		if((scanf("%d",&custinfo.dd))==0||custinfo.dd<1||custinfo.dd>31){
			printf("Input out of range.Please try again...\n");
			fflush(stdin);
		}
	}while(custinfo.dd<1||custinfo.dd>31);	
	printf("Month (mm) : ");
	do{
		if((scanf("%d",&custinfo.mm))==0||custinfo.mm<1||custinfo.mm>12){
			printf("Input out of range.Please try again...\n");
			fflush(stdin);
		}
	}while(custinfo.mm<1||custinfo.mm>12);
	printf("Year (yyyy) : ");
	do{
		if((scanf("%d",&custinfo.yyyy))==0||custinfo.yyyy<1900||custinfo.yyyy>3000){
			printf("Input out of range.Please try again...\n");
			fflush(stdin);
		}
	}while(custinfo.yyyy<1900||custinfo.yyyy>3000);
	printf("\nID no. (6 digits): ");
	do{
		if((scanf("%d", &custinfo.id))==0||custinfo.id<100000||custinfo.id>999999){
			printf("Input out of range.Please try again...\n");
			fflush(stdin);
		}
	}while(custinfo.id<100000||custinfo.id>999999);
	
	printf("\nCall type (A : Local/ B : Long distance/ C : International)\n");
	do{	
	    choicecty=getch();
	    choicecty=toupper(choicecty);
	    switch(choicecty){
	    	
	        case 'A':	        	
	    	    printf("The call type---A : Local\n"); strcpy(custinfo.type,"Local"); break;
	        case 'B':
	    	    printf("The call type---B : Long distance\n"); strcpy(custinfo.type,"Long distance"); break;
	        case 'C':
	          	printf("The call type---C : International\n"); strcpy(custinfo.type,"International"); break;
	        default:
	        	printf("Input out of range.Please try again\n");
    	}
    }while(choicecty!='A'&&choicecty!='B'&&choicecty!='C');
    
	printf("\nDuration of call (minutes): ");
	scanf("%d", &custinfo.minute);
	
	printf("\nTime range (A:7am - 6pm/ B:6pm - 12am/ C:12am - 7am)\n");
	do{
		choicecr=getch();
		choicecr=toupper(choicecr);
		switch(choicecr){
	    	
	        case 'A':	        	
	    	    printf("The time range---A : 7am - 6pm\n"); strcpy(custinfo.range,"(7am - 6pm)"); break;
	        case 'B':
	    	    printf("The time range---B : 6pm - 12am\n"); strcpy(custinfo.range,"(6pm - 12am)"); break;
	        case 'C':
	            printf("The time range---C : 12am - 7am\n"); strcpy(custinfo.range,"(12am - 7am)"); break;
	        default:
	        	printf("Input out of range.Please try again\n");
    	}
	}while(choicecr!='A'&&choicecr!='B'&&choicecr!='C');

	printf("\nIs customer call on Weekend or Public Holidays? Y/N\n");
	do{
	    choiceph=getch();
	    choiceph=toupper(choiceph);
	    switch(choiceph){
	    	case 'Y':
	    		break;
	    	case 'N':
	    		break;
	    	default:
	    		printf("Input out of range.Please try again\n");
		}
	}while(choiceph!='Y'&&choiceph!='N');
	custinfo.day = choiceph;
	
	system("cls");
	printf("Please make sure all the information is corect.\n\n");
	ranrecnum();
	printf("\nName                             : %s",custinfo.name);
	printf("\nDate                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
	printf("\nID                               : %d",custinfo.id);
	if(choicecty=='A'){
		printf("\nCall type                        : A---Local");
	}
	else if(choicecty=='B'){
		printf("\nCall type                        : B---Long distance");
	}
	else if(choicecty=='C'){
		printf("\nCall type                        : C---International");
	}
	printf("\nDuration of call                 : %d minutes",custinfo.minute);
	if(choicecr=='A'){
		printf("\nTime range                       : A---7am - 6pm");
	}
	else if(choicecr=='B'){
		printf("\nTime range                       : B---6pm - 12am");
	}
	else if(choicecr=='C'){
		printf("\nTime range                       : C---12am - 7am");
	}
	if(custinfo.day=='Y'){
		printf("\nWeekend / Public Holiday calling : Yes\n");
	}
	else if(custinfo.day=='N'){
		printf("\nWeekend / Public Holiday calling : No\n");
	}
	calcbill();
	
	printf("\n\nWould you want to record the customer bill? Y/N\n");
	do{
		confirm=getch();
		confirm=toupper(confirm);
		switch(confirm){
			case 'Y':
				FILE *iamptr;
				FILE *iamptr4; 
				
				if((iamptr = fopen("Customer receipt.txt","w"))==NULL||(iamptr4 = fopen("Custdata.dat","ab+"))==NULL){
					printf("File could not be opened. Probably you can try again later.\n");
					printf("Press 'any button' go back to menu...");
					getch();
					fflush(stdin);
					menu();
				}
				else{
					
					if(custinfo.recnum<10){
		            	fprintf(iamptr,"Receipt number                   : 00%d",custinfo.recnum);
	            	}
	            	else if(custinfo.recnum<100){
		            	fprintf(iamptr,"Receipt number                   : 0%d",custinfo.recnum);
                 	}
		            else{
		                fprintf(iamptr,"Receipt number                   : %d",custinfo.recnum);
                	}
					fprintf(iamptr,"\nName                             : %s",custinfo.name);
					fprintf(iamptr,"\nDate                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
					fprintf(iamptr,"\nID                               : %d",custinfo.id);
					fprintf(iamptr,"\nCall type                        : %s",custinfo.type);
					fprintf(iamptr,"\nCall minutes                     : %d minutes",custinfo.minute);
					fprintf(iamptr,"\nTime range                       : %s",custinfo.range);
					if(custinfo.day=='Y'){
	                	fprintf(iamptr,"\nWeekend / Public Holiday calling : Yes\n");
                	}
                	else if(custinfo.day=='N'){
	                	fprintf(iamptr,"\nWeekend / Public Holiday calling : No\n");       
                	}
                	fprintf(iamptr,"Total bill                       : RM%.2f\n\n", custinfo.ttbill);
					fclose(iamptr);
					fwrite(&custinfo,sizeof(struct custinfonbill),1,iamptr4);
					fclose(iamptr4);
				}
				break;
			case 'N':
				printf("\n\nThe record of customer bill is cancle.\n");
				printf("Press 'enter' to add the new record.\nPress 'esc' go back to menu.\n");
				do{	
	              	back=getch();
	            	switch(back){   // Decides where user goes after input their bill information
	                    case 13:
	                     	fflush(stdin);
		    	            addbill(); break;
		                case 27:
		                 	fflush(stdin);
		                	system("cls");menu(); break;
	     	            default:
		                	printf("Input out of range.Please try again.\n");
    	            }
            	}while(back!=13&&back!=27);break;
			default:	
			    printf("Input out of range.Please try again.\n");	
		}
	}while(confirm!='Y'&&choiceph!='N');
	
	printf("\n\nYou have successfully added a record.\nPress 'enter' to add the new record.\nPress 'esc' go back to menu.\n\n");
	do{
		back=getch();
		switch(back){   // Decides where user goes after input their bill information
	        case 13:
	        	fflush(stdin);
		    	addbill(); break;
		    case 27:
		    	fflush(stdin);
		    	system("cls");menu(); break;
	     	default:
		    	printf("Input out of range.Please try again.\n");
    	}
	}while(back!=13&&back!=27);
	

}

void displaybill(){
	char choicedis,fcrconfirm,fcrname[30],pbcconfirm,pbcname[30],mrconfirm,mrname[30],mrch;
	int fcrid,pbcid,pbccheck=0,pbcmonth,mrid,mrcheck=0,mrmonth,tttbillcheck=0;
	float tttbill;
	FILE *iamptr;   //pointer of Customer receipt.txt file
	FILE *iamptr2;  //pointer of Phonebilcompile.txt file
	FILE *iamptr3;  //pointer of CCkom monthly report.txt file
	FILE *iamptr4;  //pointer of Custdata.dat file
	
	system("cls");
	printf("1 - Find Customer Receipt\n");
	printf("2 - Find Phonebillcombine\n");
	printf("3 - Monthly Report\n\n");
	printf("Please enter your choice...");
	choicedis=getch();
	fflush(stdin);
	
	switch(choicedis)
	{
		case '1':
			system("cls");
			printf("For finding the customer receipt. Please enter the name of customer and ID.\n");
			printf("Name            : ");
			scanf("%[^\n]",&fcrname);
			printf("\nID (6 digits) : ");
			do{
	        	if((scanf("%d",&fcrid))==0||fcrid<100000||fcrid>999999){
	        		printf("Input out of range.Please try again...\n");
	 		fflush(stdin);
	    	}
        	}while(fcrid<100000||fcrid>999999);
			system("cls");
			
			if((iamptr = fopen("Customer receipt.txt","w"))==NULL||(iamptr4 = fopen("Custdata.dat","rb"))==NULL){
					printf("File could not be opened. Probably you can try again later.\n");
					printf("Press 'any button' go back to menu...");
					getch();
					fflush(stdin);
					menu();
			}
			else{
				rewind(iamptr4);
		        while(fread(&custinfo,sizeof(struct custinfonbill),1,iamptr4)){
		        	
		        	if((strcmpi(fcrname,custinfo.name)==0)&&(fcrid==custinfo.id)){
		        		if(custinfo.recnum<10){
		            	    printf("Receipt number                   : 00%d",custinfo.recnum);
	                 	}
	                 	else if(custinfo.recnum<100){
		                 	printf("Receipt number                   : 0%d",custinfo.recnum);
                     	}
		                else{
		                    printf("Receipt number                   : %d",custinfo.recnum);
                     	}
					    printf("\nName                             : %s",custinfo.name);
				     	printf("\nDate                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
				    	printf("\nID                               : %d",custinfo.id);
				    	printf("\nCall type                        : %s",custinfo.type);
				    	printf("\nCall minutes                     : %d minutes",custinfo.minute);
			    		printf("\nTime range                       : %s",custinfo.range);
				    	if(custinfo.day=='Y'){
	                     	printf("\nWeekend / Public Holiday calling : Yes\n");
                    	}
                	    else if(custinfo.day=='N'){
	                	    printf("\nWeekend / Public Holiday calling : No\n");       
                    	}
                    	printf("Total bill                       : RM%.2f\n\n", custinfo.ttbill);
                    	
                    	printf("Would you want to print out this record to 'Customer receipt.txt'? Y/N\n");
                    	do{
                    		fcrconfirm=getch();
                    		fcrconfirm=toupper(fcrconfirm);
                    		switch(fcrconfirm){
                    			case 'Y':
                    				if(custinfo.recnum<10){
		                            	fprintf(iamptr,"Receipt number                   : 00%d",custinfo.recnum);
	                            	}
	                            	else if(custinfo.recnum<100){
		                            	fprintf(iamptr,"Receipt number                   : 0%d",custinfo.recnum);
                                	}
		                            else{
		                                fprintf(iamptr,"Receipt number                   : %d",custinfo.recnum);
                                	}
				                	fprintf(iamptr,"\nName                             : %s",custinfo.name);
				                	fprintf(iamptr,"\nDate                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
				                  	fprintf(iamptr,"\nID                               : %d",custinfo.id);
				                	fprintf(iamptr,"\nCall type                        : %s",custinfo.type);
				                	fprintf(iamptr,"\nCall minutes                     : %d minutes",custinfo.minute);
				                 	fprintf(iamptr,"\nTime range                       : %s",custinfo.range);
				                	if(custinfo.day=='Y'){
	                                	fprintf(iamptr,"\nWeekend / Public Holiday calling : Yes\n");
                                	}
                                	else if(custinfo.day=='N'){
	                                 	fprintf(iamptr,"\nWeekend / Public Holiday calling : No\n");       
                                	}
                                	fprintf(iamptr,"Total bill                       : RM%.2f\n\n", custinfo.ttbill);
                                	printf("\nYou have successfully to print out the record to 'Customer receipt.txt'\nPress 'any button' go back to menu.");
                                	fclose(iamptr);
			                    	fclose(iamptr4);
                                	getch();
                                	fflush(stdin);
                                	system("cls");
                                	menu();
                                	break;
                    			case 'N':
								printf("\n");break;
								default:
									printf("Input out of range.Please try again.\n");
									
							}
						}while(fcrconfirm!='Y'&&fcrconfirm!='N');
					}
				}
				fclose(iamptr);
				fclose(iamptr4);
				printf("System cannot find out the record from the file. Pbobably you can try it later.\n");
				printf("Press 'any button' go back to menu.");
				getch();
				fflush(stdin);
				system("cls");
				menu();
			}
			break;
		case '2':
			system("cls");
			printf("For finding the phonebillcompine. Please enter the name of customer, ID and month��with 2 digits).\n\n");
			printf("Name                       : ");
			scanf("%[^\n]",&pbcname);
			printf("\nID (6 digits)              : ");
			do{
	        	if((scanf("%d", &pbcid))==0||pbcid<100000||pbcid>999999){
	        		printf("Input out of range.Please try again...\n");
		        	fflush(stdin);
	        	}
        	}while(pbcid<100000||pbcid>999999);
			printf("\nMonth (with 2 digits) : ");
			do{
	        	if((scanf("%d",&pbcmonth))==0||pbcmonth<1||pbcmonth>12){
	        	printf("Input out of range.Please try again...\n");
	    		fflush(stdin);
    		}
        	}while(pbcmonth<1||pbcmonth>12);
			system("cls");
			
			if((iamptr2 = fopen("Phonebillcompile.txt","w"))==NULL||(iamptr4 = fopen("Custdata.dat","rb"))==NULL){
					printf("File could not be opened. Probably you can try again later.\n");
					printf("Press 'any button' go back to menu...");
					getch();
					fflush(stdin);
					menu();
				}
			else{
				rewind(iamptr4);
				while(fread(&custinfo,sizeof(struct custinfonbill),1,iamptr4)){
					monthcr();
					if((strcmpi(pbcname,custinfo.name)==0)&&(pbcid==custinfo.id)&&(pbcmonth==custinfo.mm)){
						pbccheck=1;
					}
				}
				if(pbccheck==1){
			    	fprintf(iamptr2,"Name  : %s",pbcname);
			    	fprintf(iamptr2,"\nID    : %d",pbcid);
			    	fprintf(iamptr2,"\nMonth : %s\n\n",custinfo.month);
			    	pbccheck=0;
		    	}
				rewind(iamptr4);
		        while(fread(&custinfo,sizeof(struct custinfonbill),1,iamptr4)){
		        monthcr();
					
		        	if((strcmpi(pbcname,custinfo.name)==0)&&(pbcid==custinfo.id)&&(pbcmonth==custinfo.mm)){
		        		if(custinfo.recnum<10){
		            	    printf("Receipt number                   : 00%d",custinfo.recnum);
	                 	}
	                 	else if(custinfo.recnum<100){
		                 	printf("Receipt number                   : 0%d",custinfo.recnum);
                     	}
		                else{
		                    printf("Receipt number                   : %d",custinfo.recnum);
                     	}
					    printf("\nName                             : %s",custinfo.name);
				     	printf("\nDate                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
				    	printf("\nID                               : %d",custinfo.id);
				    	printf("\nCall type                        : %s",custinfo.type);
				    	printf("\nCall minutes                     : %d minutes",custinfo.minute);
			    		printf("\nTime range                       : %s",custinfo.range);
				    	if(custinfo.day=='Y'){
	                     	printf("\nWeekend / Public Holiday calling : Yes\n");
                    	}
                	    else if(custinfo.day=='N'){
	                	    printf("\nWeekend / Public Holiday calling : No\n");       
                    	}
                    	printf("Total bill                       : RM%.2f\n\n", custinfo.ttbill);
                    	
                    	printf("Would you want to print out this record to 'Phonebillcompile.txt'? Y/N\n\n");
                    	do{
                    		pbcconfirm=getch();
                    		pbcconfirm=toupper(pbcconfirm);
                    		switch(pbcconfirm){
                    			case 'Y':
                    				fprintf(iamptr2,"Date                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
                    				if(custinfo.recnum<10){
		                            	fprintf(iamptr2,"\nReceipt number                   : 00%d",custinfo.recnum);
	                            	}
	                            	else if(custinfo.recnum<100){
		                            	fprintf(iamptr2,"\nReceipt number                   : 0%d",custinfo.recnum);
                                	}
		                            else{
		                                fprintf(iamptr2,"\nReceipt number                   : %d",custinfo.recnum);
                                	}
                                	fprintf(iamptr2,"\nCall minutes                     : %d minutes",custinfo.minute);
                                	fprintf(iamptr2,"\nTime range                       : %s",custinfo.range);
                                	fprintf(iamptr2,"\nTotal bill                       : RM%.2f\n\n", custinfo.ttbill);
                                	break;
                                case 'N':
                                	printf("\n");break;
								default:
									printf("Input out of range.Please try again\n");
							}
						}while(pbcconfirm!='Y'&&pbcconfirm!='N');
					}
				}
				fclose(iamptr2);
				fclose(iamptr4);
				printf("All the record already find out from file.\n");
				printf("Press 'any button' go back to menu.");
				getch();
				fflush(stdin);
				system("cls");
				menu();
			}
			break;  
		case '3':
			system("cls");
			printf("For recording the CCkom monthly report. Please enter the name of customer, ID and month(with 2 digits).\n");
			printf("Name                       : ");
			scanf("%[^\n]",&mrname);
			printf("\nID (6 digits)              : ");
			do{
	        	if((scanf("%d", &mrid))==0||mrid<100000||mrid>999999){
	    		printf("Input out of range.Please try again...\n");
	    		fflush(stdin);
	        	}
        	}while(mrid<100000||mrid>999999);
			printf("\nMonth (with 2 digits)      : ");
			do{
	        	if((scanf("%d",&mrmonth))==0||mrmonth<1||mrmonth>12){
	        	printf("Input out of range.Please try again...\n");
	    		fflush(stdin);
    		}
        	}while(mrmonth<1||mrmonth>12);
			system("cls");
			
			if((iamptr3 = fopen("CCkom monthly report.txt","a+"))==NULL||(iamptr4 = fopen("Custdata.dat","rb"))==NULL){
					printf("File could not be opened. Probably you can try again later.\n");
					printf("Press 'any button' go back to menu...");
					getch();
					fflush(stdin);
					menu();
				}
			else{
				rewind(iamptr4);
				while(fread(&custinfo,sizeof(struct custinfonbill),1,iamptr4)){
			    	monthcr();
			    	if((strcmpi(mrname,custinfo.name)==0)&&(mrid==custinfo.id)&&(mrmonth==custinfo.mm)){
				    	mrcheck=1;
					}
				}
				mrch=fgetc(iamptr3);
				fseek(iamptr3,0L,2);
				if((mrch==EOF)&&(mrcheck==1)){
					custinfo.mm = mrmonth;
					monthcr();
					fprintf(iamptr3,"Month : %s\n\n",custinfo.month);
				}
				if(mrcheck==1){
			    	fprintf(iamptr3,"Name  : %s",mrname);
			    	fprintf(iamptr3,"\nID    : %d\n",mrid);
			    	mrcheck=0;
		    	} 
				rewind(iamptr4);
		        while(fread(&custinfo,sizeof(struct custinfonbill),1,iamptr4)){
		            monthcr();
		        	
		        	if((strcmpi(mrname,custinfo.name)==0)&&(mrid==custinfo.id)&&(mrmonth==custinfo.mm)){
		        		if(custinfo.recnum<10){
		            	    printf("Receipt number                   : 00%d",custinfo.recnum);
	                 	}
	                 	else if(custinfo.recnum<100){
		                 	printf("Receipt number                   : 0%d",custinfo.recnum);
                     	}
		                else{
		                    printf("Receipt number                   : %d",custinfo.recnum);
                     	}
					    printf("\nName                             : %s",custinfo.name);
				     	printf("\nDate                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
				    	printf("\nID                               : %d",custinfo.id);
				    	printf("\nCall type                        : %s",custinfo.type);
				    	printf("\nCall minutes                     : %d minutes",custinfo.minute);
			    		printf("\nTime range                       : %s",custinfo.range);
				    	if(custinfo.day=='Y'){
	                     	printf("\nWeekend / Public Holiday calling : Yes\n");
                    	}
                	    else if(custinfo.day=='N'){
	                	    printf("\nWeekend / Public Holiday calling : No\n");       
                    	}
                    	printf("Total bill                       : RM%.2f\n\n", custinfo.ttbill);
                    	
                    	printf("Would you want to print out this record to 'CCkom monthly report.txt'? Y/N\n\n");
						do{
                    		mrconfirm=getch();
                    		mrconfirm=toupper(mrconfirm);
                    		switch(mrconfirm){
                    			case 'Y':
                    				tttbill+=custinfo.ttbill;
									tttbillcheck=1;
									break;
                    			case 'N':
                    				printf("\n");break;
                    			default:
                    				printf("Input out of range.Please try again\n");
                    		}
                    	}while(mrconfirm!='Y'&&mrconfirm!='N');
                   	}
				}
				if(tttbillcheck==1){
			    	fprintf(iamptr3,"Total payment : %.2f\n\n",tttbill);
		    	}
		    	tttbillcheck=0;
				fclose(iamptr3);
				fclose(iamptr4);
				printf("All the record already print out into 'CCkom monthly report.txt'.\n");
				printf("Press 'any button' go back to menu.");
				getch();
				fflush(stdin);
				system("cls");
				menu();
			}
			break;
		default: 
		    printf("\nInput out of range.Please press 'any button' to try again...");
		    getch();
		    system("cls");
		    displaybill();
	}
}

void deletebill()   // Delete bill function**
{
	char dlbname[30],dlbconfirm;
	int dlbid;
	
	FILE *iamptr4;
	FILE *iamptr5; //pointer of temp.dat file
	system("cls");
	printf("For delete the customer bill record. Please enter the name of customer and ID.\n\n");
	printf("Name                       : ");
	scanf("%[^\n]",&dlbname);
	printf("\nID (6 digits)              : ");
	do{
		if((scanf("%d", &dlbid))==0||dlbid<100000||dlbid>999999){
			printf("Input out of range.Please try again...\n");
			fflush(stdin);
		}
	}while(dlbid<100000||dlbid>999999);
	system("cls");
	
	if((iamptr5 = fopen("temp.dat","wb"))==NULL||(iamptr4 = fopen("Custdata.dat","rb"))==NULL){
					printf("File could not be opened. Probably you can try again later.\n");
					printf("Press 'any button' go back to menu...");
					getch();
					fflush(stdin);
					menu();
				}
	else{
				rewind(iamptr4);
		        while(fread(&custinfo,sizeof(struct custinfonbill),1,iamptr4)){
		        	
		        	if((strcmpi(dlbname,custinfo.name)==0)&&(dlbid==custinfo.id)){
		        		if(custinfo.recnum<10){
		            	    printf("Receipt number                   : 00%d",custinfo.recnum);
	                 	}
	                 	else if(custinfo.recnum<100){
		                 	printf("Receipt number                   : 0%d",custinfo.recnum);
                     	}
		                else{
		                    printf("Receipt number                   : %d",custinfo.recnum);
                     	}
					    printf("\nName                             : %s",custinfo.name);
				     	printf("\nDate                             : %d/%d/%d",custinfo.dd,custinfo.mm,custinfo.yyyy);
				    	printf("\nID                               : %d",custinfo.id);
				    	printf("\nCall type                        : %s",custinfo.type);
				    	printf("\nCall minutes                     : %d minutes",custinfo.minute);
			    		printf("\nTime range                       : %s",custinfo.range);
				    	if(custinfo.day=='Y'){
	                     	printf("\nWeekend / Public Holiday calling : Yes\n");
                    	}
                	    else if(custinfo.day=='N'){
	                	    printf("\nWeekend / Public Holiday calling : No\n");       
                    	}
                    	printf("Total bill                       : RM%.2f\n\n", custinfo.ttbill);
                    	
                    	printf("Would you want to delete this customer bill record? Y/N\n");
                    	do{
                    		dlbconfirm=getch();
                    		dlbconfirm=toupper(dlbconfirm);
                    		switch(dlbconfirm){
                    			case 'Y':
                    				printf("\n");break;
                    			case 'N':
                    				fwrite(&custinfo,sizeof(struct custinfonbill),1,iamptr5);break;
                    			default:
                    				printf("Input out of range.Please try again.\n");
                    		}
                    	}while(dlbconfirm!='Y'&&dlbconfirm!='N');
                    }
                    else{
                    	fwrite(&custinfo,sizeof(struct custinfonbill),1,iamptr5);
					}
				}
				fclose(iamptr5);
				fclose(iamptr4);
				remove("Custdata.dat");
				rename("temp.dat","Custdata.dat");
				printf("Program is already finish.\n");
				printf("Press 'any button' go back to menu.");
				getch();
				fflush(stdin);
				system("cls");
				menu();
                    
    }
	
			
	
	// Function to be added later
	/*  printf("Please enter the customer ID that you would like to delete.\n");
    	scanf("%d", custinfo.id);
	
	    printf("You have successfully deleted the customer bill.\n");     */
}

void viewbill()     // View bill function**
{
	system("cls");
	FILE *iamptr4;
	
	if((iamptr4 = fopen("custdata.dat","rb"))==NULL){
		printf("The file cannot be open. Probably you need to add a new record by using 'Enter Customer Bill'.");
		printf("\nPress 'any button' go back to menu...");
		getch();
		fflush(stdin);
		menu();
	}
	else{
		printf("%-10s%-30s%-10s%-15s%-15s%-13s%-14s%-11s%-15s\n","No.Recpt","Name","ID","Call minutes","Call Type","Date","Time Range","Ex.charge","Total Bill");
		rewind(iamptr4);
		while(fread(&custinfo,sizeof(struct custinfonbill),1,iamptr4)){
			printf("%-10d%-30s%-10d%-15d%-15s%d/%d/%-7d%-14s%-11cRM%-15.2f\n\n",custinfo.recnum,custinfo.name,custinfo.id,custinfo.minute,custinfo.type,custinfo.dd,custinfo.mm,custinfo.yyyy,custinfo.range,custinfo.day,custinfo.ttbill);
	    }
	    fclose(iamptr4);
	    printf("\nThis is all of the record of the customer bill.");
	    printf("\nPress 'any button' go back to menu...");
	    getch();
	    fflush(stdin);
	    system("cls");
	    menu();
	}
	
	
	//Function to be added later. Iffah, please add file operation function to call the memory so that it can print out statement below. (Delete this comment after completed)
	/*{
		printf("\nName\tID number\tCall type:\tDuration of call (minutes:\tTime range:\n)");
		printf("%s \t%d \t%s \t%d \t%s", custinfo.name, custinfo.id, custinfo.type, custinfo.minute, custinfo.range);     
	} */
}

void quit()        // Quit program function**
{
	char quitconfirm;
	
	system("cls");
	printf("\nWould you want to quit the CCkom communication service program ? Y/N\n\n");
	do{
	    quitconfirm=getch();
	    quitconfirm=toupper(quitconfirm);
	    switch(quitconfirm){
	    	case 'Y':
	    		printf("The program have been closing...");break;
	    	case 'N':
	    		system("cls");
				menu();break;
	    	default:
	    		printf("Input out of range.Please try again\n");
		}
	}while(quitconfirm!='Y'&&quitconfirm!='N');
	
}

void calcbill()    // Function that redirect to either local/long distance/international function
{
	switch(choicecty)
	{
		case 'A':
			calclocal(); break;
		case 'B':
			calclong(); break;
		case 'C':
			calcinter(); break;
	}
}

int calclocal()   // Function that calculate local           
{
	if(choicecr == 'A')
	{
		if(custinfo.minute <= 1)
		{
			billrate.total = custinfo.minute * 0.30;
		}
		else if(custinfo.minute >= 2)
		{
			billrate.total = ((custinfo.minute - 1) * 0.40) + 0.30;
		}
	}
	
	if(choicecr == 'B')
	{
		if(custinfo.minute <= 1)
		{
			billrate.total = custinfo.minute * 0.30;
		}
		else if(custinfo.minute >= 2)
		{
			billrate.total = ((custinfo.minute - 1) * 0.30) + 0.30;
		}
	}
	
	if(choicecr == 'C')
	{
		billrate.total = custinfo.minute * 0.40;
	}
	
	if(custinfo.day == 'Y')
	{
		billrate.total *=1.10;
		printf("The total of the bill is         : RM%.2f", billrate.total);
	}
	else if(custinfo.day == 'N')
	{
		printf("The total of the bill is         : RM%.2f", billrate.total);
	}
	custinfo.ttbill = billrate.total;
	
	return 0;
}

int calclong()   // Function that calculate long distance call
{
	if(choicecr == 'A')
	{
		if(custinfo.minute <= 1)
		{
			billrate.total = custinfo.minute * 0.50;
		}
		else if(custinfo.minute >= 2)
		{
			billrate.total = ((custinfo.minute - 1) * 0.60) + 0.50;
		}
	}
	
	if(choicecr == 'B')
	{
		if(custinfo.minute <= 1)
		{
			billrate.total = custinfo.minute * 0.40;
		}
		else if(custinfo.minute >= 2)
		{
			billrate.total = ((custinfo.minute - 1) * 0.40) + 0.40;
		}
	}
	
	if(choicecr == 'C')
	{
		billrate.total = custinfo.minute * 0.60;
	}
	
	if(custinfo.day == 'Y')
	{
		billrate.total *=1.10;
		printf("The total of the bill is          : RM%.2f", billrate.total);
	}
	else if(custinfo.day == 'N')
	{
		printf("The total of the bill is          : RM%.2f", billrate.total);
	}
	custinfo.ttbill = billrate.total;
	
	return 0;
}

int calcinter()  // Function that calculate international call
{
	if(choicecr == 'A')
	{
		if(custinfo.minute <= 1)
		{
			billrate.total = custinfo.minute * 2.50;
		}
		else if(custinfo.minute >= 2)
		{
			billrate.total = ((custinfo.minute - 1) * 1.00) + 2.50;
		}
	}
	
	if(choicecr == 'B')
	{
		if(custinfo.minute <= 1)
		{
			billrate.total = custinfo.minute * 2.00;
		}
		else if(custinfo.minute >= 2)
		{
			billrate.total = ((custinfo.minute - 1) * 0.80) + 2.00;
		}
	}
	
		if(choicecr == 'C')
	{
		billrate.total = custinfo.minute * 1.20;
	}
	
	if(custinfo.day == 'Y')
	{
		billrate.total *=1.10; 
		printf("The total of the bill is         : RM%.2f", billrate.total);
	}
	else if(custinfo.day == 'N')
	{
		printf("The total of the bill is         : RM%.2f", billrate.total);
	}
	custinfo.ttbill = billrate.total;
	
	return 0;
}

void ranrecnum(){
	int recnum, j, runtimes=1, counter[999]={0};
	srand(time(0));
		if(runtimes==1000){
		    for(j=0;j<999;j++){
		    	counter[j]=0;
			}
			runtimes=1;
		}
		
		do{
			recnum = rand() % 999 + 1;
		}while (counter[recnum-1]!=0);
		
		custinfo.recnum=recnum;
		
		if(custinfo.recnum<10){
			printf("Receipt number                   : 00%d",custinfo.recnum);
		}
		else if(custinfo.recnum<100){
			printf("Receipt number                   : 0%d",custinfo.recnum);
	}
		else{
		    printf("Receipt number                   : %d",custinfo.recnum);
	}	
		runtimes++;
		counter[recnum-1]++;
		
}

void monthcr(){
	if(custinfo.mm==1){
		strcpy(custinfo.month,"January");
	}
	else if(custinfo.mm==2){
		strcpy(custinfo.month,"February");
	}
	else if(custinfo.mm==3){
		strcpy(custinfo.month,"March");
	}
	else if(custinfo.mm==4){
		strcpy(custinfo.month,"April");
	}
	else if(custinfo.mm==5){
		strcpy(custinfo.month,"May");
	}
	else if(custinfo.mm==6){
		strcpy(custinfo.month,"June");
	}
	else if(custinfo.mm==7){
		strcpy(custinfo.month,"July");
	}
	else if(custinfo.mm==8){
		strcpy(custinfo.month,"August");
	}
	else if(custinfo.mm==9){
		strcpy(custinfo.month,"September");
	}
	else if(custinfo.mm==10){
		strcpy(custinfo.month,"October");
	}
	else if(custinfo.mm==11){
		strcpy(custinfo.month,"November");
	}
	else if(custinfo.mm==12){
		strcpy(custinfo.month,"December");
	}
}
