#ifndef _WIN32
#include <unistd.h>
#endif

#include <main.hpp>
#include <fstream>
#include <string>
#include <RenderEngine.hpp>

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
    return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
    return ProjectionMatrix;
}


glm::vec3 position = glm::vec3(0, 0, 5);
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;

float speed = 0.01f; // 0.01 units / second
float mouseSpeed = 0.005f;

void computeMatricesFromInputs(SDL_Window *window) {

    static double lastTime = SDL_GetTicks();

    // Compute time difference between current and last frame
    double currentTime = SDL_GetTicks();
    float deltaTime = float(currentTime - lastTime);

    int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);
    SDL_WarpMouseInWindow(window, 1280 / 2, 720 / 2);
    horizontalAngle += mouseSpeed * float(1280 / 2 - xpos);
    verticalAngle += mouseSpeed * float(720 / 2 - ypos);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            sin(horizontalAngle - 3.14f / 2.0f),
            0,
            cos(horizontalAngle - 3.14f / 2.0f)
    );

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        position += direction * deltaTime * speed;
    }
    if (state[SDL_SCANCODE_S])
    {
        position -= direction * deltaTime * speed;
    }
    if (state[SDL_SCANCODE_D])
    {
        position += right * deltaTime * speed;
    }
    if (state[SDL_SCANCODE_A])
    {
        position -= right * deltaTime * speed;
    }
    if (state[SDL_SCANCODE_ESCAPE])
    {
		exit(0);
    }

    float FoV = initialFoV;

    // Projection matrix : 45� Field of View, 16:9 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(FoV, 16.0f / 9.0f, 0.1f, 100.0f);
    // Camera matrix
    ViewMatrix = glm::lookAt(
            position,           // Camera is here
            position + direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ?\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

GLuint loadBMP(const char * imagepath, GLuint texture)
{
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char * data;

    FILE * file = fopen(imagepath, "rb");
    if (!file) { printf("Image could not be opened\n"); return 0; }
    if (fread(header, 1, 54, file) != 54)
    {
        printf("Incorrect file type\n");
        return false;
    }
    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("File header incorrect\n");
        return 0;
    }

    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    //Some files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = width * height * 3; // 3 : 1 byte for each color component
    if (dataPos == 0)
        dataPos = 54; //Standard BMP header formatting

    data = new unsigned char[imageSize];

    fread(data, 1, imageSize, file);

    fclose(file);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(data);
}

bool loadOBJ(
        const char * path,
        std::vector<glm::vec3> & out_vertices,
        std::vector<glm::vec2> & out_uvs,
        std::vector<glm::vec3> & out_normals
) {
    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    FILE * file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file !\n");
        getchar();
        return false;
    }

    while (1) {

        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            //uv.y = -uv.y; //Will come in handy if we use DDS textures
            temp_uvs.push_back(uv);
        }
        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0) {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
        else {
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

    }

    for (unsigned int i = 0; i<vertexIndices.size(); i++)
	{
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        glm::vec2 uv = temp_uvs[uvIndex - 1];
        glm::vec3 normal = temp_normals[normalIndex - 1];

        out_vertices.push_back(vertex);
        out_uvs.push_back(uv);
        out_normals.push_back(normal);
    }
    return true;
}

renderData initGlew()
{
    renderData rdata;
    rdata.Textures = new GLuint[3];
    glGenTextures(3, rdata.Textures);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Error : " << "Failed to initialize GLEW" << std::endl;
        rdata.res = -1;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
    rdata.shaders = LoadShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
	GLuint tx = loadBMP("textures/ore2.bmp", rdata.Textures[0]);
    tx = loadBMP("textures/Cobblestone.bmp", rdata.Textures[1]);
    tx = loadBMP("textures/ore.bmp", rdata.Textures[2]);
    rdata.objRes = loadOBJ("obj/suzanne.obj", rdata.objVertices, rdata.objUVS, rdata.objNormals);
	rdata.MatrixID = glGetUniformLocation(rdata.shaders, "MVP");
	rdata.ViewMatrixID = glGetUniformLocation(rdata.shaders, "V");
	rdata.ModelMatrixID = glGetUniformLocation(rdata.shaders, "M");
	rdata.LightID = glGetUniformLocation(rdata.shaders, "LightPosition_worldspace");

	indexVBO(rdata.objVertices, rdata.objUVS, rdata.objNormals, rdata.Indices, rdata.indexed_vertices, rdata.indexed_uvs, rdata.indexed_normals);

    glGenBuffers(1, &rdata.VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_vertices.size() * sizeof(glm::vec3), &rdata.indexed_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &rdata.UVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_uvs.size() * sizeof(glm::vec2), &rdata.indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &rdata.NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_normals.size() * sizeof(glm::vec3), &rdata.indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &rdata.ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rdata.Indices.size() * sizeof(unsigned short), &rdata.Indices[0], GL_STATIC_DRAW);

    return rdata;
}

//void drawCubes(std::vector<std::vector<int>> *blocks)
//{
//	for (int i = 0; i < blocks->size(); i++)
//	{
//
//	}
//}

int     draw(SDL_Window *window, renderData rdata)
{
    computeMatricesFromInputs(window);
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(rdata.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(rdata.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(rdata.ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

	static int v = 1;
	static int i = 0;
	if (i == 100)
		v = -1;
	if (i == 2)
		v = 1;
	i += v;
	glm::vec3 lightPos = glm::vec3((i / 2), 6, 5 * 2);

    #ifdef _WIN32
	    Sleep(15);
    #else
        usleep(15000);
    #endif

    glUseProgram(rdata.shaders);
	glUniform3f(rdata.LightID, lightPos.x, lightPos.y, lightPos.z);

	glBindTexture(GL_TEXTURE_2D, rdata.Textures[0]);

    glEnable(GL_MULTISAMPLE);

	for (float x = 2; x < 25; x++)
	{
		for (int z = 2; z < 45; z++)
		{
			glm::mat4 ModelMatrix = glm::mat4(1.0);
			ModelMatrix = glm::translate(ModelMatrix, glm::vec3(((x * 2) - 4), 0.0f, ((z * 2) - 4)));
			glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(rdata.MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(rdata.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.VertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 2nd attribute buffer : UVs
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.UVBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// 3rd attribute buffer : normals
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.NormalBuffer);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
			glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
	}
	/*std::vector<std::vector<int>> blocks[3];
	blocks[0].push_back(std::vector<int>());
	blocks[0][0].push_back(1);
	blocks[0][1].push_back(1);
	blocks[1].push_back(std::vector<int>());
	blocks[1][0].push_back(1);
	blocks[1][1].push_back(2);
    glBindTexture(GL_TEXTURE_2D, rdata.Textures[1]);
	drawCubes(blocks);*/

	for (float x = 2; x < 14; x++)
	{
		for (int z = 2; z < 24; z++)
		{
			glm::mat4 ModelMatrix2 = glm::mat4(1.0);
			ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3((((x * 2) * 2)- 8), 2.0f, (((z * 2) * 2) - 8)));
			glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;

			glUniformMatrix4fv(rdata.MatrixID, 1, GL_FALSE, &MVP2[0][0]);
			glUniformMatrix4fv(rdata.ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.VertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.UVBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.NormalBuffer);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
			glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
	}

    glBindTexture(GL_TEXTURE_2D, rdata.Textures[2]);

    int x, z;

    x = 1;
    z = 3;

    glm::mat4 ModelMatrix2 = glm::mat4(1.0);
    ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(x * 2, 2.0f, z * 2));
    glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;

    glUniformMatrix4fv(rdata.MatrixID, 1, GL_FALSE, &MVP2[0][0]);
    glUniformMatrix4fv(rdata.ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.VertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.UVBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.NormalBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
    glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_MULTISAMPLE);
    return (0);
}