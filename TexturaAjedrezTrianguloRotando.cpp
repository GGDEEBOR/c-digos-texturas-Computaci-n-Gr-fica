#include <GL/glut.h>

// Variables globales
GLuint textureId; // Identificador de textura
float angle = 0.0f;

// Función para inicializar OpenGL
void init()
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // Color de fondo negro

    glEnable(GL_TEXTURE_2D);

    // Genera un identificador de textura
    glGenTextures(1, &textureId);

    // Selecciona la textura actual
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Define los parámetros de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Define los datos de la textura (textura de ajedrez 2x2)
    unsigned char pixels[] = {
        255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0, 255, 255, 255, 0, 0, 0
    };

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}

// Función para renderizar (dibujar) la escena
void render()
{
    glClear(GL_COLOR_BUFFER_BIT); // Limpia el buffer de color

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f); // Mueve la escena hacia atrás para que se vea

    glRotatef(angle, 0.0f, 1.0f, 0.0f); // Rota sobre el eje Y
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, textureId); // Selecciona la textura
    // Dibuja el triángulo con textura de tablero de ajedrez
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
    glTexCoord2f(0.5f, 1.0f); glVertex2f(0.0f, 0.5f);
    glEnd();

    glFlush(); // Renderiza la escena
}

// Función para actualizar la escena
void update()
{
    angle += 0.5f; // Incrementa el ángulo de rotación
    if (angle > 360.0f)
        angle -= 360.0f;

    glutPostRedisplay(); // Marca la ventana como "necesita ser redibujada"
}

// Función principal
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triángulo con textura de tablero de ajedrez");

    init(); // Inicializa OpenGL

    glutDisplayFunc(render); // Establece la función de renderizado
    glutIdleFunc(update); // Establece la función de actualización

    glutMainLoop(); // Inicia el bucle principal de OpenGL

    return 0;
}
