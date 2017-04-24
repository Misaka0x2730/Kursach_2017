#pragma once

#include "ScanThread.h"

namespace Server {

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
	using namespace System::Resources;
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
			schedule = gcnew Schedule();
			textBox2->Text = "10032";
			//
			//TODO: добавьте код конструктора
			//
		}
		Schedule^ GetSchedule()
		{
			return schedule;
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
				return nullptr;
			else
				return value;
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
	private: System::Windows::Forms::ListBox^  listBox1;
	protected:
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Label^  label3;


	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Button^  button2;


	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::DateTimePicker^  dateTimePicker1;
	private: ScanThread^ threadScanData;
	private: Thread^ scanThread;
	private: Schedule^ schedule;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;
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
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->dateTimePicker1 = (gcnew System::Windows::Forms::DateTimePicker());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(6, 81);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(127, 95);
			this->listBox1->TabIndex = 0;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &ClientForm::listBox1_SelectedIndexChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 65);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(94, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Список клиентов";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->button1);
			this->groupBox1->Controls->Add(this->listBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(139, 220);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Настройки сервера";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(19, 32);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(100, 20);
			this->textBox2->TabIndex = 6;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(49, 16);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Порт";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(6, 182);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(127, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Сервер остановлен";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &ClientForm::startStopServerButton_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->button3);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Controls->Add(this->textBox3);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->dateTimePicker1);
			this->groupBox2->Location = System::Drawing::Point(157, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(235, 220);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Расписание";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(6, 182);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(212, 23);
			this->button3->TabIndex = 6;
			this->button3->Text = L"Отправить расписание";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &ClientForm::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(6, 153);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(212, 23);
			this->button2->TabIndex = 5;
			this->button2->Text = L"Сохранить расписание";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &ClientForm::button2_Click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(118, 62);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(100, 20);
			this->textBox3->TabIndex = 2;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 65);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(109, 13);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Длительность(мин):";
			// 
			// dateTimePicker1
			// 
			this->dateTimePicker1->CustomFormat = L"dd.MM.yyyy hh:mm:ss";
			this->dateTimePicker1->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dateTimePicker1->Location = System::Drawing::Point(6, 29);
			this->dateTimePicker1->Name = L"dateTimePicker1";
			this->dateTimePicker1->Size = System::Drawing::Size(212, 20);
			this->dateTimePicker1->TabIndex = 0;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(398, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(206, 220);
			this->textBox1->TabIndex = 4;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &ClientForm::timer1_Tick);
			// 
			// ClientForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(642, 252);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"ClientForm";
			this->Text = L"Управление сеансом связи v1.0";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ClientForm::ClientForm_Closing);
			this->Load += gcnew System::EventHandler(this, &ClientForm::ClientForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ClientForm_Load(System::Object^  sender, System::EventArgs^  e);

private: System::Void startStopServerButton_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void ClientForm_Closing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);
};
}
