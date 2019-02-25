#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <time.h>
#include <random>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;

void checkInput(int &input);

struct studentas{


string firstName;
string secondName;

vector<double> nd;
double visiNd = 0;
double egz = 0;



    void data() {
        cout << "Studento vardas: ";
        cin >> firstName;
        cout << "\n";
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "Studento pavarde: ";
        cin >> secondName;
        cout << "\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Ar noresite sugeneruoti random pazymius ir egzamino balus? Random - spauskite 1. Ivesties budu - spauskite 0: \n";
        int ivestiesRadom;
        cin >> ivestiesRadom;

        checkInput(ivestiesRadom);

        if (ivestiesRadom == 1) {
            randomNumbers();
        }else {
            numberInput();
            cout << "Iveskite studento egzamino rezultata: \n";
            cin >> egz;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

//Generuoja random skaicius

    void randomNumbers() {
        cout << "Iveskite kiek norite sugeneruoti skaiciu!: \n";
        cin >> visiNd;

        while (cin.fail()){
            cout << "Blogas irasymas, bandykite dar karta: \n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> visiNd;
        }

        nd.reserve(visiNd);

        const unsigned int seed = time(0);
        mt19937_64 rng(seed);
        uniform_real_distribution<double> random(1, 10);

        for (int i = 0; i<visiNd; i++) {
            nd.push_back(static_cast<int>(random(rng)));
        }

        egz = static_cast<int>(random(rng));
    }


//Rankiniu budu turi suvest nd ir egz

    void numberInput() {
        cout << "Iveskit namu darbu pazymius, norint pabaigti, iveskite ne skaiciu! \n";

        int skc;

        while (cin >> skc) {
            if (!(skc >= 1 && skc <= 10)){
                cout << "Pazymys turi buti tarp 1 ir 10! \n";
                continue;
            }
            nd.push_back(skc);
        }

        visiNd  = nd.size();

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

//Vidutinio skaiciavimas

    double vid () {
        double vidutinis = 0;

        for (auto &viens : nd) {
            vidutinis += viens;
        }

        vidutinis /= nd.size();

        return vidutinis;
}

//Medianos skaiciavimas

    double median (vector<double>set) {
        sort(set.begin(), set.end());
        return (set.size()% 2 == 0 ? (set[set.size()/2] + set[(set.size() / 2 ) - 1]) / 2 : set[set.size() / 2]);
    }

    double galutinioM() {
        return 0.4 * median(nd) + 0.6 * egz;
    }

    double galutinioV() {
        return 0.4 * vid() + 0.6 * egz;
    }
};

void display(vector<studentas> s, int index);

int main()
{
    vector<studentas> s;
    int index = 0;
    cout << "Kiek noresite ivesti studentu ?" << endl;
    int stud;
    cin >> stud;
    while(cin.fail() || stud > 100000) {
        cin.clear();
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        cout << "Neteisingai ivedete, veskite dar karta! ";
        cin >> stud;
    }
    s.resize(stud);
    index = stud;

    cout << "\n";

    for (int i = 0; i < stud; i++) {
        s[i].data();
    }

    display(s, stud);

 return 0;
}

void checkInput(int &input) {

    while (cin.fail() || (input !=1 && input !=0)){
            cout << "Blogas irasymas, bandykite dar karta: \n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cin >> input;
    }

}

void display(vector<studentas> s, int index)
{
 //Displaying information

    cout << "Ar norite skaiciuoti galsutini su mediana, ar su vidurkiu? Su vidurkiu, spauskite 1, su mediana spauskite 0 \n";
    int pasirinkimas = 0;
    cin >> pasirinkimas;

    //tikrinimas
    checkInput(pasirinkimas);

    if (pasirinkimas == 1){

        cout << "Jusu pateikta informacija su VIDURKIU: \n";

        cout << "Vardas"<<setw(15)<<"Pavarde"<<setw(20)<<"Galutinis(Vid.)\n";

        cout <<"-------------------------------------------------------------------------------------\n";


    for (int i = 0; i < index; ++i) {
        cout << s[i].firstName << setw(15) << s[i].secondName << setw(20) << fixed<< setprecision(2) << s[i].galutinioV() <<"\n";
    }
    }
    else {

        cout << "Jusu pateikta informacija su MEDIANA: \n";

        cout << "Vardas"<<setw(15)<<"Pavarde"<<setw(20)<< "Galutinis(Med.) \n";

        cout <<"-------------------------------------------------------------------------------------\n";


    for (int i = 0; i < index; ++i) {
        cout << s[i].firstName << setw(15) << s[i].secondName << setw(20) << fixed<< setprecision(2) << s[i].galutinioM() <<"\n";
    }
    }
}

