#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<vector>
using namespace std;


class Customer{
private:
    char ID[3];
    char name[20];
    double balance;
public:
    Customer(char ID1[3], char name1[20], double balance1)
    {
        strcpy(ID, ID1);
        strcpy(name, name1);
        balance = balance1;
    }
    Customer(){
        
    }
    void EnterCustomer(){
        cout << "Enter Your ID: ";
        cin >> ID;
        cout << "Enter Your name: ";
        cin >> name;
        cout << "Enter Your balance: ";
        cin >> balance;
        
    }
    void WriteCustomer(fstream &f)
    {
        short nSize = strlen(ID);
        f.write((char*)&nSize, sizeof(short));
        f.write(ID, nSize);
        
        nSize = strlen(name);
        f.write((char*)&nSize, sizeof(short));
        f.write(name, nSize);
        
        nSize = strlen((char*)&balance);
        f.write((char*)&nSize, sizeof(short));
        f.write((char*)&balance, nSize);
    }
    void  ReadCustomer(fstream &f)
    {
        short nSize;
        while (f.read((char*)&nSize, sizeof(short)))
        {
            f.read(ID, nSize);
            
            f.read((char*)&nSize, sizeof(short));
            f.read(name, nSize);
            
            f.read((char*)&nSize, sizeof(short));
            f.read((char*)&balance, nSize);
            
            cout<<ID<<endl;
            cout<<name<<endl;
            cout<<balance<<endl;
        }
        
    }
    bool SearchCustomer(fstream &f, int id)
    {
        short nSize;
        while (f.read((char*)&nSize, sizeof(short)))
        {
            f.read(ID, nSize);
            if (id == atoi(ID))
            {
                f.read((char*)&nSize, sizeof(short));
                f.read(name, nSize);
                f.read((char*)&nSize, sizeof(short));
                f.read((char*)&balance, nSize);
                
                cout << ID << endl;
                cout << name << endl;
                cout << balance << endl;
                
                return true;
            }
        }
        return false;
    }
    void PrintCustomer(){
        cout << ID << endl;
        cout << name << endl;
        cout << balance << endl;
    }
    
    void Update_Recoed()
    {
        int ID_Search;
        short nSize;
        fstream f1;
        fstream f2;
        f1.open("test1", ios::in);
        f2.open("test2", ios::out);
        cout << "Enter Your ID" << endl;
        cin >> ID_Search;
        while (f1.read((char*)&nSize, sizeof(short)))
        {
            f1.read(ID, nSize);
            if (ID_Search ==atoi(ID))
            {
                cout << "Enter New Date Of Record : " << endl;
                EnterCustomer();
                WriteCustomer(f2);
                
            }
            else
            {
                f1.read((char*)&nSize, sizeof(short));
                f1.read(name, nSize);
                
                f1.read((char*)&nSize, sizeof(short));
                f1.read((char*)&balance, nSize);
                WriteCustomer(f2);
            }
        }
        f1.close();
        f2.close();
        f1.open("test1", ios::out);
        f2.open("test2", ios::in);
        while (f2.read((char*)&nSize, sizeof(short)))
        {
            f2.read(ID, nSize);
            f2.read((char*)&nSize, sizeof(short));
            f2.read(name, nSize);
            
            f2.read((char*)&nSize, sizeof(short));
            f2.read((char*)&balance, nSize);
            WriteCustomer(f1);
            
        }
        f1.close();
        f2.close();
    }
    
    void Delete_Record()
    {
        int ID_Search;
        short nSize;
        fstream f1;
        fstream f2;
        f1.open("test1", ios::in);
        f2.open("test2", ios::out);
        cout << "Enter Your ID" << endl;
        cin >> ID_Search;
        while (f1.read((char*)&nSize, sizeof(short)))
        {
            f1.read(ID, nSize);
            if (ID_Search == atoi(ID))
            {
                continue;
            }
            else
            {
                f1.read((char*)&nSize, sizeof(short));
                f1.read(name, nSize);
                
                f1.read((char*)&nSize, sizeof(short));
                f1.read((char*)&balance, nSize);
                WriteCustomer(f2);
            }
        }
        f1.close();
        f2.close();
        f1.open("test1", ios::out);
        f2.open("test2", ios::in);
        while (f2.read((char*)&nSize, sizeof(short)))
        {
            f2.read(ID, nSize);
            f2.read((char*)&nSize, sizeof(short));
            f2.read(name, nSize);
            
            f2.read((char*)&nSize, sizeof(short));
            f2.read((char*)&balance, nSize);
            WriteCustomer(f1);
            
        }
        f1.close();
        f2.close();
        
    }
};



int main(){
    Customer cs;
    int id;
    fstream f("test1", ios::in | ios::out|ios::binary);
    char z;
    int choice;
    do{
        
        
        cout << "Insert: 1 \nSearch : 2 \nUpdate : 3 \nDelete : 4 \nReadDate : 5 " << endl;
        cout<<"Enter Your Choice:";
        cin >> choice;
        switch (choice){
            case 1:
                cs.EnterCustomer();
                cs.WriteCustomer(f);
                break;
            case 2:
                cout << "Enter Your Id" << endl;
                cin >> id;
                cs.SearchCustomer(f, id);
                
                break;
            case 3:
                cs.Update_Recoed();
                break;
            case 4:
                cs.Delete_Record();
                break;
            case 5:
                cs.ReadCustomer(f);
                break;
            default:
                cout << "choose right number" << endl;
                
        }
        cout << "if you continue to use program press  y " << endl;
        cin >> z;
    }while(z=='y');

    return 0;
    
}
