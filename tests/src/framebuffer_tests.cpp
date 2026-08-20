#include <gtest/gtest.h>

#include "framebuffer.h"

TEST(Framebuffer, ClearUsesRequestedColor) {
	const Pixel original{ 1, 2, 3, 255 };
	const Pixel replacement{ 10, 20, 30, 128 };
	Framebuffer framebuffer{ 3, 2, original };

	framebuffer.clear(replacement);

	for (const Pixel pixel : framebuffer.data()) {
		EXPECT_EQ(pixel, replacement);
	}
}
