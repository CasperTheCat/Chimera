#include <iostream>
#include <boost/filesystem.hpp>
#include <queue>
#include "Util.h"

void PrintHelp()
{
	
}

void RecurseDirectory(boost::filesystem::path path, std::queue<boost::filesystem::path> &fQueue)
{
	const boost::filesystem::directory_iterator finalIter;
	boost::filesystem::directory_iterator iter(path);
	while (iter != finalIter)
	{
		if (is_regular_file(*iter))
		{
			fQueue.emplace(*iter);
		}
		else if (is_directory(*iter))
		{
			RecurseDirectory(*iter, fQueue);
		}
		else
		{
			return;
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

	std::queue<boost::filesystem::path> fileQueue;

	PRINT_SSO("Building Job List");

	for(int32_t i = 1; i < argc; ++i)
	{
		const boost::filesystem::path argAsPath(argv[i]);
		if (boost::filesystem::is_regular_file(argAsPath))
			fileQueue.emplace(argAsPath);
		else
			RecurseDirectory(argAsPath, fileQueue);
	}

	PRINT_SSO("Job List contains " + std::to_string(fileQueue.size()) + " jobs");

	return EXIT_SUCCESS;
}