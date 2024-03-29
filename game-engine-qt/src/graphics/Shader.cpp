#include "../../include/engine/graphics/Shader.h"
#include "../../include/engine/game/ContextController.h"
#include "../../include/engine/graphics/Camera.h"
#include "../../include/engine/graphics/lighting/DirectionalLight.h"

// assgins some static functions
static void checkShaderError (GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string loadShader(const std::string& fileName);
static GLuint createGLSLShader (const std::string& text, GLenum shaderType);

Shader::Shader(const std::filesystem::path& shaderName, unsigned int id) : Asset(shaderName, id) {
    // setting up
    QOpenGLFunctions* f = ContextController::getFunctions();
    std::string fullPath = filePath/filePath.filename().string();
    _program = f->glCreateProgram();
    
    // assigning the vs and fs
    _shaders[0] = createGLSLShader(loadShader(fullPath + ".vs"), GL_VERTEX_SHADER);
    _shaders[1] = createGLSLShader(loadShader(fullPath + ".fs"), GL_FRAGMENT_SHADER);

    for (GLuint _shader : _shaders)
        f->glAttachShader(_program, _shader);
    
    // allows these to be passed into the fs and vs programs
    f->glBindAttribLocation(_program, 0, "position");
    f->glBindAttribLocation(_program, 1, "texCoord");
    f->glBindAttribLocation(_program, 2, "normal");

    f->glLinkProgram(_program);
    checkShaderError(_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");

    f->glValidateProgram(_program);
    checkShaderError(_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");
    
    // allows these to be passed into the fs programs
    _uniforms[TRANSFORM_U] = f->glGetUniformLocation(_program, "transform");
    _uniforms[NORMAL_MATRIX_U] = f->glGetUniformLocation(_program, "normalMatrix");
    _uniforms[DIRECTIONAL_LIGHT_DIRECTION_U] = f->glGetUniformLocation(_program, "directionalLightDirection");
    _uniforms[AMBIENT_U] = f->glGetUniformLocation(_program, "ambient");
    _uniforms[DIRECTIONAL_LIGHT_COLOUR_U] = f->glGetUniformLocation(_program, "colour");
}

Shader::~Shader() {
    // cleaning up on deleting
    QOpenGLFunctions* f = ContextController::getFunctions();
    for (unsigned int _shader : _shaders) {
        f->glDetachShader(_program, _shader);
        f->glDeleteShader(_shader);
    }

    f->glDeleteProgram(_program);
}

void Shader::bind() const {
    // assigns this shader to be used
    QOpenGLFunctions* f = ContextController::getFunctions();
    f->glUseProgram(_program);
}

void Shader::update(Transform &transform, const Camera& camera, DirectionalLight* directionalLight) {
    QOpenGLFunctions* f = ContextController::getFunctions();
    // calculates model view projection mat
    glm::mat4 model = transform.getModel();
    glm::mat4 MVP = camera.getViewProjection() * model;

    glm::vec3 direction = directionalLight->getDirection();
    glm::vec3 colour = directionalLight->getColour();
    glm::vec3 ambient = camera.ambient;
    
    // updates shader programs
    f->glUniformMatrix4fv(_uniforms[TRANSFORM_U], 1, GL_FALSE, &MVP[0][0]);
    f->glUniformMatrix4fv(_uniforms[NORMAL_MATRIX_U], 1, GL_FALSE, &model[0][0]);
    f->glUniform3f(_uniforms[DIRECTIONAL_LIGHT_DIRECTION_U], direction.x, direction.y, direction.z);
    f->glUniform4f(_uniforms[AMBIENT_U], ambient.x, ambient.y, ambient.z, 0.0f);
    f->glUniform4f(_uniforms[DIRECTIONAL_LIGHT_COLOUR_U], colour.x, colour.y, colour.z, 1.0f);
}

Shader *Shader::createShader(const std::string &name, const std::filesystem::path &fileName, const std::filesystem::path &filePath) {
    // creates a shader through the asset manager request system
    return AssetManager<Shader>::createAsset(name, filePath/fileName);
}


static std::string loadShader(const std::string& fileName) {
    std::ifstream file;
    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if (file.is_open()) {
        while (file.good()) {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    else {
        std::cerr << "unable to load shader: " << fileName << std::endl;
    }
    return output;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage) {
    QOpenGLFunctions* f = ContextController::getFunctions();
    GLint success = 0;
    GLchar error[1024] = {0};

    // checks for any error
    if (isProgram)
        f->glGetProgramiv(shader, flag, &success);
    else
        f->glGetShaderiv(shader, flag, &success);
    
    // gets specific error
    if (success == GL_FALSE) {
        if (isProgram)
            f->glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            f->glGetShaderInfoLog(shader, sizeof(error), NULL, error);
        // stops program and outputs to console as error
        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

static GLuint createGLSLShader (const std::string& text, GLenum shaderType) {
    QOpenGLFunctions* f = ContextController::getFunctions();

    GLuint shader = f->glCreateShader(shaderType);

    if (shader == 0)
        std::cerr << "Error: Shader creation failed!" << std::endl;

    const GLchar* shaderSourceStrings[1];
    GLint shaderSourceStringLengths[1];

    shaderSourceStrings[0] = text.c_str();
    shaderSourceStringLengths[0] = text.length();

    f->glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
    f->glCompileShader(shader);

    checkShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader compilation failed: ");

    return shader;
}
