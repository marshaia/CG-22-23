#include <stdio.h>
#include "../pointHolder.h"


void planeYZ(PointHolder ph,int length, int divisions,bool facing,float distance){
    float subDivisionLen = ((float) length)/((float) divisions);
    for (int line = 0; line < divisions;line++){
        //Valores "atuais" de X e Y
        float actY = ((float) length)/2 -  ((float) line) * subDivisionLen;
        for(int col = 0; col < divisions;col++){
            float actZ = ((float) length)/2 -  ((float) col) * subDivisionLen;;

            if(facing){
                addPoint(ph,distance,actY,actZ);
                addPoint(ph,distance,actY-subDivisionLen,actZ-subDivisionLen);
                addPoint(ph,distance,actY,actZ-subDivisionLen);

                addPoint(ph,distance,actY,actZ);
                addPoint(ph,distance,actY-subDivisionLen,actZ);
                addPoint(ph,distance,actY-subDivisionLen,actZ-subDivisionLen);
            }
            else{
                addPoint(ph,distance,actY,actZ);
                addPoint(ph,distance,actY,actZ-subDivisionLen);
                addPoint(ph,distance,actY-subDivisionLen,actZ-subDivisionLen);

                addPoint(ph,distance,actY,actZ);
                addPoint(ph,distance,actY-subDivisionLen,actZ-subDivisionLen);
                addPoint(ph,distance,actY-subDivisionLen,actZ);
            }

        }
    }
}


void planeXZ(PointHolder ph,int length, int divisions,bool facing,float distance){
    float subDivisionLen = ((float) length)/((float) divisions);
    for (int line = 0; line < divisions;line++){
        //Valores "atuais" de X e Z
        float actZ = ((float) length)/2 -  ((float) line) * subDivisionLen;
        for(int col = 0; col < divisions;col++){
            float actX = ((float) length)/2 -  ((float) col) * subDivisionLen;;

            if(facing){
                addPoint(ph,actX,distance,actZ);
                addPoint(ph,actX,distance,actZ-subDivisionLen);
                addPoint(ph,actX-subDivisionLen,distance,actZ-subDivisionLen);

                addPoint(ph,actX,distance,actZ);
                addPoint(ph,actX-subDivisionLen,distance,actZ-subDivisionLen);
                addPoint(ph,actX-subDivisionLen,distance,actZ);
            }
            else{
                addPoint(ph,actX,distance,actZ);
                addPoint(ph,actX-subDivisionLen,distance,actZ-subDivisionLen);
                addPoint(ph,actX,distance,actZ-subDivisionLen);

                addPoint(ph,actX,distance,actZ);
                addPoint(ph,actX-subDivisionLen,distance,actZ);
                addPoint(ph,actX-subDivisionLen,distance,actZ-subDivisionLen);
            }

        }
    }
}

void planeXY(PointHolder ph,int length, int divisions,bool facing,float distance){
    float subDivisionLen = ((float) length)/((float) divisions);
    for (int line = 0; line < divisions;line++){
        //Valores "atuais" de X e Z
        float actY = ((float) length)/2 -  ((float) line) * subDivisionLen;
        for(int col = 0; col < divisions;col++){
            float actX = ((float) length)/2 -  ((float) col) * subDivisionLen;;

            if(facing){
                addPoint(ph,actX,actY,distance);
                addPoint(ph,actX-subDivisionLen,actY-subDivisionLen,distance);
                addPoint(ph,actX,actY-subDivisionLen,distance);

                addPoint(ph,actX,actY,distance);
                addPoint(ph,actX-subDivisionLen,actY,distance);
                addPoint(ph,actX-subDivisionLen,actY-subDivisionLen,distance);
            }
            else{
                addPoint(ph,actX,actY,distance);
                addPoint(ph,actX,actY-subDivisionLen,distance);
                addPoint(ph,actX-subDivisionLen,actY-subDivisionLen,distance);

                addPoint(ph,actX,actY,distance);
                addPoint(ph,actX-subDivisionLen,actY-subDivisionLen,distance);
                addPoint(ph,actX-subDivisionLen,actY,distance);
            }

        }
    }
}


void addGenericPlane(PointHolder ph, int length, int divisions, char axis,bool direction,float distance){

    if(axis != 'x' && axis != 'y' && axis != 'z') throw 100;

    if (axis == 'x') planeYZ(ph,length,divisions,direction,distance);
    else if(axis == 'y') planeXZ(ph,length,divisions,direction,distance);
    else if(axis == 'z') planeXY(ph,length,divisions,direction,distance);
}

void generateXZPlane(int length,int divisions,FILE* file){
    PointHolder ph = initPointHolder();
    addGenericPlane(ph,length,divisions,'y', true,0);
    printToFile(ph,file);
}