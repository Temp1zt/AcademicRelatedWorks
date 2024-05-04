// Bank Management System
// Shoutout sa Indian kong pinanood para sa guide kung paano to gawin

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cctype>

using namespace std;

class Bank_Account{
    int account_number;
    char name[50];
    char type;
    int Money_Despoit;

public:
    void modify();
    void report() const;
    int retacno() const{
        return account_number;
    }
    void dep(int x){
        Money_Despoit+=x;
    }
    void draw(int x){
        Money_Despoit-=x;
    }
    int retdeposit() const{
        return Money_Despoit;
    }
    void create_account();
    void Display_Account();

};
void Bank_Account::report() const{
    cout<<account_number<<setw(10)<<" "<< name<<setw(6)<<type<<setw(7)<<Money_Despoit<<endl;
}

void Bank_Account::modify(){
        cout<<"\t Account Number: "<<account_number<<endl;
        cout<<"\t Modify Account Holder Name: ";
        cin.ignore();
        cin.getline(name,50);
        cout<<"\t Modify Type of Account: ";
        cin>>type;
        type=toupper(type);  //convert to upper case
        cout<<"\t Modify Balance amount: ";
        cin>>Money_Despoit;
}



void write_account(); //function to write record in binary file
void display_details(int); //function to display account details given by user
void delete_account(int); //function to delete record of files
void display_all(); //function to display all account details
void Money_deposit_withdraw(int, int); //function to deposit/withdraw amount for given account
void Updation_bank_account(int); //function to update account details

void Bank_Account::create_account(){
    system("cls");
    cout<<"\t Enter account number: ";
    cin>>account_number;
    cout<<"\t Enter the name of the card holder: ";
    cin.ignore();
    cin.getline(name,50);
    cout<<"\t Enter the type of account (C/S): ";
    cin>>type;
    type=toupper(type);
    cout<<"\t Enter the initial amount (>=500 for Saving and >=1000 for current): ";
    cin>>Money_Despoit;
    cout<<endl;
    cout<<"\t Account Created.... Sheesh";
    cout<<endl;

}

void Bank_Account::Display_Account(){

    cout<<"\t Account Number: "<<account_number<<endl;
    cout<<"\t Account Holder Number: "<<name<<endl;
    cout<<"\t Type of Account : "<<type<<endl;
    cout<<"\t Balance amount : "<<Money_Despoit<<endl;
}

int main(){
    char ch;
    int num;
    do{

    cout<<"\t\t ------------------------------------------------------------"<<endl;
    cout<<"\t\t | Welcome to the Not Real Bank Management System of Gensokyo|"<<endl;
    cout<<"\t\t ------------------------------------------------------------"<<endl;

    cout<<endl;
    cout<<"\t --- Main Menu ---"<<endl;
    cout<<"\t 1. Create Account"<<endl; //created
    cout<<"\t 2. Deposit Money"<<endl;  //created
    cout<<"\t 3. Withdraw Money"<<endl; //created
    cout<<"\t 4. Balance Enquiry"<<endl; //created
    cout<<"\t 5. All Account Holder List"<<endl; //created
    cout<<"\t 6. Close an Account"<<endl; //created
    cout<<"\t 7. Modify an Account"<<endl; //created
    cout<<"\t 8. Exit"<<endl; //created
    cout<<endl;

    cout<<"\t Enter your choice (1-8): ";
    cin>>ch;

    switch(ch){
        case '1':
            write_account();
            break;
        case '2':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            Money_deposit_withdraw(num, 1);            //deposit function
            break;
        case '3':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            Money_deposit_withdraw(num, 2);            //withdraw function
            break;
        case '4':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            display_details(num);                      //balance enquiry function
            break;
        case '5':
            display_all();                             //display all function
            break;

        case '6':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            delete_account(num);                       //close account function
            break;
        case '7':
            system("cls");
            cout<<"\t Enter the account number: ";
            cin>>num;
            Updation_bank_account(num);                //modify account function
            break;
        case '8':
            cout<<"\t Thanks for using the Not Real Bank Management System of Gensokyo. We Hope you have a pleasant day!"<<endl;
            break;
    }
    cin.ignore();
    cin.get();
    }while(ch!='8');
    return 0;

    Bank_Account B;
    cout<<endl;
    B.create_account();
    B.Display_Account();
    return 0;
}

void write_account() //function to write record in binary file
{
    Bank_Account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
    outFile.close();
}

void delete_account(int account_number) {
    Bank_Account account;
    ifstream inFile("account.dat", ios::binary);
    ofstream outFile1("temp1.dat", ios::binary);
    ofstream outFile2("temp2.dat", ios::binary);

    if (!inFile) {
        // Handle file opening error
        cout << "Error opening account file!" << endl;
        return;
    }

    bool found = false;
    while (inFile.read(reinterpret_cast<char *>(&account), sizeof(Bank_Account))) {
        if (account.retacno() == account_number) {
            found = true;
            cout << "\nAccount found. Are you sure you want to delete it? (y/n): ";
            char choice;
            cin >> choice;
            if (tolower(choice) == 'y') {
                // Delete associated data if needed (replace with your specific functions)
                // ...
                cout << "Account deleted successfully." << endl;
            } else {
                cout << "Account deletion canceled." << endl;
                outFile1.write(reinterpret_cast<char *>(&account), sizeof(Bank_Account));  // Write the account back to temp1
            }
        } else {
            outFile1.write(reinterpret_cast<char *>(&account), sizeof(Bank_Account));
        }
    }

    inFile.close();
    outFile1.close();
    outFile2.close();

    remove("account.dat");
    rename("temp1.dat", "account.dat");

    if (!found) {
        cout << "\nAccount number not found." << endl;
    }
}




void display_details(int n){
    Bank_Account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout<<"File could not be open !! Press any key...";
        return;
    }
    cout<<"\t Bank Account Details"<<endl;
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account))){
        if(ac.retacno()==n){
            ac.Display_Account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false){
        cout<<"\t Account number does not exist"<<endl;
    }
}

void display_all() //function to display all account details
{
    system("cls");
    Bank_Account ac;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not be open !! Press any key...";
        return;
    }
    cout<<"\t Bank Account Holder List"<<endl;
    cout<<"===================================================="<<endl;
    cout<<"A/c no.         NAME         TYPE         BALANCE"<<endl;
    cout<<"===================================================="<<endl;
    while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)))
    {
        ac.report();
    }
    inFile.close();
}

void Money_deposit_withdraw(int n, int option){
    int amt;
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
    if(!File){
        cout<<"File could not be open !! Press any key...";
        return;
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account));
        if(ac.retacno()==n){
            ac.Display_Account();
            if(option==1){
                cout<<"Enter the amount to be deposited: ";
                cin>>amt;
                ac.dep(amt);
            }
            if(option == 2){
                cout<<"\t Enter the amount to be withdraw: ";
                cin>>amt;
                int balance = ac.retdeposit() - amt;
                if(balance < 0){
                    cout<<"\t Insufficient balance"<<endl;
                }
                else{
                    ac.draw(amt);
                }
            }
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account));
            File.seekp(pos,ios::cur); //move the pointer to the position of the file
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)); //write the record in the file
            cout<<"\t Record Updated"<<endl;
            found = true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\t Record Not Found"<<endl;
    }
}

void Updation_bank_account(int n){
    bool found = false;
    Bank_Account ac;
    fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out); //open file in binary mode
    if(!File){
        cout<<"File could not be open !! Press any key...";
        return;
    }
    while(!File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)); //read the record from the file
        if(ac.retacno()==n){
            ac.Display_Account();
            cout<<endl;
            cout<<"\t Enter the new details of the account"<<endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(Bank_Account));  //move the pointer to the position of the file
            File.seekp(pos,ios::cur);  //move the pointer to the position of the file
            File.write(reinterpret_cast<char *> (&ac), sizeof(Bank_Account)); //write the record in the file
            cout<<"\t Record Updated"<<endl;
            found = true;
        }
    }
    File.close();
    if(found == false){
        cout<<"\t Record Not Found"<<endl;
    }
}


