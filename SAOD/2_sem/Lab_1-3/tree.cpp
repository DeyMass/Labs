#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

int H;
int CHH;
int CS;
int S;
int MIDH;
int BR;

struct tree{
    int data;
    tree *l;
    tree *r;
    };
    
void graph(tree *head);
int shir(int n);
void graphtree(tree *head, int xhead, int yhead, int level);
void delete_vertex(tree *&head, int data);
bool define_tree(tree* head);

void print_struct (tree *m){	
	if ( !m ) return;
	print_struct (m->l);
	printf("%3d ",m->data);
	CS += m->data;
	print_struct (m->r);
}



void BinTrMaking(int *A, int first, int last, tree *&head){
    int i = (int)((first + last) / 2);
    CHH++;
    head = new tree;
    head->data = A[i];
    head->l = head->r = NULL;
    S++;
    int p;
    if (i < last){
    	p = i+1;
            BinTrMaking(A, p, last, head->r);
    }
    if (i > first){
        p = i-1;
		  BinTrMaking(A, first, p, head->l);
	}
	MIDH += CHH;
	BR++;
    if(CHH > H)
		H = CHH;
	CHH--; 
    return;
    }
    
void RandTrMakingTwice (int data, tree *&head){
    tree **p = &head;
    S++;
    while (*p){
        if (data < (*p)->data) {p = &((*p)->l); CHH++;}
        else if (data > (*p)->data) {p = &((*p)->r); CHH++;}
            else if (data == (*p)->data) {
                    //CHH = 0;
                    S--; 
                    return;}
    }
    if (!(*p)){
        (*p) = new tree;
        (*p)->data = data;
        (*p)->r = (*p)->l = NULL;
        MIDH += CHH;
        BR++;
        if (CHH > H)
            H = CHH;
        CHH = 1;
    }
}

void RandTrMaking (int data, tree *&head){
   if (head == NULL){    
        head = new tree;
        head->data = data;
        head->l = head->r = NULL;  
        S++;
        MIDH += CHH;
        BR++;
        if (CHH > H)
            H = CHH;
        CHH = 1;
    }
    if (data > head->data) {RandTrMaking (data, head->r); CHH++;}
    else if (data < head->data) {RandTrMaking (data, head->l); CHH++;}
        else if (data == head->data) {
            CHH = 1;
            return;
            }

}
       
tree *t_search (tree *m, int key)
{
	if ( !m ) return NULL;
	if (key == m->data)
		return m;
	if (key < m->data)
		return t_search (m->l,key);
	else return t_search (m->r,key);
	
}
       
void InsertSort (int *a, int n)     
{int i,j,key;
for (j=1;j<n;j++)
{key=a[j];
i=j-1;
while(i>=0 && a[i]>key)
{a[i+1]=a[i];
i--;
          }
 a[i+1]=key;        
}
} 

void ClearTree(tree *S){
    if ( S->l )
        ClearTree ( S->l );
    if ( S->r )
        ClearTree ( S->r );
    free (S);
}

main(){
	srand (time(NULL));
    int n = 10;
    int key;
    int *A = new int [n];
    tree *h;
    tree *see = NULL;
    int i,j;
    CS = H = S = MIDH = BR = 0; 
    CHH = 0;
    
    printf("Input array: \n");
    for (i=0;i<n;i++){
		A[i] = rand()%200 + 10;
		CS += A[i];
		for(j=0;j<i;j++){
            if (A[j] == A[i]) break;   
        }
        if (j < i) {CS -= A[i]; i--;}
        else printf("%4d",A[i]);
	}
	InsertSort (A, n);
	printf(" \nSorted array: \n");
	for (i=0;i<n;i++){
        printf("%4d",A[i]);
    }
    printf("\nCS - %d", CS);
    CS = 0;
    
    puts("\n\n******************  LAB 1  *******************************");
    
    BinTrMaking(A, 0, n-1, h);
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nISDP: CS - %d, HEIGHT - %d, SIZE - %d, MIDDLEH - %d", CS, H, S, (MIDH/BR)+2);
    graph(h);
    ClearTree (h);
    h = NULL;
    CS = 0;
    
    puts("\n\n**********************  LAB 2  ***************************");
    
    puts("\n");
    printf("\nInput array: \n");
    for (i=0;i<n;i++){
		A[i] = rand()%200 + 10;
		CS += A[i];
		for(j=0;j<i;j++){
            if (A[j] == A[i]) break;   
        }
        if (j < i) {CS -= A[i]; i--;}
        else printf("%4d",A[i]);
    }
	printf("\nCS - %d", CS);
    CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    for(i = 0; i < n; i++){
        RandTrMakingTwice (A[i], h);
    }
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nSDP: CS - %d, HEIGHT - %d, SIZE - %d, MIDDLEH - %d", CS, H, S, (MIDH/BR)+2);
    graph(h);
    bool check = define_tree(h);
    if (check)
        printf("\n It's a search tree!");
    else
        printf("\n It's not a search tree!");
    ClearTree (h);
    h = NULL;
    
    puts("\n\n*************************************************");
    
    puts("\n");
    CS = H = S = MIDH = BR = 0; 
    CHH = 1;
    for(i = 0; i < n; i++){
        RandTrMaking (A[i], h);
    }
    printf("\nTree was maden! \n");
    print_struct (h);
    printf("\nSDP: CS - %d, HEIGHT - %d, SIZE - %d, MIDDLEH - %d", CS, H, S, (MIDH/BR)+2);
    graph(h);
    /*see = t_search(h,key);
    if (see) {
    	printf("\nElement was found! %d", see->data);
    } else {
    	printf("\nElement wasn't found!");
    }*/
    while (h) {
          printf("\nEnter the key:");
          scanf ( "%d", &key );
        delete_vertex(h,key);
        print_struct (h);
        graph(h);
    }
    ClearTree (h);
    h = NULL;
    free (A);  
    system ("pause");
}

void graph(tree *head){
    int graphx = 3 + shir(H);
    int graphy = 5 + 2 * H - 1;
    initwindow(graphx * 20, graphy * 20);
    int actx,acty;
    actx = (graphx * 20) / 2;
    acty = 10;
    while (1) {
         cleardevice(); 
         graphtree (head, actx, acty, 0);
         char ch = getch();
         fflush(stdin);
         if (ch == 'a') actx+=20;
         if (ch == 'd') actx-=20;
         if (ch == 'w') acty+=20;
         if (ch == 's') acty-=20;
         if (ch == 27) break;
    }
    cleardevice();
    closegraph();
}

int shir(int n){
    if (n <= 1) return 1;
    if (n == 2) return 5;
    return shir(n-1) * 2 + 1;
}

void graphtree(tree *head, int xhead, int yhead, int level){
   // bar(xhead, yhead, xhead + 20, yhead + 20);
    int x,y,k;
    k = shir(H - level) / 4; 
    settextstyle (10,0,1);
    bgiout << head->data;
    outstreamxy(xhead + 2, yhead + 2);
    if (head->l){
        x = xhead;
        y = yhead + 20;
        line(x, y, x - 20 * k, y + 20);
        graphtree(head->l, x - 20 * k - 20, y + 20, level + 1);
    }
    if (head->r){
        x = xhead + 20;
        y = yhead + 20;
        line(x, y, x + 20 * k, y + 20);
        graphtree(head->r, x + 20 * k, y + 20, level + 1);
    }
}

void delete_vertex(tree *&head, int data){
     tree* q, *r, *s;
     tree** p = &head;
     //*p = t_search(head, data);
     while (*p != NULL) {
           if (data < (*p)->data) p = &((*p)->l);
           else if (data > (*p)->data) p = &((*p)->r);
                else break;
     }
     if (*p != NULL) {
            q = *p;
            if (q->l == NULL) *p = q->r;
            else
                 if (q->r == NULL) *p = q->l;
                 else {
                          r = q->l;
                          s = q;
                          if (r->r == NULL) {
                                   r->r = q->r;
                                   *p = r;
                          } else {
                                 while (r->r != NULL) {
                                       s = r;
                                       r = r->r;
                                 }
                                 s->r = r->l;
                                 r->l = q->l;
                                 r->r = q->r;
                                 *p = r;
                          }
                 }
            delete q;
            q = NULL;
     }
}

bool define_tree(tree* head){
     tree* p = head;
     bool dp = true;
     if (p != NULL && (
             (p->l != NULL && 
                   (p->data <= p->l->data || 
                            !define_tree(p->l)   )) 
     ||      (p->r != NULL && 
                   (p->data >= p->r->data || 
                            !define_tree(p->r)   ))
     )){ dp = false;
     }
     return dp;
}
