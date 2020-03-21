#pragma once
#include <cstdint>
namespace Balbino
{

	struct Color
	{
		Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );
		Color( uint32_t color );

		unsigned char r, g, b, a;
	};

	struct vec3
	{
		vec3( float x = 0.f, float y = 0.f, float z = 0.f );
		float x, y, z;
	};
}