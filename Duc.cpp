#include <iostream>

using namespace std;

int main() {
    int i = system("ls -F CS163-Data |grep -v / | wc -l");
    cout << "hihi = " << i;
    return 0;
}
