#include "stdafx.h"
#include "../../inc/types.h"
#include "../../inc/main.h"

#include "script.h"
#include "Functions.h"
#include "Trainer.h"
#include "keyboard.h"

#define IMG_HTML(dict, img, width, height) "<img src='img://" dict "/" img "' height='" height "' width='" width "'/>"

// Externals

char* FtoS(float input)
{
	char returnvalue[64];
	int wholenumber = (int)input;
	input -= wholenumber;
	input *= 100;
	sprintf(returnvalue, "%d.%d", wholenumber, (int)input);
	return returnvalue;
}

bool Controller_KeyPressed(char* key)
{
	return PAD::IS_CONTROL_JUST_PRESSED(0, joaat(key));
}

bool CCEqual(const char* cc1, const char* cc2)
{
	return !strcmp(cc1, cc2);
}

const char* GetKeyboardInput(const char* defaultText = "")
{
	MISC::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", defaultText, "", "", "", 64);

	while (MISC::UPDATE_ONSCREEN_KEYBOARD() == 0)
	{
		scriptWait(0);
	}

	if (MISC::UPDATE_ONSCREEN_KEYBOARD() != 1 || CCEqual(MISC::GET_ONSCREEN_KEYBOARD_RESULT(), defaultText))
	{
		return "";
	}

	return MISC::GET_ONSCREEN_KEYBOARD_RESULT();
}

void Draw_Text(uint16_t x, uint16_t y, char* text, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float scaleX, float scaleY)
{
	float fX = x / (float)1920;
	float fY = y / (float)1080;
	HUD::SET_TEXT_SCALE(scaleX, scaleY);
	HUD::_SET_TEXT_COLOR(r, g, b, a);
	char* varString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	HUD::_DISPLAY_TEXT(varString, fX, fY);
}

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

char* CreateColoredString(char* string, int color)
{
	char* literalString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", string);
	return MISC::_CREATE_VAR_STRING_2(42, "COLOR_STRING", MISC::_CREATE_COLOR_STRING(color), literalString);
}

char* ItoS(int num)
{
	char buf[30];
	snprintf(buf, sizeof(buf), "%i", num);
	return buf;
}

char* SetStringFormat(const char* text, int font, int Rightmargin, char * ALIGN)
{
	char buffer[1000];
	char* fontID;
	switch (font)
	{
	case 0: fontID = "$body";  break;
	case 1: fontID = "$body1"; break;
	case 2: fontID = "$body2";  break;
	case 3: fontID = "$body3"; break;
	case 4: fontID = "$FixedWidthNumbers";  break;
	case 5: fontID = "$Font2"; break;
	case 6: fontID = "$Font2_cond_NOT_GAMERNAME";  break;
	case 7: fontID = "$Font5"; break;
	case 8: fontID = "$gamername";  break;
	case 9: fontID = "$gtaCash"; break;
	case 10: fontID = "$handwritten";  break;
	case 11: fontID = "$RockstarTAG"; break;
	case 12: fontID = "$SOCIAL_CLUB_COND_REG";  break;
	case 13: fontID = "$SOCIAL_CLUB_COND_BOLD"; break;
	case 14: fontID = "$title";  break;
	case 15: fontID = "$title1"; break;
	case 16: fontID = "$title2";  break;
	case 17: fontID = "$util"; break;
	case 18: fontID = "$catalog1";  break;
	case 19: fontID = "$catalog2"; break;
	case 20: fontID = "$catalog3"; break;
	case 21: fontID = "$catalog4"; break;
	case 22: fontID = "$catalog5"; break;
	case 23: fontID = "$wantedPostersGeneric"; break;
	case 24: fontID = "$ledger"; break;
	case 25: fontID = "$Debug_REG"; break;
	case 26: fontID = "$Debug_BOLD"; break;
	case 27: fontID = "$chalk"; break;
	case 28: fontID = "$Font5_limited"; break;
	case 29: fontID = "$creditNames"; break;
	}
	char* literalString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	char* fontString = MISC::_CREATE_VAR_STRING_2(42, "COLOR_STRING", 0, literalString);
	//snprintf(buffer, sizeof(buffer), "<font face=\"%s\">%s</font>", fontID, fontString);
	snprintf(buffer, sizeof(buffer), "<TEXTFORMAT INDENT='0' LEFTMARGIN='0' RIGHTMARGIN='%i' LEADING='0'><FONT FACE='%s'><P ALIGN='%s'>%s</P></FONT></TEXTFORMAT>", Rightmargin, fontID, ALIGN, fontString);
	return buffer;
}

char* ForceStringColor(char* text, char* color)
{
	char buffer[1000];
	snprintf(buffer, sizeof(buffer), "<font face=\"%s\">%s</font>", color, text);
	return buffer;
}

char* SetTextCenterd(char* text, int Rightmargin )
{
	//char buffer[1000];
	//snprintf(buffer, sizeof(buffer), "<TEXTFORMAT INDENT='0' LEFTMARGIN='0' RIGHTMARGIN='%i' LEADING='0'><FONT FACE='%s' COLOR='rgb(%i,%i,%i)'><P ALIGN='CENTER'>%s</P></FONT></TEXTFORMAT>", Rightmargin, text);
	//return buffer;
}

void Draw_Rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	float fWidth = width / (float)1920;
	float fHeight = height / (float)1080;
	float fX = (x + width / 2) / (float)1920;
	float fY = (y + height / 2) / (float)1080;

	GRAPHICS::DRAW_RECT( fX, fY, fWidth, fHeight, r, g, b, a, true, true);

	Rect_wide = fX * 3840;
}

void Draw_Header(const char * TitleText, int font, int Rightmargin, char* ALIGN)
{
	
	char* Title = SetStringFormat(TitleText, FONT_STYLE_CREDITNAMES, 0, "LEFT");
	Draw_Rect(Menu_X_Coord, 48, 500, 50, 0, 0, 0, 200);
	Draw_Text(Text_X_Coord, 54, Title, 255, 0, 0, 200, 0.582f, 0.582f);
}

void PrintSubtitle(const char* text)
{
	char* varStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	UILOG::_LOG_SET_CACHED_OBJECTIVE(varStr);
	UILOG::_LOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_LOG_CLEAR_CACHED_OBJECTIVE();
}

void PrintSubtitleFormated(const char* text)
{
	char* varStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text);
	UILOG::_LOG_SET_CACHED_OBJECTIVE(varStr);
	UILOG::_LOG_PRINT_CACHED_OBJECTIVE();
	UILOG::_LOG_CLEAR_CACHED_OBJECTIVE();
}

void ClearSubtitle()
{
	PrintSubtitle(" ");
}

Hash joaat(const char* str)
{
	return MISC::GET_HASH_KEY(str);
}

// Intrernals

void Menu_Actions()
{
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_WHISTLE"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_WHISTLE_HORSEBACK"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_SELECT_RADAR_MODE"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_EXPAND_RADAR"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_OPEN_SATCHEL_MENU"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_OPEN_SATCHEL_HORSE_MENU"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_REVEAL_HUD"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_SPRINT"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_OPEN_JOURNAL"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_OPEN_WHEEL_MENU"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_OPEN_CRAFTING_MENU"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_OPEN_EMOTE_WHEEL"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_INTERACTION_MENU"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_MELEE_ATTACK"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_HUD_SPECIAL"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_PLAYER_MENU"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_HORSE_ATTACK"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_HORSE_ATTACK2"), 0);
	PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_HORSE_MELEE"), 0);

    PAD::SET_INPUT_EXCLUSIVE(2, joaat(UP));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(DOWN));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(RIGHT));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(LEFT));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(Y));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(A));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(X));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(B));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(L_TRIGGER));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(R_TRIGGER));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(L_BUMBER));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(R_BUMBER));
	PAD::SET_INPUT_EXCLUSIVE(2, joaat(L3));
    PAD::SET_INPUT_EXCLUSIVE(2, joaat(R3));

	if (Option_Count > Max_Options)
	{
		//GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions * 0.035f) / 2) + 0.159f), 0.19f, (maxOptions * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		Draw_Rect(Menu_X_Coord, 112, 500, (Max_Options * 37), 0, 0, 0, 200);//Background
		Draw_Rect(Menu_X_Coord * 6.1, 112, 18, (Max_Options * 37), 0, 0, 0, 200);
		//Draw_Rect(Menu_X_Coord * 6.1, 112, 18, (Option_Count * 37), 0, 0, 0, 200);
		if (Current_Option > Max_Options)
		{
			//GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
			Draw_Rect(Menu_X_Coord, ((Max_Options * 37) + 80), 500, 35, 255, 215, 0, 200); //Scroller
			//Draw_Rect(Menu_X_Coord * 6.1, ((Max_Options * 37) + 10), 16, (Option_Count * 37) / 3, 255, 0, 0, 200);
			Draw_Rect(Menu_X_Coord * 6.1, (Max_Options * 37), 16, (Max_Options * 15) , 255, 215, 0, 200); //scroll bar
		}
		else
		{
			//GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
			Draw_Rect(Menu_X_Coord, ((Current_Option * 37) + 80), 500, 35, 255, 215, 0, 200); //Scroller
			if (Current_Option == Max_Options)
			{
				Draw_Rect(Menu_X_Coord * 6.1, (Current_Option * 37), 16, (Max_Options * 15), 255, 215, 0, 200); //scroll bar
			}
			else if (Current_Option > Max_Options / 2)
			{
				Draw_Rect(Menu_X_Coord * 6.1, (Current_Option * 37) + 20, 16, (Max_Options * 15), 255, 215, 0, 200); //scroll bar
			}
			else if (Current_Option < Max_Options / 2)
			{
				Draw_Rect(Menu_X_Coord * 6.1, 112, 16, (Max_Options * 15), 255, 215, 0, 200); //scroll bar
			}
			else
			{
				Draw_Rect(Menu_X_Coord * 6.1, (Current_Option * 37) + 50, 16, (Max_Options * 15), 255, 215, 0, 200); //scroll bar
			}
			
			
		}
		if (Current_Option != Option_Count)
		{
			//GRAPHICS::DRAW_RECT(menuXCoord, ((maxOptions * 0.035f) + 0.161f), 0.19f, 0.005f, indicatorRed, indicatorGreen, indicatorBlue, indicatorOpacity); //Down Indicator
			//GRAPHICS::DRAW_RECT(menuXCoord, (((maxOptions + 1) * 0.035f) + 0.1415f), 0.19f, 0.025f, bannerRectRed, bannerRectGreen, bannerRectBlue, bannerRectOpacity); //Info Box
			//GRAPHICS::DRAW_RECT(menuXCoord - 0.10f, (((maxOptions + 1) * 0.035f) + 0.1415f), 0.002f, 0.025f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity); //Info Box Right Border
			//GRAPHICS::DRAW_RECT(menuXCoord + 0.10f, (((maxOptions + 1) * 0.035f) + 0.1415f), 0.002f, 0.025f, bannerTextRed, bannerTextGreen, bannerTextBlue, bannerTextOpacity); //Info Box Right Border
			//Options_Count();
		}
	}
	else
	{
		//GRAPHICS::DRAW_RECT(menuXCoord, (((optionCount * 0.035f) / 2) + 0.159f), 0.19f, (optionCount * 0.035f), backgroundRed, backgroundGreen, backgroundBlue, backgroundOpacity); //Background
		Draw_Rect(Menu_X_Coord, 112, 500, (Option_Count * 37), 0, 0, 0, 200); //Background
		//GRAPHICS::DRAW_RECT(menuXCoord, ((currentOption * 0.035f) + 0.1415f), 0.19f, 0.035f, scrollerRed, scrollerGreen, scrollerBlue, scrollerOpacity); //Scroller
		Draw_Rect(Menu_X_Coord, ((Current_Option * 37) + 80), 500, 35, 255, 215, 0, 200); //Scroller
		//Draw_Rect(Menu_X_Coord * 6.1, (Current_Option * 37) + 80, 16, (Option_Count * 15), 255, 0, 0, 200);
	}
}

void Add_Option(char* option , int Rightmargin, char* ALIGN, int font)
{
	char* _Option = SetStringFormat(option, FONT_STYLE_CREDITNAMES, 0, "LEFT");
	Option_Count++;
	
	if (Current_Option == Option_Count)
	{
		//infoText = info;
	}

	if (Current_Option <= Max_Options && Option_Count <= Max_Options)
	{
		Draw_Text(Text_X_Coord, (Option_Count * 37 + 80), _Option, 255, 255, 255, 255, 0.400f, 0.400f);
	}

	else if ((Option_Count > (Current_Option - Max_Options)) && Option_Count <= Current_Option)
	{
		Draw_Text(Text_X_Coord, ((Option_Count - (Current_Option - Max_Options)) * 37 + 80), _Option, 255, 255, 255, 255, 0.400f, 0.400f);
	}
	//CurrentOptionText = option;
}

void Bool_Option_Helper(char* toogle, float Rightmargin, char* ALIGN, int font, color RGBA)
{
	char* ON_OFF = SetStringFormat(toogle, FONT_STYLE_CREDITNAMES, Rightmargin, ALIGN);

	if (Current_Option <= Max_Options && Option_Count <= Max_Options)
	{
		Draw_Text(Text_X_Coord * Rightmargin, (Option_Count * 37 + 80), ON_OFF, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}

	else if ((Option_Count > (Current_Option - Max_Options)) && Option_Count <= Current_Option)
	{
		Draw_Text(Text_X_Coord * Rightmargin, ((Option_Count - (Current_Option - Max_Options)) * 37 + 80), ON_OFF, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}
}

void Bool_Option_Helper_2(char* toogle, int Rightmargin, char* ALIGN, int font, color RGBA)
{
	char* ON_OFF = SetStringFormat(toogle, FONT_STYLE_CREDITNAMES, Rightmargin, ALIGN);

	if (Current_Option <= Max_Options && Option_Count <= Max_Options)
	{
		Draw_Text(Text_X_Coord * Rightmargin, (Option_Count * 37 + 80), ON_OFF, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}

	else if ((Option_Count > (Current_Option - Max_Options)) && Option_Count <= Current_Option)
	{
		Draw_Text(Text_X_Coord * Rightmargin, ((Option_Count - (Current_Option - Max_Options)) * 37 + 80), ON_OFF, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}
}

void Add_Bool_Option(char* option, bool toogle, int Rightmargin, char* ALIGN, int font)
{
	color RED = { 255, 0, 0, 255 };
	color GREEN = { 0, 255, 0, 255 };
	color WHITE = { 255, 255, 255, 255 };
	color GREY = { 128, 128, 128, 255 };
	
	if (toogle)
	{
		Add_Option(option, Rightmargin, ALIGN, font);
		Bool_Option_Helper("{", 4.5, "LEFT", font, WHITE);
		if (Current_Option == Option_Count)
		{
			Bool_Option_Helper("ON", 4.9, "LEFT", font, GREY);
		}
		else
		{
			Bool_Option_Helper("ON", 4.9, "LEFT", font, GREEN);
		}
		Bool_Option_Helper("}", 5.5, "LEFT", font, WHITE);
	}
	else
	{
		Add_Option(option, Rightmargin, ALIGN, font);
		Bool_Option_Helper("{", 4.5, "LEFT", font, WHITE);
		if (Current_Option == Option_Count)
		{
			Bool_Option_Helper("OFF", 4.8, "LEFT", font, GREY);
		}
		else
		{
			Bool_Option_Helper("OFF", 4.8, "LEFT", font, RED);
		}
		Bool_Option_Helper("}", 5.5, "LEFT", font, WHITE);
	}
}

void Int_Option_Helper(char* var, float Rightmargin, char* ALIGN, int font, color RGBA)
{
	char* _Variable = SetStringFormat(var, FONT_STYLE_CREDITNAMES, Rightmargin, ALIGN);

	if (Current_Option <= Max_Options && Option_Count <= Max_Options)
	{
		Draw_Text(Text_X_Coord * Rightmargin, (Option_Count * 37 + 80), _Variable, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}

	else if ((Option_Count > (Current_Option - Max_Options)) && Option_Count <= Current_Option)
	{
		Draw_Text(Text_X_Coord * Rightmargin, ((Option_Count - (Current_Option - Max_Options)) * 37 + 80), _Variable, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}
}
void Add_int_Option(char* option, int* var, int min, int max, bool keyboard, int Rightmargin, char* ALIGN, int font)
{
	//char buf[30];
	//snprintf(buf, sizeof(buf), "%s: { %i }", option, *var);
	
	//Draw_Text(Text_X_Coord, (Option_Count * 37 + 80), " hey" IMG_HTML("menu_textures", "selection_arrow_left", "50", "50") " ;)", 255, 255, 255, 255, 0.400f, 0.400f);

	color WHITE = { 255, 255, 255, 255 };
	char buf[30];
	snprintf(buf, sizeof(buf), "%i",  *var);
	TXD::REQUEST_STREAMED_TEXTURE_DICT("selection_arrow_left", 0);
	GRAPHICS::DRAW_SPRITE("menu_textures", "selection_arrow_left", ((Menu_X_Coord / 100) / 2) + 0.25f, (Option_Count * 0.035f + 0.122f), 0.009f, 0.011f, 0.0f, 255, 255, 255, 255, true);
	TXD::REQUEST_STREAMED_TEXTURE_DICT("selection_arrow_right", 0);
	GRAPHICS::DRAW_SPRITE("menu_textures", "selection_arrow_right", ((Menu_X_Coord / 100) / 2) + 0.30f, (Option_Count * 0.035f + 0.122f), 0.009f, 0.011f, 0.0f, 255, 255, 255, 255, true);
	Add_Option(option, Rightmargin, ALIGN, font);
	Int_Option_Helper(buf, 4.8, "LEFT", font, WHITE);
	
	if (Current_Option == Option_Count)
	{
		//lrInstruction = true;
		if (Right_Press)
		{
			//playSound("NAV_UP_DOWN");
			if (*var >= max)
			{
				*var = min;
			}
			else
			{
				*var = *var + 1;
			}
		}
		if (Left_Press)
		{
			//playSound("NAV_UP_DOWN");
			if (*var <= min)
			{
				*var = max;
			}
			else
			{
				*var = *var - 1;
			}
		}
		if (keyboard)
		{
			//squareInstruction = true;
			//if (squarePress)
			//{
				//startKeyboard(0, "", (strlen(ItoS(max)) + 1));
				//keyboardVar = var;
			//}
		}
	}
}

void Add_CharInt_Option(char* option, char** From, int* var, int min, int max, bool any)
{
	char buf[100];
	color WHITE = { 255, 255, 255, 255 };
	if (!any)
	{
		
		snprintf(buf, sizeof(buf), "%s ", From[*var]);
		Add_Option(option);
		Int_Option_Helper(buf, 4.4, "LEFT", FONT_STYLE_CREDITNAMES, WHITE);
		if (Current_Option == Option_Count)
		{
			//lrInstruction = true;
			if (Right_Press)
			{
				//playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1;
			}
			else if (Left_Press)
			{
				//playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1;
			}
		}
	}
	else
	{
		snprintf(buf, sizeof(buf), "- %s +", From[*var]);
		Add_Option(option);
		Int_Option_Helper(buf, 4.0, "LEFT", FONT_STYLE_CREDITNAMES, WHITE);
		if (Current_Option == Option_Count)
		{
			//lrInstruction = true;
			if (Right_Press)
			{
				//playSound("NAV_UP_DOWN");
				if (*var >= max)
					*var = min;
				else
					*var = *var + 1;
			}
			else if (Left_Press)
			{
				//playSound("NAV_UP_DOWN");
				if (*var <= min)
					*var = max;
				else
					*var = *var - 1;
			}
		}
	}

}

void Float_Option_Helper(char* var, float Rightmargin, char* ALIGN, int font, color RGBA)
{
	char* _Variable = SetStringFormat(var, FONT_STYLE_CREDITNAMES, Rightmargin, ALIGN);

	if (Current_Option <= Max_Options && Option_Count <= Max_Options)
	{
		Draw_Text(Text_X_Coord * Rightmargin, (Option_Count * 37 + 80), _Variable, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}

	else if ((Option_Count > (Current_Option - Max_Options)) && Option_Count <= Current_Option)
	{
		Draw_Text(Text_X_Coord * Rightmargin, ((Option_Count - (Current_Option - Max_Options)) * 37 + 80), _Variable, RGBA.r, RGBA.g, RGBA.b, RGBA.a, 0.400f, 0.400f);
	}
}

void Add_Float_Option(char* option, float* var, float min, float max, int Rightmargin, char* ALIGN, int font)
{
	float speed;
	color WHITE = { 255, 255, 255, 255 };
	char buf[30];
	snprintf(buf, sizeof(buf), "%s", FtoS(*var));
	TXD::REQUEST_STREAMED_TEXTURE_DICT("selection_arrow_left", 0);
	GRAPHICS::DRAW_SPRITE("menu_textures", "selection_arrow_left", ((Menu_X_Coord / 100) / 2) + 0.24f, (Option_Count * 0.035f + 0.122f), 0.009f, 0.011f, 0.0f, 255, 255, 255, 255, true);
	TXD::REQUEST_STREAMED_TEXTURE_DICT("selection_arrow_right", 0);
	GRAPHICS::DRAW_SPRITE("menu_textures", "selection_arrow_right", ((Menu_X_Coord / 100) / 2) + 0.30f, (Option_Count * 0.035f + 0.122f), 0.009f, 0.011f, 0.0f, 255, 255, 255, 255, true);
	Add_Option(option, Rightmargin, ALIGN, font);
	Int_Option_Helper(buf, 4.6, "LEFT", font, WHITE);

	if (Current_Option == Option_Count)
	{
		speed = 0.1f;
		if (Right_Press)
		{
			//playSound("NAV_UP_DOWN");
			if (*var >= max)
				*var = min;
			else
				*var = *var + speed;
		}
		else if (Left_Press)
		{
			//playSound("NAV_UP_DOWN");
			if (*var <= min)
				*var = max;
			else
				*var = *var - speed;
			}
	}
		
	
}

void Change_SubMenu(int newSubmenu)
{
	Last_SubMenu[SubMenu_Level] = SubMenu;
	Last_Option[SubMenu_Level] = Current_Option;
	Current_Option = 1;
	SubMenu = newSubmenu;
	SubMenu_Level++;
}

void Add_SubMenu_Option(char* option, int newSubmenu, int Rightmargin, char* ALIGN, int font)
{
	Add_Option(option, Rightmargin, ALIGN, font);
	if (Current_Option == Option_Count)
	{
		x_Instruction = true;
		if (Option_Press)
			Change_SubMenu(newSubmenu);
	}
}

int Get_Option()
{
	x_Instruction = true;
	if (Option_Press)
	{
		return Current_Option;
	}
	else
	{
		return 0;
	}
	
	
}

int Get_Var_Option()
{
	x_Instruction = true;
	if (Left_Press || Right_Press)
	{
		return Current_Option;
	}
	else
	{
		return 0;
	}


}

uint64_t * Read_Global() {
	return getGlobalPtr(1357382 + 1853);
}

void Monitor_KeyBoard()
{
	if (IsKeyJustUp(VK_F3))
	{
		if (SubMenu == Closed)
		{
			SubMenu = Main_Menu;
			Current_Option = 1;
			SubMenu_Level = 0;
		}
		else
		{
			SubMenu = Closed;
		}
		
	}

	// this part handle by the controller even just fine :P so comment it away
	/*
	if (IsKeyJustUp(VK_RETURN))
	{
		Option_Press = true;
	}

	if (IsKeyJustUp(VK_BACK))
	{
		if (SubMenu == Main_Menu)
		{
			SubMenu = Closed;
		}
		else
		{
			SubMenu = Last_SubMenu[SubMenu_Level - 1];
			Current_Option = Last_Option[SubMenu_Level - 1];
			SubMenu_Level--;
		}
		
	}

	

	if (IsKeyJustUp(VK_UP))
	{
		Current_Option--;

		if (Current_Option < 1)
		{
			Current_Option = Option_Count;
		}
		//AUDIO::PLAY_SOUND_FRONTEND("NAV_UP", "Ledger_Sounds", 1);
		char buff[100];
		PrintSubtitle(buff);
	}
	if (IsKeyJustUp(VK_DOWN))
	{
		Current_Option++;

		if (Current_Option > Option_Count)
		{
			Current_Option = 1;
		}
		//AUDIO::PLAY_SOUND_FRONTEND("NAV_DOWN", "Ledger_Sounds", 1);
		char buff[100];
		PrintSubtitle(buff);
	}
	*/

	//ClearSubtitle();
}


void Monitor_Controller()
{
	if (Controller_KeyPressed(A))
	{
		Option_Press = true;
	}

	if (Controller_KeyPressed(LEFT))
	{
		Left_Press = true;
	}

	if (Controller_KeyPressed(RIGHT))
	{
		Right_Press = true;
	}

	if (PAD::IS_CONTROL_PRESSED(0, joaat("INPUT_SPRINT")) && PAD::IS_CONTROL_PRESSED(0, joaat("INPUT_GAME_MENU_TAB_LEFT_SECONDARY")))
	{
		if (SubMenu == Closed)
		{
			SubMenu = Main_Menu;
			Current_Option = 1;
			SubMenu_Level = 0;
		}
		else
		{
			SubMenu = Closed;
		}

	}


	if (Controller_KeyPressed(B))
	{
		if (SubMenu == Main_Menu)
		{
			SubMenu = Closed;
		}
		else if (SubMenu != Closed)
		{
			SubMenu = Last_SubMenu[SubMenu_Level - 1];
			Current_Option = Last_Option[SubMenu_Level - 1];
			SubMenu_Level--;
		}

	}



	if (Controller_KeyPressed(UP))
	{
		Current_Option--;

		if (Current_Option < 1)
		{
			Current_Option = Option_Count;
		}
		AUDIO::_STOP_SOUND_FRONTED("NAV_UP", "Ledger_Sounds");
		AUDIO::PLAY_SOUND_FRONTEND("NAV_UP", "Ledger_Sounds", 1, 0);
		char buff[100];
		//PrintSubtitle(buff);
	}
	if (Controller_KeyPressed(DOWN))
	{
		Current_Option++;

		if (Current_Option > Option_Count)
		{
			Current_Option = 1;
		}
		AUDIO::_STOP_SOUND_FRONTED("NAV_DOWN", "Ledger_Sounds");
		AUDIO::PLAY_SOUND_FRONTEND("NAV_DOWN", "Ledger_Sounds", 1, 0);
		char buff[100];
		//PrintSubtitle(buff);
	}
}


void Draw_Sprite()
{
	TXD::REQUEST_STREAMED_TEXTURE_DICT("UI_DOC_BUILDCAT", 0);
	GRAPHICS::DRAW_SPRITE("UI_DOC_BUILDCAT", "UI_DOC_BUILDCAT", 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 255, 255, 255, 255, 0);
}

void Give_Cash()
{
	StatIDArgs args;
	args.BaseId = joaat("CAREER_CASH");
	args.PermutationId = 0;

	STATS::_0x6A0184E904CDF25E(&args, 50000);
	MONEY::_MONEY_INCREMENT_CASH_BALANCE(50000, 1);

	PrintSubtitle("Added $500");
}