//// Maybe not the fastest this function could be, but good to get a ground truth first
//
//// For OBJ export, we need vertex indices, vertex positions and vertex normals
//// For this we need to work in faces not vertices
//
///*std::ofstream dumpVB("dump" + std::to_string(primsCapd) + ".vb");
//std::ofstream dumpIB("dump" + std::to_string(primsCapd) + ".ib");
//std::ofstream dumpInfoB("dump" + std::to_string(primsCapd) + ".info", std::ios_base::app);*/
//
//// Predefinied Variables
//std::vector<FCAPVertex> vertices;
////vertices.reserve(PrimitiveCount * 3);
////std::vector<FCAPFace> faces;
////faces.reserve(PrimitiveCount);
//std::vector<UINT> indices;
////indices.reserve(PrimitiveCount * 3);
////faces.reserve(PrimitiveCount);
//
//if (Stride < (sizeof(float) * 3)) return;
//
//std::vector<uint16_t> indexMap;
//for (UINT i = 0; i < IndexCount; ++i) {
//	if ((i % 10000) == 0) std::cout << "\r" << "Ripping object " << primsCapd << ", " << i / static_cast<float>(IndexCount + 1) << "%\t\t\t\t";
//	//d3dw->Event << "Adding to Map " << i << std::endl;
//	//d3dw->Event << std::hex << IndexBuffer << std::endl;
//	uint16_t a = reinterpret_cast<uint16_t*>(IndexBuffer)[VertexIndexOffset + i] + BaseVertexIndex;// +Offset;
//																								   //dumpIB << i << ": " << a << std::endl;
//	if (a == UINT32_MAX) continue; // Skip this invalid index
//	std::vector<uint16_t>::iterator it = std::find(indexMap.begin(), indexMap.end(), a);
//	if (it == indexMap.end()) {
//		indexMap.push_back(a);
//
//
//#ifdef USING_VB_STRUCT
//		// Give Vertex Buffer a type
//		const auto ptr = reinterpret_cast<VBStruct *>((VertexBuffer));
//
//		// Read element a
//		const auto vert = &ptr[a];
//
//		float u;
//		float v;
//#ifdef USING_HALF_PRECISION_UV
//		// Conv u
//		u = HalfFloatToFloat(vert->u);
//		v = HalfFloatToFloat(vert->v);
//#else
//		u = vert->u;
//		v = vert->v;
//#endif
//
//
//		vertices.emplace_back(Vec3f(vert->x, vert->y, vert->z), Vec2f(u, v));
//		indices.push_back((uint16_t)(indexMap.size() - 1));
//
//#else
//		void *vertexInfo = reinterpret_cast<void *>(reinterpret_cast<uint8_t *>(VertexBuffer) + Stride * a);
//		float x = ((float *)vertexInfo)[0];
//		float y = ((float *)vertexInfo)[1];
//		float z = ((float *)vertexInfo)[2];
//		void *uv = (void *)((uint8_t *)vertexInfo + Stride - 2 * sizeof(float));
//		//float u = ((float *)uv)[0];
//		//float v = ((float *)uv)[1];
//		//dumpVB << x << " " << y << " " << z << std::endl;
//		vertices.push_back(FCAPVertex(Vec3f(x, y, z), Vec2f(0, 0)));
//		//textureCoordList.push_back(Vec2f(u, v));
//		indices.push_back((uint16_t)(indexMap.size() - 1));
//		//dumpInfoB << "Addr " << a << " is now indexed as " << indexMap.size() - 1 << endl;
//#endif
//	}
//	else {
//		//dumpInfoB << "Addr " << a << " already in index at location " << std::distance(indexMap.begin(), it) << std::endl;
//		indices.push_back((uint16_t)std::distance(indexMap.begin(), it));
//	}
//}
//
//FCAPWriteMesh(vertices, indices);
