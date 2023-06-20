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
        type = "Файл";
        int floatValue = fs::file_size(entry) / 1024;
        size = std::to_string(floatValue) + " KB";
    }
    else if (fs::is_directory(entry)) {
        type = "Папка";
    }

    std::time_t modification_time = to_time_t(fs::last_write_time(entry));
    std::cout << std::left << std::setw(45) << filename;
    std::cout << std::setw(15) << type;
    std::cout << std::setw(15) << size;
    std::cout << std::setw(25) << std::asctime(std::localtime(&modification_time));
 //   std::cout << std::endl;
}

void displayFileTable(const std::string& path) {
    std::cout << std::left << std::setw(45) << "Ім'я файлу";
    std::cout << std::setw(15) << "Тип об'єкта";
    std::cout << std::setw(15) << "Розмір";
    std::cout << std::setw(25) << "Дата зміни";
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

    std::cout << std::left << std::setw(25) << "Ім'я файлу";
    std::cout << std::setw(15) << "Тип об'єкта";
    std::cout << std::setw(15) << "Розмір";
    std::cout << std::setw(25) << "Дата зміни";
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
    std::cout << "Введіть назву стовпця: Ім'я файлу\n";

    //std::cin >> input;
    std::cout << "Оберіть тип сортування (“d” - за спаданням, “a” - за зростанням): d\n";
    // std::cin >> input;
    std::cout << "Відсортовано за спаданням за стовпцем Ім'я файлу: \n\n";
    displayFileTableA("F:\\Other\\Lessons");

}
void Search() {

    std::string input;
    std::cout << "Введіть назву/частину назви папки або файлу: ПР_\n";

    //std::cin >> input;
    // std::cin >> input;
    std::cout << "Знайдені файли і папки: \n\n";

   


    displayFileTableA("F:\\Other\\Lessons");
    std::cout << std::endl;

}

void NewFolder() {
    std::cout << "Введіть назву нової папки: Test_folder\n";
    std::cout << "Папка створена.\n";
  //  std::cout << "Список файлів і директорій на у директорії Other_Documents: \n";
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
    std::cout << "Об'єкти скопійовано до буферу обміну.\n";
}
void ShowBuffer() {
    std::cout << "\nПоточний вміст буферу обміну: \n";
    if (FilesBuffer.size() == 0) {
        std::cout << "-Елементів немає \n\n";
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
    std::cout << "\nМеню вибірки: \n";
    std::cout << "1. Додати об’єкт" << std::endl;
    std::cout << "2. Прибрати об’єкт" << std::endl;
    std::cout << "3. Очистити вибірку" << std::endl;
    std::cout << "4. Відобразити вміст списку" << std::endl;
    std::cout << "5. Повернутися" << std::endl;
    while (true)
    {
        std::cout << "Оберіть пункт меню: ";
         std::getline(std::cin, ch);
        //std::cin >> choice;
         choice = ch[0];
        // if( )
        switch (choice)
        {
        case '1': {
           // std::getline(std::cin, obj_name);
            std::cout << "Введіть назву файлу/папки в поточній директорії: ";
            std::getline(std::cin, obj_name);
            obj_name = working_directory + obj_name;
            //std::cout << "obj_name: " << obj_name << "\n";
            if (D_pathExists(obj_name)) {
                FileList.push_back(obj_name);
                std::cout << "Об'єкт додано. \n";
            }
            else {
                std::cout << "Об'єкту не існує! \n";
            }
            // pathExists()
            break;

        }
        case '2': {
            int inx;
            char inx1;
            std::string inx2;
            std::cout << "\nПоточний вміст вибірки: \n";
            if (FileList.size() == 0) {
                std::cout << "-Елементів немає \n\n";
                break;
            }
            for (int i = 0; i < FileList.size(); i++) {
                std::cout << i + 1 << ". " << FileList[i] << " \n";
            }
            std::cout << "Введіть номер об'єкту зі списку який хочете видалити: ";
            //std::cin >> inx;
            std::getline(std::cin, inx2);
            inx1 = inx2[0];
            inx = static_cast<int>(inx1 - '0');
            if (inx < 0 || inx > FileList.size()) {
                std::cout << "Невірний номер елементу!\n";
                break;
            }
            FileList.erase(FileList.begin() + inx-1);
          // int ind = std::find(nums.begin(), nums.end(), value_to_find);
            std::cout << "Елемент видалено. \n";
            break;
            
        }
        case '3': {
            FileList.clear();
            std::cout << "Вибірку очищено. \n";
            break;
        }
        
        case '4':
        {
            std::cout << "\nПоточний вміст вибірки: \n";
            if (FileList.size() == 0) {
                std::cout << "-Елементів немає \n\n";
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

            std::cout << "Невірний пункт!\n";

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
        std::cout << "Видалено успішна.\n";
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
        std::cout << "Вирізано успішно.\n";
    }
    else {
        std::cout << "Вставка успішна.\n";
    }
}

void Paste() {
    int choice;
    std::cout << "Впевнені що хочете вставити усі файли з вибірки до поточної директорії? 1 - так  2 - ні: ";
    std::cin >> choice;
    std::cout << "\n";
    if (choice == 1) {
        copyFilesAndDirectories(FileList, working_directory);

    }
}
void Remove() {
    int choice;
    std::cout << "Впевнені що хочете видалити усі файли з вибірки? 1 - так  2 - ні: ";
    std::cin >> choice;
    std::cout << "\n";
    if (choice == 1) {
        removeFilesAndDirectories(FileList);

    }
}
void Copy() {
    int choice;
    std::string path;
    /*std::cout << "Оберіть метод яким необхідно задати шлях призначення:\n";
    std::cout << "1. Ввести шлях вручну\n";
    std::cout << "2. Вибрати шлях використовуючи інтерфейс програми\n";*/
    std::cout << "Файли скопійовано. ";
    while (true)
    {

        //  std::getline(std::cin, obj_name);
       // std::cin >> choice;
        // if( )
        //std::getline(std::cin, path);
        //switch (choice)
        //{
        //case 1: {

        //    std::cout << "Введіть шлях : ";
        //    std::getline(std::cin, path);
        //    //  path = working_directory + path;
        //    if (pathExists(path)) {
        //        copyFilesAndDirectories(FileList, "D:\\Other\\test1");
        //    }
        //    else {
        //        std::cout << "\nНе існує! \n";
        //    }
        //    break;

        //}
        //case 4:
        //{
        //    std::cout << "\nПоточний вміст вибірки: \n";
        //    for (int i = 0; i < FileList.size(); i++) {
        //        std::cout << i << ". " << FileList[i] << " \n";
        //    }
        //    break;
        //}
        //default: {
        //    std::cout << "Невірний пункт! ";
        //    // std::cin >> choice;
        //    continue;
        //    break; }
        //}
    }
    /*std::cout << "Введіть пункт меню: 1\n";
    std::cout << "Введіть шлях призначення:  D:\\Other_Documents\\WebDesign\\\n";
    std::cout << "Скопійовано 2 файли зі списку вибірки.\n";
    std::cout << "\nСписок файлів і директорій у директорії D:\\Other_Documents\\WebDesign\\: \n";
    displayFileTable("F:\\Other\\Lessons\\WebDesign");
    std::cout << "Відобразити вміст попередньої директорії [Натисніть ENTER]\n\n\n";*/
}


void Menu2() {
    std::cout << "\nМеню керування: \n";
    std::cout << "1. Переміститися до іншої папки" << std::endl;
    std::cout << "2. Переміститися до папки рівнем вище (назад)" << std::endl;
    std::cout << "3. Задати робочий шлях" << std::endl;
    std::cout << "4. Відсортувати за стовпцем (обрати стовпець)" << std::endl;
    std::cout << "5. Знайти файл (пошук по імені)" << std::endl;
    std::cout << "6. Додати папку" << std::endl;
    std::cout << "7. Створити файл" << std::endl;
    std::cout << "8. Відобразити/редагувати список вибірки" << std::endl;
    std::cout << "9.  Переглянути буфер обміну" << std::endl;
    std::cout << "10. Копіювати (вибірка)" << std::endl;
    std::cout << "11. Вирізати(з вибірки до буфера обміну)" << std::endl;
    std::cout << "12. Вставити (вибірка)" << std::endl;
    std::cout << "13. Видалити  (вибірка)" << std::endl;
   


}

void Menu1() {
   /* std::cout << "\nМеню керування: \n";
    std::cout << "1. Переміститися до іншої папки" << std::endl;
    std::cout << "2. Переміститися до папки рівнем вище (назад)" << std::endl;
    std::cout << "3. Задати робочий шлях" << std::endl;
    std::cout << "4. Відсортувати за стовпцем (обрати стовпець)" << std::endl;
    std::cout << "5. Знайти файл (пошук по імені)" << std::endl;
    std::cout << "6. Додати папку" << std::endl;
    std::cout << "7. Створити файл" << std::endl;
    std::cout << "8. Відобразити/редагувати список вибірки" << std::endl;
    std::cout << "9.  Переглянути буфер обміну" << std::endl;
    std::cout << "10. Копіювати (вибірка)" << std::endl;
    std::cout << "11. Вирізати(з вибірки до буфера обміну)" << std::endl;
    std::cout << "12. Вставити (вибірка)" << std::endl;
    std::cout << "13. Видалити  (вибірка)" << std::endl;*/
    int tabs = 50;
    std::cout << "\nМеню керування: \n";
    std::cout << std::left << std::setw(tabs) << "1. Переміститися до іншої папки";
    std::cout << "7. Відобразити/редагувати список вибірки\n";
    std::cout << std::left << std::setw(tabs) << "2. Переміститися до папки рівнем вище (назад)";
    std::cout << "8.  Переглянути буфер обміну\n";

    std::cout << std::left << std::setw(tabs) << "3. Задати робочий шлях";
    std::cout << "9. Копіювати (вибірка)\n";
    std::cout << std::left << std::setw(tabs) << "4. Знайти файл (пошук по імені)";
    std::cout << "10. Вирізати(з вибірки до буфера обміну)\n";

    std::cout << std::left << std::setw(tabs) << "5. Додати папку";
    std::cout << "11. Вставити (вибірка)\n";
    std::cout << std::left << std::setw(tabs) << "6. Створити файл";
    std::cout << "12. Видалити  (вибірка)\n";

    
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
    std::cout << "Список логічних дисків на компьютері: \n";
    std::vector<char> drivesList = listLogicalDrives();
    //while(true) {}
    while (true) {
        std::cout << "Введіть букву диску щоб перейти до нього: \n";
        std::getline(std::cin, driveLetter_str);
        if (driveLetter_str.length() != 1) {
            std::cout << "Введено невірну букву диску, оберіть диск зі списку!" << std::endl;
            continue;
        }
        
        driveLetter = driveLetter_str[0];
        std::vector<char>::iterator result = std::find(drivesList.begin(), drivesList.end(), driveLetter);

        if (result != drivesList.end()) {
            return driveLetter;
        }
        else {
            std::cout << "Введено невірну букву диску, оберіть диск зі списку!" << std::endl;
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
    std::cout << std::left << std::setw(25) << "Ім'я файлу";
    std::cout << std::setw(15) << "Тип об'єкта";
    std::cout << std::setw(15) << "Розмір";
    std::cout << std::endl;

    std::cout << std::setfill('-') << std::setw(60) << "-" << std::endl;
    std::cout << std::setfill(' ');

    for (const auto& entry : fs::directory_iterator(path)) {
        std::string name = entry.path().filename().string();
        if (name.find(substring) != std::string::npos) {
            std::cout << std::left << std::setw(25) << name;

            if (fs::is_regular_file(entry)) {
                std::cout << std::setw(15) << "Файл";
                std::cout << std::setw(15) << fs::file_size(entry);
            }
            else if (fs::is_directory(entry)) {
                std::cout << std::setw(15) << "Папка";
                std::cout << std::setw(15) << "N/A";
            }

            std::cout << std::endl;
        }
    }
}

void SearchMenu() {
    std::string Fname;
    while (true) {
        std::cout << "Введіть ім'я файлу/папки який треба знайти:  " ;
        std::getline(std::cin, Fname);
        if (Fname.size()) {
            std::cout << "\nЗнайдені файли і папки:  " << std::endl;
            SearchFolderAndFile(working_directory, Fname);
            break;
        }
        else {
            std::cout << "Введіть вірну назву файлу/папки!" << std::endl;
        }
        
        
        
    }
    //std::cout << "Введіть ім'я файлу/папки який треба знайти:  \n" << std::endl;
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

    
    std::cout << "1. Назва файлу: " << find_file_data.cFileName << std::endl;

  
    std::string file_type = "";
    SHFILEINFO shFileInfo;
    if (SHGetFileInfo(path.c_str(), 0, &shFileInfo, sizeof(SHFILEINFO),
        SHGFI_TYPENAME)) {
        file_type = shFileInfo.szTypeName;
    }
    std::cout << "2. Тип файлу: " << file_type << std::endl;

    std::cout << "3. Розміщення: " << getParentDirectory(path) << std::endl;

    ULARGE_INTEGER size;
    size.LowPart = find_file_data.nFileSizeLow;
    size.HighPart = find_file_data.nFileSizeHigh;

    std::cout << "4. Розмір: " << size.QuadPart << " байт" << std::endl;

    FILETIME creation_time = find_file_data.ftCreationTime;
    SYSTEMTIME system_creation_time;
    FileTimeToSystemTime(&creation_time, &system_creation_time);

    std::cout << "5. Дата створення: " << system_creation_time.wDay << "/"
        << system_creation_time.wMonth << "/"
        << system_creation_time.wYear << " "
        << system_creation_time.wHour+2 << ":"
        << system_creation_time.wMinute << std::endl;

    FILETIME last_modified = find_file_data.ftLastWriteTime;
    SYSTEMTIME system_last_modified;
    FileTimeToSystemTime(&last_modified, &system_last_modified);

    std::cout << "6. Дата зміни: " << system_last_modified.wDay << "/"
        << system_last_modified.wMonth << "/"
        << system_last_modified.wYear << " "
        << system_last_modified.wHour+2 << ":"
        << system_last_modified.wMinute << std::endl;

    std::filesystem::path file_path(path);
    std::cout << "7. Розширення: " << file_path.extension().string() << "\n";
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
        std::cerr << "Невірний шлях до папки!" << std::endl;
        return;
    }

   
    std::cout << "1. Назва папки: " << find_folder_data.cFileName << std::endl;

    std::cout << "2. Розміщення: " << path << std::endl;

    unsigned long long folder_size = getFolderSize(path);
   // std::cout << "3. Розмір: " << folder_size << " байт" << std::endl;

    FILETIME creation_time = find_folder_data.ftCreationTime;
    SYSTEMTIME system_creation_time;
    FileTimeToSystemTime(&creation_time, &system_creation_time);

    std::cout << "3. Дата створення: " << system_creation_time.wDay << "/"
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
        std::cout << "немає доступних атрибутів для зчитування" << std::endl;
    }
    std::cout << std::endl;
}

void ObjectMenu(std::string obj_name) {
    //std::cout << "\nМеню керування: \n";
    std::string Fpath = working_directory + obj_name;
    std::cout << std::endl;
    
    //  ObjectMenu();

    char choice;
    
    int obj_type = IsFolderOrFile(Fpath);
    bool exit = false;
    while (true) {
        if (IsFolderOrFile(Fpath) == 2) {
            std::cout << "\nФайл: " << obj_name << std::endl;
        }
        else {
            std::cout << "Папка: " << obj_name << std::endl;
        }
        std::cout << "1. Переглянути інформацію/властивості" << std::endl;
       
        std::cout << "2. Редагувати атрибути" << std::endl;
     //   std::cout << "3. Копіювати повний шлях" << std::endl;
        std::cout << "3. Перейменувати" << std::endl;
      //  std::cout << "5. Видалити " << std::endl;

        std::cout << "4. Відкрити за допомогою програми визначеної за замовчуванням системою ->" << std::endl;
        std::cout << "5. Повернутися\n" << std::endl;
        std::cout << "Оберіть пункт меню: ";
        //  std::getline(std::cin, obj_name);
        std::cin >> choice;
        if (choice >= '0' && choice <= '9') {
            int choice_int = choice - '0';
            switch (choice_int) {
            case 1: {
                if (obj_type == 2) {
                    std::cout << "\nВластивості файлу " << obj_name << ": \n";
                    File_Properties(Fpath);
                }
                else {
                    std::cout << "\nВластивості папки " << obj_name << ": \n";
                    Dir_Properties(Fpath);
                }
                std::cout << " \n";
                system("pause");
                std::cout << " \n";
                break;
            }
            case 2: {
                std::cout << "\nРедагування атрибутів: \n";
                std::cout << "1. Переглянути атрибути" << std::endl;
                std::cout << "2. Додати атрибут" << std::endl;
                std::cout << "3. Видалити атрибут" << std::endl;
                std::cout << "4. Повернутися" << std::endl;
                std::cout << "Введіть пункт: ";
                char choice2;
                std::cin >> choice2;
                int choice_int2 = choice2 - '0';
                if (choice2 == '1') {
                    std::cout << "\nАтрибути для об'єкту " << obj_name << ": \n";
                    ShowAttr(Fpath);
                    /*char cont;
                    std::cout << "Продовжити роботу [Натисніть ENTER]";
                    std::cin >> cont;*/
                    system("pause");
                    std::cout << "\n";
                    break;
                }
                else if (choice2 == '3' || choice2 == '2') {
                    char InputAtr;
                    std::cout << "Введіть букву атрибуту: ";
                    std::cin >> InputAtr;
                    /*std::string cont;
                    std::getline(std::cin, cont);*/
                    if (!(InputAtr == 'A' || InputAtr == 'H' || InputAtr == 'R' || InputAtr == 'S')) {
                        std::cout << "Невірне значення атрибуту!\n";
                        std::string cont;
                        system("pause");
                        /*std::cout << "Продовжити роботу [Натисніть ENTER]";
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
                        std::cerr << "Невдалося задати атрибут!" << std::endl;

                    }
                    //  std::cout << "attrib2\n";
                    std::cout << "Атрибути задано успішно!\n\n";
                    system("pause");
                    std::cout << "\n";
                }
                else if (choice2 != '4') {
                    std::cout << "Невірний пункт!\n\n";
                }



                //ShowAttr(Fpath);
                break;
            }
            case 3: {
                std::string New_name;
                std::cout << "Введіть нове ім'я файлу: ";
                std::getline(std::cin, New_name);
                std::getline(std::cin, New_name);
                if (!hasInvalidChars(New_name)) {
                    std::string New_path = working_directory + New_name;
                   // std::cout << "Path: " << New_path << std::endl;

                    if (std::rename(Fpath.c_str(), New_path.c_str()) == 0) {
                        std::cout << "Об'єкт перейменовано успішно.\n" << std::endl;
                        system("pause");
                        std::cout << std::endl;
                        ObjectMenu(New_name);
                        return;
                    }
                    else {
                        std::cout << "Невдалося перейменувати об'єкт." << std::endl;
                    }
                }
                else {
                    std::cout << "Некорректне ім'я файлу/папки!\n" << std::endl;
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
                std::cout << "\nВідкриття...\n\n";
                std::cout << "\nПродовжити роботу [Натисніть ENTER]";

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
                std::cout << "Невірний пункт! \n\n";
                //system("pause");
                break;
            }
            
            }
        }
        else {
            std::cout << "Невірний пункт! \n\n";
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
    std::cout << "Програма \"Файловий менеджер\" \n" << std::endl;
    std::cout << "Для того щоб розпочати роботу з програмою, оберіть метод яким хочете задати початковий робочий шлях: \n";
    std::cout << "1. Ввести шлях вручну\n";
    std::cout << "2. Вибрати шлях використовуючи інтерфейс програми\n";
    while (true) {
        std::cout << "Введіть пункт меню: ";
        // std::cin >> pathChoice;
        std::getline(std::cin, pathChoice_str);
        if (pathChoice_str.length() == 1) {
            if (pathChoice_str[0] == '1') {
                while (true) {
                    std::cout << "Введіть шлях до директорії, в якій хочете працювати: ";

                    std::getline(std::cin, input);
                    if (IsFolderOrFile(input) == 1) {
                        working_directory = input;
                        break;
                    }
                    else {
                        std::cout << "Невірний шлях! \n";
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
                std::cout << "Невірний пункт! \n";
            }
        }
        else {
            std::cout << "Невірний пункт! \n";
        }
    }
  //  std::getline(std::cin, input);
        /*std::cout << "Список логічних дисків на компьютері: \n";
       
        std::vector<char> drivesList = listLogicalDrives();
        std::string path1 = "C:\\MAMP\\bin\\";*/


    /////////////
       
        
        /*std::cout << "Введіть букву диску щоб перейти до нього: \n";
        std::cin >> driveLetter;

        std::vector<char>::iterator result = std::find(drivesList.begin(), drivesList.end(), driveLetter);
        working_directory = driveLetter;
        working_directory += ":\\";
        
        if (result != drivesList.end()) {
            
            std::getline(std::cin, cont);
          
            std::cout << "Список файлів і директорій на диску (" << driveLetter << ":) : \n";
          
        }
        else {
            std::cout << "Введено невірну букву диску, оберіть диск зі списку!" << std::endl;
        }*/
            while (true)
            {

               // std::cout << "\nСписок файлів і папок у директорії " << working_directory << " :\n";
                displayFileTable(working_directory);
                std::cout << "\nПоточне розташування: " << working_directory << "\n";
                Menu1();
                std::cout << "Введіть команду для файлового менеджера: ";
                std::getline(std::cin, input);
              //  std::getline(std::cin, input);

                if (input.substr(0, 2) == ".\\") {

                    std::string f_path = working_directory + input.substr(2);
                    ///std::cout << "path: " << f_path << std::endl;
                    if (pathExists(f_path))
                    {
                        std::cout << "Перехід до папки .\\" << input.substr(2) << "." << std::endl;
                        working_directory += input.substr(2) + "\\";
                    }
                    else
                    {
                        std::cout << "Такої директорії не знайдено!" << std::endl;
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
                    std::cout << "Введіть назву папки в яку треба перейти: ";
                    
                    std::getline(std::cin, Fnew);
                    std::string f_path = working_directory + Fnew;
                    if (pathExists(f_path) && Fnew.length())
                    {
                        std::cout << "Перехід до папки .\\" << Fnew << "." << std::endl;
                        working_directory += Fnew + "\\";
                    }
                    else
                    {
                        std::cout << "Такої директорії не знайдено!" << std::endl;
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
                        std::cout << "Введіть шлях до директорії, в яку хочете перейти: ";

                        std::getline(std::cin, New_p);
                        if (IsFolderOrFile(New_p) == 1) {
                            working_directory = New_p;
                            break;
                        }
                        else {
                            std::cout << "Невірний шлях! \n";
                        }
                    }
                }
                else if (input == "4") {
                    SearchMenu();
                }
                else if (input == "5") {
                    std::string Fname;
                    while (true) {
                        std::cout << "Введіть назву папки яку треба створити: ";
                        std::getline(std::cin, Fname);
                        if (Fname.size() && !hasInvalidChars(Fname)) {
                            if (createFolder(working_directory, Fname)) {
                                std::cout << "Папка " << Fname << " успішно створена. \n";
                                break;
                            }
                            else {
                                std::cout << "Виникла помилка при створенні папки! \n";
                                break;
                            }
                        }
                        else {
                            std::cout << "Введіть корректну назву папки! \n";
                        }
                    }

                    //   SearchMenu();
                }
                else if (input == "6") {
                    std::string Fname;
                    while (true) {
                        std::cout << "Введіть назву файлу який треба створити: ";
                        std::getline(std::cin, Fname);
                        if (Fname.size() && !hasInvalidChars(Fname)) {
                            if (Create_File(working_directory, Fname)) {
                                std::cout << "Файл " << Fname << " успішно створений. \n";
                                break;
                            }
                            else {
                                std::cout << "Виникла помилка при створенні файлу! \n";
                                break;
                            }
                        }
                        else {
                            std::cout << "Введіть корректну назву файлу! \n";
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
                    std::cout << "Ви впевнені, що бажаєте видалити усі файли які є у вибірці? Y/N : ";
                    std::cin >> choice;
                    if (choice == 'Y') {
                        removeFilesAndDirectories(FileList);
                    }
                    else {
                        std::cout << "Видалення відмінено. \n";
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
                        std::cout << "Команда не знайдена." << std::endl;
                        
                    }

                    
                    
                }
                //std::cout << "команда: " << input << "\n";
              //  std::cout << "  Workdir:" << working_directory << "\n";
                std::cout << "\nПродовжити роботу, оновити список файлів і директорій [Натисніть ENTER]";
               
                
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

