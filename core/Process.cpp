#include "Process.h"
#include "Util.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <unordered_set>
#include <unordered_map>

#include <glm/gtc/matrix_inverse.hpp>
#include <glm/trigonometric.hpp>
#include "Format.h"
#include "ImageProcessing/Image.h"
#include "DX/DirectXRender.h"

glm::vec4 Helper_IdentRowSafe(uint32_t loopCount)
{
	if (loopCount < 4)
	{
		return glm::mat4(1.0)[loopCount];
	}
	else
	{
		return glm::vec4(0);
	}
}

void ApplySkin(
	std::vector<FChimeraVertex>& verts,
	std::vector<glm::vec4>& skinningMatrix,
	FBDOShaderBindings& vtxBindings,
	DrawBufferInformation& dbi
)
{
	// Just for this function
	using namespace glm;

	// First do a small check
	//if (verts.size() > vtxBindings.TexCoord1.size()) { return; }

	//if (verts.size() > vtxBindings.TexCoord1.size()) { return; }
	if (vtxBindings.cb0.size() < 5) { return; }

	// Crush the Mat4x4 to ID
	vtxBindings.cb0[0] = Helper_IdentRowSafe(0);
	vtxBindings.cb0[1] = Helper_IdentRowSafe(1);
	vtxBindings.cb0[2] = Helper_IdentRowSafe(2);
	vtxBindings.cb0[3] = Helper_IdentRowSafe(3);
	vtxBindings.cb0[4] = vec4(0, 0, 0, 0);

#pragma omp parallel for
	for (int64_t i = 0; i < verts.size(); ++i)
	{
		auto cVert = verts[i];
		auto vi = vtxBindings.Offset / 112;// cVert.indexBufferLocale;// i + dbi.BaseVertex;

		auto t0 = skinningMatrix.data();
		auto cb0 = vtxBindings.cb0.data();
		auto cb2 = vtxBindings.cb2.data();
		auto cb3 = vtxBindings.cb3.data();


		//Wif(vi)

		// Registers
		vec4 o0 = vec4(0);
		vec4 r0 = vec4(0);
		vec4 r1 = vec4(0);
		vec4 r2 = vec4(0);
		vec4 r3 = vec4(0);
		vec4 r4 = vec4(0);
		vec4 r5 = vec4(0);
		vec4 r6 = vec4(0);
		vec4 r7 = vec4(0);
		vec4 r8 = vec4(0);
		vec4 r9 = vec4(0);
		vec4 r10 = vec4(0);
		vec4 r11 = vec4(0);
		vec4 r12 = vec4(0);
		vec4 r13 = vec4(0);
		vec4 r14 = vec4(0);
		vec4 r15 = vec4(0);

		vec4 v0 = vec4(cVert.Position, 1.0f);
		vec4 v1 = cVert.Tangents;
		vec2 v2 = vec2(cVert.TexCoords);
		vec4 v3 = cVert.Colour;
		auto v4 = cVert.BoneIndices;
		vec4 v5 = cVert.BlendWeights;
		vec4 v6 = vtxBindings.TexCoord1[vi];
		vec4 v7 = vtxBindings.TexCoord2[vi];
		vec4 v8 = vtxBindings.TexCoord3[vi];
		vec4 v9 = vtxBindings.TexCoord4[vi];
		vec4 v10 = vtxBindings.TexCoord5[vi];
		vec4 v11 = vtxBindings.TexCoord6[vi];
		vec4 v12 = vtxBindings.TexCoord7[vi];



		uint32_t temp_0 = 0xFFFFFFFF;
		uint32_t temp_1 = 0x0;
		uint32_t temp_2 = 0x0;
		int32_t temp_4 = 0x0;
		int32_t temp_5 = 0x0;
		int32_t temp_6 = 0x0;
		int32_t temp_7 = 0x0;
		uint32_t temp_8 = 0x0;
		uint32_t temp_9 = 0x0;
		uint32_t temp_10 = 0x0;
		uint32_t temp_11 = 0x0;
		float temp_12 = 0x0;
		float temp_13 = 0x0;
		float temp_14 = 0x0;
		float temp_15 = 0x0;
		r0.xyzw = vec4(v1.xyzw) * vec4(6.283185f, 6.283185f, 6.283185f, 6.283185f);
		r0.xyzw = vec4(r0.xyzw) + vec4(-3.141593f, -3.141593f, -3.141593f, -3.141593f);
		r1.xyzw = sin(vec4(r0.xyzw));
		r2.xyzw = cos(vec4(r0.xyzw));
		r3.xy = abs(vec2(r1.yw)) * vec2(r2.xz);
		r1.xy = vec2(r1.xz) * abs(vec2(r1.yw));
		r1.z = r2.y;
		r1.w = r3.x;
		r3.z = r2.w;
		r3.w = r1.y;
		r0.xyz = vec3(r1.xzw) * vec3(r3.zyw);
		r2.xyz = vec3(r3.wzy) * vec3(r1.zwx);
		r0.xyz = vec3(r0.xyz) + -vec3(r2.xyz);
		{
			temp_12 = 0.000000f < r0.w ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r0.w _CONVERT(0.000000) r0.w
			r0.w = temp_12;
		}
		{
			temp_12 = (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<float*>(&r0.x)) : -(*reinterpret_cast<float*>(&r0.x)); // MOVC r0.xyz r0.xyzx -r0.xyzx
			temp_13 = (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<float*>(&r0.y)) : -(*reinterpret_cast<float*>(&r0.y)); // MOVC r0.xyz r0.xyzx -r0.xyzx
			temp_14 = (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<float*>(&r0.z)) : -(*reinterpret_cast<float*>(&r0.z)); // MOVC r0.xyz r0.xyzx -r0.xyzx
			r0.x = temp_12;
			r0.y = temp_13;
			r0.z = temp_14;
		}
		temp_2 = int32_t(v9.w); //FTOI softcast
		r0.w = (*reinterpret_cast<float*>(&temp_2)); // FTOI hardcast
		r2.xyz = vec3(0, 0, 0);// vec3(v10.xyz) + -vec3(cb0[4].xyz);
		//r2.xyz = vec3(v10.xyz) + -vec3(cb0[4].xyz);
		temp_2 = int32_t(v12.x); //FTOI softcast
		r1.y = (*reinterpret_cast<float*>(&temp_2)); // FTOI hardcast
		{
			temp_4 = (*reinterpret_cast<int32_t*>(&r1.y)) < 0 ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // ILT r2.w r1.y _CONVERT(0)
			r2.w = (*reinterpret_cast<float*>(&temp_4));
		}
		{
			temp_4 = 1 > (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // IGE r3.x _CONVERT(1) r0.w
			r3.x = (*reinterpret_cast<float*>(&temp_4));
		}
		{
			temp_4 = (*reinterpret_cast<int32_t*>(&r2.w)) & (*reinterpret_cast<int32_t*>(&r3.x)); // AND r2.w r2.w r3.x
			r2.w = (*reinterpret_cast<float*>(&temp_4));
		}
		{
			temp_4 = 1 < (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // ILT r4.x _CONVERT(1) r0.w
			r4.x = (*reinterpret_cast<float*>(&temp_4));
		}
		{
			temp_4 = (*reinterpret_cast<int32_t*>(&cb3[5].w)) != 0 ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // INE r4.y cb3[5].w _CONVERT(0)
			r4.y = (*reinterpret_cast<float*>(&temp_4));
		}
		{
			temp_4 = -1 == (*reinterpret_cast<int32_t*>(&r4.y)) ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // IEQ r4.y _CONVERT(-1) r4.y
			r4.y = (*reinterpret_cast<float*>(&temp_4));
		}
		{
			temp_4 = 1 == (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // IEQ r0.w _CONVERT(1) r0.w
			r0.w = (*reinterpret_cast<float*>(&temp_4));
		}
		{
			temp_4 = (*reinterpret_cast<int32_t*>(&r0.w)) & (*reinterpret_cast<int32_t*>(&r4.y)); // AND r0.w r0.w r4.y
			r0.w = (*reinterpret_cast<float*>(&temp_4));
		}
		r4.y = v5.y + v5.x;
		r5.z = -r4.y + 1.000000f;
		r5.x = 3.f;
		r6.x = 4.f;
		r6.z = v5.z;
		{
			temp_12 = (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<float*>(&r5.x)) : (*reinterpret_cast<float*>(&r6.x)); // MOVC r5.xz r5.xxzx r6.xxzx
			temp_13 = (*reinterpret_cast<int32_t*>(&r0.w)) ? (*reinterpret_cast<float*>(&r5.z)) : (*reinterpret_cast<float*>(&r6.z)); // MOVC r5.xz r5.xxzx r6.xxzx
			r5.x = temp_12;
			r5.z = temp_13;
		}
		r6.xy = vec2(1.f, 1.000000f);
		r6.z = v5.z;
		r5.y = v5.x;
		{
			temp_12 = (*reinterpret_cast<int32_t*>(&r4.x)) ? (*reinterpret_cast<float*>(&r6.x)) : (*reinterpret_cast<float*>(&r5.x)); // MOVC r4.xzw r6.xxyz r5.xxyz
			temp_13 = (*reinterpret_cast<int32_t*>(&r4.x)) ? (*reinterpret_cast<float*>(&r6.y)) : (*reinterpret_cast<float*>(&r5.y)); // MOVC r4.xzw r6.xxyz r5.xxyz
			temp_14 = (*reinterpret_cast<int32_t*>(&r4.x)) ? (*reinterpret_cast<float*>(&r6.z)) : (*reinterpret_cast<float*>(&r5.z)); // MOVC r4.xzw r6.xxyz r5.xxyz
			r4.x = temp_12;
			r4.z = temp_13;
			r4.w = temp_14;
		}
		r5.xz = vec2(r4.zw);
		r5.yw = vec2(v5.yw);
		r6.xyz = vec3(0.f, 0.f, 0.f);
		r7.xyz = vec3(0.f, 0.f, 0.f);
		r8.xyz = vec3(0.f, 0.f, 0.f);
		r9.xyz = vec3(0.f, 0.f, 0.f);
		r4.z = 0.f;
		while (true) {
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r4.z)) < (*reinterpret_cast<int32_t*>(&r4.x)) ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // ILT r0.w r4.z r4.x
				r0.w = (*reinterpret_cast<float*>(&temp_4));
			}
			//r6.w = dot(vec4(r5.xyzw), vec4(icb[r4.z + 0].xyzw));
			r6.w = dot(vec4(r5.xyzw), vec4(Helper_IdentRowSafe((*reinterpret_cast<int32_t*>(&r4.z))).xyzw));
			{
				temp_12 = 0.000000f < r6.w ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r7.w _CONVERT(0.000000) r6.w
				r7.w = temp_12;
			}
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r0.w)) & (*reinterpret_cast<int32_t*>(&r7.w)); // AND r0.w r0.w r7.w
				r0.w = (*reinterpret_cast<float*>(&temp_4));
			}
			if ((*reinterpret_cast<int32_t*>(&r0.w)) == 0) { break; }
			temp_2 = -1 * (*reinterpret_cast<int32_t*>(&r4.z));
			r0.w = (*reinterpret_cast<float*>(&temp_2));
			{
				temp_8 = (*reinterpret_cast<uint32_t*>(&r4.z)) < 1 ? (*reinterpret_cast<uint32_t*>(&temp_0)) : (*reinterpret_cast<uint32_t*>(&temp_1)); // ULT r10.xyz r4.zzzz _CONVERT(1, 2, 3, 0)
				temp_9 = (*reinterpret_cast<uint32_t*>(&r4.z)) < 2 ? (*reinterpret_cast<uint32_t*>(&temp_0)) : (*reinterpret_cast<uint32_t*>(&temp_1)); // ULT r10.xyz r4.zzzz _CONVERT(1, 2, 3, 0)
				temp_10 = (*reinterpret_cast<uint32_t*>(&r4.z)) < 3 ? (*reinterpret_cast<uint32_t*>(&temp_0)) : (*reinterpret_cast<uint32_t*>(&temp_1)); // ULT r10.xyz r4.zzzz _CONVERT(1, 2, 3, 0)
				r10.x = (*reinterpret_cast<float*>(&temp_8));
				r10.y = (*reinterpret_cast<float*>(&temp_9));
				r10.z = (*reinterpret_cast<float*>(&temp_10));
			}
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r0.w)) & (*reinterpret_cast<int32_t*>(&r10.y)); // AND r11.y r0.w r10.y
				r11.y = (*reinterpret_cast<float*>(&temp_4));
			}
			temp_4 = (*reinterpret_cast<int32_t*>(&r4.z)) + 1;
			temp_5 = (*reinterpret_cast<int32_t*>(&r4.z)) - 3;
			r4.z = (*reinterpret_cast<float*>(&temp_4));
			r4.w = (*reinterpret_cast<float*>(&temp_5));
			{
				temp_12 = (*reinterpret_cast<int32_t*>(&r10.y)) ? 0 : (*reinterpret_cast<float*>(&r4.w)); // MOVC r11.z _CONVERT(0) r4.w
				r11.z = temp_12;
			}
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r10.z)) == 0 ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // IEQ r11.w r10.z _CONVERT(0)
				r11.w = (*reinterpret_cast<float*>(&temp_4));
			}
			r11.x = r10.x;
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r11.x)) & (*reinterpret_cast<int16_t*>(&v4.x)); // AND r10.xyzw r11.xyzw v4.xyzw
				temp_5 = (*reinterpret_cast<int32_t*>(&r11.y)) & (*reinterpret_cast<int16_t*>(&v4.y)); // AND r10.xyzw r11.xyzw v4.xyzw
				temp_6 = (*reinterpret_cast<int32_t*>(&r11.z)) & (*reinterpret_cast<int16_t*>(&v4.z)); // AND r10.xyzw r11.xyzw v4.xyzw
				temp_7 = (*reinterpret_cast<int32_t*>(&r11.w)) & (*reinterpret_cast<int16_t*>(&v4.w)); // AND r10.xyzw r11.xyzw v4.xyzw
				r10.x = (*reinterpret_cast<float*>(&temp_4));
				r10.y = (*reinterpret_cast<float*>(&temp_5));
				r10.z = (*reinterpret_cast<float*>(&temp_6));
				r10.w = (*reinterpret_cast<float*>(&temp_7));
			}
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r10.y)) | (*reinterpret_cast<int32_t*>(&r10.x)); // OR r10.xy r10.ywyy r10.xzxx
				temp_5 = (*reinterpret_cast<int32_t*>(&r10.w)) | (*reinterpret_cast<int32_t*>(&r10.z)); // OR r10.xy r10.ywyy r10.xzxx
				r10.x = (*reinterpret_cast<float*>(&temp_4));
				r10.y = (*reinterpret_cast<float*>(&temp_5));
			}
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r10.y)) | (*reinterpret_cast<int32_t*>(&r10.x)); // OR r0.w r10.y r10.x
				r0.w = (*reinterpret_cast<float*>(&temp_4));
			}
			temp_2 = (*reinterpret_cast<int32_t*>(&r0.w)) << 2;
			r0.w = (*reinterpret_cast<float*>(&temp_2));
			temp_2 = (*reinterpret_cast<int32_t*>(&r0.w));
			r0.w = float(temp_2); // UTOF softcast
			r0.w = r0.w + v6.z;
			temp_2 = uint32_t(r0.w); //FTOU softcast
			r4.w = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
			temp_2 = (*reinterpret_cast<int32_t*>(&r4.w));
			r10.x = t0[temp_2].x;
			r10.y = t0[temp_2].y;
			r10.z = t0[temp_2].z;
			r10.xyz = vec3(r6.www) * vec3(r10.xyz);
			r6.xyz = vec3(r6.xyz) + vec3(r10.xyz);
			r10.xyz = vec3(r0.www) + vec3(1.000000f, 2.000000f, 3.000000f);
			temp_2 = uint32_t(r10.x); //FTOU softcast
			r10.x = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
			temp_2 = uint32_t(r10.y); //FTOU softcast
			r10.y = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
			temp_2 = uint32_t(r10.z); //FTOU softcast
			r10.z = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
			temp_2 = (*reinterpret_cast<int32_t*>(&r10.x));
			r11.x = t0[temp_2].x;
			r11.y = t0[temp_2].y;
			r11.z = t0[temp_2].z;
			r11.xyz = vec3(r6.www) * vec3(r11.xyz);
			r7.xyz = vec3(r7.xyz) + vec3(r11.xyz);
			temp_2 = (*reinterpret_cast<int32_t*>(&r10.y));
			r10.x = t0[temp_2].x;
			r10.y = t0[temp_2].y;
			r10.w = t0[temp_2].z;
			r10.xyw = vec3(r6.www) * vec3(r10.xyw);
			r8.xyz = vec3(r8.xyz) + vec3(r10.xyw);
			temp_2 = (*reinterpret_cast<int32_t*>(&r10.z));
			r10.x = t0[temp_2].x;
			r10.y = t0[temp_2].y;
			r10.z = t0[temp_2].z;
			r10.xyz = vec3(r6.www) * vec3(r10.xyz);
			r9.xyz = vec3(r9.xyz) + vec3(r10.xyz);
		}
		{
			temp_12 = 0.020000f < v3.w ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r0.w _CONVERT(0.020000) v3.w
			r0.w = temp_12;
		}
		{
			temp_4 = (*reinterpret_cast<int32_t*>(&r0.w)) & (*reinterpret_cast<int32_t*>(&r2.w)); // AND r0.w r0.w r2.w
			r0.w = (*reinterpret_cast<float*>(&temp_4));
		}
		//if ((*reinterpret_cast<int32_t*>(&r0.w)) != 0) {
		if (false){
			{
				temp_4 = max(-1 * (*reinterpret_cast<int32_t*>(&r1.y)), (*reinterpret_cast<int32_t*>(&r1.y))); // IMAX r0.w -r1.y r1.y
				r0.w = (*reinterpret_cast<float*>(&temp_4));
			}
			r4.xzw = vec3(0.f, 0.f, 0.f);
			r5.xyz = vec3(0.f, 0.f, 0.f);
			r10.xyz = vec3(0.f, 0.f, 0.f);
			r11.xyz = vec3(0.f, 0.f, 0.f);
			r12.x = 0.f;
			while (true) {
				{
					temp_4 = (*reinterpret_cast<int32_t*>(&r12.x)) < 4 ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // ILT r1.y r12.x _CONVERT(4)
					r1.y = (*reinterpret_cast<float*>(&temp_4));
				}
				//r2.w = dot(vec4(v5.xyzw), vec4(icb[r12.x + 0].xyzw));
				r2.w = dot(vec4(v5.xyzw), vec4(Helper_IdentRowSafe((*reinterpret_cast<int32_t*>(&r4.z))).xyzw));
				{
					temp_12 = 0.000000f < r2.w ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r5.w _CONVERT(0.000000) r2.w
					r5.w = temp_12;
				}
				{
					temp_4 = (*reinterpret_cast<int32_t*>(&r1.y)) & (*reinterpret_cast<int32_t*>(&r5.w)); // AND r1.y r1.y r5.w
					r1.y = (*reinterpret_cast<float*>(&temp_4));
				}
				if ((*reinterpret_cast<int32_t*>(&r1.y)) == 0) { break; }
				temp_2 = -1 * (*reinterpret_cast<int32_t*>(&r12.x));
				r1.y = (*reinterpret_cast<float*>(&temp_2));
				{
					temp_8 = (*reinterpret_cast<uint32_t*>(&r12.x)) < 1 ? (*reinterpret_cast<uint32_t*>(&temp_0)) : (*reinterpret_cast<uint32_t*>(&temp_1)); // ULT r13.xyz r12.xxxx _CONVERT(1, 2, 3, 0)
					temp_9 = (*reinterpret_cast<uint32_t*>(&r12.x)) < 2 ? (*reinterpret_cast<uint32_t*>(&temp_0)) : (*reinterpret_cast<uint32_t*>(&temp_1)); // ULT r13.xyz r12.xxxx _CONVERT(1, 2, 3, 0)
					temp_10 = (*reinterpret_cast<uint32_t*>(&r12.x)) < 3 ? (*reinterpret_cast<uint32_t*>(&temp_0)) : (*reinterpret_cast<uint32_t*>(&temp_1)); // ULT r13.xyz r12.xxxx _CONVERT(1, 2, 3, 0)
					r13.x = (*reinterpret_cast<float*>(&temp_8));
					r13.y = (*reinterpret_cast<float*>(&temp_9));
					r13.z = (*reinterpret_cast<float*>(&temp_10));
				}
				{
					temp_4 = (*reinterpret_cast<int32_t*>(&r1.y)) & (*reinterpret_cast<int32_t*>(&r13.y)); // AND r14.y r1.y r13.y
					r14.y = (*reinterpret_cast<float*>(&temp_4));
				}
				temp_4 = (*reinterpret_cast<int32_t*>(&r12.x)) + 1;
				temp_5 = (*reinterpret_cast<int32_t*>(&r12.x)) - 3;
				r12.x = (*reinterpret_cast<float*>(&temp_4));
				r12.y = (*reinterpret_cast<float*>(&temp_5));
				{
					temp_12 = (*reinterpret_cast<int32_t*>(&r13.y)) ? 0 : (*reinterpret_cast<float*>(&r12.y)); // MOVC r14.z _CONVERT(0) r12.y
					r14.z = temp_12;
				}
				{
					temp_4 = (*reinterpret_cast<int32_t*>(&r13.z)) == 0 ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // IEQ r14.w r13.z _CONVERT(0)
					r14.w = (*reinterpret_cast<float*>(&temp_4));
				}
				r14.x = r13.x;
				{
					temp_4 = (*reinterpret_cast<int32_t*>(&r14.x)) & (*reinterpret_cast<int16_t*>(&v4.x)); // AND r13.xyzw r14.xyzw v4.xyzw
					temp_5 = (*reinterpret_cast<int32_t*>(&r14.y)) & (*reinterpret_cast<int16_t*>(&v4.y)); // AND r13.xyzw r14.xyzw v4.xyzw
					temp_6 = (*reinterpret_cast<int32_t*>(&r14.z)) & (*reinterpret_cast<int16_t*>(&v4.z)); // AND r13.xyzw r14.xyzw v4.xyzw
					temp_7 = (*reinterpret_cast<int32_t*>(&r14.w)) & (*reinterpret_cast<int16_t*>(&v4.w)); // AND r13.xyzw r14.xyzw v4.xyzw
					r13.x = (*reinterpret_cast<float*>(&temp_4));
					r13.y = (*reinterpret_cast<float*>(&temp_5));
					r13.z = (*reinterpret_cast<float*>(&temp_6));
					r13.w = (*reinterpret_cast<float*>(&temp_7));
				}
				{
					temp_4 = (*reinterpret_cast<int32_t*>(&r13.y)) | (*reinterpret_cast<int32_t*>(&r13.x)); // OR r12.yz r13.yywy r13.xxzx
					temp_5 = (*reinterpret_cast<int32_t*>(&r13.w)) | (*reinterpret_cast<int32_t*>(&r13.z)); // OR r12.yz r13.yywy r13.xxzx
					r12.y = (*reinterpret_cast<float*>(&temp_4));
					r12.z = (*reinterpret_cast<float*>(&temp_5));
				}
				{
					temp_4 = (*reinterpret_cast<int32_t*>(&r12.z)) | (*reinterpret_cast<int32_t*>(&r12.y)); // OR r1.y r12.z r12.y
					r1.y = (*reinterpret_cast<float*>(&temp_4));
				}
				temp_4 = (*reinterpret_cast<int32_t*>(&r0.w)) + (*reinterpret_cast<int32_t*>(&r1.y));
				r1.y = (*reinterpret_cast<float*>(&temp_4));
				temp_2 = (*reinterpret_cast<int32_t*>(&r1.y)) << 2;
				r1.y = (*reinterpret_cast<float*>(&temp_2));
				temp_2 = (*reinterpret_cast<int32_t*>(&r1.y));
				r1.y = float(temp_2); // UTOF softcast
				r1.y = r1.y + v6.z;
				temp_2 = uint32_t(r1.y); //FTOU softcast
				r5.w = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
				temp_2 = (*reinterpret_cast<int32_t*>(&r5.w));
				r12.y = t0[temp_2].x;
				r12.z = t0[temp_2].y;
				r12.w = t0[temp_2].z;
				r12.yzw = vec3(r2.www) * vec3(r12.yzw);
				r4.xzw = vec3(r4.xzw) + vec3(r12.yzw);
				r12.yzw = vec3(r1.yyy) + vec3(1.000000f, 2.000000f, 3.000000f);
				temp_2 = uint32_t(r12.y); //FTOU softcast
				r12.y = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
				temp_2 = uint32_t(r12.z); //FTOU softcast
				r12.z = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
				temp_2 = uint32_t(r12.w); //FTOU softcast
				r12.w = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
				temp_2 = (*reinterpret_cast<int32_t*>(&r12.y));
				r13.x = t0[temp_2].x;
				r13.y = t0[temp_2].y;
				r13.z = t0[temp_2].z;
				r13.xyz = vec3(r2.www) * vec3(r13.xyz);
				r5.xyz = vec3(r5.xyz) + vec3(r13.xyz);
				temp_2 = (*reinterpret_cast<int32_t*>(&r12.z));
				r13.x = t0[temp_2].x;
				r13.y = t0[temp_2].y;
				r13.z = t0[temp_2].z;
				r13.xyz = vec3(r2.www) * vec3(r13.xyz);
				r10.xyz = vec3(r10.xyz) + vec3(r13.xyz);
				temp_2 = (*reinterpret_cast<int32_t*>(&r12.w));
				r12.y = t0[temp_2].x;
				r12.z = t0[temp_2].y;
				r12.w = t0[temp_2].z;
				r12.yzw = vec3(r2.www) * vec3(r12.yzw);
				r11.xyz = vec3(r11.xyz) + vec3(r12.yzw);
			}
			r0.w = v3.w * v3.w;
			r0.w = r0.w * r0.w;
			r4.xzw = -vec3(r6.xyz) + vec3(r4.xzw);
			r5.xyz = -vec3(r7.xyz) + vec3(r5.xyz);
			r10.xyz = -vec3(r8.xyz) + vec3(r10.xyz);
			r11.xyz = -vec3(r9.xyz) + vec3(r11.xyz);
			r4.xzw = vec3(r0.www) * vec3(r4.xzw);
			r5.xyz = vec3(r0.www) * vec3(r5.xyz);
			r10.xyz = vec3(r0.www) * vec3(r10.xyz);
			r11.xyz = vec3(r0.www) * vec3(r11.xyz);
			r6.xyz = vec3(r4.xzw) + vec3(r6.xyz);
			r7.xyz = vec3(r5.xyz) + vec3(r7.xyz);
			r8.xyz = vec3(r8.xyz) + vec3(r10.xyz);
			r9.xyz = vec3(r9.xyz) + vec3(r11.xyz);
		}
		r4.xzw = vec3(r6.xyz) * vec3(v0.xxx);
		r5.xyz = vec3(r7.xyz) * vec3(v0.yyy);
		r4.xzw = vec3(r4.xzw) + vec3(r5.xyz);
		r5.xyz = vec3(r8.xyz) * vec3(v0.zzz);
		r4.xzw = vec3(r4.xzw) + vec3(r5.xyz);
		r5.xyz = vec3(r9.xyz) + vec3(r4.xzw);
		r0.w = r4.y + v5.z;
		r5.w = r0.w + v5.w;
		r4.xyzw = vec4(r5.xyzw) / vec4(r5.wwww);
		r5.x = v7.x;
		r5.y = v8.x;
		r5.z = v9.x;
		r9.x = dot(vec3(r6.xyz), vec3(r5.xyz));
		r10.x = v7.y;
		r10.y = v8.y;
		r10.z = v9.y;
		r11.x = dot(vec3(r6.xyz), vec3(r10.xyz));
		r12.x = v7.z;
		r12.y = v8.z;
		r12.z = v9.z;
		r6.x = dot(vec3(r6.xyz), vec3(r12.xyz));
		r9.y = dot(vec3(r7.xyz), vec3(r5.xyz));
		r11.y = dot(vec3(r7.xyz), vec3(r10.xyz));
		r6.y = dot(vec3(r7.xyz), vec3(r12.xyz));
		r9.z = dot(vec3(r8.xyz), vec3(r5.xyz));
		r11.z = dot(vec3(r8.xyz), vec3(r10.xyz));
		r6.z = dot(vec3(r8.xyz), vec3(r12.xyz));
		r7.x = dot(vec3(r0.xyz), vec3(r9.xyz));
		r7.y = dot(vec3(r0.xyz), vec3(r11.xyz));
		r7.z = dot(vec3(r0.xyz), vec3(r6.xyz));
		r0.w = dot(vec3(r7.xyz), vec3(r7.xyz));
		r0.w = 1.f / sqrt(r0.w);
		r7.xyz = vec3(r0.www) * vec3(r7.xyz);
		if ((*reinterpret_cast<int32_t*>(&r3.x)) != 0) {
			r8.x = dot(vec3(r1.wxz), vec3(r9.xyz));
			r8.y = dot(vec3(r1.wxz), vec3(r11.xyz));
			r8.z = dot(vec3(r1.wxz), vec3(r6.xyz));
			r1.x = dot(vec3(r3.ywz), vec3(r9.xyz));
			r1.y = dot(vec3(r3.ywz), vec3(r11.xyz));
			r1.z = dot(vec3(r3.ywz), vec3(r6.xyz));
			r0.w = dot(vec3(r8.xyz), vec3(r8.xyz));
			r0.w = 1.f / sqrt(r0.w);
			r3.xyz = vec3(r0.www) * vec3(r8.xyz);
			r0.w = dot(vec3(r1.xyz), vec3(r1.xyz));
			r0.w = 1.f / sqrt(r0.w);
			r1.xyz = vec3(r0.www) * vec3(r1.xyz);
		}
		else {
			r3.xyz = vec3(0.f, 0.f, 0.f);
			r1.xyz = vec3(0.f, 0.f, 0.f);
		}
		{
			temp_12 = v11.y > 0.000000f ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // FGE r0.w v11.y _CONVERT(0.000000)
			r0.w = temp_12;
		}
		if ((*reinterpret_cast<int32_t*>(&r0.w)) != 0) {
			r6.xy = vec2(v2.yy) * vec2(cb2[1].xy);
			r6.xy = vec2(v2.xx) * vec2(cb2[0].xy) + vec2(r6.xy);
			r6.xy = vec2(r6.xy) + vec2(cb2[2].xy);
		}
		else {
			r6.xy = vec2(v2.xy);
		}
		r5.w = r2.x;
		r5.x = dot(vec4(r4.xyzw), vec4(r5.xyzw));
		r10.w = r2.y;
		r5.y = dot(vec4(r4.xyzw), vec4(r10.xyzw));
		r12.w = r2.z;
		r5.z = dot(vec4(r4.xyzw), vec4(r12.xyzw));
		r8.xyz = vec3(r5.xyz) + vec3(cb0[4].xyz);
		{
			temp_12 = 0.000000f < v7.w ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r0.w _CONVERT(0.000000) v7.w
			r0.w = temp_12;
		}
		if ((*reinterpret_cast<int32_t*>(&r0.w)) != 0) {
			temp_2 = int32_t(v10.w); //FTOI softcast
			r0.w = (*reinterpret_cast<float*>(&temp_2)); // FTOI hardcast
			if ((*reinterpret_cast<int32_t*>(&r0.w)) == 0) {
				r0.w = v7.w * v7.w;
				r0.w = r0.w * r0.w;
				//o9.w = min(r0.w, 1.000000f);
				//o9.xyz = vec3(0.500000f, 0.500000f, 0.500000f);
				r9.x = r4.y;
			}
			else {
				r0.w = v6.x + 1.000000f;
				temp_2 = uint32_t(r0.w); //FTOU softcast
				r1.w = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
				temp_2 = (*reinterpret_cast<int32_t*>(&r1.w));
				r10.x = t0[temp_2].x;
				r10.y = t0[temp_2].y;
				r10.z = t0[temp_2].z;
				r0.w = r0.w + 1.000000f;
				temp_2 = uint32_t(r0.w); //FTOU softcast
				r0.w = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
				temp_2 = (*reinterpret_cast<int32_t*>(&r0.w));
				r11.x = t0[temp_2].x;
				r11.y = t0[temp_2].y;
				r11.z = t0[temp_2].z;
				r11.xyz = vec3(r8.xyz) + -vec3(r11.xyz);
				{
					temp_12 = 0.900000f < r10.z ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r0.w _CONVERT(0.900000) r10.z
					r0.w = temp_12;
				}
				r11.w = (*reinterpret_cast<int32_t*>(&r0.w)) ? 0.f : r11.z;
				r0.w = dot(vec3(r11.xyw), vec3(r11.xyw));
				r0.w = sqrt(r0.w);
				r0.w = min(1.f, max(0.f, r0.w / 260.000000f));
				r0.w = -r0.w + 1.000000f;
				r0.w = r0.w * r0.w;
				r0.w = r0.w * 2.000000f;
				r0.w = min(r0.w, 1.000000f);
				r1.w = dot(vec3(r10.xyz), vec3(r10.xyz));
				r1.w = 1.f / sqrt(r1.w);
				r10.xyz = vec3(r1.www) * vec3(r10.xyz);
				r1.w = dot(vec3(r0.xyz), vec3(r10.xyz));
				r1.w = r1.w * 0.500000f;
				r1.w = min(1.f, max(0.f, r1.w + 0.500000f));
				r1.w = r1.w * r1.w;
				r1.w = r1.w * 2.000000f;
				{
					temp_12 = r10.z < 0.900000f ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r2.w r10.z _CONVERT(0.900000)
					r2.w = temp_12;
				}
				r11.xyz = vec3(r10.xyz) * vec3(r1.www);
				r11.xyz = vec3(r0.www) * vec3(r11.xyz);
				r11.xyz = vec3(r11.xyz) * vec3(50.000000f, 50.000000f, 50.000000f);
				r3.w = log(v7.w);
				r3.w = r3.w * 10.000000f;
				r3.w = exp(r3.w);
				r11.xyz = vec3(r3.www) * vec3(r11.xyz);
				r11.xyz = vec3(r4.xyz) + vec3(r11.xyz);
				r0.xyz = vec3(r0.xyz) + vec3(r10.xyz);
				r0.xyz = vec3(r0.xyz) * vec3(r1.www);
				r0.xyz = vec3(r0.www) * vec3(r0.xyz);
				r0.xyz = vec3(r0.xyz) * vec3(25.000000f, 25.000000f, 25.000000f);
				r0.xyz = vec3(r3.www) * vec3(r0.xyz);
				r0.xyz = vec3(r0.xyz) + vec3(r4.xyz);
				r9.x = (*reinterpret_cast<int32_t*>(&r2.w)) ? r11.y : r0.y;
				r9.y = (*reinterpret_cast<int32_t*>(&r2.w)) ? r11.x : r0.x;
				r9.z = (*reinterpret_cast<int32_t*>(&r2.w)) ? r11.z : r0.z;
				r0.x = r1.w * v7.w;
				r0.y = r0.x * r0.x;
				r0.y = r0.y * r0.y;
				r0.x = r0.y * r0.x;
				//o9.w = min(r0.x, 1.000000f);
				//o9.xyz = vec3(0.392157f, 0.627451f, 0.941176f);
				r4.xz = vec2(r9.yz);
			}
		}
		else {
			r0.xy = vec2(v6.xx) + vec2(2.000000f, 1.000000f);
			temp_2 = uint32_t(r0.x); //FTOU softcast
			r0.x = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
			temp_2 = uint32_t(r0.y); //FTOU softcast
			r0.y = (*reinterpret_cast<float*>(&temp_2)); // FTOU hardcast
			temp_2 = (*reinterpret_cast<int32_t*>(&r0.x));
			r10.x = t0[temp_2].x;
			r10.y = t0[temp_2].y;
			r10.z = t0[temp_2].z;
			r10.w = t0[temp_2].w;
			r0.x = dot(vec3(r5.xyz), vec3(r5.xyz));
			r0.x = 1.f / sqrt(r0.x);
			r0.xzw = vec3(r0.xxx) * vec3(r5.xyz);
			r0.x = dot(vec3(r7.xyz), -vec3(r0.xzw));
			r0.z = -r0.x * 0.500000f + 1.500000f;
			r5.w = r0.z * -r10.w;
			r0.x = min(1.f, max(0.f, -r0.x + 1.000000f));
			r10.w = r0.x * r10.w;
			temp_2 = (*reinterpret_cast<int32_t*>(&r0.y));
			r11.x = t0[temp_2].x;
			r11.y = t0[temp_2].y;
			r11.z = t0[temp_2].z;
			r11.w = t0[temp_2].w;
			r0.w = r0.x * abs(r11.w);
			{
				temp_4 = v7.w == -1.000000f ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r12.xyzw v7.wwww _CONVERT(-1.000000, -2.000000, -3.000000, -4.000000)
				temp_5 = v7.w == -2.000000f ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r12.xyzw v7.wwww _CONVERT(-1.000000, -2.000000, -3.000000, -4.000000)
				temp_6 = v7.w == -3.000000f ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r12.xyzw v7.wwww _CONVERT(-1.000000, -2.000000, -3.000000, -4.000000)
				temp_7 = v7.w == -4.000000f ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r12.xyzw v7.wwww _CONVERT(-1.000000, -2.000000, -3.000000, -4.000000)
				r12.x = (*reinterpret_cast<float*>(&temp_4));
				r12.y = (*reinterpret_cast<float*>(&temp_5));
				r12.z = (*reinterpret_cast<float*>(&temp_6));
				r12.w = (*reinterpret_cast<float*>(&temp_7));
			}
			temp_2 = (*reinterpret_cast<int32_t*>(&v4.x));
			r13.x = float(temp_2); // UTOF softcast
			temp_2 = (*reinterpret_cast<int32_t*>(&v4.y));
			r13.y = float(temp_2); // UTOF softcast
			temp_2 = (*reinterpret_cast<int32_t*>(&v4.z));
			r13.z = float(temp_2); // UTOF softcast
			temp_2 = (*reinterpret_cast<int32_t*>(&v4.w));
			r13.w = float(temp_2); // UTOF softcast
			{
				temp_4 = r13.x == r10.x ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r13.xyzw r13.xyzw r10.xxxx
				temp_5 = r13.y == r10.x ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r13.xyzw r13.xyzw r10.xxxx
				temp_6 = r13.z == r10.x ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r13.xyzw r13.xyzw r10.xxxx
				temp_7 = r13.w == r10.x ? (*reinterpret_cast<int32_t*>(&temp_0)) : (*reinterpret_cast<int32_t*>(&temp_1)); // EQ r13.xyzw r13.xyzw r10.xxxx
				r13.x = (*reinterpret_cast<float*>(&temp_4));
				r13.y = (*reinterpret_cast<float*>(&temp_5));
				r13.z = (*reinterpret_cast<float*>(&temp_6));
				r13.w = (*reinterpret_cast<float*>(&temp_7));
			}
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r13.x)) & (*reinterpret_cast<int32_t*>(&v5.x)); // AND r1.w r13.x v5.x
				r1.w = (*reinterpret_cast<float*>(&temp_4));
			}
			r2.w = r1.w + v5.y;
			r1.w = (*reinterpret_cast<int32_t*>(&r13.y)) ? r2.w : r1.w;
			r2.w = r1.w + v5.z;
			r1.w = (*reinterpret_cast<int32_t*>(&r13.z)) ? r2.w : r1.w;
			r2.w = r1.w + v5.w;
			r1.w = (*reinterpret_cast<int32_t*>(&r13.w)) ? r2.w : r1.w;
			r11.w = r11.w * r1.w;
			{
				temp_4 = (*reinterpret_cast<int32_t*>(&r11.x)) & (*reinterpret_cast<int32_t*>(&r12.w)); // AND r13.xyzw r11.xyzw r12.wwww
				temp_5 = (*reinterpret_cast<int32_t*>(&r11.y)) & (*reinterpret_cast<int32_t*>(&r12.w)); // AND r13.xyzw r11.xyzw r12.wwww
				temp_6 = (*reinterpret_cast<int32_t*>(&r11.z)) & (*reinterpret_cast<int32_t*>(&r12.w)); // AND r13.xyzw r11.xyzw r12.wwww
				temp_7 = (*reinterpret_cast<int32_t*>(&r11.w)) & (*reinterpret_cast<int32_t*>(&r12.w)); // AND r13.xyzw r11.xyzw r12.wwww
				r13.x = (*reinterpret_cast<float*>(&temp_4));
				r13.y = (*reinterpret_cast<float*>(&temp_5));
				r13.z = (*reinterpret_cast<float*>(&temp_6));
				r13.w = (*reinterpret_cast<float*>(&temp_7));
			}
			r0.xyz = vec3(r11.xyz);
			r0.x = (*reinterpret_cast<int32_t*>(&r12.z)) ? r0.x : r13.x;
			r0.y = (*reinterpret_cast<int32_t*>(&r12.z)) ? r0.y : r13.y;
			r0.z = (*reinterpret_cast<int32_t*>(&r12.z)) ? r0.z : r13.z;
			r0.w = (*reinterpret_cast<int32_t*>(&r12.z)) ? r0.w : r13.w;
			r0.x = (*reinterpret_cast<int32_t*>(&r12.y)) ? r10.x : r0.x;
			r0.y = (*reinterpret_cast<int32_t*>(&r12.y)) ? r10.y : r0.y;
			r0.z = (*reinterpret_cast<int32_t*>(&r12.y)) ? r10.z : r0.z;
			r0.w = (*reinterpret_cast<int32_t*>(&r12.y)) ? r10.w : r0.w;
			r5.xyz = vec3(r10.xyz);
			//o9.x = (*reinterpret_cast<int32_t*>(&r12.x)) ? r5.x : r0.x;
			//o9.y = (*reinterpret_cast<int32_t*>(&r12.x)) ? r5.y : r0.y;
			//o9.z = (*reinterpret_cast<int32_t*>(&r12.x)) ? r5.z : r0.z;
			//o9.w = (*reinterpret_cast<int32_t*>(&r12.x)) ? r5.w : r0.w;
			r9.x = r4.y;
		}
		r0.x = -v0.y + v12.w;
		r0.x = r0.x + 10.000000f;
		r0.x = r0.x * 0.100000f;
		r0.y = min(1.f, max(0.f, ceil(v12.w)));
		r0.x = r0.y * r0.x;
		{
			temp_12 = 0.000000f < v12.z ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r0.y _CONVERT(0.000000) v12.z
			r0.y = temp_12;
		}
		{
			temp_12 = 0.000000f < r0.x ? (*reinterpret_cast<float*>(&temp_0)) : (*reinterpret_cast<float*>(&temp_1)); // LT r0.z _CONVERT(0.000000) r0.x
			r0.z = temp_12;
		}
		{
			temp_4 = (*reinterpret_cast<int32_t*>(&r0.z)) | (*reinterpret_cast<int32_t*>(&r0.y)); // OR r0.y r0.z r0.y
			r0.y = (*reinterpret_cast<float*>(&temp_4));
		}
		r5.y = max(r0.x, v12.z);
		r5.x = min(1.f, max(0.f, -r5.y + v12.y));
		//o8.x = (*reinterpret_cast<int32_t*>(&r0.y)) ? r5.x : v12.y;
		//o8.y = (*reinterpret_cast<int32_t*>(&r0.y)) ? r5.y : v12.z;
		//o8.z = door(v10.w);
		r5.xyzw = vec4(v7.xxxx) * vec4(cb0[0].xyzw);
		r10.xyzw = vec4(v7.yyyy) * vec4(cb0[1].xyzw);
		r5.xyzw = vec4(r5.xyzw) + vec4(r10.xyzw);
		r10.xyzw = vec4(v7.zzzz) * vec4(cb0[2].xyzw);
		r5.xyzw = vec4(r5.xyzw) + vec4(r10.xyzw);
		r10.xyzw = vec4(v8.xxxx) * vec4(cb0[0].xyzw);
		r11.xyzw = vec4(v8.yyyy) * vec4(cb0[1].xyzw);
		r10.xyzw = vec4(r10.xyzw) + vec4(r11.xyzw);
		r11.xyzw = vec4(v8.zzzz) * vec4(cb0[2].xyzw);
		r10.xyzw = vec4(r10.xyzw) + vec4(r11.xyzw);
		r11.xyzw = vec4(v9.xxxx) * vec4(cb0[0].xyzw);
		r12.xyzw = vec4(v9.yyyy) * vec4(cb0[1].xyzw);
		r11.xyzw = vec4(r11.xyzw) + vec4(r12.xyzw);
		r12.xyzw = vec4(v9.zzzz) * vec4(cb0[2].xyzw);
		r11.xyzw = vec4(r11.xyzw) + vec4(r12.xyzw);
		r12.xyzw = vec4(r2.xxxx) * vec4(cb0[0].xyzw);
		r13.xyzw = vec4(r2.yyyy) * vec4(cb0[1].xyzw);
		r12.xyzw = vec4(r12.xyzw) + vec4(r13.xyzw);
		r2.xyzw = vec4(r2.zzzz) * vec4(cb0[2].xyzw);
		r2.xyzw = vec4(r2.xyzw) + vec4(r12.xyzw);
		r2.xyzw = vec4(r2.xyzw) + vec4(cb0[3].xyzw);
		r5.xyzw = vec4(r4.xxxx) * vec4(r5.xyzw);
		r9.xyzw = vec4(r9.xxxx) * vec4(r10.xyzw);
		r5.xyzw = vec4(r5.xyzw) + vec4(r9.xyzw);
		r9.xyzw = vec4(r4.zzzz) * vec4(r11.xyzw);
		r5.xyzw = vec4(r5.xyzw) + vec4(r9.xyzw);
		r2.xyzw = vec4(r2.xyzw) * vec4(r4.wwww);
		o0.xyzw = vec4(r2.xyzw) + vec4(r5.xyzw);
		//o2.w = r4.y;
		//o2.xyz = vec3(r8.xyz);
		//o4.xyz = vec3(r3.xyz);
		//o4.w = 0.f;
		//o5.xyz = vec3(r1.xyz);
		//o5.w = 0.f;
		//o6.xyzw = vec4(v11.xyzw);
		//o7.xyzw = vec4(v6.xyzw);
		//o8.w = r0.x;
		//o10.xyz = vec3(v3.zyx);
		//o10.w = 0.f;
		//o11.xyzw = vec4(0.f, 0.f, 0.f, 0.f);
		//o12.xyzw = vec4(0.f, 0.f, 0.f, 0.f);
		//o13.xyzw = vec4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
		//r6.z = v0.x;
		//o1.xyz = vec3(r6.xyz);
		//o3.xyz = vec3(r7.xyz);





		//r0.xyzw = vec4(v1.xyzw) * vec4(6.283185f, 6.283185f, 6.283185f, 6.283185f);
		//r0.xyzw = vec4(r0.xyzw) + vec4(-3.141593f, -3.141593f, -3.141593f, -3.141593f);
		//r1.xyzw = sin(vec4(r0.xyzw));
		//r2.xyzw = cos(vec4(r0.xyzw));
		//r3.xy = abs(vec2(r1.yw)) * vec2(r2.xz);
		//r1.xy = vec2(r1.xz) * abs(vec2(r1.yw));
		//r1.z = r2.y;
		//r1.w = r3.x;
		//r3.z = r2.w;
		//r3.w = r1.y;
		//r0.xyz = vec3(r1.xzw) * vec3(r3.zyw);
		//r2.xyz = vec3(r3.wzy) * vec3(r1.zwx);
		//r0.xyz = vec3(r0.xyz) + -vec3(r2.xyz);
		//r0.w = 0.000000f < r0.w;
		//r0.x = r0.w ? r0.x : -r0.x;
		//r0.y = r0.w ? r0.y : -r0.y;
		//r0.z = r0.w ? r0.z : -r0.z;
		//r0.w = int32_t(v9.w);
		//r2.xyz = vec3(v10.xyz) + -vec3(cb0[4].xyz);
		//r1.y = int32_t(v12.x);
		//r2.w = r1.y < 0.f;
		//r3.x = 1.f > r0.w;
		//r2.w = r2.w && r3.x;
		//r4.x = 1.f < r0.w;
		//r4.y = cb3[5].w != 0.f;
		//r4.y = -1.f == r4.y;
		//r0.w = 1.f == r0.w;
		//r0.w = r0.w && r4.y;
		//r4.y = v5.y + v5.x;
		//r5.z = -r4.y + 1.000000f;
		//r5.x = 3.f;
		//r6.x = 4.f;
		//r6.z = v5.z;
		//r5.x = r0.w ? r5.x : r6.x;
		//r5.z = r0.w ? r5.z : r6.z;
		//r6.xy = vec2(1.f, 1.000000f);
		//r6.z = v5.z;
		//r5.y = v5.x;
		//r4.x = r4.x ? r6.x : r5.x;
		//r4.z = r4.x ? r6.y : r5.y;
		//r4.w = r4.x ? r6.z : r5.z;
		//r5.xz = vec2(r4.zw);
		//r5.yw = vec2(v5.yw);
		//r6.xyz = vec3(0.f, 0.f, 0.f);
		//r7.xyz = vec3(0.f, 0.f, 0.f);
		//r8.xyz = vec3(0.f, 0.f, 0.f);
		//r9.xyz = vec3(0.f, 0.f, 0.f);
		//r4.z = 0.f;
		//while (true) {
		//	r0.w = r4.z < r4.x;
		//	r6.w = dot(vec4(r5.xyzw), vec4(Helper_IdentRowSafe(uint32_t(r4.z)).xyzw));
		//	r7.w = 0.000000f < r6.w;
		//	r0.w = r0.w && r7.w;
		//	if (r0.w == 0) { break; }
		//	r0.w = float(-1 * int32_t(r4.z));
		//	uint32_t aa = 0xFFFFFFFF;
		//	r10.x = r4.z < 1.f ? *reinterpret_cast<float*>(&aa) : 0x0;
		//	r10.y = r4.z < 2.f;
		//	r10.z = r4.z < 3.f;
		//	r11.y = r0.w && r10.y;
		//	r4.zw = vec2(r4.zz) + vec2(1.f, -3.f);
		//	r11.z = r10.y ? 0.f : r4.w;
		//	r11.w = r10.z == 0.f;
		//	r11.x = r10.x;
		//	r10.x = r11.x && v4.x;
		//	r10.y = r11.y && v4.y;
		//	r10.z = r11.z && v4.z;
		//	r10.w = r11.w && v4.w;
		//	r10.x = r10.y || r10.x;
		//	r10.y = r10.w || r10.z;
		//	r0.w = r10.y || r10.x;
		//	r0.w = float(int32_t(r0.w) << 2);
		//	r0.w = float(r0.w); // This was an unsigned to float call. Expect a preceding float()!
		//	r0.w = r0.w + v6.z;
		//	r4.w = uint32_t(r0.w);
		//	r10.x = t0[uint32_t(r4.w)].x;
		//	r10.y = t0[uint32_t(r4.w)].y;
		//	r10.z = t0[uint32_t(r4.w)].z;
		//	r10.xyz = vec3(r6.www) * vec3(r10.xyz);
		//	r6.xyz = vec3(r6.xyz) + vec3(r10.xyz);
		//	r10.xyz = vec3(r0.www) + vec3(1.000000f, 2.000000f, 3.000000f);
		//	r10.x = uint32_t(r10.x);
		//	r10.y = uint32_t(r10.y);
		//	r10.z = uint32_t(r10.z);
		//	r11.x = t0[uint32_t(r10.x)].x;
		//	r11.y = t0[uint32_t(r10.x)].y;
		//	r11.z = t0[uint32_t(r10.x)].z;
		//	r11.xyz = vec3(r6.www) * vec3(r11.xyz);
		//	r7.xyz = vec3(r7.xyz) + vec3(r11.xyz);
		//	r10.x = t0[uint32_t(r10.y)].x;
		//	r10.y = t0[uint32_t(r10.y)].y;
		//	r10.w = t0[uint32_t(r10.y)].z;
		//	r10.xyw = vec3(r6.www) * vec3(r10.xyw);
		//	r8.xyz = vec3(r8.xyz) + vec3(r10.xyw);
		//	r10.x = t0[uint32_t(r10.z)].x;
		//	r10.y = t0[uint32_t(r10.z)].y;
		//	r10.z = t0[uint32_t(r10.z)].z;
		//	r10.xyz = vec3(r6.www) * vec3(r10.xyz);
		//	r9.xyz = vec3(r9.xyz) + vec3(r10.xyz);
		//}
		//r0.w = 0.020000f < v3.w;
		//r0.w = r0.w && r2.w;
		//if (r0.w != 0) {
		//	r0.w = max(-r1.y, r1.y);
		//	r4.xzw = vec3(0.f, 0.f, 0.f);
		//	r5.xyz = vec3(0.f, 0.f, 0.f);
		//	r10.xyz = vec3(0.f, 0.f, 0.f);
		//	r11.xyz = vec3(0.f, 0.f, 0.f);
		//	r12.x = 0.f;
		//	while (true) {
		//		r1.y = r12.x < 4.f;
		//		r2.w = dot(vec4(v5.xyzw), vec4(Helper_IdentRowSafe(uint32_t(r12.x)).xyzw));
		//		r5.w = 0.000000f < r2.w;
		//		r1.y = r1.y && r5.w;
		//		if (r1.y == 0) { break; }
		//		r1.y = float(-1 * int32_t(r12.x));
		//		r13.x = r12.x < 1.f;
		//		r13.y = r12.x < 2.f;
		//		r13.z = r12.x < 3.f;
		//		r14.y = r1.y && r13.y;
		//		r12.xy = vec2(r12.xx) + vec2(1.f, -3.f);
		//		r14.z = r13.y ? 0.f : r12.y;
		//		r14.w = r13.z == 0.f;
		//		r14.x = r13.x;
		//		r13.x = r14.x && v4.x;
		//		r13.y = r14.y && v4.y;
		//		r13.z = r14.z && v4.z;
		//		r13.w = r14.w && v4.w;
		//		r12.y = r13.y || r13.x;
		//		r12.z = r13.w || r13.z;
		//		r1.y = r12.z || r12.y;
		//		r1.y = r0.w + r1.y;
		//		r1.y = float(int32_t(r1.y) << 2);
		//		r1.y = float(r1.y); // This was an unsigned to float call. Expect a preceding float()!
		//		r1.y = r1.y + v6.z;
		//		r5.w = uint32_t(r1.y);
		//		r12.y = t0[uint32_t(r5.w)].x;
		//		r12.z = t0[uint32_t(r5.w)].y;
		//		r12.w = t0[uint32_t(r5.w)].z;
		//		r12.yzw = vec3(r2.www) * vec3(r12.yzw);
		//		r4.xzw = vec3(r4.xzw) + vec3(r12.yzw);
		//		r12.yzw = vec3(r1.yyy) + vec3(1.000000f, 2.000000f, 3.000000f);
		//		r12.y = uint32_t(r12.y);
		//		r12.z = uint32_t(r12.z);
		//		r12.w = uint32_t(r12.w);
		//		r13.x = t0[uint32_t(r12.y)].x;
		//		r13.y = t0[uint32_t(r12.y)].y;
		//		r13.z = t0[uint32_t(r12.y)].z;
		//		r13.xyz = vec3(r2.www) * vec3(r13.xyz);
		//		r5.xyz = vec3(r5.xyz) + vec3(r13.xyz);
		//		r13.x = t0[uint32_t(r12.z)].x;
		//		r13.y = t0[uint32_t(r12.z)].y;
		//		r13.z = t0[uint32_t(r12.z)].z;
		//		r13.xyz = vec3(r2.www) * vec3(r13.xyz);
		//		r10.xyz = vec3(r10.xyz) + vec3(r13.xyz);
		//		r12.y = t0[uint32_t(r12.w)].x;
		//		r12.z = t0[uint32_t(r12.w)].y;
		//		r12.w = t0[uint32_t(r12.w)].z;
		//		r12.yzw = vec3(r2.www) * vec3(r12.yzw);
		//		r11.xyz = vec3(r11.xyz) + vec3(r12.yzw);
		//	}
		//	r0.w = v3.w * v3.w;
		//	r0.w = r0.w * r0.w;
		//	r4.xzw = -vec3(r6.xyz) + vec3(r4.xzw);
		//	r5.xyz = -vec3(r7.xyz) + vec3(r5.xyz);
		//	r10.xyz = -vec3(r8.xyz) + vec3(r10.xyz);
		//	r11.xyz = -vec3(r9.xyz) + vec3(r11.xyz);
		//	r4.xzw = vec3(r0.www) * vec3(r4.xzw);
		//	r5.xyz = vec3(r0.www) * vec3(r5.xyz);
		//	r10.xyz = vec3(r0.www) * vec3(r10.xyz);
		//	r11.xyz = vec3(r0.www) * vec3(r11.xyz);
		//	r6.xyz = vec3(r4.xzw) + vec3(r6.xyz);
		//	r7.xyz = vec3(r5.xyz) + vec3(r7.xyz);
		//	r8.xyz = vec3(r8.xyz) + vec3(r10.xyz);
		//	r9.xyz = vec3(r9.xyz) + vec3(r11.xyz);
		//}
		//r4.xzw = vec3(r6.xyz) * vec3(v0.xxx);
		//r5.xyz = vec3(r7.xyz) * vec3(v0.yyy);
		//r4.xzw = vec3(r4.xzw) + vec3(r5.xyz);
		//r5.xyz = vec3(r8.xyz) * vec3(v0.zzz);
		//r4.xzw = vec3(r4.xzw) + vec3(r5.xyz);
		//r5.xyz = vec3(r9.xyz) + vec3(r4.xzw);
		//r0.w = r4.y + v5.z;
		//r5.w = r0.w + v5.w;
		//r4.xyzw = vec4(r5.xyzw) / vec4(r5.wwww);
		//r5.x = v7.x;
		//r5.y = v8.x;
		//r5.z = v9.x;
		//r9.x = dot(vec3(r6.xyz), vec3(r5.xyz));
		//r10.x = v7.y;
		//r10.y = v8.y;
		//r10.z = v9.y;
		//r11.x = dot(vec3(r6.xyz), vec3(r10.xyz));
		//r12.x = v7.z;
		//r12.y = v8.z;
		//r12.z = v9.z;
		//r6.x = dot(vec3(r6.xyz), vec3(r12.xyz));
		//r9.y = dot(vec3(r7.xyz), vec3(r5.xyz));
		//r11.y = dot(vec3(r7.xyz), vec3(r10.xyz));
		//r6.y = dot(vec3(r7.xyz), vec3(r12.xyz));
		//r9.z = dot(vec3(r8.xyz), vec3(r5.xyz));
		//r11.z = dot(vec3(r8.xyz), vec3(r10.xyz));
		//r6.z = dot(vec3(r8.xyz), vec3(r12.xyz));
		//r7.x = dot(vec3(r0.xyz), vec3(r9.xyz));
		//r7.y = dot(vec3(r0.xyz), vec3(r11.xyz));
		//r7.z = dot(vec3(r0.xyz), vec3(r6.xyz));
		//r0.w = dot(vec3(r7.xyz), vec3(r7.xyz));
		//r0.w = 1.f / sqrt(r0.w);
		//r7.xyz = vec3(r0.www) * vec3(r7.xyz);
		//if (r3.x != 0) {
		//	r8.x = dot(vec3(r1.wxz), vec3(r9.xyz));
		//	r8.y = dot(vec3(r1.wxz), vec3(r11.xyz));
		//	r8.z = dot(vec3(r1.wxz), vec3(r6.xyz));
		//	r1.x = dot(vec3(r3.ywz), vec3(r9.xyz));
		//	r1.y = dot(vec3(r3.ywz), vec3(r11.xyz));
		//	r1.z = dot(vec3(r3.ywz), vec3(r6.xyz));
		//	r0.w = dot(vec3(r8.xyz), vec3(r8.xyz));
		//	r0.w = 1.f / sqrt(r0.w);
		//	r3.xyz = vec3(r0.www) * vec3(r8.xyz);
		//	r0.w = dot(vec3(r1.xyz), vec3(r1.xyz));
		//	r0.w = 1.f / sqrt(r0.w);
		//	r1.xyz = vec3(r0.www) * vec3(r1.xyz);
		//}
		//else {
		//	r3.xyz = vec3(0.f, 0.f, 0.f);
		//	r1.xyz = vec3(0.f, 0.f, 0.f);
		//}
		//r0.w = v11.y > 0.000000f;
		//if (r0.w != 0) {
		//	r6.xy = vec2(v2.yy) * vec2(cb2[1].xy);
		//	r6.xy = vec2(v2.xx) * vec2(cb2[0].xy) + vec2(r6.xy);
		//	r6.xy = vec2(r6.xy) + vec2(cb2[2].xy);
		//}
		//else {
		//	r6.xy = vec2(v2.xy);
		//}
		//r5.w = r2.x;
		//r5.x = dot(vec4(r4.xyzw), vec4(r5.xyzw));
		//r10.w = r2.y;
		//r5.y = dot(vec4(r4.xyzw), vec4(r10.xyzw));
		//r12.w = r2.z;
		//r5.z = dot(vec4(r4.xyzw), vec4(r12.xyzw));
		//r8.xyz = vec3(r5.xyz) + vec3(cb0[4].xyz);
		//r0.w = 0.000000f < v7.w;
		//if (r0.w != 0) {
		//	r0.w = int32_t(v10.w);
		//	if (r0.w == 0) {
		//		r0.w = v7.w * v7.w;
		//		r0.w = r0.w * r0.w;
		//		//o9.w = min(r0.w, 1.000000f);
		//		//o9.xyz = vec3(0.500000f, 0.500000f, 0.500000f);
		//		r9.x = r4.y;
		//	}
		//	else {
		//		r0.w = v6.x + 1.000000f;
		//		r1.w = uint32_t(r0.w);
		//		r10.x = t0[uint32_t(r1.w)].x;
		//		r10.y = t0[uint32_t(r1.w)].y;
		//		r10.z = t0[uint32_t(r1.w)].z;
		//		r0.w = r0.w + 1.000000f;
		//		r0.w = uint32_t(r0.w);
		//		r11.x = t0[uint32_t(r0.w)].x;
		//		r11.y = t0[uint32_t(r0.w)].y;
		//		r11.z = t0[uint32_t(r0.w)].z;
		//		r11.xyz = vec3(r8.xyz) + -vec3(r11.xyz);
		//		r0.w = 0.900000f < r10.z;
		//		r11.w = r0.w ? 0.f : r11.z;
		//		r0.w = dot(vec3(r11.xyw), vec3(r11.xyw));
		//		r0.w = sqrt(r0.w);
		//		r0.w = min(1.f, max(0.f, r0.w / 260.000000f));
		//		r0.w = -r0.w + 1.000000f;
		//		r0.w = r0.w * r0.w;
		//		r0.w = r0.w * 2.000000f;
		//		r0.w = min(r0.w, 1.000000f);
		//		r1.w = dot(vec3(r10.xyz), vec3(r10.xyz));
		//		r1.w = 1.f / sqrt(r1.w);
		//		r10.xyz = vec3(r1.www) * vec3(r10.xyz);
		//		r1.w = dot(vec3(r0.xyz), vec3(r10.xyz));
		//		r1.w = r1.w * 0.500000f;
		//		r1.w = min(1.f, max(0.f, r1.w + 0.500000f));
		//		r1.w = r1.w * r1.w;
		//		r1.w = r1.w * 2.000000f;
		//		r2.w = r10.z < 0.900000f;
		//		r11.xyz = vec3(r10.xyz) * vec3(r1.www);
		//		r11.xyz = vec3(r0.www) * vec3(r11.xyz);
		//		r11.xyz = vec3(r11.xyz) * vec3(50.000000f, 50.000000f, 50.000000f);
		//		r3.w = log(v7.w);
		//		r3.w = r3.w * 10.000000f;
		//		r3.w = exp(r3.w);
		//		r11.xyz = vec3(r3.www) * vec3(r11.xyz);
		//		r11.xyz = vec3(r4.xyz) + vec3(r11.xyz);
		//		r0.xyz = vec3(r0.xyz) + vec3(r10.xyz);
		//		r0.xyz = vec3(r0.xyz) * vec3(r1.www);
		//		r0.xyz = vec3(r0.www) * vec3(r0.xyz);
		//		r0.xyz = vec3(r0.xyz) * vec3(25.000000f, 25.000000f, 25.000000f);
		//		r0.xyz = vec3(r3.www) * vec3(r0.xyz);
		//		r0.xyz = vec3(r0.xyz) + vec3(r4.xyz);
		//		r9.x = r2.w ? r11.y : r0.y;
		//		r9.y = r2.w ? r11.x : r0.x;
		//		r9.z = r2.w ? r11.z : r0.z;
		//		r0.x = r1.w * v7.w;
		//		r0.y = r0.x * r0.x;
		//		r0.y = r0.y * r0.y;
		//		r0.x = r0.y * r0.x;
		//		//o9.w = min(r0.x, 1.000000f);
		//		//o9.xyz = vec3(0.392157f, 0.627451f, 0.941176f);
		//		r4.xz = vec2(r9.yz);
		//	}
		//}
		//else {
		//	r0.xy = vec2(v6.xx) + vec2(2.000000f, 1.000000f);
		//	r0.x = uint32_t(r0.x);
		//	r0.y = uint32_t(r0.y);
		//	r10.x = t0[uint32_t(r0.x)].x;
		//	r10.y = t0[uint32_t(r0.x)].y;
		//	r10.z = t0[uint32_t(r0.x)].z;
		//	r10.w = t0[uint32_t(r0.x)].w;
		//	r0.x = dot(vec3(r5.xyz), vec3(r5.xyz));
		//	r0.x = 1.f / sqrt(r0.x);
		//	r0.xzw = vec3(r0.xxx) * vec3(r5.xyz);
		//	r0.x = dot(vec3(r7.xyz), -vec3(r0.xzw));
		//	r0.z = -r0.x * 0.500000f + 1.500000f;
		//	r5.w = r0.z * -r10.w;
		//	r0.x = min(1.f, max(0.f, -r0.x + 1.000000f));
		//	r10.w = r0.x * r10.w;
		//	r11.x = t0[uint32_t(r0.y)].x;
		//	r11.y = t0[uint32_t(r0.y)].y;
		//	r11.z = t0[uint32_t(r0.y)].z;
		//	r11.w = t0[uint32_t(r0.y)].w;
		//	r0.w = r0.x * abs(r11.w);
		//	r12.x = v7.w == -1.000000f;
		//	r12.y = v7.w == -2.000000f;
		//	r12.z = v7.w == -3.000000f;
		//	r12.w = v7.w == -4.000000f;
		//	r13.x = float(v4.x); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.y = float(v4.y); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.z = float(v4.z); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.w = float(v4.w); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.x = r13.x == r10.x;
		//	r13.y = r13.y == r10.x;
		//	r13.z = r13.z == r10.x;
		//	r13.w = r13.w == r10.x;
		//	r1.w = r13.x && v5.x;
		//	r2.w = r1.w + v5.y;
		//	r1.w = r13.y ? r2.w : r1.w;
		//	r2.w = r1.w + v5.z;
		//	r1.w = r13.z ? r2.w : r1.w;
		//	r2.w = r1.w + v5.w;
		//	r1.w = r13.w ? r2.w : r1.w;
		//	r11.w = r11.w * r1.w;
		//	r13.x = r11.x && r12.w;
		//	r13.y = r11.y && r12.w;
		//	r13.z = r11.z && r12.w;
		//	r13.w = r11.w && r12.w;
		//	r0.xyz = vec3(r11.xyz);
		//	r0.x = r12.z ? r0.x : r13.x;
		//	r0.y = r12.z ? r0.y : r13.y;
		//	r0.z = r12.z ? r0.z : r13.z;
		//	r0.w = r12.z ? r0.w : r13.w;
		//	r0.x = r12.y ? r10.x : r0.x;
		//	r0.y = r12.y ? r10.y : r0.y;
		//	r0.z = r12.y ? r10.z : r0.z;
		//	r0.w = r12.y ? r10.w : r0.w;
		//	r5.xyz = vec3(r10.xyz);
		//	//o9.x = r12.x ? r5.x : r0.x;
		//	//o9.y = r12.x ? r5.y : r0.y;
		//	//o9.z = r12.x ? r5.z : r0.z;
		//	//o9.w = r12.x ? r5.w : r0.w;
		//	r9.x = r4.y;
		//}
		//r0.x = -v0.y + v12.w;
		//r0.x = r0.x + 10.000000f;
		//r0.x = r0.x * 0.100000f;
		//r0.y = min(1.f, max(0.f, ceil(v12.w)));
		//r0.x = r0.y * r0.x;
		//r0.y = 0.000000f < v12.z;
		//r0.z = 0.000000f < r0.x;
		//r0.y = r0.z || r0.y;
		//r5.y = max(r0.x, v12.z);
		//r5.x = min(1.f, max(0.f, -r5.y + v12.y));
		////o8.x = r0.y ? r5.x : v12.y;
		////o8.y = r0.y ? r5.y : v12.z;
		////o8.z = floor(v10.w);
		//r5.xyzw = vec4(v7.xxxx) * vec4(cb0[0].xyzw);
		//r10.xyzw = vec4(v7.yyyy) * vec4(cb0[1].xyzw);
		//r5.xyzw = vec4(r5.xyzw) + vec4(r10.xyzw);
		//r10.xyzw = vec4(v7.zzzz) * vec4(cb0[2].xyzw);
		//r5.xyzw = vec4(r5.xyzw) + vec4(r10.xyzw);
		//r10.xyzw = vec4(v8.xxxx) * vec4(cb0[0].xyzw);
		//r11.xyzw = vec4(v8.yyyy) * vec4(cb0[1].xyzw);
		//r10.xyzw = vec4(r10.xyzw) + vec4(r11.xyzw);
		//r11.xyzw = vec4(v8.zzzz) * vec4(cb0[2].xyzw);
		//r10.xyzw = vec4(r10.xyzw) + vec4(r11.xyzw);
		//r11.xyzw = vec4(v9.xxxx) * vec4(cb0[0].xyzw);
		//r12.xyzw = vec4(v9.yyyy) * vec4(cb0[1].xyzw);
		//r11.xyzw = vec4(r11.xyzw) + vec4(r12.xyzw);
		//r12.xyzw = vec4(v9.zzzz) * vec4(cb0[2].xyzw);
		//r11.xyzw = vec4(r11.xyzw) + vec4(r12.xyzw);
		//r12.xyzw = vec4(r2.xxxx) * vec4(cb0[0].xyzw);
		//r13.xyzw = vec4(r2.yyyy) * vec4(cb0[1].xyzw);
		//r12.xyzw = vec4(r12.xyzw) + vec4(r13.xyzw);
		//r2.xyzw = vec4(r2.zzzz) * vec4(cb0[2].xyzw);
		//r2.xyzw = vec4(r2.xyzw) + vec4(r12.xyzw);
		//r2.xyzw = vec4(r2.xyzw) + vec4(cb0[3].xyzw);
		//r5.xyzw = vec4(r4.xxxx) * vec4(r5.xyzw);
		//r9.xyzw = vec4(r9.xxxx) * vec4(r10.xyzw);
		//r5.xyzw = vec4(r5.xyzw) + vec4(r9.xyzw);
		//r9.xyzw = vec4(r4.zzzz) * vec4(r11.xyzw);
		//r5.xyzw = vec4(r5.xyzw) + vec4(r9.xyzw);
		//r2.xyzw = vec4(r2.xyzw) * vec4(r4.wwww);
		//o0.xyzw = vec4(r2.xyzw) + vec4(r5.xyzw);
		////o2.w = r4.y;
		////o2.xyz = vec3(r8.xyz);
		////o4.xyz = vec3(r3.xyz);
		////o4.w = 0.f;
		////o5.xyz = vec3(r1.xyz);
		////o5.w = 0.f;
		////o6.xyzw = vec4(v11.xyzw);
		////o7.xyzw = vec4(v6.xyzw);
		////o8.w = r0.x;
		////o10.xyz = vec3(v3.zyx);
		////o10.w = 0.f;
		////o11.xyzw = vec4(0.f, 0.f, 0.f, 0.f);
		////o12.xyzw = vec4(0.f, 0.f, 0.f, 0.f);
		////o13.xyzw = vec4(1.000000f, 1.000000f, 1.000000f, 1.000000f);
		////r6.z = v0.x;
		////o1.xyz = vec3(r6.xyz);
		////o3.xyz = vec3(r7.xyz);






		
		verts[i].Position.x = o0.x;
		verts[i].Position.y = o0.y;
		verts[i].Position.z = o0.z;

		// AUTOGEN

		//r0.x = v1.x * 6.283185;
		//r0.y = v1.y * 6.283185;
		//r0.z = v1.z * 6.283185;
		//r0.w = v1.w * 6.283185;
		//r0.x = r0.x + -3.141593;
		//r0.y = r0.y + -3.141593;
		//r0.z = r0.z + -3.141593;
		//r0.w = r0.w + -3.141593;
		//r1.xyzw = sin(vec4(r0.xyzw));
		//r2.xyzw = cos(vec4(r0.xyzw));
		//r3.x = abs(r1.y) * r2.x;
		//r3.y = abs(r1.w) * r2.z;
		//r1.x = r1.x * abs(r1.y);
		//r1.y = r1.z * abs(r1.w);
		//r1.z = r2.y;
		//r1.w = r3.x;
		//r3.z = r2.w;
		//r3.w = r1.y;
		//r0.x = r1.x * r3.z;
		//r0.y = r1.z * r3.y;
		//r0.z = r1.w * r3.w;
		//r2.x = r3.w * r1.z;
		//r2.y = r3.z * r1.w;
		//r2.z = r3.y * r1.x;
		//r0.x = r0.x + -r2.x;
		//r0.y = r0.y + -r2.y;
		//r0.z = r0.z + -r2.z;
		//r0.w = 0.000000 < r0.w;
		//r0.x = r0.w ? r0.x : -r0.x;
		//r0.y = r0.w ? r0.y : -r0.y;
		//r0.z = r0.w ? r0.z : -r0.z;
		//r0.w = int32_t(v9.w);

		//r2.x = v10.x + -cb0[4].x;
		//r2.y = v10.y + -cb0[4].y;
		//r2.z = v10.z + -cb0[4].z; // View Pos

		////r2.xyz = v10.xyz;

		//r1.y = int32_t(v12.x);
		//r2.w = r1.y < 0;
		//r3.x = 1 > r0.w;
		//r2.w = r2.w && r3.x;
		//r4.x = 1 < r0.w;
		//r4.y = 0x0 != 0; // IsHair?
		//r4.y = -1 == r4.y;
		//r0.w = 1 == r0.w;
		//r0.w = r0.w && r4.y;
		//r4.y = v5.y + v5.x;
		//r5.z = -r4.y + 1.000000;
		//r5.x = 3;
		//r6.x = 4;
		//r6.z = v5.z;
		//r5.x = r0.w ? r5.x : r6.x;
		//r5.z = r0.w ? r5.z : r6.z;
		//r6.x = 1;
		//r6.y = 1.000000;
		//r6.z = v5.z;
		//r5.y = v5.x;
		//r4.x = r4.x ? r6.x : r5.x;
		//r4.z = r4.x ? r6.y : r5.y;
		//r4.w = r4.x ? r6.z : r5.z;
		//r5.x = r4.z;
		//r5.z = r4.w;
		//r5.y = v5.y;
		//r5.w = v5.w;
		//r6.x = 0;
		//r6.y = 0;
		//r6.z = 0;
		//r7.x = 0;
		//r7.y = 0;
		//r7.z = 0;
		//r8.x = 0;
		//r8.y = 0;
		//r8.z = 0;
		//r9.x = 0;
		//r9.y = 0;
		//r9.z = 0;
		//r4.z = 0;
		//while (true) {
		//	r0.w = r4.z < r4.x;
		//	
		//	r6.w = dot(vec4(r5.xyzw), vec4(Helper_IdentRowSafe(uint32_t(r4.z)).xyzw));
		//	r7.w = 0.000000 < r6.w;
		//	r0.w = r0.w && r7.w;
		//	if (r0.w == 0) { break; }
		//	// r0.w is bitset?
		//	r0.w = 1;// TwosComplement(r4.z);
		//	r10.x = r4.z < 1;
		//	r10.y = r4.z < 2;
		//	r10.z = r4.z < 3;
		//	r11.y = r0.w && r10.y;
		//	r4.z = r4.z + 1;
		//	r4.w = r4.z + -3;
		//	r11.z = r10.y ? 0 : r4.w;
		//	r11.w = r10.z == 0;
		//	r11.x = r10.x;
		//	r10.x = r11.x && v4.x;
		//	r10.y = r11.y && v4.y;
		//	r10.z = r11.z && v4.z;
		//	r10.w = r11.w && v4.w;
		//	r10.x = r10.y || r10.x;
		//	r10.y = r10.w || r10.z;
		//	r0.w = r10.y || r10.x;
		//	r0.w = float(int32_t(r0.w) << 2);
		//	r0.w = float(r0.w); // This was an unsigned to float call. Expect a preceding float()!
		//	r0.w = r0.w + v6.z;
		//	r4.w = uint32_t(r0.w);
		//	r10.x = t0[uint32_t(r4.w)].x;
		//	r10.y = t0[uint32_t(r4.w)].y;
		//	r10.z = t0[uint32_t(r4.w)].z;
		//	r10.x = r6.w * r10.x;
		//	r10.y = r6.w * r10.y;
		//	r10.z = r6.w * r10.z;
		//	r6.x = r6.x + r10.x;
		//	r6.y = r6.y + r10.y;
		//	r6.z = r6.z + r10.z;
		//	r10.x = r0.w + 1.000000;
		//	r10.y = r0.w + 2.000000;
		//	r10.z = r0.w + 3.000000;
		//	r10.x = uint32_t(r10.x);
		//	r10.y = uint32_t(r10.y);
		//	r10.z = uint32_t(r10.z);
		//	r11.x = t0[uint32_t(r10.x)].x;
		//	r11.y = t0[uint32_t(r10.x)].y;
		//	r11.z = t0[uint32_t(r10.x)].z;
		//	r11.x = r6.w * r11.x;
		//	r11.y = r6.w * r11.y;
		//	r11.z = r6.w * r11.z;
		//	r7.x = r7.x + r11.x;
		//	r7.y = r7.y + r11.y;
		//	r7.z = r7.z + r11.z;
		//	r10.x = t0[uint32_t(r10.y)].x;
		//	r10.y = t0[uint32_t(r10.y)].y;
		//	r10.w = t0[uint32_t(r10.y)].z;
		//	r10.x = r6.w * r10.x;
		//	r10.y = r6.w * r10.y;
		//	r10.w = r6.w * r10.w;
		//	r8.x = r8.x + r10.x;
		//	r8.y = r8.y + r10.y;
		//	r8.z = r8.z + r10.w;
		//	r10.x = t0[uint32_t(r10.z)].x;
		//	r10.y = t0[uint32_t(r10.z)].y;
		//	r10.z = t0[uint32_t(r10.z)].z;
		//	r10.x = r6.w * r10.x;
		//	r10.y = r6.w * r10.y;
		//	r10.z = r6.w * r10.z;
		//	r9.x = r9.x + r10.x;
		//	r9.y = r9.y + r10.y;
		//	r9.z = r9.z + r10.z;
		//}
		//r0.w = 0.020000 < v3.w;
		//r0.w = r0.w && r2.w;
		//if (r0.w != 0) {
		//	r0.w = max(-r1.y, r1.y);
		//	r4.x = 0;
		//	r4.z = 0;
		//	r4.w = 0;
		//	r5.x = 0;
		//	r5.y = 0;
		//	r5.z = 0;
		//	r10.x = 0;
		//	r10.y = 0;
		//	r10.z = 0;
		//	r11.x = 0;
		//	r11.y = 0;
		//	r11.z = 0;
		//	r12.x = 0;
		//	while (true) {
		//		r1.y = r12.x < 4;
		//		r2.w = dot(vec4(v5.xyzw), vec4(Helper_IdentRowSafe(uint32_t(r12.x)).xyzw));
		//		r5.w = 0.000000 < r2.w;
		//		r1.y = r1.y && r5.w;
		//		if (r1.y == 0) { break; }
		//		//r1.y = TwosComplement(r12.x);
		//		r1.y = 1;
		//		r13.x = r12.x < 1;
		//		r13.y = r12.x < 2;
		//		r13.z = r12.x < 3;
		//		r14.y = r1.y && r13.y;
		//		r12.x = r12.x + 1;
		//		r12.y = r12.x + -3;
		//		r14.z = r13.y ? 0 : r12.y;
		//		r14.w = r13.z == 0;
		//		r14.x = r13.x;
		//		r13.x = r14.x && v4.x;
		//		r13.y = r14.y && v4.y;
		//		r13.z = r14.z && v4.z;
		//		r13.w = r14.w && v4.w;
		//		r12.y = r13.y || r13.x;
		//		r12.z = r13.w || r13.z;
		//		r1.y = r12.z || r12.y;
		//		r1.y = r0.w + r1.y;
		//		r1.y = float(int32_t(r1.y) << 2);
		//		r1.y = float(r1.y); // This was an unsigned to float call. Expect a preceding float()!
		//		r1.y = r1.y + v6.z;
		//		r5.w = uint32_t(r1.y);
		//		r12.y = t0[uint32_t(r5.w)].x;
		//		r12.z = t0[uint32_t(r5.w)].y;
		//		r12.w = t0[uint32_t(r5.w)].z;
		//		r12.y = r2.w * r12.y;
		//		r12.z = r2.w * r12.z;
		//		r12.w = r2.w * r12.w;
		//		r4.x = r4.x + r12.y;
		//		r4.z = r4.z + r12.z;
		//		r4.w = r4.w + r12.w;
		//		r12.y = r1.y + 1.000000;
		//		r12.z = r1.y + 2.000000;
		//		r12.w = r1.y + 3.000000;
		//		r12.y = uint32_t(r12.y);
		//		r12.z = uint32_t(r12.z);
		//		r12.w = uint32_t(r12.w);
		//		r13.x = t0[uint32_t(r12.y)].x;
		//		r13.y = t0[uint32_t(r12.y)].y;
		//		r13.z = t0[uint32_t(r12.y)].z;
		//		r13.x = r2.w * r13.x;
		//		r13.y = r2.w * r13.y;
		//		r13.z = r2.w * r13.z;
		//		r5.x = r5.x + r13.x;
		//		r5.y = r5.y + r13.y;
		//		r5.z = r5.z + r13.z;
		//		r13.x = t0[uint32_t(r12.z)].x;
		//		r13.y = t0[uint32_t(r12.z)].y;
		//		r13.z = t0[uint32_t(r12.z)].z;
		//		r13.x = r2.w * r13.x;
		//		r13.y = r2.w * r13.y;
		//		r13.z = r2.w * r13.z;
		//		r10.x = r10.x + r13.x;
		//		r10.y = r10.y + r13.y;
		//		r10.z = r10.z + r13.z;
		//		r12.y = t0[uint32_t(r12.w)].x;
		//		r12.z = t0[uint32_t(r12.w)].y;
		//		r12.w = t0[uint32_t(r12.w)].z;
		//		r12.y = r2.w * r12.y;
		//		r12.z = r2.w * r12.z;
		//		r12.w = r2.w * r12.w;
		//		r11.x = r11.x + r12.y;
		//		r11.y = r11.y + r12.z;
		//		r11.z = r11.z + r12.w;
		//	}
		//	r0.w = v3.w * v3.w;
		//	r0.w = r0.w * r0.w;
		//	r4.x = -r6.x + r4.x;
		//	r4.z = -r6.y + r4.z;
		//	r4.w = -r6.z + r4.w;
		//	r5.x = -r7.x + r5.x;
		//	r5.y = -r7.y + r5.y;
		//	r5.z = -r7.z + r5.z;
		//	r10.x = -r8.x + r10.x;
		//	r10.y = -r8.y + r10.y;
		//	r10.z = -r8.z + r10.z;
		//	r11.x = -r9.x + r11.x;
		//	r11.y = -r9.y + r11.y;
		//	r11.z = -r9.z + r11.z;
		//	r4.x = r0.w * r4.x;
		//	r4.z = r0.w * r4.z;
		//	r4.w = r0.w * r4.w;
		//	r5.x = r0.w * r5.x;
		//	r5.y = r0.w * r5.y;
		//	r5.z = r0.w * r5.z;
		//	r10.x = r0.w * r10.x;
		//	r10.y = r0.w * r10.y;
		//	r10.z = r0.w * r10.z;
		//	r11.x = r0.w * r11.x;
		//	r11.y = r0.w * r11.y;
		//	r11.z = r0.w * r11.z;
		//	r6.x = r4.x + r6.x;
		//	r6.y = r4.z + r6.y;
		//	r6.z = r4.w + r6.z;
		//	r7.x = r5.x + r7.x;
		//	r7.y = r5.y + r7.y;
		//	r7.z = r5.z + r7.z;
		//	r8.x = r8.x + r10.x;
		//	r8.y = r8.y + r10.y;
		//	r8.z = r8.z + r10.z;
		//	r9.x = r9.x + r11.x;
		//	r9.y = r9.y + r11.y;
		//	r9.z = r9.z + r11.z;
		//}
		//r4.x = r6.x * v0.x;
		//r4.z = r6.y * v0.x;
		//r4.w = r6.z * v0.x;
		//r5.x = r7.x * v0.y;
		//r5.y = r7.y * v0.y;
		//r5.z = r7.z * v0.y;
		//r4.x = r4.x + r5.x;
		//r4.z = r4.z + r5.y;
		//r4.w = r4.w + r5.z;
		//r5.x = r8.x * v0.z;
		//r5.y = r8.y * v0.z;
		//r5.z = r8.z * v0.z;
		//r4.x = r4.x + r5.x;
		//r4.z = r4.z + r5.y;
		//r4.w = r4.w + r5.z;
		//r5.x = r9.x + r4.x;
		//r5.y = r9.y + r4.z;
		//r5.z = r9.z + r4.w;
		//r0.w = r4.y + v5.z;
		//r5.w = r0.w + v5.w;
		//r4.x = r5.x / r5.w;
		//r4.y = r5.y / r5.w;
		//r4.z = r5.z / r5.w;
		//r4.w = r5.w / r5.w;
		//r5.x = v7.x;
		//r5.y = v8.x;
		//r5.z = v9.x;
		//r9.x = dot(vec3(r6.xyz), vec3(r5.xyz));
		//r10.x = v7.y;
		//r10.y = v8.y;
		//r10.z = v9.y;
		//r11.x = dot(vec3(r6.xyz), vec3(r10.xyz));
		//r12.x = v7.z;
		//r12.y = v8.z;
		//r12.z = v9.z;
		//r6.x = dot(vec3(r6.xyz), vec3(r12.xyz));
		//r9.y = dot(vec3(r7.xyz), vec3(r5.xyz));
		//r11.y = dot(vec3(r7.xyz), vec3(r10.xyz));
		//r6.y = dot(vec3(r7.xyz), vec3(r12.xyz));
		//r9.z = dot(vec3(r8.xyz), vec3(r5.xyz));
		//r11.z = dot(vec3(r8.xyz), vec3(r10.xyz));
		//r6.z = dot(vec3(r8.xyz), vec3(r12.xyz));
		//r7.x = dot(vec3(r0.xyz), vec3(r9.xyz));
		//r7.y = dot(vec3(r0.xyz), vec3(r11.xyz));
		//r7.z = dot(vec3(r0.xyz), vec3(r6.xyz));
		//r0.w = dot(vec3(r7.xyz), vec3(r7.xyz));
		//r0.w = 1.f / sqrt(r0.w);
		//r7.x = r0.w * r7.x;
		//r7.y = r0.w * r7.y;
		//r7.z = r0.w * r7.z;
		//if (r3.x != 0) {
		//	r8.x = dot(vec3(r1.wxz), vec3(r9.xyz));
		//	r8.y = dot(vec3(r1.wxz), vec3(r11.xyz));
		//	r8.z = dot(vec3(r1.wxz), vec3(r6.xyz));
		//	r1.x = dot(vec3(r3.ywz), vec3(r9.xyz));
		//	r1.y = dot(vec3(r3.ywz), vec3(r11.xyz));
		//	r1.z = dot(vec3(r3.ywz), vec3(r6.xyz));
		//	r0.w = dot(vec3(r8.xyz), vec3(r8.xyz));
		//	r0.w = 1.f / sqrt(r0.w);
		//	r3.x = r0.w * r8.x;
		//	r3.y = r0.w * r8.y;
		//	r3.z = r0.w * r8.z;
		//	r0.w = dot(vec3(r1.xyz), vec3(r1.xyz));
		//	r0.w = 1.f / sqrt(r0.w);
		//	r1.x = r0.w * r1.x;
		//	r1.y = r0.w * r1.y;
		//	r1.z = r0.w * r1.z;
		//}
		//else {
		//	r3.x = 0;
		//	r3.y = 0;
		//	r3.z = 0;
		//	r1.x = 0;
		//	r1.y = 0;
		//	r1.z = 0;
		//}
		//r0.w = v11.y > 0.000000;
		//if (r0.w != 0) {
		//	r6.x = v2.y * cb2[1].x;
		//	r6.y = v2.y * cb2[1].y;
		//	r6.x = v2.x * cb2[0].x + r6.x;
		//	r6.y = v2.x * cb2[0].y + r6.y;
		//	r6.x = r6.x + cb2[2].x;
		//	r6.y = r6.y + cb2[2].y;
		//}
		//else {
		//	r6.x = v2.x;
		//	r6.y = v2.y;
		//}
		//r5.w = r2.x;
		//r5.x = dot(vec4(r4.xyzw), vec4(r5.xyzw));
		//r10.w = r2.y;
		//r5.y = dot(vec4(r4.xyzw), vec4(r10.xyzw));
		//r12.w = r2.z;
		//r5.z = dot(vec4(r4.xyzw), vec4(r12.xyzw));
		//r8.x = r5.x;// +cb0[4].x;
		//r8.y = r5.y;// +cb0[4].y;
		//r8.z = r5.z;// +cb0[4].z;
		//r0.w = 0.000000 < v7.w;
		//if (r0.w != 0) {
		//	r0.w = int32_t(v10.w);
		//	if (r0.w == 0) {
		//		r0.w = v7.w * v7.w;
		//		r0.w = r0.w * r0.w;
		//		//o9.w = min(r0.w, 1.000000);
		//		//o9.x = 0.500000;
		//		//o9.y = 0.500000;
		//		//o9.z = 0.500000;
		//		r9.x = r4.y;
		//	}
		//	else {
		//		r0.w = v6.x + 1.000000;
		//		r1.w = uint32_t(r0.w);
		//		r10.x = t0[uint32_t(r1.w)].x;
		//		r10.y = t0[uint32_t(r1.w)].y;
		//		r10.z = t0[uint32_t(r1.w)].z;
		//		r0.w = r0.w + 1.000000;
		//		r0.w = uint32_t(r0.w);
		//		r11.x = t0[uint32_t(r0.w)].x;
		//		r11.y = t0[uint32_t(r0.w)].y;
		//		r11.z = t0[uint32_t(r0.w)].z;
		//		r11.x = r8.x + -r11.x;
		//		r11.y = r8.y + -r11.y;
		//		r11.z = r8.z + -r11.z;
		//		r0.w = 0.900000 < r10.z;
		//		r11.w = r0.w ? 0 : r11.z;
		//		r0.w = dot(vec3(r11.xyw), vec3(r11.xyw));
		//		r0.w = sqrt(r0.w);
		//		r0.w = min(1.f, max(0.f, r0.w / 260.f));
		//		r0.w = -r0.w + 1.000000;
		//		r0.w = r0.w * r0.w;
		//		r0.w = r0.w * 2.000000;
		//		r0.w = min(r0.w, 1.f);
		//		r1.w = dot(vec3(r10.xyz), vec3(r10.xyz));
		//		r1.w = 1.f / sqrt(r1.w);
		//		r10.x = r1.w * r10.x;
		//		r10.y = r1.w * r10.y;
		//		r10.z = r1.w * r10.z;
		//		r1.w = dot(vec3(r0.xyz), vec3(r10.xyz));
		//		r1.w = r1.w * 0.500000;
		//		r1.w = min(1.f, max(0.f, r1.w + 0.5f));
		//		r1.w = r1.w * r1.w;
		//		r1.w = r1.w * 2.000000;
		//		r2.w = r10.z < 0.900000;
		//		r11.x = r10.x * r1.w;
		//		r11.y = r10.y * r1.w;
		//		r11.z = r10.z * r1.w;
		//		r11.x = r0.w * r11.x;
		//		r11.y = r0.w * r11.y;
		//		r11.z = r0.w * r11.z;
		//		r11.x = r11.x * 50.000000;
		//		r11.y = r11.y * 50.000000;
		//		r11.z = r11.z * 50.000000;
		//		r3.w = log(v7.w);
		//		r3.w = r3.w * 10.000000;
		//		r3.w = exp(r3.w);
		//		r11.x = r3.w * r11.x;
		//		r11.y = r3.w * r11.y;
		//		r11.z = r3.w * r11.z;
		//		r11.x = r4.x + r11.x;
		//		r11.y = r4.y + r11.y;
		//		r11.z = r4.z + r11.z;
		//		r0.x = r0.x + r10.x;
		//		r0.y = r0.y + r10.y;
		//		r0.z = r0.z + r10.z;
		//		r0.x = r0.x * r1.w;
		//		r0.y = r0.y * r1.w;
		//		r0.z = r0.z * r1.w;
		//		r0.x = r0.w * r0.x;
		//		r0.y = r0.w * r0.y;
		//		r0.z = r0.w * r0.z;
		//		r0.x = r0.x * 25.000000;
		//		r0.y = r0.y * 25.000000;
		//		r0.z = r0.z * 25.000000;
		//		r0.x = r3.w * r0.x;
		//		r0.y = r3.w * r0.y;
		//		r0.z = r3.w * r0.z;
		//		r0.x = r0.x + r4.x;
		//		r0.y = r0.y + r4.y;
		//		r0.z = r0.z + r4.z;
		//		r9.x = r2.w ? r11.y : r0.y;
		//		r9.y = r2.w ? r11.x : r0.x;
		//		r9.z = r2.w ? r11.z : r0.z;
		//		r0.x = r1.w * v7.w;
		//		r0.y = r0.x * r0.x;
		//		r0.y = r0.y * r0.y;
		//		r0.x = r0.y * r0.x;
		//		//o9.w = min(r0.x, 1.f);
		//		//o9.x = 0.392157;
		//		//o9.y = 0.627451;
		//		//o9.z = 0.941176;
		//		r4.x = r9.y;
		//		r4.z = r9.z;
		//	}
		//}
		//else {
		//	r0.x = v6.x + 2.000000;
		//	r0.y = v6.x + 1.000000;
		//	r0.x = uint32_t(r0.x);
		//	r0.y = uint32_t(r0.y);
		//	r10.x = t0[uint32_t(r0.x)].x;
		//	r10.y = t0[uint32_t(r0.x)].y;
		//	r10.z = t0[uint32_t(r0.x)].z;
		//	r10.w = t0[uint32_t(r0.x)].w;
		//	r0.x = dot(vec3(r5.xyz), vec3(r5.xyz));
		//	r0.x = 1.f / sqrt(r0.x);
		//	r0.x = r0.x * r5.x;
		//	r0.z = r0.x * r5.y;
		//	r0.w = r0.x * r5.z;
		//	r0.x = dot(vec3(r7.xyz), -vec3(r0.xzw));
		//	r0.z = -r0.x * 0.500000 + 1.500000;
		//	r5.w = r0.z * -r10.w;
		//	r0.x = min(1.f, max(0.f, -r0.x + 1.f));
		//	r10.w = r0.x * r10.w;
		//	r11.x = t0[uint32_t(r0.y)].x;
		//	r11.y = t0[uint32_t(r0.y)].y;
		//	r11.z = t0[uint32_t(r0.y)].z;
		//	r11.w = t0[uint32_t(r0.y)].w;
		//	r0.w = r0.x * r11.w;
		//	r12.x = v7.w == -1.000000;
		//	r12.y = v7.w == -2.000000;
		//	r12.z = v7.w == -3.000000;
		//	r12.w = v7.w == -4.000000;
		//	r13.x = float(v4.x); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.y = float(v4.y); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.z = float(v4.z); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.w = float(v4.w); // This was an unsigned to float call. Expect a preceding float()!
		//	r13.x = r13.x == r10.x;
		//	r13.y = r13.y == r10.x;
		//	r13.z = r13.z == r10.x;
		//	r13.w = r13.w == r10.x;
		//	r1.w = r13.x && v5.x;
		//	r2.w = r1.w + v5.y;
		//	r1.w = r13.y ? r2.w : r1.w;
		//	r2.w = r1.w + v5.z;
		//	r1.w = r13.z ? r2.w : r1.w;
		//	r2.w = r1.w + v5.w;
		//	r1.w = r13.w ? r2.w : r1.w;
		//	r11.w = r11.w * r1.w;
		//	r13.x = r11.x && r12.w;
		//	r13.y = r11.y && r12.w;
		//	r13.z = r11.z && r12.w;
		//	r13.w = r11.w && r12.w;
		//	r0.x = r11.x;
		//	r0.y = r11.y;
		//	r0.z = r11.z;
		//	r0.x = r12.z ? r0.x : r13.x;
		//	r0.y = r12.z ? r0.y : r13.y;
		//	r0.z = r12.z ? r0.z : r13.z;
		//	r0.w = r12.z ? r0.w : r13.w;
		//	r0.x = r12.y ? r10.x : r0.x;
		//	r0.y = r12.y ? r10.y : r0.y;
		//	r0.z = r12.y ? r10.z : r0.z;
		//	r0.w = r12.y ? r10.w : r0.w;
		//	r5.x = r10.x;
		//	r5.y = r10.y;
		//	r5.z = r10.z;
		//	//o9.x = r12.x ? r5.x : r0.x;
		//	//o9.y = r12.x ? r5.y : r0.y;
		//	//o9.z = r12.x ? r5.z : r0.z;
		//	//o9.w = r12.x ? r5.w : r0.w;
		//	r9.x = r4.y;
		//}
		//r0.x = -v0.y + v12.w;
		//r0.x = r0.x + 10.000000;
		//r0.x = r0.x * 0.100000;
		//r0.y = min(1.f, max(0.f, ceil(v12.w)));
		//r0.x = r0.y * r0.x;
		//r0.y = 0.000000 < v12.z;
		//r0.z = 0.000000 < r0.x;
		//r0.y = r0.z || r0.y;
		//r5.y = max(r0.x, v12.z);
		//r5.x = min(1.f, max(0.f, -r5.y + v12.y));
		////o8.x = r0.y ? r5.x : v12.y;
		////o8.y = r0.y ? r5.y : v12.z;
		////o8.z = floor(v10.w);
		//r5.x = v7.x * cb0[0].x;
		//r5.y = v7.x * cb0[0].y;
		//r5.z = v7.x * cb0[0].z;
		//r5.w = v7.x * cb0[0].w;
		//r10.x = v7.y * cb0[1].x;
		//r10.y = v7.y * cb0[1].y;
		//r10.z = v7.y * cb0[1].z;
		//r10.w = v7.y * cb0[1].w;
		//r5.x = r5.x + r10.x;
		//r5.y = r5.y + r10.y;
		//r5.z = r5.z + r10.z;
		//r5.w = r5.w + r10.w;
		//r10.x = v7.z * cb0[2].x;
		//r10.y = v7.z * cb0[2].y;
		//r10.z = v7.z * cb0[2].z;
		//r10.w = v7.z * cb0[2].w;
		//r5.x = r5.x + r10.x;
		//r5.y = r5.y + r10.y;
		//r5.z = r5.z + r10.z;
		//r5.w = r5.w + r10.w;
		//r10.x = v8.x * cb0[0].x;
		//r10.y = v8.x * cb0[0].y;
		//r10.z = v8.x * cb0[0].z;
		//r10.w = v8.x * cb0[0].w;
		//r11.x = v8.y * cb0[1].x;
		//r11.y = v8.y * cb0[1].y;
		//r11.z = v8.y * cb0[1].z;
		//r11.w = v8.y * cb0[1].w;
		//r10.x = r10.x + r11.x;
		//r10.y = r10.y + r11.y;
		//r10.z = r10.z + r11.z;
		//r10.w = r10.w + r11.w;
		//r11.x = v8.z * cb0[2].x;
		//r11.y = v8.z * cb0[2].y;
		//r11.z = v8.z * cb0[2].z;
		//r11.w = v8.z * cb0[2].w;
		//r10.x = r10.x + r11.x;
		//r10.y = r10.y + r11.y;
		//r10.z = r10.z + r11.z;
		//r10.w = r10.w + r11.w;
		//r11.x = v9.x * cb0[0].x;
		//r11.y = v9.x * cb0[0].y;
		//r11.z = v9.x * cb0[0].z;
		//r11.w = v9.x * cb0[0].w;
		//r12.x = v9.y * cb0[1].x;
		//r12.y = v9.y * cb0[1].y;
		//r12.z = v9.y * cb0[1].z;
		//r12.w = v9.y * cb0[1].w;
		//r11.x = r11.x + r12.x;
		//r11.y = r11.y + r12.y;
		//r11.z = r11.z + r12.z;
		//r11.w = r11.w + r12.w;
		//r12.x = v9.z * cb0[2].x;
		//r12.y = v9.z * cb0[2].y;
		//r12.z = v9.z * cb0[2].z;
		//r12.w = v9.z * cb0[2].w;
		//r11.x = r11.x + r12.x;
		//r11.y = r11.y + r12.y;
		//r11.z = r11.z + r12.z;
		//r11.w = r11.w + r12.w;
		//r12.x = r2.x * cb0[0].x;
		//r12.y = r2.x * cb0[0].y;
		//r12.z = r2.x * cb0[0].z;
		//r12.w = r2.x * cb0[0].w;
		//r13.x = r2.y * cb0[1].x;
		//r13.y = r2.y * cb0[1].y;
		//r13.z = r2.y * cb0[1].z;
		//r13.w = r2.y * cb0[1].w;
		//r12.x = r12.x + r13.x;
		//r12.y = r12.y + r13.y;
		//r12.z = r12.z + r13.z;
		//r12.w = r12.w + r13.w;
		//r2.x = r2.z * cb0[2].x;
		//r2.y = r2.z * cb0[2].y;
		//r2.z = r2.z * cb0[2].z;
		//r2.w = r2.z * cb0[2].w;
		//r2.x = r2.x + r12.x;
		//r2.y = r2.y + r12.y;
		//r2.z = r2.z + r12.z;
		//r2.w = r2.w + r12.w;
		//r2.x = r2.x + cb0[3].x;
		//r2.y = r2.y + cb0[3].y;
		//r2.z = r2.z + cb0[3].z;
		//r2.w = r2.w + cb0[3].w;
		//r5.x = r4.x * r5.x;
		//r5.y = r4.x * r5.y;
		//r5.z = r4.x * r5.z;
		//r5.w = r4.x * r5.w;
		//r9.x = r9.x * r10.x;
		//r9.y = r9.x * r10.y;
		//r9.z = r9.x * r10.z;
		//r9.w = r9.x * r10.w;
		//r5.x = r5.x + r9.x;
		//r5.y = r5.y + r9.y;
		//r5.z = r5.z + r9.z;
		//r5.w = r5.w + r9.w;
		//r9.x = r4.z * r11.x;
		//r9.y = r4.z * r11.y;
		//r9.z = r4.z * r11.z;
		//r9.w = r4.z * r11.w;
		//r5.x = r5.x + r9.x;
		//r5.y = r5.y + r9.y;
		//r5.z = r5.z + r9.z;
		//r5.w = r5.w + r9.w;
		//r2.x = r2.x * r4.w;
		//r2.y = r2.y * r4.w;
		//r2.z = r2.z * r4.w;
		//r2.w = r2.w * r4.w;
		
		//verts[i].Position.x = r2.x + r5.x;
		//verts[i].Position.y = r2.y + r5.y;
		//verts[i].Position.z = r2.z + r5.z;
		//cVert.Position.w = r2.w + r5.w;
		//o2.w = r4.y;
		//o2.x = r8.x;
		//o2.y = r8.y;
		//o2.z = r8.z;
		//o4.x = r3.x;
		//o4.y = r3.y;
		//o4.z = r3.z;
		//o4.w = 0;
		//o5.x = r1.x;
		//o5.y = r1.y;
		//o5.z = r1.z;
		//o5.w = 0;
		//o6.x = v11.x;
		//o6.y = v11.y;
		//o6.z = v11.z;
		//o6.w = v11.w;
		//o7.x = v6.x;
		//o7.y = v6.y;
		//o7.z = v6.z;
		//o7.w = v6.w;
		//o8.w = r0.x;
		//o10.x = v3.z;
		//o10.y = v3.y;
		//o10.z = v3.x;
		//o10.w = 0;
		//o11.x = 0;
		//o11.y = 0;
		//o11.z = 0;
		//o11.w = 0;
		//o12.x = 0;
		//o12.y = 0;
		//o12.z = 0;
		//o12.w = 0;
		//o13.x = 1.000000;
		//o13.y = 1.000000;
		//o13.z = 1.000000;
		//o13.w = 1.000000;
		//r6.z = v0.x;
		//o1.x = r6.x;
		//o1.y = r6.y;
		//o1.z = r6.z;
		//o3.x = r7.x;
		//o3.y = r7.y;
		//o3.z = r7.z;




		//verts[i].Position = r7.xyz;



































		//r0 = cVert.Tangents * vec4(2.f * 3.1415926535);
		//r0 += vec4(-3.1415926535);

		//r1 = sin(r0);
		//r2 = cos(r0);

		//r3.xy = abs(vec2(r1.yw)) * r2.xz;
		//r1.xy = r1.xz * abs(vec2(r1.yw));

		//r0.xyz = r1.xzw * r2.zyw;
		//r2.xyz = r3.wzy * r1.zwx;
		//r0.xyz = r0.xyz + -vec3(r2.xyz);

		//if (r0.w >= 0)
		//{
		//	r0.xyz *= vec3(-1);
		//}

		//// Int!
		//r0.w = vtxBindings.TexCoord4[vi].w;
		//r2.xyz = vtxBindings.TexCoord5[vi].xyz; // Normally, we subtract vecViewPos. But let's assume the camera is at the origin for now
		//r1.y = vtxBindings.TexCoord7[vi].x;

		//r2.w =  (r1.y < 0.f && r0.w < 1.f);

		//r4.x = r0.w > 1.f;
		//r4.y = false != false;
		//r4.y = r4.y == true;
		//
		//r0.w = r0.w == 1 && r4.y;

		//r4.y = cVert.BlendWeights.x + cVert.BlendWeights.y;
		//
		//r5.z = -r4.y + 1.f;
		//r5.x = 3.f;

		//r6.x = 4.f;
		//r6.z = cVert.BlendWeights.z;

		//if (!r0.w)
		//{
		//	r5.xz = r6.xz;
		//}

		//r6.xy = vec2(1, 1);
		//r6.z = cVert.BlendWeights.z;
		//
		//r5.y = cVert.BlendWeights.x;

		//r4.xzw = r4.x ? r6.xyz : r5.xyz;

		//r5.xz = r4.zw;
		//r5.yw = cVert.BlendWeights.yw;

		//r6 = r7 = r8 = r9 = vec4(0);

		//auto LoopCount = 0; // r4.z

		//while (true)
		//{
		//	if (LoopCount >= r4.x) { break; }
		//	r6.w = dot(r5, mat4(1.0)[LoopCount]);

		//	//if (LoopCount > r4.x && r6.w < 0) { break; }
		//	if (r6.w < 0) { break; }

		//	r0.w = LoopCount;
		//	r10.x = LoopCount < 1;
		//	r10.y = LoopCount < 2;
		//	r10.z = LoopCount < 3;

		//	r11.y = r0.w && r10.y;

		//	LoopCount += 1;
		//	r4.w = LoopCount - 3;

		//	r11.z = r10.y ? 0 : r4.w;
		//	r11.w = r10.z == 0.f;
		//	r11.x = r10.x;

		//	uint32_t r0wAsInt = ((r11.x && cVert.BlendWeights.x) || (r11.y && cVert.BlendWeights.y))
		//		|| ((r11.z && cVert.BlendWeights.z)	|| (r11.w && cVert.BlendWeights.w));
		//	r0.w = float(r0wAsInt << 2);

		//	r0.w += vtxBindings.TexCoord1[vi].z;
		//	
		//	// Load indices?
		//	r10.xyz = skinningMatrix[uint32_t(r0.w)];
		//	r10.xyz = r6.www * r10.xyz;
		//	r6.xyz = r6.xyz + r10.xyz;
		//	r10.xyz = r0.www + vec3(1, 2, 3);

		//	r11.xyz = skinningMatrix[uint32_t(r10.x)];
		//	r11.xyz = r6.www * r11.xyz;
		//	r7.xyz = r7.xyz + r11.xyz;

		//	r10.xyw = skinningMatrix[uint32_t(r10.y)];
		//	r10.xyw = r6.www * r10.xyw;
		//	r8.xyz = r8.xyz + r10.xyw;

		//	r10.xyz = skinningMatrix[uint32_t(r10.z)];
		//	r10.xyz = r6.www * r10.xyz;
		//	r9.xyz = r9.xyz + r10.xyz;
		//}

		////
		//r0.w = 0.02 < cVert.Colour.w;
		//r0.w = r0.w && r2.w;

		//if (r0.w)
		//{
		//	int32_t r1yAsInt = r1.y;
		//	r0.w = max(-r1yAsInt, r1yAsInt);
		//	r4.xzw = vec4(0);
		//	r5.xyz = vec4(0);
		//	r10.xyz = vec4(0);
		//	r11.xyz = vec4(0);
		//	r12.x = 0;

		//	LoopCount = 0; // r12.x

		//	while (true)
		//	{
		//		if (LoopCount >= 4) { break; }
		//		r1.y = LoopCount < 4;
		//		r2.w = dot(cVert.BlendWeights, mat4(1.0)[LoopCount]);
		//		r5.w = 0 < r2.w;
		//		r1.y = r1.y && r5.w;

		//		//if (LoopCount > 4 && r2.w < 0) { break; }
		//		if (r2.w < 0) { break; }

		//		r1.y = LoopCount;
		//		r13.x = LoopCount < 1;
		//		r13.y = LoopCount < 2;
		//		r13.z = LoopCount < 3;

		//		r14.y = r1.y && r13.y;
		//		
		//		LoopCount += 1;
		//		r12.xy += vec2(1, -3);
		//		
		//		r14.z = r13.y ? 0 : r12.y;
		//		r14.w = r13.z == 0;
		//		r14.x = r13.x;

		//		// and r13.xyzw, r14.xyzw, v4.xyzw
		//		// or r12.yz, r13.yywy, r13.xxzx
		//		// or r1.y, r12.z, r12.y
		//		r1yAsInt = ((r14.x && cVert.BlendWeights.x) || (r14.y && cVert.BlendWeights.y))
		//			|| ((r14.z && cVert.BlendWeights.z) || (r14.w && cVert.BlendWeights.w));

		//		r1yAsInt += r0.w;
		//		r1.y = float(r1yAsInt << 2);
		//		r1.y += vtxBindings.TexCoord1[vi].z;

		//		// Load indices?
		//		r12.yzw = skinningMatrix[uint32_t(r1.y)];
		//		r12.yzw = r2.www * r12.yzw;
		//		r4.xzw = r4.xzw + r10.xyz;
		//		r12.yzw = r1.yyy + vec3(1, 2, 3);

		//		r13.xyz = skinningMatrix[uint32_t(r12.y)];
		//		r13.xyz = r2.www * r13.xyz;
		//		r5.xyz = r5.xyz + r13.xyz;

		//		r10.xyw = skinningMatrix[uint32_t(r12.z)];
		//		r13.xyz = r2.www * r13.xyz;
		//		r10.xyz = r10.xyz + r10.xyz;

		//		r12.yzw = skinningMatrix[uint32_t(r12.w)];
		//		r12.yzw = r2.www * r12.yzw;
		//		r11.xyz = r11.xyz + r12.yzw;
		//	}

		//	r0.w = cVert.Colour.w;
		//	r0.w = r0.w * r0.w;
		//	r0.w = r0.w * r0.w;

		//	r4.xzw = -vec3(r6.xyz) + r4.xzw;
		//	r5.xyz = -vec3(r7.xyz) + r5.xyz;
		//	r10.xyz = -vec3(r8.xyz) + r10.xyz;
		//	r11.xyz = -vec3(r9.xyz) + r11.xyz;

		//	r4.xzw *= r0.www;
		//	r5.xyz *= r0.www;
		//	r10.xyz *= r0.www;
		//	r11.xyz *= r0.www;

		//	r6.xyz += r4.xzw;
		//	r7.xyz += r5.xyz;
		//	r8.xyz += r10.xyz;
		//	r9.xyz += r11.xyz;
		//}

		//// r6,7,8,9 contain a matrix, I think

		//r4.xzw = r6.xyz * cVert.Position.x;
		//r5.xyz = r7.xyz * cVert.Position.y;
		//r4.xzw += r5.xyz;

		//r5.xyz = r8.xyz * cVert.Position.z;
		//r4.xzw += r5.xyz;
		//r5.xyz = r9.xyz + r4.xzw;

		//r0.w = r4.y + cVert.BlendWeights.z;
		//r5.w = r0.w + cVert.BlendWeights.w;

		//r4.xyzw = r5.xyzw / r5.wwww;

		//r5.x = vtxBindings.TexCoord2[vi].x;
		//r5.y = vtxBindings.TexCoord3[vi].x;
		//r5.z = vtxBindings.TexCoord3[vi].x;
		//r9.x = dot(vec3(r6.xyz), vec3(r5.xyz));
		//
		//r10.x = vtxBindings.TexCoord2[vi].y;
		//r10.y = vtxBindings.TexCoord3[vi].y;
		//r10.z = vtxBindings.TexCoord3[vi].y;
		//r11.x = dot(vec3(r6.xyz), vec3(r10.xyz));

		//r12.x = vtxBindings.TexCoord2[vi].z;
		//r12.y = vtxBindings.TexCoord3[vi].z;
		//r12.z = vtxBindings.TexCoord3[vi].z;

		//r6.x = dot(vec3(r6.xyz), vec3(r12.xyz));
		//r9.y = dot(vec3(r7.xyz), vec3(r5.xyz));
		//r11.y = dot(vec3(r7.xyz), vec3(r10.xyz));
		//r6.y = dot(vec3(r7.xyz), vec3(r12.xyz));

		//r9.z = dot(vec3(r8.xyz), vec3(r5.xyz));
		//r11.z = dot(vec3(r8.xyz), vec3(r10.xyz));
		//r6.z = dot(vec3(r8.xyz), vec3(r12.xyz));
		//r7.x = dot(vec3(r0.xyz), vec3(r9.xyz));

		//r7.y = dot(vec3(r0.xyz), vec3(r11.xyz));
		//r7.z = dot(vec3(r0.xyz), vec3(r6.xyz));
		//r0.w = dot(vec3(r7.xyz), vec3(r7.xyz));

		//r0.w = 1.f / sqrt(r0.w);
		//r7.xyz = r0.www * r7.xyz;

		
	}

	/*
		0x00001360: dp3 r7.y, r0.xyzx, r11.xyzx
		0x0000137C: dp3 r7.z, r0.xyzx, r6.xyzx
		0x00001398: dp3 r0.w, r7.xyzx, r7.xyzx
		0x000013B4: rsq r0.w, r0.w
	*/










//#pragma omp parallel for
//	for (int64_t i = 0; i < verts.size(); ++i)
//	{
//		// Get out vert
//		auto cVert = verts[i];
//		glm::vec4 vPos(cVert.Position, 1.0f);
//		glm::vec4 vNrm(cVert.Tangents.xyz(), 0.0f);
//
//
//		// Get the first bone index and apply it
//		auto index = cVert.BoneIndices.x;
//		glm::vec4 oPos = (skinningMatrix[index] * vPos) * cVert.BlendWeights.x;
//		glm::vec4 oNrm = (skinningMatrix[index] * vNrm) * cVert.BlendWeights.x;
//
//		index = cVert.BoneIndices.y;
//		oPos = (skinningMatrix[index] * vPos) * cVert.BlendWeights.y + oPos;
//		oNrm = (skinningMatrix[index] * vNrm) * cVert.BlendWeights.y + oPos;
//
//		index = cVert.BoneIndices.z;
//		oPos = (skinningMatrix[index] * vPos) * cVert.BlendWeights.z + oPos;
//		oNrm = (skinningMatrix[index] * vNrm) * cVert.BlendWeights.z + oPos;
//
//		index = cVert.BoneIndices.w;
//		oPos = (skinningMatrix[index] * vPos) * cVert.BlendWeights.w + oPos;
//		oNrm = (skinningMatrix[index] * vNrm) * cVert.BlendWeights.w + oPos;
//
//		verts[i].Position = oPos.xyz();
//		verts[i].Tangents = glm::normalize(oNrm);// *glm::inverseTranspose(glm::mat4()));
//	}
	// Like a GPU

	PRINT_SSO("Skinning Completed!!!");
}


void WritePoly
(
	std::vector<FChimeraVertex>& verts,
	std::vector<uint32_t>& indices,
	const std::string& saveLocation,
	std::vector<glm::vec4>& skinningMatrix,
	FBDOShaderBindings& vtxBindings,
	DrawBufferInformation& dbi
)
{
	std::ofstream plyStream(saveLocation, std::ios::binary);

	// Ply Header
	plyStream << "ply" << std::endl;
	//plyStream << "format binary_little_endian 1.0" << std::endl;
	plyStream << "format ascii 1.0" << std::endl;

	// VertInfo
	plyStream << "element vertex " << verts.size() << std::endl;
	plyStream << "property float x" << std::endl; // Pos
	plyStream << "property float y" << std::endl;
	plyStream << "property float z" << std::endl;
	//plyStream << "property float red" << std::endl; // Colour
	//plyStream << "property float green" << std::endl;
	//plyStream << "property float blue" << std::endl;
	plyStream << "property uchar red" << std::endl; // Colour
	plyStream << "property uchar green" << std::endl;
	plyStream << "property uchar blue" << std::endl;
	//plyStream << "property float alpha" << std::endl;
	plyStream << "property float s" << std::endl; // Coords
	plyStream << "property float t" << std::endl;
	plyStream << "property float nx" << std::endl; // Colour
	plyStream << "property float ny" << std::endl;
	plyStream << "property float nz" << std::endl;
	//plyStream << "property float normalW" << std::endl;
	//plyStream << "property float blendWeightX" << std::endl; // BlendWeights
	//plyStream << "property float blendWeightY" << std::endl; // BlendWeights
	//plyStream << "property float blendWeightZ" << std::endl; // BlendWeights
	//plyStream << "property float blendWeightW" << std::endl; // BlendWeights
	//plyStream << "property ushort blendIndexX" << std::endl; 
	//plyStream << "property ushort blendIndexY" << std::endl;
	//plyStream << "property ushort blendIndexZ" << std::endl;
	//plyStream << "property ushort blendIndexW" << std::endl;

	// Face Info
	plyStream << "element face " << indices.size() / 3 << std::endl;
	plyStream << "property list uchar uint vertex_indices" << std::endl; // Pos

	plyStream << "end_header" << std::endl;
	

	// Data for verts
	for (uint32_t v = 0; v < verts.size(); ++v)
	{
		auto currentVert = &verts[v];

		plyStream << currentVert->Position.x << " " <<
			currentVert->Position.y << " " <<
			currentVert->Position.z << " " <<
			uint32_t(currentVert->Colour.r * 256.f) << " " <<
			uint32_t(currentVert->Colour.a * 256.f) << " " <<
			uint32_t(currentVert->Colour.g * 256.f) << " " <<
			currentVert->TexCoords.x << " " <<
			currentVert->TexCoords.y << " " <<

			currentVert->Tangents.x << " " <<
			currentVert->Tangents.y << " " <<
			currentVert->Tangents.z <<	
			std::endl;

		//plyStream.write(
		//	reinterpret_cast<char *>(&(currentVert->Position)),
		//	sizeof(float) * 3
		//);

		//plyStream.write(
		//	reinterpret_cast<char*>(&(currentVert->Colour)),
		//	sizeof(float) * 4
		//);

		//plyStream.write(
		//	reinterpret_cast<char*>(&(currentVert->TexCoords)),
		//	sizeof(float) * 2
		//);

		//plyStream.write(
		//	reinterpret_cast<char*>(&(currentVert->Tangents)),
		//	sizeof(float) * 4
		//);

		//plyStream.write(
		//	reinterpret_cast<char*>(&(currentVert->BlendWeights)),
		//	sizeof(float) * 4
		//);

		//plyStream.write(
		//	reinterpret_cast<char*>(&(currentVert->BoneIndices)),
		//	sizeof(uint16_t) * 4
		//);
	}

	// indices
	uint8_t temp = 3;
	for (uint32_t i = 0; i < indices.size() / 3; ++i)
	{
		plyStream << "3 " << indices[i*3] << " " <<
			indices[i*3+1] << " " <<
			indices[i*3+2] << std::endl;
		//plyStream.write(
		//	reinterpret_cast<char*>(&(temp)),
		//	sizeof(uint8_t)
		//);

		//plyStream.write(
		//	reinterpret_cast<char*>(&(indices.data()[i * 3])),
		//	sizeof(uint32_t) * 3
		//);
	}


	plyStream.close();
}


#pragma region VS_RipFunctions

void writeMeshOBJ
(
	std::vector<FChimeraVertex> &verts,
	std::vector<uint32_t> &indices,
	const std::string& saveLocation,
	std::vector<glm::vec4>& skinningMatrix,
	FBDOShaderBindings& vtxBindings,
	DrawBufferInformation& dbi
)
{
	// Write using OBJ export
	std::ofstream objStream(saveLocation + ".obj");

	objStream << std::fixed << std::showpoint;
	objStream << std::setprecision(8);
	uint32_t i;

	// Write all vert positions in VB order
	for (i = 0; i < verts.size(); i++)
	{
		objStream << "v " << verts[i].Position.x << " " << verts[i].Position.y << " " << verts[i].Position.z << " 1" << std::endl;
	}

	for (i = 0; i < verts.size(); i++)
	{
		objStream << "vt " << verts[i].TexCoords.x << " " << verts[i].TexCoords.y << std::endl;
	}

	// Write all face data, using full desc
	for (i = 0; i < indices.size() / 3; i++)
	{
		// f v/vt/vn v/vt/vn v/vt/vn
		objStream << "f " <<
			1 + indices[i * 3] << "/" << 1 + indices[i * 3] << " " <<
			1 + indices[i * 3 + 1] << "/" << 1 + indices[i * 3 + 1] << " " <<
			1 + indices[i * 3 + 2] << "/" << 1 + indices[i * 3 + 2] << std::endl;
	}

	objStream.close();

	WritePoly(verts, indices, saveLocation + ".ply", skinningMatrix, vtxBindings, dbi);

	// Do skinning transform?
	if (skinningMatrix.size() > 100)
	{
		ApplySkin(verts, skinningMatrix, vtxBindings, dbi);

		// Write using OBJ export
		std::ofstream objStream(saveLocation + "." + std::to_string(vtxBindings.meshID) + ".applied.obj");

		objStream << std::fixed << std::showpoint;
		objStream << std::setprecision(8);
		uint32_t i;

		// Write all vert positions in VB order
		for (i = 0; i < verts.size(); i++)
		{
			objStream << "v " << verts[i].Position.x << " " << verts[i].Position.y << " " << verts[i].Position.z << " 1" << std::endl;
		}

		for (i = 0; i < verts.size(); i++)
		{
			objStream << "vt " << verts[i].TexCoords.x << " " << verts[i].TexCoords.y << std::endl;
		}

		// Write all face data, using full desc
		for (i = 0; i < indices.size() / 3; i++)
		{
			// f v/vt/vn v/vt/vn v/vt/vn
			objStream << "f " <<
				1 + indices[i * 3] << "/" << 1 + indices[i * 3] << " " <<
				1 + indices[i * 3 + 1] << "/" << 1 + indices[i * 3 + 1] << " " <<
				1 + indices[i * 3 + 2] << "/" << 1 + indices[i * 3 + 2] << std::endl;
		}

		objStream.close();
	}

	WritePoly(verts, indices, saveLocation + "." + std::to_string(vtxBindings.meshID) + ".skinned.ply", skinningMatrix, vtxBindings, dbi);
}


void createModel
(
	VertexBufferInformation &vbi,
	IndexBufferInformation &ibi,
	DrawBufferInformation &dbi,
	const std::string& saveLocation,
	std::vector<glm::vec4>& skinningMatrix,
	FBDOShaderBindings& vtxBindings
)
{
	std::vector<FChimeraVertex> vertices;
	std::vector<uint32_t> indices;
	const auto ptr = reinterpret_cast<VBStruct *>((vbi.VertexBufferData));

	PRINT_DEBUG("Struct is " + std::to_string(sizeof(VBStruct)) + " bytes vs " + std::to_string(vbi.VertexStructureWidth));

	if (dbi.StartIndex > ibi.BufferSize)
	{
		PRINT_SSO("Skipping due to SARS");
		return;
	}

	if (sizeof(VBStruct) != vbi.VertexStructureWidth) return;

	std::vector<IndexBufferType> indexMap;
	for (uint32_t i = 0; i < dbi.IndexCount; ++i) {

		// Might not be 16 in all cases. Engine dependant
		IndexBufferType a = reinterpret_cast<IndexBufferType*>(ibi.IndexBufferData)[i + dbi.StartIndex] + dbi.BaseVertex;

		if (a == UINT32_MAX) continue; // Skip this invalid index

		if ((a * sizeof(VBStruct)) > vbi.BufferSize)
		{
			PRINT_SSO("Skipping due to Covid-19");
			return;
			//throw std::exception("G");
		}

		const std::vector<IndexBufferType>::iterator it = std::find(indexMap.begin(), indexMap.end(), a);
		if (it == indexMap.end()) {
			indexMap.push_back(a);

			// Read element a
			auto vert = ptr[a];
			
			FChimeraVertex convertedType
			(
				a,
				vert.GetPosition(),
				vert.GetTexCoord(),
				vert.GetTangents(),
				vert.GetBoneIndices(),
				vert.GetBlendWeights(),
				vert.GetColour()
			);

			vertices.emplace_back(convertedType);
			indices.emplace_back(static_cast<uint32_t>(indexMap.size() - 1));

		}
		else {
			indices.push_back(static_cast<uint32_t>(std::distance(indexMap.begin(), it)));
		}
	}

	writeMeshOBJ(vertices, indices, saveLocation, skinningMatrix, vtxBindings, dbi);
}

#pragma endregion 

char * loadFileToBuffer(std::string &&fileToLoad)
{
	std::ifstream fileLoader = std::ifstream(fileToLoad, std::ios::binary | std::ios::ate);

	// Check File
	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg, 0);

		// Create Buffer for VertexData
		const auto vertexBuffer = new char[fileSize];
		fileLoader.read(vertexBuffer, fileSize);

		return vertexBuffer;
	}
	return nullptr;
}

FPosition ABlackDesertVertexType::GetPosition()
{
	FPosition pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = this->z;
	return pos;
}

FTexCoord ABlackDesertVertexType::GetTexCoord()
{
	FTexCoord tex;
	tex.x = HalfFloatToFloat(this->u);
	tex.y = HalfFloatToFloat(this->v);
	return tex;
}

FTangents ABlackDesertVertexType::GetTangents()
{
	FTangents retVal;
	retVal.x = normal_unorm[0] / 256.f;
	retVal.y = normal_unorm[1] / 256.f;
	retVal.z = normal_unorm[2] / 256.f;
	retVal.w = normal_unorm[3] / 256.f;
	return retVal;
}

FBlendWeights ABlackDesertVertexType::GetBlendWeights()
{
	// Each weight is between 0 and 255 inclusive.
	// Cast to float
	FBlendWeights retVal{};
	retVal.x = blendweight_unorm[0] / 256.f;
	retVal.y = blendweight_unorm[1] / 256.f;
	retVal.z = blendweight_unorm[2] / 256.f;
	retVal.w = blendweight_unorm[3] / 256.f;

	return retVal;
}

FBoneIndices ABlackDesertVertexType::GetBoneIndices()
{
	FBoneIndices retVal{};

	retVal.x = blendIndices_uint[0];
	retVal.y = blendIndices_uint[1];
	retVal.z = blendIndices_uint[2];
	retVal.w = blendIndices_uint[3];

	return retVal;
}

glm::vec4 ABlackDesertVertexType::GetColour()
{
	glm::vec4 retVec;

	retVec.x = color_unorm_bgr[0] / 256.f;
	retVec.y = color_unorm_bgr[1] / 256.f;
	retVec.z = color_unorm_bgr[2] / 256.f;
	retVec.w = color_unorm_bgr[3] / 256.f;

	return retVec;
}

FPosition ANierAutomataVertexType::GetPosition()
{
	FPosition pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = this->z;
	return pos;
}

FTexCoord ANierAutomataVertexType::GetTexCoord()
{
	FTexCoord tex;
	tex.x = HalfFloatToFloat(this->u);
	tex.y = HalfFloatToFloat(this->v);
	return tex;
}

FTangents ANierAutomataVertexType::GetTangents()
{
	FTangents retVal;
	retVal.x = tangent_unorm[0] / 256.f;
	retVal.y = tangent_unorm[1] / 256.f;
	retVal.z = tangent_unorm[2] / 256.f;
	retVal.w = tangent_unorm[3] / 256.f;
	return retVal;
}

FBlendWeights ANierAutomataVertexType::GetBlendWeights()
{
	FBlendWeights retVal{};
	retVal.x = blendweight_unorm[0] / 256.f;
	retVal.y = blendweight_unorm[1] / 256.f;
	retVal.z = blendweight_unorm[2] / 256.f;
	retVal.w = blendweight_unorm[3] / 256.f;

	return retVal;
}

FBoneIndices ANierAutomataVertexType::GetBoneIndices()
{
	FBoneIndices retVal{};

	retVal.x = blendIndices_uint[0];
	retVal.y = blendIndices_uint[1];
	retVal.z = blendIndices_uint[2];
	retVal.w = blendIndices_uint[3];

	return retVal;
}

glm::vec4 ANierAutomataVertexType::GetColour()
{
	return glm::vec4(0);
}

FPosition AOblivionVertexType::GetPosition()
{
	FPosition pos;
	pos.x = this->x;
	pos.y = this->y;
	pos.z = this->z;
	return pos;
}

FTexCoord AOblivionVertexType::GetTexCoord()
{
	return TexCoord;
}

FTangents AOblivionVertexType::GetTangents()
{
	return glm::vec4(Tangents, 0);
}

FBlendWeights AOblivionVertexType::GetBlendWeights()
{
	return glm::vec4(BlendWeights, 0);
}

FBoneIndices AOblivionVertexType::GetBoneIndices()
{
	FBoneIndices retVal{};

	retVal.x = BlendIndices[0];
	retVal.y = BlendIndices[1];
	retVal.z = BlendIndices[2];
	retVal.w = BlendIndices[3];

	return retVal;
}

glm::vec4 AOblivionVertexType::GetColour()
{
	return Colour;
}

void Chimera_ProcessRenderInfo(const std::filesystem::path& item)
{
	// These should be vmrinfo files, I honestly don't care if the extension doesn't match
	std::ifstream masterFile(item.string(), std::ifstream::in);
	std::string line;

	VertexBufferInformation vbInformation{};
	VertexShaderInformation vsInformation{};
	IndexBufferInformation  ibInformation{};

	std::unordered_map<uint32_t, char *> loadedBuffers;


	//PRINT_SSO("Rejected Job " + item.filename().string());
	//return;

	uint32_t counter = 0;

	// Vertex Buffer info is in the RINFO files
	{
		while (std::getline(masterFile, line))
		{
			std::string bufType;
			std::string buf1stParam;
			std::string buf2ndParam;
			std::string buf3rdParam;
			std::string buf4thParam;
			std::string buf5thParam;
			std::string buf6thParam;
			std::string buf7thParam;
			std::stringstream ls(line);
			// Get Type, Size and Stride
			std::getline(ls, bufType, ',');
			std::getline(ls, buf1stParam, ',');
			std::getline(ls, buf2ndParam, ',');

			// Dump BindFlags
			std::getline(ls, buf3rdParam, ',');

			// Dump Usage
			std::getline(ls, buf4thParam, ',');

			// Get Offset, VertStride and disk Index
			std::getline(ls, buf5thParam, ',');
			std::getline(ls, buf6thParam, ',');
			std::getline(ls, buf7thParam, ',');

			if (bufType == "VertexInfo")
			{
				
				vbInformation.BufferSize = stoul(buf1stParam);
				vbInformation.BufferOffset = std::stoul(buf5thParam);
				vbInformation.DiskBufferNumber = std::stoul(buf7thParam);
				vbInformation.BufferStride = std::stoul(buf2ndParam);
				vbInformation.VertexStructureWidth = std::stoul(buf6thParam);

				// Load Vertex Buffer
				// Check if previous information is bound
				// Delete old
				if (vbInformation.VertexBufferData) delete[] vbInformation.VertexBufferData;

				const auto vertBuffer = loadFileToBuffer(item.parent_path().string() + "/" + std::to_string(vbInformation.DiskBufferNumber) + ".vmrvb");
				if (vertBuffer)
					vbInformation.VertexBufferData = vertBuffer;
				else
				{
					PRINT_SSO("Vertex Buffer failed to load correctly");
				}

				vbInformation.isValid = true;
			}
			else if (bufType == "DrawIndexed")
			{
				uint32_t requestedIndexBuffer = std::stoul(buf1stParam);
				// Create a new DrawBufferInformation
				DrawBufferInformation dbi{};
				dbi.IndexCount = std::stoul(buf2ndParam);
				dbi.StartIndex = std::stoul(buf3rdParam);
				if(!buf4thParam.empty())
					dbi.BaseVertex = std::stoul(buf4thParam);

				ibInformation.DiskBufferNumber = requestedIndexBuffer; // Out of order in rinfo files
				ibInformation.BufferStride = 0; // 

				const auto location = loadedBuffers.find(requestedIndexBuffer);
				if (location == loadedBuffers.end())
				{
					// Load the buffer
					const auto indexBuffer = loadFileToBuffer(item.parent_path().string() + "/" + std::to_string(ibInformation.DiskBufferNumber) + ".vmrib");
					if (indexBuffer)
					{
						ibInformation.IndexBufferData = indexBuffer;
						loadedBuffers.emplace(std::make_pair(requestedIndexBuffer, indexBuffer));
					}
					else
					{
						PRINT_SSO("Index Buffer failed to load correctly");
					}
				}
				else
				{
					ibInformation.IndexBufferData = location->second;
				}


				//ibInformation.VertexStructureWidth = std::stoul(vertStride);
				ibInformation.isValid = true;

				//createModel(vbInformation, ibInformation, dbi, item.string() + "." + std::to_string(++counter));
			}
		}
	}

	if(vbInformation.VertexBufferData) delete[] vbInformation.VertexBufferData;
}

void Chimera_ProcessVMRInfo(const std::filesystem::path& item)
{
	// These should be vmrinfo files, I honestly don't care if the extension doesn't match
	std::ifstream masterFile(item.string(), std::ifstream::in);
	std::string line;

	VertexBufferInformation vbInformation{};
	VertexShaderInformation vsInformation{};
	IndexBufferInformation  ibInformation{};
	DrawBufferInformation drawBufferInformation{};

	// Read CSV
	{
		std::string bufType;
		std::string buf1stParam;
		std::string buf2ndParam;
		std::string buf3rdParam;
		std::string buf4thParam;
		std::string buf5thParam;
		std::string buf6thParam;
		std::string buf7thParam;

		std::getline(masterFile, line); // Drop Header Row
		while (std::getline(masterFile, line))
		{
			std::stringstream ls(line);


			// Get Type, Size and Stride
			std::getline(ls, bufType, ',');
			std::getline(ls, buf1stParam, ',');
			std::getline(ls, buf2ndParam, ',');

			// Dump BindFlags
			std::getline(ls, buf3rdParam, ',');

			// Dump Usage
			std::getline(ls, buf4thParam, ',');

			// Get Offset, VertStride and disk Index
			std::getline(ls, buf5thParam, ',');
			std::getline(ls, buf6thParam, ',');
			std::getline(ls, buf7thParam, ',');

			if (bufType == "Vertex")
			{
				vbInformation.BufferSize = std::stoul(buf1stParam);
				vbInformation.BufferOffset = std::stoul(buf5thParam);
				vbInformation.DiskBufferNumber = std::stoul(buf7thParam);
				vbInformation.BufferStride = std::stoul(buf2ndParam);
				vbInformation.VertexStructureWidth = std::stoul(buf6thParam);
				vbInformation.isValid = true;
			}
			else if (bufType == "Index")
			{
				ibInformation.BufferSize = std::stoul(buf1stParam);
				ibInformation.BufferOffset = std::stoul(buf5thParam);
				ibInformation.DiskBufferNumber = std::stoul(buf7thParam);
				ibInformation.BufferStride = std::stoul(buf2ndParam);
				//ibInformation.VertexStructureWidth = std::stoul(vertStride);
				ibInformation.isValid = true;
			}
			else if (bufType == "VSShader")
			{
				vsInformation.DiskBufferNumber = std::stoul(buf7thParam);
				vsInformation.AnimationDataWidth = 128; // Number of elements in the area total, can be parsed from shader
				vsInformation.AnimationDataFormat = AnimDataFormat::float4x3;
				vsInformation.AnimationVaryingLocation = 0; // No idea where in the varying this is...
			}
			else if (bufType == "DrawInfo")
			{
				// Fill draw information.
				// Gets messy because the names don't fit for this single row
				drawBufferInformation.IndexCount = std::stoul(buf1stParam);
				drawBufferInformation.StartIndex = std::stoul(buf2ndParam);
				drawBufferInformation.BaseVertex = std::stol(buf3rdParam);
			}
		}
	}

	// In order to load a model, at least VB and IB must be valid
	if (!vbInformation.isValid || !ibInformation.isValid)
	{
		PRINT_SSO("Rejected Job " + item.filename().string());

		if (!ibInformation.isValid) PRINT_DEBUG("IndexBuffer is invalid");
		if (!vbInformation.isValid) PRINT_DEBUG("VertexBuffer is invalid");

		return;
	}

	{
		// Load Vertex Buffer
		const auto vertBuffer = loadFileToBuffer(item.parent_path().string() + "/" + std::to_string(vbInformation.DiskBufferNumber) + ".vmrvb");
		if (vertBuffer)
			vbInformation.VertexBufferData = vertBuffer;
		else
			return;

		const auto indexBuffer = loadFileToBuffer(item.parent_path().string() + "/" + std::to_string(ibInformation.DiskBufferNumber) + ".vmrib");
		if (indexBuffer)
			ibInformation.IndexBufferData = indexBuffer;
		else
			return;		
	}

	//createModel(vbInformation, ibInformation, drawBufferInformation, item.string());

	// Clean up
	delete[] vbInformation.VertexBufferData;
	delete[] ibInformation.IndexBufferData;
}

void LoadDrawBuffer(const std::filesystem::path& item, DrawBufferInformation& dBuffer)
{
	std::ifstream fileLoader = std::ifstream(item, std::ios::binary | std::ios::ate);

	// Check File
	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();

		if (fileSize < 16)
		{
			return;
		}

		fileLoader.seekg(std::ios::beg, 0);

		char byteBufferData[20];
		memset(byteBufferData, 0, 20);

		fileLoader.read(byteBufferData, fileSize);

		auto asBuffer = reinterpret_cast<DrawBufferInformation*>(byteBufferData);

		dBuffer.BaseVertex = asBuffer->BaseVertex;
		dBuffer.IndexCount = asBuffer->IndexCount;
		dBuffer.StartIndex = asBuffer->StartIndex;
		dBuffer.CallType = asBuffer->CallType;
		dBuffer.PrimitiveType = asBuffer->PrimitiveType;

		// Catch the strange world that is D3D9
		if (dBuffer.PrimitiveType == 4)
		{
			dBuffer.IndexCount *= 3;
		}

		PRINT_DEBUG("\tCall Type is " << reinterpret_cast<uint32_t*>(byteBufferData)[3]);

	}
	return;
}

void IsReal(const std::filesystem::path& item, std::unordered_map<FHashKey, std::filesystem::path>& fileMap)
{
	std::ifstream fileLoader = std::ifstream(item, std::ios::binary | std::ios::ate);

	// Check File
	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg);

		FHashKey hash{};
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(FHashKey));

		if (fileSize > 40)
		{
			PRINT_SSO("File " << item.string() << " is real.");
			fileLoader.close();
		}
		else
		{
			fileLoader.close();
			PRINT_SSO("File " << item.string() << " is a redirect.");
			// Lookup
			auto loc = fileMap.find(hash);

			if (loc != fileMap.end())
			{
				IsReal(loc->second, fileMap);
			}
		}
	}
}

std::vector<uint8_t> LoadShader(const std::filesystem::path& item, std::unordered_map<FHashKey, std::filesystem::path>& fileMap)
{
	std::vector<uint8_t> rVec;
	std::ifstream fileLoader = std::ifstream(item, std::ios::binary | std::ios::ate);

	// Check File
	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg);

		FHashKey hash{};
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(FHashKey));

		if (fileSize > 32)
		{
			PRINT_SSO("File " << item.string() << " is real.");

			rVec.resize(fileSize - 32);
			fileLoader.read(reinterpret_cast<char*>(rVec.data()), rVec.size());

			fileLoader.close();
		}
		else
		{
			fileLoader.close();
			PRINT_SSO("File " << item.string() << " is a redirect.");
			// Lookup
			auto loc = fileMap.find(hash);

			if (loc != fileMap.end())
			{
				return LoadShader(loc->second, fileMap);
			}
		}
	}
}

bool Chimera_ProcessHashBuffer(const std::filesystem::path& item, std::unordered_map<FHashKey, std::filesystem::path>& fileMap, std::vector<uint8_t> &rVec)
{
	PRINT_DEBUG("\t\tChecking " << item.string());
	std::ifstream fileLoader = std::ifstream(item, std::ios::binary | std::ios::ate);

	// Check File
	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg);

		FHashKey hash{};
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(FHashKey));

		// Clear this info too
		uint64_t info;
		fileLoader.read(reinterpret_cast<char*>(&info), sizeof(uint64_t));

		if (fileSize > 40)
		{
			// This is a full file
			// Just read it all

			rVec.resize(fileSize - 40);
			fileLoader.read(reinterpret_cast<char*>(rVec.data()), rVec.size());

			fileLoader.close();
			return true;
		}
		else
		{
			fileLoader.close();
			// Lookup
			auto loc = fileMap.find(hash);

			if(loc != fileMap.end())
			{
				return Chimera_ProcessHashBuffer(loc->second, fileMap, rVec);
			}
		}
	}
	return false;
}


void LoadIndexBuffer(const std::filesystem::path& item, IndexBufferInformation& indexBuffer)
{
	indexBuffer.IndexBufferData = loadFileToBuffer(item.string());
}

void Chimera_LoadImageFromHash(
	const std::filesystem::path& item, std::unordered_map<FHashKey, std::filesystem::path>& fileMap,
	std::vector<uint8_t> &imageVector,
	FTextureInfo &texInfo
)
{
	PRINT_DEBUG("\t\tChecking " << item.string());
	std::ifstream fileLoader = std::ifstream(item, std::ios::binary | std::ios::ate);

	// Check File
	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg);

		if (fileSize > sizeof(FHashKey) + sizeof(FTextureInfo))
		{

			FHashKey hash{};
			fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(FHashKey));

			fileLoader.read(reinterpret_cast<char*>(&texInfo), sizeof(FTextureInfo));


			imageVector.resize(fileSize - (sizeof(FHashKey) + sizeof(FTextureInfo)));
			fileLoader.read(reinterpret_cast<char*>(imageVector.data()), imageVector.size());
		}
		fileLoader.close();
	}
}

void Chimera_Image(const std::filesystem::path& item, std::unordered_map<FHashKey, std::filesystem::path>& fileMap)
{
	PRINT_DEBUG("\t\Imaging " << item.string());
	std::ifstream fileLoader = std::ifstream(item, std::ios::binary | std::ios::ate);
	std::vector<uint8_t> imageVector;
	FTextureInfo texInfo;

	// Check File
	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg);

		FHashKey hash{};
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(FHashKey));

		// Clear this info too
		fileLoader.read(reinterpret_cast<char*>(&texInfo), sizeof(FTextureInfo));

		if (fileSize > sizeof(FHashKey) + sizeof(FTextureInfo))
		{
			// This is a full file
			// Just read it all

			imageVector.resize(fileSize - (sizeof(FHashKey) + sizeof(FTextureInfo)));
			fileLoader.read(reinterpret_cast<char*>(imageVector.data()), imageVector.size());
		}
		else
		{
			// Lookup
			auto loc = fileMap.find(hash);

			if (loc != fileMap.end())
			{
				Chimera_LoadImageFromHash(loc->second, fileMap, imageVector, texInfo);
			}
		}

		fileLoader.close();
	}

	if (imageVector.size() == 0)
	{
		return;
	}

	auto outImage = ProcessImage(imageVector, texInfo);
	SerialiseImage(outImage, texInfo, item.string());
}


void Chimera_DX
(
	std::filesystem::path& item,
	std::unordered_map<FHashKey, std::filesystem::path>& fileMap
)
{



	//// DirectX it
	//DXRenderer dxRender;
	////dxRender.AddVertexBuffer();
	////dxRender.AddConstVertexBuffer();
	//dxRender.SetVertexShader(LoadShader(item / "vertex.shader", fileMap));
	//

}


void fixTriangeStrip(
	std::vector<uint8_t> &incomingVerts,
	std::vector<uint8_t> &incomingIndices
)
{
	auto numTriangles = (incomingVerts.size() / sizeof(VBStruct)) - 2;
	std::vector<uint8_t> verts;
	verts.resize(numTriangles * 3 * sizeof(VBStruct));

	std::vector<uint8_t> indices;
	indices.resize(numTriangles * 3 * 2);

	auto ivAsType = reinterpret_cast<VBStruct*>(incomingVerts.data());
	auto vAsType = reinterpret_cast<VBStruct*>(verts.data());

	auto iAsType = reinterpret_cast<uint16_t*>(indices.data());

	for (int i = 0; i < numTriangles; i++)
	{
		if (i % 2) 
		{
			vAsType[i * 3 + 0] = ivAsType[i + 0];
			vAsType[i * 3 + 1] = ivAsType[i + 1];
			vAsType[i * 3 + 2] = ivAsType[i + 2];
		}
		else
		{
			vAsType[i * 3 + 0] = ivAsType[i + 0];
			vAsType[i * 3 + 1] = ivAsType[i + 2];
			vAsType[i * 3 + 2] = ivAsType[i + 1];
		}

		iAsType[i * 3 + 0] = i * 3 + 0;
		iAsType[i * 3 + 1] = i * 3 + 1;
		iAsType[i * 3 + 2] = i * 3 + 2;
	}

	std::swap(verts, incomingVerts);
	std::swap(indices, incomingIndices);
}

void Chimera_Process(std::queue<std::filesystem::path> &fQueue, std::unordered_map<FHashKey, std::filesystem::path> &fileMap)
{
	uint32_t uTotalProcessed = 0;
	//for(boost::filesystem::path queueItem : fQueue)
	while (!fQueue.empty())
	{
		std::filesystem::path queueItem = fQueue.front();

		//// Is it an image?
		//if (queueItem.parent_path().string().rfind("00104") == -1)
		//{
		//	fQueue.pop();
		//	continue;
		//}

		// Is it an image?
		if (queueItem.extension().string().rfind(".tex", 0) == 0)
		{
			Chimera_Image(queueItem, fileMap);
			fQueue.pop();
			continue;
		}

		if (
			!(queueItem.stem().string().rfind("vertex.0", 0) == 0)
			||
			!(queueItem.extension().string().rfind(".buffer", 0) == 0)
			)
		{
			fQueue.pop();
			continue;
		}

		PRINT_SSO("Processing Job: " + fQueue.front().string());

		//if (queueItem.extension().string() == ".rinfo")
		//	Chimera_ProcessRenderInfo(queueItem);
		//else
		//	Chimera_ProcessVMRInfo(queueItem);

		VertexBufferInformation vbi{};
		IndexBufferInformation ibi{};
		DrawBufferInformation dbi{};

		// Load Draw Info
		auto drawPath = queueItem.parent_path() / "call.info";
		LoadDrawBuffer(drawPath, dbi);

		// Load IndexBuffer
		auto indPath = queueItem.parent_path() / "index.buffer";
		std::vector<uint8_t> indBuffer;

		if (!Chimera_ProcessHashBuffer(indPath, fileMap, indBuffer))
		{
			PRINT_SSO("[WARN] FAILED!");
			fQueue.pop();
			continue;
		}

		// Load Ourself
		std::vector<uint8_t> vtxBuffer;
		if (!Chimera_ProcessHashBuffer(queueItem, fileMap, vtxBuffer))
		{
			PRINT_SSO("[WARN] FAILED!");
			fQueue.pop();
			continue;
		}

		// No good, very bad, absolutely awful function.
		if (dbi.PrimitiveType == 5)
		{
			//fixTriangeStrip(vtxBuffer, indBuffer);
		}

		ibi.IndexBufferData = reinterpret_cast<char*>(indBuffer.data());
		ibi.BufferSize = indBuffer.size();

		vbi.VertexBufferData = reinterpret_cast<char*>(vtxBuffer.data());
		vbi.VertexStructureWidth = sizeof(VBStruct);
		vbi.BufferSize = vtxBuffer.size();



		// Look for SRV in the folder
		std::vector<glm::vec4> skinningMatrix = LoadSkinMatrix(queueItem.parent_path() / "vertex.0.srvbuffer", fileMap);

		// Look for Texcoord Buffer
		FBDOShaderBindings stVtxBinding{};
		BuildBDOBindings(queueItem.parent_path() / "vertex.1.buffer", fileMap, stVtxBinding);
		
		auto offsets = GetCallOffset(queueItem.parent_path() / "call.info", fileMap);
		if (offsets.size() == 0)
		{
			stVtxBinding.Offset = 112 * 3;// std::max(0, int32_t(uTotalProcessed) - 11) * 112;// uTotalProcessed * 112;
		}
		else
		{
			stVtxBinding.Offset = offsets[3]; // Each is a uint32, and we want the offset for VB1
			stVtxBinding.cb0 = LoadSkinMatrix(queueItem.parent_path() / "vertex.0.constbuffer", fileMap);
			stVtxBinding.cb2 = LoadSkinMatrix(queueItem.parent_path() / "vertex.2.constbuffer", fileMap);
			stVtxBinding.cb3 = LoadSkinMatrix(queueItem.parent_path() / "vertex.3.constbuffer", fileMap);
			stVtxBinding.meshID = uTotalProcessed;
		}

		IsReal(queueItem.parent_path() / "vertex.shader", fileMap);

		// Call Information

		std::cout << "\tWriting " << (queueItem).string() << ".obj" << std::endl;

		createModel(vbi, ibi, dbi, (queueItem).string(), skinningMatrix, stVtxBinding);





		fQueue.pop();
		++uTotalProcessed;
	}
	
}

std::vector<glm::vec4> LoadSkinMatrix(std::filesystem::path& path, std::unordered_map<FHashKey, std::filesystem::path>& fileMap)
{
	std::vector<glm::vec4> skinMatrix;
	// If I have a problem, let's just forget about
	PRINT_DEBUG("\t\tLoading " << path.string());

	std::ifstream fileLoader = std::ifstream(path, std::ios::binary | std::ios::ate);

	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg);

		FHashKey hash{};
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(FHashKey));

		// Clear this info too
		uint64_t info;
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(uint64_t));

		if (fileSize > 40)
		{
			// This is a full file
			// Just read it all
			auto nItems = (fileSize - 40) / sizeof(glm::vec4);

			PRINT_DEBUG("Got " << nItems << " Items");

			skinMatrix.resize(nItems);
			fileLoader.read(reinterpret_cast<char*>(skinMatrix.data()), skinMatrix.size() * sizeof(glm::vec4));

			fileLoader.close();
			return skinMatrix;
		}
		else
		{
			fileLoader.close();
			// Lookup
			auto loc = fileMap.find(hash);

			if (loc != fileMap.end())
			{
				return LoadSkinMatrix(loc->second, fileMap);
			}
		}
	}


	return skinMatrix;
}

std::vector<uint32_t> GetCallOffset(std::filesystem::path& path, std::unordered_map<FHashKey, std::filesystem::path>& fileMap)
{
	std::vector<uint32_t> OffsetStrides;
	// If I have a problem, let's just forget about
	PRINT_DEBUG("\t\tLoading " << path.string());

	std::ifstream fileLoader = std::ifstream(path, std::ios::binary | std::ios::ate);

	if (fileLoader)
	{
		// Read Size
		fileLoader.seekg(sizeof(uint32_t) * 4);
		const uint64_t fileSize = fileLoader.tellg();
		

		if (fileSize > 0)
		{
			// This is a full file
			// Just read it all
			auto nItems = (fileSize) / sizeof(uint32_t);

			//PRINT_DEBUG("Got " << nItems << " Items");

			OffsetStrides.resize(nItems);
			fileLoader.read(reinterpret_cast<char*>(OffsetStrides.data()), OffsetStrides.size() * sizeof(uint32_t));

			fileLoader.close();
		}
	}

	return OffsetStrides;
}

void BuildBDOBindings(std::filesystem::path& path, std::unordered_map<FHashKey, std::filesystem::path>& fileMap, FBDOShaderBindings &stBinding)
{
	std::vector<glm::vec4> loadPacked;
	// If I have a problem, let's just forget about
	PRINT_DEBUG("\t\tLoading " << path.string());

	std::ifstream fileLoader = std::ifstream(path, std::ios::binary | std::ios::ate);

	if (fileLoader)
	{
		// Read Size
		const uint64_t fileSize = fileLoader.tellg();
		fileLoader.seekg(std::ios::beg);

		FHashKey hash{};
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(FHashKey));

		// Clear this info too
		uint64_t info;
		fileLoader.read(reinterpret_cast<char*>(&hash), sizeof(uint64_t));

		if (fileSize > 40)
		{
			// This is a full file
			// Just read it all
			auto nItems = (fileSize - 40) / sizeof(glm::vec4);

			PRINT_DEBUG("Got " << nItems << " Items");

			loadPacked.resize(nItems);
			fileLoader.read(reinterpret_cast<char*>(loadPacked.data()), loadPacked.size() * sizeof(glm::vec4));

			fileLoader.close();
		}
		else
		{
			fileLoader.close();
			// Lookup
			auto loc = fileMap.find(hash);

			if (loc != fileMap.end())
			{
				loadPacked = LoadSkinMatrix(loc->second, fileMap);
			}
		}
	}

	if (loadPacked.size() == 0)
	{
		return;
	}

	// Otherwise, swizzle it
	auto limit = loadPacked.size() / 7; // We have 7 channels
	
	//if (limit * 7 != loadPacked.size())
	//	return;

	stBinding.TexCoord1.resize(limit); 
	stBinding.TexCoord2.resize(limit);
	stBinding.TexCoord3.resize(limit);
	stBinding.TexCoord4.resize(limit);
	stBinding.TexCoord5.resize(limit);
	stBinding.TexCoord6.resize(limit);
	stBinding.TexCoord7.resize(limit);

	for (uint32_t i = 0; i < limit; ++i)
	{
		stBinding.TexCoord1[i] = loadPacked[i * 7 + 0];
		stBinding.TexCoord2[i] = loadPacked[i * 7 + 1];
		stBinding.TexCoord3[i] = loadPacked[i * 7 + 2];
		stBinding.TexCoord4[i] = loadPacked[i * 7 + 3];
		stBinding.TexCoord5[i] = loadPacked[i * 7 + 4];
		stBinding.TexCoord6[i] = loadPacked[i * 7 + 5];
		stBinding.TexCoord7[i] = loadPacked[i * 7 + 6];
	}
}


/// BELOW IS CODE USED FOR PARSING VMRINFO FILES.
/// I WILL MAKE A SWITCH FOR PROCESSING DRAW BASED OBJ
/// RATHER THAN VB BASED

