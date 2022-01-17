#include "stdafx.h"
#include "../../inc/types.h"
#include "../../inc/main.h"

#include "script.h"


// Variables

extern int Text_X_Coord;
extern int Rect_wide;
extern int Menu_X_Coord;
extern int Max_Options;
extern int Option_Count;
extern int Current_Option;
extern int Last_Option[20];
extern int SubMenu;
extern int Last_SubMenu[20];
extern int SubMenu_Level;

extern bool Option_Press;
extern bool x_Instruction;
extern bool Right_Press;
extern bool Left_Press;

//
extern bool GODMODE;
extern bool SUPERJUMP;
extern bool FASTRUN;
extern bool FASTSWIM;
extern bool FREE_AIM_GUN;
extern bool TELEPORTGUN;
extern bool GRAVITYGUN;

extern bool VALENTINESALOON;

extern bool Create_UFO;

extern int Time_Var;

enum Fonts
{
	FONT_STYLE_BODY,
	FONT_STYLE_BODY_1,
	FONT_STYLE_BODY_2,
	FONT_STYLE_BODY_3,
	FONT_STYLE_FIXED_WIDTH_NUMBERS,
	FONT_STYLE_STANDARD,
	FONT_STYLE_STANDARD_NOT_GAMERNAME,
	FONT_STYLE_CURSIVE,
	FONT_STYLE_CONDENSED_NOT_GAMERNAME,
	FONT_STYLE_PRICEDOWN,
	FONT_STYLE_HANDWRITTEN,
	FONT_STYLE_ROCKSTAR_TAG,
	FONT_STYLE_SOCIAL_CLUB_REG,
	FONT_STYLE_SOCIAL_CLUB_BOLD,
	FONT_STYLE_TITLE,
	FONT_STYLE_TITLE_1,
	FONT_STYLE_TITLE_2,
	FONT_STYLE_UTIL,
	FONT_STYLE_CATALOG_1,
	FONT_STYLE_CATALOG_2,
	FONT_STYLE_CATALOG_3,
	FONT_STYLE_CATALOG_4,
	FONT_STYLE_CATALOG_5,
	FONT_STYLE_WANTED,
	FONT_STYLE_LEDGER,
	FONT_STYLE_CONDENSED,
	FONT_STYLE_CON_BOLD,
	FONT_STYLE_CHALK_HAND,
	FONT_STYLE_LIMITED,
	FONT_STYLE_CREDITNAMES
};

enum Submenus
{
	Closed,
	Main_Menu,
	Player_Menu,
	Weapons_Menu,
	Vehicles_Menu,
	Teleporter_Menu,
	Objects_Menu,
	Pedestrians_Menu,
	World_Menu,
	Weather_Menu,
	Time_Menu,
	Snow_Menu,
	Wind_Menu,
	Settings_Menu
};



// Externals

char* CreateColoredString(char* string, int color);
char* SetStringFormat(const char* text, int font, int Rightmargin, char* ALIGN);
char* ForceStringColor(char* text, char* color);
void Draw_Text(uint16_t x, uint16_t y, char* text, uint8_t r, uint8_t g, uint8_t b, uint8_t a, float scaleX, float scaleY);
void Draw_Rect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
void Draw_Header(const char* TitleText, int font, int Rightmargin, char* ALIGN);
void PrintSubtitle(const char* text);
void ClearSubtitle();
Hash joaat(const char* str);
char* ItoS(int num);
void Change_SubMenu(int newSubmenu);

bool Controller_KeyPressed(char* key);

// Internals

void Menu_Actions();
void Add_Option(char* option, int Rightmargin = 0, char* ALIGN = "LEFT", int font = FONT_STYLE_CREDITNAMES);
void Add_Bool_Option(char* option, bool toogle, int Rightmargin = 0, char* ALIGN = "LEFT", int font = FONT_STYLE_CREDITNAMES);
void Add_int_Option(char* option, int* var, int min, int max, bool keyboard, int Rightmargin = 0, char* ALIGN = "LEFT", int font = FONT_STYLE_CREDITNAMES);
void Add_CharInt_Option(char* option, char** From, int* var, int min, int max, bool any = false);
void Add_Float_Option(char* option, float* var, float min, float max, int Rightmargin = 0, char* ALIGN = "LEFT", int font = FONT_STYLE_CREDITNAMES);
void Change_SubMenu(int newSubmenu);
void Add_SubMenu_Option(char* option, int newSubmenu, int Rightmargin = 0, char* ALIGN = "LEFT", int font = FONT_STYLE_CREDITNAMES);
void Monitor_KeyBoard();
void Monitor_Controller();
void Draw_Sprite();

int Set_Ped_size(Ped player, float size);

int Get_Option();
int Get_Var_Option();