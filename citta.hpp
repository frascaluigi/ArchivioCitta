#ifndef citta_hpp
#define citta_hpp
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

class Citta{
	private:
		string nome_citta;
		string provincia;
		int n_abitanti;
		vector<string> att_tur;
		int count; //contiene il numero delle attrazioni della citta'
	private:
		bool ctrlPro(string x); //controlla l'immissione della provincia
		bool ctrlCitta(string x); //controlla l'immissione della citta
		bool ctrlInt(); // controlla l'immissione di interi
	public:
		Citta(){ count=0; }
		void setcount(int x){ count = x; } //setta count(contiene il numero di attrazioni) a un determinato numero
		int getcount() { return count; } //ritorna count,cioè il numero di attrazioni
		void setcitta(istream& c); // setta la citta,viene passato lo stream quando è l'utente ad immettere
		void setcitta(string x); // setta la citta,viene passata la stringa quando legge da file
		void setprovincia(istream& p); //setta la provincia,con lo stream sia da file che da immissione utente
		void setabitanti(istream& n); //setta gli abitanti,con lo stream sia da file che da immissione utente
		int setatt(const string &a); //setta le attrazioni turistiche
		void cancatt(int ind_el);
		void pulisci(); //riporta a 0 l'array delle attrazioni turistiche dell'oggetto di tipo citta'
		string getcitta(); //ritorna il nome della citta'
		string getprovincia(); // ritorna il nome della provincia
		int getabitanti(); //ritorna il numero di abitanto
		string getatt(int x); //ritorna una certa attrazione in base all'indice
		string low(string str); //ritorna la stringa minuscola
	};
	
	string Citta::low(string s){
           string str(s.length(),' '); 
           for ( int i=0; i<s.length(); i++ ){
                 str[i]=tolower(s[i]);
            }
           return str;
	}
	 
	bool Citta::ctrlPro(string x){
		int ctrl;
		stringstream convert(x);
		if((x.size()!=2)||(convert>>ctrl)) return 0;
		return 1;
	}
	
	bool Citta::ctrlCitta(string x){
		int ctrl;
		stringstream convert(x);
		if(convert>>ctrl) return 0;
		return 1;
	}
	
	bool Citta::ctrlInt(){
			if(cin.fail()){
				cin.clear();
				cin.ignore(256,'\n');
				return 0;
			}else return 1;
		}
	
	void Citta::setcitta(istream& c){ 
		getline(c,nome_citta,'\n');
		while(!ctrlCitta(nome_citta)){
			cerr<<"Errore nell'immissione della citta',prego ripetere"<<endl;
			getline(c,nome_citta,'\n');
		}
		nome_citta = low(nome_citta);
	}
		
	void Citta::setcitta(string x){ nome_citta = x; }
		 
	string Citta::getcitta(){ return nome_citta; }
	
	void Citta::setprovincia(istream& p){ 
		p>>provincia;
		while(!ctrlPro(provincia)){
			cerr<<"Errore nell'immissione della citta,prego ripetere"<<endl;
			p>>provincia;
		}
		provincia = low(provincia);
	}
	
	string Citta::getprovincia(){ return provincia; }	
	
	void Citta::setabitanti(istream& n){ 
		n>>n_abitanti;	
		while(n_abitanti<0||!ctrlInt()){
			cerr<<"Errore nell'immissione degli abitanti,prego ripetere"<<endl;
			n>>n_abitanti;
		}
	}
	
	int Citta::getabitanti(){ return n_abitanti; }
	
	int Citta::setatt(const string &a){
			int n;
			if(count <= 9){
				att_tur.push_back(a);
				n = att_tur.size();
				return n; //ritorna il numero di attrazioni inserite
				}else{ 
					cerr<<"Non e' possibile inserire piu' di 10 attrazioni"<<endl;
					return n;	
				}
		}	
	
	void Citta::cancatt(int ind_el){
			att_tur.erase(att_tur.begin()+ind_el);
			count = att_tur.size();
			if(count == 0) pulisci();
	}
	
	string Citta::getatt(int x){ if(count>0) return att_tur.at(x); }
	
	void Citta::pulisci(){ att_tur.clear(); }
#endif
