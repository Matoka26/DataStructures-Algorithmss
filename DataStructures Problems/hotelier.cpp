#include <iostream>
#include <string>
using namespace std;

int main() {
    char camera[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
    int n;
    string operatii;
    cin>>n>>operatii;

    for (int i = 0; i < n; i++) {
        if (operatii[i] == 'L') {
            int j = 0;
            while (camera[j] != '0') {
                j++;
            }
            camera[j] = '1';
        } else if (operatii[i] == 'R') {
            int j = 9;
            while (camera[j] != '0') {
                j--;
            }
            camera[j] = '1';
        } else if (operatii[i] >= '0' && operatii[i] <= '9') {
            camera[operatii[i] - '0'] = '0';
        }
    }
    for (int i = 0; i < 10; i++) {
        cout<<camera[i];
    }

    return 0;
}
