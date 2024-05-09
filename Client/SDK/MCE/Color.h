#pragma once

namespace mce {
	struct Color {
		float r;
		float g;
		float b;
		float a;

		Color() : r(0), g(0), b(0) {};
		Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {};
	};
}