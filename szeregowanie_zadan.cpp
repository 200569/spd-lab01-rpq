#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstring>

using namespace std;

int iIndexZadan = 0;

struct Zadanie {
        int kolejnosc;//kolejnosc zadania
        int r;//czas przygotowania
        int p;//czas na maszynie
        int q;//czas stygniecia
};
Zadanie TabZadan[100]; //deklaracja tablicy zadan
int kolejnosc[100];

unsigned int max(unsigned int x, unsigned int y){ return (x<=y)?y:x; }
unsigned int min(unsigned int x, unsigned int y){ return (x<=y)?x:y; }
int cmax(Zadanie Tab[], unsigned int rozmiar){
    unsigned int i, t=0,u=0;
    for (i=0;i<rozmiar;i++){
        t=max(t,Tab[i].r)+Tab[i].p;
        u=max(u,t+Tab[i].q);
    }
    return u;
}

istream& operator>> (istream& wejscie, Zadanie& zad){
    zad.kolejnosc = ++iIndexZadan;
    wejscie >> zad.r >> zad.p >> zad.q;
    return wejscie;
}
ostream& operator<< (ostream& wyjscie, const Zadanie& zad){
    cout << zad.r << " - " << zad.p << " - " << zad.q << endl; 
    return wyjscie;
}
// 1-r, 2-p, 3-q
void heapsort(Zadanie arr[], unsigned int N, int rpq){ //http://www.codecodex.com/wiki/Heapsort#C.2B.2B
    unsigned int n = N, i = n/2, parent, child;  
    Zadanie t;  
    
    for (;;) { /* Loops until arr is sorted */  
        if (i > 0) { /* First stage - Sorting the heap */  
            i--;           /* Save its index to i */  
            t = arr[i];    /* Save parent value to t */  
        } else {     /* Second stage - Extracting elements in-place */  
            n--;           /* Make the new heap smaller */  
            if (n == 0) return; /* When the heap is empty, we are done */  
            t = arr[n];    /* Save last value (it will be overwritten) */  
            arr[n] = arr[0]; /* Save largest value at the end of arr */  
        }  
    
        parent = i; /* We will start pushing down t from parent */  
        child = i*2 + 1; /* parent's left child */  
    
        /* Shift operation - pushing the value of t down the heap */  
        while (child < n) { 
            if (rpq==1){
                if (child + 1 < n  &&  arr[child + 1].r > arr[child].r) {  
                    child++; /* Choose the largest child */  
                } 
            }else if (rpq == 2){
                if (child + 1 < n  &&  arr[child + 1].p > arr[child].p) {  
                    child++; /* Choose the largest child */  
                }
            }else if (rpq == 3){
                if (child + 1 < n  &&  arr[child + 1].q > arr[child].q) {  
                    child++; /* Choose the largest child */  
                }
            }
            //if (child + 1 < n  &&  arr[child + 1] > arr[child]) {  
            //    child++; /* Choose the largest child */  
            //}  
            if (rpq==1){
                if (arr[child].r > t.r) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                }
            }else if (rpq == 2){
                if (arr[child].p > t.p) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                } 
            }else if (rpq == 3){
                if (arr[child].q > t.q) { /* If any child is bigger than the parent */  
                    arr[parent] = arr[child]; /* Move the largest child up */  
                    parent = child; /* Move parent pointer to this child */  
                    //child = parent*2-1; /* Find the next child */  
                    child = parent*2+1; /* the previous line is wrong*/  
                } else {  
                    break; /* t's place is found */  
                } 
            }
        }  
        arr[parent] = t; /* We save t in the heap */  
    }  
}

void fdr(Zadanie Tab[], int arr[], unsigned int rozmiar){
    heapsort(Tab,rozmiar,1);
    for (unsigned int i = 0; i < rozmiar; i++){
        arr[i] = Tab[i].kolejnosc;
    }

}

int main(){
    unsigned int LiczbaZadan = 0, index = 0;
    bool xFirst=1;
    string line, filename;

    cout<<"Podaj nazwe pliku z danymi: ";
    cin>>filename;
    cout<<"\n";

    ifstream myfile ("JACK"+filename+".DAT");
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
        cout << "\n Odczytano plik z danymi.\n";
        myfile.close();
    }else cout << "Unable to open file"; 
    // obsluga algorytmu, czyli petle zamieniajace kolejnosc dzialan
    fdr(TabZadan, kolejnosc, LiczbaZadan);
    
    // wyswietlenie kolejnosci:
    cout << endl << "Wyliczona kolejnosc: ";
    for (unsigned int i = 0; i < LiczbaZadan; i++){
        //cout << TabZadan[i];
        cout << kolejnosc[i] << " ";
    }
    cout << endl << "Obliczanie Cmax: ";
    int cm = cmax(TabZadan,LiczbaZadan);
    cout << cm << endl;
    // zapis do pliku
    FILE *fp = fopen("out.txt","w");
    if (fp){
        fprintf(fp,"%d\n", cm);
        fclose(fp);
        cout << "Plik zostal zapisany.\n";
    }else {
        cout << "Nie moge otworzyc pliku " << filename << endl;
        return -1;
    }
    return 0;
}