#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tarea{
    char nombre[50];
    int estado;
    char fecha[20];
    char materia[20];
};

void menu(){
    struct tarea tareas[10] = {};
    int espacio_libre = 0, opc = 0;
    char busqueda[50];
    do{
        for(int i = 0; i<10; i++){
            if(tareas[i].estado == 0){
                espacio_libre = i;
                break;
            }
        }
        limpiarPantalla();
        printf("GESTOR DE TAREAS\n\n");
        printf("1- Agregar una nueva tarea\n2- Marcar una tarea como completada\n3- "
               "Listar todas las tareas pendientes\n4- Listar todas las tareas\n5- Buscar\n6- Salir\n\nSeleccione una opcion: ");
        scanf("%i", &opc);
        switch(opc){
            case 1:
                agregar_tarea(&tareas[espacio_libre]);
                break;
            case 2:
                marcar_tarea(&tareas);
                break;
            case 3:
                listar_pendientes(&tareas);
                break;
            case 4:
                listar_todas(&tareas);
                break;
            case 5:
                limpiarPantalla();
                char busqueda[50] = {};
                int contador = 0;
                printf("Buscar: ");
                fflush(stdin);
                fgets(busqueda, 50, stdin);
                if ((strlen(busqueda) > 0) && (busqueda[strlen(busqueda) - 1] == '\n')){
                    busqueda[strlen(busqueda) - 1] = '\0';
                }
                buscar(&tareas, &busqueda, contador);
                break;
            case 6:
                break;
            default:
                limpiarPantalla();
                printf("Seleccione una opcion correcta\n");
                pausarPantalla();
                break;
        }
    }while(opc != 6);
}

void agregar_tarea(struct tarea *tareas){
    limpiarPantalla();
    printf("Ingrese el nombre de la tarea: ");
    fflush(stdin);
    fgets(tareas->nombre, sizeof(tareas->nombre), stdin);
    if ((strlen(tareas->nombre) > 0) && (tareas->nombre[strlen(tareas->nombre) - 1] == '\n')){
        tareas->nombre[strlen(tareas->nombre) - 1] = '\0';
    }
    tareas->estado = 1;
    printf("\nIngrese la fecha de entrega (dd/mm/aaaa): ");
    scanf("%s", tareas->fecha);
    printf("\nIngrese la materia a la que pertenece: ");
    scanf("%s", tareas->materia);
    limpiarPantalla();
    printf("Tarea registrada con exito\n");
    pausarPantalla();
}

void marcar_tarea(struct tarea *tareas){
    limpiarPantalla();
    int seleccion = 0, contador = 0;
    for(int x = 0; x<10; x++){
        if(tareas[x].estado == 1){
            printf("%i. Nombre:%s\t", x+1, tareas[x].nombre);
            printf("Estado: ");
            if(tareas[x].estado == 1){
                printf("Pendiente\t");
            }else{
                printf("Completada\t");
            }
            printf("Fecha de entrega: %s\t", tareas[x].fecha);
            printf("Materia: %s\n", tareas[x].materia);
            contador++;
        }
    }
    printf("Seleccione la tarea que quiera marcar como completada: ");
    while(true){
        scanf("%i", &seleccion);
        if(seleccion <= contador){
            break;
        }else{
            printf("\nIngrese una opcion valida: ");
        }
    }
    seleccion--;
    tareas[seleccion].estado = 2;
    printf("Tarea marcada como completada\n");
    pausarPantalla();
}

void listar_pendientes(struct tarea *tareas){
    limpiarPantalla();
    for(int x = 0; x<10; x++){
        if(tareas[x].estado == 1){
            printf("Nombre:%s\t", tareas[x].nombre);
            printf("Estado: ");
            if(tareas[x].estado == 1){
                printf("Pendiente\t");
            }else{
                printf("Completada\t");
            }
            printf("Fecha de entrega: %s\t", tareas[x].fecha);
            printf("Materia: %s\n", tareas[x].materia);
        }
    }
    pausarPantalla();
}

void listar_todas(struct tarea *tareas){
    limpiarPantalla();
    for(int x = 0; x<10; x++){
        if(tareas[x].estado != 0){
            printf("Nombre:%s\t", tareas[x].nombre);
            printf("Estado: ");
            if(tareas[x].estado == 1){
                printf("Pendiente\t");
            }else{
                printf("Completada\t");
            }
            printf("Fecha de entrega: %s\t", tareas[x].fecha);
            printf("Materia: %s\n", tareas[x].materia);
        }
    }
    pausarPantalla();
}

void buscar(struct tarea *tareas, char *busqueda, int contador){
    if(strstr(tareas->nombre, busqueda) != NULL && tareas->estado != 0){
        printf("Nombre:%s\t", tareas->nombre);
        printf("Estado: ");
        if(tareas->estado == 1){
            printf("Pendiente\t");
        }else{
            printf("Completada\t");
        }
        printf("Fecha de entrega: %s\t", tareas->fecha);
        printf("Materia: %s\n", tareas->materia);
    }
    if(contador<10){
        buscar(tareas + 1, busqueda, contador + 1);
    }else{
        pausarPantalla();
    }
}

void limpiarPantalla(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausarPantalla(){
    printf("\nPresione ENTER para continuar...");
    fflush(stdin);
    getchar();
}

#endif // FUNCIONES_H_INCLUDED
