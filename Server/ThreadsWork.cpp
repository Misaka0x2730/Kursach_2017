#include "stdafx.h"
#include "ThreadsWork.h"

ThreadWork::ThreadWork(void)
{
	collectThread = gcnew List<Thread^>(6);
	maxSize = defaultMaxSize;
}
ThreadWork::ThreadWork(Int32 amount)
{
	collectThread = gcnew List<Thread^>(amount);
	if(amount <= defaultMaxSize)
		maxSize = defaultMaxSize;
	else
		maxSize = amount;
}
ThreadWork::ThreadWork(Int32 amount, Int32 max)
{
	collectThread = gcnew List<Thread^>(amount);
	if(amount <= max)
		maxSize = max;
	else
		maxSize = amount;
}
ThreadWork::~ThreadWork()
{
	//RemoveAll();
}
Int32 ThreadWork::Add(Thread^ thread)
{
	Int32 position = -1;
	if(Count < maxSize)
	{
		collectThread->Add(thread);
		position = Count - 1;
	}
	return position;
}
void ThreadWork::Clear()
{
	collectThread->Clear();
}
void ThreadWork::CopyTo(Array^ array, int index)
{
	Int32 j = index;
	for(Int32 i = 0; i < Count; i++)
	{
		array->SetValue(collectThread,j);
		j++;
	}
}
Int32 ThreadWork::IndexOf(Thread^ value)
{
    Int32 itemIndex = -1;
    for (int i = 0; i < Count; i++)
    {
		if (collectThread[i]->Equals(value) == true)
        {
            itemIndex = i;
            break;
        }
    }
    return itemIndex;
}
void ThreadWork::Insert(int index, Thread^ value)
{
	if ((index < maxSize) && (index >= 0))
{
	for (int i = Count - 1; i > index; i--)
		collectThread[i] = collectThread[i - 1];
	collectThread[index] = value;
}
}
void ThreadWork::Remove(Thread^ value)
{
	RemoveAt(IndexOf(value));
}
void ThreadWork::RemoveAt(int index)
{
	if ((index >= 0) && (index < Count))
	{
		collectThread[index]->Abort();
		for (int i = index; i < Count - 1; i++)
			collectThread[i] = collectThread[i + 1];
		if(collectThread[Count-1]->IsAlive)
			collectThread[Count - 1]->Abort();
		collectThread->RemoveAt(Count - 1);
	}
}
void ThreadWork::RemoveAll(void)
{
	while(Count > 0)
		RemoveAt(0);
}
void ThreadWork::CheckAlive(void)
{
	for(Int32 i = 0; i < Count; i++)
		if((collectThread[i] != nullptr)&&(collectThread[i]->IsAlive == false))
			RemoveAt(i);
}
void ThreadWork::Block(bool% lock)
{
	Monitor::Enter(SyncRoot,lock);
}
void ThreadWork::UnBlock(bool% lock)
{
	if(lock)
	{
		Monitor::PulseAll(SyncRoot);
		Monitor::Exit(SyncRoot);
	}
}
