#pragma once

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Security::Cryptography;
	using namespace System::Text;
	using namespace System::Resources;
	using namespace System::Threading;
	using namespace System::Configuration;
	/// <summary>
	/// Сводка для ClientForm
	/// </summary>
	public ref class ClientForm : public System::Windows::Forms::Form
	{
	public:
		ClientForm(void)
		{
			InitializeComponent();
			timer1->Interval = 1000;
			timer1->Enabled = true;
			networkState = true;
			timer1_Tick((System::Object^)timer1, nullptr);

			if (ReadSetting("serverIP") == String::Empty)
				AddUpdateSetting("serverIP", "127.0.0.1");

			if (ReadSetting("serverPort") == String::Empty)
				AddUpdateSetting("serverPort", "10032");
	
			ipBox->Text = ReadSetting("serverIP");
			portBox->Text = ReadSetting("serverPort");
			/*if (ReadSetting("schedule") == String::Empty)
			{
				MessageBox::Show("Расписание не получено", "Расписание не получено");
				label4->Text = "Сеть включена";
			}
			else
			{

			}*/
			//
			//TODO: добавьте код конструктора
			//
		}
		void AddUpdateSetting(String^ key, String^ value)
		{
			ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);
			System::Configuration::Configuration^ configFile = ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);
			System::Configuration::KeyValueConfigurationCollection^ settings = configFile->AppSettings->Settings;
			if (settings[key] == nullptr)
				settings->Add(key, value);
			else
				settings[key]->Value = value;

			configFile->Save(ConfigurationSaveMode::Modified);
			ConfigurationManager::RefreshSection(configFile->AppSettings->SectionInformation->Name);
		}
		String^ ReadSetting(String^ key)
		{
			System::Collections::Specialized::NameValueCollection^ appSettings = ConfigurationManager::AppSettings;
			String^ value = appSettings[key];
			if (value == nullptr)
				return String::Empty;
			else
				return value;
		}
		void NetworkChangeState(bool state)
		{
			if ((state == true) && (networkState == false))
			{
				label4->Text = "Сеть включена";
				networkState = true;
				MessageBox::Show("Сеть включена!");
			}
			if ((state == false) && (networkState == true))
			{
				label4->Text = "Сеть выключена";
				networkState = false;
				MessageBox::Show("Сеть выключена!");
			}
		}
	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~ClientForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  ipBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  portBox;
	private: System::Windows::Forms::Button^  connectBox;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: Thread^ newClient;
	private: bool networkState;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ipBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->portBox = (gcnew System::Windows::Forms::TextBox());
			this->connectBox = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(98, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"IP-адрес сервера:";
			// 
			// ipBox
			// 
			this->ipBox->Location = System::Drawing::Point(15, 25);
			this->ipBox->Name = L"ipBox";
			this->ipBox->Size = System::Drawing::Size(100, 20);
			this->ipBox->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 65);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(32, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Порт";
			// 
			// portBox
			// 
			this->portBox->Location = System::Drawing::Point(15, 81);
			this->portBox->Name = L"portBox";
			this->portBox->Size = System::Drawing::Size(100, 20);
			this->portBox->TabIndex = 3;
			// 
			// connectBox
			// 
			this->connectBox->Location = System::Drawing::Point(15, 107);
			this->connectBox->Name = L"connectBox";
			this->connectBox->Size = System::Drawing::Size(100, 23);
			this->connectBox->TabIndex = 4;
			this->connectBox->Text = L"Подключиться";
			this->connectBox->UseVisualStyleBackColor = true;
			this->connectBox->Click += gcnew System::EventHandler(this, &ClientForm::button1_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 161);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(108, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Сетевое состояние:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(126, 161);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(83, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"Сеть включена";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ClientForm::timer1_Tick);
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(237, 196);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->connectBox);
			this->Controls->Add(this->portBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->ipBox);
			this->Controls->Add(this->label1);
			this->Name = L"ClientForm";
			this->Text = L"Клиент";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ClientForm::clientForm_Closing);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void clientForm_Closing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
};
}
