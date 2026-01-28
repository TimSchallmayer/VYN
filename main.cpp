#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    fstream datei ("test_groesser.txt", ios::binary | ios::in | ios::out);

    if (datei.bad()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    streampos begin, end;
    begin = datei.tellg();
    datei.seekg(0, ios::end);
    end = datei.tellg();
    cout << "Size in bytes: " << (end - begin) << endl;
    datei.seekp(12000000, ios::end);
    datei.put('.');
    datei.seekg(0, ios::end);
    end = datei.tellg();
    cout << "New Size in bytes: " << (end - begin) << endl;
    datei.close();
    return 0;
}