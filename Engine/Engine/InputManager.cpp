#include "InputManager.h"
InputManager::Key InputManager::lastKeyDown = InputManager::Key::NONE;//the last key that was pressed prior to this frame
InputManager::Key InputManager::lastKeyUp = InputManager::Key::NONE;//the last key released prior to this frame
void InputManager::KeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
	Key convertedKey;
	if (isValidKey(i_VKeyID))
	{
		convertedKey = static_cast<Key>(i_VKeyID);

		if (bWentDown)
		{
			lastKeyDown = convertedKey;
		}
		else
		{
			lastKeyUp = convertedKey;
			if (lastKeyDown == lastKeyUp)
			{
				lastKeyDown = Key::NONE;
			}
		}
	}
	

}

inline bool InputManager::isValidKey(int keyId)
{
	return (keyId <= Key::Z && keyId >= Key::A) | keyId == 0x00;
}
