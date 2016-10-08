#ifndef archivio_hpp
#define archivio_hpp
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
using namespace std;

class Archivio{
	private:
		vector<Citta> elencocitta; //elenco di tutte le citta' presenti
		ofstream file; //file dove scrivere
		ifstream file_lettura; //file da dove leggere
		vector<string> dat_trovati; //mantiene le occorrenze trovate
		vector<int> ind_trovati; //mantiene gli indici effettivi delle occorrenze
	private:
		void Salva(); //salva tutto l'archivio su file,funzione chiamata dal distruttore di classe
		void search(int opzione); //effettua delle ricerche in base all'opzione passata 
		void dati_citta(int indice); //visualizzazione dei dati di una citta',trovata tramite l'indice passato come parametro
		bool ctrlInt(); //controlla che l'immissione di interi non abbia dato errori
		bool ctrlStr(string x);
        void prov_citta(string prov); //visualizza tutte le citta che hanno una determinata provincia,passata come parametro
		void num_citta(int n); //trova le citta' sotto un numero di abitanti che gli vengono passati come un parametro
		void stampa(); // stampa l'array dat_trovati;
		void vis_citta_att(); //visualizzazione citta'Â  che hanno una certa attrazione turistica
		int agg_attrazione(int indice); //aggiunge un'attrazione turistica,viene passato l'indice della citta a cui aggiungere
		void canc_attrazione(int ind_citta,int ind_canc); //cancella un'attrazione turistica,viene passato l'indice della citta 
		int menu_attrazione(int indice); //stampa delle attrazioni;(mancante)
	public:	
		void canc(); //cancella la citta solo se non è presente in mappa
		bool present(string x); //vede se una citta e' presente in archivio
		int getindtrovati(int s);
		string getdattrovati(int x);
		void immissione();
		void modifica(); 
		void ricerca();
		void vis(); //funzione da eliminare	
		int getnumcitta();
		string getcitta(int x);
		vector<string> separa(string x,char fine);
		int ric_sottostringa(const string x); //ricerca una sottostringa che viene passata come parametro in una stringa
		int menu_sottostringa(); //stampa il menu di quello che ha trovato ric_sottostringa()	
	public:
		Archivio(){ 
			file_lettura.open("dati.txt");
				if(file_lettura.fail()){
					cerr<<"\nNon e' stato trovato nessun file,da cui caricare l'archivio"<<endl;
					cout<<"Inserire almeno una citta\n"<<endl; 
					immissione();
				}else{
					Citta temp; 
					string *p = new string;
					string *att = new string;
							if(file_lettura.eof()){
									cout<<"File vuoto"<<endl;
							}else{
									while(!file_lettura.eof()){ //controllo che il file non e' finito
											getline(file_lettura,*p,'\n');
											int i;
											if((!file_lettura.eof())&&(*p!="...")){
												temp.setcitta(*p);
												temp.setprovincia(file_lettura); 
												temp.setabitanti(file_lettura); 
												getline(file_lettura,*att,'\n');
												while(*att!="..."){	
													if(*att!=""){ 
														i = temp.setatt(*att);
														temp.setcount(i);
													}
													getline(file_lettura,*att,'\n');
												}
											}else{
												break;
											}
										elencocitta.push_back(temp);
										temp.pulisci();
										}
										delete p;
										delete att;
									}
											
					file_lettura.close();
				}
		}
		
		
		~Archivio(){ Salva(); }
	};
	
	void Archivio::Salva(){ //private
			int k = elencocitta.size(); 
			string att; 
			file.open("dati.txt");	
			if(file.fail()) cerr<<"Impossibile Salvare"<<endl;	
			for(int p=0;p<k;p++){
				file<<elencocitta[p].getcitta()<<endl;
				file<<elencocitta[p].getprovincia()<<endl;
				file<<elencocitta[p].getabitanti()<<endl;
				int i = 0;
				int count = elencocitta[p].getcount();
				if(count>0){
					do{
						att=elencocitta[p].getatt(i);
						i++;
						file<<att<<endl;
					}while(i<count);
				}
				file<<"..."<<endl;
			}
		file.close();
	}
	
	bool Archivio::ctrlInt(){
			if(cin.fail()){
				cin.clear();
				cin.ignore(256,'\n');
				return 0;
			}else return 1;
		}
	
	bool Archivio::ctrlStr(string x){
		int ctrl;
		stringstream convert(x);
		if(convert>>ctrl) return 0;
		return 1;
	}
	
	int Archivio::getindtrovati(int s){ 
		int k;
		k = ind_trovati.at(s);
		return k;
	}
	
	string Archivio::getdattrovati(int x){ 
		return dat_trovati.at(x);
	}
	
	bool Archivio::present(string x){
		int i = elencocitta.size();
		for(int j=0;j<i;j++){
		string app = elencocitta[j].getcitta();
		if(app == x) return 1;
		}
		return 0;
	}
		
	
	int Archivio::ric_sottostringa(const string x){ //private
		dat_trovati.clear();
		ind_trovati.clear();
		int n_citta = elencocitta.size(); 
		cout << "citta in archivio:\t" <<n_citta<<endl; 
		int c=0;
		string app;
		size_t found;
		for(int i=0;i<n_citta;i++){
			app = elencocitta[i].getcitta();
			found=app.find(x);
			if(found!=string::npos) {
				c++;
				dat_trovati.push_back(app);
				ind_trovati.push_back(i);
				int k = dat_trovati.size();
				int j = ind_trovati.size();
			}
		}
		return c;	
	}
	
	int Archivio::menu_sottostringa(){ //private
		int scelta;
		int n = dat_trovati.size();
		int i=0;
		do{
			do{
				cout<<"\t"<<i<<dat_trovati.at(i)<<endl;
				i++;
			}while(i<n);
			cout<<"Inserisci scelta"<<endl;
			cin>>scelta;
		}while(scelta<0||scelta>=n);
		return scelta;		
	}
	
	void Archivio::dati_citta(int indice){ //private
		int i=0;
		cout<<"citta:\t"<<elencocitta[indice].getcitta()<<endl;
		cout<<"provincia:\t"<<elencocitta[indice].getprovincia()<<endl;
		cout<<"abitanti:\t"<<elencocitta[indice].getabitanti()<<endl;
		int count = elencocitta[indice].getcount();
		do{
			string att=elencocitta[indice].getatt(i);
			cout<<"attrazione\t"<<att<<endl;
			i++;
		}while(i<count); 
	}
	
	void Archivio::prov_citta(string prov){ //private
		dat_trovati.clear();
		int n = elencocitta.size();
		for(int i=0;i<n;i++){
			string temp = elencocitta[i].getprovincia();
			if(temp == prov){
				string citta = elencocitta[i].getcitta();
				dat_trovati.push_back(citta);
			}
		}
	}
	
	vector<string> Archivio::separa(string x,char fine){
		           vector<string> dati_separati;
		           size_t Cpos, indice=0;
		           while(Cpos!=string::npos){
			                                 Cpos=x.find(fine,indice);
			                                 dati_separati.push_back(x.substr(indice,Cpos-indice));
			                                 indice=Cpos;
			                                 indice++;
                   }     
                   return dati_separati;
                   }
	
	
	void Archivio::num_citta(int n){ //private
		dat_trovati.clear();
		int x = elencocitta.size();
		int num; 
		for(int i=0;i<x;i++){
			num = elencocitta[i].getabitanti();
			if(num<n){
				string citta = elencocitta[i].getcitta();
				dat_trovati.push_back(citta);
			}
		} 
	}
	
	void Archivio::stampa(){ //private
		int n = dat_trovati.size();
		for(int i=0;i<n;i++){
			cout<<"citta:"<<i<<dat_trovati[i]<<endl;
		}
	}
	
	void Archivio::search(int opzione){ //private
		string temp;
		switch(opzione){
			case 1:
				int app;
				cout<<"Inserisci il nome della citta di cui si vogliono avere le informazioni"<<endl;
				cin>>temp;
				app = ric_sottostringa(temp);
				if(app!=0){
					int i = menu_sottostringa();
					int mod = ind_trovati.at(i);
					dati_citta(mod);
				}else{
					cout<<"Non e' stata trovata nessuna citta'"<<endl;
				}
				break;
			case 2:
				cout<<"Inserisci la provincia di cui si vogliono sapere le citta"<<endl;
				cin>>temp; 
				prov_citta(temp);
				stampa();
				break;
			case 3:
				int n;
				cout<<"Visualizza le citta' sotto un certo numero di abitanti,inserisci il numero"<<endl;
				cin>>n;
				while(n<0||!ctrlInt()){
					cerr<<"Errore nell'immissione del numero,prego ripetere"<<endl;
					cin>>n;
				}
				num_citta(n);
				stampa();
				break;
			default: 
			break;	
		}
	}
	
	int Archivio::getnumcitta(){
			int n = elencocitta.size();
			return n;
		}
		
	string Archivio::getcitta(int x){
		string citta = elencocitta[x].getcitta();
		return citta;
	}
	void Archivio::immissione(){ //public
		bool nuova; 
		do{
			Citta temp;
			string attrazione;
			bool risp;
			cout<<"Inserisci nome della citta' da inserire"<<endl;
			cin.clear();
			cin.ignore(256,'\n');
			temp.setcitta(cin); 
			cout<<"Inserisci la provincia di appartenenza della citta' (es.PR)"<<endl;
			temp.setprovincia(cin);
			cout<<"Inserisci il numero abitanti della citta"<<endl;
			temp.setabitanti(cin);
			cout<<"Inserisci l'attrazione di questa citta"<<endl;
			do{
				cin.ignore(256,'\n');
				getline(cin,attrazione);
				int i = temp.setatt(attrazione);
				//i contiene il numero di attrazioni inserite
				temp.setcount(i); 
				cin.clear();
				if(i!=-1){
					cout<<"Ci sono altre attrazioni che vuoi aggiungere?(1-si/0-no)"<<endl;
					cin>>risp;
				    while(!ctrlInt()){
                                     cout<<"Errore immissione,prego ripetere"<<endl;
                                     cin>>risp;
                                     }
                }else{ break; }
			}while(risp);
			cout<<"sono state inserite:"<<temp.getcount()<<"attrazioni"<<endl;
			elencocitta.push_back(temp);
			cout<<"Vuoi inserire un'altra citta?(1-si/0-no)\t"<<endl;
			cin>>nuova;
		}while(nuova);
	}
	
	void Archivio::canc(){
         ifstream file_mappa;
         file_mappa.open("mappa.txt");
         if(!file_mappa.fail()){
                                string x;
                                cout<<"Inserisci la citta che si vuole eliminare(anche sottostringa)"<<endl;
                                cin>>x;
                                int ric = ric_sottostringa(x);
                                if(ric!=0){
                                           int i = menu_sottostringa();
                                           int mod = ind_trovati.at(i); //qui ho l'elemento che forse deve cancellare
                                           string ctrl = elencocitta[mod].getcitta();
                                           string infonodo;
                        	               char c[300];
                                           file_mappa.getline(c,300,'\n'); //prendo tutta la linea 
                                           while(!file_mappa.eof()){
                                                                    infonodo=c; 
                                                                    vector<string> ctrl_primo = separa(infonodo,'*');	//prendo il nodo le stringhe tra *
					                                                //controllo il primo elemento
                                                                    if(ctrl_primo[0]==ctrl){
                                                                                           cout<<"non è possibile cancellare"<<endl;
                                                                                           return;
                                                                    }
                                                                    int j = ctrl_primo.size();
                                                                    for(int i=1;i<j;i++){
                                                                            vector<string> ctrl_successivo = separa(ctrl_primo[i],'-');
                                                                            if(ctrl_successivo[1]==ctrl){
                                                                                                         cout<<"non è possibile cancellare"<<endl;
                                                                                                         return;
                                                                                                         }                               
                                                                      }
                                                                    file_mappa.getline(c,300,'\n'); //prendo tutta la linea
                                           }
                                           elencocitta.erase(elencocitta.begin()+mod);
                                           }else{
                                                 cout<<"Occorrenza non trovata"<<endl;
                                           }
                                }else{
                                      string x;
                                      cout<<"Inserisci la citta che si vuole eliminare(anche sottostringa)"<<endl;
                                      cin>>x;
                                      int ric = ric_sottostringa(x);
                                          if(ric!=0){
                                                     int i = menu_sottostringa();
                                                     int mod = ind_trovati.at(i);
                                                     elencocitta.erase(elencocitta.begin()+mod);
                                                     }else{ cout<<"Occorrenza non trovata"<<endl; }
                                }
         }
                                      
	
	int Archivio::agg_attrazione(int indice){ //private
		int n = elencocitta[indice].getcount();
		if(n<10){
			string nuova_att;	
			cout<<"Inserisci l'attrazione che si vuole aggiungere"<<endl;
			cin>>nuova_att; 
			while(!ctrlStr(nuova_att)){
                              cout<<"Errore immissione,prego ripetere"<<endl;
                              cin>>nuova_att;
                              }
            n = elencocitta[indice].setatt(nuova_att);
            elencocitta[indice].setcount(n);
			return 1;
		}else{ return 0; }
	}
	
	int Archivio::menu_attrazione(int indice){
		int elimina,j=1;
		int n = elencocitta[indice].getcount();
		if(n>0){
			for(int i=0;i<n;i++){
				cout<<"\t"<<j<<elencocitta[indice].getatt(i)<<endl;
				j++;
			}
			cout<<"Inserisci l'indice della citta che si vuole eliminare"<<endl;
			do{
				cin>>elimina;
			}while(elimina<1||elimina>n);
			return elimina;
		}else{ return -1;}
	}
	
	void Archivio::canc_attrazione(int ind_citta,int ind_canc){
			elencocitta[ind_citta].cancatt(ind_canc);
			cout<<"Eliminato"<<endl;
		}
	
	void Archivio::modifica(){ //public
		string x;
		int mod = 0;
		int opzione,j;
		cout<<"Inserisci il nome(o la sottostringa) della citta che si vuole modificare"<<endl;
		cin>>x;
		while(!ctrlStr(x)){
                          cout<<"Errore nell'immissione,prego ripetere"<<endl;
                          cin>>x;
                          }
		j = ric_sottostringa(x);
		if(j!=-1){
		int i = menu_sottostringa();
			mod = ind_trovati.at(i);
			cout<<"Per la citta' scelta,cosa si vuole modificare?"<<endl;
			do{	
				cout<<"\t1. numero abitanti della citta"<<endl;
				cout<<"\t2. attrazioni turistiche della citta"<<endl;
				cout<<"\t0. Esci"<<endl;
				cin>>opzione;
			}while(opzione<0||opzione>2);
			switch(opzione){
				case 1:
					cout<<"Inserisci il nuovo numero di abitanti"<<endl;
					elencocitta[mod].setabitanti(cin);
					break;
				case 2:
					int sub_opzione,canc;
					do{
						cout<<"\t1. Aggiungi nuova attrazione turistica"<<endl;
						cout<<"\t2. Cancella attrazione turistica"<<endl;
						cout<<"\t0. Esci"<<endl;
						cin>>sub_opzione;
					}while(sub_opzione<0||sub_opzione>2);
					switch(sub_opzione){
						case 1:
							agg_attrazione(mod);
							break;
						case 2:
							canc = menu_attrazione(mod);
							if(canc!=-1) canc_attrazione(mod,canc); 
							else cerr<<"Non ci sono attrazioni da eliminare per questa citta"<<endl;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		}else{
				cout<<"Nulla da modificare\n"<<endl;
				return;
			}
		}
	
	void Archivio::ricerca(){ //public
		int scelta;
		do{	
			cout<<"*\t1.visualizza dati di una citta(individuata tramite sottostringa)"<<endl;
			cout<<"*\t2.visualizza citta appartenenti ad una provincia"<<endl;
			cout<<"*\t3.visualizza citta con meno di n abitanti"<<endl;
			cout<<"*\t0.Menu' precedente"<<endl;
			cout<<"\t_______________________________"<<endl;
			cout<<"\tDigitare il numero dell'opzione"<<endl;
			do{
				cin>>scelta;
			}while(scelta<0||scelta>4);
			search(scelta);
		}while(scelta!=0);
	}
#endif
