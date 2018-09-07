#include <iostream>
#include <fstream>
#include <string>
#include "stdafx.h"
#include "MP3TAG.h"



using namespace std;

const int fileNameLength = 1024;
const int mp3TagSize = 128;

MP3TAG::MP3TAG() {

	title = "Untitled";
	artist = "Untitled";
	album = "Untitled";
	year = "Untitled";

}
void MP3TAG::Init(CString filepath) {
		

		TAGdata tagStruct = { 0 };
		//char  fileName[fileNameLength + 1];
		ifstream mp3File;
		char buffer[mp3TagSize + 1];




		mp3File.open(filepath);
		buffer[mp3TagSize] = '\0';  

		if (!mp3File)
			throw exception("Can't read MP3 tags");

		mp3File.seekg(-(mp3TagSize), ios::end);
		if (mp3File.fail()) {
			throw exception("Can't read MP3 tags");
		}

		mp3File.read(reinterpret_cast <char *>(&tagStruct), mp3TagSize);
		if (mp3File.fail()) {
			throw exception("Can't read MP3 tags");
		}

		mp3File.close();

		
		
		title = tagStruct.title;
		artist = tagStruct.artist;
		album = tagStruct.album;
		year = tagStruct.year;

		
	}
	
	