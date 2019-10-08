#include <vcl.h>
#include <iomanip>
#include <iostream>

#pragma hdrstop
#include "Unit_Main.h"

#pragma package(smart_init)
#pragma resource "*.dfm"

#define DISPLAY_LEN 10

TfrmMain *frmMain;

__fastcall TfrmMain::TfrmMain(TComponent* Owner) : TForm(Owner) {}



/**
 * Limpa o display.
 */
void TfrmMain::clearEntry() {
	lblRes->Caption = 0;
}



/**
 * Calcula o resultado a partir do valor e da operação armazenados.
 */
void TfrmMain::calculate() {
	switch (operation) {
		// Adição.
		case 1:
			stored += display;
			break;
		// Subtração.
		case 2:
			stored -= display;
			break;
		// Multiplicação.
		case 3:
			stored *= display;
			break;
        // Divisão.
		case 4:
			stored /= display;
			break;
        // Operação não definida.
		default:
			stored = display;
            equal = false;
			break;
	}

	// Obtém a quantidade de caracteres do resultado.
	int storedLen = AnsiString(abs((long long int) stored)).Length();

    // Retorna erro caso a quantidade de caracteres seja maior que DISPLAY_LEN.
	if (storedLen > DISPLAY_LEN) {
        return error();
	}

    // Calcula a quantidade de casas decimais.
	int precision = pow(10, DISPLAY_LEN - storedLen - 1);

    // Armazena o valor a ser mostrado no display.
	double caption;

    // Armazena a máscara de formatação.
	AnsiString mask = "";

	// Concatena uma quantia igual à storedLen - 1 de símbolos #
	// para a parte inteira da máscara.
	for (int i = 0; i < storedLen - 1; i++) {
		mask += "#";
	}

	// Adiciona um 0 no final da parte inteira da máscara.
	mask += "0";

	// Se há casas decimais, ...
	if (precision > 0) {
		// ... o valor é um não-inteiro e um arredondamento deve ser feito.
		caption = round(stored * precision) / precision;

		// Adiciona o ponto decimal à máscara.
		mask += ".";

		// Concatena uma quantia igual à storedLen de símbolos #
		// para a parte decimal da máscara.
		for (int i = 0; i < DISPLAY_LEN - storedLen - 1; i++) {
			mask += "#";
		}
	// Senão, o valor é inteiro...
	} else {
		// ... e pode ser diretamente armazenado na variável caption.
		caption = stored;
	}

	// Exibe o valor final no display.
    lblRes->Caption = FormatFloat(mask, caption);
}



/**
 * Tratamento de erros.
 */
void TfrmMain::error() {
    // Exibe a mensagem "ERROR" no display.
	lblRes->Caption = "ERROR";

    // Reseta as variáveis.
    reset();
}



/**
 * Aplica uma operação.
 */
void TfrmMain::push(int op) {
	// Se a tecla de igual foi a última pressionada...
	if (equal) {
		// ... armazena o valor do display na variável stored.
		stored = lblRes->Caption.ToDouble();
	// Senão, caso não esteja pausado...
	} else if (!paused) {
		// ... verifica se alguma operação já foi selecionada.
		if (!operation) {
			// Neste caso, também armazena o valor
			// do display na variável stored.
			stored = lblRes->Caption.ToDouble();
		} else {
			// Senão, armazena o valor do display
			// como o último valor informado...
			display = lblRes->Caption.ToDouble();

			// ... e faz os cálculos.
			calculate();
		}
	}

    // Define as flags.
	paused = true;
    equal = false;

	// Muda a operação caso a escolhida seja diferente da já definida.
	if (op != operation) {
		operation = op;
	}
}



/**
 * Reseta as variáveis.
 */
void TfrmMain::reset() {
    // Zera todas as variáveis.
    stored = 0;
	display = 0;
	operation = 0;

    // Define como pausado e reinicia a flag equal.
	paused = true;
	equal = false;
}



/**
 * Digita um número no display.
 */
void TfrmMain::type(int digit) {
	// Caso esteja pausado ou esteja mostrando 0 inicia um novo valor.
	if (paused || lblRes->Caption == "0") {
		lblRes->Caption = digit;
		paused = false;
	// Senão incrementa com o valor digitado,
	// suportando até DISPLAY_LEN caracteres.
	} else if (lblRes->GetTextLen() < DISPLAY_LEN) {
		lblRes->Caption += digit;
	}
}



/**
 * Eventos dos dígitos.
 */
void __fastcall TfrmMain::btnNum0Click(TObject *Sender) {
	// Digita o 0.
	type(0);
}

void __fastcall TfrmMain::btnNum1Click(TObject *Sender) {
	// Digita o 1.
	type(1);
}

void __fastcall TfrmMain::btnNum2Click(TObject *Sender) {
	// Digita o 2.
	type(2);
}

void __fastcall TfrmMain::btnNum3Click(TObject *Sender) {
	// Digita o 3.
	type(3);
}

void __fastcall TfrmMain::btnNum4Click(TObject *Sender) {
	// Digita o 4.
	type(4);
}

void __fastcall TfrmMain::btnNum5Click(TObject *Sender) {
	// Digita o 5.
	type(5);
}

void __fastcall TfrmMain::btnNum6Click(TObject *Sender) {
	// Digita o 6.
	type(6);
}

void __fastcall TfrmMain::btnNum7Click(TObject *Sender) {
	// Digita o 7.
	type(7);
}

void __fastcall TfrmMain::btnNum8Click(TObject *Sender) {
	// Digita o 8.
	type(8);
}

void __fastcall TfrmMain::btnNum9Click(TObject *Sender) {
	// Digita o 9.
	type(9);
}

void __fastcall TfrmMain::btnComClick(TObject *Sender) {
	// Caso esteja pausado.
	if (paused) {
		lblRes->Caption = "0,";
		paused = false;
	// O valor no display não pode ter vírgula e
	// deve ter no máximo DISPLAY_LEN dígitos.
	} else if (!lblRes->Caption.Pos(",") && lblRes->GetTextLen() < DISPLAY_LEN) {
		lblRes->Caption += ",";
	}
}



/**
 * Eventos das operações aritméticas.
 */
void __fastcall TfrmMain::btnPluClick(TObject *Sender) {
	// Adição.
	push(1);
}

void __fastcall TfrmMain::btnMinClick(TObject *Sender) {
	// Subtração.
	push(2);
}

void __fastcall TfrmMain::btnMulClick(TObject *Sender) {
	// Multiplicação.
	push(3);
}

void __fastcall TfrmMain::btnDivClick(TObject *Sender) {
    // Divisão.
	push(4);
}



/**
 * Evento da tecla de igual.
 */
void __fastcall TfrmMain::btnEquClick(TObject *Sender) {
	// Obtém a string do display.
	AnsiString caption = lblRes->Caption;

    // Case esteja escrito "ERROR", sai desta função imediatamente.
	if (caption == "ERROR") {
		return;
	}

	// Se a última operação foi esta, ...
	if (!paused && equal) {
		// ... armazena o que está no display diretamente na variável stored.
		stored = caption.ToDouble();
	}

	// Se esta a flag equal não estiver definida, ...
	if (!equal) {
        // ... a variável display recebe o que está no display.
		display = caption.ToDouble();
	}

	// Define as flags.
	paused = true;
	equal = true;

    // Faz os cálculos.
	calculate();
}



/**
 * Eventos das funções da calculadora.
 */
void __fastcall TfrmMain::btnSwiClick(TObject *Sender) {
	// Alterna o valor do display entre positivo e negativo...
	lblRes->Caption = lblRes->Caption.ToDouble() * -1.0;

	// ... e remove a pausa.
	paused = false;
}

void __fastcall TfrmMain::btnCleClick(TObject *Sender) {
	// Zera o valor do display mas mantém os resultados e operações anteriores.
	clearEntry();
}

void __fastcall TfrmMain::btnClaClick(TObject *Sender) {
	// Reinicia todos os valores e variáveis...
	reset();

	// ... e zera o valor do display.
	clearEntry();
}



/**
 * Eventos das teclas de atalho.
 */
void __fastcall TfrmMain::frmMainKeyDown(TObject *Sender, WORD &Key, TShiftState Shift) {
	if (pressed) {
		return;
	}

    switch (Key) {
		case 8: // Backspace
        case 46: // Delete
            btnCle->Click();
			btnCle->SetFocus();
			break;
		case 13: // Enter
			btnEqu->Click();
			btnEqu->SetFocus();
            break;
		case 27: // Escape
			btnCla->Click();
			btnCla->SetFocus();
			break;
		case 48: // 0
		case 96: // Numpad 0
			btnNum0->Click();
			btnNum0->SetFocus();
			break;
		case 49: // 1
		case 97: // Numpad 1
			btnNum1->Click();
			btnNum1->SetFocus();
			break;
		case 50: // 2
		case 98: // Numpad 2
			btnNum2->Click();
			btnNum2->SetFocus();
			break;
		case 51: // 3
		case 99: // Numpad 3
			btnNum3->Click();
			btnNum3->SetFocus();
			break;
		case 52: // 4
		case 100: // Numpad 4
			btnNum4->Click();
			btnNum4->SetFocus();
			break;
		case 53: // 5
		case 101: // Numpad 5
			btnNum5->Click();
			btnNum5->SetFocus();
			break;
		case 54: // 6
		case 102: // Numpad 6
			btnNum6->Click();
			btnNum6->SetFocus();
			break;
		case 55: // 7
		case 103: // Numpad 7
			btnNum7->Click();
			btnNum7->SetFocus();
			break;
		case 56: // 8/*
			if (Shift.Contains(ssShift)) { // *
				btnMul->Click();
				btnMul->SetFocus();
			} else { // 8
				btnNum8->Click();
				btnNum8->SetFocus();
			}

            break;
		case 57: // 9
		case 105: // Numpad 9
			btnNum9->Click();
			btnNum9->SetFocus();
			break;
		case 104: // Numpad 8
			btnNum8->Click();
			btnNum8->SetFocus();
			break;
        case 106: // Numpad *
			btnMul->Click();
			btnMul->SetFocus();
			break;
		case 107: // Numpad +
            btnPlu->Click();
			btnPlu->SetFocus();
			break;
        case 109: // Numpad -
		case 189: // -
			btnMin->Click();
			btnMin->SetFocus();
			break;
		case 110: // Numpad ,
        case 188: // ,
			btnCom->Click();
			btnCom->SetFocus();
			break;
		case 111: // Numpad /
        case 193: // /
			btnDiv->Click();
			btnDiv->SetFocus();
			break;
		case 187: // +/=
			if (Shift.Contains(ssShift)) { // +
				btnPlu->Click();
				btnPlu->SetFocus();
			} else { // =
				btnEqu->Click();
				btnEqu->SetFocus();
			}

			break;
		case 192: // '
			btnSwi->Click();
			btnSwi->SetFocus();
            break;
		default:
			// Finaliza a função antes de definir a flag abaixo
			// se nenhuma das teclas acima foi pressionada.
			return;
	}

	// Define nesta flag que uma tecla foi pressionada.
    pressed = true;
}



/**
 * Evento ao soltar uma tecla.
 */
void __fastcall TfrmMain::frmMainKeyUp(TObject *Sender, WORD &Key, TShiftState Shift) {
	// Indica que a tecla foi solta para que
	// as teclas de atalho voltem a funcionar.
	pressed = false;
}



/**
 * Evento de criação da janela.
 */
void __fastcall TfrmMain::frmMainFormCreate(TObject *Sender) {
	// Reposiciona a janela ao criá-la.
	frmMain->Left = (Screen->Width / 2) - (frmMain->Width / 2);
	frmMain->Top = (Screen->Height / 2) - (frmMain->Height / 2);
}
