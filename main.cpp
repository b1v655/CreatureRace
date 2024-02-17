#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include "leny.h"
using namespace std;
void beolvas(string &napok,string fajlnev, vector<leny*> &a);
string gyoztes(vector<leny*> leny,string napok);
enum Exception { MINDMEGDOGLOTT };
#define NORMAL_MODE
#ifdef NORMAL_MODE
int main()
{
    setlocale(LC_ALL,"hun");
    vector<leny*> leny;
    string napok;
    beolvas(napok,"inp12.txt",leny);
    try{cout<<gyoztes(leny,napok);}catch(Exception MINDMEGDOGLOTT){cout<<"nem ért célba senki!";}
    for(int i=0; i<(int)leny.size(); ++i) delete leny[i];
    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("1", "beolvasas es eredmenyek tesztelese")
{
	vector<leny*> verseny;
	string napok, nyer;
	int halalszam = 0;
	beolvas(napok,"inp11.txt",verseny);
	nyer = gyoztes(verseny,napok);
	for (int i = 0; i < (int)verseny.size(); ++i) {
		if (!verseny[i]->el_e())halalszam++;
	}
	CHECK(verseny.size() == 4);
	CHECK(nyer == "Vandor");
	CHECK(halalszam == 0);

	for (int i = 0; i < (int)verseny.size(); ++i) delete verseny[i];

	//Verseny 1 halottal
	beolvas(napok,"inp12.txt",verseny);
	nyer = gyoztes(verseny, napok);
	halalszam = 0;
	for (int i = 0; i < (int)verseny.size(); ++i) {
		if (!verseny[i]->el_e())halalszam++;
	}
	CHECK(verseny.size() == 4);
	CHECK(nyer == "Seta");
	CHECK(halalszam == 1);

	for (int i = 0; i < (int)verseny.size(); ++i) delete verseny[i];

	//Mind megdöglik
    beolvas(napok,"inp13.txt", verseny);
	try{nyer = gyoztes(verseny, napok);}catch(Exception ex){CHECK(ex==MINDMEGDOGLOTT);}

}


TEST_CASE("2", "vizvaltozas")
{
	leny* leny;
	leny = new homokjaro("Homokjáró célbaér", 2,0);
	leny->lepes('n');
	CHECK(leny->el_e());
	delete leny;
	leny = new homokjaro("Homokjáró megdöglik", 1);
	leny->lepes('n');
	CHECK(!leny->el_e());
	delete leny;
	leny = new szivacs("Szivacs célbaér", 5);
	leny->lepes('n');
	CHECK(leny->el_e());
	delete leny;
	leny = new szivacs("Szivacs megdöglik", 4);
	leny->lepes('n');
	CHECK(!leny->el_e());
	delete leny;
	leny = new lepegeto("Lépegetõ célbaér", 3);
	leny->lepes('n');
	CHECK(leny->el_e());
	delete leny;
	leny = new lepegeto("Lépegetõ megdöglik", 2);
	leny->lepes('n');
	CHECK(!leny->el_e());
    delete leny;
}
TEST_CASE("3","viztulcsordulas")
{
    leny* leny;
    leny=new lepegeto("maxviz",12);
    leny->lepes('e');

    for(int i=0;i<6;++i){
        leny->lepes('n');
    }
    CHECK(!leny->el_e());
    delete leny;
    leny=new homokjaro("maxviz",8);
    leny->lepes('e');
    for(int i=0;i<8;++i){
        leny->lepes('n');
    }
    CHECK(!leny->el_e());
    delete leny;
    leny=new szivacs("maxviz",20);
    leny->lepes('e');
    for(int i=0;i<5;++i){
        leny->lepes('n');
    }
    CHECK(!leny->el_e());
    delete leny;
}
TEST_CASE("4","tavolsag es lepes mtodus teljesulese")
{
	leny* leny;
	leny = new homokjaro("kedves", 5,0);
	leny->lepes('n');
	CHECK(leny->tavolsag() == 3);
	leny->lepes('f');
	CHECK(leny->tavolsag() == 4);
	leny->lepes('e');
	CHECK(leny->tavolsag() == 4);
	CHECK(leny->el_e());
	delete leny;
	leny = new szivacs("bob", 12,0);
	leny->lepes('n');
	CHECK(leny->tavolsag() == 0);
	leny->lepes('f');
	CHECK(leny->tavolsag() == 1);
	leny->lepes('e');
	CHECK(leny->tavolsag() == 4);
	CHECK(leny->el_e());
	delete leny;
	leny = new lepegeto("birodalmi", 7,0);
	leny->lepes('n');
	CHECK(leny->tavolsag() == 1);
	leny->lepes('f');
	CHECK(leny->tavolsag() == 3);
	leny->lepes('e');
	CHECK(leny->tavolsag() == 4);
	CHECK(leny->el_e());
}

#endif
void beolvas(string &napok,string fajlnev, vector<leny*> &a)
{

    ifstream adatbe(fajlnev.c_str());
    if(adatbe.fail()) {
        cout << "A fájl nem található";
        exit(1);
    }
    int m;
    adatbe>>m;
    char k;
    string n;
    int v;
    a.resize(m);
    for(int i=0;i<m;i++){
        adatbe>>n>>k>>v;
        switch(k){
            case 'h':a[i]=new homokjaro(n,v);
                break;
            case 'l':a[i]=new lepegeto(n,v);
                break;
            case 's':a[i]=new szivacs(n,v);
                break;
        }
    }
    adatbe>>napok;
}

string gyoztes(vector<leny*> leny,string napok)
{

    string gyoztes="n.a.";
    int max=0;
    for(int i=0; i<(int)leny.size(); ++i){
        int j=0;
        while(leny[i]->el_e()&&j<(int)napok.size()){
            leny[i]->lepes(napok[j]);
            ++j;
            //lépéskiírás:
            cout<<leny[i]->neve()<<" t: "<<leny[i]->tavolsag()<<", v:"<<leny[i]->viz()<<", n:"<<napok[j]<<endl;
        }

        if(leny[i]->el_e()&&leny[i]->tavolsag()>max){
            max=leny[i]->tavolsag();
            gyoztes=leny[i]->neve();
        }
    }
    if(gyoztes=="n.a.") throw MINDMEGDOGLOTT;
    return gyoztes;
}
