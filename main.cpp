#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace filesystem;
using namespace chrono;

void createFile(const string& filename, const string& content) {
    string fullFilename = filename;
    if (filename.substr(filename.find_last_of(".") + 1) != "txt") {
        fullFilename += ".txt";
    }
    ofstream file(fullFilename);
    if (file) {
        file << content << endl;
        cout << "File created and content written successfully: " << fullFilename << endl;
    } else {
        cerr << "Failed to create file: " << fullFilename << endl;
    }
}

void deleteFile(const string& filename) {
    if (remove(filename)) {
        cout << "File deleted successfully: " << filename << endl;
    } else {
        cerr << "Failed to delete file: " << filename << endl;
    }
}

void readFile(const string& filename) {
    ifstream file(filename);
    if (file) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cerr << "Failed to read file: " << filename << endl;
    }
}

void listFiles(const string& directory) {
    try {
        for (const auto& entry : directory_iterator(directory)) {
            auto path = entry.path();
            auto fileSize = file_size(path);
            auto lastWriteTime = last_write_time(path);
            auto sctp = time_point_cast<system_clock::duration>(lastWriteTime - file_time_type::clock::now() + system_clock::now());
            auto cftime = system_clock::to_time_t(sctp);

            cout << "File Information:" << endl;
            cout << "a. Name: " << path.filename() << endl;
            cout << "b. Size: " << fileSize << " bytes" << endl;
            cout << "c. Location: " << absolute(path) << endl;
            cout << "d. Last Modified: " << put_time(localtime(&cftime), "%F %T") << endl;
            cout << "e. Type: " << (path.extension() == ".txt" ? "Text file" : "Other file") << endl;
            cout << "-----------------------" << endl;
        }
    } catch (const exception& ex) {
        cerr << "Error listing files: " << ex.what() << endl;
    }
}

void copyFile(const string& srcFilename, const string& destFilename) {
    try {
        copy(srcFilename, destFilename);
        cout << "File copied successfully: " << srcFilename << " to " << destFilename << endl;
    } catch (const exception& ex) {
        cerr << "Failed to copy file: " << ex.what() << endl;
    }
}

void renameFile(const string& oldFilename, const string& newFilename) {
    try {
        rename(oldFilename, newFilename);
        cout << "File renamed successfully: " << oldFilename << " to " << newFilename << endl;
    } catch (const exception& ex) {
        cerr << "Failed to rename file: " << ex.what() << endl;
    }
}

void displayMenu() {
    cout << "Please choose a job to perform:" << endl;
    cout << "1. Create a file" << endl;
    cout << "2. Read a file" << endl;
    cout << "3. List all files in the directory" << endl;
    cout << "4. Delete a file" << endl;
    cout << "5. Copy a file" << endl;
    cout << "6. Rename a file" << endl;
    cout << "Enter your choice: ";
}

int main() {
    int choice;
    string filename, content, srcFilename, destFilename, oldFilename, newFilename;
    const string directory = "."; // Current directory

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the name of the file to create: ";
                cin >> filename;
                cin.ignore(); // Ignore leftover newline
                cout << "Enter the content of the file: ";
                getline(cin, content);
                createFile(filename, content);
                break;
            case 2:
                cout << "Enter the name of the file to read: ";
                cin >> filename;
                readFile(filename);
                break;
            case 3:
                cout << "Listing all files in the directory:" << endl;
                listFiles(directory);
                break;
            case 4:
                cout << "Enter the name of the file to delete: ";
                cin >> filename;
                deleteFile(filename);
                break;
            case 5:
                cout << "Enter the name of the source file to copy: ";
                cin >> srcFilename;
                cout << "Enter the name of the destination file: ";
                cin >> destFilename;
                copyFile(srcFilename, destFilename);
                break;
            case 6:
                cout << "Enter the current name of the file to rename: ";
                cin >> oldFilename;
                cout << "Enter the new name of the file: ";
                cin >> newFilename;
                renameFile(oldFilename, newFilename);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}
