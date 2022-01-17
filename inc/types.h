#pragma once

#include <Windows.h>
#include "../samples/HotAirBalloon/stdafx.h"

#define UP "INPUT_FRONTEND_UP"
#define DOWN "INPUT_FRONTEND_DOWN"
#define RIGHT "INPUT_FRONTEND_RIGHT"
#define LEFT "INPUT_FRONTEND_LEFT"
#define Y "INPUT_FRONTEND_Y"
#define A "INPUT_FRONTEND_ACCEPT"
#define X "INPUT_FRONTEND_X"
#define B "INPUT_FRONTEND_CANCEL"
#define L_TRIGGER "INPUT_FRONTEND_LT"
#define R_TRIGGER "INPUT_FRONTEND_RT"
#define L_BUMBER "INPUT_FRONTEND_LB"
#define R_BUMBER "INPUT_FRONTEND_RB"
#define L3 "INPUT_FRONTEND_LS"
#define R3 "INPUT_FRONTEND_RS"

using Entity = int;
using Ped = int;
using Vehicle = int;
using Cam = int;
using Object = int;
using Pickup = int;
using Blip = int;
using ScrHandle = int;
using Player = unsigned int;
using Hash = unsigned int;
using Void = uint64_t;
using Any = uint64_t;

using Prompt = int;
using Interior = int;
using Itemset = int;
using PopZone = int;
using Volume = int;
using AnimScene = bool;
using FireId = int;
using WeaponGroup = int;


const double PI = 3.141592653589793238463;

struct Vector3
{
	alignas(8) float x, y, z;
};

struct Time
{
	alignas(8) int h, m, s;
};

struct color
{
	alignas(8) int r, g, b, a;
};

struct StatIDArgs
{
	alignas(8) int BaseId;
	alignas(8) int PermutationId;
};

struct KeyIDArgs
{
	alignas(8) uint64_t* BaseId;
	alignas(8) uint64_t* PermutationId;
};

/*
typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;

#define ALIGN8 __declspec(align(8))

struct Vector3
{
	ALIGN8 float x;
	ALIGN8 float y;
	ALIGN8 float z;
};

static_assert(sizeof(Vector3) == 24, "");
*/