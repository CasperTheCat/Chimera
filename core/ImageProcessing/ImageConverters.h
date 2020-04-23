#pragma once
#include <vector>
#include "../Format.h"

inline uint32_t MinOne(uint32_t metric)
{
	return metric ? metric : 1;
}

std::vector<float> C4_U8_F32
(
	std::vector<uint8_t>& inVec,
	FTextureInfo& texInfo
);

std::vector<float> C4_S8_F32
(
	std::vector<uint8_t>& inVec,
	FTextureInfo& texInfo
);

std::vector<float> C4_S8_F32
(
	std::vector<uint8_t>& inVec,
	FTextureInfo& texInfo
);

template<typename T, typename X> 
std::vector<X> Raw
(
	std::vector<T>& inVec
)
{
	std::vector<X> outVec;
	outVec.resize(inVec.size() * sizeof(T) / sizeof(X));

	memcpy(outVec.data(), inVec.data(), inVec.size() * sizeof(T));
	return outVec;
}

template<typename T>
std::vector<float> C4_U32ToC4_F32
(
	std::vector<T>& inVec,
	FTextureInfo& texInfo
)
{
	std::vector<float> outVec;
	outVec.resize(MinOne(texInfo.uWidth) * MinOne(texInfo.uHeight) * MinOne(texInfo.uDepth) * 4);

	uint32_t* asU32 = reinterpret_cast<uint32_t*>(inVec.data());

	uint64_t index = 0;

#pragma omp parallel for private(index)
	for (int64_t z = 0; z < MinOne(texInfo.uDepth); ++z)
	{
		for (int64_t y = 0; y < MinOne(texInfo.uHeight); ++y)
		{
			for (int64_t x = 0; x < MinOne(texInfo.uWidth); ++x)
			{
				index = z * texInfo.uHeight * texInfo.uWidth + y * texInfo.uWidth + x * 4;

				outVec[index + 0] = asU32[index + 0] / float(UINT32_MAX);
				outVec[index + 1] = asU32[index + 1] / float(UINT32_MAX);
				outVec[index + 2] = asU32[index + 2] / float(UINT32_MAX);
				outVec[index + 3] = asU32[index + 3] / float(UINT32_MAX);
			}
		}
	}

	return outVec;
}

std::vector<uint8_t> C3_T8ToC4_T8
(
	std::vector<uint8_t> &inVec,
	FTextureInfo &texInfo
);

template<typename T>
std::vector<T> BGR_TToRGB_T
(
	std::vector<T>& inVec,
	FTextureInfo& texInfo
)
{
	std::vector<T> outVec;
	outVec.resize(MinOne(texInfo.uWidth) * MinOne(texInfo.uHeight) * MinOne(texInfo.uDepth) * 3);

	uint64_t index = 0;

#pragma omp parallel for private(index)
	for (int64_t z = 0; z < MinOne(texInfo.uDepth); ++z)
	{
		for (int64_t y = 0; y < MinOne(texInfo.uHeight); ++y)
		{
			for (int64_t x = 0; x < MinOne(texInfo.uWidth); ++x)
			{
				index = z * texInfo.uHeight * texInfo.uWidth + y * texInfo.uWidth + x * 3;

				outVec[index + 2] = asU32[index + 0];
				outVec[index + 1] = asU32[index + 1];
				outVec[index + 0] = asU32[index + 2];
			}
		}
	}
	return outVec;
}

template<typename T>
std::vector<T> BGRA_TToRGBA_T
(
	std::vector<T>& inVec,
	FTextureInfo& texInfo
)
{
	std::vector<T> outVec;
	outVec.resize(MinOne(texInfo.uWidth) * MinOne(texInfo.uHeight) * MinOne(texInfo.uDepth) * 4);

	uint64_t index = 0;

#pragma omp parallel for private(index)
	for (int64_t z = 0; z < MinOne(texInfo.uDepth); ++z)
	{
		for (int64_t y = 0; y < MinOne(texInfo.uHeight); ++y)
		{
			for (int64_t x = 0; x < MinOne(texInfo.uWidth); ++x)
			{
				index = z * texInfo.uHeight * texInfo.uWidth + y * texInfo.uWidth + x * 4;

				outVec[index + 2] = inVec[index + 0];
				outVec[index + 1] = inVec[index + 1];
				outVec[index + 0] = inVec[index + 2];
				outVec[index + 3] = inVec[index + 3];
			}
		}
	}
	return outVec;
}

std::vector<float> C4_AnyToF32
(
	std::vector<uint8_t>& inVec,
	FTextureInfo& texInfo
);

std::vector<float> C4_BC1ToF32
(
	std::vector<uint8_t>& inVec,
	FTextureInfo& texInfo
);

std::vector<float> C4_BCXToF32
(
	std::vector<uint8_t>& inVec,
	FTextureInfo& texInfo
);

std::vector<float> C4_BCXToF32
(
	std::vector<uint8_t>& inVec,
	FTextureInfo& texInfo
);

