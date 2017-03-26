#pragma once
#include "ScanThread.h"

namespace ServerXp 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
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
	using namespace MyExtendControls;

	public ref class StatMenuXp : public System::Windows::Forms::Form
	{
		public:
			StatMenuXp(void)
			{
				InitializeComponent();
			}
		protected:
			~StatMenuXp()
			{
				if (components)
				{
					delete components;
				}
			}
		private: System::Windows::Forms::TextBox^  countOnlineBox;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::TextBox^  countThreadBox;
		private: System::Windows::Forms::Button^  startServerButton;
		private: System::Windows::Forms::Button^  stopServerButton;
		private: System::Net::Sockets::TcpListener^ server;
		private: System::Windows::Forms::Label^  label3;
		private: System::ComponentModel::IContainer^  components;
		private: ScanThread^ threadScanData;
		private: Thread^ scanThread;
		private: ListOfOnline^  onlineList;

	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(StatMenuXp::typeid));
			this->onlineList = (gcnew MyExtendControls::ListOfOnline());
			this->countOnlineBox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->countThreadBox = (gcnew System::Windows::Forms::TextBox());
			this->startServerButton = (gcnew System::Windows::Forms::Button());
			this->stopServerButton = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// onlineList
			// 
			this->onlineList->BackColor = System::Drawing::Color::MintCream;
			this->onlineList->Location = System::Drawing::Point(12, 103);
			this->onlineList->Name = L"onlineList";
			this->onlineList->Size = System::Drawing::Size(167, 121);
			this->onlineList->TabIndex = 9;
			this->onlineList->UseCompatibleStateImageBehavior = false;
			this->onlineList->View = System::Windows::Forms::View::SmallIcon;
			// 
			// countOnlineBox
			// 
			this->countOnlineBox->BackColor = System::Drawing::Color::MintCream;
			this->countOnlineBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->countOnlineBox->HideSelection = false;
			this->countOnlineBox->Location = System::Drawing::Point(12, 25);
			this->countOnlineBox->Name = L"countOnlineBox";
			this->countOnlineBox->ReadOnly = true;
			this->countOnlineBox->Size = System::Drawing::Size(167, 20);
			this->countOnlineBox->TabIndex = 0;
			this->countOnlineBox->TabStop = false;
			this->countOnlineBox->Text = L"Сервер остановлен";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(144, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Количество клиентов онлайн:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Location = System::Drawing::Point(9, 48);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(170, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Количество потоков для клиентов:";
			// 
			// countThreadBox
			// 
			this->countThreadBox->BackColor = System::Drawing::Color::MintCream;
			this->countThreadBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->countThreadBox->Location = System::Drawing::Point(12, 64);
			this->countThreadBox->Name = L"countThreadBox";
			this->countThreadBox->ReadOnly = true;
			this->countThreadBox->Size = System::Drawing::Size(167, 20);
			this->countThreadBox->TabIndex = 3;
			this->countThreadBox->TabStop = false;
			this->countThreadBox->Text = L"Сервер остановлен";
			// 
			// startServerButton
			// 
			this->startServerButton->BackColor = System::Drawing::Color::Transparent;
			this->startServerButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->startServerButton->Location = System::Drawing::Point(15, 243);
			this->startServerButton->Name = L"startServerButton";
			this->startServerButton->Size = System::Drawing::Size(75, 23);
			this->startServerButton->TabIndex = 0;
			this->startServerButton->TabStop = false;
			this->startServerButton->Text = L"Запуск!";
			this->startServerButton->UseVisualStyleBackColor = false;
			this->startServerButton->Click += gcnew System::EventHandler(this, &StatMenuXp::startServerButton_Click);
			// 
			// stopServerButton
			// 
			this->stopServerButton->BackColor = System::Drawing::Color::Transparent;
			this->stopServerButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->stopServerButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->stopServerButton->Location = System::Drawing::Point(104, 243);
			this->stopServerButton->Name = L"stopServerButton";
			this->stopServerButton->Size = System::Drawing::Size(75, 23);
			this->stopServerButton->TabIndex = 6;
			this->stopServerButton->TabStop = false;
			this->stopServerButton->Text = L"Стоп";
			this->stopServerButton->UseVisualStyleBackColor = false;
			this->stopServerButton->Click += gcnew System::EventHandler(this, &StatMenuXp::stopServerButton_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Location = System::Drawing::Point(9, 87);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(129, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Подключенные клиенты:";
			// 
			// StatMenuXp
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(511, 275);
			this->Controls->Add(this->onlineList);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->stopServerButton);
			this->Controls->Add(this->startServerButton);
			this->Controls->Add(this->countThreadBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->countOnlineBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"StatMenuXp";
			this->Text = L"RailServer";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &StatMenuXp::StatMenu_Closing);
			this->Load += gcnew System::EventHandler(this, &StatMenuXp::StatMenu_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void StatMenu_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void startServerButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void stopServerButton_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void StatMenu_Closing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
};
}
