#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class Zadanie {
    public:
        int r;//czas przygotowania
        int p;//czas na maszynie
        int q;//czas stygniecia
};
istream& operator>> (istream& wejscie, Zadanie& zad){
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
                Zadanie TabZadan[LiczbaZadan];
                dane >> TabZadan[index]; //wgranie danych do tablicy struktur
                cout << TabZadan[index]; //wyswietlenie danych
                index++;
            }
        }   
        myfile.close();
    }else cout << "Unable to open file"; 
    

  return 0;
}