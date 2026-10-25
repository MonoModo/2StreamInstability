#include "GLSLReader.h"

#include "embedded_shaders.h"

#include "shaderOptions.h"
#include <stdexcept>

std::string GLSLReader::readShader(const char* relativePath)
{
	if (relativePath == nullptr)
		throw std::invalid_argument("Shader path cannot be null");

	const std::string path(relativePath);
	const std::string filename = path.substr(path.find_last_of("/\\") == std::string::npos
		? 0
		: path.find_last_of("/\\") + 1);

	if (filename == "default.vs.glsl")
		return reinterpret_cast<const char*>(EmbeddedShaders::DefaultVertex);
	if (filename == "default.fs.glsl")
		return reinterpret_cast<const char*>(EmbeddedShaders::DefaultFragment);

	throw std::invalid_argument("No embedded shader named: " + filename);
}