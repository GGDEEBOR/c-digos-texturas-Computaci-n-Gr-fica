#include <GL/glut.h>

float cubeAngleX = 0.0f; // Ángulo de rotación en el eje X
float cubeAngleY = 0.0f; // Ángulo de rotación en el eje Y
float cubeAngleZ = 0.0f; // Ángulo de rotación en el eje Z

void display() {
    glClearColor(0.8f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, 0.0f); // Transladar el cubo al centro

    gluLookAt(0.0, 0.0, 5.0,  // Posición de la cámara
        0.0, 0.0, 0.0,  // Punto de referencia
        0.0, 1.0, 0.0); // Vector de orientación

    // Aplicar rotaciones
    glRotatef(cubeAngleX, 1.0f, 0.0f, 0.0f);
    glRotatef(cubeAngleY, 0.0f, 1.0f, 0.0f);
    glRotatef(cubeAngleZ, 0.0f, 0.0f, 1.0f);

    

    glBegin(GL_QUADS);

    // Cara frontal
    glColor3f(0.0f, 1.0f, 0.0f); // Verde
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Cara trasera
    glColor3f(0.0f, 0.0f, 1.0f); // Azul
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Cara superior
    glColor3f(1.0f, 1.0f, 1.0f); // Blanco
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Cara inferior
    glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Cara izquierda
    glColor3f(1.0f, 0.0f, 0.0f); // Rojo
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    // Cara derecha
    glColor3f(1.0f, 0.5f, 0.0f); // Naranja
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);

    glEnd();

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / height, 1.0, 10.0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'x' || key == 'X') {
        cubeAngleX += 5.0f; // Incrementa el ángulo de rotación en el eje X
    } 
    else if (key == 'y' || key == 'Y') {
        cubeAngleY += 5.0f; // Incrementa el ángulo de rotación en el eje Y
    } 
    else if (key == 'z' || key == 'Z') {
        cubeAngleZ += 5.0f; // Incrementa el ángulo de rotación en el eje Z
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(1000, 900);
    glutCreateWindow("Laboratorio Cubo/ Computacion Grafica");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); // Registra la función de teclado

    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}
