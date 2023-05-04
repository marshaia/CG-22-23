#include <math.h>
#include "pointHolder.h"


void generateSphere(int radius, int slices, int stacks,FILE* file){
    PointHolder ph = initPointHolder();

    float subAlpha = M_PI * 2 / ((float) slices);
    float subBeta = M_PI / ((float) stacks);
    float delta = (M_PI / ((float) 2));

    for(int actSlice = 0; actSlice < slices; actSlice++){
        for(int actStack = 0; actStack < stacks;actStack++){
            float p1X = radius * cos(subBeta * actStack - delta ) * sin(subAlpha * actSlice);
            float p1Y = radius * sin(subBeta * actStack - delta);
            float p1Z = radius * cos(subBeta * actStack - delta) * cos(subAlpha * actSlice);

            float p2X = radius * cos(subBeta * actStack - delta) * sin(subAlpha * (actSlice+1));
            float p2Y = radius * sin(subBeta * actStack - delta);
            float p2Z = radius * cos(subBeta * actStack - delta) * cos(subAlpha * (actSlice+1));

            float p3X = radius * cos(subBeta * (actStack+1) - delta) * sin(subAlpha * (actSlice+1));
            float p3Y = radius * sin(subBeta * (actStack+1) - delta);
            float p3Z = radius * cos(subBeta * (actStack+1) - delta) * cos(subAlpha * (actSlice+1));

            float p4X = radius * cos(subBeta * (actStack+1) - delta) * sin(subAlpha * actSlice);
            float p4Y = radius * sin(subBeta * (actStack+1) - delta);
            float p4Z = radius * cos(subBeta * (actStack+1) - delta) * cos(subAlpha * actSlice);

            addPoint(ph,p1X,p1Y,p1Z);
            addPoint(ph,p2X,p2Y,p2Z);
            addPoint(ph,p3X,p3Y,p3Z);

            addPoint(ph,p1X,p1Y,p1Z);
            addPoint(ph,p3X,p3Y,p3Z);
            addPoint(ph,p4X,p4Y,p4Z);
        }
    }

    printToFile(ph,file);
}