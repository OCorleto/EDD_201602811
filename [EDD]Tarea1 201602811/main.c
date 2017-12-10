#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
    int valor;
    struct nodo *siguiente;
    struct nodo *anterior;
}Nodo;
Nodo *Crear(int valor);
void Insertar(Nodo **primero,int valor);
void Mostrar(Nodo *primero);
void Eliminar(Nodo **primero,int valor);

Nodo *Crear(int valor){
    Nodo *nuevo=NULL;
    nuevo=(Nodo*)malloc(sizeof(Nodo));
    if(nuevo!=NULL){
        nuevo->valor=valor;
        nuevo->siguiente=NULL;
        nuevo->anterior=NULL;
    }
    return nuevo;
}

void Insertar(Nodo **primero,int valor){
    Nodo *nuevo=NULL;
    nuevo=Crear(valor);
    if(nuevo!=NULL){
        nuevo->siguiente=*primero;
        nuevo->anterior=NULL;
        if(*primero!=NULL){
            (*primero)->anterior=nuevo;
        }
        *primero=nuevo;
    }
}

void Mostrar(Nodo *primero){
    Nodo *auxiliar= primero;
    while(auxiliar!=NULL){
        printf("valor: %d\n",auxiliar->valor);
        auxiliar=auxiliar->siguiente;
    }
}

void Eliminar(Nodo **primero,int valor){
    int band=0,cont=0;

    while(band==0){
    cont=0;
    Nodo *actual=*primero;
    Nodo *viejo=NULL;
    Nodo *nuevo=NULL;
        while((actual!=NULL)&&(cont==0)){
        if(actual->valor==valor){
            if(actual==*primero){
                *primero=actual->siguiente;
                if(actual->siguiente!=NULL){
                    actual->siguiente->anterior=NULL;
                }
            }

            else{
                if(actual->siguiente==NULL){
                    viejo=actual->anterior;
                    actual->anterior=NULL;
                    viejo->siguiente=NULL;
                }
                else{
                    viejo=actual->anterior;
                    actual->anterior=NULL;
                    nuevo=actual->siguiente;
                    actual->siguiente=NULL;
                    viejo->siguiente=nuevo;
                    nuevo->anterior=viejo;
                }
            }
            free(actual);

            cont=1;
        }
        actual = actual->siguiente;
        }
        if(actual==NULL){band=1;}
    }
}

void inicio(){
    printf("MENU\n");
    printf("\t 1.\tIngresar\n");
    printf("\t 2.\tMostrar\n");
    printf("\t 3.\tEliminar\n");
    printf("\t otro.\tSALIR\n");
}


int main()
{
    int opcion=0;
    int dato;
    Nodo *primero=NULL;
    while(opcion<4){
        system("cls");
        inicio();
        printf("Ingrese su opcion: ");
        scanf("%i",&opcion);
        system("cls");
        switch(opcion){
        case 1:
            printf("Ingresar\n");
            printf("Ingrese el valor: ");
            scanf("%i",&dato);
            Insertar(&primero,dato);
            break;
        case 2:
            printf("Mostrar\n");
            Mostrar(primero);
            break;
        case 3:
            printf("Eliminar\n");
            printf("Ingrese el valor: ");
            scanf("%i",&dato);
            Eliminar(&primero,dato);
            break;
        default:
            printf("SALIENDO DEL PROGRAMA \n");
            break;
        }
        system("pause");
    }
    return 0;

}

