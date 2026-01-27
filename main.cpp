#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    cout << "Hello, World!" << std::endl;
    FILE *datei = fopen("test.txt", "r");

    return 0;
}