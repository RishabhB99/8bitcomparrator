#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node{
    int key;
    char color;
    struct node *left;
    struct node *right;
    struct node *parent;
} ;
struct node* root=NULL;
int blackheight(){
  int b = 0;
  struct node* p = root;
  if(p->color=='b')
    b++;
  while(p->left!=NULL){
    p = p->left;
    if(p->color == 'b')
      b++;
  }
   return b; 
}
void search(int value){
  int b = 0;
  struct node* p = root;
  while(p!=NULL)
  {
    if(p->key==value)
    {
      if(p->color == 'b')
        b++;
      if(p->color=='b')
      printf("%c,%d ",p->color,b-blackheight()+1);
      else
      printf("%c,%d ",p->color,b-blackheight());
      return;
    }
    else if(p->key>value)
    {
      if(p->color == 'b')
        b++;
      p = p->left;
    }
    else
    {
      if(p->color == 'b')
        b++;
      p = p->right;
    }  
  }
  printf("-1,-1 ");
}
int s(int value){
  struct node* p = root;
  while(p!=NULL)
  {
    if(p->key==value)
    {
      return 1;
    }
    else if(p->key>value)
    {
      
      p = p->left;
    }
    else
    {
      
      p = p->right;
    }  
  }
  return 0;
}
void leftRotate(struct node *x){
    struct node *y;
    y = x->right;  
    x->right = y->left; 
    if( y->left != NULL)
    {
        y->left->parent = x; 
    }
    y->parent = x->parent; 
    if( x->parent == NULL){
        root = y;
    }
    else if((x->parent->left!=NULL) &&  (x->key == x->parent->left->key)){
        x->parent->left = y; 
    }
    else x->parent->right = y;
    y->left = x;
    x->parent = y; 

    return;
}

void rightRotate(struct node *y){
    struct node *x;
    x = y->left; 
    y->left = x->right; 
    if ( x->right != NULL){
        x->right->parent = y;
    }
    x->parent = y->parent; 
    if( y->parent == NULL){
        root = x;
    } 
    else if( (y->parent->left!=NULL) && (y->key == y->parent->left->key)){
        y->parent->left = x; 
    }
    else y->parent->right = x;
    x->right = y; 
    y->parent = x; 

    return;

}
void fix_delete(struct node *x){          
    while (x != root && x->color == 'b'){
        struct node *w = NULL;
        if ((x->parent->left!=NULL) && (x == x->parent->left)){
            w = x->parent->right;
            if ((w!=NULL) && (w->color == 'r')){
                w->color = 'b';
                x->parent->color = 'r';
                leftRotate(x->parent);
                if(x->parent!=NULL)
                    w = x->parent->right;
            }
            if((w!=NULL) && (w->color=='b') && (w->left->color == 'b') && (w->right->color == 'b')){
                w->color = 'r';
                if(x->parent->color=='r'){
                    x->parent->color='b';
                    x=root;
                }
                else
                    x = x->parent;
            }
            else if((w!=NULL) &&(w->color=='b') && (w->right->color == 'b')){
                w->left->color = 'b';
                w->color = 'r';
                rightRotate(w);
                w = x->parent->right;
            }
            if((w!=NULL) && (w->color=='b')&&(w->right->color=='r')){
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->right->color = 'b';
                leftRotate(x->parent);
                x = root;
            }
        }
        else if(x->parent!=NULL){
            w = x->parent->left;
            if ((w!=NULL) && (w->color == 'r')){
                w->color = 'b';
                x->parent->color = 'r';
                rightRotate(x->parent);
                if(x->parent!=NULL)
                    w = x->parent->left;
            }
            if((w!=NULL) &&(w->color=='b')&& (w->right->color == 'b') && (w->left->color == 'b')){
                w->color = 'r';
                if(x->parent->color=='r'){
                    x->parent->color='b';
                    x=root;
                }
                else
                    x = x->parent;
            }
            else if((w!=NULL) && (w->color=='b') && (w->left->color == 'b')){
                w->right->color = 'b';
                w->color = 'r';
                leftRotate(w);
                w = x->parent->left;
            }
            if((w!=NULL) && (w->color=='b')&&(w->left->color=='r')){
                w->color = x->parent->color;
                x->parent->color = 'b';
                w->left->color = 'b';
                rightRotate(x->parent);
                x = root;
            }
        }
    } 
    x->color = 'b';
}
void delete(int value){
  struct node* p = root;
  int flag = 0;
  struct node* q;
  while(p!=NULL)
  {
    if(p->key==value)
    {
      if(p->right!=NULL)
      {
        q = p->right;
        while(q->left!=NULL)
        {
          q = q->left;
        }
        p->key = q->key;
        
      }
      else
        q = p;
      fix_delete(q);
      free(q);
      flag = 1;
      break;
    }
    else if(p->key>value)
    {
      p = p->left;
    }
    else
    {
      p = p->right;
    }  
  }
  if(flag == 0)
    printf("-1 ");
  else
    printf("%d ",blackheight());
}

void fix_insert(struct node *z){
    struct node *y=NULL;
    while ((z->parent != NULL) && (z->parent->color == 'r')){
       if ( (z->parent->parent->left != NULL) && (z->parent->key == z->parent->parent->left->key)){
            if(z->parent->parent->right!=NULL)
                y = z->parent->parent->right;
            if ((y!=NULL) && (y->color == 'r')){
                  z->parent->color = 'b';
                   y->color = 'b';
                    z->parent->parent->color = 'r';
                    if(z->parent->parent!=NULL)
                    z = z->parent->parent;
            }
            else{
                if ((z->parent->right != NULL) && (z->key == z->parent->right->key)){
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                rightRotate(z->parent->parent);
            }
      }
      else{
            if(z->parent->parent->left!=NULL)
            y = z->parent->parent->left;
            if ((y!=NULL) && (y->color == 'r')){
                z->parent->color = 'b';
                y->color = 'b';
                z->parent->parent->color = 'r';
                if(z->parent->parent!=NULL)
                z = z->parent->parent;
            }
            else{
               if ((z->parent->left != NULL) && (z->key == z->parent->left->key)){
                   z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = 'b';
                z->parent->parent->color = 'r';
                leftRotate(z->parent->parent);
            }
        }
    }          
    root->color = 'b';
}
void insert(int value){
    struct node* z = (struct node*)malloc(sizeof(struct node));
    z->key=value;
    z->left=NULL;
    z->right=NULL;
    z->color='r';
    struct node* x=root;
    struct node* y;
    if(root==NULL){
        root=z;
        root->color='b';
        return;
    }
    while(x!=NULL){
        y=x;
        if(z->key<x->key)
            x=x->left;
        else
            x=x->right;
    }
    z->parent=y;
    if(y==NULL)
        root=z;
    else if(z->key<y->key)
        y->left=z;
    else
        y->right=z;
    fix_insert(z);
}
void inorder(struct node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d,%c ", root->key,root->color);
    inorder(root->right);
}
int main() {
    int n;
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        if(!s(a))
        insert(a);
        printf("%d ",blackheight());
    }
    printf("\n");
     scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        delete(a); 
    }
    printf("\n");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a;
        scanf("%d",&a);
        search(a);
    }
    return 0;
}