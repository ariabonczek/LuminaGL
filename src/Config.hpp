#ifndef CONFIG_HPP
#define CONFIG_HPP

#define NS_BEGIN namespace LuminaGL {
#define NS_END }

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "LuminaGL"
#define MSAA_SAMPLES 4
#define DEBUG true

#include <GL\glew.h>
#include <GLFW\glfw3.h> 

#include "Math\Math.hpp"

#if DEBUG
#include <iostream>
#endif

#include <string>
#include <vector>
#include <algorithm>

typedef unsigned char byte;

#endif