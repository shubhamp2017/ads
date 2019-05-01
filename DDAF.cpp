// PROGRAM TO IMPLEMENT HASH TABLE USING LINEAR PROBING WITH AND WITHOUT REPLACEMENT
// OPTIONS : INSERT AND DISPLAY
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include <iomanip>      // std::setw
#define MAX 10
using namespace std;

struct hashLP
{
	int id, chain;
	char name[20];
}rec[MAX],tmp;

class hashtable
{
	public:
	void initialize();
	int hashing( int );
	void woreplace( struct hashLP );
	void wreplace( struct hashLP );
	void place_at_next_slot(int, int, struct hashLP);
	void display();
	void search(int);
		  void read_file();
		  void send_to_file();
};

void hashtable::initialize() {
	int i;
	for(i = 0; i < MAX; i++ ){
		rec[i].id = -1;
		strcpy( rec[i].name, "-" );
		rec[i].chain = -1;
	}
}// End of initialize()

int hashtable::hashing( int no ) {
	int key;
	key = no % MAX;      //calculating key
	return( key );
}// End of hashing

void hashtable::woreplace( struct hashLP h ) {
	int i,k,z,org_index;
	k = hashing( h.id );    // Calculating key using hash function
	org_index = k;

	if( rec[k].id == -1 ) {
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else  // SEARCH LINEARLY DOWN FOR EMPTY SLOT
		place_at_next_slot(k,org_index,h);
}//End of Without Replacement

void hashtable::place_at_next_slot( int k, int org_index, struct hashLP h )
{ // SEARCH LINEARLY DOWN FOR EMPTY SLOT
	int i, z;
	int flag=0;
	for(i = 1; i < MAX; i++ ){
		z = (k+i)%MAX;  // (hash(key) + i)%M
		if( rec[z].id == -1 )
		{
			rec[z].id = h.id;
			strcpy( rec[z].name, h.name );
			if(hashing(rec[org_index].id) == k)  //linking same index values
				rec[org_index].chain = z;
			flag = 1;  //For updating chains for with-replacement
			break;
		}//if
		if( hashing( rec[z].id ) == k )  // MAINTAIN CHAIN
			   org_index = z;
	}//for
	if(flag==1)
	{
		rec[org_index].chain=z;
	}//flag

}//place at next_slot

void hashtable::wreplace( struct hashLP h )
{
	int k,p,org_index,change_pos;    // Storing key and position for chain table


	k = hashing( h.id );    // Calculating key using hash function
	org_index = k;

	if( rec[k].id == -1 )
	{
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else if( hashing(rec[k].id) == hashing(h.id) )//VALUE IS AT APPROPRIATE POSITION
		place_at_next_slot(k,org_index,h);  //Pass new key for next empty position
	else // HASH VALUE IS NOT AT APPROPRIATE POSITION
	{
		// COPY EXISTING RECORD IN TMP RECORD
		tmp.id = rec[k].id;
		strcpy( tmp.name, rec[k].name );
		tmp.chain = rec[k].chain;

		// COPY NEW RECORD AT ITS PROPER POSITION
		rec[k].id = h.id;
		strcpy(rec[k].name, h.name);
		rec[k].chain = -1;

		place_at_next_slot(k,hashing(tmp.id),tmp);  // RE-store existing record at next EMPTY SLOT

	}// End of else
}//End of With Replacement

void hashtable::send_to_file()
{
	ofstream o;
	o.open("emp.txt",ios::binary |ios::out);
	o.seekp(0);
	for( int i = 0; i < MAX; i++ )
	{
		o.write((char *)&rec[i],sizeof(rec[i]) );
	}
	o.close();
	read_file();
}

void hashtable::read_file()
{	ifstream in_file;
	hashLP result[MAX];int i;
	in_file.open("emp.txt",ios::binary |ios::in);
	in_file.seekg(0);
	cout << endl << std::setw(10) << "Position" << std::setw(10) << "ID"  << std::setw(15) << "Name" << std::setw(10) << "Chain";
	for( i = 0; i < MAX; i++ )
	{
		in_file.read((char *)&result[i],sizeof(result[i]) );

		cout << endl << std::setw(10) << i << std::setw(10) << result[i].id  << std::setw(15) << result[i].name<< std::setw(10) << result[i].chain;
	}
	in_file.close();
}

// function to search and display from binary file
void hashtable:: search(int n)
{
	int index,file_pos,record_present=0;
	fstream inFile;
	inFile.open("emp.txt", ios::binary|ios::in);

	index = hashing(n);
	file_pos = index * sizeof(tmp);
	inFile.seekp(file_pos,ios::beg);

	while(inFile.read((char*)&tmp, sizeof(tmp)))
	{
		if(tmp.id == n)
		{
			cout << endl << tmp.id << "\t" << tmp.name;
			record_present=1;
			break;
		}
		else if( hashing(tmp.id) == hashing(n) && tmp.chain != -1)
		{
			// HASH VALUE MATCHES WITH CHAIN PRESENT
			file_pos = tmp.chain * sizeof(tmp);
			inFile.seekp(file_pos,ios::beg);
		}
		else if( hashing(tmp.id) == hashing(n))
		{
			file_pos = 0;
			inFile.seekp(file_pos,ios::beg);
		}
	}//while
	inFile.close();
	if(record_present==0) cout <<"\n Record not found";
}


int main(){
	hashtable h;
	int ch,ch1,key;
	char ans;
	struct hashLP temph;
		do	{
		cout<<"\n Collision Handling ";
		cout<<"\n 1. Without Replacement \n 2. With Replacement ";
		cout<<"\n 3. Search Record \n 4. Exit \n Enter your choice : ";
		cin>>ch;
		switch(ch){
			case 1:
				h.initialize();
				do {
					cout<<"\n Enter ID : ";
					cin>>temph.id;
					cout<<"\n Enter Name : ";
					cin>>temph.name;
					h.woreplace(temph);
					cout<<"\n Do you want to add more elements(0/1)? ";
					cin>>ch1;
				}while( ch1 != 0 );
				h.send_to_file();
				break;

			case 2:
				h.initialize();
				do{
					cout<<"\n Enter ID : ";
					cin>>temph.id;
					cout<<"\n Enter Name : ";
					cin>>temph.name;
					h.wreplace(temph);
					cout<<"\n Do you want to add more elements(0/1)? ";
					cin>>ch1;
				}while( ch1 != 0 );
				h.send_to_file();
				break;
			case 3:
                               	cout << "\n Enter the id for searching: ";
				cin >> key;
                               	h.search(key);
				break;
			case 4:  exit(0);
		}// End of switch()*/
	}while( ch != 4 );
return 0;
}//End of program


/* OUTPUT
hp@slave1:~/Desktop$ g++ DAF.cpp -o p && ./p

 Collision Handling
 1. Without Replacement
 2. With Replacement
 3. Search Record
 4. Exit
 Enter your choice : 1

 Enter ID : 12

 Enter Name : Asha

 Do you want to add more elements(0/1)? 1

 Enter ID : 13

 Enter Name : Sheetal

 Do you want to add more elements(0/1)? 1

 Enter ID : 2

 Enter Name : Rahul

 Do you want to add more elements(0/1)? 1

 Enter ID : 14

 Enter Name : Rayan

 Do you want to add more elements(0/1)? 1

 Enter ID : 99

 Enter Name : Raghav

 Do you want to add more elements(0/1)? 1

 Enter ID : 89

 Enter Name : Jyoti

 Do you want to add more elements(0/1)? 0

  Position        ID           Name     Chain
         0        89          Jyoti        -1
         1        -1              -        -1
         2        12           Asha         4
         3        13        Sheetal        -1
         4         2          Rahul         5
         5        14          Rayan        -1
         6        -1              -        -1
         7        -1              -        -1
         8        -1              -        -1
         9        99         Raghav         0
 Collision Handling
 1. Without Replacement
 2. With Replacement
 3. Search Record
 4. Exit
 Enter your choice :  2

 Enter ID : 12

 Enter Name : Asha

 Do you want to add more elements(0/1)? 1

 Enter ID : 13

 Enter Name : jyoti

 Do you want to add more elements(0/1)? 1

 Enter ID : 2

 Enter Name : raghav

 Do you want to add more elements(0/1)? 1

 Enter ID : 14

 Enter Name : Rayan

 Do you want to add more elements(0/1)? 1

 Enter ID : 99

 Enter Name : Rahul

 Do you want to add more elements(0/1)? 1

 Enter ID : 44

 Enter Name : Rushikesh

 Do you want to add more elements(0/1)? 0

  Position        ID           Name     Chain
         0        -1              -        -1
         1        -1              -        -1
         2        12           Asha         5
         3        13          jyoti        -1
         4        14          Rayan         6
         5         2         raghav        -1
         6        44      Rushikesh        -1
         7        -1              -        -1
         8        -1              -        -1
         9        99          Rahul        -1
 Collision Handling
 1. Without Replacement
 2. With Replacement
 3. Search Record
 4. Exit
 Enter your choice : 3

 Enter the id for searching: 2

2	raghav
 Collision Handling
 1. Without Replacement
 2. With Replacement
 3. Search Record
 4. Exit
 Enter your choice : 4
*/
