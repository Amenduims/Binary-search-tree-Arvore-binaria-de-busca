#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct node Node;

typedef struct node{
    int key;
    Node *left, *right, *father;
}Node;


typedef struct abb{
    Node *root;
    
}ABB;



ABB* createTree(){
    ABB *tree = malloc(sizeof(ABB));
    
    tree->root = NULL;
    
    return tree;
}

Node* createNode(int key){
    Node* newNode = malloc(sizeof(Node));
    
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->father = NULL;
    
    return newNode;

}

///////////////////////////////////////////

void insertAux(Node* root, Node *newNode){
    if(newNode->key < root->key){
        if(root->left == NULL){
            root->left = newNode;
            newNode->father = root;
        }else{
            insertAux(root->left, newNode);
        }
        
    }else if(newNode->key > root->key){
        if(root->right == NULL){
            root->right = newNode;
            newNode->father = root;
        }else{
            insertAux(root->right, newNode);
        }
    }
}

void insert(ABB *tree, int key){
    Node* newNode = createNode(key);
    
    if(tree->root == NULL){
        tree->root = newNode;
    }else{
        insertAux(tree->root, newNode);
    }
    
}

///////////////////////////////////////////

int returnBiggestKeyAux(Node *root){
    if(root->right == NULL)
        return root->key;
    else
        returnBiggestKeyAux(root->right);
}


int returnBiggestKey(ABB *tree){
    if(tree->root->right == NULL)
        return tree->root->key;
    else
        returnBiggestKeyAux(tree->root);
}

///////////////////////////////////////////

int returnSmallestKeyAux(Node *root){
    if(root->left == NULL)
        return root->key;
    else
        returnSmallestKeyAux(root->left);
}


int returnSmallestKey(ABB *tree){
    if(tree->root->left == NULL)
        return tree->root->key;
    else
        returnSmallestKeyAux(tree->root);
}

/////////////////////////////////////////////

void inOrderAux(Node *root){
    if(root != NULL){
        inOrderAux(root->left);
        printf("%i ", root->key);
        inOrderAux(root->right);
    }
}


void inOrder(ABB *tree){
    if(tree->root != NULL)
        inOrderAux(tree->root);
    else
        printf("treeore vazia!!!");
}

//////////////////////////////////////////////////////

void preOrderAux(Node* root){
    if(root != NULL){
        printf("%i ", root->key);
        preOrderAux(root->left);
        preOrderAux(root->right);
        
        
    }
}


void preOrder(ABB *tree){
    if(tree->root != NULL){
        preOrderAux(tree->root);
    }else{
        printf("treeore vazia!!!");
    }
}

///////////////////////////////////////////////

void postOrderAux(Node *root){
    if(root != NULL){
        postOrderAux(root->left);
        postOrderAux(root->right);
        printf("%i ", root->key);
    }
}



void psotOrder(ABB *tree){
    if(tree->root != NULL){
        postOrderAux(tree->root);
        
    }else{
        printf("treeore vazia!!!");
    }
}

/////////////////////////////////////////////////////////////////////////

int findKeyAux(Node *root, int key){
    
    if(key != root->key && root->right == NULL && root->left == NULL)
        return 0;
    if(key == root->key)
        return 1;
    else if(key < root->key)
        findKeyAux(root->left, key);
    else if(key > root->key)
        findKeyAux(root->right, key);
    
}


int findKey(ABB *tree, int key){
    if(key == tree->root->key)
        return 1;
    else
        findKeyAux(tree->root, key);
}

/////////////////////////////////////////////////////////////////////////

Node* searchImmediateAncestor(Node* root){
    if(root->right != NULL)
        searchImmediateAncestor(root->right);
    else
        return root;
}


int removeAux(Node *root, int key){
    if(key < root->key){
        removeAux(root->left, key);
        
    }else if(key > root->key){
        removeAux(root->right, key);
        
    }else{
        if(root->left == NULL && root->right == NULL){
            
            if(root->father->left == root)
                root->father->left = NULL;
            else
                root->father->right = NULL;
            
            free(root);
            return 1;
            
        }else if(root->left != NULL && root->right == NULL){
            root->left->father = root->father;
            
             if(root->father->left == root)
                root->father->left = root->left;
            else
                root->father->right = root->left;
                
            free(root);
            return 1;
            
        }else if(root->left == NULL && root->right != NULL){
            root->right->father = root->father;
            
            if(root->father->left == root)
                root->father->left = root->right;
            else
                root->father->right = root->right;
                
            free(root);
            return 1;
            
        }else if(root->left != NULL && root->right != NULL){
            Node* NodeAux = searchImmediateAncestor(root->left);
            if(root->father->left == root){
                root->father->left = NodeAux;
                root->right->father = NodeAux;
                NodeAux->right = root->right;
                NodeAux->father = root->father;
            }else{
                root->father->right = NodeAux;
                root->left->father = NodeAux;
                NodeAux->left = root->right;
                NodeAux->father = root->father;
            } 
            
            free(root);
        }
    }
}


int remove_node(ABB *tree, int key){
    
    if(key != tree->root->key){
        removeAux(tree->root, key);
        
    }else{
        if(tree->root->left == NULL && tree->root->right == NULL){
            free(tree->root);
            return 1;
        }else if(tree->root->left != NULL && tree->root->right == NULL){
            tree->root->left->father = NULL;
            tree->root = tree->root->left;
        }else if(tree->root->left == NULL && tree->root->right != NULL){
            tree->root->right->father = NULL;
            tree->root = tree->root->right;
        }else if(tree->root->left != NULL && tree->root->right != NULL){
            Node* NodeAux = searchImmediateAncestor(tree->root->left);
            Node* NodeAux2 = tree->root;
            
            if(NodeAux->father->left == NodeAux){
                NodeAux->father->left = NULL;
            }else{
                NodeAux->father->right = NULL;
            }
            NodeAux2->right->father = NodeAux;
            NodeAux2->right->father = NodeAux;
            NodeAux->father = NULL;
            NodeAux->left = NodeAux2->left;
            NodeAux->right = NodeAux2->right;
     
            tree->root = NodeAux;
            
        }
    }
}

/////////////////////////////////////////////////////////////////////

int main(){
    
    ABB *tree = createTree();
    
    insert(tree, 15);
    insert(tree, 14);
    insert(tree, 13);
    insert(tree, 16);
    insert(tree, 17);
  
   return 0;
}
