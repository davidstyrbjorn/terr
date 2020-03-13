#include <stdlib.h>

namespace terr {

	class Color {
	private:
			

	public:
		float r, g, b, a;

		Color();
		Color(const Color& c) = default;
		Color(float red, float green, float blue);
		Color(float red, float green, float blue, float alpha);
		
		static Color Red();
		static Color Green();
		static Color Blue();
		static Color GetRandomColor();
		
		Color Mix(Color c, const float bias = 0.5);
	};
}