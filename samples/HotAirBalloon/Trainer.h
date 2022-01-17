#include "stdafx.h"
#include "../../inc/main.h"

#include "script.h"


void Looped_Functions();

Vector3 GetCamDirection();
Vector3 GetCoordsInfrontOfCam(float distance);
void Add_Time(int hours, int minutes, int seconds);
void Set_Weather(const char* weather);
Time Get_Time_MHS();
int Get_Time(char HMS);
char* Get_Game_Time(Time _Time);
bool TeleportPlayer(float x, float y, float z, bool groundZ = true);
void TeleportPlayerFade(float x, float y, float z, bool groundZ = true);
void TeleportToWaypoint(bool groundZ = true);
void Teleport_Gun();
void GiveAllWeapons();
void RemoveAllWeapons();
void Create_Gold_PickUp();
void Create_Weapon_PickUp();
void CreateUFO();
void CallUFO();

extern char* Snow_Types_Strings[];
extern int Snow_Types[];
extern int Snow_Types_Count;
