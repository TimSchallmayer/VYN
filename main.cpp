#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    fstream datei ("main.exe", ios::binary | ios::in);

    if (datei.bad()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }
    streampos begin, end;
    begin = datei.tellg();
    datei.seekg(0, ios::end);
    end = datei.tellg();
    datei.close();
    cout << "Size in bytes: " << (end - begin) << endl;
    return 0;
}