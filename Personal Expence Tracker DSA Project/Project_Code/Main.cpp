/*
 * PENNYSTACK: SMART PERSONAL EXPENSE TRACKER
 * Using Data Structures
 * 
 * Abdul Rafay (243705)
 * Abdullah Rafay (243619)
 * 
 * Mr. Syed Atta Ur Rehman
 * Data Structures - Spring 2025
 * Air University Multan Campus
 */

#include<iostream>
#include<iomanip>
#include "PennyStack.h"
using namespace std;

void displayMenu(){
    cout<<"============================================================"<<endl;
    cout<<"PENNYSTACK - SMART EXPENSE TRACKER\n";
    cout<<"============================================================"<<endl;
}

void line(){
    for(int i=0; i<60; i++) cout<<"=";
    cout<<endl;
}

int main(){
    PennyStack app;
    
    // Login authentication
    if(!app.login()) return 0;
    
    int choice;
    
    while(true){
        system("cls");
        displayMenu();
        cout<<"Balance: PKR "<<fixed<<setprecision(2)<<app.getBalance()<<endl;
        line();
        
        cout<<"\n[1] Add Transaction\n";
        cout<<"[2] Undo Last Action\n";
        cout<<"[3] View Transaction History\n";
        cout<<"[4] Schedule Bill\n";
        cout<<"[5] Pay Pending Bill\n";
        cout<<"[6] View Category Report\n";
        cout<<"[7] Exit\n";
        line();
        cout<<"Choice: ";
        cin>>choice;
        
        if(choice == 1){
            double amount;
            string type, category;
            
            cout<<"\n Amount: ";
            amount = app.getValidAmount();
            cout<<" Type (Income/Expense): ";
            type = app.getValidType();
            cout<<" Category: ";
            cin>>category;
            
            app.addTransaction(amount, type, category);
        }
        else if(choice == 2){
            app.undoLast();
        }
        else if(choice == 3){
            app.viewHistory();
        }
        else if(choice == 4){
            string billName;
            double billAmount;
            
            cout<<"\n Bill Name: ";
            cin>>billName;
            cout<<" Amount: ";
            billAmount = app.getValidAmount();
            
            app.scheduleBill(billName, billAmount);
        }
        else if(choice == 5){
            app.payPendingBill();
        }
        else if(choice == 6){
            app.categoryReport();
        }
        else if(choice == 7){
            app.save();
            cout<<"\n\n Thank You for using PennyStack!\n\n";
            break;
        }
        else{
            cout<<"\n Invalid Choice!\n";
        }
        
        if(choice < 7){
            cout<<"\n";
            system("pause");
        }
    }
    
    return 0;
}