#ifndef Unit_MainH
#define Unit_MainH

#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

class TfrmMain : public TForm {
	__published:
		/**
		 * Elementos visuais.
		 */

		// Display.
		TLabel *lblRes;

		// Dígitos.
		TButton *btnNum0;
		TButton *btnNum1;
		TButton *btnNum2;
		TButton *btnNum3;
		TButton *btnNum4;
		TButton *btnNum5;
		TButton *btnNum6;
		TButton *btnNum7;
		TButton *btnNum8;
		TButton *btnNum9;
		TButton *btnCom;

		// Operações.
		TButton *btnPlu;
		TButton *btnMin;
		TButton *btnMul;
		TButton *btnDiv;
		TButton *btnEqu;

		// Funções.
		TButton *btnSwi;
		TButton *btnCle;
		TButton *btnCla;



		/**
		 * Eventos de entrada.
         */

		// Eventos dos dígitos.
		void __fastcall btnNum0Click(TObject *Sender);
		void __fastcall btnNum1Click(TObject *Sender);
		void __fastcall btnNum2Click(TObject *Sender);
		void __fastcall btnNum3Click(TObject *Sender);
		void __fastcall btnNum4Click(TObject *Sender);
		void __fastcall btnNum5Click(TObject *Sender);
		void __fastcall btnNum6Click(TObject *Sender);
		void __fastcall btnNum7Click(TObject *Sender);
		void __fastcall btnNum8Click(TObject *Sender);
		void __fastcall btnNum9Click(TObject *Sender);
        void __fastcall btnComClick(TObject *Sender);

		// Eventos das operações aritméticas.
		void __fastcall btnPluClick(TObject *Sender);
		void __fastcall btnMinClick(TObject *Sender);
		void __fastcall btnMulClick(TObject *Sender);
		void __fastcall btnDivClick(TObject *Sender);
        void __fastcall btnEquClick(TObject *Sender);

		// Eventos das funções da calculadora.
		void __fastcall btnSwiClick(TObject *Sender);
		void __fastcall btnCleClick(TObject *Sender);
		void __fastcall btnClaClick(TObject *Sender);

		// Eventos das teclas de atalho.
		void __fastcall frmMainKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall frmMainKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);

		// Evento de criação da janela.
		void __fastcall frmMainFormCreate(TObject *Sender);
	private:
		// Flags de funcionalidades.
		bool paused, equal, pressed;

		// Última operação selecionada.
		int operation;

		// Variáveis de armazenamento de valores.
		double stored, display;
	public:
        // Limpa o display.
		void clearEntry();

        // Calcula o resultado a partir do valor e da operação armazenados.
		void calculate();

        // Tratamento de erros.
		void error();

        // Aplica uma operação.
		void push(int op);

        // Reseta as variáveis.
		void reset();

        // Digita um número no display.
		void type(int n);

		__fastcall TfrmMain(TComponent *Owner);
};

extern PACKAGE TfrmMain *frmMain;

#endif