#pragma once
#ifndef W2S
#define W2S
#include "../../../kernel/driver.h"

#include "../../../framework/d3d/d3dx9math.h"

#define M_PI 3.14159265358979323846f
class Vector2
{
public:
	Vector2() : x(0.f), y(0.f) {}
	Vector2(double _x, double _y) : x(_x), y(_y) {}
	~Vector2() {}
	double x, y;
};
class Vector3
{
public:
	double x, y, z;

	Vector3()
	{
		x = y = z = 0.0f;
	}

	Vector3(double X, double Y, double Z)
	{
		x = X; y = Y; z = Z;
	}

	Vector3(double XYZ)
	{
		x = XYZ; y = XYZ; z = XYZ;
	}

	Vector3(double* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vector3(const double* v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	__forceinline Vector3& operator=(const Vector3& v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	__forceinline Vector3& operator=(const double* v)
	{
		x = v[0]; y = v[1]; z = v[2]; return *this;
	}

	__forceinline double& operator[](int i)
	{
		return ((double*)this)[i];
	}

	__forceinline double operator[](int i) const
	{
		return ((double*)this)[i];
	}

	__forceinline Vector3& operator+=(const Vector3& v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	__forceinline Vector3& operator-=(const Vector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	__forceinline Vector3& operator*=(const Vector3& v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	__forceinline Vector3& operator/=(const Vector3& v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	__forceinline Vector3& operator+=(double v)
	{
		x += v; y += v; z += v; return *this;
	}

	__forceinline Vector3& operator-=(double v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	__forceinline Vector3& operator*=(double v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	__forceinline Vector3& operator/=(double v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	__forceinline Vector3 operator-() const
	{
		return Vector3(-x, -y, -z);
	}

	__forceinline Vector3 operator+(const Vector3& v) const
	{
		return Vector3(x + v.x, y + v.y, z + v.z);
	}

	__forceinline Vector3 operator-(const Vector3& v) const
	{
		return Vector3(x - v.x, y - v.y, z - v.z);
	}

	__forceinline Vector3 operator*(const Vector3& v) const
	{
		return Vector3(x * v.x, y * v.y, z * v.z);
	}

	__forceinline Vector3 operator/(const Vector3& v) const
	{
		return Vector3(x / v.x, y / v.y, z / v.z);
	}

	__forceinline Vector3 operator+(double v) const
	{
		return Vector3(x + v, y + v, z + v);
	}

	__forceinline Vector3 operator-(double v) const
	{
		return Vector3(x - v, y - v, z - v);
	}

	__forceinline Vector3 operator*(double v) const
	{
		return Vector3(x * v, y * v, z * v);
	}

	__forceinline Vector3 operator/(double v) const
	{
		return Vector3(x / v, y / v, z / v);
	}

	__forceinline double Distance(Vector3 v)
	{
		return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y) + (v.z - z) * (v.z - z));
	}

	__forceinline double Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	__forceinline double Dot(const Vector3& v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}
};

typedef struct entitys
{
	uintptr_t actor;
	uintptr_t mesh;
	uintptr_t currentweapon;
	uintptr_t playerstate;
}entitys;

std::vector<entitys> entitylist;
struct fquat
{
	double x;
	double y;
	double z;
	double w;
};
struct frotator
{
	double Pitch;
	double Yaw;
	double Roll;
};
struct FTransform
{
	fquat rot;
	Vector3 translation;
	char pad[4];
	Vector3 scale;
	char pad1[4];
	D3DMATRIX ToMatrixWithScale()
	{
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		float x2 = rot.x + rot.x;
		float y2 = rot.y + rot.y;
		float z2 = rot.z + rot.z;

		float xx2 = rot.x * x2;
		float yy2 = rot.y * y2;
		float zz2 = rot.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		float yz2 = rot.y * z2;
		float wx2 = rot.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		float xy2 = rot.x * y2;
		float wz2 = rot.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		float xz2 = rot.x * z2;
		float wy2 = rot.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}
};
struct unrealengine
{
	struct FQ
	{
		double x;
		double y;
		double z;
		double w;
	};

	FQ rotation;
	Vector3 translation;
	Vector3 scale;

	__forceinline auto visibilitycheck(uintptr_t mesh) -> bool
	{
		SPOOF;

		float fLastSubmitTime = read<float>(mesh + offsets->lastsubmit);
		float fLastRenderTimeOnScreen = read<float>(mesh + offsets->lastrender);
		const float tick = 0.01f;
		return fLastRenderTimeOnScreen + tick >= fLastSubmitTime;
		//return fLastRenderTimeOnScreen + 0.06f >= fLastSubmitTime;

	}

	__forceinline auto matrixtos() -> D3DXMATRIX
	{
		SPOOF;
		D3DMATRIX m;
		m._41 = translation.x;
		m._42 = translation.y;
		m._43 = translation.z;

		double x2 = rotation.x + rotation.x;
		double y2 = rotation.y + rotation.y;
		double z2 = rotation.z + rotation.z;

		double xx2 = rotation.x * x2;
		double yy2 = rotation.y * y2;
		double zz2 = rotation.z * z2;
		m._11 = (1.0f - (yy2 + zz2)) * scale.x;
		m._22 = (1.0f - (xx2 + zz2)) * scale.y;
		m._33 = (1.0f - (xx2 + yy2)) * scale.z;

		double yz2 = rotation.y * z2;
		double wx2 = rotation.w * x2;
		m._32 = (yz2 - wx2) * scale.z;
		m._23 = (yz2 + wx2) * scale.y;

		double xy2 = rotation.x * y2;
		double wz2 = rotation.w * z2;
		m._21 = (xy2 - wz2) * scale.y;
		m._12 = (xy2 + wz2) * scale.x;

		double xz2 = rotation.x * z2;
		double wy2 = rotation.w * y2;
		m._31 = (xz2 + wy2) * scale.z;
		m._13 = (xz2 - wy2) * scale.x;

		m._14 = 0.0f;
		m._24 = 0.0f;
		m._34 = 0.0f;
		m._44 = 1.0f;

		return m;
	}

	__forceinline auto matrix(Vector3 rotation, Vector3 origin = Vector3(0, 0, 0)) -> D3DXMATRIX
	{
		SPOOF;
		double radPitch = (rotation.x * double(M_PI) / 180.f);
		double radYaw = (rotation.y * double(M_PI) / 180.f);
		double radRoll = (rotation.z * double(M_PI) / 180.f);

		double SP = sinf(radPitch);
		double CP = cosf(radPitch);
		double SY = sinf(radYaw);
		double CY = cosf(radYaw);
		double SR = sinf(radRoll);
		double CR = cosf(radRoll);

		D3DMATRIX matrix;
		matrix.m[0][0] = CP * CY;
		matrix.m[0][1] = CP * SY;
		matrix.m[0][2] = SP;
		matrix.m[0][3] = 0.f;

		matrix.m[1][0] = SR * SP * CY - CR * SY;
		matrix.m[1][1] = SR * SP * SY + CR * CY;
		matrix.m[1][2] = -SR * CP;
		matrix.m[1][3] = 0.f;

		matrix.m[2][0] = -(CR * SP * CY + SR * SY);
		matrix.m[2][1] = CY * SR - CR * SP * SY;
		matrix.m[2][2] = CR * CP;
		matrix.m[2][3] = 0.f;

		matrix.m[3][0] = origin.x;
		matrix.m[3][1] = origin.y;
		matrix.m[3][2] = origin.z;
		matrix.m[3][3] = 1.f;

		return matrix;
	}

	__forceinline auto matrixm(D3DMATRIX pM1, D3DMATRIX pM2) -> D3DXMATRIX
	{
		SPOOF;
		D3DMATRIX pOut;
		pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
		pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
		pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
		pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
		pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
		pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
		pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
		pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
		pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
		pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
		pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
		pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
		pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
		pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
		pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
		pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

		return pOut;
	}

	DWORD_PTR bonearray;

	FTransform GetBoneIndex(DWORD_PTR mesh, int index)
	{
		SPOOF;
		int isCached = read<int>(mesh + offsets->bonec);
		bonearray = read<DWORD_PTR>(mesh + offsets->bonearray);
		if (bonearray == NULL)
		{
			bonearray = read<DWORD_PTR>(mesh + offsets->bonearray + 0x10);
		}
		return read<FTransform>(bonearray + (index * 0x60));
	}


	Vector3 bonewithrotation(uintptr_t mesh, int bone_id)
	{
		SPOOF;
		uintptr_t bone_array = read<uintptr_t>(mesh + offsets->bonearray);
		if (bone_array == NULL) bone_array = read<uintptr_t>(mesh + offsets->bonearray + 0x10);
		FTransform bone = read<FTransform>(bone_array + (bone_id * 0x60));
		FTransform component_to_world = read<FTransform>(mesh + offsets->comptowrld);
		D3DMATRIX matrix = matrixm(bone.ToMatrixWithScale(), component_to_world.ToMatrixWithScale());
		return Vector3(matrix._41, matrix._42, matrix._43);
	}
	struct cdecrypt
	{
		Vector3 location;
		Vector3 rotation;
		float fov;
	};

	__forceinline auto viewpoint() -> cdecrypt
	{// UPDATED BY H
		SPOOF;
		uintptr_t cachedgworld = read<uintptr_t>(globals->imagebase + offsets->gworld);
		uintptr_t cachedgameinstance = read<uintptr_t>(cachedgworld + offsets->gameinstance);
		uintptr_t cachedlocalplayers = read<uintptr_t>(cachedgameinstance + offsets->localplayers);
		uintptr_t cachedlocalplayer = read<uintptr_t>(cachedlocalplayers);
		uintptr_t cachedplayercontroller = read<uintptr_t>(cachedlocalplayer + offsets->playercontroller);

		cdecrypt camera;

		auto locationp = read<uintptr_t>(cachedgworld + 0x110);
		auto rotationp = read<uintptr_t>(cachedgworld + 0x120);

		struct fnrotation
		{
			double a;
			double b;
			double c;
		}fnrotation;

		fnrotation.a = read<double>(rotationp);
		fnrotation.b = read<double>(rotationp + 0x20);
		fnrotation.c = read<double>(rotationp + 0x1d0);

		camera.location = read<Vector3>(locationp);
		camera.rotation.x = asin(fnrotation.c) * (180.0 / M_PI);
		camera.rotation.y = ((atan2(fnrotation.a * -1, fnrotation.b) * (180.0 / M_PI)) * -1) * -1;
		camera.fov = read<float>((uintptr_t)cachedplayercontroller + 0x394) * 90.f;

		return camera;
	}

	__forceinline auto worldtscreen(Vector3 WorldLocation) -> Vector2
	{
		SPOOF;
		cdecrypt ViewPoint = viewpoint();
		D3DMATRIX MatrixT = matrix(ViewPoint.rotation);
		Vector3 AxisX = Vector3(MatrixT.m[0][0], MatrixT.m[0][1], MatrixT.m[0][2]);
		Vector3 AxisY = Vector3(MatrixT.m[1][0], MatrixT.m[1][1], MatrixT.m[1][2]);
		Vector3 AxisZ = Vector3(MatrixT.m[2][0], MatrixT.m[2][1], MatrixT.m[2][2]);
		Vector3 Delta = WorldLocation - ViewPoint.location;
		Vector3 Transformed = Vector3(Delta.Dot(AxisY), Delta.Dot(AxisZ), Delta.Dot(AxisX));
		if (Transformed.z < 1.f)
		{
			Transformed.z = 1.f;
		}
		//return Vector2((globals->width / 2.0f) + Transformed.x * (((globals->width / 2.0f) / tanf(ViewPoint.fov * (float)M_PI / 360.f))) / Transformed.z, (globals->height / 2.0f) - Transformed.y * (((globals->width / 2.0f) / tanf(ViewPoint.fov * (float)M_PI / 360.f))) / Transformed.z, 0);
		return Vector2((globals->width / 2.0f) + Transformed.x * (((globals->width / 2.0f) / tanf(ViewPoint.fov * (float)M_PI / 360.f))) / Transformed.z, (globals->height / 2.0f) - Transformed.y * (((globals->width / 2.0f) / tanf(ViewPoint.fov * (float)M_PI / 360.f))) / Transformed.z);

	}
	__forceinline auto vecvalid(Vector3 vec3) -> bool
	{
		return !(vec3.x == 0 && vec3.y == 0 && vec3.z == 0);
	}

	__forceinline auto cdistance(double x1, double y1, double x2, double y2) -> double
	{
		return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
	}
};

std::unique_ptr<unrealengine> uengine = std::make_unique<unrealengine>();

#endif