#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} Ponto;


float calcula_area_triangulo(Ponto a, Ponto b, Ponto c) {
    return 0.5 * fabs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

float calcula_area_poligono(Ponto vertices[], int num_vertices) {
    float area = 0.0;
    int i;

    for (i = 1; i < num_vertices - 1; i++) {
        area += calcula_area_triangulo(vertices[0], vertices[i], vertices[i + 1]);
    }

    return area;
}


int main() {
    FILE *arquivo;
    int num_vertices, i;
    float area;
    Ponto *vertices;

    arquivo = fopen("trianguloABC.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivo, "%d", &num_vertices);

    vertices = (Ponto *)malloc(num_vertices * sizeof(Ponto));

    for (i = 0; i < num_vertices; i++) {
        fscanf(arquivo, "%f %f", &vertices[i].x, &vertices[i].y);
    }

    fclose(arquivo);

    area = calcula_area_poligono(vertices, num_vertices);

    printf("A area do poligono e: %.2f\n", area);

    free(vertices);
    return 0;
}