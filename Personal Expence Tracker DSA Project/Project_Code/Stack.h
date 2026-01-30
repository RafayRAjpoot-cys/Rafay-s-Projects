#ifndef STACK_H
#define STACK_H

#include "DoublyLinkedList.h"

// Stack Node Structure
struct StackNode{
    Transaction* trans;
    StackNode* next;
};

// Stack Class for Undo Functionality
class Stack{
private:
    StackNode* top;
    
public:
    Stack(){
        top = NULL;
    }
    
    // Push transaction onto stack
    void push(Transaction* trans){
        StackNode* newNode = new StackNode;
        newNode->trans = trans;
        newNode->next = top;
        top = newNode;
    }
    
    // Pop transaction from stack
    Transaction* pop(){
        if(isEmpty()){
            return NULL;
        }
        
        StackNode* temp = top;
        Transaction* trans = top->trans;
        top = top->next;
        delete temp;
        
        return trans;
    }
    
    // Peek at top transaction
    Transaction* peek(){
        if(isEmpty()){
            return NULL;
        }
        return top->trans;
    }
    
    // Check if stack is empty
    bool isEmpty(){
        return top == NULL;
    }
    
    // Clear entire stack
    void clear(){
        while(!isEmpty()){
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    ~Stack(){
        clear();
    }
};

#endif