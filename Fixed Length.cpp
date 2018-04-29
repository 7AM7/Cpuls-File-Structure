//
//  main.cpp
//  cpp
//
//  Created by AM7 on 1/26/18.
//  Copyright © 2018 AM7. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <string.h>
using namespace std;

class Student
{
private:
    char name[20];
    char rolNo[2];
    char branch[2];
    char marks[3];
    char grade;
    
public:

    void getData()
    {
        cout << "Student rolNo : ";
        cin >> rolNo;
        cout << "Student Name : ";
        cin >> name;
        cout << "Student branch : ";
        cin >> branch;
        cout << "Student Mark : ";
        cin >> marks;
        cout << "Student grade : ";
        cin >> grade;
    }
    
    void DisplayData()
    {
        cout << "Student rolNo : "<<rolNo<<endl;
        cout << "Student Name : " <<name<<endl;
        cout << "Student branch : " <<branch<<endl;
        cout << "Student Mark : "<< marks<<endl;
        cout << "Student grade : "<<grade<<endl;
    }
    int getRolNO(){
        return atoi(rolNo);
    }
};

//temp vector for sort file
vector <Student> temp;

class File
{
    public:
    void ShowALL(fstream& f,Student std)
    {
        while(f.read((char *)&std,sizeof(std)))
        {
            std.DisplayData();
        }
    }
    /*
    void EmptyData(Student std)
    {
        memset(&std, NULL, sizeof(std));
    }
     */
    void Insert(fstream& f,Student std)
    {
        std.getData();
        f.write((char *)&std,sizeof(std));
    }
    bool Search(fstream& f,Student std,int rolNO)
    {
        bool check=false;
        long pos;
        while(!f.eof())
        {
            pos = f.tellg();
            f.read((char *)&std,sizeof(std));
            if(std.getRolNO()==rolNO)
            {
                std.DisplayData();
                f.seekg(pos);
                check=true;
                break;
            }
        }
        return check;
    }
    void Delete(fstream& f,Student std,int rolNO)
    {
        ofstream tmp("tmp.txt",ios::out);
         f.read((char*)&std,sizeof(std));
        while (!f.eof())
        {
            if(std.getRolNO()!=rolNO)
            {
                 tmp.write((char *)&std,sizeof(std));
            }
            f.read((char*)&std,sizeof(std));
        }
        tmp.close();
        f.close();
        remove("test1.txt");
        rename("tmp.txt", "test1.txt");
    }
    void SortFile(fstream& f,Student std)
    {
        temp.clear();
        Student std1;
        std1.getData();

        while(f.read((char *)&std,sizeof(std)))
        {
            temp.push_back(std);
        }
        // push new object
        temp.push_back(std1);

    }
    bool Modify(fstream& f,Student std,int rolNO)
    {
        long pos;
        bool check =false;
        while (!f.eof())
        {
            pos = f.tellg();
             f.read((char*)&std,sizeof(std));
            if(std.getRolNO()==rolNO)
            {
                f.seekg(pos);
                Insert(f,std);
                check=true;
                break;
            }
        }
        return check;
    }
};
struct less_than_rolNo // to compare rolNO firt item with second item ----- for sort class this has data fileds
{
    bool operator() ( Student& std1,  Student& std2)
    {
        return (std1.getRolNO() < std2.getRolNO());
    }
};
int main(int argc, const char * argv[])
{
    Student std;
    File fs;
    int rolNO,choice;
    fstream f;
    char answ='y';
    if (!f)
    {
        cout << "cannot open file" << endl;
        return 0;
    }
    do{
        //system("clear"); cuz mac
        cout<<"1- Search for a student\n2- Append a student\n3- Insert a student in sorted file\n4- Delete a student\n5- Modify a student\n6- Show All\n7- Insert\n99- Exit\n";
        cout<<"Enter Your Choice: ";
        cin>>choice;
        switch (choice)
        {
            case 1:
                 cout<<"---------------------------------------------------\n";
                cout<<"Enter Student rolNo: ";
                cin>>rolNO;
                f.open("test1.txt", ios::in);
                if(!fs.Search(f,std, rolNO))cout<<"Not Found Student"<<endl;
                 cout<<"---------------------------------------------------\n";
                f.close();
                break;
            case 2:
                f.open("test1.txt", ios::out|ios::app);
               
                while (answ=='y' || answ=='Y')
                {
                    cout<<"---------------------------------------------------\n";
                    fs.Insert(f,std);
                    cout<<"Appended Successfully.."<<endl;
                    cout<<"Continue (y/n): ";
                    cin>>answ;
                    cout<<"---------------------------------------------------\n";
                }
                f.close();
                break;
            case 3:
                /*
                 myabe in this part i can use a new file like delete item(show next case) but i like this way.
                So, I use 2 ways:
                 1- vector or array as temp for super file. in (sorting file)
                 2- another file as temp for super file. in (delete object)
                 */
                
                
                cout<<"---------------------------------------------------\n";
                f.open("test1.txt", ios::in);
                fs.SortFile(f,std) ; //push data to vector
                f.close();
                f.open("test1.txt", ios::out);
                sort(temp.begin(),temp.end(),less_than_rolNo()); //sort vector before push it to file
                for(int i = 0;i<temp.size();i++)
                {
                    //push vector data to file after sorted
                    f.write((char *)&temp[i],sizeof(temp[i]));
                }
                cout<<"---------------------------------------------------\n";
                f.close();
                break;
            case 4:
                 cout<<"---------------------------------------------------\n";
                cout<<"Enter Student rolNo: ";
                cin>>rolNO;
                f.open("test1.txt", ios::in);
                fs.Delete(f, std, rolNO);
                cout<<"Deleted..";
                 cout<<"---------------------------------------------------\n";
                f.close();
                break;
            case 5:
                cout<<"---------------------------------------------------\n";
                cout<<"Enter Student rolNo: ";
                cin>>rolNO;
                f.open("test1.txt", ios::in |ios::out);
                if(!fs.Modify(f,std, rolNO))cout<<"Not Found Student"<<endl;
                f.close();
                f.open("test1.txt", ios::in);
                cout<<"----->After Modifed: "<<endl;
                fs.ShowALL(f, std);
                 cout<<"---------------------------------------------------\n";
                f.close();
                break;
            case 6:
                 cout<<"---------------------------------------------------\n";
                f.open("test1.txt", ios::in);
                fs.ShowALL(f,std);
                 cout<<"---------------------------------------------------\n";
                f.close();
                break;
            case 7:
                f.open("test1.txt", ios::out);
                cout<<"---------------------------------------------------\n";
                fs.Insert(f,std);
                cout<<"Inserted Successfully.."<<endl;
                cout<<"---------------------------------------------------\n";
                f.close();
                break;
            default:
                break;
        }
    }while (choice!=99);

    return 0;

}

