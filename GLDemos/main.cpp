#include <iostream>
//#include <GL/glew.h>
//#include <GL/glxew.h>
//#include <GL/wglew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace transform
{
    float aspect = 800 / 600.0;
    GLuint  update_prog;
    GLuint vao[2];
    GLuint vbo[2];
    GLuint xfb;

    GLuint render_prog;
    GLuint geometry_vbo;
    GLuint render_vao;
    GLuint render_model_matrix_loc;
    GLuint render_projection_matrix_loc;

    GLuint geometry_tex;

    GLuint geometry_xfb;
    GLuint particle_xfb;

    GLint model_matrix_loc;
    GLint projection_matrix_loc;
    GLint triangle_count_loc;
    GLint time_step_loc;

    VBO
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}












