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
    void Create()
    {
        fstream f1,f2;
        cout <<"Enter First id:";
        cin>>emp.emp_id;
        cout <<"Enter First name:";
        cin>>emp.name;
        cout <<"Enter First salary:";
        cin>>emp.salary;
        indx.pos=0;
        char y='n';
        f2.open("indexer",ios::out|ios::app);
        f1.open("test",ios::out|ios::app);
        do{
            
            indx.emp_id=emp.emp_id;
            f2.write((char*)&indx,sizeof(Index));
            indx.pos++;
            
            f1.write((char*)&emp,sizeof(Employee));
            cout<<"Enter (y) to contuines: ";
            cin>>y;
        }while(y=='y');
        f2.close();
        f1.close();
    }
    
    void Display()
    {
        fstream f1,f2;
        f2.open("indexer",ios::in);
        f1.open("test",ios::in);
        while(f2.read((char*)&indx,sizeof(Index)))
        {
            int value = indx.pos*sizeof(Index);
            
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
    void PrintData(){
        cout<<emp.emp_id<<endl;
        cout<<emp.name<<endl;
        cout<<emp.salary<<endl;
    }
    bool Search(int id)
    {
        fstream f1,f2;
        f2.open("indexer",ios::in);
        f1.open("test",ios::in);
        bool check=false;
        while(f2.read((char*)&indx,sizeof(Index)))
        {
            if(indx.emp_id == id)
            {
                int value = indx.pos*sizeof(Index);
                
                f1.seekg(value);
                f1.read((char*)&emp,sizeof(Employee));
                if(emp.emp_id!=-1)
                {
                    check=true;
                    break;
                }
            }
        }
        f2.close();
        f1.close();
        return check;
    }

};




int main(){
    Company comp;
    
    comp.Create();
    comp.Display();


    return 0;
    
}
