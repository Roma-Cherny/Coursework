#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <string> 
#include <sys/stat.h>
#include <stdio.h>

#include <time.h>
#include <limits.h>

namespace fs = std::filesystem;
std::string working_directory;


template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
        + system_clock::now());
    return system_clock::to_time_t(sctp);
}


/////////




////////////

void displayFileInfo(const fs::directory_entry& entry) {
    std::error_code ec;
    fs::file_status fileStatus = fs::status(entry, ec);

    if (ec) {
        
        return;
    }

    std::string filename = entry.path().filename().string();
    std::string type;
    std::string size = "N/A";

    if (fs::is_regular_file(entry)) {
        type = "����";
        int floatValue = fs::file_size(entry) / 1024;
        size = std::to_string(floatValue) + " KB";
    }
    else if (fs::is_directory(entry)) {
        type = "�����";
    }

    std::time_t modification_time = to_time_t(fs::last_write_time(entry));
    std::cout << std::left << std::setw(45) << filename;
    std::cout << std::setw(15) << type;
    std::cout << std::setw(15) << size;
    std::cout << std::setw(25) << std::asctime(std::localtime(&modification_time));
 //   std::cout << std::endl;
}

void displayFileTable(const std::string& path) {
    std::cout << std::left << std::setw(45) << "��'� �����";
    std::cout << std::setw(15) << "��� ��'����";
    std::cout << std::setw(15) << "�����";
    std::cout << std::setw(25) << "���� ����";
    std::cout << std::endl;

    std::cout << std::setfill('-') << std::setw(100) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (const auto& entry : fs::directory_iterator(path)) {
        displayFileInfo(entry);
    }
}

void displayFileTableA(const std::string& path) {
    std::vector<fs::directory_entry> entries;


    for (const auto& entry : fs::directory_iterator(path)) {
        entries.push_back(entry);
    }

    
    std::sort(entries.begin(), entries.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
        return a.path().filename().string() > b.path().filename().string();
        });

    std::cout << std::left << std::setw(25) << "��'� �����";
    std::cout << std::setw(15) << "��� ��'����";
    std::cout << std::setw(15) << "�����";
    std::cout << std::setw(25) << "���� ����";
    std::cout << std::endl;

    std::cout << std::setfill('-') << std::setw(80) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (const auto& entry : entries) {
        displayFileInfo(entry);
    }
}
std::vector<fs::path> list_directory(fs::path path)
{
    std::vector<fs::path> entries;
    for (const auto& entry : fs::directory_iterator(path))
    {
        entries.push_back(entry.path());
    }
    return entries;
}

void display_entries(const std::vector<fs::path>& entries)
{
    int index = 1;
    for (const auto& entry : entries)
    {
        std::cout << index << ". " << entry.filename().string() << std::endl;
        index++;
    }
}

void Sotrting() {

    std::string input;
    std::cout << "������ ����� �������: ��'� �����\n";

    //std::cin >> input;
    std::cout << "������ ��� ���������� (�d� - �� ���������, �a� - �� ����������): d\n";
    // std::cin >> input;
    std::cout << "³���������� �� ��������� �� �������� ��'� �����: \n\n";
    displayFileTableA("F:\\Other\\Lessons");

}
void Search() {

    std::string input;
    std::cout << "������ �����/������� ����� ����� ��� �����: ��_\n";

    //std::cin >> input;
    // std::cin >> input;
    std::cout << "������� ����� � �����: \n\n";

   


    displayFileTableA("F:\\Other\\Lessons");
    std::cout << std::endl;

}

void NewFolder() {
    std::cout << "������ ����� ���� �����: Test_folder\n";
    std::cout << "����� ��������.\n";
  //  std::cout << "������ ����� � ��������� �� � �������� Other_Documents: \n";
    displayFileTableA("F:\\Other\\Lessons");
}
std::vector < std::string> FileList, FilesBuffer;
bool previous_buffer_action = 0;
bool D_pathExists(const std::string& path) {
    DWORD attributes = GetFileAttributesA(path.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES);
}


void CopyToBuffer() {
    FilesBuffer.clear();
    for (int i = 0; i < FileList.size(); i++) {
        FilesBuffer.push_back(FileList[i]);
    }
    std::cout << "��'���� ���������� �� ������ �����.\n";
}
void ShowBuffer() {
    std::cout << "\n�������� ���� ������ �����: \n";
    if (FilesBuffer.size() == 0) {
        std::cout << "-�������� ���� \n\n";
        return;
    }
    for (int i = 0; i < FilesBuffer.size(); i++) {
        std::cout << i + 1 << ". " << FilesBuffer[i] << " \n";
    }
    
    
   
   
}
void Vibirka() {
    char choice;
    
    std::string obj_name, ch;
    bool exit = false;
    std::cout << "\n���� ������: \n";
    std::cout << "1. ������ �ᒺ��" << std::endl;
    std::cout << "2. �������� �ᒺ��" << std::endl;
    std::cout << "3. �������� ������" << std::endl;
    std::cout << "4. ³��������� ���� ������" << std::endl;
    std::cout << "5. �����������" << std::endl;
    while (true)
    {
        std::cout << "������ ����� ����: ";
         std::getline(std::cin, ch);
        //std::cin >> choice;
         choice = ch[0];
        // if( )
        switch (choice)
        {
        case '1': {
           // std::getline(std::cin, obj_name);
            std::cout << "������ ����� �����/����� � ������� ��������: ";
            std::getline(std::cin, obj_name);
            obj_name = working_directory + obj_name;
            //std::cout << "obj_name: " << obj_name << "\n";
            if (D_pathExists(obj_name)) {
                FileList.push_back(obj_name);
                std::cout << "��'��� ������. \n";
            }
            else {
                std::cout << "��'���� �� ����! \n";
            }
            // pathExists()
            break;

        }
        case '2': {
            int inx;
            char inx1;
            std::string inx2;
            std::cout << "\n�������� ���� ������: \n";
            if (FileList.size() == 0) {
                std::cout << "-�������� ���� \n\n";
                break;
            }
            for (int i = 0; i < FileList.size(); i++) {
                std::cout << i + 1 << ". " << FileList[i] << " \n";
            }
            std::cout << "������ ����� ��'���� � ������ ���� ������ ��������: ";
            //std::cin >> inx;
            std::getline(std::cin, inx2);
            inx1 = inx2[0];
            inx = static_cast<int>(inx1 - '0');
            if (inx < 0 || inx > FileList.size()) {
                std::cout << "������� ����� ��������!\n";
                break;
            }
            FileList.erase(FileList.begin() + inx-1);
          // int ind = std::find(nums.begin(), nums.end(), value_to_find);
            std::cout << "������� ��������. \n";
            break;
            
        }
        case '3': {
            FileList.clear();
            std::cout << "������ �������. \n";
            break;
        }
        
        case '4':
        {
            std::cout << "\n�������� ���� ������: \n";
            if (FileList.size() == 0) {
                std::cout << "-�������� ���� \n\n";
                break;
            }
            for (int i = 0; i < FileList.size(); i++) {
                std::cout << i+1 << ". " << FileList[i] << " \n";
            }
            break;
        }
        case '5': {
            exit = true;
            break;
        }
        default: {

            std::cout << "������� �����!\n";

            // std::cin >> choice;
            
            break; }
        }
        if (exit == true) {
            break;
        }
    }



  
}


int IsFolderOrFile(const std::string& path)
{
    DWORD attributes = GetFileAttributes(path.c_str());

    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        return 0; 
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return 1; 
    }

    return 2; 
}

bool pathExists(const std::string& path)
{
    DWORD attributes = GetFileAttributes(path.c_str());

    if (attributes == INVALID_FILE_ATTRIBUTES)
    {
        return false; 
    }

    if (attributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        return true; 
    }

    return false; 
}
void removeFilesAndDirectories(const std::vector<std::string>& fileList) {
    try {
        
        for (const auto& path : fileList) {
            std::filesystem::path targetPath = path;
            std::filesystem::remove_all(targetPath);
        }
        std::cout << "�������� ������.\n";
    }
    catch (std::filesystem::filesystem_error & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
void copyFilesAndDirectories(const std::vector<std::string>& fileList, const std::string& targetFolderPath) {
    
    try {
      
        std::filesystem::create_directory(targetFolderPath);

      
        for (const auto& path : fileList) {
            std::filesystem::path srcPath = path;
            std::filesystem::path dstPath = targetFolderPath / srcPath.filename();
            std::filesystem::copy(srcPath, dstPath, std::filesystem::copy_options::recursive);
          //  std::cout << "copy ok\n";
        }
        
    }
    catch (std::filesystem::filesystem_error & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    if (previous_buffer_action == 1) {
        removeFilesAndDirectories(FileList);
        FileList.clear();
        FilesBuffer.clear();
        std::cout << "������� ������.\n";
    }
    else {
        std::cout << "������� ������.\n";
    }
}

void Paste() {
    int choice;
    std::cout << "������� �� ������ �������� �� ����� � ������ �� ������� ��������? 1 - ���  2 - �: ";
    std::cin >> choice;
    std::cout << "\n";
    if (choice == 1) {
        copyFilesAndDirectories(FileList, working_directory);

    }
}
void Remove() {
    int choice;
    std::cout << "������� �� ������ �������� �� ����� � ������? 1 - ���  2 - �: ";
    std::cin >> choice;
    std::cout << "\n";
    if (choice == 1) {
        removeFilesAndDirectories(FileList);

    }
}
void Copy() {
    int choice;
    std::string path;
    /*std::cout << "������ ����� ���� ��������� ������ ���� �����������:\n";
    std::cout << "1. ������ ���� ������\n";
    std::cout << "2. ������� ���� �������������� ��������� ��������\n";*/
    std::cout << "����� ����������. ";
    while (true)
    {

        //  std::getline(std::cin, obj_name);
       // std::cin >> choice;
        // if( )
        //std::getline(std::cin, path);
        //switch (choice)
        //{
        //case 1: {

        //    std::cout << "������ ���� : ";
        //    std::getline(std::cin, path);
        //    //  path = working_directory + path;
        //    if (pathExists(path)) {
        //        copyFilesAndDirectories(FileList, "D:\\Other\\test1");
        //    }
        //    else {
        //        std::cout << "\n�� ����! \n";
        //    }
        //    break;

        //}
        //case 4:
        //{
        //    std::cout << "\n�������� ���� ������: \n";
        //    for (int i = 0; i < FileList.size(); i++) {
        //        std::cout << i << ". " << FileList[i] << " \n";
        //    }
        //    break;
        //}
        //default: {
        //    std::cout << "������� �����! ";
        //    // std::cin >> choice;
        //    continue;
        //    break; }
        //}
    }
    /*std::cout << "������ ����� ����: 1\n";
    std::cout << "������ ���� �����������:  D:\\Other_Documents\\WebDesign\\\n";
    std::cout << "���������� 2 ����� � ������ ������.\n";
    std::cout << "\n������ ����� � ��������� � �������� D:\\Other_Documents\\WebDesign\\: \n";
    displayFileTable("F:\\Other\\Lessons\\WebDesign");
    std::cout << "³��������� ���� ���������� �������� [�������� ENTER]\n\n\n";*/
}


void Menu2() {
    std::cout << "\n���� ���������: \n";
    std::cout << "1. ������������ �� ���� �����" << std::endl;
    std::cout << "2. ������������ �� ����� ����� ���� (�����)" << std::endl;
    std::cout << "3. ������ ������� ����" << std::endl;
    std::cout << "4. ³���������� �� �������� (������ ��������)" << std::endl;
    std::cout << "5. ������ ���� (����� �� ����)" << std::endl;
    std::cout << "6. ������ �����" << std::endl;
    std::cout << "7. �������� ����" << std::endl;
    std::cout << "8. ³���������/���������� ������ ������" << std::endl;
    std::cout << "9.  ����������� ����� �����" << std::endl;
    std::cout << "10. �������� (������)" << std::endl;
    std::cout << "11. �������(� ������ �� ������ �����)" << std::endl;
    std::cout << "12. �������� (������)" << std::endl;
    std::cout << "13. ��������  (������)" << std::endl;
   


}

void Menu1() {
   /* std::cout << "\n���� ���������: \n";
    std::cout << "1. ������������ �� ���� �����" << std::endl;
    std::cout << "2. ������������ �� ����� ����� ���� (�����)" << std::endl;
    std::cout << "3. ������ ������� ����" << std::endl;
    std::cout << "4. ³���������� �� �������� (������ ��������)" << std::endl;
    std::cout << "5. ������ ���� (����� �� ����)" << std::endl;
    std::cout << "6. ������ �����" << std::endl;
    std::cout << "7. �������� ����" << std::endl;
    std::cout << "8. ³���������/���������� ������ ������" << std::endl;
    std::cout << "9.  ����������� ����� �����" << std::endl;
    std::cout << "10. �������� (������)" << std::endl;
    std::cout << "11. �������(� ������ �� ������ �����)" << std::endl;
    std::cout << "12. �������� (������)" << std::endl;
    std::cout << "13. ��������  (������)" << std::endl;*/
    int tabs = 50;
    std::cout << "\n���� ���������: \n";
    std::cout << std::left << std::setw(tabs) << "1. ������������ �� ���� �����";
    std::cout << "7. ³���������/���������� ������ ������\n";
    std::cout << std::left << std::setw(tabs) << "2. ������������ �� ����� ����� ���� (�����)";
    std::cout << "8.  ����������� ����� �����\n";

    std::cout << std::left << std::setw(tabs) << "3. ������ ������� ����";
    std::cout << "9. �������� (������)\n";
    std::cout << std::left << std::setw(tabs) << "4. ������ ���� (����� �� ����)";
    std::cout << "10. �������(� ������ �� ������ �����)\n";

    std::cout << std::left << std::setw(tabs) << "5. ������ �����";
    std::cout << "11. �������� (������)\n";
    std::cout << std::left << std::setw(tabs) << "6. �������� ����";
    std::cout << "12. ��������  (������)\n";

    
   // std::cout << std::setw(15) << size;

}


std::vector<char> listLogicalDrives()
{
    DWORD dwDrives = GetLogicalDrives();
    std::vector<char> drivesList;
    std::string driveLetters = "";
    for (int i = 0; i < 26; ++i)
    {
        if (dwDrives & (1 << i)) //!
        {
            char driveLetter = 'A' + i;
            driveLetters += driveLetter;
            driveLetters += ":\\";
            drivesList.push_back(driveLetter);

            char volumeName[MAX_PATH] = "";
            GetVolumeInformationA(driveLetters.c_str(), volumeName, MAX_PATH, nullptr, nullptr, nullptr, nullptr, 0);

            std::cout << "" << driveLetter << ":\\" << " - " << volumeName << std::endl;
            // std::cout << "dr: " << driveLetters << "\n";
            driveLetters.clear();
        }
    }
    // std::cout << "len: " << drivesList.size() << "\n";
    for (int i = 0; i < drivesList.size(); i++) {
        //  std::cout << "Drive: " << drivesList[i] << "\n";
    }
    return drivesList;

}



std::string getParentDirectory(const std::string& path) {
  




    std::size_t lastBackslash = path.find_last_of('\\', path.length() - 2);


    if (lastBackslash != std::string::npos) {
        return path.substr(0, lastBackslash + 1);
    }

    
    return "no-parent";

}


char DiskSelectMenu() {
    char  driveLetter;
    std::string driveLetter_str;
    std::cout << "������ ������� ����� �� ���������: \n";
    std::vector<char> drivesList = listLogicalDrives();
    //while(true) {}
    while (true) {
        std::cout << "������ ����� ����� ��� ������� �� �����: \n";
        std::getline(std::cin, driveLetter_str);
        if (driveLetter_str.length() != 1) {
            std::cout << "������� ������ ����� �����, ������ ���� � ������!" << std::endl;
            continue;
        }
        
        driveLetter = driveLetter_str[0];
        std::vector<char>::iterator result = std::find(drivesList.begin(), drivesList.end(), driveLetter);

        if (result != drivesList.end()) {
            return driveLetter;
        }
        else {
            std::cout << "������� ������ ����� �����, ������ ���� � ������!" << std::endl;
        }
    }
}

struct FileInfo {
    std::string filename;
    std::string type;
    std::string size;
    std::time_t modification_time;
};

FileInfo getFileInfo(const fs::directory_entry& entry) {
    std::error_code ec;
    fs::file_status fileStatus = fs::status(entry, ec);

    if (ec) {
        
        return FileInfo();
    }

    FileInfo fileInfo;
    fileInfo.filename = entry.path().filename().string();

    if (fs::is_regular_file(entry)) {
        fileInfo.type = "File";
        int floatValue = fs::file_size(entry);
        fileInfo.size = std::to_string(floatValue);
    }
    else if (fs::is_directory(entry)) {
        fileInfo.type = "Folder";
        fileInfo.size = "N/A";
    }

    fileInfo.modification_time = to_time_t(fs::last_write_time(entry));
    return fileInfo;
}

void selectionSort(std::vector<FileInfo>& files, int column, bool ascending) {
    int n = files.size();

    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i;

        for (int j = i + 1; j < n; ++j) {
            bool condition = false;
            switch (column) {
            case 0: 
                condition = files[j].filename < files[minIdx].filename;
                break;
            case 1: 
                condition = files[j].type < files[minIdx].type;
                break;
            case 2: 
                condition = files[j].size < files[minIdx].size;
                break;
            case 3: 
                condition = files[j].modification_time < files[minIdx].modification_time;
                break;
            }
            if (ascending ? condition : !condition) {
                minIdx = j;
            }
        }

        if (minIdx != i) {
            std::swap(files[i], files[minIdx]);
        }
    }
}




void SearchFolderAndFile(const std::string& path, const std::string& substring) {
    std::cout << std::left << std::setw(25) << "��'� �����";
    std::cout << std::setw(15) << "��� ��'����";
    std::cout << std::setw(15) << "�����";
    std::cout << std::endl;

    std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (const auto& entry : fs::directory_iterator(path)) {
        std::string name = entry.path().filename().string();
        if (name.find(substring) != std::string::npos) {
            std::cout << std::left << std::setw(25) << name;

            if (fs::is_regular_file(entry)) {
                std::cout << std::setw(15) << "����";
                std::cout << std::setw(15) << fs::file_size(entry);
            }
            else if (fs::is_directory(entry)) {
                std::cout << std::setw(15) << "�����";
                std::cout << std::setw(15) << "N/A";
            }

            std::cout << std::endl;
        }
    }
}

void SearchMenu() {
    std::string Fname;
    while (true) {
        std::cout << "������ ��'� �����/����� ���� ����� ������:  " ;
        std::getline(std::cin, Fname);
        if (Fname.size()) {
            std::cout << "\n������� ����� � �����:  " << std::endl;
            SearchFolderAndFile(working_directory, Fname);
            break;
        }
        else {
            std::cout << "������ ���� ����� �����/�����!" << std::endl;
        }
        
        
        
    }
    //std::cout << "������ ��'� �����/����� ���� ����� ������:  \n" << std::endl;
    //system("pause");
}
bool Create_File(const std::string folder, const std::string filename) {
    
    std::string filepath = folder + "/" + filename;

  
    std::ofstream file(filepath);

    
    if (!file.is_open()) {
        
        return false;
    }

    
    file.close();

    return true;
}
bool hasInvalidChars(const std::string& folderName)
{
    
    const std::string invalidChars = "<>:\"/\\|?*";

    for (char c : folderName)
    {
        if (invalidChars.find(c) != std::string::npos)
        {
            return true;  
        }
    }

    return false;  
}
bool createFolder(std::string directory, std::string folderName)
{
    std::filesystem::path folderPath = directory;
   // folderPath +="\\";
    folderPath += folderName;


  
    return std::filesystem::create_directory(folderPath);
}


void File_Properties(std::string path) {
    WIN32_FIND_DATA find_file_data;
    HANDLE first_file = FindFirstFile(path.c_str(), &find_file_data);

   
    if (first_file == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: Invalid file path" << std::endl;
        return;
    }

    
    std::cout << "1. ����� �����: " << find_file_data.cFileName << std::endl;

  
    std::string file_type = "";
    SHFILEINFO shFileInfo;
    if (SHGetFileInfo(path.c_str(), 0, &shFileInfo, sizeof(SHFILEINFO),
        SHGFI_TYPENAME)) {
        file_type = shFileInfo.szTypeName;
    }
    std::cout << "2. ��� �����: " << file_type << std::endl;

    std::cout << "3. ���������: " << getParentDirectory(path) << std::endl;

    ULARGE_INTEGER size;
    size.LowPart = find_file_data.nFileSizeLow;
    size.HighPart = find_file_data.nFileSizeHigh;

    std::cout << "4. �����: " << size.QuadPart << " ����" << std::endl;

    FILETIME creation_time = find_file_data.ftCreationTime;
    SYSTEMTIME system_creation_time;
    FileTimeToSystemTime(&creation_time, &system_creation_time);

    std::cout << "5. ���� ���������: " << system_creation_time.wDay << "/"
        << system_creation_time.wMonth << "/"
        << system_creation_time.wYear << " "
        << system_creation_time.wHour+2 << ":"
        << system_creation_time.wMinute << std::endl;

    FILETIME last_modified = find_file_data.ftLastWriteTime;
    SYSTEMTIME system_last_modified;
    FileTimeToSystemTime(&last_modified, &system_last_modified);

    std::cout << "6. ���� ����: " << system_last_modified.wDay << "/"
        << system_last_modified.wMonth << "/"
        << system_last_modified.wYear << " "
        << system_last_modified.wHour+2 << ":"
        << system_last_modified.wMinute << std::endl;

    std::filesystem::path file_path(path);
    std::cout << "7. ����������: " << file_path.extension().string() << "\n";
}



unsigned long long getFolderSize(const std::string& folder_path) {
    unsigned long long folder_size = 0;
    WIN32_FIND_DATA find_file_data;
    std::string search_path = folder_path + "\\*";
    HANDLE search_handle = FindFirstFile(search_path.c_str(), &find_file_data);

    if (search_handle != INVALID_HANDLE_VALUE) {
        do {
            if (!(find_file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                ULARGE_INTEGER file_size;
                file_size.LowPart = find_file_data.nFileSizeLow;
                file_size.HighPart = find_file_data.nFileSizeHigh;

                folder_size += file_size.QuadPart;
            }
        } while (FindNextFile(search_handle, &find_file_data));
        FindClose(search_handle);
    }

    return folder_size;
}

void Dir_Properties(const std::string& path) {
    WIN32_FIND_DATA find_folder_data;
    HANDLE first_folder = FindFirstFile(path.c_str(), &find_folder_data);

    
    if (first_folder == INVALID_HANDLE_VALUE) {
        std::cerr << "������� ���� �� �����!" << std::endl;
        return;
    }

   
    std::cout << "1. ����� �����: " << find_folder_data.cFileName << std::endl;

    std::cout << "2. ���������: " << path << std::endl;

    unsigned long long folder_size = getFolderSize(path);
   // std::cout << "3. �����: " << folder_size << " ����" << std::endl;

    FILETIME creation_time = find_folder_data.ftCreationTime;
    SYSTEMTIME system_creation_time;
    FileTimeToSystemTime(&creation_time, &system_creation_time);

    std::cout << "3. ���� ���������: " << system_creation_time.wDay << "/"
        << system_creation_time.wMonth << "/"
        << system_creation_time.wYear << " "
        << system_creation_time.wHour+2 << ":"
        << system_creation_time.wMinute << std::endl;
}

void ShowAttr(const std::string& Fpath) {
    DWORD fileAttributes = GetFileAttributes(Fpath.c_str());


    
    bool attributes_found = false;
    if (fileAttributes & FILE_ATTRIBUTE_ARCHIVE) {
        std::cout << "- A ";
        attributes_found = true;
    }
   
    if (fileAttributes & FILE_ATTRIBUTE_HIDDEN) {
        std::cout << "- H ";
        attributes_found = true;
    }
    if (fileAttributes & FILE_ATTRIBUTE_READONLY) {
        std::cout << "- R ";
        attributes_found = true;
    }
   
    if (fileAttributes & FILE_ATTRIBUTE_SYSTEM) {
        std::cout << "- S ";
        attributes_found = true;
    }
    if (!attributes_found) {
        std::cout << "���� ��������� �������� ��� ����������" << std::endl;
    }
    std::cout << std::endl;
}

void ObjectMenu(std::string obj_name) {
    //std::cout << "\n���� ���������: \n";
    std::string Fpath = working_directory + obj_name;
    std::cout << std::endl;
    
    //  ObjectMenu();

    char choice;
    
    int obj_type = IsFolderOrFile(Fpath);
    bool exit = false;
    while (true) {
        if (IsFolderOrFile(Fpath) == 2) {
            std::cout << "\n����: " << obj_name << std::endl;
        }
        else {
            std::cout << "�����: " << obj_name << std::endl;
        }
        std::cout << "1. ����������� ����������/����������" << std::endl;
       
        std::cout << "2. ���������� ��������" << std::endl;
     //   std::cout << "3. �������� ������ ����" << std::endl;
        std::cout << "3. �������������" << std::endl;
      //  std::cout << "5. �������� " << std::endl;

        std::cout << "4. ³������ �� ��������� �������� ��������� �� ������������� �������� ->" << std::endl;
        std::cout << "5. �����������\n" << std::endl;
        std::cout << "������ ����� ����: ";
        //  std::getline(std::cin, obj_name);
        std::cin >> choice;
        if (choice >= '0' && choice <= '9') {
            int choice_int = choice - '0';
            switch (choice_int) {
            case 1: {
                if (obj_type == 2) {
                    std::cout << "\n���������� ����� " << obj_name << ": \n";
                    File_Properties(Fpath);
                }
                else {
                    std::cout << "\n���������� ����� " << obj_name << ": \n";
                    Dir_Properties(Fpath);
                }
                std::cout << " \n";
                system("pause");
                std::cout << " \n";
                break;
            }
            case 2: {
                std::cout << "\n����������� ��������: \n";
                std::cout << "1. ����������� ��������" << std::endl;
                std::cout << "2. ������ �������" << std::endl;
                std::cout << "3. �������� �������" << std::endl;
                std::cout << "4. �����������" << std::endl;
                std::cout << "������ �����: ";
                char choice2;
                std::cin >> choice2;
                int choice_int2 = choice2 - '0';
                if (choice2 == '1') {
                    std::cout << "\n�������� ��� ��'���� " << obj_name << ": \n";
                    ShowAttr(Fpath);
                    /*char cont;
                    std::cout << "���������� ������ [�������� ENTER]";
                    std::cin >> cont;*/
                    system("pause");
                    std::cout << "\n";
                    break;
                }
                else if (choice2 == '3' || choice2 == '2') {
                    char InputAtr;
                    std::cout << "������ ����� ��������: ";
                    std::cin >> InputAtr;
                    /*std::string cont;
                    std::getline(std::cin, cont);*/
                    if (!(InputAtr == 'A' || InputAtr == 'H' || InputAtr == 'R' || InputAtr == 'S')) {
                        std::cout << "������ �������� ��������!\n";
                        std::string cont;
                        system("pause");
                        /*std::cout << "���������� ������ [�������� ENTER]";
                        std::getline(std::cin, cont);*/
                        break;

                    }
                    // std::cout << "attrib1\n";
                    DWORD fileAttributes = GetFileAttributes(Fpath.c_str());
                    DWORD ChangeAtr;
                    switch (InputAtr) {
                    case 'S':
                        ChangeAtr = FILE_ATTRIBUTE_SYSTEM;
                        break;
                    case 'H':
                        ChangeAtr = FILE_ATTRIBUTE_HIDDEN;
                        break;
                    case 'R':
                        ChangeAtr = FILE_ATTRIBUTE_READONLY;
                        break;
                    case 'A':
                        ChangeAtr = FILE_ATTRIBUTE_ARCHIVE;
                        break;


                    }
                    if (choice2 == '2') {


                        fileAttributes |= ChangeAtr;
                    }
                    else {


                        fileAttributes &= ~ChangeAtr;
                    }
                    if (!SetFileAttributes(Fpath.c_str(), fileAttributes)) {
                        std::cerr << "��������� ������ �������!" << std::endl;

                    }
                    //  std::cout << "attrib2\n";
                    std::cout << "�������� ������ ������!\n\n";
                    system("pause");
                    std::cout << "\n";
                }
                else if (choice2 != '4') {
                    std::cout << "������� �����!\n\n";
                }



                //ShowAttr(Fpath);
                break;
            }
            case 3: {
                std::string New_name;
                std::cout << "������ ���� ��'� �����: ";
                std::getline(std::cin, New_name);
                std::getline(std::cin, New_name);
                if (!hasInvalidChars(New_name)) {
                    std::string New_path = working_directory + New_name;
                   // std::cout << "Path: " << New_path << std::endl;

                    if (std::rename(Fpath.c_str(), New_path.c_str()) == 0) {
                        std::cout << "��'��� ������������� ������.\n" << std::endl;
                        system("pause");
                        std::cout << std::endl;
                        ObjectMenu(New_name);
                        return;
                    }
                    else {
                        std::cout << "��������� ������������� ��'���." << std::endl;
                    }
                }
                else {
                    std::cout << "����������� ��'� �����/�����!\n" << std::endl;
                }
                system("pause");
                break;
                //std::getline(std::cin, cont);
            }
            case 4: {
                std::string cmd = "rundll32.exe shell32.dll,ShellExec_RunDLL ";
                cmd += '\"' + Fpath;
                cmd += '\"';
                //std::cout << "cmd: " << cmd << "\n";
                system(cmd.c_str());
                std::cout << "\n³�������...\n\n";
                std::cout << "\n���������� ������ [�������� ENTER]";

                std::string cont;
                std::getline(std::cin, cont);
             //   system("pause");

               
                break;
            }
            
            case 5: {
                exit = true;
                break;
            }
            default:
            {
                std::cout << "������� �����! \n\n";
                //system("pause");
                break;
            }
            
            }
        }
        else {
            std::cout << "������� �����! \n\n";
           // system("pause");
        }
        if (exit) {
            std::string cont;
            std::getline(std::cin, cont);
            break;
        }
    }
}
int main()
{
    
   
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");
    
    fs::path working_directory1;
    std::string input, pathChoice_str;
    char  driveLetter;
    int test = 0;
    std::string cont;
    char pathChoice = 0;
    std::cout << "�������� \"�������� ��������\" \n" << std::endl;
    std::cout << "��� ���� ��� ��������� ������ � ���������, ������ ����� ���� ������ ������ ���������� ������� ����: \n";
    std::cout << "1. ������ ���� ������\n";
    std::cout << "2. ������� ���� �������������� ��������� ��������\n";
    while (true) {
        std::cout << "������ ����� ����: ";
        // std::cin >> pathChoice;
        std::getline(std::cin, pathChoice_str);
        if (pathChoice_str.length() == 1) {
            if (pathChoice_str[0] == '1') {
                while (true) {
                    std::cout << "������ ���� �� ��������, � ��� ������ ���������: ";

                    std::getline(std::cin, input);
                    if (IsFolderOrFile(input) == 1) {
                        working_directory = input;
                        break;
                    }
                    else {
                        std::cout << "������� ����! \n";
                    }
                }
                break;
            }
            else if (pathChoice_str[0] == '2') {
                driveLetter = DiskSelectMenu();
                //       std::cout << "  Letter:" << driveLetter << "\n";
                     //  system("pause");
                working_directory = driveLetter;
                working_directory += ":\\";
                //  DiskSelectMenu();
                break;
            }
            else {
                std::cout << "������� �����! \n";
            }
        }
        else {
            std::cout << "������� �����! \n";
        }
    }
  //  std::getline(std::cin, input);
        /*std::cout << "������ ������� ����� �� ���������: \n";
       
        std::vector<char> drivesList = listLogicalDrives();
        std::string path1 = "C:\\MAMP\\bin\\";*/


    /////////////
       
        
        /*std::cout << "������ ����� ����� ��� ������� �� �����: \n";
        std::cin >> driveLetter;

        std::vector<char>::iterator result = std::find(drivesList.begin(), drivesList.end(), driveLetter);
        working_directory = driveLetter;
        working_directory += ":\\";
        
        if (result != drivesList.end()) {
            
            std::getline(std::cin, cont);
          
            std::cout << "������ ����� � ��������� �� ����� (" << driveLetter << ":) : \n";
          
        }
        else {
            std::cout << "������� ������ ����� �����, ������ ���� � ������!" << std::endl;
        }*/
            while (true)
            {

               // std::cout << "\n������ ����� � ����� � �������� " << working_directory << " :\n";
                displayFileTable(working_directory);
                std::cout << "\n������� ������������: " << working_directory << "\n";
                Menu1();
                std::cout << "������ ������� ��� ��������� ���������: ";
                std::getline(std::cin, input);
              //  std::getline(std::cin, input);

                if (input.substr(0, 2) == ".\\") {

                    std::string f_path = working_directory + input.substr(2);
                    ///std::cout << "path: " << f_path << std::endl;
                    if (pathExists(f_path))
                    {
                        std::cout << "������� �� ����� .\\" << input.substr(2) << "." << std::endl;
                        working_directory += input.substr(2) + "\\";
                    }
                    else
                    {
                        std::cout << "���� �������� �� ��������!" << std::endl;
                    }
                }
                else if (input == "..") {
                    std::string parent = getParentDirectory(working_directory);
                    //   std::cout << "Parent: " << parent << "  Workdir:" << working_directory << "\n";
                    if (parent == "no-parent") {
                        driveLetter = DiskSelectMenu();
                        //       std::cout << "  Letter:" << driveLetter << "\n";
                             //  system("pause");
                        working_directory = driveLetter;
                        working_directory += ":\\";
                        /*   std::cout << "  Exist: " << D_pathExists("D:\\Other") << "\n";
                           std::cout << "  Exist2: " << D_pathExists("D:\\Other\\math1.PNG") << "\n";
                           std::cout << "  Exist: " << D_pathExists("D:\\Other1") << "\n";
                           std::cout << "  Exist2: " << D_pathExists("D:\\Other\\math45.PNG") << "\n";*/
                    }
                    else {
                        working_directory = parent;
                    }
                    

                }
               
                else if (input == "1") {
                    std::string Fnew;
                    std::cout << "������ ����� ����� � ��� ����� �������: ";
                    
                    std::getline(std::cin, Fnew);
                    std::string f_path = working_directory + Fnew;
                    if (pathExists(f_path) && Fnew.length())
                    {
                        std::cout << "������� �� ����� .\\" << Fnew << "." << std::endl;
                        working_directory += Fnew + "\\";
                    }
                    else
                    {
                        std::cout << "���� �������� �� ��������!" << std::endl;
                    }
                }
                else if (input == "2") {
                    std::string parent = getParentDirectory(working_directory);
                    //   std::cout << "Parent: " << parent << "  Workdir:" << working_directory << "\n";
                    if (parent == "no-parent") {
                        driveLetter = DiskSelectMenu();
                        //       std::cout << "  Letter:" << driveLetter << "\n";
                             //  system("pause");
                        working_directory = driveLetter;
                        working_directory += ":\\";
                        /*   std::cout << "  Exist: " << D_pathExists("D:\\Other") << "\n";
                           std::cout << "  Exist2: " << D_pathExists("D:\\Other\\math1.PNG") << "\n";
                           std::cout << "  Exist: " << D_pathExists("D:\\Other1") << "\n";
                           std::cout << "  Exist2: " << D_pathExists("D:\\Other\\math45.PNG") << "\n";*/
                    }
                    else {
                        working_directory = parent;
                    }
                }
                else if (input == "3") {
                    std::string New_p;
                    while (true) {
                        std::cout << "������ ���� �� ��������, � ��� ������ �������: ";

                        std::getline(std::cin, New_p);
                        if (IsFolderOrFile(New_p) == 1) {
                            working_directory = New_p;
                            break;
                        }
                        else {
                            std::cout << "������� ����! \n";
                        }
                    }
                }
                else if (input == "4") {
                    SearchMenu();
                }
                else if (input == "5") {
                    std::string Fname;
                    while (true) {
                        std::cout << "������ ����� ����� ��� ����� ��������: ";
                        std::getline(std::cin, Fname);
                        if (Fname.size() && !hasInvalidChars(Fname)) {
                            if (createFolder(working_directory, Fname)) {
                                std::cout << "����� " << Fname << " ������ ��������. \n";
                                break;
                            }
                            else {
                                std::cout << "������� ������� ��� �������� �����! \n";
                                break;
                            }
                        }
                        else {
                            std::cout << "������ ��������� ����� �����! \n";
                        }
                    }

                    //   SearchMenu();
                }
                else if (input == "6") {
                    std::string Fname;
                    while (true) {
                        std::cout << "������ ����� ����� ���� ����� ��������: ";
                        std::getline(std::cin, Fname);
                        if (Fname.size() && !hasInvalidChars(Fname)) {
                            if (Create_File(working_directory, Fname)) {
                                std::cout << "���� " << Fname << " ������ ���������. \n";
                                break;
                            }
                            else {
                                std::cout << "������� ������� ��� �������� �����! \n";
                                break;
                            }
                        }
                        else {
                            std::cout << "������ ��������� ����� �����! \n";
                        }
                    }

                    //   SearchMenu();
                }
                else if (input == "7") {
                    Vibirka();
                }
                else if (input == "8") {
                    ShowBuffer();
                }
                else if (input == "9") {
                previous_buffer_action = 0;
                CopyToBuffer();
                }
                else if (input == "10") {
                previous_buffer_action = 1;
                CopyToBuffer();
                }
                else if (input == "11") {
                copyFilesAndDirectories(FilesBuffer, working_directory);
                }
                else if (input == "12") {
                    char choice;
                    std::cout << "�� �������, �� ������ �������� �� ����� �� � � ������? Y/N : ";
                    std::cin >> choice;
                    if (choice == 'Y') {
                        removeFilesAndDirectories(FileList);
                    }
                    else {
                        std::cout << "��������� �������. \n";
                    }
                }
              
                /*else if (input == "10") {
                    Paste();
                }*/
                
                else {
                    std::string Fpath = working_directory + input;
                    if (IsFolderOrFile(Fpath) && input.length() !=0 && input[0] != ' ' && input[0] != '.' && input[0] != '\\' && input[0] != '/') {
                        ObjectMenu(input);
                    }
                    else{
                        std::cout << "������� �� ��������." << std::endl;
                        
                    }

                    
                    
                }
                //std::cout << "�������: " << input << "\n";
              //  std::cout << "  Workdir:" << working_directory << "\n";
                std::cout << "\n���������� ������, ������� ������ ����� � ��������� [�������� ENTER]";
               
                
                std::getline(std::cin, cont);
               // system("pause");
                 std::cout << std::endl;
                system("cls");
               // int test2;
                
                //std:: cin >> test2;
            }
        
        system("pause");
    
    Menu1();


    return 0;
}

