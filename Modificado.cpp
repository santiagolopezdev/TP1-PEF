#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct dato {
       char nombre[30];
       vector<vector<int>> matriz;
       int min;
       int max;
       float promedio;       
};
       
const int MAX_FILA=50;

int AbrirArchivo (struct dato *d);
int Decodificar(struct dato *d);
int ValorMaxMinProm (struct dato *d);
int GuardarArchivo (struct dato *d);
void ImprimirPorConsola(struct dato *d);

int main (void){

  dato d;
  int error=0;

  error=AbrirArchivo(&d); //Funcion que carga los datos del archivo
  if (error==1){
   cout << "\nNo se pudo abrir el archivo \n";
   return 0;
  }

  error=Decodificar(&d); //Funcion que comprime los datos del archivo
  if (error==1){
    cout << "\nFallo comprimiendo el texto";
    return 0;
  }

  //ImprimirPorConsola(&d);

  error = ValorMaxMinProm (&d);
  if(error==1){
    cout <<"\nFallo obteniendo el maximo/min/promedio";
    return 0;
  }
  error = GuardarArchivo(&d);
  if (error==1){
    cout << "\nFallo guardando el archivo";
    return 0;
  }

  return 0;
}


int AbrirArchivo(struct dato *d){
  ifstream archivo;

  cout << endl << "Ingrese el nombre de archivo: \n";
  cin >> d->nombre;
  
  archivo.open(d->nombre);
  if(!archivo){
    return 1;
  }
  string palabra;
  int contadorInterno = 0;
  vector<int>* temp = new vector<int>;

  while (archivo >> palabra){
    contadorInterno++;
    int num = stoi(palabra);
    if(contadorInterno<=50){
      temp->push_back(num);
    }
    else{
      contadorInterno = 1;
      d->matriz.push_back(*temp);
      temp = new vector<int>;
      temp->push_back(num); 
    }
  }
  if(temp->size()!=0){
    d->matriz.push_back(*temp);
  }
  return 0;
}

int ValorMaxMinProm(struct dato *d){
  int cantElem = 0;
  d->max = d->matriz[0][0];
  d->min = d->matriz[0][0];
  d->promedio = 0;
  
  for (int i=0; i<d->matriz.size(); i++){
    for (int j=0; j<d->matriz[i].size(); j++){
      if (d->max < d->matriz[i][j]){
        d->max = d->matriz[i][j];
      }
      if (d->min > d->matriz[i][j]){
        d->min = d->matriz[i][j];
      }
      d->promedio = d->promedio + d->matriz[i][j];
      cantElem++;
    }
  }
   cout<<"La matriz tiene " << cantElem <<" Elementos"<<endl;
  d->promedio = d->promedio/cantElem;
  cout << "Promedio: " << d->promedio << " || Maximo:" << d->max << " || Minimo:" << d->min;

  return 0;  
}

int GuardarArchivo(struct dato *d){  
  char nombre[30];
  ofstream guarda;
  cout << "\nComo guardar el archivo "; 
  cin >> nombre;
  guarda.open(nombre);
  for (int i=0; i<d->matriz.size(); i++){
    for (int j=0; j<d->matriz[i].size(); j++){
      guarda << d->matriz[i][j] << " ";
    } 
    guarda << "\n";
  }
  guarda.close();
  
  return 0;    
}

void ImprimirPorConsola(struct dato *d){
  cout<<"La matriz tiene " << d->matriz.size()<<" filas"<<endl;
  for (int i = 0; i < d->matriz.size(); i++){
    for (int j = 0; j < d->matriz[i].size(); j++){
        cout << d->matriz[i][j]<<" ";
    }
    cout << endl;
  }
}

int Decodificar(struct dato *d){
  vector< vector<int> > decodificado;
  
  for (int i = 0; i < d->matriz.size(); i++){
    int valorPrevio= d->matriz[i][0];
    for (int j = 1; j < d->matriz[i].size(); j++){
      d->matriz[i][j] = valorPrevio + d->matriz[i][j];
      valorPrevio = d->matriz[i][j];
    }
  }
  return 0;
}