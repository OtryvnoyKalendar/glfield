#include <vector>

#include "glcore.hpp"

namespace {
	using scankey_t = sf::Keyboard::Scan;

	struct PressedSave {
		scankey_t key;
		bool pressed;
	};

	static std::vector<PressedSave> savedKeyStates{};


	bool IsPressedOnce(bool currentPress, bool& previousPress) {
		if(currentPress) {
			if(!previousPress) {
				previousPress = true;
				return true;
			}
		}
		else
			previousPress = false;

		return false;
	}
}

bool IsKeyPressedOnce(scankey_t key) {
	while(true) {
		for(auto& i : savedKeyStates)
			if(i.key == key)
				return IsPressedOnce(sf::Keyboard::isKeyPressed(key), i.pressed);

		savedKeyStates.push_back(PressedSave({key, false}));
	}
}

namespace IsMouseClicked {
	namespace {
		static bool leftPressed{false};
		static bool rightPressed{false};
		static bool middlePressed{false};

		bool IsClicked(sf::Mouse::Button button, bool& mousePressed) {
			return IsPressedOnce(sf::Mouse::isButtonPressed(button), mousePressed);
		}
	}

	bool Left() {
		return IsClicked(sf::Mouse::Button::Left, leftPressed);
	}
	bool Right() {
		return IsClicked(sf::Mouse::Button::Right, rightPressed);
	}
	bool Middle() {
		return IsClicked(sf::Mouse::Button::Middle, middlePressed);
	}
}

