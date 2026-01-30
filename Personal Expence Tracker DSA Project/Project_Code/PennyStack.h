#ifndef PENNYSTACK_H
#define PENNYSTACK_H

#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "BST.h"
#include<fstream>

class PennyStack{
private:
    DoublyLinkedList transactionList;  // Transaction history
    Stack undoStack;                    // Undo functionality
    Queue billQueue;                    // Bill scheduling
    BST categoryTree;                   // Category tracking
    
    int transactionID;
    double balance;
    int storedHash;
    
    // PIN hashing
    int hashPIN(int pin){
        return (pin % 1000) * 5 + 7;
    }
    
    // Load data from file
    void load(){
        ifstream file("data.txt");
        if(!file) return;
        
        file>>balance;
        if(file.fail()){
            balance = 0;
            file.close();
            return;
        }
        
        int id; 
        double amount; 
        string type, category;
        
        while(file>>id>>amount>>type>>category){
            if(file.fail()) break;
            
            Transaction* newTrans = new Transaction;
            newTrans->id = id;
            newTrans->amount = amount;
            newTrans->type = type;
            newTrans->category = category;
            
            transactionList.insertAtTail(newTrans);
            transactionID = id + 1;
            
            if(type == "Expense"){
                categoryTree.insert(category, amount);
            }
        }
        file.close();
    }
    
public:
    PennyStack(){
        transactionID = 1;
        balance = 0;
        storedHash = hashPIN(2471);  // Default PIN: 2471
        load();
    }
    
    // Login system
    bool login(){
        system("cls");
        cout<<"============================================================"<<endl;
        cout<<"PENNYSTACK LOGIN\n";
        cout<<"============================================================"<<endl;
        
        int pin;
        cout<<"\nEnter PIN: ";
        cin>>pin;
        
        int inputHash = hashPIN(pin);
        
        if(inputHash == storedHash){
            cout<<"\nAccess Granted!\n\n";
            system("pause");
            return true;
        }
        
        cout<<"\nAccess Denied!\n\n";
        system("pause");
        return false;
    }
    
    // Save data to file
    void save(){
        ofstream file("data.txt");
        if(!file) return;
        
        file<<balance<<endl;
        
        Transaction* trans = transactionList.getHead();
        while(trans){
            file<<trans->id<<" "<<trans->amount<<" "
                <<trans->type<<" "<<trans->category<<endl;
            trans = trans->next;
        }
        file.close();
        cout<<"\n Data Saved!\n";
    }
    
    // Input validation
    double getValidAmount(){
        double amount;
        while(true){
            cin>>amount;
            if(cin.fail() || amount <= 0){
                cin.clear();
                cin.ignore(10000, '\n');
                cout<<"Invalid! Enter positive amount: ";
            }
            else{
                return amount;
            }
        }
    }
    
    string getValidType(){
        string type;
        while(true){
            cin>>type;
            if(type == "Income" || type == "Expense"){
                return type;
            }
            cout<<"Invalid! Enter 'Income' or 'Expense': ";
        }
    }
    
    // Add transaction
    void addTransaction(double amount, string type, string category){
        Transaction* newTrans = new Transaction;
        newTrans->id = transactionID++;
        newTrans->amount = amount;
        newTrans->type = type;
        newTrans->category = category;
        
        transactionList.insertAtHead(newTrans);
        undoStack.push(newTrans);
        
        if(type == "Income"){
            balance += amount;
        }
        else{
            balance -= amount;
            categoryTree.insert(category, amount);
        }
        
        cout<<"\n Transaction Added!\n";
        save();
    }
    
    // Undo last transaction
    void undoLast(){
        if(undoStack.isEmpty()){
            cout<<"\n Nothing to undo!\n";
            return;
        }
        
        Transaction* trans = undoStack.pop();
        
        if(trans->type == "Income"){
            balance -= trans->amount;
        }
        else{
            balance += trans->amount;
            categoryTree.update(trans->category, trans->amount);
        }
        
        transactionList.removeTransaction(trans);
        delete trans;
        
        cout<<"\n Last Action Undone!\n";
        save();
    }
    
    // View transaction history
    void viewHistory(){
        system("cls");
        cout<<"============================================================"<<endl;
        cout<<"TRANSACTION HISTORY\n";
        cout<<"============================================================"<<endl;
        
        transactionList.display();
        
        cout<<"============================================================"<<endl;
        cout<<"Total Transactions: "<<transactionList.count()<<endl;
        cout<<"\n";
        system("pause");
    }
    
    // Schedule bill
    void scheduleBill(string name, double amount){
        billQueue.enqueue(name, amount);
        cout<<"\n Bill Scheduled!\n";
    }
    
    // Pay pending bill
    void payPendingBill(){
        if(billQueue.isEmpty()){
            cout<<"\n No Bills to Pay.\n";
            return;
        }
        
        BillNode* bill = billQueue.getFront();
        
        cout<<"\n Next Bill: "<<bill->billName
            <<" - PKR "<<fixed<<setprecision(2)<<bill->billAmount<<endl;
        
        if(balance < bill->billAmount){
            cout<<"\n Insufficient Balance!\n";
            cout<<" Current Balance: PKR "<<balance<<endl;
            cout<<" Required: PKR "<<bill->billAmount<<endl;
            return;
        }
        
        string billName = bill->billName;
        double billAmount = bill->billAmount;
        
        billQueue.dequeue();
        addTransaction(billAmount, "Expense", "Bill_"+billName);
        
        cout<<"\n Bill Paid Successfully!\n";
    }
    
    // Category report
    void categoryReport(){
        system("cls");
        cout<<"============================================================"<<endl;
        cout<<"  CATEGORY REPORT (BST)\n";
        cout<<"============================================================"<<endl;
        
        if(categoryTree.isEmpty()){
            cout<<"\n No expense data available.\n";
        }
        else{
            string category;
            cout<<"\n Enter Category to Search: ";
            cin>>category;
            
            double total = categoryTree.search(category);
            
            if(total == 0){
                cout<<"\n Category '"<<category<<"' not found.\n";
            }
            else{
                cout<<"\n Category: "<<category<<"\n";
                cout<<" Total Spent: PKR "<<fixed<<setprecision(2)<<total<<"\n";
            }
        }
        cout<<"\n";
        system("pause");
    }
    
    // Get balance
    double getBalance(){
        return balance;
    }
};

#endif