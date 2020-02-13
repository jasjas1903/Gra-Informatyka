#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib> 
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

enum typ {bron, odzierz, zdrowie};

struct rzecz{
	string nazwa;
	typ rodzaj;
	int obrazenia;
	int ochrona;
	int lecznie;
	int bonus;
};

struct drzwi{
	string opis;
	int lokacja;
	char key;
	int klucz;
	drzwi *nastepne;
};

struct lokacja{
	string opis;
	int ileDrzwi;
	drzwi *pierwsze;
	rzecz *przedmiot;
	int skrzynia;
};

struct bohater{
	string nick;
	int sila,moc,odpornosc;
};

int main(int argc, char** argv) {
	lokacja budynek[100];
	int ile;
	fstream dane("opisy.txt",ios::in);
	dane>>ile;
	for (int i=0;i<ile;i++){
		int n,m,l;
		char key;
		string o;
		dane>>n;
		getline(dane,o);
		budynek[n].opis=o;
		dane>>m;
		budynek[n].ileDrzwi=m;
		for (int j=0;j<m;j++){
			dane>>l;
			dane>>key;
			getline(dane,o);
			drzwi *p = new drzwi;
			p->opis=o;
			p->lokacja=l;
			p->key=key;
			p->nastepne=budynek[n].pierwsze;
			budynek[n].pierwsze=p;
		}
	}
	int miejsce=0;
	char dzialanie;
	do {
		string keys="";
		system("cls");
		cout<<budynek[miejsce].opis<<" Co robisz?"<<endl;
		drzwi *start=budynek[miejsce].pierwsze;
		for (int i=1; i<=budynek[miejsce].ileDrzwi;i++){
			cout<<start->key<<" - "<<start->opis<<endl;
			keys=keys+start->key;
			start=start->nastepne;
		}
	//	do {
			dzialanie=getch();
			if(dzialanie>='A'&&dzialanie<='Z')
				dzialanie=dzialanie+32;
			if (keys.find(dzialanie)==string::npos){
				cout<<"Podales niemozliwa opcje, probuj jeszcze raz.";
				for(int i=0; i<700000000;i++);
				continue;
			}
	//	} while (keys.find(dzialanie)==string::npos);
		start=budynek[miejsce].pierwsze;
		for (int i=1; i<=budynek[miejsce].ileDrzwi;i++){
			if (start->key==dzialanie)
				miejsce=start->lokacja;
			else start=start->nastepne;
		}
		if (miejsce==100){
			cout<<"Zegnaj.";
		} 
	} while (miejsce!=100);
	return 0;
}
