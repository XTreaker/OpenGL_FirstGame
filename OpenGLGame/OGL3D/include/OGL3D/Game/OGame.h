#pragma once
#include <memory>
class OWindow;
class OGame
{
public:
	OGame();
	~OGame();

	void run();
	void quit();

protected:
	bool m_isRunning = true; //flag if game is running
	std::unique_ptr<OWindow> m_display;
};

