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
#include <direct.h>
/*
mode:
ios::app|ios::out    	 	:如果没有文件则创建文件，如果有文件，则在文件尾追加
ios::ate|ios::out     		:如果没有文件则创建文件，如果有，则清空文件。
ios::ate|ios::out|ios::in       :如果没有文件，则打开失败，有文件则定位到文件尾
*/
#define  MAX_PATH_LEN						1024*4
// -------------------------------------------------------------------------------
bool LoadFileToStream(const char* file_name, std::fstream& stream, int mode) {
	// --------------------------------------------------------
	if (!file_name || (file_name == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	stream.clear();
	// --------------------------------------------------------
	stream.open(file_name, mode);
	// --------------------------------------------------------
	if (!stream.is_open()) {
		return false;
	}
	// --------------------------------------------------------
	return true;
}

// -------------------------------------------------------------------------------
bool __fastcall IsFileExist(const char* file_name, bool bwrite) {
	// --------------------------------------------------------
	if (!file_name || (file_name == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	if (_access(file_name, 0) == -1) {
		return false;
	}
	// --------------------------------------------------------
	return true;
	// --------------------------------------------------------
}
// -------------------------------------------------------------------------------
bool Create_Directory(const char* path) {
	// --------------------------------------------------------
	if (!path) {
		return false;
	}
	// --------------------------------------------------------
	if (strlen(path) > MAX_PATH_LEN) {
		return false;
	}
	// --------------------------------------------------------
	std::string inPath(path);
	// --------------------------------------------------------
	if (inPath.find_last_of("\\") != (inPath.length() - 1)) {
		inPath += "\\";
	}
	// --------------------------------------------------------
	char tmpDirPath[MAX_PATH_LEN] = { 0 };
	// --------------------------------------------------------
	for (uint32_t i = 0; i < inPath.length(); ++i)
	{
		// ----------------------------------------------------
		tmpDirPath[i] = path[i];
		// ----------------------------------------------------
		if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
		{
			if (_access(tmpDirPath, 0) != 0)
			{
				if (_mkdir(tmpDirPath) != 0)
				{
					return false;
				}
			}
		}
		// ----------------------------------------------------
	}//for-loop
	// --------------------------------------------------------
	return true;
}

// -------------------------------------------------------------------------------
bool IsDirExist(const char* path) {
	// --------------------------------------------------------
	if (!path || (path == '\0')) {
		return false;
	}
	// --------------------------------------------------------
	return _access(path, 0);
	// --------------------------------------------------------
}

// -------------------------------------------------------------------------------
/*索引目录下所有文件，包括子目录，将索引到的文件放到file_list中*/
int GetFileList(const char* path, std::list<std::string>& file_list) {
	// --------------------------------------------------------
	if (!path || (path == '\0')) {
		return -1;
	}
	// --------------------------------------------------------
	if (!_access(path, 0)) {
		return -1;
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
	handle = _findfirst((char*)inPath.c_str(), &fileinfo);
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
	} while (!_findnext(handle, &fileinfo));
	// --------------------------------------------------------
	_findclose(handle);
	// --------------------------------------------------------
	return 0;
}
// -------------------------------------------------------------------------------
// -------------------------------------------------------------------------------
#endif
