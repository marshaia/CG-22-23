#include <stdio.h>
#include <math.h>
#include "../pointHolder.h"

void generateCone(float radius, float height, float slices, float stacks, FILE* file) {
    PointHolder ph = initPointHolder();
	float doisPI = M_PI * 2;
	float slice = (doisPI / slices);
	float stack = height / stacks;
	float raio = radius / stacks;
	

    for (float i = 0; i < doisPI; i += slice) {
        addPoint(ph, 0.0f, 0.0f, 0.0f);
        addPoint(ph, (sin(i + slice) * radius),0.0f, (cos(i + slice) * radius));
        addPoint(ph, sin(i) * radius,0.0f, cos(i) * radius);
    }
    float r = 0;
    for (float j = 0; j < (height); j += stack) {
        for (float i = 0; i < doisPI; i += slice) {
            addPoint(ph, sin(i) * (radius - (r + raio)), j + stack, cos(i) * (radius - (r + raio)));
            addPoint(ph, sin(i) * (radius - r), j, cos(i) * (radius - r));
            addPoint(ph,sin(i + slice) * (radius - r), j, cos(i + slice) * (radius - r));
        }
        r += raio;
    }
    r = 0;
    for (float a = 0 ;a < (height -stack); a += stack) {
        for (float i = 0; i < doisPI; i += slice) {
            addPoint(ph, sin(i) * (radius - (r + raio)), a + stack, cos(i) * (radius - (r + raio)));
            addPoint(ph,sin(i + slice) * (radius - r), a, cos(i + slice) * (radius - r));
            addPoint(ph, sin(i + slice) * (radius - (r + raio)), a + stack, cos(i + slice) * (radius - (r + raio)));
        }
        r += raio;
    }
	


    printToFile(ph, file);
}
