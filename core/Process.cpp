#include "Process.h"
#include "Util.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_set>


#pragma region VS_RipFunctions

void writeMeshOBJ
(
	std::vector<FChimeraVertex> &verts,
	std::vector<uint32_t> &indices,
	std::string &&saveLocation
)
{
	// Write using OBJ export
	std::ofstream objStream(saveLocation);

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



void createModel(VertexBufferInformation &vbi, IndexBufferInformation &ibi, DrawBufferInformation &dbi, const std::string& saveLocation)
{
	std::vector<FChimeraVertex> vertices;
	std::vector<uint32_t> indices;
	const auto ptr = reinterpret_cast<VBStruct *>((vbi.VertexBufferData));

	PRINT_DEBUG("Struct is " + std::to_string(sizeof(VBStruct)) + " bytes vs " + std::to_string(vbi.VertexStructureWidth));

	if (sizeof(VBStruct) != vbi.VertexStructureWidth) return;

	std::vector<IndexBufferType> indexMap;
	for (uint32_t i = 0; i < dbi.IndexCount; ++i) {

		// Might not be 16 in all cases. Engine dependant
		IndexBufferType a = reinterpret_cast<IndexBufferType*>(ibi.IndexBufferData)[i + dbi.StartIndex] + dbi.BaseVertex;

		if (a == UINT32_MAX) continue; // Skip this invalid index
		const std::vector<IndexBufferType>::iterator it = std::find(indexMap.begin(), indexMap.end(), a);
		if (it == indexMap.end()) {
			indexMap.push_back(a);

			// Read element a
			auto vert = ptr[a];
			
			FChimeraVertex convertedType
			(
				vert.GetPosition(),
				vert.GetTexCoord(),
				vert.GetTangents(),
				vert.GetBoneIndices(),
				vert.GetBlendWeights()
			);

			vertices.emplace_back(convertedType);
			indices.emplace_back(static_cast<uint32_t>(indexMap.size() - 1));

		}
		else {
			indices.push_back(static_cast<uint32_t>(std::distance(indexMap.begin(), it)));
		}
	}

	writeMeshOBJ(vertices, indices, saveLocation + ".obj");
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
	tex.u = HalfFloatToFloat(this->u);
	tex.v = HalfFloatToFloat(this->v);
	return tex;
}

FTangents ABlackDesertVertexType::GetTangents()
{
	return FTangents{};
}

FBlendWeights ABlackDesertVertexType::GetBlendWeights()
{
	return FBlendWeights{};
}

FBoneIndices ABlackDesertVertexType::GetBoneIndices()
{
	return FBoneIndices{};
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
	tex.u = HalfFloatToFloat(this->u);
	tex.v = HalfFloatToFloat(this->v);
	return tex;
}

FTangents ANierAutomataVertexType::GetTangents()
{
	return FTangents{};
}

FBlendWeights ANierAutomataVertexType::GetBlendWeights()
{
	return FBlendWeights{};
}

FBoneIndices ANierAutomataVertexType::GetBoneIndices()
{
	return FBoneIndices{};
}

void Chimera_ProcessRenderInfo(const boost::filesystem::path& item)
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

				createModel(vbInformation, ibInformation, dbi, item.string() + "." + std::to_string(++counter));
			}
		}
	}

	if(vbInformation.VertexBufferData) delete[] vbInformation.VertexBufferData;
}

void Chimera_ProcessVMRInfo(const boost::filesystem::path& item)
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

	createModel(vbInformation, ibInformation, drawBufferInformation, item.string());

	// Clean up
	delete[] vbInformation.VertexBufferData;
	delete[] ibInformation.IndexBufferData;
}

void Chimera_Process(std::queue<boost::filesystem::path> &fQueue)
{
	//for(boost::filesystem::path queueItem : fQueue)
	while (!fQueue.empty())
	{
		boost::filesystem::path queueItem = fQueue.front();
		PRINT_SSO("Processing Job " + fQueue.front().filename().string());

		if (queueItem.extension().string() == ".rinfo")
			Chimera_ProcessRenderInfo(queueItem);
		else
			Chimera_ProcessVMRInfo(queueItem);


		std::vector<DrawBufferInformation> drawBuffers;
		std::vector<IndexBufferInformation> indexBuffers;

		// Pop the processed element
		fQueue.pop();
	}
}


/// BELOW IS CODE USED FOR PARSING VMRINFO FILES.
/// I WILL MAKE A SWITCH FOR PROCESSING DRAW BASED OBJ
/// RATHER THAN VB BASED



