#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <msclr\marshal_cppstd.h>


namespace ship {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using std::string;
    using std::pair;
    using std::vector;
    using std::ofstream;
    using std::ifstream;
    using std::min;
    using std::endl;
    using std::to_string;
    struct charr {
        char have;
        vector<charr*> childs;
        void resiz(int a) {
            for (int i = 0; i < a; ++i) {
                childs.push_back(new charr);
            }
        }
        charr() {
            have = false;
        }
        charr(int a) {
            have = false;
            childs.resize(a, new charr);
        }
    };

    bool comp(pair<string, int> fir, pair<string, int> sec) {
        if (fir.second < sec.second) {
            return true;
        }
        else if (fir.second > sec.second) {
            return false;
        }
        else {
            return fir.first < sec.first;
        }
    }

    double gackar(string str1, string str2) {
        vector<char> used(str2.size(), false);
        float num = 0;
        float num2 = 0;
        float tug = 0;
        vector<char> arr(288, false);
        for (int i = 0; i < str1.size(); ++i) {
            int lol = (int)str1[i];
            if (arr[(int)str1[i] + 32]) {
                num++;
                continue;
            }
            for (int j = 0; j < str2.size(); ++j) {
                if (used[j]) continue;
                if (str2[j] == str1[i]) {
                    used[j] = true;
                    tug++;
                    break;
                }
            }
        }
        for (int i = 0; i < str2.size(); ++i) {
            if (used[i]) continue;
            if (!arr[(int)str2[i]]) {
                num2++;
                arr[(int)str2[i]] = true;
            }
        }
        return tug / (num + tug + num2);
    }

    long long Dam_Lev(string first_str, string second_str, int cur_norm)
    {
        int number_sec = second_str.size();
        int number_frst = first_str.size();
        vector<int> now_str(number_sec + 1);
        vector<int> prev_str(number_sec + 1);
        vector<int> prev_prev_str(number_sec + 1);

        for (int i = 0; i <= number_sec; ++i)
        {
            now_str[i] = prev_str[i] = i;
        }

        for (int i = 1; i <= number_frst; ++i)
        {
            prev_prev_str = prev_str;
            prev_str = now_str;
            now_str[0] = i;
            for (int j = 1; j <= number_sec; ++j)
            {
                now_str[j] = min(
                    prev_str[j] + 1, min(
                        now_str[j - 1] + 1,
                        prev_str[j - 1] +
                        (int)(!(first_str[i - 1] == second_str[j - 1]))));
                if (i > 1 && j > 1 && first_str[i - 1] == second_str[j - 2] && first_str[i - 2] == second_str[j - 1])
                {
                    now_str[j] = min(
                        now_str[j],
                        (prev_prev_str[j - 2] +
                        (int)(!(first_str[i - 1] == second_str[j - 1]))));
                }
            }
        }
        return now_str[number_sec];
    }

    long long Lev(string first_str, string second_str, int cur_norm)
    {
        int number_sec = second_str.size();
        int number_frst = first_str.size();
        vector<int> now_str(number_sec + 1);
        vector<int> prev_str(number_sec + 1);
        vector<int> prev_prev_str(number_sec + 1);

        for (int i = 0; i <= number_sec; ++i)
        {
            now_str[i] = prev_str[i] = i;
        }

        for (int i = 1; i <= number_frst; ++i)
        {
            prev_prev_str = prev_str;
            prev_str = now_str;
            now_str[0] = i;
            for (int j = 1; j <= number_sec; ++j)
            {
                now_str[j] = min(
                    prev_str[j] + 1, min(
                        now_str[j - 1] + 1,
                        prev_str[j - 1] +
                        (int)(!(first_str[i - 1] == second_str[j - 1]))));
            }
        }
        return now_str[number_sec];
    }

    vector<pair<string, int>> find(const string str, vector<vector<string>>& strs, const int norm) {
        vector<pair<string, int>> fins;
        int cur_norm = (str.size() / 10 + 1) * norm;
        int piter = str.size() - cur_norm;
        piter = max(piter, 0);
        for (int i = piter; i < str.size() + cur_norm; ++i) {
            for (int j = 0; j < strs[i].size(); ++j) {
                int numb = Dam_Lev(str, strs[i][j], cur_norm);
                if (numb == -1) continue;
                if (numb <= cur_norm) {
                    fins.push_back(pair<string, int>(strs[i][j], numb));
                }
            }
        }
        sort(fins.begin(), fins.end(), comp);
        return fins;
    }

    bool chek_str(string str, charr *start) {
        int i = 0;
        int num = 0;
        char ch;
        charr *cur_ch = start;
        for (; i < str.size(); ++i) {
            ch = str[i];
            if ((int)ch == 39 || (ch >= 97 && ch < 123 || ch == ' ' || ch == '-' || ch == ':' || ch == ',' || ch == '.' || ch == '/' || ch == ')' || ch == '(' || ch == '?' || ch == '!' || ch == '"' || ch == ';')) {
                if (ch == ' ' || ch == '-' || ch == ':' || ch == ',' || ch == '.' || ch == '/' || ch == ')' || ch == '(' || ch == '?' || ch == '!' || ch == '"' || ch == ';') {
                    num = 0;
                    cur_ch = start;
                    continue;
                }
                else {
                    if ((int)ch == 39) {
                        if (cur_ch->childs[26] == NULL) return false;
                        if (cur_ch->childs[26]->have) {
                            cur_ch = cur_ch->childs[26];
                        }
                        else {
                            return false;
                        }
                    }
                    else {
                        if (cur_ch->childs[ch - 97] == NULL) return false;
                        if (cur_ch->childs[ch - 97]->have) {
                            cur_ch = cur_ch->childs[ch - 97];
                        }
                        else {
                            return false;
                        }
                    }
                }
            }
            else {
                return false;
            }
        }
        return true;
    }
    ifstream fin("input.txt");
    ifstream in_elib("eng_lib.txt");
    ifstream in_wlib("wrong_lib.txt");
    ifstream in_rdict("rus_dict.txt");
    ifstream in_edict("eng_dict.txt");
    ofstream fout("output.txt");
    ofstream out_lib("eng_lib.txt", std::ios::app);
    ofstream out_wlib("wrong_lib.txt", std::ios::app);
    vector<vector<string>> strs(10000);
    vector<vector<string>> wstrs(10000);
    charr* eng_dict = new charr;

    int norm = 2;
    

	string SystemToStl(String ^s)
	{
		using namespace Runtime::InteropServices;
		const char* ptr = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		return string(ptr);
	}
	/// <summary>
	/// Сводка для MyForm
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		//Chess * ch;
        int num_of_words = 0;
        int num_of_strings = 0;
        int num_of_used_str = 0;
    private: System::Windows::Forms::RichTextBox^  richTextBox6;
    private: System::Windows::Forms::RichTextBox^  richTextBox7;
    private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
    private: System::Windows::Forms::Button^  button3;
    public:

		bool unpause;
        void update() {
            string text3 = "num of words in dictionary: " + to_string(num_of_words);
            richTextBox3->Text = msclr::interop::marshal_as<System::String^>(text3);
            string text4 = "num of strings in library: " + to_string(num_of_strings);
            richTextBox4->Text = msclr::interop::marshal_as<System::String^>(text4);
            string text5 = "num of strings at this session: " + to_string(num_of_used_str);
            richTextBox5->Text = msclr::interop::marshal_as<System::String^>(text5);
        }
		MyForm(void)
		{
			InitializeComponent();
           // openFileDialog1->Filter = "Text files(*.txt)|*.txt|All files(*.*)|*.*";
		
			unpause = true;
			//ch = new Chess;
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
            fin.close();
            in_elib.close();
            in_wlib.close();
            in_rdict.close();
            in_edict.close();
            fout.close();
            out_lib.close();
            out_wlib.close();
		}
    private: System::Windows::Forms::RichTextBox^  richTextBox1;
    protected:
    private: System::Windows::Forms::RichTextBox^  richTextBox2;
    private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
    private: System::Windows::Forms::Button^  button1;
    private: System::Windows::Forms::Button^  button2;
    private: System::Windows::Forms::RichTextBox^  richTextBox3;
    private: System::Windows::Forms::RichTextBox^  richTextBox4;
    private: System::Windows::Forms::RichTextBox^  richTextBox5;
             //private: vector<Control^>* pct;







	protected:



	protected:

	protected:

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
            this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
            this->richTextBox2 = (gcnew System::Windows::Forms::RichTextBox());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            this->button1 = (gcnew System::Windows::Forms::Button());
            this->button2 = (gcnew System::Windows::Forms::Button());
            this->richTextBox3 = (gcnew System::Windows::Forms::RichTextBox());
            this->richTextBox4 = (gcnew System::Windows::Forms::RichTextBox());
            this->richTextBox5 = (gcnew System::Windows::Forms::RichTextBox());
            this->richTextBox6 = (gcnew System::Windows::Forms::RichTextBox());
            this->richTextBox7 = (gcnew System::Windows::Forms::RichTextBox());
            this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
            this->button3 = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
            this->SuspendLayout();
            // 
            // richTextBox1
            // 
            this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->richTextBox1->Location = System::Drawing::Point(36, 106);
            this->richTextBox1->Name = L"richTextBox1";
            this->richTextBox1->Size = System::Drawing::Size(515, 40);
            this->richTextBox1->TabIndex = 0;
            this->richTextBox1->Text = L"";
            this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox1_TextChanged);
            // 
            // richTextBox2
            // 
            this->richTextBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->richTextBox2->Location = System::Drawing::Point(639, 36);
            this->richTextBox2->Name = L"richTextBox2";
            this->richTextBox2->ReadOnly = true;
            this->richTextBox2->Size = System::Drawing::Size(398, 503);
            this->richTextBox2->TabIndex = 1;
            this->richTextBox2->Text = L"";
            // 
            // button1
            // 
            this->button1->Location = System::Drawing::Point(36, 163);
            this->button1->Name = L"button1";
            this->button1->Size = System::Drawing::Size(87, 25);
            this->button1->TabIndex = 2;
            this->button1->Text = L"From file";
            this->button1->UseVisualStyleBackColor = true;
            this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
            // 
            // button2
            // 
            this->button2->Location = System::Drawing::Point(437, 165);
            this->button2->Name = L"button2";
            this->button2->Size = System::Drawing::Size(114, 23);
            this->button2->TabIndex = 3;
            this->button2->Text = L"Count!";
            this->button2->UseVisualStyleBackColor = true;
            this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
            // 
            // richTextBox3
            // 
            this->richTextBox3->Location = System::Drawing::Point(36, 447);
            this->richTextBox3->Name = L"richTextBox3";
            this->richTextBox3->ReadOnly = true;
            this->richTextBox3->Size = System::Drawing::Size(291, 27);
            this->richTextBox3->TabIndex = 4;
            this->richTextBox3->Text = L"";
            // 
            // richTextBox4
            // 
            this->richTextBox4->Location = System::Drawing::Point(36, 480);
            this->richTextBox4->Name = L"richTextBox4";
            this->richTextBox4->ReadOnly = true;
            this->richTextBox4->Size = System::Drawing::Size(291, 27);
            this->richTextBox4->TabIndex = 5;
            this->richTextBox4->Text = L"";
            // 
            // richTextBox5
            // 
            this->richTextBox5->Location = System::Drawing::Point(36, 513);
            this->richTextBox5->Name = L"richTextBox5";
            this->richTextBox5->ReadOnly = true;
            this->richTextBox5->Size = System::Drawing::Size(291, 26);
            this->richTextBox5->TabIndex = 6;
            this->richTextBox5->Text = L"";
            // 
            // richTextBox6
            // 
            this->richTextBox6->Enabled = false;
            this->richTextBox6->Location = System::Drawing::Point(36, 69);
            this->richTextBox6->Name = L"richTextBox6";
            this->richTextBox6->Size = System::Drawing::Size(515, 22);
            this->richTextBox6->TabIndex = 7;
            this->richTextBox6->Text = L"Введите строку для сравнения в поле ниже либо загрузите из файла";
            this->richTextBox6->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox6_TextChanged);
            // 
            // richTextBox7
            // 
            this->richTextBox7->Enabled = false;
            this->richTextBox7->Location = System::Drawing::Point(36, 221);
            this->richTextBox7->Name = L"richTextBox7";
            this->richTextBox7->Size = System::Drawing::Size(515, 34);
            this->richTextBox7->TabIndex = 8;
            this->richTextBox7->Text = L"Поле ниже характеризует количество допустимых \'ошибок\' на десять символов (уровен"
                L"ь минимальной необходимой похожести)";
            this->richTextBox7->TextChanged += gcnew System::EventHandler(this, &MyForm::richTextBox7_TextChanged);
            // 
            // numericUpDown1
            // 
            this->numericUpDown1->Location = System::Drawing::Point(36, 276);
            this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
            this->numericUpDown1->Name = L"numericUpDown1";
            this->numericUpDown1->Size = System::Drawing::Size(120, 20);
            this->numericUpDown1->TabIndex = 9;
            this->numericUpDown1->Tag = L"";
            this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2, 0, 0, 0 });
            // 
            // button3
            // 
            this->button3->Location = System::Drawing::Point(36, 319);
            this->button3->Name = L"button3";
            this->button3->Size = System::Drawing::Size(87, 25);
            this->button3->TabIndex = 10;
            this->button3->Text = L"Refresh!";
            this->button3->UseVisualStyleBackColor = true;
            this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1100, 600);
            this->Controls->Add(this->button3);
            this->Controls->Add(this->numericUpDown1);
            this->Controls->Add(this->richTextBox7);
            this->Controls->Add(this->richTextBox6);
            this->Controls->Add(this->richTextBox5);
            this->Controls->Add(this->richTextBox4);
            this->Controls->Add(this->richTextBox3);
            this->Controls->Add(this->button2);
            this->Controls->Add(this->button1);
            this->Controls->Add(this->richTextBox2);
            this->Controls->Add(this->richTextBox1);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            this->Margin = System::Windows::Forms::Padding(2);
            this->MaximizeBox = false;
            this->Name = L"MyForm";
            this->Text = L"Сравнение строк";
            this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
            this->ResumeLayout(false);

        }

#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
   
        string str;
        while (getline(in_edict, str)) {
            num_of_words++;
            charr* cur_ch = eng_dict;
            for (int i = 0; i < str.size(); ++i) {
                if (cur_ch->childs.size() == 0) {
                    cur_ch->resiz(27);
                }
                char ch = str[i];
                if ((int)ch == 39) {
                    cur_ch->childs[26]->have = true;
                    cur_ch = cur_ch->childs[26];
                }
                else {
                    cur_ch->childs[ch - 97]->have = true;
                    cur_ch = cur_ch->childs[ch - 97];
                }
            }
        }
        while (getline(in_wlib, str)) {
            num_of_strings++;
            if (str[0] == '\n') {
                break;
            }
            wstrs[str.size() - 1].push_back(str);
        }
        while (getline(in_elib, str)) {
            num_of_strings++;
            if (str[0] == '\n') {
                break;
            }
            strs[str.size() - 1].push_back(str);
        }
        update();


	}

	
             private:
                 void button1_Click(System::Object ^ sender,
                     System::EventArgs ^ e)
                 {
                     if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
                     {
                         System::IO::StreamReader ^ sr = gcnew
                             System::IO::StreamReader(openFileDialog1->FileName);
                         sr->CurrentEncoding->UTF32;
                         String ^ strt = sr->ReadToEnd();
                         richTextBox1->Text = strt;
                         sr->Close();
                     }
                 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
    string str = SystemToStl(richTextBox1->Text);
    if (str.size() > 1000) {
        str.resize(999);
    }
    num_of_used_str++;
    vector<pair<string, int>> arr = find(str, strs, norm);
    vector<pair<string, int>> warr = find(str, wstrs, norm);
  
    if (str.size() > 0 && chek_str(str, eng_dict)) {
        if (arr.size() == 0 || arr[0].second != 0) {
            strs[str.size() - 1].push_back(str);
            out_lib << str << endl;
            num_of_strings++;
        }
    }
    else {
        if (str.size() > 0 && (warr.size() == 0 || warr[0].second != 0)) {
            wstrs[str.size() - 1].push_back(str);
            out_wlib << str << endl;
            num_of_strings++;
        }
    }

    string outt;
    outt += "for string: '";
    outt += str;
    outt += "'\n";
    outt += "\n    from right lib:\n\n";
    if (arr.size() == 0) {
        outt += "nothing\n\n";
    }
    for (int i = 0; i < arr.size(); ++i) {
        float numbb = gackar(str, arr[i].first);
        outt += arr[i].first;
        outt += "\n        dam-lev:  ";
        outt += to_string(arr[i].second);
        outt += "\n        lev: ";
        outt += to_string(Lev(str, arr[i].first, norm));
        outt += "\n        koef. jak: ";
        outt += to_string(numbb);
        outt += "\n";
    }
    outt += "\n    from wrong lib:\n\n";
    if (warr.size() == 0) {
        outt += "nothing\n\n";
    }
    for (int i = 0; i < warr.size(); ++i) {
        float numbb = gackar(str, warr[i].first);
        outt += warr[i].first;
        outt += "\n        dam-lev:  ";
        outt += to_string(warr[i].second);
        outt += "\n        lev: ";
        outt += to_string(Lev(str, warr[i].first, norm));
        outt += "\n        koef. jak: ";
        outt += to_string(numbb);
        outt += "\n";
    }
    String ^ strtr = msclr::interop::marshal_as<System::String^>(outt);
    richTextBox2->Text = strtr;
    update();    
}

private: System::Void richTextBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void richTextBox6_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void richTextBox7_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
    Decimal in =  this->numericUpDown1->Value;
    norm = Decimal::ToInt16(in);
}
};
}

