#include <jni.h>
#include <string>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

    const float VERTICES[] = {
        -0.5,  0.5, -0.5,
        0.5, -0.5, -0.5,
        -0.5, -0.5, -0.5,
        /* Top right */
        -0.5,  0.5, -0.5,
        0.5,  0.5, -0.5,
        0.5, -0.5, -0.5,
        /* Bottom left */
        -0.5,  0.5,  0.5,
        -0.5, -0.5, -0.5,
        -0.5, -0.5,  0.5,
        /* Top right */
        -0.5,  0.5,  0.5,
        -0.5,  0.5, -0.5,
        -0.5, -0.5, -0.5,
        /* Bottom left */
        -0.5,  0.5,  0.5,
        0.5,  0.5, -0.5,
        -0.5,  0.5, -0.5,
        /* Top right */
        -0.5,  0.5,  0.5,
        0.5,  0.5,  0.5,
        0.5,  0.5, -0.5,
        /* Bottom left */
        0.5,  0.5, -0.5,
        0.5, -0.5,  0.5,
        0.5, -0.5, -0.5,
        /* Top right */
        0.5,  0.5, -0.5,
        0.5,  0.5,  0.5,
        0.5, -0.5,  0.5,
        /* Bottom left */
        0.5,  0.5,  0.5,
        -0.5, -0.5,  0.5,
        0.5, -0.5,  0.5,
        /* Top right */
        0.5,  0.5,  0.5,
        -0.5,  0.5,  0.5,
        -0.5, -0.5,  0.5,
        /* Bottom left */
        -0.5, -0.5, -0.5,
        0.5, -0.5,  0.5,
        -0.5, -0.5,  0.5,
        /* Top right */
        -0.5, -0.5, -0.5,
        0.5, -0.5, -0.5,
        0.5, -0.5,  0.5,
    };

    const float COLORS[] = {
            1.0, 0.0, 0.0,
            0.0, 0.0, 1.0,
            0.0, 1.0, 0.0,
            /* Top right */
            1.0, 0.0, 0.0,
            1.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            /* Bottom left */
            1.0, 1.0, 1.0,
            0.0, 1.0, 0.0,
            0.0, 1.0, 1.0,
            /* Top right */
            1.0, 1.0, 1.0,
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            /* Bottom left */
            1.0, 1.0, 1.0,
            1.0, 1.0, 0.0,
            1.0, 0.0, 0.0,
            /* Top right */
            1.0, 1.0, 1.0,
            0.0, 0.0, 0.0,
            1.0, 1.0, 0.0,
            /* Bottom left */
            1.0, 1.0, 0.0,
            1.0, 0.0, 1.0,
            0.0, 0.0, 1.0,
            /* Top right */
            1.0, 1.0, 0.0,
            0.0, 0.0, 0.0,
            1.0, 0.0, 1.0,
            /* Bottom left */
            0.0, 0.0, 0.0,
            0.0, 1.0, 1.0,
            1.0, 0.0, 1.0,
            /* Top right */
            0.0, 0.0, 0.0,
            1.0, 1.0, 1.0,
            0.0, 1.0, 1.0,
            /* Bottom left */
            0.0, 1.0, 0.0,
            1.0, 0.0, 1.0,
            0.0, 1.0, 1.0,
            /* Top right */
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
            1.0, 0.0, 1.0,
    };

    const char* VERTEX_SHADER_CODE =
    "attribute vec4 position;"
    "attribute vec3 color;"
    "uniform mat4 model;"
    "uniform mat4 view;"
    "uniform mat4 projection;"
    "varying vec3 v3color;"
    "void main() {"
    "    v3color = color;"
    "    gl_Position = projection * view * model * position;"
    "}";


    const char* FRAGMENT_SHADER_CODE =
    "precision lowp float;"
    "varying vec3 v3color;"
    "void main() {"
    "    gl_FragColor = vec4(v3color, 1.0);"
    "}";

GLuint mProgram;
GLuint mPositionHandle;
GLuint mColorHandle;

    int windowWidth = -1;
    int windowHeight = -1;

    GLuint createVertexShader() {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &VERTEX_SHADER_CODE, NULL);
        glCompileShader(vertexShader);
        GLint status;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);

        return vertexShader;
    }
    GLuint createFragmentShader() {
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &FRAGMENT_SHADER_CODE, NULL);
        glCompileShader(fragmentShader);
        GLint status;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);

        return fragmentShader;
    }

    void initialize(int width, int height) {

        windowWidth = width;
        windowHeight = height;

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mProgram = glCreateProgram();

        glAttachShader(mProgram, createVertexShader());
        glAttachShader(mProgram, createFragmentShader());
        glLinkProgram(mProgram);
        GLint status;
        glGetProgramiv(mProgram, GL_LINK_STATUS, &status);

        glUseProgram(mProgram);

        mPositionHandle = glGetAttribLocation(mProgram, "position");
        mColorHandle = glGetAttribLocation(mProgram, "color");

        glViewport(0, 0, windowWidth, windowHeight);

        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    }

     void draw(float rotation) {

        glUseProgram(mProgram);

        glEnableVertexAttribArray(mPositionHandle);
        glVertexAttribPointer(
                mPositionHandle, 3, GL_FLOAT,
                GL_FALSE,0, VERTICES);

        glEnableVertexAttribArray(mColorHandle);
        glVertexAttribPointer(
                mColorHandle, 3, GL_FLOAT,
                GL_FALSE, 0, COLORS);

        glm::mat4 model = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        GLint modelLoc = glGetUniformLocation(mProgram, "model");
        GLint viewLoc = glGetUniformLocation(mProgram, "view");
        GLint projLoc = glGetUniformLocation(mProgram, "projection");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisableVertexAttribArray(mPositionHandle);
        glDisableVertexAttribArray(mColorHandle);
    }


extern "C"
{
    JNIEXPORT void JNICALL
    Java_com_example_cuberender_MyGLRenderer_CubeInit
    (JNIEnv *env, jobject,  jint width, jint height) {
        initialize(width, height);
    }

    JNIEXPORT void JNICALL Java_com_example_cuberender_MyGLRenderer_CubeDraw
    (JNIEnv *env, jobject, float rotation) {
        draw(rotation);
    }
}


