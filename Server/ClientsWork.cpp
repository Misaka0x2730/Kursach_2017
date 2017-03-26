#include "ClientsWork.h"

ClientsWork::ClientsWork(void)
{
	collect = gcnew List<Client^>(defaultMaxSize);
	maxSize = defaultMaxSize;
}
ClientsWork::ClientsWork(Int32 amount)
{
	collect = gcnew List<Client^>(amount);
	if(amount <= defaultMaxSize)
		maxSize = defaultMaxSize;
	else
		maxSize = amount;
}
ClientsWork::ClientsWork(Int32 amount, Int32 max)
{
	collect = gcnew List<Client^>(amount);
	if(amount <= max)
		maxSize = max;
	else
		maxSize = amount;
}
ClientsWork::~ClientsWork()
{
	System::Boolean lock = false;
	try
	{
		Block(lock);
		RemoveAll();
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}

Int32 ClientsWork::Add(Client^ client)
{
	Int32 position = -1;
	bool lock = false;
	try
	{
		Block(lock);
		if((Count < maxSize)&&(Contains(client->Login) == false))
		{
			collect->Add(client);
			position = Count -1;
		}
		return position;
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
Int32 ClientsWork::Add(TcpClient^ client, String^ login)
{
	Int32 position = -1;
	bool lock = false;
	try
	{
		Block(lock);
		if((Count < maxSize)&&(Contains(login) == false))
		{
			Client^ temp = gcnew Client(client,login);
			collect->Add(temp);
			position = Count -1;
		}
		return position;
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
void ClientsWork::Clear()
{
	bool lock = false;
	try
	{
		Block(lock);
		collect->Clear();
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
bool ClientsWork::Contains(Client^ value)
{
	bool inList = false;
	bool lock = false;
	try
	{
		Block(lock);
		for (int i = 0; i < Count; i++)
		{
			if (collect[i]->Equals(value) == true)
			{
				inList = true;
				break;
			}
		}
		return inList;
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
bool ClientsWork::Contains(String^ login)
{
	bool inList = false;
	bool lock = false;
	try
	{
		Block(lock);
		for (int i = 0; i < Count; i++)
		{
			if (collect[i]->Equals(login) == true)
			{
				inList = true;
				break;
			}
		}
		return inList;
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
void ClientsWork::CopyTo(Array^ arr, int index)
{
	bool lock = false;
	try
	{
		Block(lock);
		Int32 j = index;
		for(Int32 i = 0; i < Count; i++)
		{
			if(j < arr->Length)
			{
			arr->SetValue(collect,j);
			j++;
			}
			else
				return;
		}
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
Int32 ClientsWork::IndexOf(Client^ value)
{
    Int32 itemIndex = -1;
	bool lock = false;
	try
	{
		Block(lock);
		for (int i = 0; i < Count; i++)
		{
			if (collect[i]->Equals(value) == true)
			{
				itemIndex = i;
				break;
			}
		}
		return itemIndex;
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
Int32 ClientsWork::IndexOf(String^ login)
{
	bool lock = false;
	try
	{
		Block(lock);
		Int32 itemIndex = -1;
		for (int i = 0; i < Count; i++)
		{
			if (collect[i]->Equals(login) == true)
			{
				itemIndex = i;
				break;
			}
		}
    return itemIndex;
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
void ClientsWork::Insert(int index, Client^ value)
{
	bool lock = false;
	try
	{
		Block(lock);
		if ((index < maxSize) && (index >= 0))
		{
			for (int i = Count - 1; i > index; i--)
				collect[i] = collect[i - 1];
			collect[index] = value;
		}
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
void ClientsWork::Remove(Client^ value)
{
	bool lock = false;
	try
	{
		Block(lock);
		RemoveAt(IndexOf(value));
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
	
}
void ClientsWork::RemoveAt(int index)
{
	bool lock = false;
	try
	{
		Block(lock);
		if ((index >= 0) && (index < Count))
		{
			for (int i = index; i < Count - 1; i++)
				collect[i] = collect[i + 1];
			collect->RemoveAt(Count - 1);
		}
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}
void ClientsWork::RemoveAll(void)
{
	bool lock = false;
	try
	{
		Block(lock);
		while(Count > 0)
			RemoveAt(0);
	}
	finally
	{
		if(lock)
			UnBlock(lock);
	}
}

void ClientsWork::Block(bool% lock)
{
	Monitor::Enter(SyncRoot, lock);
}
void ClientsWork::UnBlock(bool% lock)
{
	if(lock)
	{
		Monitor::Pulse(SyncRoot);
		Monitor::Exit(SyncRoot);
	}
}