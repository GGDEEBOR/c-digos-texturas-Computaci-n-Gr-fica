#include <GL/glut.h>

GLuint textureId1; // Identificador de textura 1
GLuint textureId2; // Identificador de textura 2
GLuint textureId3; // Identificador de textura 3

// Función para cargar una textura de ajedrez
void loadChessTexture()
{
    unsigned char pixels[] = {
        255, 255, 255, 0, 0, 0, 255, 255,
        255, 255, 255, 0, 0, 0, 255, 255,
        0, 0, 0, 255, 255, 255, 0, 0,
        0, 0, 0, 255, 255, 255, 0, 0
    };

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Función para renderizar (dibujar) un triángulo
void drawTriangle()
{
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.25f, -0.25f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.25f, -0.25f);
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(0.0f, 0.25f);
    glEnd();
}

// Función para renderizar (dibujar) un cuadrado
void drawSquare()
{
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.25f, -0.25f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.25f, -0.25f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(0.25f, 0.25f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-0.25f, 0.25f);
    glEnd();
}

// Función para renderizar (dibujar) un pentágono
void drawPentagon()
{
    glBegin(GL_POLYGON);
    glTexCoord2f(0.0f, 0.5f);
    glVertex2f(0.0f, 0.25f);
    glTexCoord2f(0.2f, 0.1f);
    glVertex2f(0.2f, 0.1f);
    glTexCoord2f(0.12f, -0.15f);
    glVertex2f(0.12f, -0.15f);
    glTexCoord2f(-0.12f, -0.15f);
    glVertex2f(-0.12f, -0.15f);
    glTexCoord2f(-0.2f, 0.1f);
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
    glBindTexture(GL_TEXTURE_2D, textureId1);
    drawTriangle();


    glViewport(glutGet(GLUT_WINDOW_WIDTH) / 3, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, textureId2);
    drawSquare();

    glViewport((glutGet(GLUT_WINDOW_WIDTH) / 3) * 2, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, textureId3);
    drawPentagon();

    glFlush(); // Renderiza la escena
}

// Función principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1700, 900);
    glutCreateWindow("Figuras con Texturas");

    glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Color de fondo negro

    // Habilita el uso de texturas
    glEnable(GL_TEXTURE_2D);

    // Genera los identificadores de textura
    glGenTextures(1, &textureId1);
    glGenTextures(1, &textureId2);
    glGenTextures(1, &textureId3);

    // Carga la textura de ajedrez
    glBindTexture(GL_TEXTURE_2D, textureId1);
    loadChessTexture();

    glBindTexture(GL_TEXTURE_2D, textureId2);
    loadChessTexture();

    glBindTexture(GL_TEXTURE_2D, textureId3);
    loadChessTexture();

    glutDisplayFunc(render); // Establece la función de renderizado

    glutMainLoop(); // Inicia el bucle principal de OpenGL

    return 0;
}
