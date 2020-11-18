/*Copyright (c) 2020 D3fau4

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <switch.h>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>
#include "FS/FS.hpp"

json temp;

namespace FS
{
	Result createdir(string path)
	{
		if (checkdirexist(path) == false)
		{
			mkdir(path.c_str(), 0777);
			return 0;
		}
		return 1;
	}

	Result DeleteDir(string path)
	{
		std::filesystem::remove_all(path);
		rmdir(path.c_str());
		return 0;
	}

	bool checkdirexist(string path)
	{
		bool exist = false;
		DIR *dir = opendir(path.c_str());
		if (dir)
		{
			closedir(dir);
			exist = true;
		}
		return exist;
	}

	Result createFile(string path)
	{
		FILE *f;
		f = fopen(path.c_str(), "w");
		if (f)
		{
			fclose(f);
			return 0;
		}
		return 1;
	}

	Result checkFile(string path)
	{
		FILE *f;
		f = fopen(path.c_str(), "r");
		if (f)
		{
			fclose(f);
			return 1;
		}
		return 0;
	}

	Result DeleteFile(string path)
	{
		std::filesystem::remove(path);
		return 0;
	}

	Result writeConfig()
	{
		std::ifstream rom("romfs:/config.json");
		rom >> temp;
		std::ofstream sd("/switch/NightFall/config.json");
		sd << temp;
		sd.close();
		rom.close();
		return 0;
	}

	std::vector<std::string> getDirectories(const std::string &s)
	{
		std::vector<std::string> r;
		for (auto &p : std::filesystem::recursive_directory_iterator(s))
			if (p.is_directory())
				r.push_back(p.path().filename());
		return r;
	}

} // namespace FS