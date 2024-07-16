#include "config.h"
#include "triangle_mesh.h"
#include "material.h"

unsigned int make_shader(const std::string& vertex_filepath,const std::string& fragment_filepath);
unsigned int make_module(const std::string& filepath, unsigned int module_type);


int main()
{
    GLFWwindow* window;

    if(!glfwInit())
    {
        std::cout << "GLFW couldn't start" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(640,480,"OpenGL Window",NULL,NULL);
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glClearColor(0.25f,0.5f,0.75f,1.0f);
    
    //Set the rendering region to the actual scene size
    int w,h;
    glfwGetFramebufferSize(window,&w,&h);
    //(left,top,width,height)
    glViewport(0,0,w,h);

    
    TriangleMesh* triangle = new TriangleMesh();
    Material* material = new Material("../img/marika_matsumoto.jpg");
    Material* mask = new Material("../img/mask.jpg");

    unsigned int shader = make_shader(
        "../src/shaders/vertex.txt",
        "../src/shaders/fragment.txt"
    );
    // set texture units
    glUseProgram(shader);
    glUniform1i(glGetUniformLocation(shader,"material"),0 );
    glUniform1i(glGetUniformLocation(shader,"mask"),1 );

    //enable alpha blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA ,GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader);
        material->use(0);
        mask->use(1);
        triangle->draw();
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    delete triangle;
    delete material;
    delete mask;
    glfwTerminate();
    return 0;
}


unsigned int make_shader(const std::string& vertex_filepath,const std::string& fragment_filepath)
{
    std::vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath,GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath,GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for(unsigned int shaderModule: modules){
        glAttachShader(shader, shaderModule);
    } 
    glLinkProgram(shader);


    int success;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char errorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, errorLog);
        std::cout << "Shader Linking error:\n" << errorLog << std::endl ;
    }

    //Delete it
    for(unsigned int shaderModule: modules){
        glDeleteShader(shaderModule);
    } 

    return shader;
}

//Read shader file
unsigned int make_module(const std::string& filepath, unsigned int module_type)
{

    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while(std::getline(file,line))
    {
        //instead of dumping in to cout, dumping into bufferedLines
        bufferedLines << line << "\n";
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1 , &shaderSrc , NULL);
    glCompileShader(shaderModule);

    int success ;
    glGetShaderiv(shaderModule,GL_COMPILE_STATUS, &success);

    if(!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderModule, 1024, NULL, errorLog);
        std::cout << "Shader Module compilation error:\n" << errorLog << std::endl ;
    }

    return shaderModule;
}