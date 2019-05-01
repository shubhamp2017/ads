/*
Binary SeaRh Tree
*/

#include<iostream>
using namespace std;
struct node
{
	int data;
	node *L, *R;
}*root,*p,*q;


class BSTree
{
	public:
		BSTree()
		{
			root = NULL;
		}

		void create( int data );  // create a new node
		void insert(node * ); // create a tree
		void inorder( node * ); //Inorder
		void display(); // cases for display: In/Pre/Post Order
};

void BSTree :: inorder(node * t)
{
	if( t != NULL )
	{
		inorder( t->L );
		cout << t->data << "  " ;
		inorder( t->R );
	}
}

void BSTree :: create( int data )
{
	node *t,*r;
	t = new node;  //Allocate the memory
	t->data = data;
	t->L = t->R = NULL;

	if ( root == NULL )
	{
		root = t;
	}
	else
	{
		r=root;
		while(1)
		{
			if( t->data < r->data )//new node is less than root node
			{
				if(r->L==0) //empty subtree
				{
					r->L = t; //add new key
					break;
				}
				else
					r=r->L; 
			}
			else if( t->data > r->data )//new node is greater than root node
			{
				if(r->R==0)  //empty subtree
				{
					r->R = t; // and new key
					break;
				}
				else
					r=r->R;
				}
		}//inner while
	}//else
}


void BSTree :: insert(node *temp )
{
		p = root;
		q = NULL;
		while( p!= NULL )
		{
			q = p; //Preserve the value of p; before moving to left/right child
			if( temp->data < p->data )
				p = p->L;
			else
				p = p->R;
		}// End of while -- Level of current node is decided
		if( temp->data < q->data ) // To decide Position of current node
			q->L = temp;
		else
			q->R = temp;

}


void BSTree :: display()
{
	node *temp;
	temp = root;
	inorder( temp );
}


int  main()
{
	int data;
	BSTree bt;  //create an object of class BSTree
	int n;
	cout << "How many nodes you want in a tree?";
	cin >> n;
	for(int i = 0;i < n; i++ ) // Ask user to enter the values
	{
		cout << "\n Enter node :: ";
		cin >> data;
		bt.create(data);
	}
	
	bt.inorder(root);
	cout << "\n";
}

