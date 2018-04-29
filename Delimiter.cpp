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
    
    void EnterCustomer(){
        cout << "Enter Your ID: ";
        cin >> ID;
        cout << "Enter Your name: ";
        cin >> name;
        cout << "Enter Your balance: ";
        cin >> balance;
        
    }
    
    void PrintCustomer(){
        cout << ID << endl;
        cout << name << endl;
        cout << balance << endl;
    }
    
    void WriteCustomer(fstream &f)
    {
        f<<ID<<'|'<<name<<'|'<<balance<<'\n';
    }

    bool SearchCustomer(fstream &f, int id)
    {
        while(!f.eof())
        {
            f.getline(ID,3,'|');
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
        while(!f.eof())
        {
            f.getline(ID,3,'|');
            f.getline(name,20,'|');
            f.getline(balance,4);
            PrintCustomer();
        }
    }


    void Update_Recoed()
    {
        fstream f;
        fstream f2;
         int ID_Search;
        f.open("test1",ios::in);
        f2.open("temp.txt",ios::out);
        cout << "Enter Your ID" << endl;
        cin >> ID_Search;
        while(!f.eof())
        {
            f.getline(ID,3,'|');

            if(atoi(ID) == ID_Search)
            {
                cout << "Enter New Date Of Record : " << endl;
                EnterCustomer();
                WriteCustomer(f2);

            }
            else
            {
                f.getline(name,20,'|');
                f.getline(balance,4);
                WriteCustomer(f2);
            }
        }
        
        f2.close();
        f.close();
        
        f.open("test1",ios::out);
        f2.open("temp.txt",ios::in);
        while(!f2.eof())
        {
            f2.getline(ID,3,'|');
            f2.getline(name,20,'|');
            f.getline(balance,4);
            WriteCustomer(f);
        }
        f2.close();
        f.close();
        remove("temp.txt");
    }
    void Delete_Record()
    {
        int ID_Search;
        short nSize;
        fstream f1;
        fstream f2;
        f1.open("test1", ios::in);
        f2.open("temp.txt", ios::out);
        cout << "Enter Your ID" << endl;
        cin >> ID_Search;
        while (f1.read((char*)&nSize, sizeof(short)))
        {
            f1.getline(ID,3,'|');
            
            if(atoi(ID) == ID_Search)
            {
                continue;
            }
            else
            {
                f1.getline(name,20,'|');
                f1.getline(balance,4);
                WriteCustomer(f2);
            }
        }
        f1.close();
        f2.close();
        
        
        f1.open("test1", ios::out);
        f2.open("temp.txt", ios::in);
        while (f2.read((char*)&nSize, sizeof(short)))
        {
            f2.getline(ID,3,'|');
            f2.getline(name,20,'|');
            f2.getline(balance,4);
            WriteCustomer(f1);
            
        }
        f1.close();
        f2.close();
        remove("temp.txt");
    }
};
int main()
{
    
    Customer cs;
    cout<<cs.getLastID()<<endl;
    int id;
    fstream f("test1",  ios::in|ios::out|ios::binary);
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
