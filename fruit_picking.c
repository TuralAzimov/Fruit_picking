#include <stdio.h>
#include <stdlib.h>
#include<time.h>


 struct node {                      // BST yapisi
	int data;
	int first;
	struct node *left;
	struct node *right;
};

struct stack {                   // Stack yapisi
	int data;
	struct stack *next;
}*top, *top1, *temp;

struct node* meyveYarat(int data){				// BST`ye eklenecek  meyveyi yaratma
	
	struct node * tree = (struct node*)malloc(sizeof(struct node));        
    tree->data = data;
    tree->first = data;
    tree->right = NULL;
    tree->left = NULL; 
    return tree;
}


struct node* meyveEkle(struct node* tree, int data){      //BST`de uygun yere meyveyi ekleme
	if (tree== NULL){
		return meyveYarat(data);
	}
	if (data < tree->data){
		tree->left = meyveEkle(tree->left, data);
	}
	else if (data > tree->data) {
		tree->right = meyveEkle(tree->right,data);
	}
	return tree;
} 

void printPreOrder(struct node* tree){             // Visit Left Right seklinde BST yi yazdirma
	if (tree != NULL) {
	printf("%d ", tree->first);
	printPreOrder(tree->left);
	printPreOrder(tree->right);
    }
}

struct node* meyveAra(struct node* tree , int deger){       // Verilen degere sahip meyveyi arama
	if (tree == NULL || tree->first == deger){
		return tree;
	}
	if (tree->first < deger) {
		return meyveAra(tree->right,deger);
	}
	else if (tree->first > deger) {
		return meyveAra(tree->left,deger);
	}
};

struct node* minMeyve(struct node *node){          // Sag agactaki en kucuk sayiyi bulma
	struct node *current = node;
	while(current != NULL && current->left != NULL){
		current = current->left;
	}
	return current;
}


void push (int data) {                            // Stack`e deger atma
	temp = (struct stack*)malloc(sizeof(struct stack));
	temp->data = data;
    temp->next = top;
    top = temp;
	
}
int pop(){                                       // Stackden deger cekme
    int data;
    if (top == NULL) {
        printf(" Stack is empty\n");
        return 0 ;
    }
    top1 = top;
    data = top1->data;
    top = top1->next;
    free(top1);
    return data;
}

struct node* meyveSil(struct node *tree , int deger){       //BST`den meyve silme
	if (tree == NULL){
		return tree;
	}
	else  if(deger < tree->first){
		tree->left = meyveSil(tree->left, deger);
		return tree;
	}
	else if (deger > tree->first){
		tree->right = meyveSil(tree->right, deger);
		return tree;
	}
	else {
		if (tree->left == NULL){
			struct node *temp = tree->right;
			return temp;
		}
		else if(tree->right == NULL){
			struct node *temp = tree->left;
			return temp;
	    }
		else   {
		struct node *temp = minMeyve(tree->right);           // sag kisimdaki en kucuk degeri bulup 	
		    tree->first = temp->first;							 // sildigimiz node yerine yaziyoruz
		    tree->data = temp->data;
		    tree->right = meyveSil(tree->right, temp->first);
		    return tree;
	    
	    }
	}
}

struct node* meyveVur (struct node* tree, int k, int p,struct stack  **s ){    // BST`deki meyveleri alinan degere gore vurma
	struct node* tmp = meyveAra(tree,k);
	tmp->data = tmp->data - p ;
	
	
	if (tmp->data <= 0 ){
		// stack e pushla
		tree=meyveSil(tree,k);
		push(tree->first);
	}
	return tree;
	
	
}
int main() {
	int M,N,i,j,random;
	printf ("maksimum meyve agirligini ve meyve adetini giriniz : \n");
	scanf ("%d%d",&N,&M);

	int* meyveDegerleri = malloc((M)*sizeof(int));  	
	i=0; 
	srand(time(0));                               
    while ( i<(M)){
        random = rand() % N + 1;
   	    j=0;
   	while ((j<M)&&(random != meyveDegerleri[j])) {
   		j++; 
   		if (j == M ) {
			meyveDegerleri[i]=random;
			i++;
	    	} 
		}		    
    }
    struct node* root = NULL;
    for(i=0;i<M;i++){
    	
      root = meyveEkle( root, meyveDegerleri[i]);
      
	}
    printf("Agacin ilk halinin Pre Order gosterimi :  ");
    printPreOrder(root);
    struct stack  *s = NULL ;
    int k,p;
    while (root!=NULL){
    	printf (" \nVurmak istediginiz degeri ve atis gucunu giriniz : \n");
    	scanf("%d%d",&k,&p);
    	while (meyveAra(root,k)== NULL){
    		printf("\nGirdiginiz meyve degeri dizide yok lutfen yeni degerler giriniz : \n");
    		scanf("%d%d",&k,&p);
    		
		}
    	root = meyveVur(root,k,p,&s);
    	printf("\nAtistan sonra agac ");
    	printPreOrder(root);

	}
	while (s->next != NULL){
		printf("%d ", pop());
	}
	printf("\n");
    free(meyveDegerleri);
    return 0; 
}
