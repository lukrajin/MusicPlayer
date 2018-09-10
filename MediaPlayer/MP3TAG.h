#include <iostream>
#include <fstream>
#include <string>
#include "stdafx.h"
using namespace std;



class MP3TAG {


public:

	
	struct TAGdata
	{
		char tag[3];
		char title[30];
		char artist[30];
		char album[30];
		char year[4];
		char comment[30];
		int genre;
	};
	CString artist;
	CString title;
	CString album;
	CString year;

	MP3TAG();
	void Init(CString filepath);
};

