
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
    cout << "Main Menu\n"
         << "-------------------------------------------------\n"
         << "1. Drives\n"
         << "2. Directories\n"
         << "3. Files\n"
         << "0. Exit\n\n";
}

void drive_menu(){
    cout << "Let's work with Drives!\n"
         << "------------------------------------------------------------\n"
         << "1. Show all detected disks\n"
         << "2. Show all information about some disk\n"
         << "0. Return\n\n";
}

void file_attributes_menu(){
    cout << "Let's work with file's attributes!\n"
         << "------------------------------------------------------------------\n"
         << "1. Show all non-attributes of the file\n"
         << "2. Show time attributes of the file\n"
         << "3. Show attributes by handle of the file\n"
         << "4. Set non-attribute to the file\n"
         << "5. Set time attribute to the file\n"
         << "0. Return\n\n";
}

void dir_menu(){
    cout << "Let's work with directories!\n"
         << "-------------------------------------------------------------------\n"
         << "1. Create directory\n"
         << "2. Delete directory\n"
         << "0. Return\n\n";
}

void file_menu(){
   cout << "Let's work with Files!\n"
            << "---------------------------------------------------------------\n"
            << "1. Create file\n"
            << "2. Move file\n"
            << "3. Copy file\n"
            << "4. Work with file's attributes\n"
            << "0. Return\n\n";
}

void list_of_attrs(){
    cout << "It's the list of the available attributes! \n"
            << "-------------------------------------------------\n"
            << "1. FILE_ATTRIBUTE_ARCHIVE\n"
            << "2. FILE_ATTRIBUTE_HIDDEN\n"
            << "3. FILE_ATTRIBUTE_NORMAL\n"
            << "4. FILE_ATTRIBUTE_NOT_CONTENT_INDEXED\n"
            << "5. FILE_ATTRIBUTE_OFFLINE\n"
            << "6. FILE_ATTRIBUTE_READONLY\n"
            << "7. FILE_ATTRIBUTE_SYSTEM\n"
            << "8. FILE_ATTRIBUTE_TEMPORARY\n"
            << "0. Return\n\n";
}

#endif //LABA1_MAIN_MENU_H
