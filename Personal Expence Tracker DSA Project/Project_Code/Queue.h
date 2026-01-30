#ifndef QUEUE_H
#define QUEUE_H

#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

// Bill Node Structure
struct BillNode{
    string billName;
    double billAmount;
    BillNode* next;
};

// Queue Class for Bill Scheduling
class Queue{
private:
    BillNode* front;
    BillNode* rear;
    
public:
    Queue(){
        front = NULL;
        rear = NULL;
    }
    
    // Enqueue - Add bill to queue
    void enqueue(string name, double amount){
        BillNode* newBill = new BillNode;
        newBill->billName = name;
        newBill->billAmount = amount;
        newBill->next = NULL;
        
        if(rear == NULL){
            front = rear = newBill;
        }
        else{
            rear->next = newBill;
            rear = newBill;
        }
    }
    
    // Dequeue - Remove bill from queue
    void dequeue(){
        if(isEmpty()){
            return;
        }
        
        BillNode* temp = front;
        front = front->next;
        
        if(front == NULL){
            rear = NULL;
        }
        
        delete temp;
    }
    
    // Get front bill
    BillNode* getFront(){
        return front;
    }
    
    // Check if queue is empty
    bool isEmpty(){
        return front == NULL;
    }
    
    // Display pending bills
    void display(){
        if(isEmpty()){
            cout<<"\n No pending bills.\n";
            return;
        }
        
        cout<<"\n Pending Bills:\n";
        cout<<" ----------------------------------------\n";
        
        BillNode* temp = front;
        int count = 1;
        
        while(temp != NULL){
            cout<<" "<<count<<". "<<temp->billName
                <<" - PKR "<<fixed<<setprecision(2)<<temp->billAmount<<endl;
            temp = temp->next;
            count++;
        }
        cout<<" ----------------------------------------\n";
    }
    
    // Clear all bills
    void clear(){
        while(!isEmpty()){
            dequeue();
        }
    }
    
    ~Queue(){
        clear();
    }
};

#endif