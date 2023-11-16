#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QTimer>
#include "src_include/shader.h"

class StartWindow : public QOpenGLWindow,protected QOpenGLFunctions_3_3_Core
{
public:
    StartWindow(QRect screen_size, Shader *shader);

    void initializeGL();

    void resizeGL(int w,int h);

    void paintGL();

private:
    QRect screen_size_;
    Shader* shader_;
    GLuint vao_,vbo_,ebo_;
};

#endif // STARTWINDOW_H
