#include <SFML/Graphics.hpp>

#include <cmath>
#include <cstdint>
#include <optional>

#include <glm/vec2.hpp>

#include "framebuffer.h"
#include "sfml_renderer.h"

int main() {
	sf::RenderWindow window{
		sf::VideoMode::getFullscreenModes().at(0),
		"SFML Demo"
	};

	// We draw into this CPU-side framebuffer instead of issuing one SFML draw
	// call per pixel. Its dimensions match the window so each framebuffer pixel
	// maps directly to one screen pixel.
	const auto windowSize{ window.getSize() };
	const Pixel backgroundColor{};
	Framebuffer framebuffer{
		static_cast<int>(windowSize.x),
		static_cast<int>(windowSize.y),
		backgroundColor
	};

	// SFML presents the framebuffer by uploading its RGBA bytes to a texture and
	// drawing a single sprite that covers the window.
	sf::Texture framebufferTexture{ windowSize };
	framebufferTexture.setSmooth(false);
	sf::Sprite framebufferSprite{ framebufferTexture };

	while (window.isOpen()) {
		// Handle all window events before drawing the next frame. This is important
		// because SFML will not update the window contents if events are not
		// processed, and the window will appear frozen.
		while (const std::optional event{ window.pollEvent() }) {
			// Close the window if the user clicks the close button or presses Escape.
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (const auto* keyPressed{ event->getIf<sf::Event::KeyPressed>() };
				keyPressed && keyPressed->code == sf::Keyboard::Key::Escape) {
				window.close();
			}
		}

		// Start each frame with empty CPU and SFML drawing surfaces.
		window.clear(sf::Color::Black);
		framebuffer.clear(backgroundColor);

		// All drawing happens in the framebuffer. setPixel() safely ignores any
		// coordinates that fall outside its bounds.
		for (std::int32_t x{ 0 }; x < 500; ++x) {
			const std::int32_t y{
				static_cast<std::int32_t>(std::round(2.0 / 3.0 * x + 40))
			};
			framebuffer.setPixel(glm::ivec2{ x, y }, Pixel{ 255, 255, 255, 255 });
		}

		// Upload the completed CPU framebuffer and present it as one SFML frame.
		drawFramebuffer(window, framebufferTexture, framebufferSprite, framebuffer);
		window.display();
	}

	return 0;
}
