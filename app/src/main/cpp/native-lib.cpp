#include <jni.h>
#include <string>
#include <GLES2/gl2.h>
#include <GLES/gl.h>

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jniapp_JNIWrapper_onsurfacecreated(JNIEnv *env, jclass cls) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // Установка матрицы проекции и параметров области отсечения
    glMatrixMode(GL_PROJECTION);
    glOrthof(-8, 8, -8, 8, -8, 8);

    // Включение теста глубины
    glEnable(GL_DEPTH_TEST);

    // Переключение на матрицу модели видов
    glMatrixMode(GL_MODELVIEW);
}

// Обработка изменений размеров поверхности отображения
extern "C"
JNIEXPORT void JNICALL
Java_com_example_jniapp_JNIWrapper_onsurfacechanged(JNIEnv *env, jclass cls, jint width,
                                                    jint height) {
}

// Координаты вершин куба
GLfloat vertices[] = { -1, -1, 0, // 0
                       1, -1, 0,  // 1
                       1,  1, 0,  // 2
                       -1,  1, 0, // 3
                       -1, -1, -2, // 4
                       1, -1, -2,  // 5
                       1,  1, -2,  // 6
                       -1,  1, -2,// 7
};

// Координаты текстурных координат для каждой из вершин
GLfloat texCoords[] = {
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
};

int angle = 0;

extern "C"
JNIEXPORT void JNICALL Java_com_example_jniapp_JNIWrapper_ondrawframe(JNIEnv *env, jclass cls) {
    // Очистка буфера цвета и буфера глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Сброс матрицы модели видов к единичной матрице
    glLoadIdentity();

    // Увеличение угла вращения
    angle = (angle == 360) ? 0 : angle + 1;

    // Переместите центр координат в центр куба
    glTranslatef(0, 0, -4);

    // Вращение куба вокруг своей центральной оси (вертикальной)
    glRotatef(angle, 0, 1, 0);

    // Масштабирование объекта (если необходимо)
    glScalef(3, 1.5, 3);

    // Включение массива вершин и массива текстурных координат
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // Включение текстурирования
    glEnable(GL_TEXTURE_2D);

    // Отрисовка каждой грани куба
    // Лицевая грань
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    // Задняя грань
    glPushMatrix();
    glTranslatef(0, 0, -2);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    // Верхняя грань
    glPushMatrix();
    glTranslatef(0, 1, -1);
    glRotatef(90, 1, 0, 0);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    // Нижняя грань
    glPushMatrix();
    glRotatef(90, 1, 0, 0);
    glTranslatef(0, -1, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    // Левая грань
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(1, 0, -1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    // Правая грань
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(1, 0, 1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glPopMatrix();

    // Выключение текстурирования и массивов вершин и текстурных координат
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    // Верните центр координат обратно в исходное положение
    glTranslatef(0, 0, 4);

    // Обновление экрана
    glFlush();
}
