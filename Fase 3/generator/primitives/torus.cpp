#include <math.h>
#include "../pointHolder.h"

/*
 * order of points generated:
 * for each stack of each slice:
 *
 * P4 ------- P3
 * |          |
 * |          |
 * |          |
 * P1 ------- P2
 *
 */

void generateTorus (float fullRadius, float smallRadius, int slices, int stacks, FILE *file) {
    float x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    float theta = 0, phi = 0;
    float sliceAngle = 2 * M_PI / slices;
    float stackAngle = 2 * M_PI / stacks;
    // stacks == phi, slices == theta

    PointHolder ph = initPointHolder();

    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {

            x1 = (fullRadius + smallRadius * cos(phi)) * cos(theta);
            z1 = (fullRadius + smallRadius * cos(phi)) * sin(theta);
            y1 = smallRadius * sin(phi);

            x2 = (fullRadius + smallRadius * cos(phi)) * cos(theta + sliceAngle);
            z2 = (fullRadius + smallRadius * cos(phi)) * sin(theta + sliceAngle);
            y2 = smallRadius * sin(phi);

            x3 = (fullRadius + smallRadius * cos(phi + stackAngle)) * cos(theta + sliceAngle);
            z3 = (fullRadius + smallRadius * cos(phi + stackAngle)) * sin(theta + sliceAngle);
            y3 = smallRadius * sin(phi + stackAngle);

            x4 = (fullRadius + smallRadius * cos(phi + stackAngle)) * cos(theta);
            z4 = (fullRadius + smallRadius * cos(phi + stackAngle)) * sin(theta);
            y4 = smallRadius * sin(phi + stackAngle);


            addPoint(ph, x1, y1, z1);
            addPoint(ph, x2, y2, z2);
            addPoint(ph, x3, y3, z3);

            addPoint(ph, x3, y3, z3);
            addPoint(ph, x4, y4, z4);
            addPoint(ph, x1, y1, z1);

            phi = stackAngle * (float) (j + 1);
        }
        theta = sliceAngle * (float) (i + 1);
    }

    printToFile(ph, file);
}