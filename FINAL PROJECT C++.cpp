#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>

 
 
using namespace std;
 
class product
{
	int product_number;
	char product_name[25];
	float product_price,product_quantity,tax,product_discount;
	
	public:
 
 
  /****************************************************************************************************************/
  // for creating a new product in the entry
  
  
	void create_product()
	{
		cout<<endl<<"Enter Product Number: ";
		cin>>product_number;
		cout<<endl<<"Enter Name of Product: ";
		cin.ignore();
		cin.getline(product_name ,25);
		cout<<endl<<"Enter Price of Product: ";
		cin>>product_price;
		cout<<endl<<"Enter Discount (in%): ";
		cin>>product_discount;
	}
	
	
	 /****************************************************************************************************************/
	 // for showing the product when needed
	 
	void show_product()
	{
		cout<<endl<<"Product #: "<<product_number;
		cout<<endl<<"Product Name: "<<product_name;
		cout<<endl<<"Product Price: "<<product_price;
		cout<<endl<<"Discount : "<<product_discount;
	}
	
	
	 /****************************************************************************************************************/ 
	 //functions to get attributes like products and thier values
	 
	int getProduct()
	{
		return product_number;
	}
	
	float getPrice()
	{
		return product_price;
	}
	
	char* getName()
	{
		return product_name;
	}
	
	float getDiscount()
	{
		return product_discount;
	}
}; 
 
 
 
fstream fp;
product produc;
 
 /****************************************************************************************************************/
 
 //for displaying record
 
 void display_record(int num)
{
	bool found=false;
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()==num)
		{
			system("cls");
			produc.show_product();
			found=true;
		}
	}
	fp.close();
	if(found == true)
	cout<<"\n\nNo record found";
	getchar();
}
/****************************************************************************************************************/
 //for saving the record
 
 
void save_product()
{
	fp.open("database.dat",ios::out|ios::app);
	produc.create_product();
	fp.write((char*)&produc,sizeof(product));
	fp.close();
	cout<<endl<<endl<<" *** Product has been ADDED Sucessfully ***";
	getchar();
}

/****************************************************************************************************************/
 //for showing all the product simultaneously
 
 void show_all_product()
{
	system("cls");
	cout<<"\n\n------------------------------------------------------------------------------------------------------------------------";
	cout<<endl<<"\t\t\t\t\t\t PRODUCT LIST";
	cout<<"\n\n------------------------------------------------------------------------------------------------------------------------";
	fp.open("database.dat",ios::in);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		produc.show_product();
		cout<<endl<<"=======================================================\n"<<endl;
		//getchar();
	}
	fp.close();
}
 
 

 /****************************************************************************************************************/
//for editing the value of the product
 
void edit_product()
{
	int num;
	bool found=false;
	system("cls");
	cout<<endl<<endl<<"\tPlease Enter The Product #: ";
	cin>>num;
	
	fp.open("database.dat",ios::in|ios::out);
	while(fp.read((char*)&produc,sizeof(product)) && found==false)
	{
		if(produc.getProduct()==num)
		{
			produc.show_product();
			cout<<"\n\n------------------------------------------------------------------------------------------------------------------------";
			cout<<"\nEnter The New Details for Product: "<<endl;
			produc.create_product();
			int pos=1*sizeof(produc);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&produc,sizeof(product));
			cout<<endl<<endl<<" UPDATED Successfully ....";
			found=true;
		}
	}
	fp.close();
	if(found==false)
		cout<<endl<<endl<<"Record Not Found...";
	getchar();
}
 

/****************************************************************************************************************/
 //for deleting the product
 
 
void delete_product()
{
	int num;
	system("cls");
	cout<<endl<<endl<<"Please Enter The product #: ";
	cin>>num;
	fp.open("database.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&produc,sizeof(product)))
	{
		if(produc.getProduct()!=num)
		{
			fp2.write((char*)&produc,sizeof(product));
		}
	}
	fp2.close();
	fp.close();
	remove("database.dat");
	rename("Temp.dat","database.dat");
	cout<<endl<<endl<<"\tRecord Deleted...";
	getchar();
}


/****************************************************************************************************************/
//for getting the menu

void product_menu()
{
	system("cls");
	fp.open("database.dat",ios::in);
 
	cout<<endl<<endl<<"\t\tProduct MENU\n\n";
	cout<<"..........................................................\n";
	cout<<"P.NO.     \t\tNAME                   \t\tPRICE\n";
	cout<<"..........................................................\n";
	while(fp.read((char*)&produc,sizeof(product)))
	{
		cout<<produc.getProduct()<<"\t\t"<<produc.getName()<<"\t\t                 "<<produc.getPrice()<<endl;
	}
	fp.close();
}
 
/****************************************************************************************************************/
//customer function to palce the order 
 
void place_order()
{
	int  order_arr[50],quan[50],c=0;
	float amt,damt,total=0;
	char ch='Y';
	product_menu();
	cout<<"\n................................................";
	cout<<"\n PLACE YOUR ORDER HERE ";
	
	cout<<"\n................................................\n";
	cout<<"Enter Any Number TO Shop  ";
	cin>>ch;
	do{
		cout<<"\n\nEnter The Product Number: ";
		cin>>order_arr[c];
		cout<<"\nQuantity: ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Product ? if yes , enter any number ";
		cin>>ch;
		}
		while(ch=='y' ||ch=='Y');
	cout<<"\n\nThank You...";
	getchar();
	system("cls");
    cout<<"\n\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
	cout<<"\n\n\t\t\t\t\t\t(**BILL RECIPT**)\n";
	cout<<"\n\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
	cout<<"\nProduct No.   \tProduct Name      \tQuantity  \tPrice    \tAmount   \tAmount after discount\n";
	for(int x=0;x<=c;x++)
	{
		fp.open("database.dat",ios::in);
		fp.read((char*)&produc,sizeof(product));
		while(!fp.eof())
		{	
			if(produc.getProduct()==order_arr[x])
			{
				amt=produc.getPrice()*quan[x];
				damt=amt-(amt*produc.getDiscount()/100);
				cout<<"\n"<<order_arr[x]<<"\t        "<<produc.getName()<<"\t            "<<quan[x]<<"\t\t  "<<produc.getPrice()<<"\t           " <<amt<<"\t\t      "<<damt;
				total+=damt;
			}
			fp.read((char*)&produc,sizeof(product));
		}
		fp.close();
	}
	cout<<"\n\n------------------------------------------------------------------------------------------------------------------------";
	cout<<"\n\n\tTOTAL AMOUNT TO BE PAID = "<<"Rs"<<" "<<total;

		cout<<"\n\n///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////";
		cout<<"	\n \t\t\t\t\t(THANK YOU FOR SHOPPING WITH US)";
		cout<<"\n\n////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n";
	getchar();
}
 
 
/****************************************************************************************************************/
 //menu for admin
 
void admin_menu()
{
	system("cls");
	int option;
	cout<<"\t\tADMIN MENU ";
	cout<<"\n.............................................";
	cout<<"\n\t 1. ADD PRODUCT                      #";
	cout<<"\n\t 2. DISPLAY ALL PRODUCTS             #";
	cout<<"\n\t 3. SEARCH                           #";
	cout<<"\n\t 4. MODIFY PRODUCT                   #";
	cout<<"\n\t 5. DELETE PRODUCT                   #";
	cout<<"\n\t 6. MAIN MENU                        #";
	cout<<"\n.............................................#";
 
	cout<<"\n\n\tselectioN: ";
	cin>>option;
	switch(option)
	{
		case 1: system("cls");
				save_product();
				break;
				
		case 2: show_all_product();
				break;
				
		case 3:
				int num;
				system("cls");
				cout<<"\n\n\tEnter The Product Number: ";
				cin>>num;
				display_record(num);
				break;
				
		case 4: edit_product();
		break;
		
		case 5: delete_product();
		        break;
				
		case 6: system("cls");
				break;
		
		default:admin_menu();
	}
}

/****************************************************************************************************************/
 //this is the main function
 
 
 int main(int argc, char *argv[])
{

  	cout<<"\n-----------------------------------------------------------------------------------------------------------------------";
  	cout<<"\n\t\t\t\t\t **CSE project for STOCK TELLER**";
  	cout<<"\n=======================================================================================================================";
  	
  	
	int option;
	
	for(;;)
	{
		cout<< "\n #CHOOSE THE OPTION GIVEN BELOW:" ;
	//	cout<<"\n\n\n\t--------------------------------------------";
		cout<<"\n\n\n\n\t1. #CUSTOMER";
		cout<<"\n\t2. #ADMIN";
		cout<<"\n\t3. #EXIT";
		cout<<"\n\n\n***********************************************************************************************************************";
		
		cout<<"\n\n\n\n\t option: ";
		cin>>option;
		
		switch(option)
		{
			case 1: system("cls");
					place_order();
					getchar();
					break;
					
			case 2: admin_menu();
					break;
			case 3: 
					//cout<<"\n\t////////////////////////////////////";
					cout<<"\n\tBYE BYE....see ya bruh..!";
					//cout<<"\n\t\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\ \n";
					exit(0);
			
			default :cout<<"Invalid Input...\n";
			
		}
 
	}
}
