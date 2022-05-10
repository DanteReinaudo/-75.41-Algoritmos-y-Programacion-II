#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    string color,plural,famoso;
    cout << "Ingrese un color:";
    getline(cin,color);
    cout << "Ingrese un sustantivo en plural:";
    getline(cin,plural);
    cout << "Ingrese el nombre de un famoso:";
    getline(cin,famoso);

    cout << "Viendo todo " << color<<endl;
    cout << plural << " son falopas"<<endl;
    cout << famoso <<" esta pegao"<<endl;
    return 0;
}
