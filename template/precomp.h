// Template, IGAD version 3
// IGAD/NHTV/UU - Jacco Bikker - 2006-2022

// Do not include your own headers in this file, this should only contain very rarely changed headers such as standard library / third party headers.
// If anything changes in this header or in any included header it will trigger a full recompile of your project, negating any benefits.
#pragma once

// C++ headers
#include <chrono>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <thread>
#include <cmath>
#include <algorithm>
#include <cassert>
#include <io.h>

#include <iostream>
#include <bitset>
#include <array>
#include <intrin.h>

// header for AVX, and every technology before it.
// if your CPU does not support this (unlikely), include the appropriate header instead.
// see: https://stackoverflow.com/a/11228864/2844473
#include <immintrin.h>

// basic types
using uchar = uint8_t;
using uint = uint32_t;
using ushort = uint16_t;

// aligned memory allocations
#ifdef _MSC_VER
#define ALIGN( x ) __declspec( align( x ) )
#else
#define ALIGN( x ) __attribute__( ( aligned( x ) ) )
#endif

// fatal error reporting (with a pretty window)
#define FATALERROR( fmt, ... ) FatalError( "Error on line %d of %s: " fmt "\n", __LINE__, __FILE__, ##__VA_ARGS__ )
#define FATALERROR_IF( condition, fmt, ... ) do { if ( ( condition ) ) FATALERROR( fmt, ##__VA_ARGS__ ); } while ( 0 )
#define FATALERROR_IN( prefix, errstr, fmt, ... ) FatalError( prefix " returned error '%s' at %s:%d" fmt "\n", errstr, __FILE__, __LINE__, ##__VA_ARGS__ );
#define FATALERROR_IN_CALL( stmt, error_parser, fmt, ... ) do { auto ret = ( stmt ); if ( ret ) FATALERROR_IN( #stmt, error_parser( ret ), fmt, ##__VA_ARGS__ ) } while ( 0 )

// global project settings; shared with OpenCL
#include "common.h"
#include "template_math.h"
#include "template.h"

#include "surface.h"
#include "sprite.h"

// EOF