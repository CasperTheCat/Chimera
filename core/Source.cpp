#include <iostream>

#include "Process.h"
#include <string>
#include "Util.h"
#include <fstream>



void PrintHelp()
{
	
}

void RecurseDirectory(
	std::filesystem::path path,
	std::queue<std::filesystem::path> &fQueue,
	std::unordered_map<FHashKey, std::filesystem::path> &fileMap)
{
	const std::filesystem::directory_iterator finalIter;
	std::filesystem::directory_iterator iter(path);
	while (iter != finalIter)
	{
		//PRINT_DEBUG(extension(*iter));
		if (
			is_regular_file(*iter)
		)
		{
			// Open file and get size
			std::ifstream buffer((*iter).path(), std::ios::binary | std::ios::ate);
			auto bufferSize = buffer.tellg();

			if (bufferSize > 40)
			{
				// Has data, so let's register it!
				PRINT_DEBUG("[INFO] Registering " << (*iter).path());

				// Move to back, read hash to buffer
				FHashKey temp;
				buffer.seekg(std::ios::beg);
				buffer.read(reinterpret_cast<char*>(&temp), sizeof(FHashKey));

				// Check the map
				if (fileMap.find(temp) == fileMap.end())
				{
					fileMap.emplace(std::move(temp), (*iter).path());
				}
			}

			buffer.close();

			//if ((*iter).path().stem().string().rfind("vertex.", 0) == 0)
			//{
			fQueue.emplace(*iter);
			//}
		}
		else if (is_directory(*iter))
		{
			RecurseDirectory(*iter, fQueue, fileMap);
		}
		++iter;
	}
}

int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		PrintHelp();
		return EXIT_FAILURE;
	}

	std::queue<std::filesystem::path> fileQueue;
	std::unordered_map<FHashKey, std::filesystem::path> fileMap;

	PRINT_SSO("Building Job List");

	for(int32_t i = 1; i < argc; ++i)
	{
		const std::filesystem::path argAsPath(argv[i]);
		if (
			std::filesystem::is_regular_file(argAsPath)
			&&
			argAsPath.extension() == ".buffer"
			&&
			argAsPath.stem().string().rfind("vertex", 0) == 0
		)
		{
			fileQueue.emplace(argAsPath);
		}
		else
			RecurseDirectory(argAsPath, fileQueue, fileMap);
	}

	PRINT_SSO("Job List contains " + std::to_string(fileQueue.size()) + " jobs");

	Chimera_Process(fileQueue, fileMap);

	return EXIT_SUCCESS;
}