#include <GL/glut.h>

GLuint textureId1; 
GLuint textureId2; 
GLuint textureId3; 

float AnguloRotacionTriangulo = 0.0f;
float escalaCuadrado = 1.0f;
float incrementoEscalaCuadrado = 0.01f;
float dezplazamientoPentagono = 0.0f;
float incrementoDezplazamientoPentagono = 0.01f;
// Función para cargar una textura de ajedrez
void texturaAjedrez()
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

void dibujarTriangulo()
{
    glPushMatrix();
    glRotatef(AnguloRotacionTriangulo, 0.0f, 0.0f, 1.0f);  // Rota el triángulo alrededor del eje Z

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-0.25f, -0.25f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(0.25f, -0.25f);
    glTexCoord2f(0.5f, 1.0f);
    glVertex2f(0.0f, 0.25f);
    glEnd();

    glPopMatrix();
}

void dibujarCuadrado()
{
    glPushMatrix();
    glScalef(escalaCuadrado, escalaCuadrado, 1.0f);  // Escala el cuadrado

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

    glPopMatrix();
}

void dibujarPentagono()
{
    glPushMatrix();
    glTranslatef(0.0f, dezplazamientoPentagono, 0.0f);

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

    glPopMatrix();
}

void renderizar()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer de color

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, textureId1);
    dibujarTriangulo();

    glViewport(glutGet(GLUT_WINDOW_WIDTH) / 3, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, textureId2);
    dibujarCuadrado();

    glViewport((glutGet(GLUT_WINDOW_WIDTH) / 3) * 2, 0, glutGet(GLUT_WINDOW_WIDTH) / 3, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, textureId3);
    dibujarPentagono();

    glFlush();

}
void actualizar(int value)
{
    AnguloRotacionTriangulo += 1.0f;

    // Escalamiento del cuadrado
    escalaCuadrado += incrementoEscalaCuadrado;
    if (escalaCuadrado >= 1.5f || escalaCuadrado <= 0.5f)
        incrementoEscalaCuadrado *= -1.0f;  // Invierte la dirección

    // Movimiento de ida y vuelta del pentágono
    dezplazamientoPentagono += incrementoDezplazamientoPentagono;
    if (dezplazamientoPentagono >= 0.5f || dezplazamientoPentagono <= -0.5f)
        incrementoDezplazamientoPentagono *= -1.0f;  // Invierte la dirección 

    glutPostRedisplay();
    glutTimerFunc(10, actualizar, 0);
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
    texturaAjedrez();

    glBindTexture(GL_TEXTURE_2D, textureId2);
    texturaAjedrez();

    glBindTexture(GL_TEXTURE_2D, textureId3);
    texturaAjedrez();

    glutDisplayFunc(renderizar); 
    glutTimerFunc(10, actualizar, 0); 

    glutMainLoop(); 

    return 0;
}
