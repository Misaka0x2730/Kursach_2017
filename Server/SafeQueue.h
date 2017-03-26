#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;

public ref class SafeQueue abstract sealed
{
	public:
		static void Block(Object^ obj)
		{
			Monitor::Enter(obj);
		}
		static void UnBlock(Object^ obj)
		{
			Monitor::PulseAll(obj);
			Monitor::Exit(obj);
		}
};
