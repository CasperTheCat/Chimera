#include "ImageConverters.h"

#ifdef _WIN32
#include "DirectXTex/DirectXTex.h"
#endif

std::vector<float> C4_U8_F32(std::vector<uint8_t>& inVec, FTextureInfo& texInfo)
{
	std::vector<float> outVec;
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

				outVec[index + 0] = inVec[index + 0] / float(UINT8_MAX);
				outVec[index + 1] = inVec[index + 1] / float(UINT8_MAX);
				outVec[index + 2] = inVec[index + 2] / float(UINT8_MAX);
				outVec[index + 3] = inVec[index + 3] / float(UINT8_MAX);
			}
		}
	}
	return outVec;
}

std::vector<float> C4_AnyToF32(std::vector<uint8_t>& inVec, FTextureInfo& texInfo)
{
	std::vector<float> outVec;

	// Channels

	outVec.resize(texInfo.uHeight * texInfo.uWidth * 4);

#ifdef _WIN32
	// Decompress
	DirectX::Image image{};
	image.pixels = inVec.data();
	image.width = texInfo.uWidth;
	image.height = texInfo.uHeight;
	image.rowPitch = 0;// texInfo.uWidth / 2;
	image.slicePitch = 0;// texInfo.uHeight / 2;
	image.format = static_cast<DXGI_FORMAT>(texInfo.uFormat);

	DirectX::ScratchImage destImage{}; //DXGI_FORMAT_R32G32B32A32_FLOAT

	auto hr = DirectX::Convert(image, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, DirectX::TEX_FILTER_DEFAULT, DirectX::TEX_THRESHOLD_DEFAULT,  destImage);

	if (hr == S_OK)
	{
		memcpy(outVec.data(), destImage.GetPixels(), outVec.size() * sizeof(float));
	}

	destImage.Release();

#endif

	// Reset the texinfo
	texInfo.uDepth = 0;
	//texInfo.uFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	return outVec;
}

std::vector<float> C4_BC1ToF32(std::vector<uint8_t>& inVec, FTextureInfo& texInfo)
{
	{
		std::vector<float> outVec;
		outVec.resize(texInfo.uHeight * texInfo.uWidth * 4);

		if (inVec.size() != (texInfo.uHeight / 4) * texInfo.uWidth * 2)
		{
			return outVec;
		}

#ifdef _WIN32
		// Decompress
		DirectX::Image image{};
		image.pixels = inVec.data();
		image.width = texInfo.uWidth;
		image.height = texInfo.uHeight;
		//image.rowPitch = (texInfo.uWidth * 4) / 8;// *sizeof(float);
		//image.slicePitch = texInfo.uHeight * 4; // 2;
		image.rowPitch = texInfo.uWidth * 2;// *sizeof(float);
		image.slicePitch = texInfo.uHeight / 4; // 2;
		image.format = static_cast<DXGI_FORMAT>(texInfo.uFormat);



		DirectX::ScratchImage destImage{}; //DXGI_FORMAT_R32G32B32A32_FLOAT

		auto hr = DirectX::Decompress(image, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, destImage);

		if (hr == S_OK)
		{
			memcpy(outVec.data(), destImage.GetPixels(), outVec.size() * sizeof(float));
		}

		destImage.Release();

#endif

		// Reset the texinfo
		texInfo.uDepth = 0;
		//texInfo.uFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

		return outVec;
	}

}

std::vector<float> C4_BCXToF32(std::vector<uint8_t>& inVec, FTextureInfo& texInfo)
{
	std::vector<float> outVec;
	outVec.resize(texInfo.uHeight * texInfo.uWidth * 4);


	if (inVec.size() != (texInfo.uHeight / 4) * texInfo.uWidth * 4)
	{
		return outVec;
	}

#ifdef _WIN32
	// Decompress
	DirectX::Image image{};
	image.pixels = inVec.data();
	image.width = texInfo.uWidth;
	image.height = texInfo.uHeight;
	image.rowPitch = 16 * (texInfo.uWidth / 4);// *sizeof(float);
	image.slicePitch = texInfo.uHeight / 4; // 2;
	image.format = static_cast<DXGI_FORMAT>(texInfo.uFormat);

	DirectX::ScratchImage destImage{}; //DXGI_FORMAT_R32G32B32A32_FLOAT

	auto hr = DirectX::Decompress(image, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, destImage);

	if (hr == S_OK)
	{
		memcpy(outVec.data(), destImage.GetPixels(), outVec.size() * sizeof(float));
	}

	destImage.Release();

#endif

	// Reset the texinfo
	texInfo.uDepth = 0;
	//texInfo.uFormat = DXGI_FORMAT_R32G32B32A32_FLOAT;

	return outVec;
}
