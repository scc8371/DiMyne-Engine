#include "Shader.h"

GLuint Shader::VAO = 0;

std::string get_file_contents(const char* filename){
    
    std::ifstream in(filename, std::ios::in | std::ios::binary);
    if (in){
        try{
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        catch(...){
            in.close();
            std::cout << "[DiMyne] Error reading file: " << filename << std::endl;
            return "";
        }        
    }

    return "";
}

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    std::string vertex, fragment;

    //tries to read vertex and fragment files, if error is thrown, prints error
    vertex = get_file_contents(vertexPath);
    fragment = get_file_contents(fragmentPath);

    if(vertex == "" || fragment == "") return;

    //turns contents into c strings
    const char* vShaderCode = vertex.c_str();
    const char* fShaderCode = fragment.c_str();

    GLuint vertexShader, fragmentShader;
    
    //vertex shader initialization
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    //fragment shader initialization
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    //create shader ID for program
    ID = glCreateProgram();

    //attach shaders to program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    //delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //generate VAO
    glGenVertexArrays(1, &VAO);

    std::cout << "[DiMyne] Shader created" << std::endl;
    std::cout << "[DiMyne] Initialized VAO: " << VAO << " (" << &VAO << ")" << std::endl;
}

void Shader::use(){
    glUseProgram(ID);
}

void Shader::del(){
    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ID);
}

void Shader::bind(){
    glBindVertexArray(VAO);
}

void Shader::unbind(){
    glBindVertexArray(0);
}

void Shader::linkAttrib(GLuint vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Shader::setMat4(const std::string& name, const glm::mat4& matrix){
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setVec3(const std::string& name, const glm::vec3& vector){
    glUniform3f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y, vector.z);
}