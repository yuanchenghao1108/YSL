// -------------------------------------------------------------------------------
/*File.h
Autor:yuanchenghao
Time:2020/12/10
*/
// -------------------------------------------------------------------------------
#pragma once
// -------------------------------------------------------------------------------
#ifndef FILE_H
#define FILE_H
#include<fstream>
#include<string>
#include <io.h>
#include<list>
// -------------------------------------------------------------------------------
bool OpenFile(const char* file_name,bool bwrite) {
	// --------------------------------------------------------
	if (!file_name || (file_name == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	std::ifstream ifile;
	// --------------------------------------------------------
	ifile.open(file_name);
	// --------------------------------------------------------
	if (!ifile.is_open()) {
		return false;
	}
	// --------------------------------------------------------
}

// -------------------------------------------------------------------------------
/*索引目录下所有文件，包括子目录，将索引到的文件放到file_list中*/
int GetFileList(const char* path,std::list<std::string>& file_list) {
	// --------------------------------------------------------
	if (!path || (path == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	long handle;
	struct _finddata_t fileinfo;
	std::string inPath(path);
	// --------------------------------------------------------
	if (inPath.find_last_of("\\") != (inPath.length() - 1)) {
		inPath += "\\";
	}
	inPath += "*";
	// --------------------------------------------------------
	handle = _findfirst(inPath.c_str(), &fileinfo);
	if (handle == -1) {
		return -1;
	}
	// --------------------------------------------------------
	do
	{
		if (fileinfo.attrib & _A_SUBDIR)
		{
			if ((strcmp(fileinfo.name, ".") != 0) && (strcmp(fileinfo.name, "..") != 0))
			{
				inPath = path;
				inPath += fileinfo.name;
				inPath += "\\";
				//printf("%s\n", inPath.c_str());
				GetFileList(inPath.c_str(), file_list);
			}
		}
		else {
			//printf("%s\n", fileinfo.name);
			file_list.push_back(fileinfo.name);
		}
		//找到的文件的文件名
	} while (!_findnext(handle, &fileinfo));
	// --------------------------------------------------------
	_findclose(handle);
	// --------------------------------------------------------
	return 0;
}
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
#endif
