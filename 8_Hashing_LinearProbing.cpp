// PROGRAM TO IMPLEMENT HASH TABLE USING LINEAR PROBING WITH AND WITHOUT REPLACEMENT
// OPTIONS : INSERT AND DISPLAY
#include<iostream>
#include<stdlib.h>
#include<string.h>
#define MAX 10
using namespace std;

struct hashLP
{
	int id;
	char name[20];
}rec[MAX],tmp;

class hashtable
{
	public:
	void initialize();
	int hashing( int );
	void woreplace( struct hashLP );
	void wreplace( struct hashLP );
	void place_at_next_slot(int, struct hashLP);
	void display();
	void search(int);
};

void hashtable::initialize() {
	int i;
	for(i = 0; i < MAX; i++ ){
		rec[i].id = -1;      strcpy( rec[i].name, "-" );
	}
}// End of initialize()

int hashtable::hashing( int no ) {
	int key;
	key = no % MAX;      //calculating key
	return( key );
}// End of hashing

void hashtable::woreplace( struct hashLP h ) {
	int i,k,z;
	k = hashing( h.id );    // Calculating key using hash function

	if( rec[k].id == -1 ) {
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else  // SEARCH LINEARLY DOWN FOR EMPTY SLOT
		place_at_next_slot(k,h);
}//End of Without Replacement

void hashtable::place_at_next_slot( int k, struct hashLP h )
{ // SEARCH LINEARLY DOWN FOR EMPTY SLOT
	int i, z;
	for(i = 1; i < MAX; i++ ){
		z = (k+i)%MAX;  // (hash(key) + i)%M
		if( rec[z].id == -1 ){
			rec[z].id = h.id;
			strcpy( rec[z].name, h.name );
			break;
		}//if
	}//for

}//place at next_slot

void hashtable::display() {
	cout<<"\n Collision Handling :\n\t----------------------------------";
	cout<<"\n\t Index     ID      Name   \n\t----------------------------------\n";
	for(int i = 0; i < MAX; i++ ) {
		cout<<"\t"<<i <<"\t "<<rec[i].id;
		cout<<"\t "<<rec[i].name;
		cout<<"\n";
	}
	cout<<"\n\t----------------------------------\n";
}//display

void hashtable::wreplace( struct hashLP h )
{
	int k,p,change_pos;    // Storing key and position for chain table

	k = hashing( h.id );    // Calculating key using hash function

	if( rec[k].id == -1 )
	{
		rec[k].id = h.id;
		strcpy( rec[k].name, h.name );
	}
	else if( hashing(rec[k].id) == hashing(h.id) )//VALUE IS AT APPROPRIATE POSITION
		place_at_next_slot(k,h);
	else // HASH VALUE IS NOT AT APPROPRIATE POSITION
	{
		tmp.id = rec[k].id;
		strcpy( tmp.name, rec[k].name );

		rec[k].id = h.id;    // COPY NEW RECORD AT ITS PROPER POSITION
		strcpy(rec[k].name, h.name);

		place_at_next_slot(k,tmp);  // RE-store existing record at next EMPTY SLOT

	}// End of else
}//End of With Replacement

void hashtable::search( int key )
{
	int i,k,z;
	int flag = 0;
	k = hashing( key );    // Calculating key using hash function

	if( rec[k].id == key )
		cout << "\n Key " << key << " found at home address !!";
	else  		// SEARCH LINEARLY DOWN FOR EMPTY SLOT
	{
		for(z = 1; z < MAX; z++ ){
			i = (k+z)%MAX;
			if( rec[i].id == key ) {
				cout << "\n Key " << key << " found at "<< i << " address!!";
				flag=1;
				break;
			}
		}//end of for
		if (flag==0)
			cout << "\n Key " << key << " not present in the table";
	}
}//End of search



int main(){
	hashtable h;
	int ch,ch1,key;
	char ans;
	struct hashLP temph;
		do	{
		cout<<"\n Collision Handling ";
		cout<<"\n 1. Without Replacement \n 2. With Replacement ";
		cout<<"\n 3. Display Record \n 4. Search Record \n 5. Exit \n Enter your choice : ";
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
				break;
			case 3:
                               h.display();  break;
			case 4:
				cout << "\n Enter the id for searching: ";
				cin >> key;
                               	h.search(key);
				break;
			case 5:  exit(0);
		}// End of switch()*/
	}while( ch != 5 );
return 0;
}//End of program
