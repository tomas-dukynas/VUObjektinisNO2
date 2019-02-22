#ifndef STRUCT_FUNCTIONS_H
#define STRUCT_FUNCTIONS_H
#include "checkInput.h"

using namespace std;

//studento struktura, funkcijos: display, readfile, sortbyname, mycomp

struct studentas {
    string firstName;
    string secondName;

    vector<double> nd;

    double visiNd = 0;
    double egz = 0;


    void readFile (int &index, vector<studentas> &s);

//Storing information

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

            while (egz > 10 || egz < 1){
                cout << "Egzamino balas turi buti tarp 1 ir 10! \n";
                cin >> egz;
            }

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

void readFile (int &index, vector<studentas> &s) {

    string line;

    int ndVisu;

    ifstream file_("studentai.txt");

    getline(file_, line); //pirmas

    while (getline(file_, line)) {
        istringstream pirmi(line);
        s.push_back(studentas());
        pirmi >> s[index].firstName;
        pirmi >> s[index].secondName;

        while (pirmi) {
            pirmi >> ndVisu;
            s[index].nd.push_back(ndVisu);
        }

        s[index].egz = s[index].nd.back();
        s[index].nd.pop_back();
        index++;
    }

}

//Sortina studentus
bool mycomp(const studentas & s1, const studentas & s2) {
    return (s1.firstName < s2.firstName);
}
void sortSbyName(vector<studentas> & s){
    sort(s.begin(), s.end(), mycomp);
}


void display(vector<studentas> s, int index)
{
 //Displaying information

        cout << "Jusu pateikta informacija: \n";

        cout << "Vardas"<<setw(15)<<"Pavarde"<<setw(20)<<"Galutinis(Vid.)"<< setw(20)<<"Galutinis(Med.) \n";

        cout <<"-------------------------------------------------------------------------------------\n";


    for (int i = 0; i < index; ++i) {
        cout << s[i].firstName << setw(15) << s[i].secondName << setw(20) << fixed<< setprecision(2) << s[i].galutinioV() <<setw(20)<<s[i].galutinioM()<<"\n";
    }
}

#endif // STRUCT_FUNCTIONS_H