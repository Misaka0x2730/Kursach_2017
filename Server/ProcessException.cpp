#include "stdafx.h"
#include "ProcessException.h"

System::Void ProcessException::MessageException(Exception^ e, System::Type^ type, String^ method)
{
	MessageBox::Show(e->Message + Environment::NewLine + e->TargetSite->Name,type->Name+" "+method);
}
System::Void ProcessException::MessageException(Exception^ e, String^ type, String^ method)
{
	MessageBox::Show(e->Message + Environment::NewLine + e->TargetSite->Name,type+" "+method);
}
System::Void ProcessException::MessageException(String^ message, String^ target, String^ type, String^ method)
{
	MessageBox::Show(message + Environment::NewLine + target+type+"::"+method);
}
System::Void ProcessException::MessageException(Exception^ e, System::Type^ type, MethodBase^ method)
{
	MessageBox::Show(e->Message + Environment::NewLine + e->TargetSite->Name,type->Name+" "+method->Name);
}
System::Void ProcessException::MessageException(Exception^ e, String^ type, MethodBase^ method)
{
	MessageBox::Show(e->Message + Environment::NewLine + e->TargetSite->Name,type+" "+method->Name);
}