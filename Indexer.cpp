#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<vector>
using namespace std;


struct Employee{
    char name[20]; int emp_id; double salary;
};

struct Index{
    int emp_id; int pos;
};

class Company{
    Employee emp; Index indx;
    
    public :
    
    //not better way with big data in file
    int getLastIndex()
    {
        int lastIndex = 0;
        fstream f2;
        f2.open("indexer.txt",ios::in);
        while(f2.read((char*)&indx,sizeof(Index)))
        {
            lastIndex = indx.pos;
        }
        f2.close();
        return lastIndex;
    }
    void EnterData(){
        cout <<"Enter First id:";
        cin>>emp.emp_id;
        cout <<"Enter First name:";
        cin>>emp.name;
        cout <<"Enter First salary:";
        cin>>emp.salary;
    }
    void Create()
    {
        fstream f1,f2;
        char y='n';
        if(getLastIndex()!= 0)indx.pos = getLastIndex()+1;
        else indx.pos = 0;
        
        
        f2.open("indexer.txt",ios::out|ios::app|ios::binary);
        f1.open("test.txt",ios::out|ios::app|ios::binary);
        do
        {
 
            EnterData();
            indx.emp_id = emp.emp_id;
            f2.write((char*)&indx,sizeof(Index));
            indx.pos++;
            
            f1.write((char*)&emp,sizeof(Employee));
            cout<<"Enter (y) to contuines: ";
            cin>>y;
        }while(y=='y');
        f2.close();
        f1.close();
    }
    
    void PrintData()
    {
        cout<<emp.emp_id<<" ";
        cout<<emp.name<<" ";
        cout<<emp.salary<<endl;
    }
    
    void Display()
    {
        fstream f1,f2;
        f2.open("indexer.txt",ios::in);
        f1.open("test.txt",ios::in);
        while(f2.read((char*)&indx,sizeof(Index)))
        {
            int value = indx.pos*sizeof(Employee);
            f1.seekg(value);
            f1.read((char*)&emp,sizeof(Employee));
            if(emp.emp_id!=-1)
            {
                PrintData();
            }
        }
        f2.close();
        f1.close();
    }

    bool Search(int id)
    {
        fstream f1,f2;
        f2.open("indexer.txt",ios::in);
        f1.open("test.txt",ios::in);
        bool check=false;
        while(f2.read((char*)&indx,sizeof(Index)))
        {
            if(indx.emp_id == id)
            {
                int value = indx.pos*sizeof(Employee);
                
                f1.seekg(value);
                f1.read((char*)&emp,sizeof(Employee));
                if(emp.emp_id!=-1)
                {
                    PrintData();
                    check=true;
                    break;
                }
            }
        }
        f2.close();
        f1.close();
        return check;
    }
    bool Delete(int id)
    {
        fstream f1,f2;
        f2.open("indexer.txt",ios::in|ios::out);
        f1.open("test.txt",ios::in|ios::out);
        bool check=false;
        Index tmpIndex;
        while(f2.read((char*)&tmpIndex,sizeof(Index)))
        {
            long pos = f2.tellg();
            if(tmpIndex.emp_id == id)
            {
                f2.seekg(pos-sizeof(tmpIndex));
                indx.emp_id = -1;
                indx.pos = tmpIndex.pos;
                f2.write((char*)&indx,sizeof(Index));
                
                int value = indx.pos*sizeof(Employee);
                f1.seekg(value);
                f1.read((char*)&emp,sizeof(Employee));
                long pos1 = f1.tellg();
                
                if(emp.emp_id!=-1)
                {
                    f1.seekg(pos1-sizeof(emp));
                    emp.emp_id = -1;
                    strcpy(emp.name, "");
                    emp.salary = 0.0;
                    f1.write((char*)&emp,sizeof(Employee));
                    check=true;
                    break;
                }
            }
        }
        f2.close();
        f1.close();
        return check;
    }
    
    bool Update(int id)
    {
        fstream f1,f2;
        f2.open("indexer.txt",ios::in|ios::out);
        f1.open("test.txt",ios::in|ios::out);
        bool check=false;
        Index tmpIndex;
        while(f2.read((char*)&tmpIndex,sizeof(Index)))
        {
            long pos = f2.tellg();
            if(tmpIndex.emp_id == id)
            {

                int value = tmpIndex.pos*sizeof(Employee);
                f1.seekg(value);
                f1.read((char*)&emp,sizeof(Employee));
                long pos1 = f1.tellg();
                if(emp.emp_id!=-1)
                {
                    f1.seekg(pos1-sizeof(emp));
                    EnterData();
                    f1.write((char*)&emp,sizeof(Employee));
                    
                    f2.seekg(pos-sizeof(tmpIndex));
                    indx.emp_id = emp.emp_id;
                    indx.pos = tmpIndex.pos;
                    f2.write((char*)&indx,sizeof(Index));
                    check=true;
                    break;
                }
            }
        }
        f2.close();
        f1.close();
        return check;
    }
    void DisplayIndexer()
    {
        fstream f2;
        f2.open("indexer.txt",ios::in);
        while(f2.read((char*)&indx,sizeof(Index)))
        {
            cout<<indx.emp_id<<" " <<indx.pos<<endl;
        }
        f2.close();
        
    }
    void DisplayMain()
    {
        fstream f1;
        f1.open("test.txt",ios::in);
        while(f1.read((char*)&emp,sizeof(Employee)))
        {
            PrintData();
        }
        f1.close();
        
    }
    
};

int main(){
    Company comp;
    int id;
    int choice;
    char z;
    do{
        
        cout << "Insert: 1 \nSearch : 2 \nUpdate : 3 \nDelete : 4 \nDisplay : 5 " << endl;
        cout<<"Enter Your Choice:";
        cin >> choice;
        switch (choice){
            case 1:
                comp.Create();
                break;
            case 2:
                cout<<"Enter Id for Searching...: ";
                cin>>id;
                if(comp.Search(id))cout<<"Founded.."<<endl;
                else cout<<"Not Founded.."<<endl;
                break;
            case 3:
                cout<<"Enter Id for Updating...: ";
                cin>>id;
                if(comp.Update(id))cout<<"Updated.."<<endl;
                else cout<<"Not Founded.."<<endl;
                break;
            case 4:
                cout<<"Enter Id for Deleting...: ";
                cin>>id;
                if(comp.Delete(id))cout<<"Deleted.."<<endl;
                else cout<<"Not Founded.."<<endl;
                break;
            case 5:
                comp.Display();
                break;
            default:
            cout << "choose right number" << endl;
                
        }
        cout << "if you continue to use program press  y " << endl;
        cin >> z;
    }while(z=='y');
    return 0;
    
}
