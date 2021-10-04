
#ifndef LABA1_MAIN_MENU_H
#define LABA1_MAIN_MENU_H

using namespace std;


char input(void (*func)()){
    char choice;
    char c;
    int i;
    system("cls");
    func();
        cout << "Select paragraph" << endl;
        choice=getchar();
        i = 0;
        if (choice!='\n') while ((c = getchar()) != '\n')i++;
        if (i) choice = '-';
        return choice;
}


void main_menu(){
    cout << "MAIN MENU\n"
         << "1. Drive management\n"
         << "2. Directory management\n"
         << "3. File management\n"
         << "0. Exit\n\n";
}

void drive_menu(){
    cout << "DRIVE MANAGMENT MENU\n"
         << "1. Get a list of all drives\n"
         << "2. Get drive information\n"
         << "0. Go back\n\n";
}

void file_attributes_menu(){
    cout << "FILE ATTRIBUTES MANAGMENT MENU\n"
         << "1. Get attributes\n"
         << "2. Get time attributes\n"
         << "3. Get attributes by handle\n"
         << "4. Set attributes\n"
         << "5. Set time attributes\n"
         << "0. Go back\n\n";
}

void dir_menu(){
    cout << "DIRECTORY MANAGMENT MENU\n"
         << "1. Create directory\n"
         << "2. Remove directory\n"
         << "0. Go back\n\n";
}

void file_menu(){
   cout << "FILE MANAGMENT MENU\n"
            << "1. Create file\n"
            << "2. Move file\n"
            << "3. Copy file\n"
            << "4. File attributes management\n"
            << "0. Go back\n\n";
}

void list_of_attrs(){
    cout << "FILE ATTRIBUTES MENU \n"
            << "1. FILE_ATTRIBUTE_ARCHIVE\n"
            << "2. FILE_ATTRIBUTE_HIDDEN\n"
            << "3. FILE_ATTRIBUTE_NORMAL\n"
            << "4. FILE_ATTRIBUTE_NOT_CONTENT_INDEXED\n"
            << "5. FILE_ATTRIBUTE_OFFLINE\n"
            << "6. FILE_ATTRIBUTE_READONLY\n"
            << "7. FILE_ATTRIBUTE_SYSTEM\n"
            << "8. FILE_ATTRIBUTE_TEMPORARY\n"
            << "0. Go back\n\n";
}

#endif //LABA1_MAIN_MENU_H
