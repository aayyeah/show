#include <iostream>
#include <math.h>

using namespace std;

struct node // структура для представления узлов дерева
{
    int key;
    unsigned int counter;
    unsigned char height;
    node* left;
    node* right;
    node(int k) { key = k; left = right = 0; height = 1; counter = 1; }
};

unsigned char height(node* p)
{
    return p?p->height:0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
};

node* balance(node* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        p = rotateleft(p);
        return p;
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        p = rotateright(p);
        return p;
    }
    return p;
}

node* insert(node* p, int k) // вставка ключа k в дерево с корнем p
{
    if( !p ) return new node(k);
    if (k == p->key){
        p->counter++;
        balance(p);
        return p;
    }
    if( k < p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    p = balance(p);
    node *q = p;
    return q;
}

void add(node* p, int k){
    p = insert(p, k);
};

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?findmin(p->left):p;
}
//
//node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
//{
//    if( p->left==0 )
//        return p->right;
//    p->left = removemin(p->left);
//    return balance(p);
//}
//
//node* remove(node* p, int k) // удаление ключа k из дерева p
//{
//    if( !p ) return 0;
//    if( k < p->key )
//        p->left = remove(p->left,k);
//    else if( k > p->key )
//        p->right = remove(p->right,k);
//    else //  k == p->key
//    {
//        if (p->counter == 1){
//            node* q = p->left;
//            node* r = p->right;
//            delete p;
//            if( !r ) return q;
//            node* min = findmin(r);
//            min->right = removemin(r);
//            min->left = q;
//            return balance(min);
//        }else{
//            p->counter--;
//        }
//
//    }
//    return balance(p);
//}

void print(node *q, long n)
{
   long i;
   if (q)
   {
      print(q->right, n+5);
      for (i = 0; i < n; i++)
         printf(" ");
      cout << q->key << "(" << q->counter << ")" << endl;
      print(q->left, n+5);
   }
}

int main(int argc, const char * argv[]) {
    cout << "Welcome" << endl;
    node *head = new node(1);
    add(head, 8);
    add(head, 8);
    add(head, 5);
    add(head, 9);
    add(head, 6);
    add(head, 6);
    print(head, 0);
    cout << "===========" << endl;

    return 0;
}


