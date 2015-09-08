#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../Config.hpp"

NS_BEGIN

enum class ShaderType
{
	Vertex,
	TessControl,
	TessEval,
	Geometry,
	Fragment,
	Compute
};

class Material
{
public:
	Material();
	Material(const Material& material);
	~Material();

	Material& operator=(const Material& material);

	bool LoadShader(std::string filepath, ShaderType type);

	void Bind();

	uint GetProgram()const;
private:
	uint vertex, tessControl, tessEval, geometry, fragment, compute;
	uint program;
};

NS_END

#endif