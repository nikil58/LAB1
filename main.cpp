#include <iostream>
#include <windows.h>
#include "main_menu.h"



using namespace std;

void getDisks(){
    int counter = 0;
    DWORD myDrivesBitMask = GetLogicalDrives();
    if (myDrivesBitMask == 0) cout << "There is some error with reading disks";
    else {
        while (myDrivesBitMask){
            if (myDrivesBitMask & 1)
                cout << "Disk " << char(65+counter) << endl;
            counter++;
            myDrivesBitMask>>=1;
        }
    }
}

void getDisksWithString(){
    DWORD diskLengthBuffer = MAX_PATH;
    char diskLengthStringBuffer[MAX_PATH];
    DWORD Result = GetLogicalDriveStrings(diskLengthBuffer, diskLengthStringBuffer);

    if (Result > 0 && Result <= MAX_PATH)
    {
        char* currentDrive = diskLengthStringBuffer;
        while(*currentDrive)
        {
            printf("Disk: %s\n", currentDrive);

            // get the next drive
            currentDrive += strlen(currentDrive) + 1;
        }
    }
}

void typeDisk(const CHAR *Drive){
    switch (GetDriveType(Drive)){
        case 1:
            cout << Drive <<" Unknown type of Drive"<< endl;
            break;
        case 2:
            cout << Drive <<" No such Drive mounted"<< endl;
            break;
        case 3:
            cout << Drive <<" This drive is removable" << endl;
            break;
        case 4:
            cout << Drive << " This drive is fixed" << endl;
            break;
        case 5:
            cout << Drive << " This drive is remote" << endl;
            break;
        case 6:
            cout << Drive << " This drive is CD ROM" << endl;
            break;
        case 7:
            cout << Drive << " This drive is RAMDISK" << endl;
            break;
    }
}

void volumeDrive(const CHAR *Drive){
    char NameBuffer[MAX_PATH];
    char SysNameBuffer[MAX_PATH];
    DWORD SerialNumber;
    DWORD MaxComponentLength;
    DWORD FileSysFlags;

    if (GetVolumeInformation(Drive, NameBuffer, sizeof(NameBuffer),
                             &SerialNumber, &MaxComponentLength, &FileSysFlags, SysNameBuffer, sizeof(SysNameBuffer)))
    {
        cout << "Volume name is " << NameBuffer << endl;
        cout << "File system name is "<<  SysNameBuffer << endl;
        cout << "Serial number is " << SerialNumber << endl;
        cout << "Maximal components length is " << MaxComponentLength << endl;
        cout << "There is list of system flags: " << endl;
        if (FileSysFlags & FILE_CASE_PRESERVED_NAMES) cout << "FILE_CASE_PRESERVED_NAMES" << endl;
        if (FileSysFlags & FILE_CASE_SENSITIVE_SEARCH) cout << "FILE_CAS"
                                                               ""
                                                               "E_SENSITIVE_SEARCH" << endl;
        if (FileSysFlags & FILE_FILE_COMPRESSION) cout << "FILE_FILE_COMPRESSION" << endl;
        if (FileSysFlags & FILE_NAMED_STREAMS) cout << "FILE_NAMED_STREAMS" << endl;
        if (FileSysFlags & FILE_PERSISTENT_ACLS) cout << "FILE_PERSISTENT_ACLS" << endl;
        if (FileSysFlags & FILE_READ_ONLY_VOLUME) cout << "FILE_READ_ONLY_VOLUME" << endl;
        if (FileSysFlags & FILE_SEQUENTIAL_WRITE_ONCE) cout << "FILE_SEQUENTIAL_WRITE_ONCE" << endl;
        if (FileSysFlags & FILE_SUPPORTS_ENCRYPTION) cout << "FILE_SUPPORTS_ENCRYPTION" << endl;
        if (FileSysFlags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES) cout << "FILE_SUPPORTS_EXTENDED_ATTRIBUTES" << endl;
        if (FileSysFlags & FILE_SUPPORTS_HARD_LINKS) cout << "FILE_SUPPORTS_HARD_LINKS" << endl;
        if (FileSysFlags & FILE_SUPPORTS_OBJECT_IDS) cout << "FILE_SUPPORTS_OBJECT_IDS" << endl;
        if (FileSysFlags & FILE_SUPPORTS_OPEN_BY_FILE_ID) cout << "FILE_SUPPORTS_OPEN_BY_FILE_ID" << endl;
        if (FileSysFlags & FILE_SUPPORTS_REPARSE_POINTS) cout << "FILE_SUPPORTS_REPARSE_POINTS" << endl;
        if (FileSysFlags & FILE_SUPPORTS_SPARSE_FILES) cout << "FILE_SUPPORTS_SPARSE_FILES" << endl;
        if (FileSysFlags & FILE_SUPPORTS_TRANSACTIONS) cout << "FILE_SUPPORTS_TRANSACTIONS" << endl;
        if (FileSysFlags & FILE_SUPPORTS_USN_JOURNAL) cout << "FILE_SUPPORTS_USN_JOURNAL" << endl;
        if (FileSysFlags & FILE_UNICODE_ON_DISK) cout << "FILE_UNICODE_ON_DISK" << endl;
        if (FileSysFlags & FILE_VOLUME_IS_COMPRESSED) cout << "FILE_VOLUME_IS_COMPRESSED" << endl;
        if (FileSysFlags & FILE_VOLUME_QUOTAS) cout << "FILE_VOLUME_QUOTAS" << endl;
    }
}

void freeSpaceDrive(const CHAR *Drive){
    BOOLEAN Result;
    DWORD SectorsPerCluster;
    DWORD BytesPerSector;
    DWORD FreeClusters;
    DWORD TotalClusters;

    //get disk space for current drive
    Result = GetDiskFreeSpace(
            Drive, //current drive
            &SectorsPerCluster, //sectors per cluster
            &BytesPerSector, //bytes per sector
            &FreeClusters, //free clusters
            &TotalClusters //total clusters
    );

    if(!Result){
        printf("Could not get drive information.\n");
    }

    printf("Bytes per sector: %d\n", BytesPerSector);
    printf("Sectors per cluster: %d\n", SectorsPerCluster);
    printf("Free clusters: %d\n", FreeClusters);
    printf("Total clusters: %d\n", TotalClusters);

    unsigned int uiKBPerCluster = BytesPerSector * SectorsPerCluster / 1024;

    printf("You have %.2f MB of free storage\n", (double) uiKBPerCluster * FreeClusters / 1024);
    printf("You have %.2f MB of total storage\n", (double) uiKBPerCluster * TotalClusters / 1024);
}


void createDIR(const CHAR *Path){
    if (CreateDirectory(Path, nullptr))
        cout << "directory create" << endl;
    else
        cout << "error create directory" << endl;
}

void rmDIR(const CHAR *Path){
    if (RemoveDirectory(Path)) cout << "Directory was deleted" << endl;
    else cout << "ERROR: Directory wasn't deleted" << endl;
}

void createFile(const CHAR *Path){
    HANDLE creator;
    creator=CreateFile(Path, GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                       nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if(creator != INVALID_HANDLE_VALUE)
    {
        cout << "File was created successfully!" << endl;
        CloseHandle(creator);
    } else
        cout << "Error with handle" << endl;
}

void copy (const CHAR *Pathold, const CHAR *Pathnew){
    if (CopyFile(Pathold, Pathnew, true)) cout << "File was copied successfully" << endl;
    else cout << "There is some error with copping" << endl;
}

bool move(const CHAR *Pathold, const CHAR *Pathnew){
    bool result = MoveFile(Pathold,Pathnew);
    if (result) cout << "Moving file was completed" << endl;
    return result;
}

void moveEX(const CHAR *Pathold, const CHAR *Pathnew){
    if (MoveFileEx(Pathold,Pathnew, MOVEFILE_REPLACE_EXISTING)) cout << "Moving file was completed" << endl;
    else cout << "Error moving file" << endl;
}


void workWithAttributes(const CHAR *Path){
    DWORD bitMask = GetFileAttributes(Path);
    if (bitMask & FILE_ATTRIBUTE_ARCHIVE) cout << "FILE_ATTRIBUTE_ARCHIVE" << endl;
    if (bitMask & FILE_ATTRIBUTE_COMPRESSED) cout << "FILE_ATTRIBUTE_COMPRESSED" << endl;
    if (bitMask & FILE_ATTRIBUTE_DEVICE) cout <<"FILE_ATTRIBUTE_DEVICE"<<endl;
    if (bitMask & FILE_ATTRIBUTE_DIRECTORY) cout << "FILE_ATTRIBUTE_DIRECTORY" << endl;
    if (bitMask & FILE_ATTRIBUTE_DIRECTORY) cout << "FILE_ATTRIBUTE_DIRECTORY" << endl;
    if (bitMask & FILE_ATTRIBUTE_HIDDEN) cout << "FILE_ATTRIBUTE_HIDDEN" << endl;
    if (bitMask & FILE_ATTRIBUTE_NORMAL) cout << "FILE_ATTRIBUTE_NORMAL" << endl;
    if (bitMask & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) cout <<"FILE_ATTRIBUTE_NOT_CONTENT_INDEXED"<<endl;
    if (bitMask & FILE_ATTRIBUTE_OFFLINE) cout << "FILE_ATTRIBUTE_OFFLINE" << endl;
    if (bitMask & FILE_ATTRIBUTE_READONLY) cout << "FILE_ATTRIBUTE_READONLY\t" << endl;
    if (bitMask & FILE_ATTRIBUTE_REPARSE_POINT) cout << "FILE_ATTRIBUTE_REPARSE_POINT" << endl;
    if (bitMask & FILE_ATTRIBUTE_SPARSE_FILE) cout << "FILE_ATTRIBUTE_SPARSE_FILE" << endl;
    if (bitMask & FILE_ATTRIBUTE_SYSTEM) cout << "FILE_ATTRIBUTE_SYSTEM" << endl;
    if (bitMask & FILE_ATTRIBUTE_TEMPORARY) cout << "FILE_ATTRIBUTE_TEMPORARY" << endl;
}

void setAttributes(const CHAR *Path, DWORD attr){
    if (SetFileAttributes(Path, attr)) cout << "New attribute was successfully set up" << endl;
    else cout << "There is some error" << endl;
}

void getAttrsByHandle(const CHAR *Path){
    HANDLE Opener = CreateFile(Path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (Opener != INVALID_HANDLE_VALUE) {
        BY_HANDLE_FILE_INFORMATION fileInfo;
        if (GetFileInformationByHandle(Opener, &fileInfo)) {
            DWORD bitMask;
            SYSTEMTIME systime;
            bitMask = fileInfo.dwFileAttributes;
            if (bitMask & FILE_ATTRIBUTE_ARCHIVE) cout << "FILE_ATTRIBUTE_ARCHIVE" << endl;
            if (bitMask & FILE_ATTRIBUTE_COMPRESSED) cout << "FILE_ATTRIBUTE_COMPRESSED" << endl;
            if (bitMask & FILE_ATTRIBUTE_DEVICE) cout <<"FILE_ATTRIBUTE_DEVICE"<<endl;
            if (bitMask & FILE_ATTRIBUTE_DIRECTORY) cout << "FILE_ATTRIBUTE_DIRECTORY" << endl;
            if (bitMask & FILE_ATTRIBUTE_DIRECTORY) cout << "FILE_ATTRIBUTE_DIRECTORY" << endl;
            if (bitMask & FILE_ATTRIBUTE_HIDDEN) cout << "FILE_ATTRIBUTE_HIDDEN" << endl;
            if (bitMask & FILE_ATTRIBUTE_NORMAL) cout << "FILE_ATTRIBUTE_NORMAL" << endl;
            if (bitMask & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED) cout <<"FILE_ATTRIBUTE_NOT_CONTENT_INDEXED"<<endl;
            if (bitMask & FILE_ATTRIBUTE_OFFLINE) cout << "FILE_ATTRIBUTE_OFFLINE" << endl;
            if (bitMask & FILE_ATTRIBUTE_READONLY) cout << "FILE_ATTRIBUTE_READONLY\t" << endl;
            if (bitMask & FILE_ATTRIBUTE_REPARSE_POINT) cout << "FILE_ATTRIBUTE_REPARSE_POINT" << endl;
            if (bitMask & FILE_ATTRIBUTE_SPARSE_FILE) cout << "FILE_ATTRIBUTE_SPARSE_FILE" << endl;
            if (bitMask & FILE_ATTRIBUTE_SYSTEM) cout << "FILE_ATTRIBUTE_SYSTEM" << endl;
            if (bitMask & FILE_ATTRIBUTE_TEMPORARY) cout << "FILE_ATTRIBUTE_TEMPORARY" << endl;
            cout << "Serial number: " << fileInfo.dwVolumeSerialNumber << '\n';
            if (FileTimeToSystemTime(&fileInfo.ftCreationTime, &systime)) cout << systime.wYear << '-' << systime.wMonth << '-' << systime.wDay
                                                                               << ' ' << systime.wDayOfWeek << ' ' << systime.wHour << ':'
                                                                               << systime.wMinute << ':' << systime.wSecond << ':' << systime.wMilliseconds << '\n';
            if (FileTimeToSystemTime(&fileInfo.ftLastAccessTime, &systime)) cout << systime.wYear << '-' << systime.wMonth << '-' << systime.wDay
                                                                                 << ' ' << systime.wDayOfWeek << ' ' << systime.wHour << ':'
                                                                                 << systime.wMinute << ':' << systime.wSecond << ':' << systime.wMilliseconds << '\n';
            if (FileTimeToSystemTime(&fileInfo.ftLastWriteTime, &systime)) cout << systime.wYear << '-' << systime.wMonth << '-' << systime.wDay
                                                                                << ' ' << systime.wDayOfWeek << ' ' << systime.wHour << ':'
                                                                                << systime.wMinute << ':' << systime.wSecond << ':' << systime.wMilliseconds << '\n';
            std::cout << "File size: "
                      << (static_cast<long long>(fileInfo.nFileSizeHigh) << 32)
                         + static_cast<long long>(fileInfo.nFileSizeLow) << '\n';
            std::cout << "Number of links: " << fileInfo.nNumberOfLinks << '\n';
            std::cout << "ID: "
                      << (static_cast<long long>(fileInfo.nFileIndexHigh) << 32)
                         + static_cast<long long>(fileInfo.nFileIndexLow) << '\n';
            CloseHandle(Opener);
        }
        else
            std::cout << "Error occurred while getting info by handle. Error code: "
                      << GetLastError() << '\n';
    }
    else
        std::cout << "Error occurred while opening the file. Error code: "
                  << GetLastError() << '\n';
}

void getFileTime(const CHAR *Path){
    HANDLE opener = CreateFile(Path, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    SYSTEMTIME s_time;
    if (opener != INVALID_HANDLE_VALUE) {
        FILETIME creationTime, accsessTime, writeTime;
        if (GetFileTime(opener, &creationTime, &accsessTime, &writeTime)) {
            if (FileTimeToSystemTime(&creationTime, &s_time)) cout << s_time.wYear << '-' << s_time.wMonth << '-' << s_time.wDay
                                                                   << ' ' << s_time.wDayOfWeek << ' ' << s_time.wHour << ':'
                                                                   << s_time.wMinute << ':' << s_time.wSecond << ':' << s_time.wMilliseconds << '\n';
            if (FileTimeToSystemTime(&accsessTime, &s_time)) cout << s_time.wYear << '-' << s_time.wMonth << '-' << s_time.wDay
                                                                   << ' ' << s_time.wDayOfWeek << ' ' << s_time.wHour << ':'
                                                                   << s_time.wMinute << ':' << s_time.wSecond << ':' << s_time.wMilliseconds << '\n';
            if (FileTimeToSystemTime(&writeTime, &s_time)) cout << s_time.wYear << '-' << s_time.wMonth << '-' << s_time.wDay
                                                                   << ' ' << s_time.wDayOfWeek << ' ' << s_time.wHour << ':'
                                                                   << s_time.wMinute << ':' << s_time.wSecond << ':' << s_time.wMilliseconds << '\n';
        }
        else
            std::cout << "Error occurred while getting time info. Error code: "
                      << GetLastError() << '\n';
        CloseHandle(opener);
    }
    else
        std::cout << "Error occurred while opening the file. Error code: "
                  << GetLastError() << '\n';
}

void setFileTime(const CHAR *Path){
    HANDLE opener = CreateFile(Path, GENERIC_WRITE | GENERIC_READ,
                               FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
    if (opener != INVALID_HANDLE_VALUE) {
        SYSTEMTIME s_time;
        GetSystemTime(&s_time);
        FILETIME creationTime, accessTime, writeTime;
        if (SystemTimeToFileTime(&s_time, &creationTime) &&
            SystemTimeToFileTime(&s_time, &accessTime) &&
            SystemTimeToFileTime(&s_time, &writeTime)) {
            if (SetFileTime(opener, &creationTime, &accessTime, &writeTime)) {
                cout << "New file time succesfully set\n";
                if (GetFileTime(opener, &creationTime, &accessTime, &writeTime)) {
                    if (FileTimeToSystemTime(&creationTime, &s_time)) cout << s_time.wYear << '-' << s_time.wMonth << '-' << s_time.wDay
                                                                           << ' ' << s_time.wDayOfWeek << ' ' << s_time.wHour << ':'
                                                                           << s_time.wMinute << ':' << s_time.wSecond << ':' << s_time.wMilliseconds << '\n';
                    if (FileTimeToSystemTime(&accessTime, &s_time)) cout << s_time.wYear << '-' << s_time.wMonth << '-' << s_time.wDay
                                                                          << ' ' << s_time.wDayOfWeek << ' ' << s_time.wHour << ':'
                                                                          << s_time.wMinute << ':' << s_time.wSecond << ':' << s_time.wMilliseconds << '\n';
                    if (FileTimeToSystemTime(&writeTime, &s_time)) cout << s_time.wYear << '-' << s_time.wMonth << '-' << s_time.wDay
                                                                        << ' ' << s_time.wDayOfWeek << ' ' << s_time.wHour << ':'
                                                                        << s_time.wMinute << ':' << s_time.wSecond << ':' << s_time.wMilliseconds << '\n';
                }
                else
                    std::cout << "Error occurred while getting time info. Error code: "
                              << GetLastError() << '\n';
            }
            else
                std::cout << "Error occurred while setting time info. Error code: "
                          << GetLastError() << '\n';
        }
        else
            std::cout << "Error occurred while converting time info. Error code: "
                      << GetLastError() << '\n';
        CloseHandle(opener);
    }
    else
        std::cout << "Error occurred while opening the file. Error code: "
                  << GetLastError() << '\n';
}
void ui(){
    char choice;
    do{
        choice = input(main_menu);
        switch (choice)
        {
            case '1':
            {
                do
                {
                    choice = input(drive_menu);
                    switch (choice)
                    {
                        case '1':
                        {
                            cout << "Using GetLogicalDrives..." << endl;
                            getDisks();
                            cout << "--------------------------------------------------------" << endl
                                 << "Using GetLogicalDriveStrings..." << endl;
                            getDisksWithString();
                            system("pause");
                            break;
                        }
                        case '2':
                        {
                            cout << "Enter the letter of the drive" << endl;
                            char drive[MAX_PATH];
                            cin.getline(drive,MAX_PATH);
                            typeDisk(strcat(drive,":\\"));
                            volumeDrive(drive);
                            freeSpaceDrive(drive);
                            system("pause");
                            break;
                        }
                        case '0':
                        {
                            break;
                        }
                        default:
                        {
                            cout << "There is no such paragraph!" << endl;
                            system("pause");
                            break;
                        }
                    }
                } while (choice != '0');
                choice = ' ';
                break;
            }
            case '2':
            {
                do{
                    choice = input(dir_menu);
                    switch (choice)
                    {
                        case '1':
                        {
                            cout << "Enter the path where need to create the directory" << endl;
                            char path[MAX_PATH];
                            cin.getline(path, MAX_PATH);
                            createDIR(path);
                            system("pause");
                            break;
                        }
                        case '2':
                        {
                            cout << "Enter the path which directory should be deleted" << endl;
                            char path[MAX_PATH];
                            cin.getline(path, MAX_PATH);
                            rmDIR(path);
                            system("pause");
                            break;
                        }
                        case '0':
                        {
                            break;
                        }
                        default:
                        {
                            cout << "There is no such paragraph!" << endl;
                            system("pause");
                            break;
                        }
                    }
                }while (choice != '0');
                choice = ' ';
                break;
            }
            case '3':
            {
                do{
                    choice = input(file_menu);
                    switch (choice)
                    {
                        case '1':
                        {
                            cout << "Enter the path where need to create the file" << endl;
                            char path[MAX_PATH];
                            cin.getline(path, MAX_PATH);
                            createFile(path);
                            system("pause");
                            break;
                        }
                        case '2':
                        {
                            cout << "Enter the path of the file which need to be moved" << endl;
                            char oldpath [MAX_PATH], newpath [MAX_PATH];
                            cin.getline(oldpath, MAX_PATH);
                            cout << "Enter the path where file need to be moved" << endl;
                            cin.getline(newpath, MAX_PATH);
                            if (!move(oldpath,newpath)) moveEX(oldpath,newpath);
                            system("pause");
                            break;
                        }
                        case '3':
                        {
                            cout << "Enter the path of the file which need to be copied" << endl;
                            char oldpath [MAX_PATH], newpath [MAX_PATH];
                            cin.getline(oldpath, MAX_PATH);
                            cout << "Enter the path where file need to be copied" << endl;
                            cin.getline(newpath, MAX_PATH);
                            copy(oldpath,newpath);
                            system("pause");
                            break;
                        }
                        case '4':
                        {
                            do{
                                choice = input(file_attributes_menu);
                                switch (choice)
                                {
                                    case '1':
                                    {
                                        cout << "Enter the path of the file witch attributes you want to be shown" << endl;
                                        char path[MAX_PATH];
                                        cin.getline(path, MAX_PATH);
                                        workWithAttributes(path);
                                        system("pause");
                                        break;
                                    }
                                    case '2':
                                    {
                                        cout << "Enter the path of the file witch time attributes you want to be shown" << endl;
                                        char path[MAX_PATH];
                                        cin.getline(path, MAX_PATH);
                                        getFileTime(path);
                                        system("pause");
                                        break;
                                    }
                                    case '3':
                                    {
                                        cout << "Enter the path of the file witch attributes by handle you want to be shown" << endl;
                                        char path[MAX_PATH];
                                        cin.getline(path, MAX_PATH);
                                        getAttrsByHandle(path);
                                        system("pause");
                                        break;
                                    }
                                    case '4':
                                    {
                                        do{
                                            choice = input(list_of_attrs);
                                            switch (choice)
                                            {
                                                case '1':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_ARCHIVE);
                                                    system("pause");
                                                    break;
                                                }
                                                case '2':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_HIDDEN);
                                                    system("pause");
                                                    break;
                                                }
                                                case '3':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_NORMAL);
                                                    system("pause");
                                                    break;
                                                }
                                                case '4':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_NOT_CONTENT_INDEXED);
                                                    system("pause");
                                                    break;
                                                }
                                                case '5':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_OFFLINE);
                                                    system("pause");
                                                    break;
                                                }
                                                case '6':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_READONLY);
                                                    system("pause");
                                                    break;
                                                }
                                                case '7':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_SYSTEM);
                                                    system("pause");
                                                    break;
                                                }
                                                case '8':
                                                {
                                                    cout << "Enter the path of the file for setting up the selected attribute" << endl;
                                                    char path[MAX_PATH];
                                                    cin.getline(path, MAX_PATH);
                                                    setAttributes(path, FILE_ATTRIBUTE_TEMPORARY);
                                                    system("pause");
                                                    break;
                                                }
                                                case '0':
                                                {
                                                    break;
                                                }
                                                default:
                                                {
                                                    cout << "There is no such paragraph!" << endl;
                                                    system("pause");
                                                    break;
                                                }
                                            }
                                        }while (choice != '0');
                                        choice = ' ';
                                        break;
                                    }
                                    case '5':
                                    {
                                        cout << "Enter the path of the file for setting up new file time attribute" << endl;
                                        char path[MAX_PATH];
                                        cin.getline(path, MAX_PATH);
                                        setFileTime(path);
                                        system("pause");
                                        break;
                                    }
                                    case '0':
                                    {
                                        break;
                                    }
                                    default:
                                    {
                                        cout << "There is no such paragraph!" << endl;
                                        system("pause");
                                        break;
                                    }
                                }
                            }while (choice != '0');
                        }
                        case '0':
                        {
                            break;
                        }
                        default:
                        {
                            cout << "There is no such paragraph!" << endl;
                            system("pause");
                            break;
                        }
                    }
                } while (choice != '0');
                choice = ' ';
                break;
            }
            case '0':
            {
                break;
            }
            default:
            {
                cout << "There is no such paragraph!" << endl;
                system("pause");
                break;
            }
        }
    } while (choice != '0');
}
int main()
{
    ui();
    return 0;
}

