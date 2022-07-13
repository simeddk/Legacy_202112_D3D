#pragma once

#include <Windows.h>
#include <functional>
#include <assert.h>
using namespace std;

class Timer
{
public:
	void SetTimer(function<void()> e, int millsec, UINT repeat = 0)
	{
		assert(bCompleted == false);

		bCompleted = false;

		thread t([=]()
		{
			while (true)
			{
				if (repeat > 0 && count == repeat)
					break;

				if (bCompleted == true)
					break;

				count++;

				Sleep(millsec);
				e();
			}

			ClearTimer();
		});

		t.detach();
	}

	void ClearTimer()
	{
		bCompleted = true;
		count = 0;
	}

private:
	bool bCompleted = false;
	UINT count = 0;
};