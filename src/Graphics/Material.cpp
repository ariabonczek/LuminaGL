#include "Material.hpp"
#include "../Utility/FileSystem.hpp"

NS_BEGIN

Material::Material() :
	program(0)
{}

Material::Material(const Material& material)
{
	vertex = material.vertex;
	tessControl = material.tessControl;
	tessEval = material.tessEval;
	geometry = material.geometry;
	fragment = material.fragment;
	compute = material.compute;
	program = material.program;
}

Material::~Material()
{}

Material& Material::operator=(const Material& material)
{
	vertex = material.vertex;
	tessControl = material.tessControl;
	tessEval = material.tessEval;
	geometry = material.geometry;
	fragment = material.fragment;
	compute = material.compute;
	program = material.program;
	return *this;
}

bool Material::LoadShader(std::string filepath, ShaderType type)
{
	if (!program)
		program = glCreateProgram();

	const char* shaderCode = FileSystem::LoadTextFile(filepath.c_str());

	if (!shaderCode)
		return 0;

	uint* index = 0;
	GLenum t;
	switch (type)
	{
	case ShaderType::Vertex:
		index = &vertex;
		t = GL_VERTEX_SHADER;
		break;
	case ShaderType::TessControl:
		index = &tessControl;
		t = GL_TESS_CONTROL_SHADER;
		break;
	case ShaderType::TessEval:
		index = &tessEval;
		t = GL_TESS_EVALUATION_SHADER;
		break;
	case ShaderType::Geometry:
		index = &geometry;
		t = GL_GEOMETRY_SHADER;
		break;
	case ShaderType::Fragment:
		index = &fragment;
		t = GL_FRAGMENT_SHADER;
		break;
	case ShaderType::Compute:
		index = &compute;
		t = GL_COMPUTE_SHADER;
		break;
	default:
		return 0;
	}

	*index = glCreateShader(t);
	glShaderSource(*index, 1, &shaderCode, 0);
	glCompileShader(*index);

#if DEBUG
	GLint check;
	glGetShaderiv(*index, GL_COMPILE_STATUS, &check);

	if (!check)
	{
		char log[1000] = { 0 };
		int length;
		glGetShaderiv(*index, GL_INFO_LOG_LENGTH, &length);
		glGetShaderInfoLog(*index, length, 0, log);
		std::cout << log << std::endl;

		return 0;
	}
#endif

	glAttachShader(program, *index);

	glLinkProgram(program);

#if DEBUG
	glGetProgramiv(program, GL_LINK_STATUS, &check);
	if (!check)
	{
		char log[1000] = { 0 };
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		glGetShaderInfoLog(program, length, 0, log);
		std::cout << log << std::endl;
		glDeleteProgram(program);

		return 0;
	}
#endif
	return true;
}

void Material::Bind()
{
	glUseProgram(program);
}

uint Material::GetProgram()const
{
	return program;
}

NS_END