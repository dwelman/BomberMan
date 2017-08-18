#include <main.hpp>

int	 AudioThread(void *ptr)
{
	AudioManager	*audioManager = reinterpret_cast<AudioManager*>(ptr);

	// do
	// {
	// 	//audioManager->executeQue();
	// } while (0); // Add audioManager->running() or something;
	audioManager->execQueue();

	return (0);
}
