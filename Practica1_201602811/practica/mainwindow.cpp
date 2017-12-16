#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSpinBox>
#include <QDebug>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <ostream>
#include <QGraphicsPixmapItem>
#include <iostream>
using namespace std;
//Variables
int turnos=0;
int contaviones=0;
int contpasajeros=0;
int contmaletas=0;
int contescritorios=64;
int contarestaciones=0;
int contadocs=0;
//Generador de Numero aleartorios
int Random(int low,int high){
    return qrand() %((high+1)-low)+low;
}

//Aviones
struct Avion
{
    QString nombre;
    int tipo;
    int pasajero;
    int desbordaje;
    int mantenimiento;

    struct Avion *siguiente;
    struct Avion *anterior;
}*avionprimero,*avionultimo=NULL;
struct Pasajero{
    QString nombre;
    int maleta;
    int documento;
    int registro;

    struct Pasajero *siguiente;
}*pasajeroprimero,*pasajeroultimo=NULL;
struct Maleta
{
    QString nombre;
    Maleta *siguiente;
    Maleta *anterior;
}*maletaprimero,*maletaultimo;
struct  Persona{
    QString nombre;
    int turnos;
    int  maletas;
    int docs;
    Persona *siguiente;
    Persona *anterior;
};

struct Documentos{
    QString nombre;
    Documentos *siguiente;
};

struct Escritorio{
    QString nombre;
    Persona *primerapersona;
    Persona *ultimapersona;
    Documentos *docprimero;
    Documentos *docultimo;
    Escritorio *siguiente;
    Escritorio *anterior;
    int libre;
}*escritorioprimero,*escritorioultimo;
struct ColaAvion{
    QString nombre;
    int turnos;
    ColaAvion *siguiente;
}*primeravionencola,*ultimoavionencola;
struct Mantenimiento{
    QString nombre;
    QString avion;
    int turnoslibre;
    int libre;
    Mantenimiento *siguiente;
}*mantprimero,*mantultimo;
void DatosAvion(int tipo,int pasajero,int desbordaje, int mantenimiento){
    contaviones++;
    Avion *nuevo=new Avion();
    nuevo->tipo=tipo;
    nuevo->nombre= QString("avion%1").arg(contaviones);
    nuevo->pasajero=pasajero;
    nuevo->desbordaje=desbordaje;
    nuevo->mantenimiento=mantenimiento;
    nuevo->siguiente=NULL;
    if(avionultimo!=NULL){
        avionultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        avionultimo=nuevo;
    }
    else{
        avionprimero=avionultimo=nuevo;
    }

}
void CrearAviones(){
    int pasajero;
    int desbordaje;
    int mantenimiento;
    int tipo=Random(1,3);
    switch (tipo) {
    case 1:
        pasajero=Random(5,10);
        desbordaje=1;
        mantenimiento=Random(1,3);
        break;
    case 2:
        pasajero=Random(15,25);
        desbordaje=2;
        mantenimiento=Random(2,4);
        break;
    default:
        pasajero=Random(30,40);
        desbordaje=3;
        mantenimiento=Random(3,6);
        break;
    }
    DatosAvion(tipo,pasajero,desbordaje,mantenimiento);
}

void MostrarAvion(){
    Avion *aux =new Avion();
    if(avionultimo==NULL){qDebug()<<"cola vacia";return;}
    aux=avionprimero;
    qDebug()<<"Los datos son: ";
    while(aux!=NULL){
        qDebug()<<aux->nombre<<aux->tipo<<aux->pasajero<<aux->desbordaje<<aux->mantenimiento;
        aux=aux->siguiente;
    }
}
void EliminarAvion(){
    Avion *aux=new Avion();
    if(avionprimero!=NULL){
        aux=avionprimero;
        avionprimero=aux->siguiente;
        free(aux);
        if(avionprimero==NULL){
            aux=NULL;
            avionultimo=NULL;
        }
    }
}
//Pasajeros

void NuevoPasajero(){
    contpasajeros++;
    Pasajero *nuevo=new Pasajero();
    nuevo->maleta=Random(1,4);
    nuevo->nombre=QString("pasajero%1").arg(contpasajeros);
    nuevo->documento=Random(1,10);
    nuevo->registro=Random(1,3);
    if(pasajeroultimo!=NULL){
        pasajeroultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        pasajeroultimo=nuevo;
    }
    else{
        pasajeroprimero=pasajeroultimo=nuevo;
    }
}
void MostrarPasajeros(){
    Pasajero *aux =new Pasajero();
    if(pasajeroultimo==NULL){qDebug()<<"cola vacia";return;}
    aux=pasajeroprimero;
    qDebug()<<"Los datos son: ";
    while(aux!=NULL){
        qDebug()<<aux->nombre<<aux->maleta<<aux->documento<<aux->registro;
        aux=aux->siguiente;
    }
}
void EliminarPasajero(){
    Pasajero *aux=new Pasajero();
    if(pasajeroprimero!=NULL){
        aux=pasajeroprimero;
        pasajeroprimero=aux->siguiente;
        free(aux);
        if(pasajeroprimero==NULL){
            aux=NULL;
            pasajeroultimo=NULL;
        }
    }
}

void IngresarMaleta(){
    contmaletas++;
    Maleta *nuevo =new Maleta();
    nuevo->nombre= QString("maleta%1").arg(contmaletas);
    if(maletaprimero!=NULL){
        maletaultimo->siguiente=nuevo;
        nuevo->anterior=maletaultimo;
        nuevo->siguiente=maletaprimero;
        maletaultimo=nuevo;
    }
    else{
        maletaprimero=nuevo;
        maletaultimo=nuevo;
        maletaprimero->siguiente=maletaprimero;
        maletaprimero->anterior=maletaultimo;
    }
}

void MostrarMaletas(){
    Maleta *aux=new Maleta();
    aux=maletaprimero;
    if(maletaprimero!=NULL){
        do{
            qDebug()<<aux->nombre<<",";
            aux=aux->siguiente;
        }
        while(aux!=maletaprimero);
    }
}

void EliminarMaletas(){
    Maleta *aux=new Maleta();
    aux=maletaprimero;
    if(maletaprimero!=NULL){
        maletaprimero=maletaprimero->siguiente;
        maletaprimero->anterior=maletaultimo;
        maletaultimo->siguiente=maletaprimero;
        free(aux);
    }
}

void IngresarDocs(Escritorio *escritorio){
    contadocs++;
    Documentos *nuevo=new Documentos();
    nuevo->nombre=QString("documento%1").arg(contadocs);
    if(escritorio->docultimo!=NULL){
        escritorio->docultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        escritorio->docultimo=nuevo;
    }
    else{
        escritorio->docprimero=escritorio->docultimo=nuevo;
    }
}
void EliminarDocs(Escritorio *escritorio){
    Documentos *aux=new Documentos();
    if(escritorio->docprimero!=NULL){
        aux=escritorio->docprimero;
        escritorio->docprimero=aux->siguiente;
        free(aux);
        if(escritorio->docprimero==NULL){
            aux=NULL;
            escritorio->docprimero=NULL;
        }
    }
}
void InsetarPasajerosAlaCola(int turns,QString nombre,int  maletas,int docs){
    int personasenfila=0;
    Escritorio *escritorio =new Escritorio();
    Persona *persona=new Persona;
    escritorio=escritorioprimero;
    while(escritorio!=NULL){
        personasenfila=0;
        persona=escritorio->primerapersona;
        while(persona!=NULL){
            personasenfila++;
            persona=persona->siguiente;
        }
        if(personasenfila<10){
            Persona *nuevo=new Persona();
            nuevo->nombre=nombre;
            nuevo->turnos=turns;
            nuevo->maletas=maletas;
            nuevo->docs=docs;
            if(escritorio->ultimapersona!=NULL){
                escritorio->ultimapersona->siguiente=nuevo;
                nuevo->siguiente=NULL;
                escritorio->ultimapersona=nuevo;
            }
            else{
                escritorio->primerapersona=escritorio->ultimapersona=nuevo;
            }
            EliminarPasajero();
            break;
        }
        else{
            escritorio=escritorio->siguiente;
        }
    }
}

void CrearEscritorios(){
    contescritorios++;
    Escritorio *nuevo=new Escritorio();
    nuevo->nombre=QString("escritorio%1").arg(char(contescritorios));
    nuevo->libre=0;
    if(escritorioprimero==NULL){
        escritorioprimero=nuevo;
        escritorioprimero->siguiente=NULL;
        escritorioprimero->anterior=NULL;
        escritorioultimo=escritorioprimero;
    }else{
        escritorioultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        nuevo->anterior=escritorioultimo;
        escritorioultimo=nuevo;
    }
}
void ColaEliminarPersona(Escritorio *escritorio){
    Persona *aux=new Persona();
    if(escritorio->primerapersona!=NULL){
        aux=escritorio->primerapersona;
        escritorio->primerapersona=aux->siguiente;
        free(aux);
        if(escritorio->primerapersona==NULL){
            aux=NULL;
            escritorio->ultimapersona=NULL;
        }
    }
}
QString grpah;

//Mantenimiento


void CrearEstacionesMantenimiento(){
    contarestaciones++;
    Mantenimiento *nuevo=new Mantenimiento();
    nuevo->nombre=QString("estacion%1").arg(contarestaciones);
    nuevo->libre=0;
    if(mantultimo!=NULL){
        mantultimo->siguiente=nuevo;
        nuevo->siguiente=NULL;
        mantultimo=nuevo;
    }
    else{
        mantprimero=mantultimo=nuevo;
    }
}

void InsertarColaAvion(QString nombre,int turnos){
    ColaAvion *nuevo=new ColaAvion();
    nuevo->nombre=nombre;
    nuevo->turnos=turnos;
    if(ultimoavionencola!=NULL){
        ultimoavionencola->siguiente=nuevo;
        nuevo->siguiente=NULL;
        ultimoavionencola=nuevo;
    }
    else{
        primeravionencola=ultimoavionencola=nuevo;
    }
    qDebug()<<"Insertados";
}


void ColaEliminarAvion(){
    ColaAvion *aux=new ColaAvion();
    if(primeravionencola!=NULL){
        aux=primeravionencola;
        primeravionencola=aux->siguiente;
        free(aux);
        if(primeravionencola==NULL){
            aux=NULL;
            ultimoavionencola=NULL;
        }
    }
}

void LlenarEstacionesdeMantenimiento(){
    int band=0;
    Mantenimiento *estacion=new Mantenimiento();
    Mantenimiento *aux=new Mantenimiento();
    ColaAvion *avion=new ColaAvion();
    avion=primeravionencola;
    aux=mantprimero;
    while(aux!=NULL){
        if(aux->libre==0){
            estacion=aux;
            band=1;
            break;
        }
        aux=aux->siguiente;
    }
    if((band==1)&&(avion!=NULL)){

        qDebug()<<"Estacion usada";
        estacion->avion=avion->nombre;
        estacion->turnoslibre=avion->turnos;
        estacion->libre=1;
        ColaEliminarAvion();
    }
    else{qDebug()<<"No ke pasa Estacion no usada";}
}

void MostrarEstaciones(){
    Mantenimiento *aux =new Mantenimiento();
    if(mantultimo==NULL){qDebug()<<"cola vacia";return;}
    aux=mantprimero;
    qDebug()<<"Los datos son: ";
    while(aux!=NULL){
        qDebug()<<aux->nombre<<aux->avion<<aux->turnoslibre;
        aux=aux->siguiente;
    }
}


void MostrarColaPersonas(){
    Escritorio *esc=new Escritorio();
    Persona *aux =new Persona();
    esc=escritorioprimero;
    while(esc!=NULL){
        if(esc->primerapersona==NULL){qDebug()<<"cola vacia";return;}
        aux=esc->primerapersona;
        qDebug()<<"Los datos son: ";
        while(aux!=NULL){
            qDebug()<<aux->nombre<<aux->turnos;
            aux=aux->siguiente;
        }
        esc=esc->siguiente;
    }
}


void MostrarCola(){
    ColaAvion *aux =new ColaAvion();
    if(ultimoavionencola==NULL){qDebug()<<"cola vacia";return;}
    aux=primeravionencola;
    qDebug()<<"Los datos son: ";
    while(aux!=NULL){
        qDebug()<<aux->nombre<<aux->turnos;
        aux=aux->siguiente;
    }
}


//Graficar
QString DotEditor(int tam){
    QString StringDotEditor="";
    QString aviontext="";
    QString pasajerotext="";
    QString estaciontext="";
    QString colatext="";
    QString maletatext="";
    QString escritoriotext="";
    QString desabordajetext="";
    Avion *avion=new Avion();
    Pasajero *pasajero=new Pasajero();
    Maleta *maleta=new Maleta();
    Mantenimiento *estacion=new Mantenimiento();
    ColaAvion *colaavion=new ColaAvion();
    Escritorio *escritorio=new Escritorio();
    Persona *persona=new Persona();
    StringDotEditor=QString("digraph G { dpi=%1; ").arg(tam);
    //Avion
    aviontext=("subgraph clusterAviones{label = Avion;");
    avion=avionprimero;
    while(avion!=NULL){
        if(avion->siguiente==NULL){aviontext=QString("%1 %2;").arg(aviontext).arg(avion->nombre);}
        else{
            aviontext=QString("%1 %2->%3;").arg(aviontext).arg(avion->nombre).arg(avion->siguiente->nombre);
            aviontext=QString("%1 %2->%3;").arg(aviontext).arg(avion->siguiente->nombre).arg(avion->nombre);
        }
        avion=avion->siguiente;
    }
    aviontext=QString("%1}").arg(aviontext);
    //Pasajero
    pasajerotext=("subgraph clusterPasajero{label=Pasajeros;");
    pasajero=pasajeroprimero;
    while(pasajero!=NULL){
        if(pasajero->siguiente==NULL){pasajerotext=QString("%1 %2;").arg(pasajerotext).arg(pasajero->nombre);}
        else{
            pasajerotext=QString("%1 %2->%3;").arg(pasajerotext).arg(pasajero->nombre).arg(pasajero->siguiente->nombre);
        }
        pasajero=pasajero->siguiente;
    }
    pasajerotext=QString("%1}").arg(pasajerotext);
    //Escritorio
    escritoriotext=("subgraph clusterEscritorio{label=Escritorios;");
    escritorio=escritorioprimero;
    while(escritorio!=NULL){
        if(escritorio->siguiente==NULL){escritoriotext=QString("%1 %2;").arg(escritoriotext).arg(escritorio->nombre);}
        else{
            escritoriotext=QString("%1 %2->%3;").arg(escritoriotext).arg(escritorio->nombre).arg(escritorio->siguiente->nombre);
            escritoriotext=QString("%1 %2->%3;").arg(escritoriotext).arg(escritorio->siguiente->nombre).arg(escritorio->nombre);
        }
        escritorio=escritorio->siguiente;
    }
    escritoriotext=QString("%1}").arg(escritoriotext);
    //Pasajeros Desabordados
    escritorio=escritorioprimero;
    while(escritorio!=NULL){
        persona=escritorio->primerapersona;
        desabordajetext=QString("%1 subgraph clusterCola%2{label=%3;").arg(desabordajetext).arg(escritorio->nombre).arg(escritorio->nombre);
        while(persona!=NULL){
            if(persona==escritorio->primerapersona){
                desabordajetext=QString("%1 %2->%3;").arg(desabordajetext).arg(escritorio->nombre).arg(persona->nombre);
            }
            if(persona->siguiente==NULL){
                desabordajetext=QString("%1 %2;").arg(desabordajetext).arg(persona->nombre);
            }
            else{
                desabordajetext=QString("%1 %2->%3;").arg(desabordajetext).arg(persona->nombre).arg(persona->siguiente->nombre);
            }
            persona=persona->siguiente;
        }
        desabordajetext=QString("%1}").arg(desabordajetext);
        escritorio=escritorio->siguiente;
    }

    //Estaciones
    estaciontext=("subgraph clusterEstaciones{ label=Mantenimiento");
    estacion=mantprimero;
    while(estacion!=NULL){
        if(estacion->siguiente==NULL){estaciontext=QString("%1 %2;").arg(estaciontext).arg(estacion->nombre);}
        else{
            estaciontext=QString("%1 %2->%3;").arg(estaciontext).arg(estacion->nombre).arg(estacion->siguiente->nombre);
        }
        estacion=estacion->siguiente;
    }
    estaciontext=QString("%1}").arg(estaciontext);
    //ColaAviones
    colatext=("subgraph clusterCola{ label= ColaAviones");
    colaavion=primeravionencola;
    while(colaavion!=NULL){
        if(colaavion->siguiente==NULL){colatext=QString("%1 %2;").arg(colatext).arg(colaavion->nombre);}
        else{
            colatext=QString("%1 %2->%3;").arg(colatext).arg(colaavion->nombre).arg(colaavion->siguiente->nombre);
        }
        colaavion=colaavion->siguiente;
    }
    colatext=QString("%1}").arg(colatext);
    //Maletas
    maletatext=("subgraph clusterMaleta{ label=Maletas");
    maleta=maletaprimero;
    if(maleta!=NULL){
        do{
            if(maleta->siguiente!=NULL){
                maletatext=QString("%1 %2->%3;").arg(maletatext).arg(maleta->nombre).arg(maleta->siguiente->nombre);
                maletatext=QString("%1 %2->%3;").arg(maletatext).arg(maleta->siguiente->nombre).arg(maleta->nombre);
                maleta=maleta->siguiente;
            }
        }while(maleta!=maletaprimero);

    }
    maletatext=QString("%1}").arg(maletatext);
    StringDotEditor=QString("%1 %2 %3 %4 %5 %6 %7 %8}").arg(StringDotEditor).arg(aviontext).arg(pasajerotext).arg(maletatext).arg(escritoriotext).arg(desabordajetext).arg(estaciontext).arg(colatext);
    StringDotEditor=StringDotEditor.remove("\"");
    return StringDotEditor;
}






//Interfaz Grafica
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString consola="";\
    int desabordo=0;
    QString aviondesabordando="";
    int avanzar=0;
    int av=0;
    int pas=0;
    int mal=0;
    int esc=0;
    int est=0;
    int ingdoc=0;
    int maletasasacar=0;
    int pasajrosdesabordando=0;
    int docs=0;
    turnos++;
    Avion *avion=new Avion();
    Escritorio *escritorio=new Escritorio();
    Pasajero *pasajero=new Pasajero();
    Mantenimiento *estacion=new Mantenimiento();
    Persona *persona=new Persona();
    Documentos *documento=new Documentos();
    if(ui->spinBox->isEnabled()){
        av=ui->spinBox->value();
        est=ui->spinBox_4->value();
        esc=ui->spinBox_3->value();
        ui->spinBox_2->setMinimum(0);
        avanzar=1;
        while(av>0){
            CrearAviones();
            av--;
        }

        while(est>0){
            CrearEstacionesMantenimiento();
            est--;
        }
        while(esc>0){
            CrearEscritorios();
            esc--;
        }
    }
    if(avanzar=1){
        if(ui->spinBox_2->value()>0){
            ui->spinBox->setEnabled(false);
            ui->spinBox_2->setEnabled(false);
            ui->spinBox_3->setEnabled(false);
            ui->spinBox_4->setEnabled(false);
            avion=avionprimero;
            int valor=ui->spinBox_2->value()-1;
            ui->spinBox_2->setValue(valor);
            if(avion!=NULL){
                MostrarAvion();
                avion->desbordaje=avion->desbordaje-1;
                if(avion->desbordaje==0){
                    aviondesabordando=avion->nombre;
                    desabordo=1;
                    InsertarColaAvion(avion->nombre,avion->mantenimiento);
                    MostrarCola();
                    LlenarEstacionesdeMantenimiento();
                    MostrarEstaciones();
                    pas=avion->pasajero;
                    pasajrosdesabordando=avion->pasajero;
                    EliminarAvion();
                    while (pas>0) {
                        NuevoPasajero();
                        pasajero=pasajeroultimo;
                        mal=pasajero->maleta;
                        while(mal>0){
                            IngresarMaleta();
                            mal--;
                        }
                        InsetarPasajerosAlaCola(pasajero->registro,pasajero->nombre,pasajero->maleta,pasajero->documento);

                        pas--;
                    }
                    MostrarColaPersonas();
                }else{desabordo=0;}
            }
            escritorio=escritorioprimero;
            while(escritorio!=NULL){
                if(escritorio->primerapersona!=NULL){
                    ingdoc=escritorio->primerapersona->docs;
                    while(ingdoc>0){
                        IngresarDocs(escritorio);
                        ingdoc--;
                    }
                    contadocs=0;

                }
                escritorio=escritorio->siguiente;
            }
            escritorio=escritorioprimero;
            while(escritorio!=NULL){
                persona=escritorio->primerapersona;
                if(persona!=NULL){
                    qDebug()<<persona->nombre<<persona->turnos;
                    persona->turnos=persona->turnos-1;
                    if(persona->turnos==0){
                        ingdoc=persona->docs;
                        maletasasacar=persona->maletas;
                        qDebug()<<"Tiene"<<maletasasacar;
                        while(maletasasacar>0){
                            EliminarMaletas();
                            maletasasacar--;
                        }
                        documento=escritorio->docprimero;
                        while(documento!=NULL){
                            EliminarDocs(escritorio);
                            documento=documento->siguiente;
                        }
                        ColaEliminarPersona(escritorio);
                        if(pasajeroprimero!=NULL)
                        {InsetarPasajerosAlaCola(pasajeroprimero->registro,pasajeroprimero->nombre,pasajeroprimero->maleta,pasajeroprimero->documento);}
                    }
                }
                escritorio=escritorio->siguiente;
            }
            MostrarColaPersonas();
            estacion=mantprimero;
            while(estacion!=NULL){
                estacion->turnoslibre=estacion->turnoslibre-1;
                if(estacion->turnoslibre==0){estacion->libre=0;}
                else{estacion->turnoslibre=1;}
                LlenarEstacionesdeMantenimiento();
                estacion=estacion->siguiente;
            }
            MostrarPasajeros();

    }  else{ui->pushButton->setEnabled(false);MostrarEstaciones(); MostrarMaletas();}
    }
    int tam=80;
    consola=QString("Turno %1 \n").arg(turnos);
    consola=QString("%1 **************** \n").arg(consola);
    avion=avionprimero;
    if(avion!=NULL){consola=QString("%1 Arribo %2 \n").arg(consola).arg(avion->nombre);
    consola=QString("%1 Turnos restantes %2 \n").arg(consola).arg(avion->desbordaje);}
    else{consola=QString("%1 Arribo Ninguno \n").arg(consola);
    consola=QString("%1 Turnos Desabordaje 0 \n").arg(consola);}
    if(desabordo=1){
        consola=QString("%1 Desabordaje %2 \n").arg(consola).arg(aviondesabordando);
        consola=QString("%1 Pasajeros %2 \n").arg(consola).arg(pasajrosdesabordando);
    }
    consola=QString("%1 **************************************** \n").arg(consola);
    consola=QString("%1 +++Escritorios de registro+++ \n").arg(consola);
    escritorio=escritorioprimero;
    while(escritorio!=NULL){
        persona=escritorio->primerapersona;
        if(persona==NULL){
            consola=QString("%1 %2: libre \n").arg(consola).arg(escritorio->nombre);
            consola=QString("%1 \t Pasajero atendido: ninguno \n").arg(consola);
            consola=QString("%1 \t Turnos restantes: 0 \n").arg(consola);
            consola=QString("%1 \t Documentos: 0 \n").arg(consola);

        }
        else{
            consola=QString("%1 %2: ocupado \n").arg(consola).arg(escritorio->nombre);
            consola=QString("%1 \t Pasajero atendido: %2 \n").arg(consola).arg(persona->nombre);
            consola=QString("%1 \t Turnos restantes: %2 \n").arg(consola).arg(persona->turnos);
            consola=QString("%1 \t Documentos: %2 \n").arg(consola).arg(persona->docs);
        }
        escritorio=escritorio->siguiente;
    }
    consola=QString("%1 **************************************** \n").arg(consola);
    consola=QString("%1 +++Estaciones de Servicio+++ \n").arg(consola);
    estacion=mantprimero;
    while(estacion!=NULL){
        if(estacion->libre==0){
            consola=QString("%1 %2: libre \n").arg(consola).arg(estacion->nombre);
            consola=QString("%1 \t Avion atendido: ninguno \n").arg(consola);
            consola=QString("%1 \t Turnos restantes: 0 \n").arg(consola);
        }
        else {
            consola=QString("%1 %2: ocupado \n").arg(consola).arg(estacion->nombre);
            consola=QString("%1 \t Avion atendido: %2 \n").arg(consola).arg(estacion->avion);
            consola=QString("%1 \t Turnos restantes: %2 \n").arg(consola).arg(estacion->turnoslibre);
        }
        estacion=estacion->siguiente;
    }
    consola=QString("%1 **************************************** \n").arg(consola);
    int maletasdentro=0;
    Maleta *aux=new Maleta();
    aux=maletaprimero;
    maletasdentro=0;
    if(aux!=NULL){
        do{
            maletasdentro++;
            if(aux->siguiente!=NULL){aux=aux->siguiente;}
        }
        while(aux!=maletaprimero);
    }

    aux=maletaprimero;
    if(aux==NULL){maletasdentro=0;}
    consola=QString("%1 Cantidad de maletas en el sistema:    %2 \n").arg(consola).arg(maletasdentro);
    ui->textEdit->setText("");
    ui->textEdit->setText(consola);
    if(maletasdentro>200){
        if(maletasdentro>300){tam=15;}
        else{tam=30;}
    }
    else{tam=80;}
    try{
        ofstream fs("C:\\Users\\usuario\\Documents\\USAC\\EDD\\practica\\Graph\\dot.dot ");
        fs<<DotEditor(tam).toStdString()<<endl;
        fs.close();
        system("dot -Tpng C:\\Users\\usuario\\Documents\\USAC\\EDD\\practica\\Graph\\dot.dot -o C:\\Users\\usuario\\Documents\\USAC\\EDD\\practica\\Graph\\dot.png");
        imageObject = new QImage();
        imageObject->load("C:\\Users\\usuario\\Documents\\USAC\\EDD\\practica\\Graph\\dot.png");
        image = QPixmap::fromImage(*imageObject);
        scene = new QGraphicsScene(this);
        scene->addPixmap(image);
        scene->setSceneRect(image.rect());
        ui->graphicsView->setScene(scene);
    }
    catch(exception e){}
}



void MainWindow::on_pushButton_2_clicked()
{
    EliminarMaletas();
    MostrarMaletas();



}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    ui->spinBox_2->setMinimum(ui->spinBox->text().toInt());
}
