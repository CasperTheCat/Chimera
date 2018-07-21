#include <boost/filesystem.hpp>
#include <queue>

struct FPosition // Full Size 12B
{
	union
	{
		float x;
		float u;
		float i;
	};
	union
	{
		float y;
		float v;
		float j;
	};
	union
	{
		float z;
		float s;
		float k;
	};
};

struct FTexCoord // Full Size 8B
{
	union
	{
		float x;
		float u;
		float i;
	};
	union
	{
		float y;
		float v;
		float j;
	};
};

struct FTangents // 12 Bytes
{
	union
	{
		float x;
		float u;
		float i;
	};
	union
	{
		float y;
		float v;
		float j;
	};
	union
	{
		float z;
		float s;
		float k;
	};
};

struct FBlendWeights // 16 Bytes
{
	union
	{
		float x;
		float u;
		float i;
	};
	union
	{
		float y;
		float v;
		float j;
	};
	union
	{
		float z;
		float s;
		float k;
	};
	union
	{
		float w;
		float t;
		float l;
	};
};

struct FBoneIndices // 8 Bytes
{
	union
	{
		uint16_t x;
		uint16_t u;
		uint16_t i;
	};
	union
	{
		uint16_t y;
		uint16_t v;
		uint16_t j;
	};
	union
	{
		uint16_t z;
		uint16_t s;
		uint16_t k;
	};
	union
	{
		uint16_t w;
		uint16_t t;
		uint16_t l;
	};
};



/*
 * Dummy Abstact Type
 */
struct AChimeraVertexType
{
protected:
	AChimeraVertexType() = default;
	~AChimeraVertexType() = default;
public:
	virtual FPosition GetPosition() = 0;
	virtual FTexCoord GetTexCoord() = 0;
	virtual FTangents GetTangents() = 0;
	virtual FBlendWeights GetBlendWeights() = 0;
	virtual FBoneIndices GetBoneIndices() = 0;
};

/*
* Black Desert Vertex Type
*/
struct ABlackDesertVertexType// : private AChimeraVertexType
{
	float x;
	float y;
	float z;
	uint8_t normal_unorm[4]; // DXGI_FORMAT_R8G8B8A8_UNORM
	uint16_t u;
	uint16_t v;
	uint8_t color_unorm_bgr[4]; // B8G8R8A8_UNORM
	uint8_t blendIndices_uint[4]; // R8G8B8A8_UINT 
	uint8_t blendweight_unorm[4]; // R8G8B8A8_UNORM

	FPosition GetPosition();
	FTexCoord GetTexCoord();
	FTangents GetTangents();
	FBlendWeights GetBlendWeights();
	FBoneIndices GetBoneIndices();
};

/*
* Nier Automata Vertex Type
*/
struct ANierAutomataVertexType// : public AChimeraVertexType
{
	float x;
	float y;
	float z;
	uint8_t tangent_unorm[4]; // R8G8B8A8_UNORM
	uint16_t u;
	uint16_t v;
	uint8_t blendIndices_uint[4]; // R8G8B8A8_UINT 
	uint8_t blendweight_unorm[4]; // R8G8B8A8_UNORM

	FPosition GetPosition();
	FTexCoord GetTexCoord();
	FTangents GetTangents();
	FBlendWeights GetBlendWeights();
	FBoneIndices GetBoneIndices();
};

// Provides a conversion function for this type to the Chimera Type


// ONLY FOR BDO
//typedef int16_t IndexBufferType;
//typedef ABlackDesertVertexType VBStruct;

// NIER
typedef int32_t IndexBufferType;
typedef ANierAutomataVertexType VBStruct;

/*
 * Generic Chimera Vertex Structure
 * Used for storing data internally
 * Each game needs a conversion to this type
 */
struct FChimeraVertex
{
	FPosition Position;
	FTexCoord TexCoords;
	FTangents Tangents;
	FBoneIndices BoneIndices;
	FBlendWeights BlendWeights;

	FChimeraVertex(FPosition&& pos, FTexCoord&& tex, FTangents&& tans, FBoneIndices&& bis, FBlendWeights&& weights)
	{
		Position = std::move(pos);
		TexCoords = std::move(tex);
		Tangents = std::move(tans);
		BoneIndices = std::move(bis);
		BlendWeights = std::move(weights);
	}
};


enum class AnimDataFormat : uint8_t
{
	float4x3,
	float4x4,

	TOTAL_FORMAT_TYPES
};

/*
 * Vertex Buffer Structure
 * Aligned to 8 boundary
 * Total Size is 24 bytes
 */
struct VertexBufferInformation
{
	char * VertexBufferData; // 8 alignment
	uint32_t BufferSize; // 4
	uint32_t BufferOffset; // 4
	uint32_t DiskBufferNumber; // 4
	uint16_t BufferStride; // 4
	uint8_t VertexStructureWidth;
	uint8_t isValid : 1;
};

/*
* Index Buffer Structure
* Aligned to 8 boundary
* Total Size is 24 bytes
*/
struct IndexBufferInformation
{
	char * IndexBufferData; // 8
	uint32_t BufferSize; // 4
	uint32_t BufferOffset; // 4
	uint32_t DiskBufferNumber; // 4
	uint16_t BufferStride; // 4
	uint8_t VertexStructureWidth;
	uint8_t isValid : 1;
};

/*
* Index Buffer Structure
* Aligned to 8 boundary
* Total Size is 24 bytes
*/
struct DrawBufferInformation
{
	uint32_t IndexCount;
	uint32_t StartIndex;
	int32_t BaseVertex;
};
/*
* Vertex Shader Structure
* Aligned to 8 boundary
* Total Size is 16 bytes
*/
struct VertexShaderInformation
{
	void * VertexShaderData; // 8				-	8 Bytes
	uint32_t DiskBufferNumber; // 4				/		
	uint16_t AnimationDataWidth; // 2			|	8 Bytes
	uint8_t  AnimationVaryingLocation; // 1		|
	AnimDataFormat AnimationDataFormat; // 1	/
};

void Chimera_Process(std::queue<boost::filesystem::path> &fQueue);
