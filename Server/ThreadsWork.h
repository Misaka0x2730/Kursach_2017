#pragma once

#define defaultMaxSize 6

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::Text;
using namespace System::Security::Cryptography;
using namespace System::Media;
using namespace System::Reflection;

public ref class ThreadWork
{
private:
	List<Thread^>^ collectThread;
	Int32 maxSize;
public: 
	ThreadWork(void);
	ThreadWork(Int32 amount);
	ThreadWork(Int32 amount, Int32 max);

	property Int32 Count
	{
		Int32 get()
		{
			return collectThread->Count;
		}
	}
	property Thread^ default[Int32]
	{
		Thread^ get(Int32 index)
		{
			return collectThread[index];
		}

		void set(Int32 index, Thread^ value)
		{
			collectThread[index] = value;
		}
	}
	property Object^ SyncRoot
	{
		Object^ get()
		{
			return this;
		}
	}

	Int32 Add(Thread^ thread);
	void Clear(void);
	void CopyTo(Array^ array, int index);
	Int32 IndexOf(Thread^ value);
	void Insert(int index, Thread^ value);
	void Remove(Thread^ value);
	void RemoveAt(int index);
	void RemoveAll(void);
	void CheckAlive(void);
};