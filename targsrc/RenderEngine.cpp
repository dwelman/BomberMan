#ifndef _WIN32
#include <unistd.h>
#endif

#include <main.hpp>
#include <fstream>
#include <string>
#include <RenderEngine.hpp>

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

RenderEngine::RenderEngine()
{
	this->position = glm::vec3(0, 0, 5);
	this->horizontalAngle = 3.14f;
	this->verticalAngle = 0.0f;
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

void RenderEngine::computeMatricesFromInputs(SDL_Window *window)
{

    static double lastTime = SDL_GetTicks();
	SDL_Event event;

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

    // Compute time difference between current and last frame
    double currentTime = SDL_GetTicks();
    float deltaTime = float(currentTime - lastTime);

    int xpos, ypos;
	SDL_GetMouseState(&xpos, &ypos);
    this->horizontalAngle += this->mouseSpeed * float(g_cfg["xres"].to_int() / 2 - xpos);
    this->verticalAngle += this->mouseSpeed * float(g_cfg["yres"].to_int() / 2 - ypos);
	SDL_WarpMouseInWindow(window, g_cfg["xres"].to_int() / 2, g_cfg["yres"].to_int() / 2);

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
        //printf("%s\n", &VertexShaderErrorMessage[0]);
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
        //printf("%s\n", &FragmentShaderErrorMessage[0]);
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
        //printf("%s\n", &ProgramErrorMessage[0]);
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

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
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

renderData RenderEngine::initGlew(renderData rdata)
{
    rdata.Textures = new GLuint[6];
    glGenTextures(6, rdata.Textures);

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
    rdata.shaders = LoadShaders("shaders/vertex.glsl", "shaders/transparentFragment.glsl");
	GLuint tx = loadBMP("textures/ore2.bmp", rdata.Textures[0]);
	tx = loadDDS("textures/diffuse.DDS", rdata.Textures[1]);
    tx = loadBMP("textures/normal.bmp", rdata.Textures[2]);
	tx = loadDDS("textures/specular.DDS", rdata.Textures[3]);
    tx = loadBMP("textures/ore.bmp", rdata.Textures[4]);
	tx = loadDDS("textures/DwarfAO.dds", rdata.Textures[5]);
    //tx = loadDDS("textures/DwarfAO.dds", rdata.rObjs[0].getTextureID());
    rdata.objRes = loadOBJ("obj/cube.obj", rdata.objVertices, rdata.objUVS, rdata.objNormals);

    std::vector<glm::vec3> objV, objN, objT, objBt;
    std::vector<glm::vec2> objUV;
    std::vector<glm::vec3> iV, iN, iT, iBt;
    std::vector<glm::vec2> iUV;
	std::vector<unsigned short> ic;
    objV = rdata.rObjs[0].getObjVertices(); objUV = rdata.rObjs[0].getObjUVS(); objN = rdata.rObjs[0].getObjNormals(); objT = rdata.rObjs[0].getObjTangents(); objBt = rdata.rObjs[0].getObjBitangents();
    iV = rdata.rObjs[0].getIndexedVertices(); iUV = rdata.rObjs[0].getIndexedUVS(); iN = rdata.rObjs[0].getIndexedNormals(); iT = rdata.rObjs[0].getIndexedTangents(); iBt = rdata.rObjs[0].getIndexedBitangents();
	ic = rdata.rObjs[0].getIndices();
    loadOBJ("obj/dwarf.obj", objV, objUV, objN);

	computeTangentBasis(rdata.objVertices, rdata.objUVS, rdata.objNormals, rdata.objTangents, rdata.objBitangents);
    computeTangentBasis(objV, objUV, objN, objT, objBt);

	rdata.MatrixID = glGetUniformLocation(rdata.shaders, "MVP");
	rdata.ViewMatrixID = glGetUniformLocation(rdata.shaders, "V");
	rdata.ModelMatrixID = glGetUniformLocation(rdata.shaders, "M");
	rdata.ModelView3x3MatrixID = glGetUniformLocation(rdata.shaders, "MV3x3");
	rdata.DiffuseTextureID = glGetUniformLocation(rdata.shaders, "DiffuseTextureSampler");
	rdata.NormalTextureID = glGetUniformLocation(rdata.shaders, "NormalTextureSampler");
	rdata.SpecularTextureID = glGetUniformLocation(rdata.shaders, "SpecularTextureSampler");
	rdata.LightID = glGetUniformLocation(rdata.shaders, "LightPosition_worldspace");

	indexVBO_TBN(rdata.objVertices, rdata.objUVS, rdata.objNormals, rdata.objTangents, rdata.objBitangents,
		rdata.Indices, rdata.indexed_vertices, rdata.indexed_uvs, rdata.indexed_normals, rdata.indexed_tangents, rdata.indexed_bitangents);

	indexVBO_TBN(objV, objUV, objN, objT, objBt, ic, iV, iUV, iN, iT, iBt);

    GLuint vb, uvB, nB, tB, btB;
    vb = rdata.rObjs[0].getVertexBuffer(); uvB = rdata.rObjs[0].getUVBuffer(); nB = rdata.rObjs[0].getNormalBuffer(); tB = rdata.rObjs[0].getTangentBuffer(); btB = rdata.rObjs[0].getBitangentBuffer();

    glGenBuffers(1, &rdata.VertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_vertices.size() * sizeof(glm::vec3), &rdata.indexed_vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &rdata.UVBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.UVBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_uvs.size() * sizeof(glm::vec2), &rdata.indexed_uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &rdata.NormalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.NormalBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_normals.size() * sizeof(glm::vec3), &rdata.indexed_normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &rdata.TangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.TangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_tangents.size() * sizeof(glm::vec3), &rdata.indexed_tangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &rdata.BitangentBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.BitangentBuffer);
	glBufferData(GL_ARRAY_BUFFER, rdata.indexed_bitangents.size() * sizeof(glm::vec3), &rdata.indexed_bitangents[0], GL_STATIC_DRAW);

	glGenBuffers(1, &rdata.ElementBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rdata.Indices.size() * sizeof(unsigned short), &rdata.Indices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &vb);
    glBindBuffer(GL_ARRAY_BUFFER, vb);
    glBufferData(GL_ARRAY_BUFFER, objV.size() * sizeof(glm::vec3), &objV[0], GL_STATIC_DRAW);

    glGenBuffers(1, &uvB);
    glBindBuffer(GL_ARRAY_BUFFER, uvB);
    glBufferData(GL_ARRAY_BUFFER, objUV.size() * sizeof(glm::vec2), &objUV[0], GL_STATIC_DRAW);

    glGenBuffers(1, &nB);
    glBindBuffer(GL_ARRAY_BUFFER, nB);
    glBufferData(GL_ARRAY_BUFFER, objN.size() * sizeof(glm::vec3), &objN[0], GL_STATIC_DRAW);

    glGenBuffers(1, &tB);
    glBindBuffer(GL_ARRAY_BUFFER, tB);
    glBufferData(GL_ARRAY_BUFFER, objT.size() * sizeof(glm::vec3), &objT[0], GL_STATIC_DRAW);

    glGenBuffers(1, &btB);
    glBindBuffer(GL_ARRAY_BUFFER, btB);
    glBufferData(GL_ARRAY_BUFFER, objBt.size() * sizeof(glm::vec3), &objBt[0], GL_STATIC_DRAW);

    rdata.rObjs[0].setObjVertices(objV); rdata.rObjs[0].setObjUVS(objUV); rdata.rObjs[0].setObjNormals(objN); rdata.rObjs[0].setObjTangents(objT); rdata.rObjs[0].setObjBitangents(objBt);
    rdata.rObjs[0].setIndexedVertices(iV); rdata.rObjs[0].setIndexedUVS(iUV); rdata.rObjs[0].setIndexedNormals(iN); rdata.rObjs[0].setIndexedTangents(iT); rdata.rObjs[0].setIndexedBitangents(iBt);
    rdata.rObjs[0].setVertexBuffer(vb); rdata.rObjs[0].setUVBuffer(uvB); rdata.rObjs[0].setNormalBuffer(nB); rdata.rObjs[0].setTangentBuffer(tB); rdata.rObjs[0].setBitangentBuffer(btB);
	rdata.rObjs[0].setIndices(ic);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return rdata;
}

//void drawCubes(std::vector<std::vector<int>> *blocks)
//{
//	for (int i = 0; i < blocks->size(); i++)
//	{
//
//	}
//}

int RenderEngine::Draw(SDL_Window *window, renderData rdata)
{
    this->computeMatricesFromInputs(window);
    glm::mat4 ProjectionMatrix = this->getProjectionMatrix();
    glm::mat4 ViewMatrix = this->getViewMatrix();
    glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 ModelViewMatrix = ViewMatrix * ModelMatrix;
	glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

    glUniformMatrix4fv(rdata.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(rdata.ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix4fv(rdata.ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix3fv(rdata.ModelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);

	/*static int v = 1;
	static int i = 0;
	if (i == 100)
		v = -1;
	if (i == 2)
		v = 1;
	i += v;*/
	glm::vec3 lightPos = glm::vec3((/*i*/20 / 2), 6, 5 * 2);

    #ifdef _WIN32
	    //Sleep(15);
    #else
        //usleep(15000);
    #endif

	glEnable(GL_CULL_FACE);
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

			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.TangentBuffer);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(4);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.BitangentBuffer);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Index buffer
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
			glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
	}

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, rdata.Textures[1]);
	glUniform1i(rdata.DiffuseTextureID, 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, rdata.Textures[2]);
	glUniform1i(rdata.NormalTextureID, 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, rdata.Textures[3]);
	glUniform1i(rdata.SpecularTextureID, 3);

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

			glEnableVertexAttribArray(3);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.TangentBuffer);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glEnableVertexAttribArray(4);
			glBindBuffer(GL_ARRAY_BUFFER, rdata.BitangentBuffer);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
			glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		}
	}
	glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2); glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE3); glBindTexture(GL_TEXTURE_2D, 0);

    glActiveTexture(GL_TEXTURE1);

	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	glBindTexture(GL_TEXTURE_2D, rdata.Textures[4]);

	//drawCubes(blocks);

    int i, k;

    i = 1;
    k = 5;

    glm::mat4 ModelMatrix3 = glm::mat4(1.0);
    ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(i * 2, 2.0f, k * 2));
    glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;

    glUniformMatrix4fv(rdata.MatrixID, 1, GL_FALSE, &MVP3[0][0]);
    glUniformMatrix4fv(rdata.ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.VertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.UVBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, rdata.NormalBuffer);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.TangentBuffer);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.BitangentBuffer);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
    glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);

	glBindTexture(GL_TEXTURE_2D, rdata.Textures[5]);
	//glBindTexture(GL_TEXTURE_2D, rdata.rObjs[0].getTextureID());

	int x, z;

	x = 5;
	z = 7;

	glm::mat4 ModelMatrix2 = glm::mat4(1.0);
	ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(x * 2, 1.0f, z * 2));
	glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;

	glUniformMatrix4fv(rdata.MatrixID, 1, GL_FALSE, &MVP2[0][0]);
	glUniformMatrix4fv(rdata.ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.rObjs[0].getVertexBuffer());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.rObjs[0].getUVBuffer());
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.rObjs[0].getNormalBuffer());
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.rObjs[0].getTangentBuffer());
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, rdata.rObjs[0].getBitangentBuffer());
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rdata.ElementBuffer);
	glDrawArrays(GL_TRIANGLES, 0, rdata.rObjs[0].getObjVertices().size());
	//glDrawElements(GL_TRIANGLES, rdata.Indices.size(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_MULTISAMPLE);
    return (0);
}