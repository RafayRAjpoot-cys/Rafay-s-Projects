#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

// Transaction Node Structure
struct Transaction{
    int id;
    double amount;
    string type;
    string category;
    Transaction* next;
    Transaction* prev;
};

// Doubly Linked List Class for Transaction History
class DoublyLinkedList{
private:
    Transaction* head;
    Transaction* tail;
    
public:
    DoublyLinkedList(){
        head = NULL;
        tail = NULL;
    }
    
    // Insert at beginning (most recent first)
    void insertAtHead(Transaction* newTrans){
        newTrans->next = NULL;
        newTrans->prev = NULL;
        
        if(head == NULL){
            head = tail = newTrans;
        }
        else{
            newTrans->next = head;
            head->prev = newTrans;
            head = newTrans;
        }
    }
    
    // Insert at end (for loading from file)
    void insertAtTail(Transaction* newTrans){
        newTrans->next = NULL;
        
        if(head == NULL){
            head = tail = newTrans;
            newTrans->prev = NULL;
        }
        else{
            tail->next = newTrans;
            newTrans->prev = tail;
            tail = newTrans;
        }
    }
    
    // Remove specific transaction
    void removeTransaction(Transaction* trans){
        if(trans->next) trans->next->prev = trans->prev;
        if(trans->prev) trans->prev->next = trans->next;
        if(trans == tail) tail = trans->prev;
        if(trans == head) head = trans->next;
    }
    
    // Display all transactions
    void display(){
        if(head == NULL){
            cout<<"\n No transactions yet.\n";
            return;
        }
        
        cout<<"\n"<<left<<setw(6)<<"ID"<<setw(12)<<"Type"
            <<setw(15)<<"Category"<<right<<setw(12)<<"Amount"<<endl;
        cout<<"============================================================"<<endl;
        
        Transaction* trans = head;
        while(trans != NULL){
            cout<<left<<setw(6)<<trans->id
                <<setw(12)<<trans->type
                <<setw(15)<<trans->category
                <<right<<setw(12)<<fixed<<setprecision(2)<<trans->amount<<endl;
            trans = trans->next;
        }
    }
    
    // Count transactions
    int count(){
        int cnt = 0;
        Transaction* trans = head;
        while(trans != NULL){
            cnt++;
            trans = trans->next;
        }
        return cnt;
    }
    
    // Get head pointer
    Transaction* getHead(){
        return head;
    }
    
    // Clear all transactions
    void clear(){
        Transaction* current = head;
        while(current != NULL){
            Transaction* temp = current;
            current = current->next;
            delete temp;
        }
        head = tail = NULL;
    }
    
    ~DoublyLinkedList(){
        clear();
    }
};

#endif