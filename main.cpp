#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <conio.h>

using namespace std;
const char AGENDA_DIR[] = "agenda.dat";

struct contact {
    char dni [15];
    char name [30];
    char surname [40];
    int age;
    char email [40];
};

void mainMenu();
void registerContact(contact c);
contact readContact();
bool contactExist(char dni[]);
void displayContact(char dni[]);
void listContacts();
void deleteContact(char dni[]);
void updateContact(char dni[]);
void menuRegister();
void menuSearch();
void menuList();
void menuDelete();
void menuUpdate();

int main() {
    mainMenu();
    return 0;
}

void registerContact(contact c) {
   ofstream output;
   output.open(AGENDA_DIR, ios::binary | ios::app);
   output.write((char*)&c, sizeof(contact));
   output.close();
}

contact readContact(){
   contact c;

   cout<<"\t\t\t\t  D.N.I: ";
   cin.getline(c.dni, 15);

   cout<<"\t\t\t\t   NAME: ";
   cin.getline(c.name, 30);

   cout<<"\t\t\t\tSURNAME: ";
   cin.getline(c.surname, 40);

   cout<<"\t\t\t\t    AGE: ";
   cin>>c.age;

   cin.ignore();

   cout<<"\t\t\t\t  EMAIL: ";
   cin.getline(c.email, 40);

   return c;
}

bool contactExist(char dni[]) {
    contact c;
    ifstream input;
    input.open(AGENDA_DIR, ios::binary);
    if (input.good()) {
        while (input.read((char*)&c, sizeof(contact))) {
           if(strcmp(dni, c.dni) == 0) {
                input.close();
                return true;
           }
        }
        input.close();
        return false;
    } else {
       input.close();
       return false;
    }
}

void displayContact(char dni[]) {
    contact c;
    ifstream input;
    input.open(AGENDA_DIR, ios::binary);
        while (input.read((char*)&c, sizeof(contact))) {
           if(strcmp(dni, c.dni) == 0) {
                cout<<"\n"<<endl;
                cout<<"\t\t\t\t   NAME: "<<c.name<<endl;
                cout<<"\t\t\t\tSURNAME: "<<c.surname<<endl;
                cout<<"\t\t\t\t    AGE: "<<c.age<<endl;
                cout<<"\t\t\t\t  EMAIL: "<<c.email<<endl;
                input.close();
           }
       }
}

void listContacts() {
    contact c;
    ifstream input;
    input.open(AGENDA_DIR, ios::binary);
        while (input.read((char*)&c, sizeof(contact))) {
                cout<<"\t\t\t\t  D.N.I: "<<c.dni<<endl;
                cout<<"\t\t\t\t   NAME: "<<c.name<<endl;
                cout<<"\t\t\t\tSURNAME: "<<c.surname<<endl;
                cout<<"\t\t\t\t    AGE: "<<c.age<<endl;
                cout<<"\t\t\t\t  EMAIL: "<<c.email<<endl;
                cout<<endl;
       }
       input.close();
}

void deleteContact(char dni[]) {
    contact c;
    ifstream input;
    input.open(AGENDA_DIR, ios::binary);
       while (input.read((char*)&c, sizeof(contact))) {
           if(strcmp(dni, c.dni) != 0) {
              ofstream temporal;
              temporal.open("temp.dat", ios::binary);
              temporal.write((char*)&c, sizeof(contact));
              temporal.close();
              input.close();
              remove(AGENDA_DIR);
              rename("temp.dat", AGENDA_DIR);
              cout<<"\n\t\t\t\t CONTACT DELETED!."<<endl;
              getch();
           }
       }
       input.close();
}


void updateContact(char dni[]) {
   contact c;
    ifstream input;
    input.open(AGENDA_DIR, ios::binary);
       while (input.read((char*)&c, sizeof(contact))) {
           if(strcmp(dni, c.dni) == 0) {
              contact updt = readContact();
              ofstream temporal;
              temporal.open("temp.dat", ios::binary);
              temporal.write((char*)&updt, sizeof(contact));
              temporal.close();
              input.close();
              remove(AGENDA_DIR);
              rename("temp.dat", AGENDA_DIR);
              cout<<"\n\t\t\t\t CONTACT UPDATED!."<<endl;
              getch();
           }
       }
       input.close();
}

/******************************/
void mainMenu(){
   int opt;
    do {
        system("cls");
        cout<<"\t\t\t\tAGENDA"<<endl;
        cout<<"\t\t\tAdd contact..................[1]"<<endl;
        cout<<"\t\t\tSearch contact...............[2]"<<endl;
        cout<<"\t\t\tList all contacts............[3]"<<endl;
        cout<<"\t\t\tDelete contact...............[4]"<<endl;
        cout<<"\t\t\tUpdate contact...............[5]"<<endl;
        cout<<"\t\t\tEXIT.........................[6]"<<endl;
        cout<<"\t\t\tPick your poison ->:";
        cin>>opt;
        cin.ignore();
        switch(opt){
            case 1 : system("cls");/** Clean Screen **/
                     menuRegister();
                     break;
            case 2 : system("cls");
                     menuSearch();
                     break;
            case 3 : system("cls");
                     menuList();
                     break;
            case 4 : system("cls");
                     menuDelete();
                     break;
            case 5 : system("cls");
                     menuUpdate();
                     break;
            case 6 : break;
            default: cout<<"\t\t\tInvalid option"<<endl;
        }
    } while(opt!=6);
}


/******************************/
void menuRegister(){
    cout<<"\t\t\t\tINGRESO DE NUEVO CONTACTO\n"<<endl;
    contact c = readContact();
    registerContact(c);
    cout<<"\n\tThe contact was added successfully. Press any key to return."<<endl;
    getch();
}

void menuSearch(){
    contact c;
    cout<<"\t\t\t\tSEARCH CONTACT"<<endl;
    cout<<"\t\t\tEnter the D.N.I of the contact: ";
    cin.getline(c.dni,15);
    if(contactExist(c.dni)){
        displayContact(c.dni);
        getch();
    }
    else{
        cout<<"\n\tThe file does not exist, is empty or the contact could not be found. Press any key to return."<<endl;
        getch();
    }
}

void menuList(){
    cout<<"\t\t\t\tLIST OF CONTACTS"<<endl;
    listContacts();
    getch();/**obtener caracter**/
}

void menuDelete(){
    cout<<"\t\t\t\tDELETE CONTACT\n"<<endl;
    contact c;
    cout<<"\tEnter the D.N.I of the contact you want to delete: ";
    cin.getline(c.dni,15);
    if(contactExist(c.dni)){
        int opt;
        cout<<"\n\tAre you sure you want to delete the following contact?\n";
        displayContact(c.dni);
        do{
            cout<<"\n\t\t\t\tYES[1]....NO[2]:";
            cin>>opt;
            switch(opt){
                case 1: deleteContact(c.dni);
                        break;
                case 2: break;
                default: cout<<"\n\t\t\tINVALID OPTION"<<endl;
            }
        }while(opt!=1 && opt!=2);
    }
    else {
       cout<<"\n\tThe file does not exist, is empty or the contact could not be found. Press any key to return."<<endl;
       getch();
    }
}
void menuUpdate(){
    cout<<"\t\t\t\tUpdate Contact\n"<<endl;
    contact c;
    cout<<"\t Enter the D.N.I of the contact you want to update: ";
    cin.getline(c.dni, 15);
    if(contactExist(c.dni)){
        cout<<"\n\t\t\t\tContact to update:\n"<<endl;
        displayContact(c.dni);
        updateContact(c.dni);
    }
    else {
        cout<<"\n\tThe file does not exist, is empty or the contact could not be found. Press any key to return."<<endl;
        getch();
    }
}
