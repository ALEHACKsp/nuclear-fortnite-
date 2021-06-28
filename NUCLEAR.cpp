#include "Includes.h"
#include "spoof_call.hpp"
#include <psapi.h>

//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
//
//╭╮╱╱╭━━━┳━━━┳╮╭━┳━━━┳━━━╮╭━━┳╮╱╱╭╮╭╮╱╭╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━━━┳━━━┳━━━┳━━━╮
//┃┃╱╱┃╭━━┫╭━╮┃┃┃╭┫╭━━┻╮╭╮┃┃╭╮┃╰╮╭╯┃┃┃╱┃┃╱╱╱╱╱╱╱╱╱╱╱╱╱╱┃╭━━┫╭━╮┃╭━╮┃╭━╮┃
//┃┃╱╱┃╰━━┫┃╱┃┃╰╯╯┃╰━━╮┃┃┃┃┃╰╯╰╮╰╯╭╯┃╰━╯┣━━┳━┳╮╭┳━━┳╮╱╭┫╰━━┫╰━╯┃╰━╯┃╰━╯┃
//┃┃╱╭┫╭━━┫╰━╯┃╭╮┃┃╭━━╯┃┃┃┃┃╭━╮┣╮╭╯╱┃╭━╮┃╭╮┃╭┫╰╯┃┃━┫┃╱┃┃╭━╮┣━━╮┣━━╮┃╭━╮┃
//┃╰━╯┃╰━━┫╭━╮┃┃┃╰┫╰━━┳╯╰╯┃┃╰━╯┃┃┃╱╱┃┃╱┃┃╭╮┃┃╰╮╭┫┃━┫╰━╯┃╰━╯┣━━╯┣━━╯┃╰━╯┃
//╰━━━┻━━━┻╯╱╰┻╯╰━┻━━━┻━━━╯╰━━━╯╰╯╱╱╰╯╱╰┻╯╰┻╯╱╰╯╰━━┻━╮╭┻━━━┻━━━┻━━━┻━━━╯
//╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━╯┃
//╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╰━━╯
using namespace str;

unsigned char* g_pSpoofGadget = 0;

#define SPOOFER_MODULE E("ntdll.dll")

#define GLOBAL_DEBUG_FLAG
#define GLOBAL_UNLOAD_FLAG

#ifdef GLOBAL_DEBUG_FLAG
#define DEBUG_ENABLE true
#else
#define NODPRINTF
#define DEBUG_ENABLE false
#endif

struct FHitResult
{//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	char memes[0x1000];
};

#define COLLINMENU_COLOR_1 Colors::Black

ULONGLONG tStarted = 0;
ULONGLONG tEnded = 0;

bool HOOKED = true;

float AimbotKey = VK_RBUTTON;
float WeakSpotAimbotKey = VK_CAPITAL;

#define s c_str()

#define null NULL
#define DEBUG_USE_MBOX false
#define DEBUG_USE_LOGFILE true
#define DEBUG_USE_CONSOLE false
#define DEBUG_LOG_PROCESSEVENT_CALLS false
#define PROCESSEVENT_INDEX 64
#define POSTRENDER_INDEX 91

#define DGOffset_OGI 0x188//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
#define DGOffset_LocalPlayers 0x38
#define DGOffset_PlayerController 0x30
#define DGOffset_MyHUD 0x3C0
#define DGOffset_Canvas 0x378
#define DGOffset_Font 0x90
#define DGOffset_Levels 0x160
#define DGOffset_Actors 0x98
#define DGOffset_RootComponent 0x158
#define DGOffset_ComponentLocation 0x15C
#define DGOffset_Pawn 0x368
#define DGOffset_Mesh 0x388
#define DGOffset_PlayerState 0x348
#define DGOffset_WeaponData 0x388
#define DGOffset_Weapon 0x800
#define DGOffset_DisplayName 0x78
#define DGOffset_ViewportClient 0x70
#define DGOffset_ItemDefinition 0x18
#define DGOffset_PrimaryPickupItemEntry 0x360
#define DGOffset_Tier 0x169
#define DGOffset_BlockingHit 0x0
#define DGOffset_PlayerCameraManager 0x3C8
#define DGOffset_TeamIndex 0xCC0
#define DGOffset_ComponentVelocity 0x1B0
#define DGOffset_MovementComponent 0x390
#define DGOffset_Acceleration 0x26C
#define DGOffset_GravityScale 0x5BC
#define DGOffset_Searched 0xCA8//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
#define DGOffset_bHit 0x340
#define DGOffset_VehicleSkeletalMesh 0xAD8
#define DGOffset_pGEngine 0x5778AD0
#define DGOffset_GObjects 0x5679748
#define DGOffset_GetNameById 0x17BB030
#define DGOffset_GWorld 0x577B240
#define DGOffset_TraceVisibility 0x28BB1A0

#define _ZeroMemory(x, y) (mymemset(x, 0, y));

#ifdef NODPRINTF
#define dprintf(x)
#else
#define dprintf dprintf_func
#endif

uintptr_t GOffset_OGI = 0;
uintptr_t GOffset_LocalPlayers = 0;
uintptr_t GOffset_PlayerController = 0;
uintptr_t GOffset_MyHUD = 0;
uintptr_t GOffset_Canvas = 0;
uintptr_t GOffset_Font = 0;
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
#define M_PI		3.14159265358979323846264338327950288419716939937510582f


uintptr_t GPawn;

int g_MX = 0;
int g_MY = 0;

int g_ScreenWidth = 0;
int g_ScreenHeight = 0;

bool bAimbotActivated = false;

struct keys
{
	bool mouse[4] = {};
	bool key[256] = {};
	float mouse_wheel = 0.f;
	int16_t mouseX = 0;
	int16_t mouseY = 0;
};

keys* k;

template<class T>
struct TArray
{//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	

	public:

		friend struct FString;

	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

	void Clear()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline void Add(T InputData)
	{
		Data = (T*)realloc(Data, sizeof(T) * (Count + 1));
		Data[Count++] = InputData;
		Max = Count;
	};

	T* Data;
	int32_t Count;
	int32_t Max;
};

{
	public:

	inline FString()
	{
	};

	FString(const wchar_t* other)
	{
		Max = Count = *other ? (int32_t)std::wcslen(other) + 1 : 0;
		
		if (Count)
		{
			Data = const_cast<wchar_t*>(other);
		}
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}
};

using tGetPathName = void(__fastcall*)(void* _this, FString* fs, uint64_t zeroarg);
tGetPathName GGetPathName = 0;
void* GGetObjectClass = 0;

string WideToAnsi(const wchar_t* inWide)
{
	static char outAnsi[0x1000];

	int i = 0;
	for (; inWide[i / 2] != L'\0'; i += 2)
		outAnsi[i / 2] = ((const char*)inWide)[i];
	outAnsi[i / 2] = '\0';
	return outAnsi;
}

void __forceinline WideToAnsi(wchar_t* inWide, char* outAnsi)
{
	int i = 0;
	for (; inWide[i / 2] != L'\0'; i += 2)
		outAnsi[i / 2] = ((const char*)inWide)[i];
	outAnsi[i / 2] = '\0';
}

void __forceinline AnsiToWide(char* inAnsi, wchar_t* outWide)
{
	int i = 0;
	for (; inAnsi[i] != '\0'; i++)
		outWide[i] = (wchar_t)(inAnsi)[i];
	outWide[i] = L'\0';
}
using TObjectEntryArray = GObjsTStaticIndirectArrayThreadSafeRead<FUObjectItem, 2 * 1024 * 1024, 0x10400>;

TObjectEntryArray* GObjects;

uintptr_t FindSpooferFromModuleBase(const char* mod)
{
	auto spooferMod = (uintptr_t)GetModuleBase(mod);
	spooferMod += 0x1000;
	while (true)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	{
		if (*(UINT8*)(spooferMod) == 0xFF && *(UINT8*)(spooferMod + 1) == 0x23)
			return spooferMod;
		spooferMod++;
	}
	return 0;
}

uintptr_t FindSpooferFromModule(void* mod)
{
	auto spooferMod = (uintptr_t)mod;
	spooferMod += 0x1000;
	while (true)
	{
		if (*(UINT8*)(spooferMod) == 0xFF && *(UINT8*)(spooferMod + 1) == 0x23)
			return spooferMod;
		spooferMod++;
	}
	return 0;
}

uintptr_t GOffset_bHit = 0;

bo
		if (*(UINT8*)(p1 + off) != *(UINT8*)(p2 + off))
			return false;
		off++;
	}

	return true;
}


	char mz[] = { 0x4D, 0x5A };

	while (true)
	{
		if (MemoryBlocksEqual((void*)ptr, mz, sizeof(mz)))
			break;
		ptr--;
	}

	// we're at module base now.

	ptr += 0x1000;

	while (true)
	{
		if (*(UINT8*)(ptr) == 0xFF && *(UINT8*)(ptr + 1) == 0x23)
			return ptr;
		ptr++;
	}

	return 0;
}


struct FRotator {
	float                                              Pitch;                                                    // 0x0000(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              Yaw;                                                      // 0x0004(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              Roll;                                                     // 0x0008(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)

	inline FRotator()
		: Pitch(0), Yaw(0), Roll(0) {
	}

	inline FRotator(float x, float y, float z)
		: Pitch(x),
		Yaw(y),
		Roll(z) {
	}

	__forceinline FRotator operator+(const FRotator& V) {
		return FRotator(Pitch + V.Pitch, Yaw + V.Yaw, Roll + V.Roll);
	}//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

		return FRotator(Pitch + A, Yaw + A, Roll + A);
	}

	__forceinline FRotator operator-(float A) const {
		return FRotator(Pitch - A, Yaw - A, Roll - A);
	}

	__forceinline FRotator operator*(const FRotator& V) const {
		return FRotator(Pitch * V.Pitch, Yaw * V.Yaw, Roll * V.Roll);
	}

	__forceinline FRotator operator/(const FRotator& V) const {
		return FRotator(Pitch / V.Pitch, Yaw / V.Yaw, Roll / V.Roll);
	}

	__forceinline float operator|(const FRotator& V) const {
		return Pitch * V.Pitch + Yaw * V.Yaw + Roll * V.Roll;
	}

	__forceinline FRotator& operator+=(const FRotator& v) {//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		CHECK_VALID(*this);
		CHECK_VALID(v);
		Pitch += v.Pitch;
		Yaw += v.Yaw;
		Roll += v.Roll;
		return *this;
	}

	__forceinline FRotator& operator-=(const FRotator& v) {
		CHECK_VALID(*this);
		CHECK_VALID(v);
		Pitch -= v.Pitch;
		Yaw -= v.Yaw;
		Roll -= v.Roll;
		return *this;
	}

	__forceinline FRotator& operator*=(const FRotator& v) {
		CHECK_VALID(*this);
		CHECK_VALID(v);
		Pitch *= v.Pitch;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		Yaw *= v.Yaw;
		Roll *= v.Roll;
		return *this;
	}

	__forceinline FRotator& operator/=(const FRotator& v) {
		CHECK_VALID(*this);
		CHECK_VALID(v);
		Pitch /= v.Pitch;
		Yaw /= v.Yaw;
		Roll /= v.Roll;
		return *this;
	}

	__forceinline float operator^(const FRotator& V) const {
		return Pitch * V.Yaw - Yaw * V.Pitch - Roll * V.Roll;
	}

	__forceinline bool operator==(const FRotator& src) const {
		CHECK_VALID(src);
		CHECK_VALID(*this);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		return (src.Pitch == Pitch) && (src.Yaw == Yaw) && (src.Roll == Roll);
	}

	__forceinline bool operator!=(const FRotator& src) const {
		CHECK_VALID(src);
		CHECK_VALID(*this);
		return (src.Pitch != Pitch) || (src.Yaw != Yaw) || (src.Roll != Roll);
	}

	__forceinline float Size() const {
		return mysqrt(Pitch*Pitch + Yaw * Yaw + Roll * Roll);
	}


	__forceinline float SizeSquared() const {
		return Pitch * Pitch + Yaw * Yaw + Roll * Roll;
	}

	__forceinline float Dot(const FRotator& vOther) const {
		const FRotator& a = *this;

		return (a.Pitch * vOther.Pitch + a.Yaw * vOther.Yaw + a.Roll * vOther.Roll);
	}

	__forceinline float ClampAxis(float Angle) {
		// returns Angle in the range (-360,360)
		Angle = fmod(Angle, 360.f);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

		if (Angle < 0.f) {
			// shift to [0,360) range
			Angle += 360.f;
		}

		return Angle;
	}

	__forceinline float NormalizeAxis(float Angle) {
		// returns Angle in the range [0,360)
		Angle = ClampAxis(Angle);

		if (Angle > 180.f) {
			// shift to (-180,180]
			Angle -= 360.f;
		}

		return Angle;
	}

	__forceinline void Normalize() {
		Pitch = NormalizeAxis(Pitch);
		Yaw = NormalizeAxis(Yaw);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		Roll = NormalizeAxis(Roll);
	}

	__forceinline FRotator GetNormalized() const {
		FRotator Rot = *this;
		Rot.Normalize();
		return Rot;
	}
};

typedef struct _D3DMATRIX {
	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
} D3DMATRIX;

// ScriptStruct CoreUObject.Vector
// 0x000C
struct FVector
{
	float                                              X;                                                        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              Y;                                                        // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              Z;                                                        // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FVector()
		: X(0), Y(0), Z(0)
	{ }

	inline FVector(float x, float y, float z)
		: X(x),
		Y(y),
		Z(z)
	{ }

	__forceinline FVector operator-(const FVector& V) {//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		return FVector(X - V.X, Y - V.Y, Z - V.Z);
	}

	__forceinline FVector operator+(const FVector& V) {
		return FVector(X + V.X, Y + V.Y, Z + V.Z);
	}

	__forceinline FVector operator*(float Scale) const {
		return FVector(X * Scale, Y * Scale, Z * Scale);
	}

	__forceinline FVector operator/(float Scale) const {
		const float RScale = 1.f / Scale;
		return FVector(X * RScale, Y * RScale, Z * RScale);
	}

	__forceinline FVector operator+(float A) const {
		return FVector(X + A, Y + A, Z + A);
	}

	__forceinline FVector operator-(float A) const {
		return FVector(X - A, Y - A, Z - A);
	}
	//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	__forceinline FVector operator*(const FVector& V) const {
		return FVector(X * V.X, Y * V.Y, Z * V.Z);
	}

	__forceinline FVector operator/(const FVector& V) const {
		return FVector(X / V.X, Y / V.Y, Z / V.Z);
	}

	__forceinline float operator|(const FVector& V) const {
		return X * V.X + Y * V.Y + Z * V.Z;
	}

	__forceinline float operator^(const FVector& V) const {
		return X * V.Y - Y * V.X - Z * V.Z;
	}

	__forceinline FVector& operator+=(const FVector& v) {
		(*this);
		(v);
		X += v.X;
		Y += v.Y;
		Z += v.Z;
		return *this;
	}//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

	__forceinline FVector& operator-=(const FVector& v) {
		(*this);
		(v);
		X -= v.X;
		Y -= v.Y;
		Z -= v.Z;
		return *this;
	}

	__forceinline FVector& operator*=(const FVector& v) {
		(*this);
		(v);
		X *= v.X;
		Y *= v.Y;
		Z *= v.Z;
		return *this;
	}

	__forceinline FVector& operator/=(const FVector& v) {
		(*this);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		(v);
		X /= v.X;
		Y /= v.Y;
		Z /= v.Z;
		return *this;
	}

	__forceinline bool operator==(const FVector& src) const {
		(src);
		(*this);
		return (src.X == X) && (src.Y == Y) && (src.Z == Z);
	}

	__forceinline bool operator!=(const FVector& src) const {
		(src);
		(*this);
		return (src.X != X) || (src.Y != Y) || (src.Z != Z);
	}

	__forceinline float Size() const {
		return mysqrt(X*X + Y * Y + Z * Z);
	}
	//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	__forceinline float Size2D() const {
		return mysqrt(X*X + Y * Y);
	}

	__forceinline float SizeSquared() const {
		return X * X + Y * Y + Z * Z;
	}

	__forceinline float SizeSquared2D() const {
		return X * X + Y * Y;
	}

	__forceinline float Dot(const FVector& vOther) const {
		const FVector& a = *this;

		return (a.X * vOther.X + a.Y * vOther.Y + a.Z * vOther.Z);
	}

	__forceinline float DistanceFrom(const FVector& Other) const {
		const FVector& a = *this;
		float dx = (a.X - Other.X);
		float dy = (a.Y - Other.Y);
		float dz = (a.Z - Other.Z);

		return (mysqrt((dx * dx) + (dy * dy) + (dz * dz)));
	}
	//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	__forceinline FVector Normalize() {
		FVector vector;
		float length = this->Size();

		if (length != 0) {
			vector.X = X / length;
			vector.Y = Y / length;
			vector.Z = Z / length;
		}
		else
			vector.X = vector.Y = 0.0f;
		vector.Z = 1.0f;

		return vector;
	}

};

D3DMATRIX _inline MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2);


float GetWeaponBulletSpeed(uint64_t cwep);
FVector get_velocity(uint64_t root_comp);
FVector get_acceleration(uint64_t target);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)



// ScriptStruct CoreUObject.Plane
// 0x0004 (0x0010 - 0x000C)
struct alignas(16) FPlane : public FVector
{
	float                                              W;                                                        // 0x000C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
};


// ScriptStruct CoreUObject.Matrix
// 0x0040
struct FMatrix
{
	struct FPlane                                      XPlane;                                                   // 0x0000(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
	struct FPlane                                      YPlane;                                                   // 0x0010(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
	struct FPlane                                      ZPlane;                                                   // 0x0020(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
	struct FPlane                                      WPlane;                                                   // 0x0030(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
};

typedef FMatrix* (*tGetBoneMatrix)(UObject*, FMatrix*, int);
tGetBoneMatrix GetBoneMatrix;
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

enum Bones : uint8_t
{
	Root = 0,
	attach = 1,
	pelvis = 2,
	spine_01 = 3,
	spine_02 = 4,
	Spine_03 = 5,
	spine_04 = 6,
	spine_05 = 7,
	clavicle_l = 8,
	upperarm_l = 9,
	lowerarm_l = 10,
	Hand_L = 11,
	index_metacarpal_l = 12,
	index_01_l = 13,
	index_02_l = 14,
	index_03_l = 15,
};
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
float bestFOV = 0.f;
FRotator idealAngDelta;

float AimbotFOV = 90;//

void AimbotBeginFrame()
{
	bestFOV = AimbotFOV;
	idealAngDelta = { 0,0,0 };
}

string GetObjectFullNameA(UObject* obj);

template <typename T>
T read(uint64_t address)
{
	T tmp;
	if (read(&tmp, address, sizeof(tmp)))
		return tmp;
	else
		return T();
}

uint32_t GetGNameID(UObject* obj)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
{
	if (!obj)
		return 0;
	return read<uint32_t>((uint64_t)(obj + offsetof(UObject, UObject::name)));
}

uint64_t GetGNameID64(uint64_t obj)
{
	if (!obj)
		return 0;
	return read<uint64_t>(obj + offsetof(UObject, UObject::name));
}

using tGetNameFromId = uintptr_t(__fastcall*)(uint64_t* ID, void *buffer);
tGetNameFromId GGetNameFromId = 0;
UObject** pGEngine = 0;
UObject* GEngine = 0;
tGetBoneMatrix GGetBoneMatrix = 0;

#define MESH_BONE_ARRAY 0x5A0
#define MESH_COMPONENT_TO_WORLD 0x180
FVector BoneToWorld(Bones boneid, uint64_t mesh);

FVector GetBone3D(UObject* _this, int bone)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
{
	return BoneToWorld((Bones)bone, (uint64_t)_this);

	FMatrix vMatrix;
	GGetBoneMatrix(_this, &vMatrix, bone);
	return vMatrix.WPlane;
}

bool B2S(UObject* _this, int bone, FVector2D& outScrLoc)
{
	FVector tmp = GetBone3D(_this, bone);
	return W2S(tmp, outScrLoc);
}

wstring GetGNameByIdW(uint64_t id)
{
	if (!id || id >= 1000000)
		return E(L"None_X0");

	static wchar_t buff[0x10000];
	_ZeroMemory(buff, sizeof(buff));

	auto v47 = spoof_call(g_pSpoofGadget, GGetNameFromId, &id, (void*)buff);
	if (myIsBadReadPtr((void*)v47, 0x8))
	{
		//dprintf(E("Getgnbyid bad result"));
		return E(L"None_X1");//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	}
	if (v47 && *((DWORD *)v47 + 2))
	{
		//dprintf(E("Getgnbyid gud result"));
		return *(const wchar_t **)v47;
	}
	else
	{
		//dprintf(E("Getgnbyid bad result #2"));
		return E(L"None_X2");
	}
}

string GetGNameByIdA(uint64_t id)
{
	auto str = GetGNameByIdW(id);
	//dprintf(E("123234434"));
	return WideToAnsi(str.c_str());
}

void PrintNames(int end)
{
	if (end == 0)
		end = 500000;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

	dprintf(E("Looping through names.."));
	for (int i = 0; i < end; i++)
	{
		auto name = GetGNameByIdA(i);
		dprintf(E("[%d] -> %s"), i, name.c_str());
	}
	dprintf(E("Done.."));
}

wstring GetObjectNameW(UObject* obj);

string GetObjectNameA(UObject* obj)
{
	auto name = GetObjectNameW(obj);
	return WideToAnsi(name.c_str());
}

void GetAll(UObject* _this, vector<UObject*>* memes)
{	
	memes->push_back(_this);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

	if (!((UStruct*)_this)->Children)
		return;

	//dprintf("2");

	int cnt = 0;
	auto child = read<UStruct*>((uint64_t)_this + offsetof(UStruct, UStruct::Children));
	//dprintf("3");
	for (; child != nullptr; child = read<UStruct*>((uintptr_t)child + offsetof(UField, Next)))
	{
		if (cnt >= 100)
			return;
		//dprintf("4X");
		if (myIsBadReadPtr(child, 0x8) || myIsBadReadPtr(child->Class, 0x8))
			return;
		memes->push_back(child);
		cnt++;
	}
	//dprintf("5");
}

#define INRANGE(x,a,b)    (x >= a && x <= b) //nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xA) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

uintptr_t FindPattern(const char* pattern)
{
	char* pat = const_cast<char*>(pattern);
	uintptr_t firstMatch = 0;
	if(firstMatch)
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(BYTE*)pat == '\?')
				pat += 2;
			else
				pat += 3;
		}
		else
		{
			pat = const_cast<char*>(pattern);
			firstMatch = 0;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		}
	}

	return 0;
}

uintptr_t ResolveRelativeReference(uintptr_t address, uint32_t offset = 0)
{
	if (address)
	{
		address += offset;//

		if (*reinterpret_cast<byte*>(address) == 0xE9 || *reinterpret_cast<byte*>(address) == 0xE8)
		{
			auto displacement = *reinterpret_cast<uint32_t*>(address + 1);
			auto ret = address + displacement + 5;

			if (displacement & 0x80000000)
				ret -= 0x100000000;

			return ret;
		}
			return ret;
		}
	}
	else
	{//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		return 0;
	}
}

uintptr_t GetGObjects()
{
	auto ss = FindPattern(E("49 63 C8 48 8D 14 40 48 8B 05 ? ? ? ? 48 8B 0C C8 48 8D 04 D1"));

	if (!ss)
		return 0;

	ss += 7;

	return (ss + 7 + *(int32_t*)(ss + 3));
}

uint64_t SigScanSimple(uint64_t base, uint32_t size, PBYTE sig, int len)
{
	for (size_t i = 0; i < size; i++)
		if (MemoryBlocksEqual((void*)(base + i), sig, len))
			return base + i;
	return NULL;
}

UINT32 UWorldOffset = 0;

typedef void(*tUE4ProcessEvent)(UObject*, UObject*, void*);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

tUE4ProcessEvent GoPE = 0;//


template<typename Fn>

uint32_t GetVtableSize(void* object)
{
	auto vtable = *(void***)(object);
	int i = 0;

	for (; vtable[i]; i++)
		__noop();

	return i;
}

vector<void*>* GHookedObjects;

D3DMATRIX Matrix(FRotator rot, FVector origin = { 0, 0, 0 })
{
	float radPitch = rot.Pitch * M_PI / 180.f;
	float radYaw = rot.Yaw * M_PI / 180.f;
	float radRoll = rot.Roll * M_PI / 180.f;

	float SP = mysin(radPitch);
	float CP = mycos(radPitch);
	float SY = mysin(radYaw);//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	float CY = mycos(radYaw);
	float SR = mysin(radRoll);
	float CR = mycos(radRoll);

	return matrix;
}

bool IsObjectHooked(void* obj) 
{
	for (auto x : *GHookedObjects)
	{
		if (x == obj)
			return true;
	}

	return false;
}


class UFunction : public UStruct//

{
public:
	int32_t FunctionFlags; //0x0088
	int16_t RepOffset; //0x008C
	int8_t NumParms; //0x008E
	char pad_0x008F[0x1]; //0x008F
};//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

UFunction* S_ReceiveDrawHUD()
{
	static UFunction* ass = 0;
	if (!ass)
		ass = (UFunction*)FindObject(E("Function Engine.HUD.ReceiveDrawHUD"));
	return ass;
}

UObject* GHUD;
UObject* GCanvas;

// ScriptStruct CoreUObject.LinearColor
// 0x0010
struct FLinearColor
{
	float                                              R;                                                        // 0x0000(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              G;                                                        // 0x0004(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              B;                                                        // 0x0008(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)
	float                                              A;                                                        // 0x000C(0x0004) (Edit, BlueprintVisible, ZeroConstructor, SaveGame, IsPlainOldData)

	inline FLinearColor()
		: R(0), G(0), B(0), A(0)
	{ }

	inline FLinearColor(float r, float g, float b, float a)
		: R(r),//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		G(g),
		B(b),
		A(a)
	{ }

};

TArray<UObject*>* GActorArray = 0;

struct UCanvas_K2_DrawText_Params
{
	class UFont*                                       RenderFont;                                               // (Parm, ZeroConstructor, IsPlainOldData)
	class FString                                     RenderText;                                               // (Parm, ZeroConstructor)
	struct FVector2D                                   ScreenPosition;                                           // (Parm, IsPlainOldData)
	struct FLinearColor                                RenderColor;                                              // (Parm, IsPlainOldData)
	float                                              Kerning;                                                  // (Parm, ZeroConstructor, IsPlainOldData)
	struct FVector2D                                   ShadowOffset;                                             // (Parm, IsPlainOldData)
	bool                                               bCentreX;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bCentreY;                                                 // (Parm, ZeroConstructor, IsPlainOldData)
	bool                                               bOutl;                                                    // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                OutlineColor;                                             // (Parm, IsPlainOldData)
};
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
namespace G
{
	bool EspWeapon = true;
	bool RefreshEach1s = false;
	bool Snaplines = false;
	bool CornerBox = true;
	float CornerBoxThicc = 1.7f;
	float RedDistance = 40.0f;
	float CornerBoxScale = 0.20;
	bool PunktierSnaplines = true;
	float PunktierPower = 16.6f;
	bool SnaplinesIn50m = false;
	bool Baim = true;
	float SkeletonThicc = 1.0f;
	//bool AimbotUseRightButton = false;
	float PlayerBoxThicc = 1.0f;
	bool WeakSpotAimbot = true;
	bool ProjectileTpEnable = false;
	bool ShowTimeConsumed = true;
	float Smooth = 0.3;
	bool CollisionDisableOnAimbotKey = true;
	bool FlyingCars = true;
	bool UseEngineW2S = false;
	bool Chests = true;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	bool TpPrisonersEnable = true;
	bool DrawSelf = false;
	bool LootWeapons = true;
	int JumpScale = 1;
	bool Projectiles = true;
	int TpTimeInterval = 250;
	float LootTier = 3;
	bool LootMelee = true;
	bool bAllowedTp = true;
	bool Outline = true;
	bool Skeletons = true;
	bool EspPlayerName = false;
	bool EspLoot = true;
	bool EspRifts = false;
	bool EspSupplyDrops = false;
	bool EspTraps = true;//
	bool EspVehicles = false;
	bool Healthbars = true;
	bool LootHeals = true;
	bool LootAttachments = true;
	bool LootAmmo = true;
	bool EspBox = true;
	bool LootEquipment = true;
	bool TpLootAndCorpses = true;
	bool TpZombiesEnable = true;
	bool EnableHack = true;
	bool LootFood = true;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	bool LootWear = true;
	bool TpAnimalsEnable = true;
	bool TpSentriesEnable = true;
	uintptr_t MmBase;
	bool TimeSpeedhackEnable = false;
	bool MovSpeedhackEnable = true;
	int MovSpeedhackScale = 2;
	bool AimbotEnable = true;
	bool EspSentries = true;
	bool EspZombies = false;
	bool EspPlayers = true;
	bool EspCorpses = true;
	bool EspAnimals = true;
	bool EspDrones = true;
	float RenderDist = 650;
	float ChestsRdist = 200;
	UObject* Closest;
	bool AimbotTargetPlayers = true;
	bool AimbotTargetZombies;
	float LootRenderDist = 300;
	int IconScale = 21;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	bool LootEnable = true;
	bool AimbotTargetDrones;
	bool OnlyWeapons = true;//
	uintptr_t MmSize;
	bool AimbotTargetAnimals;
	uintptr_t CurrentTime;
	bool AimbotTargetSentries;
	int ItemRarityLevel = 7;
	UObject* CameraManager;
	uintptr_t LastTimePEHookCalled;
	bool NoRecoil = true;
	bool InfAmmo = true;
}

FVector2D K2_StrLen(UObject* canvas, class UObject* RenderFont, const struct FString& RenderText)
{

	struct
	{
		class UObject*                   RenderFont;
		struct FString                 RenderText;
		struct FVector2D               ReturnValue;
	} params;

	params.RenderFont = RenderFont;
	params.RenderText = RenderText;
	//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	ProcessEvent(canvas, fn, &params);

	return params.ReturnValue;
}

FCameraCacheEntry* GCameraCache = nullptr;



bool W2S(FVector inWorldLocation, FVector2D& outScreenLocation)
{
		return W2S((UObject*)UControl, inWorldLocation, false, &outScreenLocation);
}

bool Object_IsA(UObject* obj, UObject* cmp);

float GetDistanceTo(UObject* _this, class UObject* OtherActor)
{

}


int Dist(UObject* other)
{//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	if (!GPawn)
		return 0;

	return (int)(GetDistanceTo((UObject*)GPawn, other) / 100);
}

uintptr_t GOffset_BlockingHit;
uintptr_t GOffset_PlayerCameraManager;
uintptr_t GOffset_TeamIndex = 0;

// ScriptStruct Engine.HitResult
// 0x0088

template<class TEnum>
class TEnumAsByte
{
public:
	inline TEnumAsByte()
	{
	}


	inline TEnum GetValue() const
	{
		return (TEnum)value;
	}
	//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
private:
	uint8_t value;
};

struct alignas(16) FQuat
{
	float                                              X;                                                        // 0x0000(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              Y;                                                        // 0x0004(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              Z;                                                        // 0x0008(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
	float                                              W;                                                        // 0x000C(0x0004) (CPF_Edit, CPF_BlueprintVisible, CPF_ZeroConstructor, CPF_SaveGame, CPF_IsPlainOldData)
};

// ScriptStruct CoreUObject.Transform
// 0x0030
struct alignas(16) FTransform
{
	struct FQuat                                       Rotation;                                                 // 0x0000(0x0010) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
	struct FVector                                     Translation;                                              // 0x0010(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
	unsigned char                                      UnknownData00[0x4];                                       // 0x001C(0x0004) MISSED OFFSET
	struct FVector                                     Scale3D;                                                  // 0x0020(0x000C) (CPF_Edit, CPF_BlueprintVisible, CPF_SaveGame, CPF_IsPlainOldData)
	unsigned char                                      UnknownData01[0x4];                   //nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)                    // 0x002C(0x0004) MISSED OFFSET
};

uintptr_t GOffset_Mesh = 0;
uintptr_t GOffset_Weapon = 0;
uintptr_t GOffset_WeaponData = 0;
uintptr_t GOffset_DisplayName = 0;
uintptr_t GOffset_ViewportClient = 0;

struct UCanvas_K2_DrawLine_Params
{
	FVector2D                                   ScreenPositionA;                                          // (Parm, IsPlainOldData)
	FVector2D                                   ScreenPositionB;                                          // (Parm, IsPlainOldData)
	float                                              Thickness;                                                // (Parm, ZeroConstructor, IsPlainOldData)
	struct FLinearColor                                RenderColor;                                              // (Parm, IsPlainOldData)
};

struct FName GetBoneName(UObject* _this, int BoneIndex)
{
	static UFunction* fn = 0; if (!fn) fn = (UFunction*)FindObject(E("Function Engine.SkinnedMeshComponent.GetBoneName"));

	struct
	{
		int                            BoneIndex;
		struct FName                   ReturnValue;
	} params;//

	params.BoneIndex = BoneIndex;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

	ProcessEvent(_this, fn, &params);

	return params.ReturnValue;
}

bool __forceinline point_valid(FVector2D& val)
{
	return val.X > 0 && val.X < (float)g_ScreenWidth && val.Y > 0 && val.Y < (float)g_ScreenHeight;
}

void DrawBones(UObject* mesh, Bones* arr, int sz, FLinearColor clr, FVector2D& topleft, FVector2D& downright, float b_thicc = 1.0f)
{
	for (int i = 1; i < sz; i++)
	{
		FVector2D spPrev;
		FVector2D spNext;

		FVector previousBone = GetBone3D(mesh, arr[i - 1]);

		if (previousBone == FVector())
			continue;

		if (!W2S(previousBone, spPrev))
			continue;

		FVector nextBone = GetBone3D(mesh, arr[i]);

		if (nextBone == FVector())
			continue;

		if (!W2S(nextBone, spNext))
			continue;

		if (previousBone.DistanceFrom(nextBone) > 100)
			continue;

		auto x = spPrev;

		if (x.X > downright.X)//
			downright.X = x.X;

	}
}
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
void DebugDrawBoneIDs(UObject* mesh)
{
	for (int x = 0; x < 100; x++)
	{
		FVector2D mem;
		B2S(mesh, x, mem);
		string id = myitoa(x);
		xDrawText(AnsiToWide(id.c_str()).c_str(), mem, Colors::Red);
	}
}



struct FString GetPlayerName(UObject* player)
{


}//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

uintptr_t GOffset_PlayerState = 0;

class FTextData {
public:
	char pad_0x0000[0x28];  //0x0000
	wchar_t* Name;          //0x0028 
	__int32 Length;         //0x0030 

};

struct FText {
	FTextData* Data;
	char UnknownData[0x10];

	wchar_t* Get() const {
		if (Data) {
			return Data->Name;
		}

		return nullptr;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	}//
};

class UControl
{
public:

	FVector2D Origin;
	FVector2D Size;
	bool* BoundBool = nullptr;
	bool bIsMenuTabControl;

	bool ContainsPoint(FVector2D pt)
	{
		auto extent = Origin + Size;
		return (pt.X > Origin.X && pt.Y > Origin.Y && pt.X < extent.X && pt.Y < extent.Y);
	}
};


uintptr_t GOffset_PrimaryPickupItemEntry = 0;
uintptr_t GOffset_Tier = 0;
uintptr_t GOffset_ItemDefinition = 0;
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
void MwMenuDraw();

vector<UControl>* g_ControlBoundsList;


D3DMATRIX _inline MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;

	return pOut;
}

#define x X
#define y Y
#define z Z
#define w W
#undef x
#undef y
#undef z
#undef w

uintptr_t g_VehSelected = 0;

HWND GHGameWindow = 0;

int GetTeamId(UObject* actor)
{
	auto playerState = read<UObject*>((uintptr_t)actor + DGOffset_PlayerState);

	if (playerState)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	{
		return read<int>((uint64_t)playerState + DGOffset_TeamIndex);
	}

	return 0;
}

float cached_bullet_gravity_scale = 0.f, cached_world_gravity = 0.f;

int GMyTeamId = 0;

uintptr_t GOffset_GravityScale = 0;
uintptr_t GOffset_Searched = 0;

FRotator Clamp(FRotator r)
{
	if (r.Yaw > 180.f)
		r.Yaw -= 360.f;
	else if (r.Yaw < -180.f)//

		r.Yaw += 360.f;

	if (r.Pitch > 180.f)
		r.Pitch -= 360.f;

	return r;
}
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
void AimToTarget()
{
	if (bestFOV >= AimbotFOV)
		return;

	//bAimbotActivated = true;

	SetViewAngles(GCameraCache->Rotation + idealAngDelta*G::Smooth);
}

#define DEG2RAD(x)  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define M_PI_F		((float)(M_PI))
#define RAD2DEG(x)  ( (float)(x) * (float)(180.f / M_PI_F) )

FRotator Vec2Rot(FVector vec)
{
	FRotator rot;

	rot.Yaw = RAD2DEG(myatan(vec.Y, vec.X));
	rot.Pitch = RAD2DEG(myatan(vec.Z, mysqrt(vec.X * vec.X + vec.Y * vec.Y)));
	rot.Roll = 0.f;

	return rot;
}//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
bool get_visible(UObject* mesh)
{
	
}

void Render()
{
	FLinearColor clr(1, 1, 1, 1);

	if (G::EnableHack)
	{
		if(G::AimbotEnable)
			AimbotBeginFrame();
		

		auto bCaps = false;


		for (int levelIndex = 0; (G::LootEnable? (levelIndex != levels.Num()) : levelIndex != 1); levelIndex++)
		{
			auto level = levels[levelIndex];

			if (!level)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
			{
				xDrawText(E(L"NO LEVEL #2!"), { 600, 600 }, clr);
				return;
			}

			GActorArray = (TArray<UObject*>*)((uintptr_t)level + DGOffset_Actors);
			auto actors = *GActorArray;

			static UClass* supply_class = nullptr;
			static UClass* trap_class = nullptr;
			static UClass* fortpickup_class = nullptr;
			static UClass* projectiles_class = nullptr;		
			static UClass* weakspot_class = nullptr;


		bAimbotActivated = false;

		if (G::AimbotEnable)
		{
			if (bCaps)
			{
				auto old = AimbotFOV;
				AimbotFOV = 90;
				AimToTarget();
				AimbotFOV = old;
			}
			else//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
			{
				if (spoof_call(g_pSpoofGadget, GetAsyncKeyState, (int)AimbotKey))
				{
					bAimbotActivated = true;
					AimToTarget();
				}
			}
		}
	}

	if (g_Menu)
		MwMenuDraw();
}
	//

uintptr_t GOffset_Pawn;

uintptr_t GetWorld()
{
	return *(uint64_t*)(GFnBase + UWorldOffset);
}

bool get_camera(FMinimalViewInfo* view, uint64_t player_camera_mgr)
{
	auto player_camera_mgr_VTable = read<uintptr_t>(player_camera_mgr);
	if (!player_camera_mgr_VTable)
		return false;
	//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
}

void PreRender()
{
	GWorld = GetWorld();

	if (GWorld && GCanvas)
	{
		auto GameInstance = read<uint64_t>(GWorld + DGOffset_OGI);
		auto LocalPlayers = read<uint64_t>(GameInstance + DGOffset_LocalPlayers);
		auto ULocalPlayer = read<uint64_t>(LocalPlayers);
	}
}

urn spoof_call(g_pSpoofGadget, GoPE, _this, (UObject*)fn, parms);
}

int find_last_of(str::string& _this, char c)
{
	auto last = -1;
	for (int i = 0; i < _this.length(); i++)
	{
		auto cCurrent = _this[i];
		if (cCurrent == c)
			last = i;
	}
	return last;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
}
//

string GetObjectFullNameA(UObject* obj)
{
	if (myIsBadReadPtr(obj, sizeof(UObject)))
		return E("None_X9");

	if (myIsBadReadPtr(obj->Class, sizeof(UClass)))
		return E("None_X10");

	auto objName = GetObjectNameA(obj);
	auto className = GetObjectNameA(obj->Class);

	str::string temp;
	str::string name;
	//dprintf("14");
	int memes = 0;
	for (auto p = obj->Outer; !myIsBadReadPtr(p, 0x8); p = p->Outer)
	{
		memes++;
		if (memes >= 100)
			return E("None_X13");
		//dprintf("14.5");
		str::string temp2;
		auto outerName = GetObjectNameA(p);
		temp2 = outerName;
		temp2.append(E("."));//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
		temp2.append(temp);
		temp = temp2;
	}
	//dprintf("16");

	str::string shit;

	shit.append(temp);
	shit.append(objName);

	auto last = find_last_of(shit, '/');
	if (last != -1)
		shit.pop_front(last + 1);

	name.append(className);
	name.append(E(" "));
	name.append(shit);//


	//name.append(" ");
	//name.append(myitoa(last));
	//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
	return name;
}

uintptr_t GOffset_ComponentVelocity = 0;
uintptr_t GOffset_MovementComponent = 0;
uintptr_t GOffset_Acceleration = 0;

struct AFortWeapon_GetProjectileSpeed_Params
{
	float                                              ReturnValue;                                              // (Parm, OutParm, ZeroConstructor, ReturnParm, IsPlainOldData)
};

void CallUFunction(UObject* obj, UFunction * fn, void * params)
{
	if (!obj || !fn)
		return;
	static int FunctionFlags_Offset = 0x88; //tried from 0x80 - 0x8e
	/*{
		char buf[40];
		sprintf_s(buf, "trying 0x%x\r\n", FunctionFlags_Offset);
		write_debug_log(buf);
	}*/

	auto flags = *(uint32_t*)((uint64_t)fn + FunctionFlags_Offset);

}
//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

bool Object_IsA(UObject* obj, UObject* cmp)
{
	if (!cmp)
		return false;

	UINT i = 0;

	//dprintf(E(""));
	//dprintf(E("-> IsA %p (%s)"), cmp, GetObjectFullNameA(cmp).c_str());
	//dprintf(E(""));

	for (auto super = read<uint64_t>((uint64_t)obj + offsetof(UObject, UObject::Class)); super; super = read<uint64_t>(super + offsetof(UStruct, UStruct::SuperField)))
	{

	//dprintf(E(""));

	return false;
}

bool bLogFindObject = true;

UObject* FindObject(const char* name)
{
	char fullName[1024];

	if(bLogFindObject)
		dprintf(E("FindObject: finding: %s"), name);

	for (int i = 0; i < GObjects->Num(); i++)

		vector<UObject*> objs;
		GetAll(obj_x, &objs);

		for(int x = 0; x < objs.size(); x++)
		{
			auto obj = objs[x];

			auto fullName = GetObjectFullNameA(obj);

			if (!mystrcmp(name, fullName.c_str()))
			{
				if (bLogFindObject)
					dprintf(E("FindObject: found: [%d] -> 0x%p -> %s"), i, obj, fullName.c_str());
				return obj;
			}
		}
	}
	if (bLogFindObject)
		dprintf(E("Search has failed!"));

	return 0;
}

UClass* SC_AHUD()
{
	static UClass* obj = 0;
	if (!obj)
		obj = (UClass*)FindObject(E("Class Engine.HUD"));
	return obj;
}

using tUE4PostRender = void(*)(UObject* _this, UObject* canvas);

tUE4PostRender GoPR = 0;

FVector get_velocity(uint64_t root_comp)
{
	return read<FVector>(root_comp + DGOffset_ComponentVelocity);

}

FVector get_acceleration(uint64_t target)//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)
{
}

int g_MenuW = 500;
int g_MenuH = 470;

uintptr_t GetGetGNameById()
{
	uintptr_t cs = 0;
	int addy = 0;

	cs = FindPattern(E("E8 ? ? ? ? 83 7C 24 ? ? 48 0F 45 7C 24 ? EB 0E "));
	if (!cs)
	{
		dprintf(E("SS Fail (1)"));
		cs = FindPattern(E("48 83 C3 20 E8 ? ? ? ? "));
		addy = 4;
	}
	if (!cs) 
	{
		dprintf(E("SS Fail (2)"));
		addy = 0;
		cs = FindPattern(E("E8 ? ? ? ? 48 8B D0 48 8D 4C 24 ? E8 ? ? ? ? 48 8B D8 E8 ? ? ? ? "));
	}

	if (!cs)
	{
		dprintf(E("SS Fail (3)"));
		return 0;
	}

	cs += addy;

	return ResolveRelativeReference(cs);
}

bool g_Chineese = false;
bool g_Russian = false;
bool g_Korean = false;

void drawFilledRect(const FVector2D& initial_pos, float w, float h, const FLinearColor& color);

void RegisterButtonControl(const FVector2D initial_pos, float w, float h, const FLinearColor color, int tabIndex = -1, bool* boundBool = nullptr)
{
	drawFilledRect(initial_pos, w, h, color);
	UControl bounds;
	bounds.Origin = initial_pos;
	g_ControlBoundsList->push_back(bounds);
}

FVector2D g_Clientarea;//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

FVector2D g_MenuInitialPos = { 400, 400 };

int g_MenuIndex = 1;

uintptr_t GetTraceVisibilityFn()
{
	return FindPattern(E("4C 8B DC 56 48 81 EC 50 01 00 00 48 8B"));
}

void main()
{

	dprintf(E("GFnBase: 0x%p, GFnSize: 0x%X"), GFnBase, GFnSize);

	g_pSpoofGadget = (unsigned char*)FindSpooferFromModule((void*)GFnBase);
	dprintf(E("New Spoof gadget: 0x%p"), g_pSpoofGadget);

#ifdef GLOBAL_DEBUG_FLAG
	PatchFwFuncs();
#endif GLOBAL_DEBUG_FLAG

#ifdef GLOBAL_DEBUG_FLAG

	GObjects = (TObjectEntryArray*)(GetGObjects());

	if (!GObjects)
	{
		dprintf(E("Failed to initialize GObjects!"));
		return;
	}
	else
		dprintf(E("GObjects OK"));

	GGetNameFromId = (tGetNameFromId)(GetGetGNameById());

	if (!GGetNameFromId)
	{
		dprintf(E("Failed to initialize GetGNameById!"));
		return;//

	}
	else
		dprintf(E("GetNameShit OK"));

	pGEngine = (UObject**)GetGEngine();


	GTraceVisibilityFn = (tTraceVisibility)GetTraceVisibilityFn();

#else

#endif

	GEngine = *pGEngine;

#ifdef GLOBAL_DEBUG_FLAG

	auto pUWorldRefFunc = SigScanSimple(GFnBase, GFnSize, (PBYTE)E("\x40\x57\x48\x83\xEC\x50\x48\x8B\x49\x08\x8B\xFA\x48\x83\xC1\x30"), 16);

	// 40 57 48 83 EC 50 48 8B 49 08 8B FA 48 83 C1 30//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

	if (!pUWorldRefFunc)
	{
		dprintf(E("No UWorld ref func!"));
		return;
	}
	else
	{
		dprintf((E("UWorld ref found!")));
	}//


	for (int i = 0; i < 0x100; i++) 
	{
		if (MemoryBlocksEqual(&PBYTE(pUWorldRefFunc)[i], (PBYTE)"\x48\x8B\x05", 3)) 
		{
			auto f = pUWorldRefFunc + i;
			auto offset = *PINT(f + 3);
			UWorldOffset = (f + offset + 7) - (uintptr_t)GFnBase;
			dprintf(E("UWorldOffset: 0x%X"), UWorldOffset);
		}
	}

#else

	UWorldOffset = DGOffset_GWorld;

#endif

}


//nuclear source from 2018 leaked by Harvey#6998 , dm if you need help fixing :)

//
//╭╮╱╱╭━━━┳━━━┳╮╭━┳━━━┳━━━╮╭━━┳╮╱╱╭╮╭╮╱╭╮╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━━━┳━━━┳━━━┳━━━╮
//┃┃╱╱┃╭━━┫╭━╮┃┃┃╭┫╭━━┻╮╭╮┃┃╭╮┃╰╮╭╯┃┃┃╱┃┃╱╱╱╱╱╱╱╱╱╱╱╱╱╱┃╭━━┫╭━╮┃╭━╮┃╭━╮┃
//┃┃╱╱┃╰━━┫┃╱┃┃╰╯╯┃╰━━╮┃┃┃┃┃╰╯╰╮╰╯╭╯┃╰━╯┣━━┳━┳╮╭┳━━┳╮╱╭┫╰━━┫╰━╯┃╰━╯┃╰━╯┃
//┃┃╱╭┫╭━━┫╰━╯┃╭╮┃┃╭━━╯┃┃┃┃┃╭━╮┣╮╭╯╱┃╭━╮┃╭╮┃╭┫╰╯┃┃━┫┃╱┃┃╭━╮┣━━╮┣━━╮┃╭━╮┃
//┃╰━╯┃╰━━┫╭━╮┃┃┃╰┫╰━━┳╯╰╯┃┃╰━╯┃┃┃╱╱┃┃╱┃┃╭╮┃┃╰╮╭┫┃━┫╰━╯┃╰━╯┣━━╯┣━━╯┃╰━╯┃
//╰━━━┻━━━┻╯╱╰┻╯╰━┻━━━┻━━━╯╰━━━╯╰╯╱╱╰╯╱╰┻╯╰┻╯╱╰╯╰━━┻━╮╭┻━━━┻━━━┻━━━┻━━━╯
//╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╭━╯┃
//╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╱╰━━╯
