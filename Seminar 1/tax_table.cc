#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    cout << "INPUT PART" << endl;
    cout << setfill('=') << setw(10) << "" << endl;
    
    float first_price{}, last_price{}, stride{}, tax_percent{};

    cout << "Enter first price: ";
    cin >> first_price;
    while (first_price < 0) {
        cerr << "First price must be atleast 0 (zero) SEK" << endl;
        cout << "Enter first price: ";
        cin >> first_price;
    }

    cout << "Enter last price : ";
    cin >> last_price;
    while (last_price <= first_price) {
        cerr << "Last price must be greater than first price" << endl;
        cout << "Enter last price: ";
        cin >> last_price;
    }

    cout << "Enter stride     : ";
    cin >> stride;
    while (stride < 0.01) {
        cerr << "Stride must be atleast 0.01" << endl;
        cout << "Enter stride     : ";
        cin >> stride;
    }

    cout << "Enter tax percent: ";
    cin >> tax_percent;
    while (tax_percent <= 0 || tax_percent > 100) {
        cerr << "Tax percent must be within (0, 100]" << endl;
        cout << "Enter tax percent: ";
        cin >> tax_percent;
    }
    tax_percent /= 100;

    cout << "TAX TABLE" << endl;
    cout << setfill('=') << setw(9) << "" << endl;
    cout << setfill(' ') << setw(20) << "Price" << setw(20) << "Tax" << setw(20) << "Price with tax" << endl;
    cout << setfill('-') << setw(60) << "" << endl << setfill(' ');

    for (float price{first_price}; price <= last_price; price +=stride)
    {
        float tax = tax_percent * price;
        float price_with_tax = price + tax;
        cout << showpoint << fixed << setprecision(2) << setw(20) << price << setw(20) << tax << setw(20) << price_with_tax << endl;
    }
}
