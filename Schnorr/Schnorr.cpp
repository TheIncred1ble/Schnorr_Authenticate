#include <iostream>
#include <vector>

using namespace std;
vector<int> factors;
bool checkPrimeNumber(int n) {

    bool isPrimeNumber = true;
    // 0 и 1 не являются простыми числами 
    if (n == 0 || n == 1) {

        isPrimeNumber = false;
    }
    else {
        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                isPrimeNumber = false;
                break;
            }
        }
    }
    return isPrimeNumber;
}

vector<int> factorize(int x) {
    for (int i = 2; i <= sqrt(x); i++) {
        while (x % i == 0) {
            factors.push_back(i);
            x /= i;
        }
    }
    if (x != 1) {
        factors.push_back(x);
    }
    return factors;
}

int rand_between(const int from, const int to) {
    srand(time(NULL));
    if (to == from)
        return to;
    if (to < from)
        return rand_between(to, from);
    return from + rand() % (to - from + 1);
}

long long powabmodp(long long a, long long b, long long p)
{
    long long b2 , po, y = 1;
    if (b % 2 == 1)
    {
        b2 = b / 2;
        for (int f = 0; f < b2; f++)
        {
            po = pow(a, 2);
            po = po % p;
            y *= po;
            y = y % p;
        }
        y *= a;
        y = y % p;
    }
    else
    {
        b2 = b / 2;
        for (int f = 0; f < b2; f++)
        {
            po = pow(a, 2);
            po = po % p;
            y *= po;
            y = y % p;
        }
    }
    return y;
}

int main() {

    long long p = 0, q = 0, g = 0;
    do
    {
        cout << "Enter p: ";
        cin >> p;
        if (!checkPrimeNumber(p))
        {
            p = 0;
            cout << endl << "This is not Prime number!" << endl << endl;
        }
    } while (p == 0);
    factorize(p-1);
    q = factors[0];
    for (int i = 0; i < factors.size(); i++) {
        if (factors[i] > q)
            q = factors[i];
    }
    long long j = 1, ig = 1;
    bool og = false;
    for (int i = 1000; i < 100000; i++) 
    {
        j = pow(i, q);
        if (j == (9223372036854775808))
        {
            j = 1;
            ig = powabmodp(i, q, p);
            og = true;
        }
        if (j == 1 && !og)
        {
            g = i;
            break;
        }
        else if (ig == 1 && og)
        {
            g = i;
            break;
        }
        ig = 1;
    }
    long long w = rand_between(1, q);
    //long long w = 357; // Для примера
    long long l = q - w;
    long long y;
    y = powabmodp(g, l, p);

    cout << endl << "Public Key:" << endl << "p: " << p << endl << "q: " << q << endl << "g: " << g << endl << "y: " << y << endl << endl;
    
    long long r = rand_between(1, q);
    //long long r = 274; // Для примера 
    long long x;
    x = powabmodp(g, r, p);
    cout << "Alice sends Bob: x = " << x << endl << endl;

    long long e = rand_between(1, q);
    //long long e = 129;

    cout << "Bob sends Alice: e = " << e << endl << endl;

    long long s;
    s = w * e;
    s = s % q;
    s += r;
    s = s % q;

    cout << "Alice sends Bob: s = " << s << endl << endl;

    long long gs, ye;
    gs = powabmodp(g, s, p);
    ye = powabmodp(y, e, p);
    long long z = gs * ye;
    z = z % p;
    if (x == z)
    {
        cout << "x: " << x << endl << "z: " << z << endl << "Bob authenticates Alice!" << endl;
    }
    else
    {
        cout << "x: " << x << endl << "z: " << z << endl << "Bob does not authenticates Alice!" << endl;
    }
    return 0;
}