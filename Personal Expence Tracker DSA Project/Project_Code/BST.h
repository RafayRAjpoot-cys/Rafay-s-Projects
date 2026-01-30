#ifndef BST_H
#define BST_H

#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

// Category Node Structure
struct CategoryNode{
    string categoryName;
    double totalSpent;
    CategoryNode* left;
    CategoryNode* right;
};

// Binary Search Tree for Category Management
class BST{
private:
    CategoryNode* root;
    
    // Insert helper
    CategoryNode* insertHelper(CategoryNode* node, string cat, double amt){
        if(node == NULL){
            CategoryNode* newNode = new CategoryNode;
            newNode->categoryName = cat;
            newNode->totalSpent = amt;
            newNode->left = NULL;
            newNode->right = NULL;
            return newNode;
        }
        
        if(cat == node->categoryName){
            node->totalSpent += amt;
        }
        else if(cat < node->categoryName){
            node->left = insertHelper(node->left, cat, amt);
        }
        else{
            node->right = insertHelper(node->right, cat, amt);
        }
        return node;
    }
    
    // Search helper
    double searchHelper(CategoryNode* node, string cat){
        if(node == NULL) return 0;
        if(cat == node->categoryName) return node->totalSpent;
        else if(cat < node->categoryName) return searchHelper(node->left, cat);
        else return searchHelper(node->right, cat);
    }
    
    // Find minimum node
    CategoryNode* findMin(CategoryNode* node){
        CategoryNode* current = node;
        while(current->left != NULL){
            current = current->left;
        }
        return current;
    }
    
    // Delete node helper
    CategoryNode* deleteHelper(CategoryNode* node, string cat){
        if(node == NULL) return NULL;
        
        if(cat < node->categoryName){
            node->left = deleteHelper(node->left, cat);
        }
        else if(cat > node->categoryName){
            node->right = deleteHelper(node->right, cat);
        }
        else{
            // Node with no child or one child
            if(node->left == NULL && node->right == NULL){
                delete node;
                return NULL;
            }
            else if(node->left == NULL){
                CategoryNode* temp = node->right;
                delete node;
                return temp;
            }
            else if(node->right == NULL){
                CategoryNode* temp = node->left;
                delete node;
                return temp;
            }
            else{
                // Node with two children
                CategoryNode* temp = findMin(node->right);
                node->categoryName = temp->categoryName;
                node->totalSpent = temp->totalSpent;
                node->right = deleteHelper(node->right, temp->categoryName);
            }
        }
        return node;
    }
    
    // Update helper (for undo)
    CategoryNode* updateHelper(CategoryNode* node, string cat, double amt){
        if(node == NULL) return NULL;
        
        if(cat == node->categoryName){
            node->totalSpent -= amt;
            if(node->totalSpent <= 0.01){
                return deleteHelper(node, cat);
            }
            return node;
        }
        else if(cat < node->categoryName){
            node->left = updateHelper(node->left, cat, amt);
        }
        else{
            node->right = updateHelper(node->right, cat, amt);
        }
        return node;
    }
    
    // Display chart
    void showChart(double amount){
        int bars = (int)(amount/100);
        if(bars > 30) bars = 30;
        for(int i=0; i<bars; i++) cout<<"|";
        cout<<" PKR "<<fixed<<setprecision(2)<<amount;
    }
    
    // Inorder traversal helper
    void inorderHelper(CategoryNode* node){
        if(node == NULL) return;
        inorderHelper(node->left);
        cout<<"\n "<<left<<setw(15)<<node->categoryName<<" : ";
        showChart(node->totalSpent);
        inorderHelper(node->right);
    }
    
    // Clear tree helper
    void clearHelper(CategoryNode* node){
        if(node == NULL) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }
    
public:
    BST(){
        root = NULL;
    }
    
    // Insert category
    void insert(string cat, double amt){
        root = insertHelper(root, cat, amt);
    }
    
    // Search category
    double search(string cat){
        return searchHelper(root, cat);
    }
    
    // Update category (subtract amount)
    void update(string cat, double amt){
        root = updateHelper(root, cat, amt);
    }
    
    // Display all categories (inorder)
    void display(){
        if(root == NULL){
            cout<<"\n No expense data available.\n";
            return;
        }
        inorderHelper(root);
    }
    
    // Check if tree is empty
    bool isEmpty(){
        return root == NULL;
    }
    
    // Clear entire tree
    void clear(){
        clearHelper(root);
        root = NULL;
    }
    
    ~BST(){
        clear();
    }
};

#endif