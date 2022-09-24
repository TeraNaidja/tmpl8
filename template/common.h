// Template, IGAD version 3
// IGAD/NHTV/UU - Jacco Bikker - 2006-2022
#pragma once

// common.h is to be included in host and device code and stores
// global settings and defines.

// default screen resolution
static constexpr int SCRWIDTH  = 1280;
static constexpr int SCRHEIGHT = 720;
// #define FULLSCREEN

// constants
static constexpr float PI = 3.14159265358979323846264f;
static constexpr float INVPI = 0.31830988618379067153777f;
static constexpr float INV2PI = 0.15915494309189533576888f;
static constexpr float TWOPI = 6.28318530717958647692528f;
static constexpr float SQRT_PI_INV = 0.56418958355f;
static constexpr float LARGE_FLOAT = 1e34f;

// IMPORTANT NOTE ON OPENCL COMPATIBILITY ON OLDER LAPTOPS:
// Without a GPU, a laptop needs at least a 'Broadwell' Intel CPU (5th gen, 2015):
// Intel's OpenCL implementation 'NEO' is not available on older devices.
// Same is true for Vulkan, OpenGL 4.0 and beyond, as well as DX11 and DX12.