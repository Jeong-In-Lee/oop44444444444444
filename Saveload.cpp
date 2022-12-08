#pragma once
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
#include<vector>
#include <sstream>
#include "CSphere.h"
#include "Board.cpp"
#include "d3dUtility.h"
 

class Saveload {

public:
	void gamesave(Board& brd) //포인터로 받아야함-------------------------------------------

	{
		//fstream fout;
		//fout.open("SaveData.txt", ios::out);
		//if (fout.is_open())
		//{
		//	for (int i = 0; i < brd.getRow(); i++)
		//	{
		//		for (int j = 0; j < brd.getCol(); j++)
		//		{
		//			fout << brd.getBall(i,j).getColor() << " "; //ㅇㄹ호ㅓㅏㅣㅓㅗㅎㄹㅇ
		//			fout << brd.getBall(i, j).getCenter().x << " ";
		//			fout << brd.getBall(i, j).getCenter().y << " ";
		//			fout << brd.getBall(i, j).getCenter().z << " ";
		//			fout << brd.getBall(i, j).getExist() << " "; //true = 1 false 0
		//			fout << endl;
		//		}

		//	}
		//	fout.close();

		//}
	}
	void gameload(Board& brd)
	{
		//string line;
		//fstream fin;
		//fin.open("SaveData.txt", ios::in);
		//ifstream myfile("SaveData.txt");

		//if (myfile.is_open())
		//{
		//	int col = brd.getCol();
		//	int row = brd.getRow();


		//	for (int i = 0; i < row; i++)
		//	{
		//		for (int j = 0; j < col; j++)
		//		{
		//			while (getline(myfile, line))
		//			{
		//				stringstream ss(line);
		//				string color, x, y, z, exist;
		//				ss >> color >> x >> y >> z >> exist;
		//				float X = stof(x);
		//				float Y = stof(y);
		//				float Z = stof(z);
		//				int Color = stoi(color);
		//				int exist_ = stoi(exist);
		//				bool Exist;

		//				if (exist_ == 0) {
		//					Exist = false;
		//				}
		//				else {
		//					Exist = true;
		//				}

		//				brd.resume(j, i, X, Y, Z, Color, Exist);

		//				break;
		//			}
		//		}
		//	}




		//	//fin >> score;
		//	//fin >> moves;
		//	//fin.close();
		//}
		//cout <<score<< moves;

	}

};