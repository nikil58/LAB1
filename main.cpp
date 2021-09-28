#include <iostream>
#include <windows.h>


using namespace std;

void getDisks(){
    int counter = 0;
    DWORD myDrivesBitMask = GetLogicalDrives();
    if (myDrivesBitMask == 0) cout << "Can't read the disk list";
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
    DWORD dwResult = GetLogicalDriveStrings(diskLengthBuffer, diskLengthStringBuffer);

    if (dwResult > 0 && dwResult <= MAX_PATH)
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
            cout << Drive <<" Unknown type of Drive";
            break;
        case 2:
            cout << Drive <<" No such Drive mounted";
            break;
        case 3:
            cout << Drive <<" This drive is removable";
            break;
        case 4:
            cout << Drive << " This drive is fixed";
            break;
        case 5:
            cout << Drive << " This drive is remote";
            break;
        case 6:
            cout << Drive << " This drive is CD ROM";
            break;
        case 7:
            cout << Drive << " This drive is RAMDISK";
            break;
    }
}

void volumeDrive(const CHAR *Drive){
    char NameBuffer[MAX_PATH];
    char SysNameBuffer[MAX_PATH];
    DWORD VSNumber;
    DWORD MCLength;
    DWORD FileSF;

    if (GetVolumeInformation(Drive,NameBuffer, sizeof(NameBuffer),
                             &VSNumber,&MCLength,&FileSF,SysNameBuffer,sizeof(SysNameBuffer)))
    {
        cout <<  NameBuffer << endl;
        cout <<  SysNameBuffer << endl;
        cout <<  VSNumber << endl;
    }
}

void freeSpaceDrive(const CHAR *Drive){
    BOOLEAN bSuccess;

    DWORD dwSectorsPerCluster;
    DWORD dwBytesPerSector;
    DWORD dwFreeClusters;
    DWORD dwTotalClusters;

    //get disk space for current drive
    bSuccess = GetDiskFreeSpace(
            Drive, //current drive
            &dwSectorsPerCluster, //sectors per cluster
            &dwBytesPerSector, //bytes per sector
            &dwFreeClusters, //free clusters
            &dwTotalClusters //total clusters
    );

    if(!bSuccess){
        printf("Could not get drive information.\n");
        exit(EXIT_FAILURE);
    }

    printf("Bytes per sector: %d\n", dwBytesPerSector);
    printf("Sectors per cluster: %d\n", dwSectorsPerCluster);
    printf("Free clusters: %d\n", dwFreeClusters);
    printf("Total clusters: %d\n", dwTotalClusters);

    unsigned int uiKBPerCluster = dwBytesPerSector * dwSectorsPerCluster / 1024;

    printf("You have %.2f MB of free storage\n", (double) uiKBPerCluster * dwFreeClusters / 1024);
    printf("You have %.2f MB of total storage\n", (double) uiKBPerCluster * dwTotalClusters / 1024);
}

int main()
{
    cout << "Using GetLogicalDrives..." << endl;
   getDisks();
   cout << "--------------------------------------------------------"<<endl<<"Using GetLogicalDriveStrings..."<<endl;
   getDisksWithString();
   typeDisk("E:\\");
   volumeDrive("C:\\");
    freeSpaceDrive("C:\\");
}
