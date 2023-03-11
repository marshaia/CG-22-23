#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include "cone.cpp"
#include "cylinder.cpp"
#include "box.cpp"
#include "sphere.cpp"

void helpAndClose(int error){
    if (error == 1) printf("Invalid Shape!\n\n");
    else if (error == 2) printf("Invalid Number of arguments!\n\n");
    else if (error == 3) printf("Invalid Number!\n\n");
    else if (error == 4) printf("Invalid FileName!\n\n");
    else printf("Upsi, you need help with arguments, here:\n\n");

    printf("How to execute:\n\n");
    printf("Sphere: ./generator sphere [RADIUS] [SLICES] [STACKS] [FILENAME].3d\n");
    printf("Cube: ./generator box [LENGTH] [DIVISIONS] [FILENAME].3d\n");
    printf("Cone: ./generator cone [RADIUS] [HEIGHT] [SLICES] [STACKS] [FILENAME].3d\n");
    printf("Plane: ./generator plane [LENGTH] [DIVISIONS] [FILENAME].3d\n");
    printf("Cylinder: ./generator cylinder [RADIUS] [HEIGHT] [SLICES] [FILENAME].3d\n ");
    exit(1);
}

int main(int argc, char **argv) {

    //TEM QUE TER UMA SHAPE NO MINIMO
    if(argc < 2) helpAndClose(0);

    //VERIFICA SHAPE VÁLIDA
    int shape = -1; //codigo
    if(!strcmp(argv[1],"sphere")) shape = 1;
    else if(!strcmp(argv[1],"box")) shape = 2;
    else if(!strcmp(argv[1],"cone")) shape = 3;
    else if(!strcmp(argv[1],"plane")) shape = 4;
    else if (!strcmp(argv[1], "cylinder")) shape = 5;
    else helpAndClose(1);

    //PARA CADA SHAPE, VE SE HÁ O NUMERO CORRETO DE ARGUMENTOS
    if(shape == 1 && argc != 6) helpAndClose(2);
    else if(shape == 2 && argc != 5) helpAndClose(2);
    else if(shape == 3 && argc != 7) helpAndClose(2);
    else if(shape == 4 && argc != 5) helpAndClose(2);
    else if(shape == 5 && argc != 6) helpAndClose(2);

    //LÊ OS ARGUMENTOS/PARAMETROS DA SHAPE
    int shapeValues[4] = {-1,-1,-1,-1};
    for (int i = 2; i < argc-1;i++){
        if (sscanf(argv[i],"%d",&shapeValues[i-2]) != 1) helpAndClose(3);
        if (shapeValues[i-2] <= 0) helpAndClose(3);
    }

    //VERIFICA SE É FILE .3d E SE É VÁLIDO
    char* filename = argv[argc-1];
    int len = strlen(filename);
    if (strcmp(&filename[len-3],".3d")) helpAndClose(4); //Might not be working!
    FILE* file = fopen(filename,"w");
    if (!file) helpAndClose(4);

    //ALL READY TO GO, CALL FUNCTION IN EACH
    if (shape == 1) generateSphere(shapeValues[0],shapeValues[1],shapeValues[2],file);
    else if (shape == 2) generateBox(shapeValues[0],shapeValues[1],file);
    else if (shape == 3) generateCone(shapeValues[0],shapeValues[1],shapeValues[2],shapeValues[3],file);
    else if (shape == 4) generateXZPlane(shapeValues[0], shapeValues[1], file);
    else if (shape == 5) generateCylinder(shapeValues[0], shapeValues[1], shapeValues[2], file);

    fclose(file);
    return 0;
}