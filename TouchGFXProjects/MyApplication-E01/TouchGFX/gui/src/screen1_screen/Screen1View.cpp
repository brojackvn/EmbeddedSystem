#include <gui/screen1_screen/Screen1View.hpp>
#include <cmsis_os.h>
Screen1View::Screen1View()
{
	tickCount = 0;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

extern osMessageQueueId_t Queue1Handle;
void Screen1View::handleTickEvent() {
	Screen1ViewBase::handleTickEvent(); // Call superclass eventhandler
	tickCount += 1;
	image1.setY(tickCount % 320);
	uint8_t res = 0;
	uint32_t count = osMessageQueueGetCount(Queue1Handle);

	if (count>0)
	{
		//note: the below fuction may block this thread
		osMessageQueueGet(Queue1Handle, &res, NULL, osWaitForever);
		if (res == 'R')
		{
			int16_t x = image1.getX();
			x += 2;
			if (x>240)
			{
				x = 0;
			}
			image1.setX(x);
		}
	}

	invalidate();
}
