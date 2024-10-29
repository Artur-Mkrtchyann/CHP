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


    if ((a > 0 && b < 0) || (a < 0 && b > 0)) {
        cout << "Goyutyun chuni amenapoqr yndhanur bazmapatik" << endl;
        return 1; 
    }

    int result = gcd(a, b);
    int res = bazmapatik(a, b);

    cout << "bajanarar: " << result << endl;
    cout << "bazmapatik: " << res << endl;

    return 0;
}
