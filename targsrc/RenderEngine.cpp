#ifndef _WIN32
#include <unistd.h>
#endif

#include <main.hpp>
#include <fstream>
#include <string>
#include <RenderEngine.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

RenderEngine::RenderEngine()
{
	this->position = glm::vec3(-5.926516f, 51.767967f, 42.664486f);
//	this->horizontalAngle = 3.14f;
//	this->verticalAngle = 0.0f;
    this->horizontalAngle = 7.860002f;
    this->verticalAngle = -1.060000f;
	this->FoV = 45.0f;
	this->speed = 0.01f; // 0.01 units / second
	this->mouseSpeed = 0.005f;
}

RenderEngine::RenderEngine(const RenderEngine &renderEngine)
{
	*this = renderEngine;
}

RenderEngine &RenderEngine::operator = (const RenderEngine &rhs)
{
	position = rhs.position;
	horizontalAngle = rhs.horizontalAngle;
	verticalAngle = rhs.verticalAngle;
	FoV = rhs.FoV;
	speed = rhs.speed;
	mouseSpeed = rhs.mouseSpeed;
	return *this;
}

RenderEngine::~RenderEngine()
{

}

void RenderEngine::handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    //gluPerspective(45.0, static_cast<double>(w) / static_cast<double>(h), 1.0, 200.0);
}

void RenderEngine::setViewMatrix(glm::mat4 viewMatrix)
{
	this->ViewMatrix = viewMatrix;
}

void RenderEngine::setProjectionMatrix(glm::mat4 projectionMatrix)
{
	this->ProjectionMatrix = projectionMatrix;
}

glm::mat4 RenderEngine::getViewMatrix() {
    return this->ViewMatrix;
}
glm::mat4 RenderEngine::getProjectionMatrix() {
    return this->ProjectionMatrix;
}

void RenderEngine::computeMatricesFromInputs(SDL_Window *window, SDL_Event &event)
{

    static double lastTime = SDL_GetTicks();
/*	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			default:
				break;
			}
			break;
		}
	}
*/
    // Compute time difference between current and last frame
    double currentTime = SDL_GetTicks();
    float deltaTime = float(currentTime - lastTime);

    int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);
//    this->horizontalAngle += this->mouseSpeed * float(g_cfg["xres"].to_int() / 2 - xpos);
//    this->verticalAngle += this->mouseSpeed * float(g_cfg["yres"].to_int() / 2 - ypos);
//    usleep(50000);
//	SDL_WarpMouseInWindow(window, g_cfg["xres"].to_int() / 2, g_cfg["yres"].to_int() / 2);

    // Direction : Spherical coordinates to Cartesian coordinates conversion
    glm::vec3 direction(
            cos(this->verticalAngle) * sin(this->horizontalAngle),
            sin(this->verticalAngle),
            cos(this->verticalAngle) * cos(this->horizontalAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
            sin(this->horizontalAngle - 3.14f / 2.0f),
            0,
            cos(this->horizontalAngle - 3.14f / 2.0f)
    );

    // Up vector
    glm::vec3 up = glm::cross(right, direction);

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_W])
    {
        this->position += direction * deltaTime * this->speed;
    }
    if (state[SDL_SCANCODE_S])
    {
        this->position -= direction * deltaTime * this->speed;
    }
    if (state[SDL_SCANCODE_D])
    {
        this->position += right * deltaTime * this->speed;
    }
    if (state[SDL_SCANCODE_A])
    {
        this->position -= right * deltaTime * this->speed;
    }
    if (state[SDL_SCANCODE_ESCAPE])
    {
		exit(0);
    }

    // Projection matrix : 45� Field of View, 16:9 ratio, display range : 0.1 unit <-> 100 units
    this->ProjectionMatrix = glm::perspective(this->FoV, 16.0f / 9.0f, 0.1f, 100.0f);
    // Camera matrix
    this->ViewMatrix = glm::lookAt(
            this->position,           // Camera is here
            this->position + direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // For the next frame, the "last time" will be "now"
    lastTime = currentTime;
}

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path)
{
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open())
	{
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }
	else
	{
		std::cerr << "Unable to open " << vertex_file_path << "." << std::endl;
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

	if (FragmentShaderStream.is_open())
	{
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
	else
	{
		std::cerr << "Unable to open " << fragment_file_path << "." << std::endl;
		getchar();
		return 0;
	}

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex Shader
	std::cout << "Compiling shader : " << vertex_file_path << std::endl;
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0)
	{
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cerr << &VertexShaderErrorMessage[0] << std::endl;
    }

    // Compile Fragment Shader
	std::cout << "Compiling shader : " << fragment_file_path << std::endl;
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0)
	{
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cerr << &FragmentShaderErrorMessage[0] << std::endl;
    }

    // Link the program
	std::cout << "Linking program" << std::endl;
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

	if (InfoLogLength > 0)
	{
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cerr << &ProgramErrorMessage[0] << std::endl;
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

GLuint RenderEngine::loadBMP(const char * imagepath, GLuint texture)
{
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char * data;

    FILE * file = fopen(imagepath, "rb");
	if (!file) { std::cerr << "Image could not be opened" << std::endl; return 0; }
    if (fread(header, 1, 54, file) != 54)
    {
		std::cerr << "Incorrect file type" << std::endl;
        return false;
    }
    if (header[0] != 'B' || header[1] != 'M')
    {
		std::cerr << "File header incorrect" << std::endl;
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
    delete data;
	return 0;
}

GLuint RenderEngine::loadDDS(const char * imagepath, GLuint texture)
{
	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath, "rb");
	if (fp == NULL) {
		printf("%s could not be opened.", imagepath); getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

//	GLuint textureID;
//	glGenTextures(1, &textureID);
//
	glBindTexture(GL_TEXTURE_2D, texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures
		if (width < 1) width = 1;
		if (height < 1) height = 1;

	}

	free(buffer);

	return 0;//textureID;
}

bool RenderEngine::loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals)
{
	std::cout << "Loading OBJ file " << path << "..." << std::endl;

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;


    FILE * file = fopen(path, "r");
    if (file == NULL) {
		std::cerr << "Unable to open OBJ file!" << std::endl;
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
            uv.y = -uv.y; //Will come in handy if we use DDS textures
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
				std::cerr << "File can't be read by this stupid parser yet :-(  Try exporting with other options for now" << std::endl;
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

void RenderEngine::computeTangentBasis(
	// inputs
	std::vector<glm::vec3> & vertices,
	std::vector<glm::vec2> & uvs,
	std::vector<glm::vec3> & normals,
	// outputs
	std::vector<glm::vec3> & tangents,
	std::vector<glm::vec3> & bitangents
)
{
	for (unsigned int i = 0; i<vertices.size(); i += 3) {

		// Shortcuts for vertices
		glm::vec3 & v0 = vertices[i + 0];
		glm::vec3 & v1 = vertices[i + 1];
		glm::vec3 & v2 = vertices[i + 2];

		// Shortcuts for UVs
		glm::vec2 & uv0 = uvs[i + 0];
		glm::vec2 & uv1 = uvs[i + 1];
		glm::vec2 & uv2 = uvs[i + 2];

		// Edges of the triangle : postion delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;

		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;

		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later, in vboindexer.cpp
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		// Same thing for binormals
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}

	for (unsigned int i = 0; i<vertices.size(); i += 1)
	{
		glm::vec3 & n = normals[i];
		glm::vec3 & t = tangents[i];
		glm::vec3 & b = bitangents[i];

		// Gram-Schmidt orthogonalize
		t = glm::normalize(t - n * glm::dot(n, t));

		// Calculate handedness
		if (glm::dot(glm::cross(n, t), b) < 0.0f) {
			t = t * -1.0f;
		}

	}
}

void RenderEngine::initGlew()
{
    for (int i = 0; i < 3; i++)
    {
        renderData *obj = new renderData;
        rdata.push_back(*obj);
    }
    rdata[0].Textures = new GLuint[7];
    glGenTextures(7, rdata[0].Textures);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Error : " << "Failed to initialize GLEW" << std::endl;
        rdata[0].res = -1;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    glClearColor(0.1f, 0.0f, 0.0f, 0.0f);
    rdata[0].shaders = LoadShaders("shaders/vertex.glsl", "shaders/transparentFragment.glsl");
	GLuint tx = loadBMP("textures/ore2.bmp", rdata[0].Textures[0]);
	tx = loadDDS("textures/diffuse.DDS", rdata[0].Textures[1]);
    tx = loadBMP("textures/normal.bmp", rdata[0].Textures[2]);
	tx = loadDDS("textures/specular.DDS", rdata[0].Textures[3]);
    tx = loadBMP("textures/ore.bmp", rdata[0].Textures[4]);
	tx = loadDDS("textures/DwarfAO.dds", rdata[0].Textures[5]);
    //tx = loadBMP("textures/DwarfAO.bmp", rdata[0].Textures[5]);
    tx = loadDDS("textures/BombAO.dds", rdata[0].Textures[6]);
    //tx = loadDDS("textures/DwarfAO.dds", rdata.rObjs[0].getTextureID());

    //std::vector<glm::vec3> objV, objN, objT, objBt;
    //std::vector<glm::vec2> objUV;
    //std::vector<glm::vec3> iV, iN, iT, iBt;
    //std::vector<glm::vec2> iUV;
	//std::vector<unsigned short> ic;
    //objV = rdata.rObjs[0].getObjVertices(); objUV = rdata.rObjs[0].getObjUVS(); objN = rdata.rObjs[0].getObjNormals(); objT = rdata.rObjs[0].getObjTangents(); objBt = rdata.rObjs[0].getObjBitangents();
    //iV = rdata.rObjs[0].getIndexedVertices(); iUV = rdata.rObjs[0].getIndexedUVS(); iN = rdata.rObjs[0].getIndexedNormals(); iT = rdata.rObjs[0].getIndexedTangents(); iBt = rdata.rObjs[0].getIndexedBitangents();
	//ic = rdata.rObjs[0].getIndices();
    //rdata[0].objRes = loadOBJ("obj/cube.obj", rdata[0].objVertices, rdata[0].objUVS, rdata[0].objNormals);
    //rdata[1].objRes = loadOBJ("obj/dwarf.obj", rdata[1].objVertices, rdata[1].objUVS, rdata[1].objNormals);
    //rdata[2].objRes = loadOBJ("obj/bomb.obj", rdata[2].objVertices, rdata[2].objUVS, rdata[2].objNormals);

    Mesh *cube = new Mesh("obj/cube.obj");
    mesh.push_back(*cube);

    Mesh *dwarf = new Mesh("obj/dwarf.dae");
    mesh.push_back(*dwarf);

    Mesh *bomb = new Mesh("obj/bomb.obj");
    mesh.push_back(*bomb);

    //computeTangentBasis(rdata[1].objVertices, rdata[1].objUVS, rdata[1].objNormals, rdata[1].objTangents, rdata[1].objBitangents);

	rdata[0].MatrixID = glGetUniformLocation(rdata[0].shaders, "MVP");
	rdata[0].ViewMatrixID = glGetUniformLocation(rdata[0].shaders, "V");
	rdata[0].ModelMatrixID = glGetUniformLocation(rdata[0].shaders, "M");
	rdata[0].ModelView3x3MatrixID = glGetUniformLocation(rdata[0].shaders, "MV3x3");
	rdata[0].DiffuseTextureID = glGetUniformLocation(rdata[0].shaders, "DiffuseTextureSampler");
	rdata[0].NormalTextureID = glGetUniformLocation(rdata[0].shaders, "NormalTextureSampler");
	rdata[0].SpecularTextureID = glGetUniformLocation(rdata[0].shaders, "SpecularTextureSampler");
	rdata[0].LightID = glGetUniformLocation(rdata[0].shaders, "LightPosition_worldspace");

    //GLuint vb, uvB, nB, tB, btB;
    //vb = rdata.rObjs[0].getVertexBuffer(); uvB = rdata.rObjs[0].getUVBuffer(); nB = rdata.rObjs[0].getNormalBuffer(); tB = rdata.rObjs[0].getTangentBuffer(); btB = rdata.rObjs[0].getBitangentBuffer();

//    for (int i = 0; i < rdata.size(); i++)
//    {
//        computeTangentBasis(rdata[i].objVertices, rdata[i].objUVS, rdata[i].objNormals, rdata[i].objTangents, rdata[i].objBitangents);
//
//        indexVBO_TBN(rdata[i].objVertices, rdata[i].objUVS, rdata[i].objNormals, rdata[i].objTangents, rdata[i].objBitangents,
//                     rdata[i].Indices, rdata[i].indexed_vertices, rdata[i].indexed_uvs, rdata[i].indexed_normals, rdata[i].indexed_tangents, rdata[i].indexed_bitangents);
//
//        glGenBuffers(1, &rdata[i].VertexBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].VertexBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].indexed_vertices.size() * sizeof(glm::vec3),
//                     &rdata[i].indexed_vertices[0], GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[i].UVBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].UVBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].indexed_uvs.size() * sizeof(glm::vec2), &rdata[i].indexed_uvs[0],
//                     GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[i].NormalBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].NormalBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].indexed_normals.size() * sizeof(glm::vec3), &rdata[i].indexed_normals[0],
//                     GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[i].TangentBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].TangentBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].indexed_tangents.size() * sizeof(glm::vec3),
//                     &rdata[i].indexed_tangents[0], GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[i].BitangentBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].BitangentBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].indexed_bitangents.size() * sizeof(glm::vec3),
//                     &rdata[i].indexed_bitangents[0], GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[i].ElementBuffer);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[i].ElementBuffer);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, rdata[i].Indices.size() * sizeof(unsigned short), &rdata[i].Indices[0],
//                     GL_STATIC_DRAW);
//    }
//    for (int i = 1; i < rdata.size(); i++)
//    {
//        indexVBO_TBN(rdata[i].objVertices, rdata[i].objUVS, rdata[i].objNormals, rdata[i].objTangents, rdata[i].objBitangents,
//                     rdata[i].Indices, rdata[i].indexed_vertices, rdata[i].indexed_uvs, rdata[i].indexed_normals, rdata[i].indexed_tangents, rdata[i].indexed_bitangents);
//
//        glGenBuffers(1, &rdata[i].VertexBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].VertexBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].objVertices.size() * sizeof(glm::vec3), &rdata[i].objVertices[0], GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[1].UVBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].UVBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].objUVS.size() * sizeof(glm::vec2), &rdata[i].objUVS[0], GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[1].NormalBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].NormalBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].objNormals.size() * sizeof(glm::vec3), &rdata[i].objNormals[0], GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[1].TangentBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].TangentBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].objTangents.size() * sizeof(glm::vec3), &rdata[i].objTangents[0], GL_STATIC_DRAW);
//
//        glGenBuffers(1, &rdata[1].BitangentBuffer);
//        glBindBuffer(GL_ARRAY_BUFFER, rdata[i].BitangentBuffer);
//        glBufferData(GL_ARRAY_BUFFER, rdata[i].objBitangents.size() * sizeof(glm::vec3), &rdata[i].objBitangents[0], GL_STATIC_DRAW);
//    }

    //rdata.rObjs[0].setObjVertices(objV); rdata.rObjs[0].setObjUVS(objUV); rdata.rObjs[0].setObjNormals(objN); rdata.rObjs[0].setObjTangents(objT); rdata.rObjs[0].setObjBitangents(objBt);
    //rdata.rObjs[0].setIndexedVertices(iV); rdata.rObjs[0].setIndexedUVS(iUV); rdata.rObjs[0].setIndexedNormals(iN); rdata.rObjs[0].setIndexedTangents(iT); rdata.rObjs[0].setIndexedBitangents(iBt);
    //rdata.rObjs[0].setVertexBuffer(vb); rdata.rObjs[0].setUVBuffer(uvB); rdata.rObjs[0].setNormalBuffer(nB); rdata.rObjs[0].setTangentBuffer(tB); rdata.rObjs[0].setBitangentBuffer(btB);
	//rdata.rObjs[0].setIndices(ic);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glShadeModel(GL_SMOOTH);
}

//void drawCubes(std::vector<std::vector<int>> *blocks)
//{
//	for (int i = 0; i < blocks->size(); i++)
//	{
//
//	}
//}

int RenderEngine::Draw(SDL_Window *window, bool gameStarted, std::vector<GameObjectRenderInfo> gameObjects)
{
 //   if (gameStarted)
//        this->computeMatricesFromInputs(window);

    glm::mat4 ProjectionMatrix = this->getProjectionMatrix();
    glm::mat4 ViewMatrix = this->getViewMatrix();
    glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
    glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
    glUniformMatrix4fv(rdata[0].ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
    glUniformMatrix3fv(rdata[0].ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);

    /*static int v = 1;
    static int i = 0;
    if (i == 100)
        v = -1;
    if (i == 2)
        v = 1;
    i += v;*/

#ifdef _WIN32
    //Sleep(15);
#else
    //usleep(15000);
#endif

    glEnable(GL_CULL_FACE);
    glUseProgram(rdata[0].shaders);

    glBindTexture(GL_TEXTURE_2D, rdata[0].Textures[0]);

    glEnable(GL_MULTISAMPLE);

	static int i = 0;

//	for (int l = 0; l < gameObjects.size(); l++)
//	{
//		bool shouldDraw = false;
//
//		while (gameObjects[i].GetObjectType() != 1) {
//			l++;
//			i++;
//			if (i == gameObjects.size())
//				break;
//			//            if (gameObjects[i].GetObjectType() == 0) {
//			//                shouldDraw = true;
//			//            }
//		}
//		if (i >= gameObjects.size()) {
//			shouldDraw = false;
//		}
//		else
//			shouldDraw = true;
//
//		if (shouldDraw)
//		{
//			glm::mat4 ModelMatrix3 = glm::mat4(1.0);
//			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(gameObjects[i].GetPosition().GetY() * 2, gameObjects[i].GetPosition().GetZ() * 2, gameObjects[i].GetPosition().GetX() * 2));
//			ModelMatrix3 = glm::rotate(ModelMatrix3, gameObjects[i].GetDirection() * 1.575f, glm::vec3(0, 1, 0));
//			glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;
//
//			glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP3[0][0]);
//			glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);
//
////			glEnableVertexAttribArray(0);
////			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].VertexBuffer);
////			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
////
////			glEnableVertexAttribArray(1);
////			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].UVBuffer);
////			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
////
////			glEnableVertexAttribArray(2);
////			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].NormalBuffer);
////			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
////
////			glEnableVertexAttribArray(3);
////			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].TangentBuffer);
////			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
////
////			glEnableVertexAttribArray(4);
////			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].BitangentBuffer);
////			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
////
////			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[0].ElementBuffer);
////			glDrawElements(GL_TRIANGLES, rdata[0].Indices.size(), GL_UNSIGNED_SHORT, (void *)0);
//            mesh[0].render();
//		}
//		i++;
//	}
//
//	i = 0;

    //for (float x = 2; x < 25; x++) {
    //    for (int z = 2; z < 45; z++) {
    //        glm::mat4 ModelMatrix = glm::mat4(1.0);
    //        ModelMatrix = glm::translate(ModelMatrix, glm::vec3(((x * 2) - 4), 0.0f, ((z * 2) - 4)));
    //        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    //        // Send our transformation to the currently bound shader,
    //        // in the "MVP" uniform
    //        glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //        glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);

    //        // 1rst attribute buffer : vertices
    //        glEnableVertexAttribArray(0);
    //        glBindBuffer(GL_ARRAY_BUFFER, rdata[0].VertexBuffer);
    //        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //        // 2nd attribute buffer : UVs
    //        glEnableVertexAttribArray(1);
    //        glBindBuffer(GL_ARRAY_BUFFER, rdata[0].UVBuffer);
    //        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //        // 3rd attribute buffer : normals
    //        glEnableVertexAttribArray(2);
    //        glBindBuffer(GL_ARRAY_BUFFER, rdata[0].NormalBuffer);
    //        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //        glEnableVertexAttribArray(3);
    //        glBindBuffer(GL_ARRAY_BUFFER, rdata[0].TangentBuffer);
    //        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //        glEnableVertexAttribArray(4);
    //        glBindBuffer(GL_ARRAY_BUFFER, rdata[0].BitangentBuffer);
    //        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    //        // Index buffer
    //        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[0].ElementBuffer);
    //        glDrawElements(GL_TRIANGLES, rdata[0].Indices.size(), GL_UNSIGNED_SHORT, (void *) 0);
    //    }
    //}

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, rdata[0].Textures[1]);
    glUniform1i(rdata[0].DiffuseTextureID, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, rdata[0].Textures[2]);
    glUniform1i(rdata[0].NormalTextureID, 2);

    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, rdata[0].Textures[3]);
    glUniform1i(rdata[0].SpecularTextureID, 3);

	for (int l = 0; l < gameObjects.size(); l++)
	{
		bool shouldDraw = false;

		while (gameObjects[i].GetObjectType() != 1) {
			l++;
			i++;
			if (i == gameObjects.size())
				break;
			//            if (gameObjects[i].GetObjectType() == 0) {
			//                shouldDraw = true;
			//            }
		}
		if (i >= gameObjects.size()) {
			shouldDraw = false;
		}
		else
			shouldDraw = true;

		if (shouldDraw)
		{
			glm::mat4 ModelMatrix3 = glm::mat4(1.0);
			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(gameObjects[i].GetPosition().GetY() * 2, gameObjects[i].GetPosition().GetZ() * 2, gameObjects[i].GetPosition().GetX() * 2));
			ModelMatrix3 = glm::rotate(ModelMatrix3, gameObjects[i].GetDirection() * 1.575f, glm::vec3(0, 1, 0));
			glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;

			glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP3[0][0]);
			glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);

			//			glEnableVertexAttribArray(0);
			//			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].VertexBuffer);
			//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			//
			//			glEnableVertexAttribArray(1);
			//			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].UVBuffer);
			//			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
			//
			//			glEnableVertexAttribArray(2);
			//			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].NormalBuffer);
			//			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			//
			//			glEnableVertexAttribArray(3);
			//			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].TangentBuffer);
			//			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			//
			//			glEnableVertexAttribArray(4);
			//			glBindBuffer(GL_ARRAY_BUFFER, rdata[0].BitangentBuffer);
			//			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			//
			//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[0].ElementBuffer);
			//			glDrawElements(GL_TRIANGLES, rdata[0].Indices.size(), GL_UNSIGNED_SHORT, (void *)0);
			mesh[0].render();
		}
		i++;
	}

	i = 0;

    /*for (float x = 2; x < 14; x++) {
        for (int z = 2; z < 24; z++) {
            glm::mat4 ModelMatrix2 = glm::mat4(1.0);
            ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3((((x * 2) * 2) - 8), 2.0f, (((z * 2) * 2) - 8)));
            glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;

            glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP2[0][0]);
            glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].VertexBuffer);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].UVBuffer);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0);

            glEnableVertexAttribArray(2);
            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].NormalBuffer);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

            glEnableVertexAttribArray(3);
            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].TangentBuffer);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

            glEnableVertexAttribArray(4);
            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].BitangentBuffer);
            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[0].ElementBuffer);
            glDrawElements(GL_TRIANGLES, rdata[0].Indices.size(), GL_UNSIGNED_SHORT, (void *) 0);
        }
    }*/
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);

    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);

    glBindTexture(GL_TEXTURE_2D, rdata[0].Textures[4]);

    //drawCubes(blocks);

//    int i, k;
//
//    i = 1;
//    k = 5;
//    gameObjects[0].SetObjectType(BLOCK_OT);
//    gameObjects[0].SetPosition(Vec3(1, 1, 5));
//    gameObjects[1].SetObjectType(BOMB_OT);
//    gameObjects[1].SetPosition(Vec3(3, 1, 5));

    for (int l = 0; l < gameObjects.size(); l++)
    {
        bool shouldDraw = false;

        while (gameObjects[i].GetObjectType() != 0) {
            l++;
            i++;
            if (i == gameObjects.size())
                break;
            //            if (gameObjects[i].GetObjectType() == 0) {
            //                shouldDraw = true;
            //            }
        }
        if (i >= gameObjects.size()) {
            shouldDraw = false;
        }
        else
            shouldDraw = true;

        if (shouldDraw)
        {
            glm::mat4 ModelMatrix3 = glm::mat4(1.0);
            ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(gameObjects[i].GetPosition().GetY() * 2, gameObjects[i].GetPosition().GetZ() * 2, gameObjects[i].GetPosition().GetX() * 2));
            ModelMatrix3 = glm::rotate(ModelMatrix3, gameObjects[i].GetDirection() * 1.575f, glm::vec3(0, 1, 0));
            glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;

            glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP3[0][0]);
            glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);

//            glEnableVertexAttribArray(0);
//            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].VertexBuffer);
//            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
//
//            glEnableVertexAttribArray(1);
//            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].UVBuffer);
//            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);
//
//            glEnableVertexAttribArray(2);
//            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].NormalBuffer);
//            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
//
//            glEnableVertexAttribArray(3);
//            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].TangentBuffer);
//            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
//
//            glEnableVertexAttribArray(4);
//            glBindBuffer(GL_ARRAY_BUFFER, rdata[0].BitangentBuffer);
//            glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
//
//            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[0].ElementBuffer);
//            glDrawElements(GL_TRIANGLES, rdata[0].Indices.size(), GL_UNSIGNED_SHORT, (void *)0);
            mesh[0].render();
        }
        i++;
    }

    i = 0;

    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);

    glBindTexture(GL_TEXTURE_2D, rdata[0].Textures[5]);
    //glBindTexture(GL_TEXTURE_2D, rdata.rObjs[0].getTextureID());

//    int x, z;
//
//    x = 5;
//    z = 7;
//    gameObjects[0].SetObjectType(BOMB_OT);
//    gameObjects[0].SetPosition(Vec3(1, 0.5, 7));
//    gameObjects[0].SetDirection(SOUTH);
//    gameObjects[1].SetObjectType(PLAYER_OT);
//    gameObjects[1].SetPosition(Vec3(5, 0.5, 7));
//    gameObjects[1].SetDirection(SOUTH);

    for (int l = 0; l < gameObjects.size(); l++)
    {
        bool shouldDraw = false;

        while (gameObjects[i].GetObjectType() != 2) {
			l++;
            i++;
			if (i == gameObjects.size())
				break;
//            if (gameObjects[i].GetObjectType() == 0) {
//                shouldDraw = true;
//            }
        }
        if (i >= gameObjects.size()) {
            shouldDraw = false;
        } else
            shouldDraw = true;

		if (shouldDraw)
		{
			glm::mat4 ModelMatrix2 = glm::mat4(1.0);
			ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(gameObjects[i].GetPosition().GetY() * 2, (gameObjects[i].GetPosition().GetZ() * 2) + 1, gameObjects[i].GetPosition().GetX() * 2));
			ModelMatrix2 = glm::rotate(ModelMatrix2, gameObjects[i].GetDirection() * 1.575f, glm::vec3(0, 1, 0));
            ModelMatrix2 = glm::rotate(ModelMatrix2, 1.575f, glm::vec3(-1, 0, 0));
			glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;

			glm::vec3 lightPos = glm::vec3(gameObjects[i].GetPosition().GetY() * 2, gameObjects[i].GetPosition().GetZ() + 9.0f, /*z*/gameObjects[i].GetPosition().GetX() * 2);
			glUniform3f(rdata[0].LightID, lightPos.x, lightPos.y, lightPos.z);

			glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP2[0][0]);
			glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

//			glEnableVertexAttribArray(0);
//			glBindBuffer(GL_ARRAY_BUFFER, rdata[1].VertexBuffer);
//			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//			glEnableVertexAttribArray(1);
//			glBindBuffer(GL_ARRAY_BUFFER, rdata[1].UVBuffer);
//			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//			glEnableVertexAttribArray(2);
//			glBindBuffer(GL_ARRAY_BUFFER, rdata[1].NormalBuffer);
//			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//			glEnableVertexAttribArray(3);
//			glBindBuffer(GL_ARRAY_BUFFER, rdata[1].TangentBuffer);
//			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//			glEnableVertexAttribArray(4);
//			glBindBuffer(GL_ARRAY_BUFFER, rdata[1].BitangentBuffer);
//			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[1].ElementBuffer);
//			glDrawElements(GL_TRIANGLES, rdata[1].Indices.size(), GL_UNSIGNED_SHORT, (void *)0);
            mesh[1].render();
		}
        i++;
    }

    i = 0;

    glBindTexture(GL_TEXTURE_2D, rdata[0].Textures[6]);

//    gameObjects[0].SetObjectType(BOMB_OT);
//    gameObjects[0].SetPosition(Vec3(4, 0.5, 7));
//    gameObjects[0].SetDirection(SOUTH);

    static float scale = 1.0f;
    static bool scaleUp = false;
    glScalef(scale, scale, scale);
    for (int l = 0; l < gameObjects.size(); l++)
    {
        bool shouldDraw = false;

        while (gameObjects[i].GetObjectType() != 3) {
			l++;
            i++;
			if (i == gameObjects.size())
				break;
//            if (gameObjects[i].GetObjectType() == 0) {
//                shouldDraw = true;
//            }
        }
        if (i >= gameObjects.size()) {
            shouldDraw = false;
        } else
            shouldDraw = true;

		if (shouldDraw)
		{
            if (scale >= 1.3f)
                scaleUp = false;
            if (scale <= 1.0f)
                scaleUp = true;
            if (scaleUp)
                scale += 0.05f;
            else
                scale -= 0.05f;
            //std::cout << scale << std::endl;
			glm::mat4 ModelMatrix2 = glm::mat4(1.0);
			ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(gameObjects[i].GetPosition().GetY() * 2, (gameObjects[i].GetPosition().GetZ() * 2) + 1, gameObjects[i].GetPosition().GetX() * 2));
			ModelMatrix2 = glm::rotate(ModelMatrix2, gameObjects[i].GetDirection() * 1.575f, glm::vec3(0, 1, 0));
            ModelMatrix2 = glm::scale_slow(ModelMatrix2, glm::vec3(scale, scale, scale));
			glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;

			//        if (shouldDraw)
			//        {
			//            glm::vec3 lightPos = glm::vec3(gameObjects[i].GetPosition().GetX() * 2, 9.0f, /*z*/gameObjects[i].GetPosition().GetZ() * 2);
			//            glUniform3f(rdata[0].LightID, lightPos.x, lightPos.y, lightPos.z);
			//        }

			glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP2[0][0]);
			glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

			/*glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, rdata[2].VertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, rdata[2].UVBuffer);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, rdata[2].NormalBuffer);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, rdata[2].TangentBuffer);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(4);
			glBindBuffer(GL_ARRAY_BUFFER, rdata[2].BitangentBuffer);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[2].ElementBuffer);
			glDrawElements(GL_TRIANGLES, rdata[2].Indices.size(), GL_UNSIGNED_SHORT, (void *)0);*/
			mesh[2].render();
		}
        i++;
    }

    i = 0;
//
//    glm::mat4 ModelMatrix2 = glm::mat4(1.0);

//    static int v = 1;
//    static float m = 0.0;
//    if (m >= 40) {
//        v = -1;
//    }
//    if (m <= 2) {
//        v = 1;
//    }
//    if (v == -1)
//        gameObjects[1].SetDirection(WEST);
//    else
//        gameObjects[1].SetDirection(EAST);
//	m += v / 10.0;
//    ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(x * 2, 1.0f, /*z*/m * 2));
//    ModelMatrix2 = glm::rotate(ModelMatrix2, gameObjects[1].GetDirection() * 1.575f, glm::vec3(0, 1, 0));

    #ifdef _WIN32
	    Sleep(15);
    #else
        usleep(15000);
    #endif

//    glm::vec3 lightPos = glm::vec3(x * 2, 9.0f, /*z*/m * 2);
//
//    glUniform3f(rdata[0].LightID, lightPos.x, lightPos.y, lightPos.z);
//	glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;
//
//	glUniformMatrix4fv(rdata[0].MatrixID, 1, GL_FALSE, &MVP2[0][0]);
//	glUniformMatrix4fv(rdata[0].ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, rdata[1].VertexBuffer);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, rdata[1].UVBuffer);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glEnableVertexAttribArray(2);
//	glBindBuffer(GL_ARRAY_BUFFER, rdata[1].NormalBuffer);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glEnableVertexAttribArray(3);
//	glBindBuffer(GL_ARRAY_BUFFER, rdata[1].TangentBuffer);
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//	glEnableVertexAttribArray(4);
//	glBindBuffer(GL_ARRAY_BUFFER, rdata[1].BitangentBuffer);
//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata[1].ElementBuffer);
//    glDrawElements(GL_TRIANGLES, rdata[1].Indices.size(), GL_UNSIGNED_SHORT, (void *) 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
	//glDrawArrays(GL_TRIANGLES, 0, rdata[1].objVertices.size());
	//glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_MULTISAMPLE);
    return (0);
}