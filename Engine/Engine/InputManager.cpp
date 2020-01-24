#include "InputManager.h"

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
		}
	}
	

}

inline bool InputManager::isValidKey(int keyId)
{
	return (keyId <= Key::Z && keyId >= Key::A);
}
