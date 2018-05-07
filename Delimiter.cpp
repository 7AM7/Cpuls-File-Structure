#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class Customer{
private:
    char ID[3];
    char name[20];
    char balance[4];
public:
    int getLastID()
    {
        fstream infile;
        infile.open("test1",ios::in);
        char ch;
        infile.seekg(-1, std::ios::end);
        infile.get(ch);
        if (ch == '\n')
        {
            infile.seekg(-2, std::ios::cur);
            infile.seekg(-1, std::ios::cur);
            infile.get(ch);
            while(ch != '\n')
            {
                infile.seekg(-2, std::ios::cur);
                infile.get(ch);
            }
            infile.getline(ID,3,'|');
        }
        
        if(strlen(ID)==0)
            return 0;
        
        return atoi(ID);
    }
    
    void EnterCustomer()
    {
        cout << "Enter Your ID: ";
        cin >> ID;
        cout << "Enter Your name: ";
        cin >> name;
        cout << "Enter Your balance: ";
        cin >> balance;
        
    }
    
    void PrintCustomer()
    {
        cout << ID << "  ";
        cout << name << "  ";
        cout << balance << endl;
    }
    
    void WriteCustomer(fstream &f)
    {
        f<<ID<<'|'<<name<<'|'<<balance<<'\n';
    }
    
    bool SearchCustomer(fstream &f, int id)
    {
        while(f.getline(ID,3,'|'))
        {
            f.getline(name,20,'|');
            f.getline(balance,4);
            if(atoi(ID) == id)
            {
                PrintCustomer();
                return true;
            }
        }
        return false;
    }
    
    
    void ReadCustomer(fstream &f)
    {
        while(f.getline(ID,3,'|'))
        {
            f.getline(name,20,'|');
            f.getline(balance,4);
            PrintCustomer();
        }
    }
    void Delete(fstream &f, int id)
    {
        fstream f2;
        f2.open("temp.txt",ios::out);
        
        while(f.getline(ID,3,'|'))
        {
            f.getline(name,20,'|');
            f.getline(balance,4);
            if(atoi(ID) != id)
            {
                WriteCustomer(f2);
            }
        }
        f.close();
        f2.close();
        
        remove("test1.txt");
        rename("temp.txt","test1.txt");
    }
    
    void Update(fstream &f, int id)
    {
        fstream f2;
        f2.open("temp.txt",ios::out);
        
        while(f.getline(ID,3,'|'))
        {
            f.getline(name,20,'|');
            f.getline(balance,4);
            if(atoi(ID) == id)
            {
                cout << "Enter New Date Of Record : " << endl;
                EnterCustomer();
                WriteCustomer(f2);
            }
            else{
                 WriteCustomer(f2);
            }
        }
        f.close();
        f2.close();
        
        remove("test1.txt");
        rename("temp.txt","test1.txt");
    }

};
int main()
{
    
    Customer cs;
    cout<<cs.getLastID()<<endl;
    int id;
    fstream f;
    char z;
    int choice;
    do{
        
        
        cout << "Insert: 1 \nSearch : 2 \nUpdate : 3 \nDelete : 4 \nReadDate : 5 " << endl;
        cout<<"Enter Your Choice:";
        cin >> choice;
        switch (choice){
            case 1:
                f.open("test1.txt",  ios::out|ios::app);
                cs.EnterCustomer();
                cs.WriteCustomer(f);
                f.close();
                break;
            case 2:
                f.open("test1.txt",  ios::in);
                cout << "Enter Your Id" << endl;
                cin >> id;
                cs.SearchCustomer(f, id);
                f.close();
                break;
            case 3:
                f.open("test1.txt",  ios::in);
                cout << "Enter Your Id" << endl;
                cin >> id;
                cs.Update(f, id);
                break;
            case 4:
                f.open("test1.txt",  ios::in);
                cout << "Enter Your Id" << endl;
                cin >> id;
                cs.Delete(f, id);
                break;
            case 5:
                f.open("test1.txt",  ios::in);
                cs.ReadCustomer(f);
                f.close();
                break;
            default:
                cout << "choose right number" << endl;
                
        }
        cout << "if you continue to use program press  y " << endl;
        cin >> z;
    }while(z=='y');
    
    return 0;
    
}
