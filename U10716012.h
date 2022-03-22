//---------------------------------------------------------------------------

#ifndef U10716012H
#define U10716012H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "GLCtrl.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TGLBox *GLBox1;
        TGroupBox *GroupBox1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TGroupBox *GroupBox2;
        TScrollBar *Yscale;
        TScrollBar *Zscale;
        TButton *ScaleButton;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TGroupBox *GroupBox3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TScrollBar *XRo;
        TScrollBar *YRo;
        TScrollBar *ZRo;
        TButton *TransButton;
        TGroupBox *GroupBox4;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TScrollBar *XTrans;
        TScrollBar *YTrans;
        TScrollBar *ZTrans;
        TButton *Button1;
        TLabel *XL;
        TLabel *YL;
        TLabel *ZL;
        TLabel *XR;
        TLabel *YR;
        TLabel *ZR;
        TLabel *XT;
        TLabel *YT;
        TLabel *ZT;
        TCheckBox *samesize;
        TScrollBar *Xscale;
        TGroupBox *GroupBox5;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TGroupBox *GroupBox6;
        TRadioButton *RadioButton5;
        TRadioButton *RadioButton6;
        TGroupBox *GroupBox7;
        TGroupBox *GroupBox8;
        TRadioButton *RadioButton7;
        TRadioButton *RadioButton8;
        TRadioButton *RadioButton9;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        void __fastcall init(TObject *Sender);
        void __fastcall drawing(TObject *Sender);
        void __fastcall XscaleChange(TObject *Sender);
        void __fastcall YscaleChange(TObject *Sender);
        void __fastcall ZscaleChange(TObject *Sender);
        void __fastcall XRoChange(TObject *Sender);
        void __fastcall YRoChange(TObject *Sender);
        void __fastcall ZRoChange(TObject *Sender);
        void __fastcall XTransChange(TObject *Sender);
        void __fastcall YTransChange(TObject *Sender);
        void __fastcall ZTransChange(TObject *Sender);
        void __fastcall ScaleButtonClick(TObject *Sender);
        void __fastcall TransButtonClick(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall samesizeClick(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall RadioButton4Click(TObject *Sender);
        void __fastcall RadioButton5Click(TObject *Sender);
        void __fastcall RadioButton6Click(TObject *Sender);

        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall CheckBox2Click(TObject *Sender);
//    
        void __fastcall CheckBox3Click(TObject *Sender);
        void __fastcall RadioButton7Click(TObject *Sender);
        void __fastcall RadioButton8Click(TObject *Sender);
        void __fastcall RadioButton9Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
