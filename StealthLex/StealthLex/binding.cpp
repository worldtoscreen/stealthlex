#include "binding.hpp"

int waitUntilKeyPressed()
{
	std::cout << "Press a key! We reccomend you use a key that you don't use often." << std::endl;
	int buf = 0;

	do {
		for (int i = 2; i < 256; i++)
		{
			if (GetAsyncKeyState(i) & 1)
			{
				bool confirmed = false;
				for (int j = 0; j < 100; j++)
				{
					confirmed = GetAsyncKeyState(i);
				}

				if (confirmed)
				{
					buf = i;
					break;
				}
			}
		}
	} while (buf == 0);
	
	keybd_event(VK_BACK, 0, 0, 0); // Keydown
	keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0); // Keyup

	return buf;
}