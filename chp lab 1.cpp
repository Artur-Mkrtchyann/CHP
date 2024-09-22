#include <iostream>

using namespace std;

int gcd(int a, int b) {

    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }

    return (a < 0) ? -a : a;
}

int bazmapatik(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {

    int a, b;

    cout << "Enter two numbers: ";
    cin >> a >> b;

    int res = bazmapatik(a, b);
    int result = gcd(a, b);
    cout<< "bajanarar:"<< result<<endl;

    cout << "bazmapatik: " << res;

    return 0;
}