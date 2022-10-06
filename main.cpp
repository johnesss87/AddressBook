#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct User {
    int id;
    string name, surname, phoneNumber, email, address;
};

string readLine() {
    string line = "";
    cin.sync();
    getline(cin,line);

    return line;
}

int downloadAddressBook(vector <User>& users, int usersNumber) {

    string line, spiltLine;
    fstream file;
    User user;

    file.open("AddressBook.txt", ios::in);
    if (file.good() == true) {
        while(getline(file,line)) {
            int switchNumber = 1;

            for (int i = 0, j = 0; i < line.length(); i++) {
                if (line[i] == '|') {
                    spiltLine = line.substr(j,i-j);

                    switch(switchNumber) {
                    case 1:
                        user.id = atoi(spiltLine.c_str());
                        break;
                    case 2:
                        user.name = spiltLine;
                        break;
                    case 3:
                        user.surname = spiltLine;
                        break;
                    case 4:
                        user.phoneNumber = spiltLine;
                        break;
                    case 5:
                        user.email = spiltLine;
                        break;
                    case 6:
                        user.address = spiltLine;
                        break;
                    }
                    j=i+1;
                    switchNumber++;
                }
            }
            users.push_back(user);
            usersNumber ++;
        }
        file.close();
    }
    return usersNumber;
}

int enterNewUser(vector <User>& users, int usersNumber) {
    string name, surname, phoneNumber, email, address;
    fstream file;
    User user;

    cout << "Podaj imie nowej osoby: " << endl;
    name = readLine();
    cout << "Podaj nazwisko nowej osoby: " << endl;;
    surname = readLine();
    cout << "Podaj nr telefonu nowej osoby: " << endl;;
    phoneNumber = readLine();
    cout << "Podaj e-mail nowej osoby: " << endl;;
    email = readLine();
    cout << "Podaj adres nowej osoby: "<< endl;
    address = readLine();

    if (usersNumber != 0) {
        user.id = users[usersNumber-1].id + 1;
    } else {
        user.id = 1;
    }
    user.name = name;
    user.surname = surname;
    user.phoneNumber = phoneNumber;
    user.email = email;
    user.address = address;

    users.push_back(user);

    file.open("AddressBook.txt", ios::out | ios::app);

    file << user.id << "|" << user.name << "|" << user.surname << "|" << user.phoneNumber << "|" << user.email << "|" << user.address << "|" << endl;

    file.close();

    cout << "Znajomy wprowadzony" << endl << endl;
    system("pause");
    return usersNumber + 1;
}

void searchByName(vector <User>& users, int usersNumber, string searchedName) {
    int positiveResultsNumber = 0;

    for (int i = 0; i < usersNumber; i++) {
        if (users[i].name == searchedName) {
            cout << users[i].id << "|" << users[i].name << "|" << users[i].surname << "|" << users[i].phoneNumber << "|" << users[i].email << "|" << users[i].address << "|" << endl;
            positiveResultsNumber++;
        }
    }

    if (positiveResultsNumber == 0) {
        cout << "Nie znaleziono wynikow dla imienia: " << searchedName << endl;
    }
    cout << endl;
    system("pause");
}

void searchBySurname(vector <User>& users, int usersNumber, string searchedSurname) {
    int positiveResultsNumber = 0;

    for (int i = 0; i < usersNumber; i++) {
        if (users[i].surname == searchedSurname) {
            cout << users[i].id << "|" << users[i].name << "|" << users[i].surname << "|" << users[i].phoneNumber << "|" << users[i].email << "|" << users[i].address << "|" << endl;
            positiveResultsNumber++;
        }
    }
    if (positiveResultsNumber == 0) {
        cout << "Nie znaleziono wynikow dla nazwiska: " << searchedSurname << endl;
    }
    cout << endl;
    system("pause");
}

void showWholeAdrressBook(vector <User>& users, int usersNumber) {
    if (usersNumber == 0) {
        cout << "Ksiazka Adresowa jest pusta" << endl;
    }

    for (int i = 0; i < usersNumber; i++) {
        cout << users[i].id << "|" << users[i].name << "|" << users[i].surname << "|" << users[i].phoneNumber << "|" << users[i].email << "|" << users[i].address << "|" << endl;
    }
    cout << endl;
    system("pause");
}

int deleteUserFromAdrressBook(vector <User>& users, int usersNumber, int idNumberToDelete) {
    char confirmButton;
    int idExistenceCheckPointer = usersNumber;

    fstream file;

    for (int i = 0; i < usersNumber; i++) {
        if (users[i].id == idNumberToDelete) {
            cout << "Adresat o podanym ID istnieje. Wcisnij 't' dla potwierdzenia operacji usuwania" << endl;
            cin >> confirmButton;

            if (confirmButton == 't') {
                for (int j=i; j < usersNumber; j++) {
                    users[j].id = users[j+1].id;
                    users[j].name = users[j+1].name;
                    users[j].surname = users[j+1].surname;
                    users[j].phoneNumber = users[j+1].phoneNumber;
                    users[j].email = users[j+1].email;
                    users[j].address = users[j+1].address;
                }
                usersNumber--;
                users.pop_back();

                file.open("AddressBook.txt", ios::out);

                for (int i = 0; i < usersNumber; i++) {
                    file << users[i].id << "|" << users[i].name << "|" << users[i].surname << "|" << users[i].phoneNumber << "|" << users[i].email << "|" << users[i].address << "|" << endl;
                }
                file.close();
                cout << "Adresat o podanym ID zostal usunietny" << endl;

            } else {
                cout << "Adreast o podanym ID nie zostal usuniety" << endl;
            }
        }
    }
    if (idExistenceCheckPointer == usersNumber) {
        cout << "Adresat o podanym ID nie istnieje" << endl;
    }
    cout << endl;
    system("pause");
    return usersNumber;
}

void makeChangeToExistingUser(vector <User>& users, int usersNumber, int idNumberToDelete) {
    string name, surname, phoneNumber, email, address;
    int idExistenceCheckPointer = 0;
    fstream file;

    for (int i = 0; i < usersNumber; i++) {
        if (users[i].id == idNumberToDelete) {

            char choice;

            while(choice != '6') {
                system("cls");
                cout << endl;
                cout << "MENU EDYCJI" << endl;
                cout << "*****************" << endl;
                cout << "1. Imie" << endl;
                cout << "2. Nazwisko" << endl;
                cout << "3. Numer Telefonu" << endl;
                cout << "4. Email" << endl;
                cout << "5. Adres" << endl;
                cout << "6. Powrot do menu glownego" << endl;
                cout << endl;

                choice = getch();

                switch(choice) {
                case '1':
                    cout << "Podaj nowe imie: " << endl;
                    name = readLine();
                    users[i].name = name;
                    cout << "Imie zostalo zmienione pomyslnie" << endl;
                    system("pause");
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: " << endl;
                    surname = readLine();
                    users[i].surname = surname;
                    cout << "Nazwisko zostalo zmienione pomyslnie" << endl << endl;
                    system("pause");
                    break;
                case '3':
                    cout << "Podaj nowy Numer Telefonu: " << endl;
                    phoneNumber = readLine();
                    users[i].phoneNumber = phoneNumber;
                    cout << "Numer Telefonu zostal zmieniony pomyslnie" << endl << endl;
                    system("pause");
                    break;
                case '4':
                    cout << "Podaj nowy Email: " << endl;
                    email = readLine();
                    users[i].email = email;
                    cout << "Emial zostal zmieniony pomyslnie" << endl << endl;
                    system("pause");
                    break;
                case '5':
                    cout << "Podaj nowy adres: " << endl;
                    address = readLine();
                    users[i].address = address;
                    cout << "Adres zostal zmieniony pomyslnie" << endl << endl;
                    system("pause");
                    break;
                case '6':
                    cout << "Wracasz do glownego manu" << endl << endl;
                    break;
                default:
                    cout << "Nie ma takiej opcji w menu!!!" << endl << endl;
                    system("pause");
                }
            }
            file.open("AddressBook.txt", ios::out);

            for (int i = 0; i < usersNumber; i++) {
                file << users[i].id << "|" << users[i].name << "|" << users[i].surname << "|" << users[i].phoneNumber << "|" << users[i].email << "|" << users[i].address << "|" << endl;
            }
            file.close();
        } else {
            idExistenceCheckPointer++;
        }
    }
    if (idExistenceCheckPointer == usersNumber) {
        cout << "Adresat o podanym ID nie istnieje" << endl;
    }
    cout << endl;
    system("pause");
}

int main() {

    vector <User> users;
    int usersNumber = 0, idNumberToDelete = 0, idNumberToChange = 0;
    string searchedName, searchedSurname;
    char choice;

    usersNumber = downloadAddressBook(users, usersNumber);

    while(true) {
        system("cls");
        cout << endl;
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "*****************" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << endl;

        choice = getch();

        switch(choice) {
        case '1':
            usersNumber = enterNewUser(users, usersNumber);
            break;
        case '2':
            cout << endl << "Podaj szukane imie: ";
            cin >> searchedName;
            cout << endl << "LISTA ADRESATOW O PODANYM IMIENIU:" << endl;
            searchByName(users, usersNumber, searchedName);
            break;
        case '3':
            cout << endl << "Podaj szukane nazwisko: ";
            cin >> searchedSurname;
            cout << endl << "LISTA ADRESATOW O PODANYM NAZWISKU:" <<endl;
            searchBySurname(users, usersNumber, searchedSurname);
            break;
        case '4':
            cout << "LISTA WSZYSTKICH ADRESATOW:" << endl;
            showWholeAdrressBook(users, usersNumber);
            break;
        case '5':
            if (usersNumber == 0) {
                cout << "Ksiazka Adresowa jest pusta, nie ma mozliwosci usuniecia adresata" << endl << endl;
                system("pause");
            } else {
                cout << "Podaj ID adresata ktorego chcesz usunac: " << endl;
                cin >> idNumberToDelete;
                usersNumber = deleteUserFromAdrressBook(users, usersNumber, idNumberToDelete);
            }
            break;
        case '6':
            if (usersNumber == 0) {
                cout << "Ksiazka Adresowa jest pusta, nie ma mozliwosci usuniecia adresata" << endl << endl;
                system("pause");
            } else {
                cout << "Podaj ID adresata ktorego dane chcesz zmienic: " << endl;
                cin >> idNumberToChange;
                makeChangeToExistingUser(users, usersNumber, idNumberToChange);
            }
            break;
        case '9':
            exit(0);
            break;

        default:
            cout << "Nie ma takiej opcji w menu!!!" << endl << endl;
            system("pause");
        }
    }
    return 0;
}
