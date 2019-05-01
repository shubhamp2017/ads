#include<iostream>
#include<iomanip>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<cstdio>
using namespace std;

class hashing
{
	private:
		   int id,chain,rec[100];
		   char name[20];
	public:
		  hashing()
		  {
			for(int i = 0; i < 5; i++ )
			{
				rec[i].id = -1;
				rec[i].chain = -1;
				strcpy( rec[i].name, "-" );
			}
		  }
		  int hash( int );			// Function to calculate hash key
		  int woreplace( hashing );   // Collision without replacement
		  int wreplace( hashing );    // Collision with replacement
		  void send_to_file();        // File Handling
		  void finddata();            // Searching the data
		  void getRecord();           // Accepting records
}rec[10],temp;

void hashing :: getRecord()
{
	cout << endl << "Enter ID :";
	cin >> id;
	cout << endl << "Enter Name:";
	cin >> name;
}

int hashing :: hash( int no )
{
	int key;
	key = no % 10;      //calculating key
	return( key );
}

int hashing :: woreplace( hashing h )
{
	int k, p;            // Storing key and position for chain table
	k = hash( h.id );    // Calculating key using hash function
	p = k;
	if( rec[k].id == -1 )
	{
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else
	{
		for(int i = k+1; i < 5; i++ )    //Search Empty position i.e -1
		{
			if ( hash( rec[i].id ) == k )
			{
				p = i;
			}
			if( rec[i].id == -1 )
			{
				rec[i].id = h.id;
				strcpy( rec[i].name, h.name );
				if( hash( rec[p].id ) == k )
					rec[p].chain = i;
				return (0);
			}
		}
	}
}

int hashing :: wreplace( hashing h )
{
	int k, p;            // Storing key and position for chain table
	k = hash( h.id );    // Calculating key using hash function
	p = k;
	int tmpkey;
	if( rec[k].id == -1 )
	{
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else
	{
		if( hash(rec[k].id ) == k )
		{
			for(int i = k+1; i < 5; i++ )
			{
				if ( hash( rec[i].id ) == k )
				{
					p = i;
				}
				if( rec[i].id == -1 )
				{
					rec[i].id = h.id;
					strcpy( rec[i].name, h.name );
					if( hash( rec[p].id ) == k )
						rec[p].chain = i;
					return (0);
				}
			}
		}
		else
		{
		   p = k;
		   temp.id = rec[k].id;
		   strcpy( temp.name, rec[k].name);
		   tmpkey = hash( temp.id );
		   rec[k].id = h.id;
		   strcpy( rec[k].name, h.name );
		   rec[k].chain = -1;

		   for(int i = k+1; i < 5; i++ )
			{
				if ( hash( rec[i].id ) == k )
				{
					p = i;
				}
				if( rec[i].id == -1 )
				{
					rec[i].id = temp.id;
					strcpy( rec[i].name, temp.name );
					rec[i].chain = -1;
					rec[tmpkey].chain = i;
					return (0);
				}
			}
		}
	}
}

void hashing :: send_to_file()
{
/*********************** WRITE INTO FILE STARTS *************************/

	ofstream o;
	o.open("emp.dat",ios::out|ios::app);
	for( int i = 0; i < 5; i++ )
	{
		o.write((char *)&rec[i],sizeof(rec[i]) );
	}
	o.close();

/*********************** WRITE INTO FILE ENDS *************************/

/*********************** READ FROM FILE STARTS *************************/
	ifstream ii;
	ii.open("emp.dat",ios::in);
	ii.seekg(0);
	cout << endl << "\t" << "Key" << "\t" << "ID" << "\t" << "Name" <<"\t" << "Chain" << endl;
	for( i = 0; i < 5; i++ )
	{
		ii.read((char *)&rec[i],sizeof(rec[i]) );
		cout << endl << "\t" << i << "\t" << rec[i].id << "\t" << rec[i].name <<"\t" << rec[i].chain << endl;
	}
	ii.close();
/*********************** READ FROM FILE ENDS *************************/
}

void hashing::finddata()
{
	int n;
	ifstream f;
	cout << endl << "Searching Records::" << endl;
	cout << "Enter ID :-> ";
	cin >> n;
	f.open("emp.dat", ios::in);

	int pos = hash(n);
	int file_pos = 0;
	f.seekg(0);

	while(f)
	{
		f.read((char*)&rec[5], sizeof(rec[5]));
		if (rec[5].id==n )
		{
		 cout << endl <<"id=="<< rec[pos].id << "\t" << rec[pos].name << endl;
		 break;
		 }
		else
		{
			if(rec[pos].chain!=-1)
			{
				pos = rec[pos].chain;
			}
		}
		file_pos=f.tellg();
		f.seekg(file_pos);
}
	 f.close();
}

int main()
{
	int ch,no;
	hashing h,h1;
	char ch1,ans;

	do
	{
			cout << endl << "\t------- Collision Handling ------- ";
			cout << endl << "\t 1. Without replacement ";
			cout << endl << "\t 2. With replacement";
			cout << endl << "\t 3. Exit";
			cout << endl << "\t Enter your choice :-> ";
			cin >> ch;
			switch(ch)
			{
				case 1:
					do
					{
						h.getRecord();
						h1.woreplace(h);
						cout << endl << "Do you want to add more elements?";
						ch1 = getche();
					}while( ch1 == 'y' || ch1 == 'Y' );
					h.send_to_file();
					h.finddata();
					break;
				case 2:
					do
					{
						h.getRecord();
						h1.wreplace(h);
						cout << endl << "Do you want to add more elements?";
						ch1 = getche();
					}while( ch1 == 'y' || ch1 == 'Y' );
					h.send_to_file();
					h.finddata();
					break;
				case 3:
					exit(0);
			}
			cout << endl << "Do you want to continue?";
			ans = getche();
	}while( ans == 'y' || ans == 'Y' );

}
