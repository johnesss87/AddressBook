#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct User {
    int idUser;
    string login, password;
};

struct Contact {
    int idContact, idUser;
    string name, surname, phoneNumber, email, address;
};

string readLine() {
    string line = "";
    cin.sync();
    getline(cin,line);

    return line;
}

void downloadUsersList(vector <User>& users) {

    string line, spiltLine;
    fstream file;
    User user;

    file.open("Users.txt", ios::in);
    if (file.good()) {
        while(getline(file,line)) {
            int switchNumber = 1;

            for (int i = 0, j = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    spiltLine = line.substr(j,i-j);

                    switch(switchNumber) {
                    case 1:
                        user.idUser = atoi(spiltLine.c_str());
                        break;
                    case 2:
                        user.login = spiltLine;
                        break;
                    case 3:
                        user.password = spiltLine;
                        break;
                    }
                    j=i+1;
                    switchNumber++;
                }
            }
            users.push_back(user);
        }
        file.close();
    }
}

void registration (vector <User>& users) {
    string login, password;
    fstream file;
    User user;

    cout << "Podaj nazwe uzytkownika: ";
    cin >> login;
    int i = 0;
    while (i < (int) users.size()) {
        if (users[i].login == login) {
            cout << "Taki uzytkownik juz istnieje. Podaj inna nazwe uzytkownika: ";
            cin >> login;
            i = 0;
        } else {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> password;
    user.login = login;
    user.password = password;
    user.idUser = users.size() + 1;

    users.push_back(user);

    file.open("Users.txt", ios::out | ios::app);

    file << user.idUser << "|" << user.login << "|" << user.password << "|" << endl;

    file.close();

    cout << "Konto zalozono pomyslnie!" << endl;
    system("pause");
}

void downloadAddressBook(vector <Contact>& contacts, int idLoggedUser) {

    string line, spiltLine;
    fstream file;
    Contact contact;

    file.open("AddressBook.txt", ios::in);
    if (file.good()) {
        while(getline(file,line)) {
            int switchNumber = 1;

            for (int i = 0, j = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    spiltLine = line.substr(j,i-j);

                    switch(switchNumber) {
                    case 1:
                        contact.idContact = atoi(spiltLine.c_str());
                        break;
                    case 2:
                        contact.idUser = atoi(spiltLine.c_str());
                        break;
                    case 3:
                        contact.name = spiltLine;
                        break;
                    case 4:
                        contact.surname = spiltLine;
                        break;
                    case 5:
                        contact.phoneNumber = spiltLine;
                        break;
                    case 6:
                        contact.email = spiltLine;
                        break;
                    case 7:
                        contact.address = spiltLine;
                        break;
                    }
                    j=i+1;
                    switchNumber++;
                }
            }
            if(contact.idUser == idLoggedUser) {
                contacts.push_back(contact);
            }
        }
        file.close();
    }
}

int latestIdNumberControlInFile() {

    string line, spiltLine;
    fstream file;
    int latestIdContactNumberInFile = 0;

    file.open("AddressBook.txt", ios::in);
    if (file.good()) {
        while(getline(file,line)) {
            int switchNumber = 1;

            for (int i = 0, j = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    spiltLine = line.substr(j,i-j);

                    switch(switchNumber) {
                    case 1:
                        latestIdContactNumberInFile = atoi(spiltLine.c_str());
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    }
                    j=i+1;
                    switchNumber++;
                }
            }
        }
        file.close();
    }
    return latestIdContactNumberInFile;
}

void removeContactFromFile(int idContactNumberToDelete) {

    string line, spiltLine;
    fstream file, tempFile;

    file.open("AddressBook.txt", ios::in);
    tempFile.open("Temp.txt", ios::out);
    if (file.good()) {
        while(getline(file,line)) {
            int switchNumber = 1;
            int removedLinePointer = 0;

            for (int i = 0, j = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    spiltLine = line.substr(j,i-j);

                    switch(switchNumber) {
                    case 1:
                        if (idContactNumberToDelete == atoi(spiltLine.c_str())) {
                            removedLinePointer = 1;
                            break;
                        } else {
                            tempFile << atoi(spiltLine.c_str()) << "|";
                            break;
                        }
                    case 2:
                        if (removedLinePointer == 1) {
                            break;
                        } else {
                            tempFile << atoi(spiltLine.c_str()) << "|";
                            break;
                        }
                    case 3:
                        if (removedLinePointer == 1) {
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 4:
                        if (removedLinePointer == 1) {
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 5:
                        if (removedLinePointer == 1) {
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 6:
                        if (removedLinePointer == 1) {
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 7:
                        if (removedLinePointer == 1) {
                            break;
                        } else {
                            tempFile << spiltLine << "|" << endl;
                            break;
                        }
                    }
                    j=i+1;
                    switchNumber++;
                }
            }
        }
        file.close(), tempFile.close();
        remove ("AddressBook.txt");
        rename("Temp.txt", "AddressBook.txt");
    }
}

void makeChangeInFile (vector <Contact>& contacts, int contactLinePointer) {

    string line, spiltLine;
    fstream file, tempFile;

    file.open("AddressBook.txt", ios::in);
    tempFile.open("Temp.txt", ios::out);
    if (file.good()) {
        while(getline(file,line)) {
            int switchNumber = 1;
            int changedLinePointer = 0;

            for (int i = 0, j = 0; i < (int) line.length(); i++) {
                if (line[i] == '|') {
                    spiltLine = line.substr(j,i-j);

                    switch(switchNumber) {
                    case 1:
                        tempFile << atoi(spiltLine.c_str()) << "|";
                        if (contacts[contactLinePointer].idContact == atoi(spiltLine.c_str())) {
                            changedLinePointer = 1;
                        }
                        break;
                    case 2:
                        tempFile << atoi(spiltLine.c_str()) << "|";
                        break;
                    case 3:
                        if (changedLinePointer == 1) {
                            tempFile << contacts[contactLinePointer].name << "|";
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 4:
                        if (changedLinePointer == 1) {
                            tempFile << contacts[contactLinePointer].surname << "|";
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 5:
                        if (changedLinePointer == 1) {
                            tempFile << contacts[contactLinePointer].phoneNumber << "|";
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 6:
                        if (changedLinePointer == 1) {
                            tempFile << contacts[contactLinePointer].email << "|";
                            break;
                        } else {
                            tempFile << spiltLine << "|";
                            break;
                        }
                    case 7:
                        if (changedLinePointer == 1) {
                            tempFile << contacts[contactLinePointer].address << "|" << endl;
                            break;
                        } else {
                            tempFile << spiltLine << "|" << endl;
                            break;
                        }
                    }
                    j=i+1;
                    switchNumber++;
                }
            }
        }
        file.close(), tempFile.close();
        remove ("AddressBook.txt");
        rename("Temp.txt", "AddressBook.txt");
    }
}

void enterNewContact(vector <Contact>& contacts, int idLoggedUser) {
    fstream file;
    Contact contact;

    int latestIdContactNumberInFile = latestIdNumberControlInFile();

    contact.idContact = latestIdContactNumberInFile + 1;
    cout << "Podaj imie nowej osoby: " << endl;
    contact.name = readLine();
    cout << "Podaj nazwisko nowej osoby: " << endl;;
    contact.surname = readLine();
    cout << "Podaj nr telefonu nowej osoby: " << endl;;
    contact.phoneNumber = readLine();
    cout << "Podaj e-mail nowej osoby: " << endl;;
    contact.email = readLine();
    cout << "Podaj adres nowej osoby: "<< endl;
    contact.address = readLine();
    contact.idUser = idLoggedUser;

    contacts.push_back(contact);

    file.open("AddressBook.txt", ios::out | ios::app);

    file << contact.idContact << "|" << contact.idUser << "|" << contact.name << "|" << contact.surname << "|" << contact.phoneNumber << "|" << contact.email << "|" << contact.address << "|" << endl;

    file.close();

    cout << "Znajomy wprowadzony" << endl << endl;
    system("pause");
}

void searchByName(vector <Contact>& contacts) {
    int positiveResultsNumber = 0;
    string searchedName;

    cout << endl << "Podaj szukane imie: ";
    cin >> searchedName;

    cout << endl << "LISTA ADRESATOW O PODANYM IMIENIU:" << endl;
    for (int i = 0; i < (int) contacts.size(); i++) {
        if (contacts[i].name == searchedName) {
            cout << contacts[i].idContact << "|" << contacts[i].name << "|" << contacts[i].surname << "|" << contacts[i].phoneNumber << "|" << contacts[i].email << "|" << contacts[i].address << "|" << endl;
            positiveResultsNumber++;
        }
    }

    if (positiveResultsNumber == 0) {
        cout << "Nie znaleziono wynikow dla imienia: " << searchedName << endl;
    }
    cout << endl;
    system("pause");
}

void searchBySurname(vector <Contact>& contacts) {
    int positiveResultsNumber = 0;
    string searchedSurname;

    cout << endl << "Podaj szukane nazwisko: ";
    cin >> searchedSurname;

    cout << endl << "LISTA ADRESATOW O PODANYM NAZWISKU:" <<endl;
    for (int i = 0; i < (int) contacts.size(); i++) {
        if (contacts[i].surname == searchedSurname) {
            cout << contacts[i].idContact << "|" << contacts[i].name << "|" << contacts[i].surname << "|" << contacts[i].phoneNumber << "|" << contacts[i].email << "|" << contacts[i].address << "|" << endl;
            positiveResultsNumber++;
        }
    }
    if (positiveResultsNumber == 0) {
        cout << "Nie znaleziono wynikow dla nazwiska: " << searchedSurname << endl;
    }
    cout << endl;
    system("pause");
}

void showWholeAdrressBook(vector <Contact>& contacts) {

    cout << "LISTA WSZYSTKICH ADRESATOW:" << endl;
    if (contacts.size() == 0) {
        cout << "Ksiazka Adresowa jest pusta" << endl;
    }
    for (int i = 0; i < (int) contacts.size(); i++) {
        cout << contacts[i].idContact << "|" << contacts[i].name << "|" << contacts[i].surname << "|" << contacts[i].phoneNumber << "|" << contacts[i].email << "|" << contacts[i].address << "|" << endl;
    }
    cout << endl;
    system("pause");
}

void deleteContactFromAdrressBook(vector <Contact>& contacts) {
    char confirmButton;
    int idContactNumberToDelete = 0;
    int idContactExistenceCheckPointer = contacts.size();

    fstream file;

    if (contacts.size() == 0) {
        cout << "Ksiazka Adresowa jest pusta, nie ma mozliwosci usuniecia adresata" << endl << endl;
        system("pause");
    } else {
        cout << "Podaj ID adresata ktorego chcesz usunac: " << endl;
        cin >> idContactNumberToDelete;

        for (int i = 0; i < contacts.size(); i++) {
            if (contacts[i].idContact == idContactNumberToDelete) {
                cout << "Adresat o podanym ID istnieje. Wcisnij 't' dla potwierdzenia operacji usuwania" << endl;
                cin >> confirmButton;
                if (confirmButton == 't') {
                    contacts.erase(contacts.begin() + i);

                    removeContactFromFile(idContactNumberToDelete);

                    cout << "Adresat o podanym ID zostal usunietny" << endl;

                } else {
                    cout << "Adreast o podanym ID nie zostal usuniety" << endl;
                }
            }
        }
        if (idContactExistenceCheckPointer == contacts.size()) {
            cout << "Adresat o podanym ID nie istnieje" << endl;
        }
        cout << endl;
        system("pause");
    }
}

void makeChangeToExistingContact(vector <Contact>& contacts) {
    int idContactNumberToChange = 0;
    int idContactExistenceCheckPointer = 0;
    int contactLinePointer = 0;
    char choice;
    fstream file;

    if (contacts.size() == 0) {
        cout << "Ksiazka Adresowa jest pusta, nie ma mozliwosci zmiany danych adresata" << endl << endl;
        system("pause");
    } else {
        cout << "Podaj ID adresata ktorego dane chcesz zmienic: " << endl;
        cin >> idContactNumberToChange;

        for (int i = 0; i < contacts.size(); i++) {
            if (contacts[i].idContact == idContactNumberToChange) {
                contactLinePointer = i;

                while(choice != '6') {
                    system("cls");
                    cout << endl;
                    cout << "MENU EDYCJI" << endl;
                    cout << "****************************" << endl;
                    cout << "1. Imie" << endl;
                    cout << "2. Nazwisko" << endl;
                    cout << "3. Numer Telefonu" << endl;
                    cout << "4. Email" << endl;
                    cout << "5. Adres" << endl;
                    cout << "****************************" << endl;
                    cout << "6. Powrot do poprzedniego menu" << endl;
                    cout << endl;

                    choice = getch();

                    switch(choice) {
                    case '1':
                        cout << "Podaj nowe imie: " << endl;
                        contacts[i].name = readLine();
                        cout << "Imie zostalo zmienione pomyslnie" << endl;
                        system("pause");
                        break;
                    case '2':
                        cout << "Podaj nowe nazwisko: " << endl;
                        contacts[i].surname = readLine();
                        cout << "Nazwisko zostalo zmienione pomyslnie" << endl << endl;
                        system("pause");
                        break;
                    case '3':
                        cout << "Podaj nowy Numer Telefonu: " << endl;
                        contacts[i].phoneNumber = readLine();
                        cout << "Numer Telefonu zostal zmieniony pomyslnie" << endl << endl;
                        system("pause");
                        break;
                    case '4':
                        cout << "Podaj nowy Email: " << endl;
                        contacts[i].email = readLine();
                        cout << "Emial zostal zmieniony pomyslnie" << endl << endl;
                        system("pause");
                        break;
                    case '5':
                        cout << "Podaj nowy adres: " << endl;
                        contacts[i].address = readLine();
                        cout << "Adres zostal zmieniony pomyslnie" << endl << endl;
                        system("pause");
                        break;
                    case '6':
                        cout << "Wracasz do poprzedniego menu" << endl << endl;
                        break;
                    default:
                        cout << "Nie ma takiej opcji w menu!!!" << endl << endl;
                        system("pause");
                    }
                }
            } else {
                idContactExistenceCheckPointer++;
            }
        }
        if (idContactExistenceCheckPointer == contacts.size()) {
            cout << "Adresat o podanym ID nie istnieje" << endl;
        }
        cout << endl;
        makeChangeInFile(contacts, contactLinePointer);
        system("pause");
    }
}

void passwordChange(vector <User>& users, int idLoggedUser) {
    string password;
    fstream file;
    char choice;

    system("cls");
    cout << endl;
    cout << "ZMIANA HASLA" << endl;
    cout << "*****************" << endl;
    cout << "1. Zmiana hasla" << endl;
    cout << "9. Wroc do poprzedniego menu" << endl;
    cout << endl;

    choice = getch();
    switch(choice) {
    case '1':
        cout << "Podaj nowe haslo: ";
        cin >> password;
        for (int i = 0; i < users.size(); i++) {
            if (users[i].idUser == idLoggedUser) {
                users[i].password = password;
                cout << "Haslo zostalo zmienione pomyslnie!" << endl;

                file.open("Users.txt", ios::out);
                for (int i = 0; i < users.size(); i++) {
                    file << users[i].idUser << "|" << users[i].login << "|" << users[i].password << "|" << endl;
                }
                file.close();

                system("pause");
            }
        }
        break;
    case '9':
        cout << "Wracasz do poprzedniego menu" << endl << endl;
        break;
    default:
        cout << "Nie ma takiej opcji w menu!!!" << endl << endl;
        system("pause");
    }
}

void addressBookMenu(vector <User>& users, int idLoggedUser) {

    vector <Contact> contacts;
    char choice;

    downloadAddressBook(contacts, idLoggedUser);

    while(choice != '9') {
        system("cls");
        cout << endl;
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "****************************" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "****************************" << endl;
        cout << "7. Zmiana hasla uzytkownika" << endl;
        cout << "****************************" << endl;
        cout << "9. Wyloguj sie" << endl;
        cout << endl;

        choice = getch();

        switch(choice) {
        case '1':
            enterNewContact(contacts, idLoggedUser);
            break;
        case '2':
            searchByName(contacts);
            break;
        case '3':
            searchBySurname(contacts);
            break;
        case '4':
            showWholeAdrressBook(contacts);
            break;
        case '5':
            deleteContactFromAdrressBook(contacts);
            break;
        case '6':
            makeChangeToExistingContact(contacts);
            break;
        case '7':
            passwordChange(users, idLoggedUser);
            break;
        case '9':
            cout << "Zostales wylogowany" << endl << endl;
            system("pause");
            break;
        default:
            cout << "Nie ma takiej opcji w menu!!!" << endl << endl;
            system("pause");
        }
    }
}

void loginOperation(vector <User>& users) {
    string login, password;

    cout << "Podaj nazwe: ";
    cin >> login;
    int i = 0;
    while (i < users.size()) {
        if (users[i].login == login) {
            for (int attempts = 0; attempts < 3; attempts++) {
                cout << "Podaj haslo. Pozostalo prob " << 3 - attempts << ": ";
                cin >> password;
                if (users[i].password == password) {
                    cout << "Zalogowales sie pomyslnie!" << endl;
                    system("pause");
                    addressBookMenu(users, users[i].idUser);
                    return;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
        }
        i++;
    }
    cout << "Nie istnieje uzytkownik o podanym loginie" << endl;
    system("pause");
}

int main() {

    vector <User> users;
    char choice;

    downloadUsersList(users);

    while(true) {

        system("cls");
        cout << endl;
        cout << "LOGOWANIE" << endl;
        cout << "****************************" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "****************************" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << endl;

        choice = getch();

        switch(choice) {
        case '1':
            registration(users);
            break;
        case '2':
            loginOperation(users);
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
