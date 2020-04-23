#include <filesystem>
#include <queue>
#include <unordered_map>


#define GLM_SWIZZLE
#include <glm/mat4x4.hpp>
#include <glm\ext\matrix_float4x4.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>


typedef glm::vec3 FPosition;

//struct FPosition // Full Size 12B
//{
//	union
//	{
//		float x;
//		float u;
//		float i;
//	};
//	union
//	{
//		float y;
//		float v;
//		float j;
//	};
//	union
//	{
//		float z;
//		float s;
//		float k;
//	};
//};

typedef glm::vec2 FTexCoord;

//struct FTexCoord // Full Size 8B
//{
//	union
//	{
//		float x;
//		float u;
//		float i;
//	};
//	union
//	{
//		float y;
//		float v;
//		float j;
//	};
//};

typedef glm::vec4 FTangents;

//struct FTangents // 12 Bytes
//{
//	union
//	{
//		float x;
//		float u;
//		float i;
//	};
//	union
//	{
//		float y;
//		float v;
//		float j;
//	};
//	union
//	{
//		float z;
//		float s;
//		float k;
//	};
//};

typedef glm::vec4 FBlendWeights;

//struct FBlendWeights // 16 Bytes
//{
//	union
//	{
//		float x;
//		float u;
//		float i;
//	};
//	union
//	{
//		float y;
//		float v;
//		float j;
//	};
//	union
//	{
//		float z;
//		float s;
//		float k;
//	};
//	union
//	{
//		float w;
//		float t;
//		float l;
//	};
//};

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


struct FHashKey
{
	uint64_t u1;
	uint64_t u2;
	uint64_t u3;
	uint64_t u4;

	bool operator==(const FHashKey& other) const
	{
		return this->u1 == other.u1
			&& this->u2 == other.u2
			&& this->u3 == other.u3
			&& this->u4 == other.u4;
	}
};

namespace std {
	template<>
	struct hash<FHashKey>
	{
		std::size_t operator()(const FHashKey& k) const
		{
			return k.u1 ^ k.u2 + k.u3 ^ k.u4;
		}
	};
}



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
	glm::vec4 GetColour();
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


//// ONLY FOR BDO
typedef int16_t IndexBufferType;
typedef ABlackDesertVertexType VBStruct;

// NIER
//typedef int32_t IndexBufferType;
//typedef ANierAutomataVertexType VBStruct;

/*
 * Generic Chimera Vertex Structure
 * Used for storing data internally
 * Each game needs a conversion to this type
 */
struct FChimeraVertex
{
	int32_t indexBufferLocale;
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec4 Tangents;
	FBoneIndices BoneIndices;
	glm::vec4 BlendWeights;
	glm::vec4 Colour;

	FChimeraVertex(int32_t locale, FPosition&& pos, FTexCoord&& tex, FTangents&& tans, FBoneIndices&& bis, FBlendWeights&& weights, glm::vec4 &&vColour)
	{
		indexBufferLocale = locale;
		Position = std::move(pos);
		TexCoords = std::move(tex);
		Tangents = std::move(tans);
		BoneIndices = std::move(bis);
		BlendWeights = std::move(weights);
		Colour = std::move(vColour);
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

struct FBDOShaderBindings
{
	// VB1 -> V6,7,8,9,10,11,12
	std::vector<glm::vec4> TexCoord1;
	std::vector<glm::vec4> TexCoord2;
	std::vector<glm::vec4> TexCoord3;
	std::vector<glm::vec4> TexCoord4;
	std::vector<glm::vec4> TexCoord5;
	std::vector<glm::vec4> TexCoord6;
	std::vector<glm::vec4> TexCoord7;

	std::vector<glm::vec4> cb0;
	std::vector<glm::vec4> cb2;
	std::vector<glm::vec4> cb3;

	uint32_t Offset;
	uint32_t meshID;
};


void Chimera_ProcessVertexBuffer(const std::filesystem::path& item);

void LoadIndexBuffer(const std::filesystem::path& item, IndexBufferInformation& indexBuffer);

void Chimera_Process(std::queue<std::filesystem::path> &fQueue, std::unordered_map<FHashKey, std::filesystem::path>& fileMap);

std::vector<glm::vec4> LoadSkinMatrix(std::filesystem::path& path, std::unordered_map<FHashKey, std::filesystem::path>& fileMap);
std::vector<uint32_t> GetCallOffset(std::filesystem::path& path, std::unordered_map<FHashKey, std::filesystem::path>& fileMap);
void BuildBDOBindings(std::filesystem::path& path, std::unordered_map<FHashKey, std::filesystem::path>& fileMap, FBDOShaderBindings& stBinding);
