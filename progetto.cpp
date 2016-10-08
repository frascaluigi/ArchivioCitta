#include "citta.hpp"
#include "archivio.hpp"
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<fstream>
#include<list>
using namespace std;

struct peso{
      
      int km;
      float cost;

          peso operator+(const peso& p) {
                peso r;
                r.km=km+p.km;
                r.cost=cost+p.cost;
	            return r;
         }
         
         peso operator=(const peso& p) {
	        km=p.km;
            cost=p.cost;
            return *this;
         }
         
         peso operator+=(const peso& p) {
	        km+=p.km;
            cost+=p.cost;
            return *this;
         }
         
         bool operator<(const peso &a){
                return km<a.km;
         }
};

class Collegamento{ // collegamento è da considerarsi un arco
	private:
		string cittacollegata;
		string tipo_collegamento;
		peso p;
	public:
		Collegamento(){}
		void setcittacollegata(string nome);
		string getcittacollegata();
		void settipo(string s);
		string gettipo();
		void setPeso(peso q);
		peso getPeso();
		~Collegamento(){} //distruttore
};

void Collegamento::setcittacollegata(string nome){ cittacollegata = nome; } //setta il collegamento
string Collegamento::getcittacollegata(){ return cittacollegata; } //ritorna il collegamento del nodo
void Collegamento::settipo(string s){ tipo_collegamento = s; } //setta il tipo di collegamento
string Collegamento::gettipo(){ return tipo_collegamento; } //ritorna il tipo di collegamento
void Collegamento::setPeso(peso q){ p=q; }     
peso Collegamento::getPeso(){ return p; }

class Mappa{
		public:
			struct Nodo{
				string citta;
        		list<Collegamento> collegamenti;
			};
		private:
			Archivio nuovo; 
			ifstream file_archivio;
			ifstream file_mappa;
			ofstream file_mapp;
			vector<Nodo> vertici;
			bool ctrlCitta(string x);
			bool isPresent(string x);
			bool exist_citta(string x);
			bool ctrlInt();
		
		public:
			Mappa(){
				file_mappa.open("mappa.txt");
				Nodo temp_nodo;
				Collegamento temp_coll;
				if(!file_mappa.fail()){ 
					string infonodo;
					char c[300];
					file_mappa.getline(c,300,'\n'); //prendo tutta la linea 
					while(!file_mappa.eof()){
                        infonodo=c;
						vector<string> dati_nodo = separa(infonodo,'*');	//prendo il nodo le stringhe tra *
																		//la prima va in vertici[0].nome
																		//le altre sono da collegare
						temp_nodo.citta = dati_nodo[0]; //inserito il nodo in una variabile temporanea collegamento
						vertici.push_back(temp_nodo);
						int p = vertici.size();
						peso temp;
						int n = dati_nodo.size(),pr=0;
						for(int k = 1; k < n; k++){
							vector<string> dati_collegamenti = separa(dati_nodo[k],'-');
							//in dati_collegamenti ho gli indici delle informazioni
							int j = dati_collegamenti.size();
								int i = 0;
								while(i<j-1){
									temp_coll.setcittacollegata(dati_collegamenti[i]);
									i++;
									temp_coll.settipo(dati_collegamenti[i]);
									i++;
									string convertikm = dati_collegamenti[i]; //ritorna numeri come stringa
									stringstream convert(convertikm);
									int km;
									convert>>km;
									temp = temp_coll.getPeso();
									temp.km = km;
									i++;
									temp.cost = atof(dati_collegamenti[i].c_str()); //Convertire da stringa a float
									temp_coll.setPeso(temp);
                                    i++;
								}
							vertici[p-1].collegamenti.push_back(temp_coll);	 //Il collegamento viene aggiunto
						}
				    file_mappa.getline(c,300,'\n'); //prendo tutta la linea 
					}
				file_mappa.close();	
				}else{ cerr<<"File mappa non presente"<<endl; }
				
			}			
			
			
			void inserimento();
			bool insertcolleg();
			void canc_nodo();
			void canc_coll();
			void salvafile();
			vector<string> separa(string x,char fine);
			int ricerca_nodo(string citta_nodo);
			void vis_collegamenti(int indice);
			bool exist_coll(int primonodo,string nsnodo);
			void cam_min();
			void Dijkstra(int partenza,peso *k, int *p);
			
			~Mappa(){ salvafile(); }
	};
	
	void Mappa::salvafile(){
		int k = vertici.size();
		file_mapp.open("mappa.txt");
		Collegamento tmp;
		for(int i=0;i<k;i++){
			int ctrl = k-1;
			file_mapp<<vertici[i].citta; // dopo * iniziano i collegamenti 
			int n = vertici[i].collegamenti.size();
			list<Collegamento>::iterator p;
			int count = 0;
			peso temp;
			for(p=vertici[i].collegamenti.begin();p!=vertici[i].collegamenti.end();++p){
                temp = p->getPeso();
                file_mapp<<'*';                                                               
				file_mapp<<p->getcittacollegata()<<'-';
				file_mapp<<p->gettipo()<<'-';
				file_mapp<<temp.km<<'-';
				file_mapp<<temp.cost;
            }
			file_mapp<<endl;
		}
		file_mapp.close();
	}
		
		
	vector<string> Mappa::separa(string x,char fine){
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
	bool Mappa::ctrlInt(){
		if(cin.fail()){
			cin.clear();
			cin.ignore(256,'\n');
			return 0;
		}else return 1;
	}
		
	bool Mappa::ctrlCitta(string x){ 
		int ctrl;
		stringstream convert(x);
		if(convert>>ctrl) return 0;
		return 1;
	}
	
	bool Mappa::isPresent(string x){
		int k = nuovo.present(x);
		return k;
	}
	
	bool Mappa::exist_citta(string x){
		string temp_citta = x;
		cout << "nodi gia' presenti\t" << vertici.size() << endl;
		for(int h=0;h<vertici.size();h++){
			string city = vertici.at(h).citta;
				if(temp_citta == city){
					return 1;
					break;
				}
		}
		return 0;
	}
	
	void Mappa::inserimento(){
			string nome_citta; 
			int c;
			Nodo temp;
		do{
			cout<<"Inserisci nome citta che si vuole inserire(anche tramite sottostringa)"<<endl;
			do{
				cin.ignore(256,'\n');
				getline(cin,nome_citta);
			}while(!ctrlCitta(nome_citta));
			int p = nuovo.ric_sottostringa(nome_citta);
			if(p!=0){
				int i = nuovo.menu_sottostringa();
				nome_citta = nuovo.getdattrovati(i);
				if(!exist_citta(nome_citta)){
					temp.citta = nome_citta; 
					vertici.push_back(temp); // viene aggiunto il nodo nel vector
					cout<<"hai inserito:\t"<<nome_citta<<"\tin mappa"<<endl;
				}else{cout <<"citta gia' presente in mappa"<<endl;return;}
			}else{ cerr<<"Non e' stata trovata nessuna occorrenza"<<endl; return; }
			do{
				cin.clear();
				cin.ignore(256,'\n');
				cout<<"Continuare nell'immissione delle citta?(1-si/o-no)"<<endl;
				cin>>c;
			}while((c<0 || c>1)||(!ctrlInt()));
		}while(c==1);
	}
	
	int Mappa::ricerca_nodo(string citta_nodo){
		for(int i=0;i<vertici.size();i++){
			if(vertici[i].citta == citta_nodo){
				return i;
			}
		}
		return -1;
	}
	
	bool Mappa::exist_coll(int primonodo,string nsnodo){
					list<Collegamento>::iterator p;
					for(p=vertici[primonodo].collegamenti.begin();p!=vertici[primonodo].collegamenti.end();++p){
						string ctrl = p->getcittacollegata();
						if(ctrl == nsnodo) return 1;
					}
	return 0;
	}
	
	void Mappa::vis_collegamenti(int indice){
		int n = vertici.size();
		if(n>0){
			list<Collegamento>::iterator p;
			for(p=vertici[indice].collegamenti.begin();p!=vertici[indice].collegamenti.end();++p){
				cout<<"visualizzo citta collegata\t"<<p->getcittacollegata()<<endl;
				
				cout<<"visualizzo km della citta collegata\t"<<p->getPeso().km<<endl;
			}
		}
	}
	
	bool Mappa::insertcolleg(){
			string citta_pnodo,citta_snodo;
			int indice_pnodo,indice_snodo;
			cout<<"Prego inserire il primo nodo"<<endl; //NODO 1
			cin.ignore(256,'\n');
			getline(cin,citta_pnodo);
			if((indice_pnodo=ricerca_nodo(citta_pnodo))!=-1){ //ritorna -1 se non trova la citta,altrimenti l'indice di dove l'ha trovata
				cout<<"Nodo trovato"<<endl;
				cin.clear();
				cout<<"Prego inserire il secondo nodo"<<endl; //NODO 2
				getline(cin,citta_snodo);
				if((indice_snodo=ricerca_nodo(citta_snodo))!=-1){ //ritorna -1 se non trova la citta,altrimenti l'indice di dove l'ha trovata
					cout<<"Nodo trovato"<<endl;
					if(!exist_coll(indice_pnodo,citta_snodo)){ //controlliamo se già esiste un collegamento tra le due città
						Collegamento temp;
						peso tmp;
						int km;
						int prezzo;
						temp.setcittacollegata(citta_snodo);
						cout<<"Inserisci i kilometri del collegamento"<<endl; //KM COLLEGAMENTO
						cin>>km;
						tmp = temp.getPeso();
						tmp.km = km;
						string tipo;
						cout<<"Inserisci tipo di collegamento"<<endl; //TIPO COLLEGAMETO
						cin>>tipo;
						temp.settipo(tipo);
						cout<<"Inserisci il costo del collegamento"<<endl; //COSTO COLLEGAMENTO
						cin>>prezzo;
						tmp.cost = prezzo;
						temp.setPeso(tmp);
						vertici[indice_pnodo].collegamenti.push_back(temp);
						cout<<"Collegamento inserito"<<endl;
						temp.setcittacollegata(citta_pnodo);
						vertici[indice_snodo].collegamenti.push_back(temp);
					}else cerr<<"#Collegamento già presente#"<<endl;
				}else cerr<<"#Secondo Nodo non trovato#"<<endl;
			}else cerr<<"#Primo Nodo non trovato#"<<endl;
		}
	
 
	void Mappa::canc_nodo(){
		string elimina;
		cin.ignore(256,'\n');
		cout<<"Inserire il nome della citta che si vuole eliminare"<<endl;
		getline(cin,elimina);
		int indice = ricerca_nodo(elimina);
		if(indice!=-1){
			if(vertici[indice].collegamenti.empty()){
				vertici.erase(vertici.begin()+indice);
				cout<<"Eliminato"<<endl;
			}else{
				cerr<<"Non è possibile eliminare la citta dalla mappa"<<endl;
			}
		}else{
			cout <<"Nodo non presente"<<endl;
		}
	}
	
	void Mappa::canc_coll(){
		string temp1,temp2;
		cin.clear();
		cout<<"Inserisci primo nodo"<<endl;
		cin.ignore(256,'\n');
		getline(cin,temp1);
		int e = ricerca_nodo(temp1);
		if(e!=-1){
			cout<<"Inserisci il secondo nodo"<<endl;
			cin.clear();
			getline(cin,temp2);
			int s = ricerca_nodo(temp2);
			if(s!=-1){
				list<Collegamento>::iterator p;
				for(p=vertici[e].collegamenti.begin();p!=vertici[e].collegamenti.end();++p){	
					string ctrl = p->getcittacollegata();
					cout<< "primo for" <<endl;
					if(ctrl == temp2){ vertici[e].collegamenti.erase(p);cout<<"cancellato"<<endl; break; }
				}
				for(p=vertici[s].collegamenti.begin();p!=vertici[s].collegamenti.end();++p){
					string ctrl = p->getcittacollegata();
					cout << "secondo for" <<endl;
					if(ctrl == temp1){ vertici[s].collegamenti.erase(p);cout<<"cancellato"<<endl; break; }
				} 
			}else{ cout<<"secondo nodo non presente"<<endl;}
		}else{ cout<<"primo nodo non presente"<<endl;}
	}
	
	void Mappa::Dijkstra(int partenza,peso *k, int *p){
		   int dim=vertici.size(),v;
           int INFINITO=9999;
           peso w;  
           bool nodi_t[dim];                         // contiene i nodi trovati
           string id(vertici[partenza].citta);      // contiene il nome della citta scelta 

           for(int i=0;i<dim;i++){
              k[i].km=INFINITO;
              k[i].cost=0;
              nodi_t[i]=false;
              p[i]=-1;
           }

           k[partenza].km=0;
           p[partenza]=partenza;
           int u;

           for(unsigned int i=0;i<dim;i++){
               bool first_cycle=true;
               for(int y=0;y<dim;y++){       // estrae il nodo con cammino minore 
                     if(!nodi_t[y]){
                           if((first_cycle)&&(k[y].km!=INFINITO)){
                               first_cycle=false;
                               u=y;
                           }else{
                               if((k[y].km!=INFINITO) && (k[y]<k[u])){
                                   u=y;
                               }
                           }
                      }
                }
                
                nodi_t[u]=true;
                for(list<Collegamento>::iterator y=vertici[u].collegamenti.begin(); y!=vertici[u].collegamenti.end(); y++){    
                         id=y->getcittacollegata();
                         w=y->getPeso();
                         for(int j=0;j<dim;j++){
                             if(vertici[j].citta==id){
                                v=j;
                                break;
                             }
                         }
                         if(k[v].km>(k[u].km+w.km)){    
                              k[v]=k[u]+w;
                              p[v]=u;
                         }
                }
          }
    }

	
	void Mappa::cam_min(){
		  peso w[vertici.size()];
          int p[vertici.size()],in_partenza,in_arrivo;
          string part,arr;
          cout<<"Inserisci nome della citta' di partenza"<<endl;
		  cin.ignore(256,'\n');         
          getline(cin,part); 
          cin.clear();
          cout<<"Inserisci nome della città di arrivo"<<endl;
          getline(cin,arr);
          in_partenza=ricerca_nodo(part);
          in_arrivo=ricerca_nodo(arr);
          if((in_partenza!=-1)&&(in_arrivo!=-1)){ //controllo che le città inserite siano nella mappa
          	Dijkstra(in_partenza,w,p);  
          	if(w[in_arrivo].km==9999){
          	  cout<<"non c'è collegamento tra i vertici dati"<<endl;
          	}else{
              cout<<"il cammino minimo tra "<<vertici[in_partenza].citta<<" e "<<vertici[in_arrivo].citta<<" e' di "<<w[in_arrivo].km<<" km "<<endl;
              cout<<"il costo e' di " << w[in_arrivo].cost << " euro"<<endl<<endl;
              vector<int>::iterator it;
              vector<int> cammino;
              cammino.push_back(in_arrivo);
              while(in_arrivo!=in_partenza){                      // citta percorse
                   it = cammino.begin();
                   cammino.insert(it,p[in_arrivo]);
                   in_arrivo=p[in_arrivo];
              }
              cout<<"il tragitto e' \t";
              for(int i=0;i<cammino.size();i++){
                      cout<<vertici[cammino[i]].citta<<'-';
              }
              cout<<endl;
          }
         }else{
         	cout<<"Una delle due citta' o entrambe non è presente nella mappa"<<endl;
         }
	}
	 
	
//Inizio del main

int menuprincipale(){
		int scelta;
		cout<<"*********************************************"<<endl;
		cout<<"*\tGestione Archivio citta' e mappa    *"<<endl;
		cout<<"*********************************************\n"<<endl;
		cout<<"*\t1.Gestisci Archivio"<<endl;
		cout<<"*\t2.Gestisci Mappa"<<endl;
		cout<<"*\t0.Esci"<<endl;
		cout<<"\t_______________________________"<<endl;
		cout<<"\tDigitare il numero dell'opzione"<<endl;
		do{
    		cout<<"\t";	
    		cin>>scelta;
		}while(scelta<0||scelta >2);
		return scelta;
}
int menuArchivio(){
		int sub_s;
		cout<<"\nQuali operazioni si vuole effettuare sull'archivio?\n"<<endl;
		cout<<"*\t1.Immissione nuova citta'"<<endl;
		cout<<"*\t2.Modifica citta' presente"<<endl;
		cout<<"*\t3.Cancella citta' presente"<<endl;
		cout<<"*\t4.Effettua le ricerche"<<endl;
		cout<<"*\t0.Esci"<<endl;
		cout<<"\t_______________________________"<<endl;
		cout<<"\tDigitare il numero dell'opzione"<<endl;
		do{
			cin>>sub_s;
		}while(sub_s<0||sub_s>4);
		
		return sub_s;
		
}
int menuMappa(){
	int sub_s;
	cout<<"Quali operazioni si vuole effettuare sulla mappa?\n"<<endl;
	do{
		cout<<"*\t1.Aggiunta alla mappa di una nuova citta'*"<<endl;
		cout<<"*\t2.Aggiunta alla mappa di un nuovo collegamento'*"<<endl;
		cout<<"*\t3.Ricerca cammino minimo tra due città*"<<endl;
		cout<<"*\t4.Cancellazione di una citta dalla mappa*"<<endl;
		cout<<"*\t5.Cancellazione di un collegamento dalla mappa*"<<endl;
		cout<<"*\t0.Esci"<<endl;
		cout<<"\t_______________________________"<<endl;
		cout<<"\tDigitare il numero dell'opzione"<<endl;
		cin>>sub_s;
	}while(sub_s<0||sub_s>5);
	return sub_s;
}
		
int main(){
		int choose;
		int sub_menu;
		choose=menuprincipale();
		if(choose == 0)return 0;
		do{
			if(choose==1){
				Archivio nuovo;
				int n = menuArchivio();	
				switch(n){
					case 0:
						choose=menuprincipale();
						break;
					case 1:
						nuovo.immissione();
						break;
					case 2:
						nuovo.modifica(); 
						break;
					case 3:
					 	nuovo.canc();
						break;
					case 4:
						nuovo.ricerca();
						break;
					default:
						break;
				}
			}else{
				Mappa nuova;
				int n = menuMappa();
				switch(n){
					case 0:
						choose=menuprincipale();
						break;
					case 1:
						nuova.inserimento();
						break;
					case 2:
						int x;
						nuova.insertcolleg();
						break;
					case 3:
						nuova.cam_min();
						break;
					case 4:
						nuova.canc_nodo(); 
						break;
					case 5:
						nuova.canc_coll();
						break;
					default:
						break;
				}
			}			
		}while(choose!=0);
		system("pause");
		return 0;
	}		
				
			
			
			
			
			
			
			
			
