
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using namespace std;

// Function to display directory contents
void displayDirectoryContents(const string& path) {
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << entry.path().filename() << endl;
    }
}

// Function to check if a file exists
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// Function to copy a file
void copyFile(const string& source, const string& destination) {
    fs::copy_file(source, destination, fs::copy_options::overwrite_existing);
}

// Function to move a file
void moveFile(const string& source, const string& destination) {
    fs::rename(source, destination);
}

int main() {
    string currentDirectory = fs::current_path().string();

    while (true) {
        cout << "Current Directory: " << currentDirectory << endl;
        cout << "Commands: \n";
        cout << "1. List directory contents\n";
        cout << "2. Create directory\n";
        cout << "3. View file\n";
        cout << "4. Copy file\n";
        cout << "5. Move file\n";
        cout << "6. Change directory\n";
        cout << "7. Exit\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // List directory contents
                displayDirectoryContents(currentDirectory);
                break;

            case 2: // Create directory
                {
                    string dirName;
                    cout << "Enter directory name: ";
                    cin >> dirName;
                    fs::create_directory(currentDirectory + "/" + dirName);
                    cout << "Directory created.\n";
                }
                break;

            case 3: // View file
                {
                    string filename;
                    cout << "Enter file name: ";
                    cin >> filename;
                    if (fileExists(currentDirectory + "/" + filename)) {
                        ifstream file(currentDirectory + "/" + filename);
                        cout << file.rdbuf();
                        file.close();
                    } else {
                        cout << "File not found.\n";
                    }
                }
                break;

            case 4: // Copy file
                {
                    string source, destination;
                    cout << "Enter source file name: ";
                    cin >> source;
                    cout << "Enter destination file name: ";
                    cin >> destination;
                    copyFile(currentDirectory + "/" + source, currentDirectory + "/" + destination);
                    cout << "File copied.\n";
                }
                break;

            case 5: // Move file
                {
                    string source, destination;
                    cout << "Enter source file name: ";
                    cin >> source;
                    cout << "Enter destination file name: ";
                    cin >> destination;
                    moveFile(currentDirectory + "/" + source, currentDirectory + "/" + destination);
                    cout << "File moved.\n";
                }
                break;

            case 6: // Change directory
                {
                    string newDir;
                    cout << "Enter directory name: ";
                    cin >> newDir;
                    if (fs::is_directory(currentDirectory + "/" + newDir)) {
                        currentDirectory += "/" + newDir;
                    } else {
                        cout << "Directory not found.\n";
                    }
                }
                break;

            case 7: // Exit
                cout << "Exiting program.\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
