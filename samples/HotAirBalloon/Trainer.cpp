#include "stdafx.h"
#include "../../inc/types.h"
#include "../../inc/main.h"

#include "script.h"
#include "Functions.h"
#include "../../inc/types.h"
#include "enums.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include "keyboard.h"


int GiveAllWeponsDelay = 0;

char* Snow_Types_Strings[] = { "PRIMARY", "SECONDARY", "XMAS", "XMAS SECONDARY" };
int Snow_Types[] = { 0, 1, 2, 3 };
int Snow_Types_Count;


Vector3 Get_Coords_From_Cam(float distance)
{
	Vector3 Rot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3 Coord = CAM::GET_GAMEPLAY_CAM_COORD();

	Rot.y = distance * BUILTIN::COS(Rot.x);
	Coord.x = Coord.x + Rot.y * BUILTIN::SIN(Rot.z * -1.0f);
	Coord.y = Coord.y + Rot.y * BUILTIN::COS(Rot.z * -1.0f);
	Coord.z = Coord.z + distance * BUILTIN::SIN(Rot.x);

	return Coord;
}

Vector3 GetCamDirection()
{
	uint32_t localPed = PLAYER::GET_PLAYER_PED(0);

	float pedHeading = ENTITY::GET_ENTITY_HEADING(localPed);
	float camHeading = CAM::GET_GAMEPLAY_CAM_RELATIVE_HEADING();
	float camPitch = CAM::GET_GAMEPLAY_CAM_RELATIVE_PITCH();

	float heading = (camHeading + pedHeading);

	float x = -sin(heading * PI / 180.f);
	float y = cos(heading * PI / 180.f);
	float z = sin(camPitch * PI / 180.f);

	float length = sqrt(x * x + y * y + z * z);
	if (length != 0)
	{
		x /= length;
		y /= length;
		z /= length;
	}

	return { x, y, z };
}

void ApplyForceToEntity(Player ped_id, int x, int y, int z)
{
	ENTITY::APPLY_FORCE_TO_ENTITY(ped_id, 1, 0, x, y, z, 0, 0, 0, 1, 1, 1, 0, 1);
}

Vector3 Vec3Difference(Vector3 v1, Vector3 v2) {
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return v1;
}
Vector3 GetCoordsInfrontOfCam(float distance) //GetCoordAimingAhead
{
	Vector3 GameplayCamRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	Vector3 GameplayCamCoord = CAM::GET_GAMEPLAY_CAM_COORD();

	float tan = cos(GameplayCamRot.y) * distance;
	float xPlane = (sin(GameplayCamRot.z * -1.0f) * tan) + GameplayCamCoord.y;
	float yPlane = (cos(GameplayCamRot.z * -1.0f) * tan) + GameplayCamCoord.y;
	float zPlane = (sin(GameplayCamRot.y) * distance) + GameplayCamCoord.z;

	Vector3 Output;
	Output.x = xPlane;
	Output.y = yPlane;
	Output.z = zPlane;

	return Output;
}

float GetRandomFloat(float min, float max) {
	return MISC::GET_RANDOM_FLOAT_IN_RANGE(min, max);
}

Vector3 RandomXY()
{
	Vector3 v;
	double radian = GetRandomFloat(0.0f, 1.0f) * 2 * M_PI;
	v.x = (float)(cos(radian));
	v.y = (float)(sin(radian));
	return v;
}

Vector3 Vec3Around(Vector3 pos, float distance)
{
	Vector3 v = pos;
	Vector3 randomXY = RandomXY();
	v.x += randomXY.x * distance;
	v.y += randomXY.y * distance;
	return v;
}

Vector3 Vec3New(float x, float y, float z)
{
	Vector3 vec3;
	vec3.x = x;
	vec3.y = y;
	vec3.z = z;
	return vec3;
}

Vector3 Vec3Add(Vector3 vec1, Vector3 vec2)
{
	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;
	return vec1;
}

Vector3 Vec3Sub(Vector3 vec1, Vector3 vec2)
{
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
	vec1.z -= vec2.z;
	return vec1;
}

Vector3 Vec3MultiplyFloat(Vector3 vec1, float fl)
{
	vec1.x *= fl;
	vec1.y *= fl;
	vec1.z *= fl;
	return vec1;
}

bool IsVec3Zero(Vector3 vec)
{
	return vec.x == 0 && vec.y == 0 && vec.z == 0;
}

float GetDistance(Vector3 source, Vector3 target) {
	return MISC::GET_DISTANCE_BETWEEN_COORDS(source.x, source.y, source.z, target.x, target.y, target.z, 1);
}

Vector3 GetGameplayCamDir()
{
	Vector3 dir;
	Vector3 camRot = CAM::GET_GAMEPLAY_CAM_ROT(2);
	double dirX = camRot.x / 57.295779513082320876798154814105;
	double dirZ = camRot.z / 57.295779513082320876798154814105;
	double dirMultXY = abs(cos(dirX));
	return dir;
}

void Add_Time(int hours, int minutes, int seconds)
{
	CLOCK::ADD_TO_CLOCK_TIME( hours, minutes, seconds);
}

Time Get_Time_MHS()
{
	int Hours = CLOCK::GET_CLOCK_HOURS();
	int Minutes = CLOCK::GET_CLOCK_MINUTES();
	int Seconds = CLOCK::GET_CLOCK_SECONDS();

	Time _Time = { Hours , Minutes, Seconds };

	return _Time;
}

char * Get_Game_Time(Time _Time)
{
	char Buffer[100];
	snprintf(Buffer, sizeof(Buffer), "Cur. Time - %i:%i:%i", _Time.h, _Time.m, _Time.s);
	return Buffer;
}

void Get_Time(char HMS)
{
	int time = 0;
	switch (HMS)
	{
	case'H': 
	{
		time = CLOCK::GET_CLOCK_HOURS();
		break;
	}
	case'M':
	{
		time = CLOCK::GET_CLOCK_MINUTES();
		break;
	}
	case'S':
	{
		time = CLOCK::GET_CLOCK_SECONDS();
		break;
	}
	default:
		break;
	}
	Time_Var = time;
}

void Set_Weather(const char* weather)
{
	MISC::_SET_WEATHER_TYPE_TRANSITION( joaat(weather), joaat(weather), 0.5f, true);
}

bool TeleportPlayer(float x, float y, float z, bool groundZ)
{
	int ped = PLAYER::GET_PLAYER_PED(0);
	if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
		ped = PLAYER::GET_PLAYERS_LAST_VEHICLE();
	else if (PED::IS_PED_ON_MOUNT(ped))
		ped = PED::GET_MOUNT(ped);

	ENTITY::SET_ENTITY_COORDS(ped, x, y, z, 1, 0, 1, 1);

	if (groundZ)
	{
		float groundHeight = 0.0f;
		float zValue = -50.0f;

		ENTITY::FREEZE_ENTITY_POSITION(ped, true);
		while (!MISC::GET_GROUND_Z_FOR_3D_COORD(x, y, zValue, &groundHeight, 0))
		{
			zValue += 5.0f;
			ENTITY::SET_ENTITY_COORDS(ped, x, y, zValue, 1, 0, 1, 1);
			scriptWait(0);
		}

		ENTITY::SET_ENTITY_COORDS(ped, x, y, groundHeight, 1, 0, 1, 1);
		ENTITY::FREEZE_ENTITY_POSITION(ped, false);
		return true;
	}
	return true;
}

void TeleportPlayerFade(float x, float y, float z, bool groundZ)
{
	CAM::DO_SCREEN_FADE_OUT(200);
	scriptWait(200);
	TeleportPlayer(x, y, z, groundZ);
	CAM::DO_SCREEN_FADE_IN(300);
}

void TeleportToWaypoint(bool groundZ)
{
	Vector3 coords = MAP::_GET_WAYPOINT_COORDS();
	scriptWait(5);
	TeleportPlayerFade(coords.x, coords.y, coords.z, groundZ);
}

void Teleport_Gun() // goes in loop
{
	if (TELEPORTGUN)
	{
		Vector3 coords;
		if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &coords))
		{
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, true, true, true, false);
		}
	}
}

void GiveAllWeapons()
{
	for (int i = 0; i < ARRAYSIZE(Weapons_Other_Array); i++)
	{
		if (WEAPON::IS_WEAPON_VALID(joaat(Weapons_Other_Array[i])))
		{
			Hash groupid = WEAPON::GET_WEAPONTYPE_GROUP(joaat(Weapons_Other_Array[i]));
			WEAPON::_GIVE_WEAPON_TO_PED_2(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Other_Array[i]), 100, true, true, groupid, false, 1056964608, 1065353216, 752097756, true, 0, 0);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Other_Array[i]), 100, true, groupid);
			WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Other_Array[i]), true, 0, 0, 0);
		}
	}

	for (int i = 0; i < ARRAYSIZE(Weapons_SniperRifle_Array); i++)
	{
		if (WEAPON::IS_WEAPON_VALID(joaat(Weapons_SniperRifle_Array[i])))
		{
			Hash groupid = WEAPON::GET_WEAPONTYPE_GROUP(joaat(Weapons_SniperRifle_Array[i]));
			WEAPON::_GIVE_WEAPON_TO_PED_2(PLAYER::PLAYER_PED_ID(), joaat(Weapons_SniperRifle_Array[i]), 100, true, true, groupid, false, 1056964608, 1065353216, 752097756, true, 0, 0);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), joaat(Weapons_SniperRifle_Array[i]), 100, true, groupid);
	        WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), joaat(Weapons_SniperRifle_Array[i]), true, 0, 0, 0);
		}
	}

	for (int i = 0; i < ARRAYSIZE(Weapons_Melee_Array); i++)
	{
		if (WEAPON::IS_WEAPON_VALID(joaat(Weapons_Melee_Array[i])))
		{
			Hash groupid = WEAPON::GET_WEAPONTYPE_GROUP(joaat(Weapons_Melee_Array[i]));
			WEAPON::_GIVE_WEAPON_TO_PED_2(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Melee_Array[i]), 100, true, true, groupid, false, 1056964608, 1065353216, 752097756, true, 0, 0);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Melee_Array[i]), 100, true, groupid);
			WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Melee_Array[i]), true, 0, 0, 0);
		}
	}
	
	for (int i = 0; i < ARRAYSIZE(Weapons_Pistol_Array); i++)
	{
		if (WEAPON::IS_WEAPON_VALID(joaat(Weapons_Melee_Array[i])))
		{
			Hash groupid = WEAPON::GET_WEAPONTYPE_GROUP(joaat(Weapons_Pistol_Array[i]));
			WEAPON::_GIVE_WEAPON_TO_PED_2(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Pistol_Array[i]), 100, true, true, groupid, false, 1056964608, 1065353216, 752097756, true, 0, 0);
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Pistol_Array[i]), 100, true, groupid);
			WEAPON::SET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), joaat(Weapons_Pistol_Array[i]), true, 0, 0, 0);
		}
	}


}

void RemoveAllWeapons()
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	WEAPON::REMOVE_ALL_PED_WEAPONS(playerPed, true, true);
}

void Create_Gold_PickUp()
{
	int ped = PLAYER::GET_PLAYER_PED(0);
	int Model = joaat("s_pickup_goldbar01x");
	int Model2 = joaat("p_inv_treasuregoldbar01x");

	STREAMING::REQUEST_MODEL(Model, 1);
	STREAMING::REQUEST_MODEL(Model2, 1);
	
	if (STREAMING::HAS_MODEL_LOADED(Model))
	{
		char buff[100];
		snprintf(buff, sizeof(buff), "MODEL : %i", Model);
		PrintSubtitle(buff);
		//int pickup = OBJECT::CREATE_OBJECT(Model, Coords.x, Coords.y, Coords.z, 1, 1, 0, 0, 1);
		//OBJECT::CREATE_PICKUP(-70127024, Coords.x, Coords.y, Coords.z, 8 | 16, -1, 1, 0, 0);
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1, 1);
		Vector3 Direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::PLAYER_PED_ID());
		OBJECT::CREATE_AMBIENT_PICKUP(OBJECT::_GET_PICKUP_HASH(joaat("PICKUP_MONEY_VARIABLE")), Coords.x + (Direction.x * 2), Coords.y + (Direction.y * 2), (Coords.z + Direction.z) + 6.0f, 0, 500000, Model, 0, 1, 1, 1);
		
		
	}
	else
	{
		PrintSubtitle("Model Cannot Loaded");
	}
	if (STREAMING::HAS_MODEL_LOADED(Model2))
	{
		char buff[100];
		snprintf(buff, sizeof(buff), "MODEL 2 : %i", Model2);
		PrintSubtitle(buff);
		//int pickup = OBJECT::CREATE_OBJECT(Model, Coords.x, Coords.y, Coords.z, 1, 1, 0, 0, 1);
		//OBJECT::CREATE_PICKUP(-70127024, Coords.x, Coords.y, Coords.z, 8 | 16, -1, 1, 0, 0);
		Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1, 1);
		Vector3 Direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::PLAYER_PED_ID());
		OBJECT::CREATE_AMBIENT_PICKUP(OBJECT::_GET_PICKUP_HASH(joaat("PICKUP_MONEY_VARIABLE")), Coords.x + (Direction.x * 2), Coords.y + (Direction.y * 2), (Coords.z + Direction.z) + 6.0f, 0, 500000, Model2, 0, 1, 1, 1);


	}
	else
	{
		PrintSubtitle("Model Cannot Loaded");
	}
}

void Create_Weapon_PickUp()
{
	int ped = PLAYER::GET_PLAYER_PED(0);
	int Model = joaat("WEAPON_REVOLVER_DOUBLEACTION");
	int Pickup = OBJECT::_GET_PICKUP_HASH(joaat("PICKUP_WEAPON_RIFLE_BOLTACTION"));
	char buff[100];
	snprintf(buff, sizeof(buff), "MODEL : %i", Model);
	PrintSubtitle(buff);
	Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), 1, 1);
	Vector3 Direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::PLAYER_PED_ID());
	//int pickup = OBJECT::CREATE_OBJECT(Model, Coords.x, Coords.y, Coords.z, 1, 1, 0, 0, 1);
	//OBJECT::CREATE_PICKUP(-70127024, Coords.x, Coords.y, Coords.z, 8 | 16, -1, 1, 0, 0, 0);
    OBJECT::CREATE_PICKUP(Pickup, Coords.x + (Direction.x * 2), Coords.y + (Direction.y * 2), (Coords.z + Direction.z) + 6.0f, 8 | 16, -1, 1, 0, 0, 0);
	//OBJECT::CREATE_AMBIENT_PICKUP(Pickup, Coords.x + (Direction.x * 2), Coords.y + (Direction.y * 2), (Coords.z + Direction.z) + 6.0f, 0, 999, Model, 0, 1, 1, 1);

}

int CreateUFO()
{  
	Vector3 Coords = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true, true);
	Vector3 UFOCoords;
	//s_ufo01x s_ufo02x
	//Hash Model_121 = -1221640793;
	Hash Model_122 = -1074960068;
	Hash Model_FX = 1198653116;
	Hash Red_UFO = joaat("s_ufo01x");
	Hash Green_UFO = joaat("s_ufo02x");
	int LocalModel_121 = 0;
	int LocalModel_122 = 0;
	//PED::_0xED9582B3DA8F02B4(1); //IDK Scripts something about ped
	//AUDIO::_0xD9130842D7226045("Ufos_Sounds", 0); // think has to do with checking the sound 
	
	//STREAMING::REQUEST_MODEL(Model_122, 0); // We shal see wtf is this
	if (STREAMING::IS_MODEL_IN_CDIMAGE(Red_UFO))
	{
		STREAMING::REQUEST_MODEL(Red_UFO, 0); //UFO model
		while (!STREAMING::HAS_MODEL_LOADED(Red_UFO))
		{
			STREAMING::REQUEST_MODEL(Red_UFO, 0);
			scriptWait(0);
		}
		
		if (STREAMING::HAS_MODEL_LOADED(Red_UFO))
		{
			LocalModel_121 = OBJECT::CREATE_OBJECT(Red_UFO, Coords.x, Coords.y, Coords.z + 8.0f, 1, 1, 0, 0, 1);
		}
	}
	else
	{
		PrintSubtitle("MODEL NOT IN CDIMAGE");
	}

    
	
	//if (TXD::_0xBA0163B277C2D2D0(Model_FX))
	//{
		//Hmm UFO PFX ???
		//TXD::_0xDB1BD07FB464584D(Model_FX, 0);
	//}
	if (ENTITY::DOES_ENTITY_EXIST(LocalModel_121))
	{
		UFOCoords = ENTITY::GET_ENTITY_COORDS(LocalModel_121, true, true);
		// Should play UFO sounds at its coord ?!
		AUDIO::PLAY_SOUND_FROM_COORD("Arrive", UFOCoords.x, UFOCoords.y, UFOCoords.z, "Ufos_Sounds", 0, 0, 1);
		AUDIO::PLAY_SOUND_FRONTEND("Arrive", "Ufos_Sounds", true, 1);
	}
	return LocalModel_121;
}


int UFO_Model = 0;
float groundHeight = 0.0f;
void CallUFO()
{
	if (Create_UFO){
		UFO_Model = CreateUFO();
		Create_UFO = false;
	}
	if (UFO_Model > 0 && ENTITY::DOES_ENTITY_EXIST(UFO_Model)){
		Vector3 UFOCoords = ENTITY::GET_ENTITY_COORDS(UFO_Model, false, false);
		Entity PED = PLAYER::PLAYER_PED_ID();
		Vector3 PEDCoords = ENTITY::GET_ENTITY_COORDS(PED, false, false);
		MISC::GET_GROUND_Z_FOR_3D_COORD(PEDCoords.x, PEDCoords.y, PEDCoords.z, &groundHeight, 0);
		Vector3 camDirection = GetCamDirection();
		Vector3 Rotation = ENTITY::GET_ENTITY_ROTATION(UFO_Model, 2);
		Rotation.z++;
		ENTITY::SET_ENTITY_ROTATION(UFO_Model, Rotation.x, Rotation.y, Rotation.z, 2, true);

		Vector3 difference = Vec3Difference(UFOCoords, PEDCoords);
		if (PED::IS_PED_SHOOTING(PED)){
			float Random = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f));
			PED::_SET_PED_SCALE(PLAYER::PLAYER_PED_ID(), Random);
			ENTITY::APPLY_FORCE_TO_ENTITY(PED, 3, 1.0f, 1.0f, difference.z / 2, 0, 0, 0, 0, false, false, true, 0, 1);
		}
		
		if (PAD::IS_CONTROL_PRESSED(0, joaat("INPUT_MOVE_UP_ONLY"))){
			AUDIO::PLAY_SOUND_FROM_COORD("Arrive", UFOCoords.x, UFOCoords.y, UFOCoords.z, "Ufos_Sounds", 0, 0, 1);
			AUDIO::PLAY_SOUND_FRONTEND("Arrive", "Ufos_Sounds", true, 1);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(UFO_Model, PEDCoords.x, PEDCoords.y, groundHeight + 8.0f, false, false, false);
		}
		if (PAD::IS_CONTROL_PRESSED(0, joaat("INPUT_MOVE_DOWN_ONLY"))){
			AUDIO::PLAY_SOUND_FROM_COORD("Leave", UFOCoords.x, UFOCoords.y, UFOCoords.z, "Ufos_Sounds", 0, 0, 1);
			AUDIO::PLAY_SOUND_FRONTEND("Leave", "Ufos_Sounds", true, 1);
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(UFO_Model, PEDCoords.x, PEDCoords.y, groundHeight + 8.0f, false, false, false);
		}
		if (PAD::IS_CONTROL_PRESSED(0, joaat("INPUT_MOVE_LEFT_ONLY"))){
			AUDIO::PLAY_SOUND_FROM_COORD("Loop_B", UFOCoords.x, UFOCoords.y, UFOCoords.z, "Ufos_Sounds", 0, 0, 1);
			AUDIO::PLAY_SOUND_FRONTEND("Loop_B", "Ufos_Sounds", true, 1);
		}
		if (PAD::IS_CONTROL_PRESSED(0, joaat("INPUT_MOVE_RIGHT_ONLY"))){
			AUDIO::PLAY_SOUND_FROM_COORD("Loop_A", UFOCoords.x, UFOCoords.y, UFOCoords.z, "Ufos_Sounds", 0, 0, 1);
			AUDIO::PLAY_SOUND_FRONTEND("Loop_A", "Ufos_Sounds", true, 1);
		}
	}
}

int Set_Ped_size(Ped player, float size)
{
	PED::_SET_PED_SCALE(player, size);
	return size;
}

bool Gravity_Gun_Lock = false;
Entity Gravity_Gun_Entity;
Hash Certain_Gun;
bool Limit_Gun = false;
void GravityGunTick()
{
	if (GRAVITYGUN)
	{
		//if we want to use with certain weapon only
		if (Limit_Gun)
		{
			WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &Certain_Gun, true, 1, true);
		}
		

		PAD::DISABLE_CONTROL_ACTION(0, joaat("INPUT_ATTACK"), true);
		if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(2, joaat("INPUT_ATTACK")))
		{ 
			if(PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(PLAYER::PLAYER_ID(), &Gravity_Gun_Entity))
			{
				if(ENTITY::DOES_ENTITY_EXIST(Gravity_Gun_Entity))
				{ 
					Gravity_Gun_Lock = !Gravity_Gun_Lock;
				
					if (ENTITY::IS_ENTITY_A_PED(Gravity_Gun_Entity) && PED::IS_PED_IN_ANY_VEHICLE(Gravity_Gun_Entity, false))
					{ 
						Gravity_Gun_Entity = PED::GET_VEHICLE_PED_IS_IN(Gravity_Gun_Entity, false);
					}  
				}
			}
		}

		if (Gravity_Gun_Lock)
		{
			ENTITY::SET_ENTITY_ALPHA(Gravity_Gun_Entity, 200, false);
			ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Gravity_Gun_Entity, true, true);
			//ENTITY::SET_ENTITY_DYNAMIC(Gravity_Gun_Entity, true);
			Vector3 camvf = Get_Coords_From_Cam(7.0f);
			Vector3 camDirection = GetCamDirection();
			float Heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Gravity_Gun_Entity, camvf.x, camvf.y, camvf.z, false, false, false);
			ENTITY::SET_ENTITY_HEADING(Gravity_Gun_Entity, Heading + camDirection.y);
			Vector3 Rotation = ENTITY::GET_ENTITY_ROTATION(Gravity_Gun_Entity, 2);
			ENTITY::SET_ENTITY_ROTATION(Gravity_Gun_Entity, Rotation.x, Rotation.y, Rotation.z + camDirection.z, 2, true);
			if (ENTITY::IS_ENTITY_A_PED(Gravity_Gun_Entity))
			{
				if (ENTITY::IS_ENTITY_A_PED(Gravity_Gun_Entity))
				{
					PED::SET_PED_RAGDOLL_FORCE_FALL(Gravity_Gun_Entity);
				}
			}
			Hash Entity_Model = ENTITY::GET_ENTITY_MODEL(Gravity_Gun_Entity);
			char Entity_Model_Buffer[100];
			Entity Entity_Type;
			snprintf(Entity_Model_Buffer, sizeof(Entity_Model_Buffer), "Current Picked Entity: %i", Entity_Model);
			PrintSubtitle(Entity_Model_Buffer);
		}
		else
		{
			if (ENTITY::DOES_ENTITY_EXIST(Gravity_Gun_Entity))
			{
				ENTITY::SET_ENTITY_ALPHA(Gravity_Gun_Entity, 250, false);
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(Gravity_Gun_Entity, false, false);
				//ENTITY::SET_ENTITY_DYNAMIC(Gravity_Gun_Entity, false);
				Vector3 camDirection = GetCamDirection();
				float Heading = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());
				Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(Gravity_Gun_Entity, -1);
				ENTITY::SET_ENTITY_HEADING(Gravity_Gun_Entity, Heading + camDirection.x + camDirection.y);
				ENTITY::APPLY_FORCE_TO_ENTITY(Gravity_Gun_Entity, 1, 0.0, 550.0f, 7.0f, 2.0f, 0.0f, 0.0f, 0, 1, 1, 1, 0, 1);
				//ENTITY::APPLY_FORCE_TO_ENTITY(Gravity_Gun_Entity, 1, 0.0, 0.00, 7.0f, 2.0f, 0.0f, 0.0f, 0, 0, 1, 1, 0, 1);
				if (ENTITY::IS_ENTITY_A_PED(Gravity_Gun_Entity))
				{
					ENTITY::SET_ENTITY_VELOCITY(Gravity_Gun_Entity, velocity.x + (camDirection.x * 5.0f), velocity.y + (camDirection.y * 5.0f), camDirection.z);
				}
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&Gravity_Gun_Entity);
				Gravity_Gun_Entity = 0;
			}
		}
	}
}

void Looped_Functions()
{
	int ped = PLAYER::GET_PLAYER_PED(0);
	if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
	{
		ped = PLAYER::GET_PLAYERS_LAST_VEHICLE();
	}
	else if (PED::IS_PED_ON_MOUNT(ped))
	{
		ped = PED::GET_MOUNT(ped);
	}

	GravityGunTick();
	CallUFO();

	if (VALENTINESALOON)
	{
		AUDIO::SET_AMBIENT_ZONE_LIST_STATE("AZL_RDRO_X18", true, true);
		POPULATION::_0xEC116EDB683AD479(1);
		GRAPHICS::SET_TIMECYCLE_MODIFIER("MP_reduceGlobalTemperature");
		//PrintSubtitle("VALENTINE SALOON ENABLED");
	}
	else
	{
		//PrintSubtitle("VALENTINE SALOON DISBLED");
	}

	//GOD MODE
	if (GODMODE)
	{



		GRAPHICS::ANIMPOSTFX_STOP_ALL();
		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true);
		PLAYER::SET_PLAYER_HEALTH_RECHARGE_MULTIPLIER(PLAYER::PLAYER_ID(), 100.0f);

		ATTRIBUTE::_SET_CORE_VALUE(ped, 1, 100);
		PLAYER::RESTORE_PLAYER_STAMINA(PLAYER::PLAYER_ID(), 100.0f);

		//MISC::_0xB3E9BE963F10C445(); // Super jump this frame
		//if (PED::IS_PED_SWIMMING(PLAYER::PLAYER_PED_ID()))
		//{
			//PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.49f);
			//PED::SET_PED_MOVE_RATE_OVERRIDE(PLAYER::PLAYER_PED_ID(), 10.0f);
		//}
		//PLAYER::_0xBED386157F65942C(PLAYER::PLAYER_ID(), 1.49f);
		//PLAYER::_0xC67A4910425F11F1(PLAYER::PLAYER_ID(), 1.49f);
		//PLAYER::_0xEBFF94328FF7A18A(PLAYER::PLAYER_ID(), 1.49f);
		//PLAYER::_0x95EE1DEE1DCD9070(PLAYER::PLAYER_ID(), 1.49f);
		//PLAYER::_0xAE637BB8EF017875(PLAYER::PLAYER_ID(), 1.49f)

		//if (!ENTITY::IS_ENTITY_IN_AIR(PLAYER::PLAYER_PED_ID(), 1) && TASK::IS_PED_RUNNING(PLAYER::PLAYER_PED_ID()))
		//{
			//Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID(), -1);
			//Vector3 Direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(PLAYER::PLAYER_PED_ID());
			//Vector3 Speed = ENTITY::_0x2A08A32B6D49906F(PLAYER::PLAYER_PED_ID(), 1);

			//TASK::TASK_JUMP(PLAYER::PLAYER_PED_ID(), 0);
			//ENTITY::SET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID(), velocity.x + (Direction.x * 35.0f), velocity.y + (Direction.y * 35.0f), Direction.z);




			//ENTITY::APPLY_FORCE_TO_ENTITY(PLAYER::PLAYER_PED_ID(), 1, 0.0, 35.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1);
			//char bufafaf[100];
			//snprintf(bufafaf, sizeof(bufafaf), "%f, %f, %f", velocity.x , velocity.y, velocity.z);
			//PrintSubtitle(bufafaf);


		//}
		//ENTITY::SET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID(), 100.0f, 0, 0);
		//PED::SET_PED_MOVE_RATE_OVERRIDE(PLAYER::PLAYER_PED_ID(), 100.0f);
		//PED::SET_PED_MAX_MOVE_BLEND_RATIO(PLAYER::PLAYER_PED_ID(), 100.0f);
		//TASK::SET_PED_DESIRED_MOVE_BLEND_RATIO(PLAYER::PLAYER_PED_ID(), 100.0f);
		//PED::SET_PED_KEEP_TASK(PLAYER::PLAYER_PED_ID(), 1);
		//ENTITY::SET_ENTITY_VELOCITY(PLAYER::PLAYER_PED_ID(), 100.0f, 100.0f, 100.0f);

		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, false);
		PED::SET_PED_CAN_RAGDOLL(ped, false);
		PED::SET_PED_CAN_RAGDOLL(ped, false);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(ped, false);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, false);
		PED::SET_PED_RAGDOLL_ON_COLLISION(ped, false, false);
		PED::SET_PED_MAX_HEALTH(ped, 1000);
		PED::SET_PED_MAX_TIME_UNDERWATER(ped, 100000);
		PED::SET_PED_MAX_TIME_IN_WATER(ped, 100000);

		ATTRIBUTE::_SET_CORE_VALUE(ped, 0, 100000);
		ENTITY::_SET_ENTITY_HEALTH(ped, 100000, 0); // SET_ENTITY_HEALTH
		ENTITY::SET_ENTITY_INVINCIBLE(ped, true);
		ENTITY::SET_ENTITY_PROOFS(ped, true, true);
	}
	else
	{

		PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), false);
		ENTITY::SET_ENTITY_INVINCIBLE(ped, false);
		ENTITY::SET_ENTITY_PROOFS(ped, false, false);

		PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 1);
	}

	// SUPER JUMP
	if (SUPERJUMP)
	{
		ATTRIBUTE::_SET_CORE_VALUE(PLAYER::PLAYER_PED_ID(), 1, 100);
		PLAYER::RESTORE_PLAYER_STAMINA(PLAYER::PLAYER_ID(), 100.0f);
		MISC::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());

		int ped = PLAYER::GET_PLAYER_PED(0);
		if (PED::IS_PED_IN_ANY_VEHICLE(ped, false))
			ped = PLAYER::GET_PLAYERS_LAST_VEHICLE();
		else if (PED::IS_PED_ON_MOUNT(ped))
			ped = PED::GET_MOUNT(ped);

		if (PED::IS_PED_JUMPING(ped))
		{
			float Height = 1.0f;
			float Forward = 5.0f;
			ENTITY::APPLY_FORCE_TO_ENTITY(ped, 1, 0.0, Forward, Height, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1); // MEGA JUMP
		}

	}

	// FAST RUN
	if (FASTRUN)
	{
		
		if (!ENTITY::IS_ENTITY_IN_AIR(ped, 1) && !PED::IS_PED_SWIMMING(ped))
		{
			if (TASK::IS_PED_RUNNING(ped) || TASK::IS_PED_SPRINTING(ped))
			{
				ENTITY::APPLY_FORCE_TO_ENTITY(ped, 1, 0.0, 35.0f, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1, 0, 1); // Super speed
			}

		}
	}

	// INFINITE SWIM
	if (FASTSWIM)
	{

		ATTRIBUTE::_SET_CORE_VALUE(ped, 1, 100);
		PLAYER::RESTORE_PLAYER_STAMINA(PLAYER::PLAYER_ID(), 100.0f);
		ATTRIBUTE::_SET_CORE_VALUE(ped, 0, 100000);
		ENTITY::_SET_ENTITY_HEALTH(ped, 100000, 0); // SET_ENTITY_HEALTH
		GRAPHICS::ANIMPOSTFX_STOP_ALL();

		if (PED::IS_PED_SWIMMING(ped) && ENTITY::IS_ENTITY_IN_WATER(ped))
		{
			if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_SPRINT")))
			{
				PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.49f);
				PED::SET_PED_MOVE_RATE_OVERRIDE(ped, 10.0f);
				Vector3 velocity = ENTITY::GET_ENTITY_VELOCITY(ped, -1);
				Vector3 Direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(ped);
				ENTITY::SET_ENTITY_VELOCITY(ped, velocity.x + (Direction.x * 15.0f), velocity.y + (Direction.y * 15.0f), Direction.z);
			}
		}

	}

	if (FREE_AIM_GUN)
	{
		int Aimed_Entity;
		int Player_Ped = PLAYER::PLAYER_PED_ID();
		int Player_ID = PLAYER::PLAYER_ID();
		Vector3 Target_Ped;
		Hash Weapon = MISC::GET_HASH_KEY("WEAPON_FAKE_VARIABLE");
		if (PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(Player_ID, &Aimed_Entity))
		{
			Target_Ped = ENTITY::GET_ENTITY_COORDS(Aimed_Entity, true, 0);
			if (PAD::IS_CONTROL_PRESSED(0, MISC::GET_HASH_KEY("INPUT_AIM")))
			{
				TASK::TASK_SHOOT_AT_COORD(Player_Ped, Target_Ped.x, Target_Ped.y, Target_Ped.z, 0, Weapon, false);
				//MISC::_FORCE_LIGHTNING_FLASH_AT_COORDS(Target_Ped.x, Target_Ped.y, Target_Ped.z); GRAPHICS::START_PARTICLE_FX_NON_LOOPED_AT_COORD("scr_beat_str_fght_win_smh", Target_Ped.x, Target_Ped.y, Target_Ped.z, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0);
				FIRE::ADD_OWNED_EXPLOSION(Player_Ped, Target_Ped.x, Target_Ped.y, Target_Ped.z, 25, 100.0, true, true, 0.0);
				EVENT::_0x118873DD538490B4(MISC::GET_HASH_KEY("EVENT_SHOCKING_EXPLOSION"), 0);
			}
			else if (PAD::IS_CONTROL_JUST_RELEASED(0, MISC::GET_HASH_KEY("INPUT_AIM")))
			{
				TASK::CLEAR_PED_TASKS(Player_Ped, true, true);
			}
		}

	}

	// TLEPORT GUN
	Teleport_Gun();

	// LIGHTNING GUN 
	//if (LIGHTNING_GUN)
	//{
		//Vector3 impact;
		//if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(PLAYER::PLAYER_PED_ID(), &impact))
	//{
		//GAMEPLAY::_FORCE_LIGHTNING_FLASH_AT_COORDS(impact.x, impact.y, impact.z);
	//}
   //}

//Teleport Forward 
		if (IsKeyJustUp(VK_F2))
		{
			Vector3 Coords = ENTITY::GET_ENTITY_COORDS(ped, 1, 1);
			Vector3 Direction = ENTITY::GET_ENTITY_FORWARD_VECTOR(ped);
			ENTITY::SET_ENTITY_COORDS(ped, Coords.x + Direction.x, Coords.y + Direction.y, (Coords.z + Direction.z) - 1.0f, 1, 0, 0, 1);
		}

		/*if (gravityGun)
		{
			PAD::DISABLE_CONTROL_ACTION(0, eInputType::INPUT_ATTACK, 0);

			if (gravityGunPed == NULL)
			{
				if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, eInputType::INPUT_ATTACK))
				{
					Entity entity = NULL;

					if (!PLAYER::GET_ENTITY_PLAYER_IS_FREE_AIMING_AT(GetPlayer(), &entity))
					{
						return;
					}

					if (entity != NULL && ENTITY::DOES_ENTITY_EXIST(entity))
					{
						gravityGunPed = entity;

						PED::SET_PED_TO_RAGDOLL_WITH_FALL(gravityGunPed, 5000, 10000, 0, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
					}
				}
			}
			else
			{
				Vector3 pos = GetGameplayCamOffset(5.5f);
				Vector3 force = Vec3Sub(pos, GetEntityPos(gravityGunPed));
				Vector3 forceMult = Vec3MultiplyFloat(force, 2.0f);

				ApplyForce(gravityGunPed, forceMult);

				if (PAD::IS_DISABLED_CONTROL_JUST_PRESSED(0, eInputType::INPUT_ATTACK))
				{
					Vector3 dir = GetGameplayCamDir();
					Vector3 force = Vec3MultiplyFloat(dir, 200.0f);

					ApplyForce(gravityGunPed, force);

					gravityGunPed = NULL;
				}
			}
		}*/
}