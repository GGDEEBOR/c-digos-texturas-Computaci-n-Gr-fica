#include <GL/glut.h>


// Función para renderizar (dibujar) un triángulo
void drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.25f, -0.25f);
    glVertex2f(0.25f, -0.25f);
    glVertex2f(0.0f, 0.25f);
    glEnd();
}

// Función para renderizar (dibujar) un cuadrado
void drawSquare()
{
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, -0.25f);
    glVertex2f(0.25f, -0.25f);
    glVertex2f(0.25f, 0.25f);
    glVertex2f(-0.25f, 0.25f);
    glEnd();
}

// Función para renderizar (dibujar) un pentágono
void drawPentagon()
{
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.25f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(0.12f, -0.15f);
    glVertex2f(-0.12f, -0.15f);
    glVertex2f(-0.2f, 0.1f);
    glEnd();
}

// Función para renderizar (dibujar) la escena
void render()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer de color

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Divide la ventana en tres partes
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawTriangle();

    glViewport(glutGet(GLUT_WINDOW_WIDTH) / 3, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawSquare();

    glViewport((glutGet(GLUT_WINDOW_WIDTH) / 3) * 2, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawPentagon();

    glFlush(); // Renderiza la escena
}

// Función principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1700, 900);
    glutCreateWindow("Formas Geométricas en Ventana Dividida");

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Color de fondo verde
    //init(); // inicializa Opengl
    glutDisplayFunc(render); // Establece la función de renderizado

    glutMainLoop(); // Inicia el bucle principal de OpenGL

    return 0;
}
