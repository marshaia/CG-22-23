#include <stdio.h>
#include <math.h>
#include "pointHolder.h"

void generateCylinder(float radius, float height, int slices, FILE* file) {

    PointHolder ph = initPointHolder();

    float angle = (M_PI * 2) / slices;

    for (int i = 1; i <= slices; i++) {
        //Valores "atuais" de X e Z
        float actualPointX = radius * sin(angle * (float)i);
        float actualPointZ = radius * cos(angle * (float)i);

        // Valores "seguintes" de X e Z
        float nextPointX = radius * sin(angle * ((float)i + 1));
        float nextPointZ = radius * cos(angle * ((float)i + 1));


		addPoint(ph, 0.0f, height, 0.0f);
		addPoint(ph, actualPointX, height, actualPointZ);
		addPoint(ph, nextPointX, height, nextPointZ);

		addPoint(ph, nextPointX, 0, nextPointZ);
		addPoint(ph, nextPointX, height, nextPointZ);
		addPoint(ph, actualPointX, height, actualPointZ);

		addPoint(ph, actualPointX, height, actualPointZ);
		addPoint(ph, actualPointX, 0, actualPointZ);
		addPoint(ph, nextPointX, 0, nextPointZ);

		addPoint(ph, actualPointX, 0, actualPointZ);
		addPoint(ph, 0.0, 0, 0.0);
		addPoint(ph, nextPointX, 0, nextPointZ);
    }

    printToFile(ph, file);
}