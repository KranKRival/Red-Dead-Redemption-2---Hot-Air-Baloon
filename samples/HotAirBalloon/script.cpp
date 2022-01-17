/*KranK 2019 - RDR2 MENU BASE*/

#include "../../inc/main.h"
#include "../../inc/types.h"
#include "stdafx.h"
#include "script.h"
#include "keyboard.h"

#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

#include "Functions.h"
#include "Trainer.h"


// Internals
int Text_X_Coord;
int Rect_wide;
int Menu_X_Coord;
int Max_Options;
int Option_Count;
int Current_Option;
int Last_Option[20];
int SubMenu;
int Last_SubMenu[20];
int SubMenu_Level;

bool Option_Press = false;
bool Right_Press = false;
bool Left_Press = false;

bool x_Instruction;

//
bool GODMODE = false;
bool SUPERJUMP = false;
bool FASTRUN = false;
bool FASTSWIM = false;
bool SUPERMAN = false;
bool FREE_AIM_GUN = false;
bool TELEPORTGUN = false;
bool GRAVITYGUN = false;

bool VALENTINESALOON = false;

bool Create_UFO = false;

int Time_Var = 0;
int Snow_Type = 0;

bool Show_ClosedMenu_Prompt;
int ClosedMenu_Prompt = 0;

int OpenMenu_Prompt_Select = 0;
bool Show_OpenMenu_Prompt_Select;

int OpenMenu_Prompt_Back = 0;
bool Show_OpenMenu_Prompt_Back;

int OpenMenu_Prompt_Up = 0;
bool Show_OpenMenu_Prompt_Up;

int OpenMenu_Prompt_Down = 0;
bool Show_OpenMenu_Prompt_Down;

int OpenMenu_Prompt_Left = 0;
bool Show_OpenMenu_Prompt_Left;

int OpenMenu_Prompt_Right = 0;
bool Show_OpenMenu_Prompt_Right;

bool balloon_enabled = false;
float speed = 0.5f;
float liftspeed = 0.5;
float sinkspeed = 0.5;
bool highSpeed = balloon_enabled;
bool showcontrols = false;
char speedbuffer[100];
Vector3 DimMinimum;
Vector3 DimMaximum;
bool boolped = false;
Vehicle Current_BalloonHandle;

using namespace std;
int Notification_Tick;
bool Notification_Bool;
int Notification_Text_Level;
int Notification_Font_Var;
int Notification_Bar_Level;
const char* Notification_Text = " ";
char Notification_buffer[1000];
int Notification_string_length;
float Notification_Rect_Height;
bool Notification_line_down;

void DoAnyFX(const char* asset, const char* effect, float x, float y, float z, float scale)
{
	STREAMING::REQUEST_PTFX_ASSET();
	GRAPHICS::USE_PARTICLE_FX_ASSET(asset);
	GRAPHICS::START_PARTICLE_FX_LOOPED_AT_COORD(effect, x, y, z, 0, 0, 0, scale, 0, 0, 0, 0);
}

void Notification_Draw(const char* Text, int Seconds)
{
	// Call Ones for drawing subtitle
	Notification_line_down = true;
	Notification_Rect_Height = 0.04f;
	Notification_Text_Level = 250;
	Notification_Bar_Level = 250;
	Notification_Text = Text;

	int MS = Seconds * 1000;
	Notification_Tick = MISC::GET_GAME_TIMER() + MS;
}

void Notification_Init()
{
	// Call In loop , after all GUI drawing
	if (Notification_Tick > MISC::GET_GAME_TIMER())
	{
		
		if (MISC::GET_GAME_TIMER() < Notification_Tick)
		{
			//string str_Notification_Text(Notification_Text);
			float fX = 950 / (float)1920;
			float fY = 950 / (float)1080;
			HUD::SET_TEXT_SCALE(0.4, 0.4);
			HUD::_SET_TEXT_COLOR(255, 255, 255, Notification_Text_Level);
			HUD::SET_TEXT_CENTRE(1);
			HUD::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			char* literalString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", Notification_Text);
			char* fontString = MISC::_CREATE_VAR_STRING_2(42, "COLOR_STRING", 0, literalString);
			snprintf(Notification_buffer, sizeof(Notification_buffer), "<font face=\"%s\">%s</font>", "$body1", fontString);
			HUD::_DISPLAY_TEXT(Notification_buffer, fX, fY);
			if (((float)HUD::GET_LENGTH_OF_LITERAL_STRING(Notification_buffer) / 300) > 0.23f && Notification_line_down)
			{
				Notification_Rect_Height = Notification_Rect_Height + Notification_Rect_Height;
				Notification_line_down = false;
				TXD::REQUEST_STREAMED_TEXTURE_DICT("translate_bg_1a", 0);
				//GRAPHICS::DRAW_SPRITE("menu_textures", "translate_bg_1a", fX, fY + 0.0150f, ((float)str_Notification_Text.size() / 100) - 0.070f, 0.04f, 0.0f, 0, 0, 0, Notification_Bar_Level, 1);
				GRAPHICS::DRAW_SPRITE("menu_textures", "translate_bg_1a", fX, fY + 0.0300f, ((float)HUD::GET_LENGTH_OF_LITERAL_STRING(Notification_buffer) / 500), Notification_Rect_Height, 0.0f, 0, 0, 0, Notification_Bar_Level, 1);
			}
			else
			{
				TXD::REQUEST_STREAMED_TEXTURE_DICT("translate_bg_1a", 0);
				GRAPHICS::DRAW_SPRITE("menu_textures", "translate_bg_1a", fX, fY + 0.0150f, ((float)HUD::GET_LENGTH_OF_LITERAL_STRING(Notification_buffer) / 300), Notification_Rect_Height, 0.0f, 0, 0, 0, Notification_Bar_Level, 1);
			}
			
			if (Notification_Text_Level == 0 || Notification_Bar_Level == 0)
			{}
			else
			{
				Notification_Text_Level--;
				Notification_Bar_Level--;
				fY--;
			}
		}
	}
}


int Instructions_Tick;
bool Instructions_Bool;
int Instructions_Text_Level;
int Instructions_Font_Var;
int Instructions_Bar_Level;
const char* Instructions_Text = " ";
char Instructions_buffer[1000];
int Instructions_string_length;
float Instructions_Rect_Height;
bool Instructions_line_down;
void Instructions_Draw(const char* Text, int MiliSeconds)
{
	// Call Ones for drawing subtitle
	Instructions_line_down = true;
	Instructions_Rect_Height = 0.04f;
	Instructions_Text_Level = 250;
	Instructions_Bar_Level = 250;
	Instructions_Text = Text;

	//int MS = Seconds * 1000;
	Instructions_Tick = MISC::GET_GAME_TIMER() + MiliSeconds;
}

void Instructions_Init()
{
	// Call In loop , after all GUI drawing
	if (Instructions_Tick > MISC::GET_GAME_TIMER())
	{

		if (MISC::GET_GAME_TIMER() < Instructions_Tick)
		{
			//string str_Notification_Text(Notification_Text);
			float fX = 950 / (float)1920;
			float fY = 950 / (float)1080;
			HUD::SET_TEXT_SCALE(0.4, 0.4);
			HUD::_SET_TEXT_COLOR(255, 255, 255, Instructions_Text_Level);
			HUD::SET_TEXT_CENTRE(1);
			HUD::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			char* literalString = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", Instructions_Text);
			char* fontString = MISC::_CREATE_VAR_STRING_2(42, "COLOR_STRING", 0, literalString);
			snprintf(Instructions_buffer, sizeof(Instructions_buffer), "<font face=\"%s\">%s</font>", "$body1", fontString);
			HUD::_DISPLAY_TEXT(Instructions_buffer, fX + 0.3500f, fY + 0.0650f);
			if (((float)HUD::GET_LENGTH_OF_LITERAL_STRING(Instructions_buffer) / 300) > 0.23f && Instructions_line_down)
			{
				//Instructions_Rect_Height = Instructions_Rect_Height + Instructions_Rect_Height;
				Instructions_line_down = false;
				TXD::REQUEST_STREAMED_TEXTURE_DICT("translate_bg_1a", 0);
				//GRAPHICS::DRAW_SPRITE("menu_textures", "translate_bg_1a", fX, fY + 0.0150f, ((float)str_Notification_Text.size() / 100) - 0.070f, 0.04f, 0.0f, 0, 0, 0, Notification_Bar_Level, 1);
				GRAPHICS::DRAW_SPRITE("menu_textures", "translate_bg_1a", fX + 0.3500f, fY + 0.0800f, ((float)HUD::GET_LENGTH_OF_LITERAL_STRING(Instructions_buffer) / 350), Instructions_Rect_Height, 0.0f, 255, 215, 0, 200, 1);
			}
			else
			{
				//TXD::REQUEST_STREAMED_TEXTURE_DICT("translate_bg_1a", 0);
				//GRAPHICS::DRAW_SPRITE("menu_textures", "translate_bg_1a", fX + 0.1000f, fY + 0.0150f, ((float)HUD::GET_LENGTH_OF_LITERAL_STRING(Instructions_buffer) / 500), Instructions_Rect_Height, 0.0f, 0, 0, 0, Instructions_Bar_Level, 1);
			}
		}
	}
}

void Create_Baloon()
{
	Hash model = MISC::GET_HASH_KEY("hotAirBalloon01");
	if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
	{
		STREAMING::REQUEST_MODEL(model, FALSE);
		while (!STREAMING::HAS_MODEL_LOADED(model))
			WAIT(0);

		Ped playerPed = PLAYER::PLAYER_PED_ID();
		float playerHeading = ENTITY::GET_ENTITY_HEADING(playerPed) + 5.0f;
		float heading = playerHeading + 90.0f;
		Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(playerPed, 0, 10.0f, 0);
		Vehicle veh = VEHICLE::CREATE_VEHICLE(model, coords.x, coords.y, coords.z, heading, 0, 0, 0, 0);
		Current_BalloonHandle = veh;
		DECORATOR::DECOR_SET_BOOL(veh, "wagon_block_honor", TRUE);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh, 0);
		ENTITY::SET_VEHICLE_AS_NO_LONGER_NEEDED(&veh);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
	}
}

bool _Controls_bool = true;
void Control_balloon()
{
	uint32_t localPed = PLAYER::GET_PLAYER_PED(0);
	uint32_t localveh = PED::GET_VEHICLE_PED_IS_USING(localPed);
	uint32_t localmodel = ENTITY::GET_ENTITY_MODEL(localveh);
	uint32_t localhash = MISC::GET_HASH_KEY("hotAirBalloon01");
	uint32_t Spawnedveh = Current_BalloonHandle;


	if (PED::IS_PED_IN_ANY_VEHICLE(localPed, false) && localmodel == localhash)
	{

		PED::SET_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
		TASK::TASK_WARP_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
	}

	Vector3 impact;
	if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &impact))
	{
		//GAMEPLAY::_FORCE_LIGHTNING_FLASH_AT_COORDS(impact.x, impact.y, impact.z);
	}


	if (PED::IS_PED_IN_ANY_VEHICLE(localPed, false) && localmodel == localhash)
	{
		balloon_enabled = true;
		if (_Controls_bool)
		{
			Notification_Draw("W : ~COLOR_YELLOW~Move Forward ~COLOR_OANGE~|| ~COLOR_WHITE~SHIFT : ~COLOR_YELLOW~Lift Up ~COLOR_OANGE~|| ~COLOR_WHITE~SPACE : ~COLOR_YELLOW~Sink Down \n~COLOR_WHITE~LEFT ALT : ~COLOR_YELLOW~Wrap in to last spawned Balloon", 1 / 10);
		}
		//PrintSubtitle("W : Forward // SHIFT : Up // SPACE : Down \nLEFT ALT : Wrap in to last spawned Balloon");
		//WEAPON::GIVE_DELAYED_WEAPON_TO_PED(localPed, MISC::GET_HASH_KEY("WEAPON_SNIPERRIFLE_ROLLINGBLOCK"), 1000, 1, 1);
	}
	else
	{
		balloon_enabled = false;
		//PrintSubtitle(" ");
	}

	Vector3 curPosition = ENTITY::GET_ENTITY_COORDS(localveh, false, false);
	Vector3 camDirection = GetCamDirection();

	Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(localveh, -1);
	Vector3 Direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(localveh);

	Vector3 Rotation = ENTITY::GET_ENTITY_ROTATION(localveh, 1);

	//ENTITY::SET_ENTITY_HEADING(localveh, camDirection.x + camDirection.y);

	float Windspeed = MISC::GET_WIND_SPEED();
	Vector3 winddirection = MISC::GET_WIND_DIRECTION();

	Vector3 Offset = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(localPed, 0, -0.8, 0.6);

	MISC::GET_MODEL_DIMENSIONS(ENTITY::GET_ENTITY_MODEL(localveh), &DimMinimum, &DimMaximum);

	if (boolped)
	{
		DWORD model = MISC::GET_HASH_KEY("CS_MICAHBELL");
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model, FALSE);
			while (!STREAMING::HAS_MODEL_LOADED(model))
			{
				WAIT(0);
			}

			Vector3 coords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER::PLAYER_PED_ID(), 0.0, 3.0, -0.3);
			Ped ped = PED::CREATE_PED(model, coords.x, coords.y, coords.z, static_cast<float>(rand() % 360), 0, 0, 0, 0);
			PED::_SET_PED_VISIBLE(ped, TRUE);
			ENTITY::SET_PED_AS_NO_LONGER_NEEDED(&ped);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		}
		boolped = false;
	}




	//GRAPHICS::DRAW_LINE(FromCoords_Line1.x, FromCoords_Line1.y, FromCoords_Line1.z, ToCoords_Line1.x, ToCoords_Line1.y, ToCoords_Line1.z, 255, 0, 0, 255);

	//ENTITY::SET_ENTITY_VELOCITY(localveh, 0.f, 0.f, 0.f);

	Vector3 FromCoord = PED::GET_PED_BONE_COORDS(localPed, 56200, 0, 0, 0);
	Vector3 ToCoord = GetCoordsInfrontOfCam(75);

	Vector3 FromCoords_Line1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(localveh, DimMinimum.x - 1.2f, 0.0f, 0.1f);
	Vector3 ToCoords_Line1 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(localveh, DimMinimum.x - 1.2f, 200.0f, 0.1f);
	Vector3 FromCoords_Line2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(localveh, DimMinimum.x + 1.2f, 0.0f, 0.1f);
	Vector3 ToCoords_Line2 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(localveh, DimMinimum.x + 1.2f, 200.0f, 0.1f);
	Vector3 FromCoords_Line3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(localveh, DimMinimum.x, 0.0f, 0.1);
	Vector3 ToCoords_Line3 = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(localveh, DimMinimum.x, 200.0f, 0.1);
	//SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FromCoord, ToCoord, 250, 0, WeaponID, PLAYER_PED_ID(), 1, 0, 1);

	// todo finishs weapons
	if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_AIM")))
	{
		//curPosition.x += speed * camDirection.x * (highSpeed ? 3 : 1);
		//curPosition.y += speed * camDirection.y * (highSpeed ? 3 : 1);
		//curPosition.z += speed * camDirection.z * (highSpeed ? 3 : 1);
		//TASK::TASK_SHOOT_AT_COORD(localPed, ToCoords_Line2.x, ToCoords_Line2.y, ToCoords_Line2.z, 10000, MISC::GET_HASH_KEY("FIRING_PATTERN_FULL_AUTO"), false);
	}
	else if (PAD::IS_CONTROL_JUST_RELEASED(0, MISC::GET_HASH_KEY("INPUT_AIM")))
	{
		//AI::CLEAR_PED_TASKS(localPed, true, true);
		//curPosition = ENTITY::GET_ENTITY_COORDS(localveh, false, false);

	}
	if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_ATTACK")))
	{
		//curPosition.x += speed * camDirection.x * (highSpeed ? 3 : 1);
		//curPosition.y += speed * camDirection.y * (highSpeed ? 3 : 1);
		//curPosition.z += speed * camDirection.z * (highSpeed ? 3 : 1);
		//GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FromCoord.x, FromCoord.y, FromCoord.z, ToCoord.x, ToCoord.y, ToCoord.z, 250, 0, GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE_ROLLINGBLOCK"), localPed, true, true, 1.0, true);

		//GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FromCoords_Line1.x, FromCoords_Line1.y, FromCoords_Line1.z, curPosition.x + (camDirection.x * 0.5f), curPosition.y + (camDirection.y *0.5f), camDirection.z + 0.05f, 250, 0, GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE_ROLLINGBLOCK"), localPed, true, true, 1.0, true);



		//MISC::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(FromCoords_Line2.x, FromCoords_Line2.y, FromCoords_Line2.z, ToCoords_Line2.x, ToCoords_Line2.y, ToCoords_Line2.z, 250, 0, GAMEPLAY::GET_HASH_KEY("WEAPON_SNIPERRIFLE_ROLLINGBLOCK"), localPed, true, true, 1.0, true);
	}
	else if (PAD::IS_CONTROL_JUST_RELEASED(0, MISC::GET_HASH_KEY("INPUT_AIM")))
	{
		//curPosition = ENTITY::GET_ENTITY_COORDS(localveh, false, false);
	}


	if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("input_move_up_only")))
	{
		//curPosition.x += speed * camDirection.x * (highSpeed ? 3 : 1);
		//curPosition.y += speed * camDirection.y * (highSpeed ? 3 : 1);
		//curPosition.z += speed * camDirection.z * (highSpeed ? 3 : 1);
		//ENTITY::APPLY_FORCE_TO_ENTITY(localveh, 1, 0.0, 1.9f, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1); // Super speed

		//ENTITY::SET_ENTITY_COORDS_NO_OFFSET(localveh, curPosition.x, curPosition.y, curPosition.z, false, false, false);

		if (PED::IS_PED_IN_ANY_VEHICLE(localPed, false) && localmodel == localhash)
		{

		    PED::SET_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
			TASK::TASK_WARP_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);

			//MISC::SET_WIND_SPEED(0.0);


			//ENTITY::SET_ENTITY_ROTATION(localveh, Rotation.x, Rotation.y, camDirection.y - 1, 1, true);
			ENTITY::APPLY_FORCE_TO_ENTITY(localveh, 1, 0.0, speed, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
			ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x + (camDirection.x * speed), velocity.y + (camDirection.y * speed), camDirection.z);

			//ENTITY::SET_ENTITY_COORDS_NO_OFFSET(localveh, curPosition.x + (camDirection.x * speed), curPosition.y + (camDirection.y * speed), curPosition.z, false, false, false);

			//ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x + (camDirection.x * 0.0005f), velocity.y + (camDirection.y * 0.0005f), camDirection.z);

		}
	}
	else if (PAD::IS_CONTROL_JUST_RELEASED(0, MISC::GET_HASH_KEY("input_move_up_only")))
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(localveh, 1, 0.0, speed, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
		ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x + (camDirection.x * speed), velocity.y + (camDirection.y * speed), camDirection.z);
	}

	if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("input_move_down_only")))
	{
		curPosition.x -= speed * camDirection.x * (highSpeed ? 3 : 1);
		curPosition.y -= speed * camDirection.y * (highSpeed ? 3 : 1);
		curPosition.z -= speed * camDirection.z * (highSpeed ? 3 : 1);

		//ENTITY::APPLY_FORCE_TO_ENTITY(localveh, 1, 0.0, - 5.0f, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1); // Super speed

		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(localveh, curPosition.x, curPosition.y, curPosition.z, false, false, false);

		//ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x + (camDirection.x * 5.0f), velocity.y + (camDirection.y / 15.0f), camDirection.z);
	}
	else if (PAD::IS_CONTROL_JUST_RELEASED(0, MISC::GET_HASH_KEY("input_move_down_only")))
	{
		curPosition = ENTITY::GET_ENTITY_COORDS(localveh, false, false);
	}

	if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("input_sprint")))
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(localPed, false) && localmodel == localhash)
		{
			PED::SET_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
			TASK::TASK_WARP_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);
			ENTITY::APPLY_FORCE_TO_ENTITY(localveh, 1, 0.0, 0.0, liftspeed, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
			//ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x + (camDirection.x * 0.1f), velocity.y + (camDirection.y * 0.1f), velocity.z + 0.5f);
			ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x, velocity.y, velocity.z + liftspeed);
		}
	}

	if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("input_jump")))
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(localPed, false) && localmodel == localhash)
		{
			float ground_Height = 0.0f;
			PED::SET_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
			TASK::TASK_WARP_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(PLAYER::PLAYER_PED_ID(), 0);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(localveh, curPosition.x, curPosition.y, curPosition.z - sinkspeed, false, false, false);
			ENTITY::APPLY_FORCE_TO_ENTITY(localveh, 1, 0.0, 0.0, -sinkspeed, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
			ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x + (camDirection.x * 0.2f), velocity.y + (camDirection.y * 0.2f), velocity.z - 0.001f);
			//ENTITY::SET_ENTITY_VELOCITY(localveh, velocity.x, velocity.y, velocity.z - 0.001f);
			if (MISC::GET_GROUND_Z_FOR_3D_COORD(curPosition.x, curPosition.y, curPosition.z, &ground_Height, 0))
			{
				//VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(localveh, true);
			}

		}


	}

	if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_HUD_SPECIAL")))
	{
		PED::SET_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
		TASK::TASK_WARP_PED_INTO_VEHICLE(localPed, Spawnedveh, -1);
	}
}

char * BoxOfColors(char * input, int color)
{
	char* words[4];
	words[0] = "~COLOR_RED~";
	words[1] = "~COLOR_GREEN~";
	words[2] = "~COLOR_BLUE~";
	words[3] = "~COLOR_YELLOW~";
	words[4] = "~COLOR_ORANGE~";
	words[5] = "~COLOR_WHITE~";

	char *temp;
	switch (color)
	{
	case 1: temp = words[0]; break; // RED
	case 2: temp = words[1]; break; // GREEN
	case 3: temp = words[2]; break; // BLUE
	case 4: temp = words[3]; break; // YELLOW
	case 5: temp = words[4]; break; // ORANGE
	case 6: temp = words[5]; break; // WHITE
	}


	char Bufferout[100];
	snprintf(Bufferout, sizeof(Bufferout), "%s %s  ", temp, input);
	return Bufferout;
}

void Prompts_Initalize()
{
	// OPEN MENU
	char* ClosedMenuStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", BoxOfColors("HOT AIR BALLOON MENU", 5));
	ClosedMenu_Prompt = HUD::_PROMPT_REGISTER_BEGIN();
	HUD::_0xF4A5C4509BF923B1(ClosedMenu_Prompt, 0);
	HUD::_PROMPT_SET_TEXT(ClosedMenu_Prompt, ClosedMenuStr);
	HUD::_PROMPT_SET_CONTROL_ACTION(ClosedMenu_Prompt, joaat("INPUT_SPRINT"));
	HUD::_PROMPT_SET_CONTROL_ACTION(ClosedMenu_Prompt, joaat("INPUT_GAME_MENU_TAB_LEFT_SECONDARY"));
	HUD::_PROMPT_SET_HOLD_INDEFINITELY_MODE(ClosedMenu_Prompt);
	HUD::_PROMPT_REGISTER_END(ClosedMenu_Prompt);

	// SELECT OPTION
	char* OpenMenuSelectStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", BoxOfColors("SELECT", 2));
	OpenMenu_Prompt_Select = HUD::_PROMPT_REGISTER_BEGIN();
	HUD::_0xF4A5C4509BF923B1(OpenMenu_Prompt_Select, 0);
	HUD::_PROMPT_SET_TEXT(OpenMenu_Prompt_Select, OpenMenuSelectStr);
	HUD::_PROMPT_SET_CONTROL_ACTION(OpenMenu_Prompt_Select, joaat("INPUT_FRONTEND_ACCEPT"));
	HUD::_PROMPT_SET_HOLD_INDEFINITELY_MODE(OpenMenu_Prompt_Select);
	HUD::_PROMPT_REGISTER_END(OpenMenu_Prompt_Select);

	// BACK
	char* OpenMenuBackStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", BoxOfColors("BACK", 1));
	OpenMenu_Prompt_Back = HUD::_PROMPT_REGISTER_BEGIN();
	HUD::_0xF4A5C4509BF923B1(OpenMenu_Prompt_Back, 0);
	HUD::_PROMPT_SET_TEXT(OpenMenu_Prompt_Back, OpenMenuBackStr);
	HUD::_PROMPT_SET_CONTROL_ACTION(OpenMenu_Prompt_Back, joaat("INPUT_FRONTEND_CANCEL"));
	HUD::_PROMPT_SET_HOLD_INDEFINITELY_MODE(OpenMenu_Prompt_Back);
	HUD::_PROMPT_REGISTER_END(OpenMenu_Prompt_Back);

	// UP
	char* OpenMenuUpStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", BoxOfColors("UP", 4));
	OpenMenu_Prompt_Up = HUD::_PROMPT_REGISTER_BEGIN();
	HUD::_0xF4A5C4509BF923B1(OpenMenu_Prompt_Up, 0);
	HUD::_PROMPT_SET_TEXT(OpenMenu_Prompt_Up, OpenMenuUpStr);
	HUD::_PROMPT_SET_CONTROL_ACTION(OpenMenu_Prompt_Up, joaat("INPUT_FRONTEND_UP"));
	HUD::_PROMPT_SET_HOLD_INDEFINITELY_MODE(OpenMenu_Prompt_Up);
	HUD::_PROMPT_REGISTER_END(OpenMenu_Prompt_Up);

	// DOWN
	char* OpenMenuDownStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", BoxOfColors("DOWN", 4));
	OpenMenu_Prompt_Down = HUD::_PROMPT_REGISTER_BEGIN();
	HUD::_0xF4A5C4509BF923B1(OpenMenu_Prompt_Down, 0);
	HUD::_PROMPT_SET_TEXT(OpenMenu_Prompt_Down, OpenMenuDownStr);
	HUD::_PROMPT_SET_CONTROL_ACTION(OpenMenu_Prompt_Down, joaat("INPUT_FRONTEND_DOWN"));
	HUD::_PROMPT_SET_HOLD_INDEFINITELY_MODE(OpenMenu_Prompt_Down);
	HUD::_PROMPT_REGISTER_END(OpenMenu_Prompt_Down);

	// LEFT
	char* OpenMenuLeftStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", BoxOfColors("LEFT", 3));
	OpenMenu_Prompt_Left = HUD::_PROMPT_REGISTER_BEGIN();
	HUD::_0xF4A5C4509BF923B1(OpenMenu_Prompt_Left, 0);
	HUD::_PROMPT_SET_TEXT(OpenMenu_Prompt_Left, OpenMenuLeftStr);
	HUD::_PROMPT_SET_CONTROL_ACTION(OpenMenu_Prompt_Left, joaat("INPUT_FRONTEND_LEFT"));
	HUD::_PROMPT_SET_HOLD_INDEFINITELY_MODE(OpenMenu_Prompt_Left);
	HUD::_PROMPT_REGISTER_END(OpenMenu_Prompt_Left);

	//RIGHT
	char* OpenMenuRightStr = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", BoxOfColors("RIGHT", 3));
	OpenMenu_Prompt_Right = HUD::_PROMPT_REGISTER_BEGIN();
	HUD::_0xF4A5C4509BF923B1(OpenMenu_Prompt_Right, 0);
	HUD::_PROMPT_SET_TEXT(OpenMenu_Prompt_Right, OpenMenuRightStr);
	HUD::_PROMPT_SET_CONTROL_ACTION(OpenMenu_Prompt_Right, joaat("INPUT_FRONTEND_RIGHT"));
	HUD::_PROMPT_SET_HOLD_INDEFINITELY_MODE(OpenMenu_Prompt_Right);
	HUD::_PROMPT_REGISTER_END(OpenMenu_Prompt_Right);
}

void Initalize()
{
	// whatevr initalizations go here :P

	Prompts_Initalize();
	bool* ChangeModelGlobal = (bool*)getGlobalPtr(1835009);
	*ChangeModelGlobal = true;
	Text_X_Coord = 105;
	Menu_X_Coord = 100;
	Max_Options = 8;
	SubMenu = Closed;
}

void Reset_Variables()
{
	if (SubMenu != Closed)
	{
		//Menu_Actions();
	}
		
	Option_Press = false;
	Left_Press = false;
	Right_Press = false;
	x_Instruction = false;
}

void Show_Controls()
{
	
	if (Show_ClosedMenu_Prompt)
	{
		//Instructions_Draw("~COLOR_BLACK~HOT AIR BALLOON TRAINER : ~COLOR_RED~L SHIFT ~COLOR_BLACK~+ ~COLOR_RED~Z", 100);
		HUD::_PROMPT_SET_ENABLED(ClosedMenu_Prompt, true);
		HUD::_PROMPT_SET_VISIBLE(ClosedMenu_Prompt, true);	
		PAD::ENABLE_CONTROL_ACTION(0, joaat("INPUT_SPRINT"), 0);
		PAD::ENABLE_CONTROL_ACTION(0, joaat("INPUT_GAME_MENU_TAB_LEFT_SECONDARY"), 0);
		PAD::SET_INPUT_EXCLUSIVE(0, joaat("INPUT_SPRINT"));
		PAD::SET_INPUT_EXCLUSIVE(0, joaat("INPUT_GAME_MENU_TAB_LEFT_SECONDARY"));
	}
	else
	{
		HUD::_PROMPT_SET_ENABLED(ClosedMenu_Prompt, false);
		HUD::_PROMPT_SET_VISIBLE(ClosedMenu_Prompt, false);
	}

	if (Show_OpenMenu_Prompt_Select)
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Select, true);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Select, true);
	}
	else
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Select, false);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Select, false);
	}
	
	if (Show_OpenMenu_Prompt_Back)
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Back, true);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Back, true);
	}
	else
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Back, false);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Back, false);
	}

	if (Show_OpenMenu_Prompt_Up)
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Up, true);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Up, true);
	}
	else
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Up, false);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Up, false);
	}

	if (Show_OpenMenu_Prompt_Down)
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Down, true);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Down, true);
	}
	else
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Down, false);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Down, false);
	}

	if (Show_OpenMenu_Prompt_Left)
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Left, true);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Left, true);
	}
	else
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Left, false);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Left, false);
	}

	if (Show_OpenMenu_Prompt_Right)
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Right, true);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Right, true);
	}
	else
	{
		HUD::_PROMPT_SET_ENABLED(OpenMenu_Prompt_Right, false);
		HUD::_PROMPT_SET_VISIBLE(OpenMenu_Prompt_Right, false);
	}

}
void Hide_Controls()
{
	
	//HUD::_PROMPT_DELETE(prompt);
}


bool Run()
{
	if (!HUD::IS_PAUSE_MENU_ACTIVE())
	{
		if (PLAYER::IS_PLAYER_PLAYING(0))
		{
			if (!PLAYER::IS_PLAYER_DEAD(0))
			{
				return true;
			}
		}
	}
}
bool graphics = true;
int player_size_var = 1;
float WindSpeed;
Vector3 WindDirection;
float WindDirection_x;;
float RainLevel;
bool freezewind = false;
float camfov;
void Create_Menu()
{

	Show_Controls();
	if (SubMenu != Closed)
	{
		Show_ClosedMenu_Prompt = false;

		Show_OpenMenu_Prompt_Select = true;
		Show_OpenMenu_Prompt_Back = true;
		Show_OpenMenu_Prompt_Up = true;
		Show_OpenMenu_Prompt_Down = true;
		Show_OpenMenu_Prompt_Left = true;
		Show_OpenMenu_Prompt_Right = true;

		Menu_Actions();
		char* Menu_Title = SetStringFormat("HOT AIR BALLOON", FONT_STYLE_TITLE, 0, "LEFT");

		Draw_Rect(Menu_X_Coord, 50, 500, 50, 0, 0, 0, 200);
		Draw_Rect(Menu_X_Coord, ((Max_Options) * 37) + 130, 500, 50, 0, 0, 0, 200);
		Draw_Text(Text_X_Coord * 1.5, 54, Menu_Title, 255, 215, 0, 200, 0.582f, 0.582f);
		char bufff[64];
		sprintf(bufff, "%d/%d", Current_Option, Option_Count);
		char* Count = SetStringFormat(bufff, FONT_STYLE_TITLE, 0, "LEFT");
		Draw_Text(Text_X_Coord * 4.7, 54, Count, 255, 215, 0, 200, 0.582f, 0.582f);

		char resobuff[100];
		snprintf(resobuff, sizeof(resobuff), "Current Rect Wide %i", Rect_wide);
		//PrintSubtitle(resobuff);
	}
	else
	{
		Show_ClosedMenu_Prompt = true;

		Show_OpenMenu_Prompt_Select = false;
		Show_OpenMenu_Prompt_Back = false;
		Show_OpenMenu_Prompt_Up = false;
		Show_OpenMenu_Prompt_Down = false;
		Show_OpenMenu_Prompt_Left = false;
		Show_OpenMenu_Prompt_Right = false;

		WindSpeed = MISC::GET_WIND_SPEED();
		WindDirection = MISC::GET_WIND_DIRECTION();
		//WindDirection_x = WindDirection.x;
		RainLevel = MISC::GET_RAIN_LEVEL();
		camfov = CAM::GET_CAM_FOV(CAM::GET_RENDERING_CAM());
	}



	// Trainer
	Looped_Functions();
	int Hours = CLOCK::GET_CLOCK_HOURS();
	int Minutes = CLOCK::GET_CLOCK_MINUTES();
	int Seconds = CLOCK::GET_CLOCK_SECONDS();




	Option_Count = 0;
	switch (SubMenu)
	{
		// Main Menu 
	case Main_Menu:
		Add_Option("CALL HOT AIR BALLOON");
		Add_Float_Option("BALLOON VELOCITY", &speed, 0.0f, 100.0f);
		Add_Float_Option("LIFT VELOCITY", &liftspeed, 0.0f, 100.0f);
		Add_Float_Option("SINK VELOCITY", &sinkspeed, 0.0f, 100.0f);
		Add_Option("WEATHER");
		Add_Option("SNOW EXTRA");
		Add_Option("TIME");
		Add_Option("WIND / RAIN");
		Add_Bool_Option("SHOW CONTOLS", _Controls_bool);
		switch (Get_Option())
		{
		case 1: Notification_Draw("Hot Air Balloon Spawned", 5); Create_Baloon(); break;
		case 5: Change_SubMenu(Weather_Menu); break;
		case 6: Change_SubMenu(Snow_Menu); break;
		case 7: Change_SubMenu(Time_Menu); break;
		case 8: Change_SubMenu(Wind_Menu); break;
		case 9: _Controls_bool = !_Controls_bool; break;
		}
		switch (Get_Var_Option())
		{
		case 2: break;//BALLOON VELOCITY
		case 3: break;//LIFT VELOCITY
		case 4: break;//SINK VELOCITY
		}
		break;


	case Weather_Menu:
		Add_Option("OVERCAST");
		Add_Option("RAIN");
		Add_Option("FOG");
		Add_Option("SNOWLIGHT");
		Add_Option("THUNDER");
		Add_Option("BLIZZARD");
		Add_Option("SNOW");
		Add_Option("MISTY");
		Add_Option("SUNNY");
		Add_Option("HIGH PRESSURE");
		Add_Option("CLEARING");
		Add_Option("SLEET");
		Add_Option("DRIZZLE");
		Add_Option("SHOWER");
		Add_Option("SNOW CLEARING");
		Add_Option("OVERCAST DARK");
		Add_Option("THUNDERSTORM");
		Add_Option("SANDSTORM");
		Add_Option("HURRICANE");
		Add_Option("HAIL");
		Add_Option("WHITEOUT");
		Add_Option("GROUND BLIZZARD");
		switch (Get_Option())
		{
		case 1: Set_Weather("OVERCAST"); break;
		case 2: Set_Weather("RAIN"); break;
		case 3: Set_Weather("FOG"); break;
		case 4: Set_Weather("SNOWLIGHT"); break;
		case 5: Set_Weather("THUNDER"); break;
		case 6: Set_Weather("BLIZZARD"); break;
		case 7: Set_Weather("SNOW"); break;
		case 8: Set_Weather("MISTY"); break;
		case 9: Set_Weather("SUNNY"); break;
		case 10: Set_Weather("HIGHPRESSURE"); break;
		case 11: Set_Weather("CLEARING"); break;
		case 12: Set_Weather("SLEET"); break;
		case 13: Set_Weather("DRIZZLE"); break;
		case 14: Set_Weather("SHOWER"); break;
		case 15: Set_Weather("SNOWCLEARING"); break;
		case 16: Set_Weather("OVERCASTDARK"); break;
		case 17: Set_Weather("THUNDERSTORM"); break;
		case 18: Set_Weather("SANDSTORM"); break;
		case 19: Set_Weather("HURRICANE"); break;
		case 20: Set_Weather("HAIL"); break;
		case 21: Set_Weather("WHITEOUT"); break;
		case 22: Set_Weather("GROUNDBLIZZARD"); break;
		}
		break;

	case Time_Menu:
		Add_int_Option("HOURS", &Hours, 0, 23, false);
		Add_int_Option("MINUTES", &Minutes, 0, 59, false);
		Add_int_Option("SECONDS", &Seconds, 0, 99, false);
		Add_Option("");
		Add_Option("");
		Add_Option("");
		Add_Option("");
		Add_Option(Get_Game_Time(Get_Time_MHS()));

		switch (Get_Var_Option())
		{
		case 1:
		case 2:
		case 3:
		{
			if (Left_Press)
			{
				CLOCK::SET_CLOCK_TIME(Hours, Minutes, Seconds);
			}
			if (Right_Press)
			{
				CLOCK::SET_CLOCK_TIME(Hours, Minutes, Seconds);
			}
			break;
		}
		}
		switch (Get_Option())
		{
		case 4: break;
		case 5: break;
		case 6: break;
		case 7: break;
		case 8: break;
		}
		break;

		// SNOW MENU
	case Snow_Menu:
		for (int i = 0; i < 4; i++)
		{
			Add_Option(Snow_Types_Strings[i]);
		}
		switch (Get_Option())
		{
		case 1:
		case 2:
		case 3:
		case 4: GRAPHICS::_SET_SNOW_COVERAGE_TYPE(Current_Option - 1); break;
		}
		break;

		// WIND MENU
	case Wind_Menu:
		Add_Float_Option("WIND SPEED", &WindSpeed, 0.0f, 10000.0f);
		Add_Bool_Option("WIND FREEZE", freezewind);
		Add_Float_Option("WIND DIRECTION", &WindDirection_x, 0.0f, 360.0f);
		Add_Float_Option("RAIN INTENSITY", &RainLevel, 0.0f, 10000.0f);
		if (CAM::DOES_CAM_EXIST(CAM::GET_RENDERING_CAM()))
		{
			Add_Float_Option("CAMERA FOV", &camfov, 0.0f, 300.0f);
		}

		switch (Get_Option())
		{
		case 2:
		{
			freezewind = !freezewind;
		}
		}
		switch (Get_Var_Option())
		{
		case 1:
		{
			if (PAD::IS_CONTROL_PRESSED(0, joaat(LEFT)))
			{
				WindSpeed = WindSpeed - 9.9f;
			}
			if (PAD::IS_CONTROL_PRESSED(0, joaat(RIGHT)))
			{
				WindSpeed = WindSpeed + 9.9f;
			}
			if (WindSpeed > 10000.0f)
			{
				WindSpeed = 0.0f;
			}
			MISC::SET_WIND_SPEED(WindSpeed);
			freezewind = false;
			break;
		}
		case 3:
		{
			if (PAD::IS_CONTROL_PRESSED(0, joaat(LEFT)))
			{
				WindDirection_x = WindDirection_x - 9.9f;
			}
			if (PAD::IS_CONTROL_PRESSED(0, joaat(RIGHT)))
			{
				WindDirection_x = WindDirection_x + 9.9f;
				if (WindDirection_x >= 9.89f && WindDirection_x < 10.0f)
				{
					WindDirection_x = 10.0f;
				}
			}

			MISC::SET_WIND_DIRECTION(WindDirection_x);
			if (WindDirection_x > 360.0f)
			{
				WindDirection_x = 0.0f;
			}
			break;
		}
		case 4: MISC::_SET_RAIN_FX_INTENSITY(RainLevel); break;
		case 5: CAM::SET_CAM_FOV(RainLevel, camfov); break;
		}

		break;
	}
	Reset_Variables();
}

void main()
{

	//AllocConsole();
	//AttachConsole(GetCurrentProcessId());
	//freopen("CON", "w", stdout);

	//printf("Hello From Hot Air Balloon Script\n");

	Initalize();
	
	while (Run())
	{
		//background is "menu_textures", "translate_bg_1a"
		//"generic_textures", "tick"
		//"generic_textures", "tick_box"
		//"menu_textures", "selection_arrow_(left/right)"
		//and selected item is "boot_flow", "selection_box_bg_1d"
		//TXD::REQUEST_STREAMED_TEXTURE_DICT("selection_box_bg_1d", 0);
		//GRAPHICS::DRAW_SPRITE("boot_flow", "selection_box_bg_1d", 0.18f, 0.22f, 0.25f, 0.35f, 0.0f, 255, 255, 255, 100, 150);
		

		// MENU
		Notification_Init();
		Instructions_Init();
		Create_Menu();
		Monitor_Controller();
		Monitor_KeyBoard();
		Control_balloon();
		if (freezewind)
		{
			MISC::SET_WIND_SPEED(0.0);
		}

		//WAIT(0);
		scriptWait(0);
	}
}

void ScriptMain()
{
	srand(GetTickCount());
	main();
}