#include<fstream>
#include<conio.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<string>
using namespace std;

string p="admin";
fstream fp;
string tt[6][9]={	 {"Day/Time","9-10","10-11","11-12","12-1","1-2","2-3","3-4","4-5"},
					 {"Monday","OOP","DEL","CHEM","MATH","BREAK","FREE","FREE","COM"},
					 {"Tuesday","FREE","FREE","FREE","DEL","BREAK","OOP","CHEM","COM"},
					 {"Wednesday","WORK","WORK","WORK","WORK","BREAK","MATH","OOP","CHEM"},
					 {"Thursday","FREE","FREE","OOP","DEL","BREAK","FREE","FREE","FREE"},
					 {"Friday","CHEM","FREE","FREE","FREE","BREAK","MATH","MATH","DEL"}
				};

int check(int);
void save_id();
void display_id(int);
void edit_id();
void delete_id();
void arrange_ids();

class stu_data
{
    char name[20],add[30],email[20];
	int roll_number;
	long ph;
	int math,oop,del,chem,comm;
	public:
 
	long getPhone()
	{
		return ph;
	}
	int getRoll()
	{
		return roll_number;
	}	
	char* getName()
	{
		return name;
	}
	char* getAddress()
	{
		return add;
	}
	char* getEmail()
	{
		return email;
	}
	void show_id();
	void create_id();
	void edited_id();
	void operator=(stu_data&);
	friend void att_giv();
}stu1; 
	void stu_data::operator=(stu_data &stu) // Overloading = OPERATOR FOR EASY SWAPPING
	{
		strcpy(name,stu.name);
		strcpy(add,stu.add);
		strcpy(email,stu.email);
		roll_number=stu.roll_number;
		ph=stu.ph;
	}

	void stu_data:: edited_id()		// FOR EDITING PARTICULAR FIELDS
	{
			cout<<"Name: ";
			cin.ignore();
            cin.getline(name,20);

			cout<<"Phone Number: ";
			cin>>ph;
				
			cout<<"Address: ";
			cin.ignore();
            cin.getline(add,30);

            cout<<"Email address: ";
            cin>>email;
            cout<<"\n";
	}
	
	void stu_data:: create_id()		// FOR CREATING NEW RECORD
	{
            cout<<"Roll Number: ";
            cin>>roll_number;

    		if(check(roll_number))		//CHECKS FOR UNIQUE ROLL NUMMBER
			{
				cout<<"Roll Number "<<roll_number<<" already exists";
				exit(0);
			}
			cout<<"Name: ";
			cin.ignore();
            cin.getline(name,20);

			cout<<"Phone Number: ";
			cin>>ph;
				
			cout<<"Address: ";
			cin.ignore();
            cin.getline(add,30);

            cout<<"Email address: ";
            cin>>email;
            cout<<"\n";
	}
	
	void stu_data:: show_id()	//FOR DISPLAYING THE RECORD
	{
		cout<<endl<<"Roll Number: "<<roll_number;
		cout<<endl<<"Name: "<<name;
		cout<<endl<<"Phone: "<<ph;
		cout<<endl<<"Address: "<<add;
		cout<<endl<<"Email Address : "<<email;
		cout<<endl<<"Number of absents in: "<<"1) Math "<<math<<endl<<"2) OOP "<<oop<<endl<<"3) DEL "<<del<<endl<<"4) Chemistry "<<chem<<endl<<"5) Comm. Skills "<<comm<<endl;
	}

class LeaveDetails
{
	int roll;
	short date;
	short month;
	short year;
	short day;
	char rsn[50];
	public:
	short getDate()
	{
		return date;
	}
	short getMonth()
	{
		return month;
	}
	short getYear()
	{
		return year;
	}
	char *getReason()
	{
		return rsn;
	}
	int getRoll()
	{
		return roll;
	}
	short getDay()
	{
		return day;
	}
	void create_leave(int uroll);
	void show_app();
	friend void leave_app();
}l1;

int dayofweek(int d, int m, int y) 
{ 
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 }; 
    y -= m < 3; 
    return ( y + y/4 - y/100 + y/400 + t[m-1] + d) % 7; 
} 

void LeaveDetails::create_leave(int uroll)
{
	roll=uroll;
	cout<<"Enter the date in format dd mm yyyyy"<<endl;
	cin>>date>>month>>year;
	day=dayofweek(date,month,year);
	cout<<"Enter the Reason for taking the leave:  ";
	cin.ignore();
	cin.getline(rsn,50);
}

void LeaveDetails:: show_app()	//FOR DISPLAYING THE RECORD
{
	cout<<endl<<"Roll Number: "<<roll;
	cout<<endl<<"Date: "<<date<<"-"<<month<<"-"<<year;
	cout<<endl<<"Day: "<<day;
	cout<<endl<<"Reason: "<<rsn;		
}

void leave_app()
{
	bool found=false;
	int uroll;
	fstream	fp2;
	fp.open("DataBook.dat",ios::in);
	cout<<"Enter your Roll Number";
	cin>>uroll;
	while(fp.read((char*)&stu1,sizeof(stu_data)))
	{
		if(uroll==stu1.getRoll())
		{
			found=true;
			fp2.open("Applications.dat",ios::out|ios::app);
			l1.create_leave(uroll);	
			fp2.write((char*)&l1,sizeof(LeaveDetails));
			fp2.close();
			cout<<endl<<endl<<"Closed";
			getchar();
		}
	}
	fp.close();
	if(found==false)
		cout<<"Wrong Roll Number";
}
void view_leave_app(int num2)
{
	bool found=false;
	fstream fp2("Applications.dat",ios::in);
	while(fp2.read((char*)&l1,sizeof(LeaveDetails)))
	{
		if(l1.getRoll()==num2)
		{
			found=true;
			l1.show_app();
			cout<<endl;
		}
	}
	fp2.close();
	if(found == false){
	cout<<endl<<endl<<"No record found...";}    
	getchar();
}



int pass()
{
	string pass ="";
	char ch;
	cout<<"Enter password"<<endl;
	int i=0;
	while(1)
	{
		ch=getch();
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch==36||ch==64||ch==32)
		{
			pass.push_back(ch);
			putch('*');
			i++;
		}
		else if(ch=='\b'&&i>0)
		{
			cout<<"\b \b";
			i--;
			pass.pop_back(); 
			continue;
		}
		else if(ch=='\r')
		{
			break;
		}
	}
	if(p.compare(pass)==0)
	return 1;
	else
	return 0;
}

void change_pass()
{	
	string pass="";
	char ch;
	cout<<"Enter the current password: ";
	int i=0;
	while(1)
	{
		ch=getch();
		if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch==36||ch==64||ch==32)
		{
			pass.push_back(ch);
			putch('*');
			i++;
		}
		else if(ch=='\b'&&i>0)
		{
			cout<<"\b \b";
			i--;
			pass.pop_back(); 
			continue;
		}
		else if(ch=='\r')
		{
			break;
		}
	}
	if(p.compare(pass)==0)
	{
		cout<<endl<<"Enter the new password: ";
 		string pass="";
		int i=0;
		while(1)
		{
			ch=getch();
			if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||(ch>='0'&&ch<='9')||ch==36||ch==64||ch==32)
			{
				pass.push_back(ch);
				putch('*');
				i++;
			}
			else if(ch=='\b'&&i>0)
			{
				cout<<"\b \b";
				i--;
				pass.pop_back(); 
				continue;
			}
			else if(ch=='\r')
			{
				break;
			}
		}		
		p=pass;
	}
	else
	cout<<"Try Again ";
}

int check(int rollnumb)		//CHECKS FOR THE UNIQUE ROLL NUMBER
{
	stu_data stu2;
	int c=0;
	ifstream fp("DataBook.dat",ios::in);
	while(fp.read((char*)&stu2,sizeof(stu_data)))
	{
		if(rollnumb==stu2.getRoll())
		c++;
	}
	fp.close();
	return c;
}
 
void save_id()		//FOR WRITNING A NEW RECORD TO THE DATABOOK
{
	system("cls");
	cout<<"\t\t\t\t\t\tNEW ID\n\nEnter the details of the student:"<<endl;
	fp.open("DataBook.dat",ios::out|ios::app);
	stu1.create_id();
	fp.write((char*)&stu1,sizeof(stu_data));
	fp.close();
	cout<<endl<<endl<<"Id Closed";
	getchar();
}
 
void display_id(int num)		// FOR DISPLAYING A PARTICULAR ID
{
	bool found=false;
	int ch;
	fp.open("DataBook.dat",ios::in);
	while(fp.read((char*)&stu1,sizeof(stu_data)))
	{
		if(stu1.getRoll()==num)
		{
			system("cls");
			stu1.show_id();
			found=true;
		}
	}
	
	fp.close();
	if(found == false){
	cout<<endl<<endl<<"No record found...";}    
	getchar();
}

void edit_id()		// FOR EDITING EXISTING RECORD
{
	int num;
	bool found=false;
	system("cls");
	cout<<"\t\t\t\t\t\tEDIT ID\n\nEnter the roll number of student to edit: \n"<<endl;
    cin>>num;
	
	fp.open("DataBook.dat",ios::in|ios::out);
	while(fp.read((char*)&stu1,sizeof(stu_data)) && found==false)
	{
		if(stu1.getRoll()==num)
		{
			stu1.show_id();
            cout<<endl<<"\nPlease Enter The New Details of Student: "<<endl;
			stu1.edited_id();
			int pos=-1*sizeof(stu1);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&stu1,sizeof(stu1));
			cout<<endl<<endl<<"\t ID Successfully Updated...";
			found=true;
		}
	}
	fp.close();
	if(found==false)
		cout<<endl<<endl<<"ID Not Found...";
}
 
void delete_id()	// FOR DELETING A PARTICULAR RECORD
{
	int num;
	system("cls");
	cout<<"\t\t\t\t\t\tDELETE ID\n\nEnter the roll number of student whose ID is to be deleted:";
	cin>>num;
	fp.open("DataBook.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&stu1,sizeof(stu_data)))
	{
		if(stu1.getRoll()!=num)
		{
			fp2.write((char*)&stu1,sizeof(stu_data));
		}
	}
	fp2.close();
	fp.close();
	remove("DataBook.dat");
	rename("Temp.dat","DataBook.dat");
	cout<<endl<<endl<<"\tID Deleted...";
}
 
void arrange_ids()		// FOR ARRANGING RECORD ACCORDING TO ROLL NUMBER SEQUENCE and DISPLAYING ALL RECORDS
{
	ifstream fin;
	fin.open("DataBook.dat");
	fin.seekg(0,ios::end);
	const int n=fin.tellg()/sizeof(stu_data);
	fin.seekg(0,ios::beg);
	stu_data stu[n];
	for(int i=0;i<n;i++)
	{
		fin.read((char*)&stu[i],sizeof(stu_data));
	}
	fin.close();
	stu_data temp;
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(stu[j].getRoll()<stu[i].getRoll())
			{
				temp=stu[i];
				stu[i]=stu[j];
				stu[j]=temp;
			}
		}
	}
	ofstream fout;
	fout.open("tempe.dat");
	for(int i=0;i<n;i++)
	{
		fout.write((char*)&stu[i],sizeof(stu_data));
	}
	fout.close();
	remove("DataBook.dat");
	rename("Tempe.dat","DataBook.dat");
	for(int i=0;i<n;i++)
	{
		stu[i].show_id();
		cout<<endl<<"=================================================\n"<<endl;
	}
}

void view_tt()
{
	system("cls");
	cout<<"\t\t\t\t\t\tTIME TABLE\n\n";
	for(int i=0;i<6;i++)
	{
		for(int j=0;j<9;j++)
		cout<<setw(9)<<tt[i][j]<<" ";
		cout<<endl;
	}
}
void att_giv()
{
	int m,c,o,d,co;
	char accept;
	fstream fp2("DataBook.dat",ios::in|ios::out);
	fp.open("Applications.dat",ios::in|ios::out);
	while(fp.read((char*)&l1,sizeof(LeaveDetails)))
	{
		l1.show_app();
		cout<<endl<<"Accept the application? Enter y or n"<<endl;
		cin>>accept;
		if(accept=='y'||accept=='Y')
		{
			while(fp2.read((char*)&stu1,sizeof(stu_data)))
			{
				if(stu1.getRoll()==l1.getRoll())
				{
					m=stu1.math;
					c=stu1.chem;
					o=stu1.oop;
					d=stu1.del;
					co=stu1.comm;
					for(int i=1;i<6;i++)
					{
						if(i==l1.getDay())
						{
							for(int j=1;j<9;j++)
							{
								if(tt[i][j]=="MATH")
									stu1.math=++m;
								else if(tt[i][j]=="CHEM")
									stu1.chem=++c;
								else if(tt[i][j]=="COM")
									stu1.comm=++co;
								else if(tt[i][j]=="DEL")
									stu1.del=++d;
								else if(tt[i][j]=="OOP")
									stu1.oop=++o;
							}
							int pos=-1*sizeof(stu1);
							fp2.seekp(pos,ios::cur);
							fp2.write((char*)&stu1,sizeof(stu1));
							cout<<"Success!"<<endl;
						}
					}
				}
			}
			fp2.clear();
			fp2.seekg(0,ios::beg);
			fp2.seekp(0,ios::beg);
		}
		//else if(accept=='n'||accept=='N')
			//?delete the appl.
		else cout<<"Leave not granted."<<endl;;
	}
	fp.close();
	fp2.close();
	remove("Applications.dat");
}
int main(int argc, char *argv[])
{
	system("cls");
	//system("color 30");
	
    for(;;)
    {
		int ch;
    	cout<<"\n\t **** Student Database Management System ****";
   		cout<<"\n\t\t\t\t\t\tMAIN MENU\n\n\t\t[1] Add a new ID\n\t\t[2] List all ID's\n\t\t[3] Search for an ID\n\t\t[4] Edit an ID\n\t\t[5] Delete an Id\n\t\t[6] Change Password\n\t\t[7] View Time Table\n\t\t[8] Apply for leave\n\t\t[9] View Leave Application History\n\t\t[10] Grant Leave\n\t\t[0] Exit\n\t\t=================\n\t\t";
    	cout<<"Enter the choice:";
 
    	cin>>ch;
 
    	switch(ch)
    	{
    		case 0: cout<<"\n\n\t\tThe databse has been closed.";
    				exit(0);
    				break;
    		case 1: if(pass()==1)
					{
						cout<<"\t\t\t\tWelcome"<<endl;
						save_id();
						break;
					}
					else
					{
						cout<<"\t\t\t\tWrong Password";
						break;
					}
    		case 2: arrange_ids();
					break;
   			case 3:	int num;
            		system("cls");
            		cout<<"\n\n\tRoll Number: ";
            		cin>>num;
					display_id(num);
    				break;
    		case 4: if(pass()==1)
					{
						cout<<"\t\t\t\tWelcome"<<endl;
						edit_id();
						break;
					}
					else
					{
						cout<<"\t\t\t\tWrong Password";
						break;
					}
    		case 5: if(pass()==1)
					{
						cout<<"\t\t\t\tWelcome"<<endl;
						delete_id();
						break;
					}
					else
					{
						cout<<"\t\t\t\tWrong Password";
						break;
					}
			case 6: change_pass();
					break;
			case 7: view_tt();
					break;
			case 8: leave_app();
					break;
			case 9: int num2;
            		cout<<"\n\n\tRoll Number: ";
            		cin>>num2;
					view_leave_app(num2);
					break;
			case 10:if(pass()==1)
					{
						att_giv();
						break;
					}
					else
					{
						cout<<"\t\t\t\tWrong Password";
						break;
					}
    		default:cout<<"Wrong button pressed!";
    	}
		
		int opt;
   		cout<<"\n\n\n-->Enter the Choice:\n\n\t[1] Main Menu\t\t[0] Exit\n";
 		cin>>opt;
		switch (opt)
		{
 			case 1:
				system("cls");
        		continue;
 
    		case 0:
 	       		exit(0);
			default:
				cout<<"Wrong button pressed!";
		}
	}
	return 0;
}
