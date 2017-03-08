#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
int iIndexZadan = 0;
struct Zadanie {
    int kolejnosc;//kolejnosc zadania
    int r;//czas przygotowania
    int p;//czas na maszynie
    int q;//czas stygniecia
};
Zadanie TabZadan[60]; //deklaracja tablicy zadan
istream& operator>> (istream& wejscie, Zadanie& zad){
    zad.kolejnosc = ++iIndexZadan;
    wejscie >> zad.r >> zad.p >> zad.q;
    return wejscie;
}
ostream& operator<< (ostream& wyjscie, const Zadanie& zad){
    cout << zad.r << " - " << zad.p << " - " << zad.q << endl; 
    return wyjscie;
}

int main(){
    int LiczbaZadan, index=0;
    bool xFirst=1;
    string line, filename;

    cout<<"Podaj nazwe pliku z danymi: ";
    cin>>filename;
    cout<<"\n";

    ifstream myfile (filename + ".in");
    if (myfile.is_open()){
        while (getline (myfile,line) ){
            istringstream dane(line);
            if (xFirst==1){
                dane >> LiczbaZadan;
                cout << "Liczba zadan: " << LiczbaZadan<<"\n";
                xFirst = 0;
            }else{
                dane >> TabZadan[index]; //wgranie danych do tablicy struktur
                cout << TabZadan[index]; //wyswietlenie danych
                index++;
            }
        }   
        myfile.close();
    }else cout << "Unable to open file"; 
    // obsluga algorytmu, czyli petle zamieniajace kolejnosc dzialan
    
    // wyswietlenie kolejnosci:
    cout << endl<<"Wyliczona kolejnosc: ";
    for (int i = 0; i<=LiczbaZadan; i++){
        cout << TabZadan[i].kolejnosc << " ";
    }
    cout << endl;
    
    return 0;
}