//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include "Unit1.h"
#include <FMX.Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TRectangle *Rectangle1;
	TLabel *Label2;
	TEdit *Edit1;
	TRectangle *Rectangle2;
	TLabel *Label3;
	TEdit *Edit2;
	TButton *Button1;
	TRectangle *Rectangle3;
	TLabel *Label4;
	TMemo *Memo1;
	TLabel *Label5;
	TRectangle *Rectangle4;
	TLabel *Label6;
	TMemo *Memo2;
	TButton *Button2;
	TButton *Button3;
	TButton *Button4;
	TOpenDialog *OpenDialog1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
