#include <GL/glut.h>
#include <cstdio>
#include <GL/glut.h>
#include <cstdio>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat rotationZ = 0.0f;
GLuint textureIDs[4];
int textureWidth[4], textureHeight[4];

void cargarTexturas()
{
    const char* filenames[] = {
        "D:/textura1.jpg",
        "D:/textura2.jpg",
        "D:/textura3.jpg",
        "D:/textura4.jpg"
    };

    for (int i = 0; i < 4; i++)
    {
        unsigned char* imageData = stbi_load(filenames[i], &textureWidth[i], &textureHeight[i], nullptr, 3);
        if (imageData == nullptr)
        {
            printf("No se pudo cargar la imagen %d: %s\n", i + 1, stbi_failure_reason());
            return;
        }

        glGenTextures(1, &textureIDs[i]);
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth[i], textureHeight[i], 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

        stbi_image_free(imageData);
    }
}

void dibujarPiramide()
{

    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotationZ, 0.0f, 0.0f, 1.0f);
    // Definimos los vértices de la base de la pirámide
    GLfloat baseVertices[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f
    };

    // Definimos el color verde claro (RGB: 144, 238, 144)
    glColor3f(0.5647f, 0.9333f, 0.5647f);

    // Dibujamos la base de la pirámide
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
        glVertex3f(baseVertices[i * 3], baseVertices[i * 3 + 1], baseVertices[i * 3 + 2]);
    }
    glEnd();

    // Definimos los vértices de la pirámide (con la base)
    GLfloat vertices[] = {
        // Cara frontal
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,

        // Cara trasera
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,

        // Cara izquierda
        0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,

        // Cara derecha
        0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
    };

    GLfloat texCoords[] = {
        // Cara frontal
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        // Cara trasera
        0.5f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,

        // Cara izquierda
        0.5f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        // Cara derecha
        0.5f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f,
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);

    // Dibujamos las caras de la pirámide con texturas diferentes para cada cara
    for (int i = 0; i < 4; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textureIDs[i]);
        glDrawArrays(GL_TRIANGLES, i * 3, 3);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void display()
{
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glEnable(GL_TEXTURE_2D);
    dibujarPiramide();
    glDisable(GL_TEXTURE_2D);

    glFlush();
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void inicializar()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    cargarTexturas();
}

void manejodeTeclas(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        rotationX += 5.0f;
        break;
    case 'y':
        rotationY += 5.0f;
        break;
    case 'z':
        rotationZ += 5.0f;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Laboratorio pirámide con texturas");
    glutKeyboardFunc(manejodeTeclas);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    inicializar();

    glutMainLoop();

    return 0;
}
