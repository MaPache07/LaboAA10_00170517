#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<vector>

using namespace std;

struct node{
    int key;
    struct node *left, *right;
};

struct node *newNode(int item){
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root){
    if (root != NULL){
        inorder(root->left);
        printf("%d \n", root->key);
        inorder(root->right);
    }
}

void preorder(struct node *root){
    if (root != NULL){
        printf("%d \n", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

struct node* insert(struct node* node, int key){
    if (node == NULL)
        return newNode(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

void defVector(struct node *node, vector<int> &v){
    if(node != NULL){
        defVector(node->left, v);
        v.push_back(node->key);
        defVector(node->right, v);
    }
}

struct node *balance(vector<int> v, struct node *node, int i, int f){
    cout << i << " " << f << endl;
    if((i-f != 1 && i-f != -1) && i != f){
        int q = (f-i)-((f-i)/2);
        if(i == 0 && f == v.size()-1) node = insert(node, v.at(i+q));
        else insert(node, v.at(q));
        balance(v, node, i, q-1);
        balance(v, node, q+1, f);
    }
    else {
        insert(node, v.at(i));
    }
    return node;
}

struct node *preBalance(struct node *node){
    vector<int> v;
    defVector(node, v);
    struct node *root = NULL;
    return balance(v, root, 0, v.size()-1);
}

int main(){
    struct node *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);
    root = preBalance(root);
    return 0;
}
