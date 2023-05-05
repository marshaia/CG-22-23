#include "../pointHolder.h"
#include "math.h"


void generateSphere(float x, float y, float z, float radius, int slices, int stacks, PointHolder ph){

    float subAlpha = M_PI * 2 / ((float) slices);
    float subBeta = M_PI / ((float) stacks);
    float delta = (M_PI / ((float) 2));

    for(int actSlice = 0; actSlice < slices; actSlice++){
        for(int actStack = 0; actStack < stacks;actStack++){
            float p1X = x + radius * cos(subBeta * actStack - delta ) * sin(subAlpha * actSlice);
            float p1Y = y + radius * sin(subBeta * actStack - delta);
            float p1Z = z + radius * cos(subBeta * actStack - delta) * cos(subAlpha * actSlice);

            float p2X = x + radius * cos(subBeta * actStack - delta) * sin(subAlpha * (actSlice+1));
            float p2Y = y + radius * sin(subBeta * actStack - delta);
            float p2Z = z + radius * cos(subBeta * actStack - delta) * cos(subAlpha * (actSlice+1));

            float p3X = x + radius * cos(subBeta * (actStack+1) - delta) * sin(subAlpha * (actSlice+1));
            float p3Y = y + radius * sin(subBeta * (actStack+1) - delta);
            float p3Z = z + radius * cos(subBeta * (actStack+1) - delta) * cos(subAlpha * (actSlice+1));

            float p4X = x + radius * cos(subBeta * (actStack+1) - delta) * sin(subAlpha * actSlice);
            float p4Y = y + radius * sin(subBeta * (actStack+1) - delta);
            float p4Z = z + radius * cos(subBeta * (actStack+1) - delta) * cos(subAlpha * actSlice);

            addPoint(ph,p1X,p1Y,p1Z);
            addPoint(ph,p2X,p2Y,p2Z);
            addPoint(ph,p3X,p3Y,p3Z);

            addPoint(ph,p1X,p1Y,p1Z);
            addPoint(ph,p3X,p3Y,p3Z);
            addPoint(ph,p4X,p4Y,p4Z);
        }
    }
}

void generateAsteroidBelt (float fullRadius, float smallRadius, int slices, int stacks, FILE *file) {
    float x1, y1, z1;
    float theta = 0, phi = 0;
    float sliceAngle = 2 * M_PI / slices;
    float stackAngle = 2 * M_PI / stacks;
    // stacks == phi, slices == theta

    PointHolder ph = initPointHolder();

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {

            float r = rand()*(1/RAND_MAX) + 0.5;
            int slice = 4; int stack = 5;

            x1 = ((fullRadius + smallRadius * cos(phi)) * cos(theta)) + float(rand()*(1/RAND_MAX) -0.5);
            z1 = ((fullRadius + smallRadius * cos(phi)) * sin(theta)) + float(rand()*(1/RAND_MAX) -0.5);
            y1 = (smallRadius * sin(phi)) + float(rand()*(1/RAND_MAX) -0.5);
            generateSphere(x1, y1, z1, r, slice, stack, ph);

            j += rand()%(3-1 + 1) + 1;
            phi = stackAngle * (float) (j + 1);
        }
        theta = sliceAngle * (float) (i + 1);
    }

    printToFile(ph, file);
}