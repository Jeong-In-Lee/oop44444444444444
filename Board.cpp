#include <stdio.h>
#include <vector>
#include "CWall.h"
#include "CSphere.h"
#include <random>

using namespace std;

class Board {

private:
    CSphere brd[10][8];
    CSphere extBrd [15];
    float x_bdCtr, y_bdCtr, z_bdCtr;
    int rBoundary;
    int empFl = -3;

public:

    //Board() {
    //            x_bdCtr = gamemanager.getcenter_x();
    //            y_bdCtr = gamemanager.getcenter_y();
    //            z_bdCtr = gamemanager.getcenter_z();
    //}



    void create(float X, float Y, float Z, IDirect3DDevice9* pDevice, float depth) {

        this->x_bdCtr = X;
        this->y_bdCtr = Y;
        this->z_bdCtr = Z;

        rBoundary = 3;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dis(1, 4);


        for (int i = 0; i < sizeof(brd) / sizeof(brd[0]); i++) //row
        {
            for (int j = 0; j < sizeof(brd[0]) / sizeof(CSphere); j++) //col
            {
                brd[i][j].create(pDevice);

                int color = dis(gen);
                if (color == 1)
                    brd[i][j].setColor(d3d::YELLOW);
                else if (color == 2)
                    brd[i][j].setColor(d3d::RED);
                else if (color == 3)
                    brd[i][j].setColor(d3d::BLUE);
                else
                    brd[i][j].setColor(d3d::GREEN);

                if (i % 2 == 0) {
                    brd[i][j].setCenter(x_bdCtr - (4  - j) * brd[i][j].getRadius() / 0.5, 0.5, z_bdCtr + depth / 2 - i * brd[i][j].getRadius() / 0.5);
                }
                else if (i % 2 == 1) {
                    brd[i][j].setCenter(x_bdCtr - (3.5 - j) * brd[i][j].getRadius()/0.5, 0.5, z_bdCtr + depth / 2 - i * brd[i][j].getRadius()/0.5);
                }

                if (i > 3)
                {
                    brd[i][j].setExist(false);
                    brd[i][j].setColor(d3d::MAGENTA);
                }
            }
        }
    }

    int destroy(int m, int n, int col) {
        this->chNeighball(m, n, col, 1);

        //�ٿ���� �� ����ϴ� �ݺ���
        int hit = 0;
        
        /*for (int i = 0; i < sizeof(brd[0]) / sizeof(CSphere); i++) {
            if (brd[rBoundary][i].getExist())
                break;
            else if (i == sizeof(brd[0]) / sizeof(CSphere) && (!brd[rBoundary][i].getExist())) {
                i = -1;
                rBoundary--;

            }
        }*/
        // �Ͷ߸��� �ݺ���
        for (int i = 0; i < 10; i++) {
            for (int j = 0; i < sizeof(brd[0]) / sizeof(CSphere); j++) {
                if (brd[i][j].getChflag() == 1) {
                    //�Ͷ߸��� ����
                    brd[i][j].setExist(false);
                    brd[i][j].setColor(d3d::MAGENTA);
                    hit++;

                }
            }
        }
        return hit;
    }

    void chNeighball(int m, int n, int col) {
        //ball ??chflag 추�?, getter, setter ??마찬가지
        if (brd[m][n].getChflag() == 0) {
            if (brd[m][n].getColor() == col) {
                brd[m][n].setChflag(1);

                if (n < sizeof(brd[0]) / sizeof(CSphere) - 1) {
                    chNeighball(m, n + 1, col);
                }

                if (m % 2 == 0) {
                    if (m <= 10 ) { //rb                        
                        chNeighball(m + 1, n, col);
                        if (n > 0)
                            chNeighball(m + 1, n - 1, col);

                    }
                    if (n > 0) {
                        chNeighball(m, n - 1, col);
                        if (m > 0)
                            chNeighball(m - 1, n - 1, col);
                    }
                    if (m > 0)
                        chNeighball(m - 1, n, col);
                }

                else if (m % 2 == 1) {
                    if (m <= 10) { //rb
                        if (n < sizeof(brd[0]) / sizeof(CSphere) - 1)
                            chNeighball(m + 1, n + 1, col);

                        chNeighball(m + 1, n, col);
                    }
                    if (n > 0)
                        chNeighball(m, n - 1, col);

                    if (m > 0) {
                        chNeighball(m - 1, n, col);
                        if (n < sizeof(brd[0]) / sizeof(CSphere) - 1)
                            chNeighball(m - 1, n + 1, col);
                    }
                }

            }
        }
    }


    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld) {
        for (int i = 0; i < sizeof(brd) / sizeof(brd[0]); i++) //row
        {
            for (int j = 0; j < sizeof(brd[0]) / sizeof(CSphere); j++) //col
            {
                if (brd[i][j].getExist())
                    brd[i][j].draw(pDevice, mWorld);
            }
        }
    }

    void bAttach(int m, int n, CSphere& ball) {
        int available[6] = { 0, };

        if (m == 0)
            available[0] = available[1] = 1;

        if (m % 2 == 0)
        {
            float short_distance = 1000;
            float temp;
            int pos = 6; // 0 left above 1 right above 2 left 3 right 4 left under 5 right under 

            if (!brd[m - 1][n - 1].getExist())
            {
                temp = brd[m - 1][n - 1].getDistance(ball);
                if (short_distance > temp)
                {
                    short_distance = temp;
                    pos = 0;
                }
            }

            if (!brd[m - 1][n].getExist())
            {
                temp = brd[m - 1][n].getDistance(ball);
                if (short_distance > temp)
                {
                    short_distance = temp;
                    pos = 1;
                }
            }

            if (!brd[m][n - 1].getExist())
            {
                temp = brd[m][n - 1].getDistance(ball);
                if (short_distance > temp)
                {
                    short_distance = temp;
                    pos = 2;
                }
            }

            if (!brd[m][n + 1].getExist())
            {
                temp = brd[m][n + 1].getDistance(ball);
                if (short_distance > temp)
                {
                    short_distance = temp;
                    pos = 3;
                }
            }

            if (!brd[m + 1][n - 1].getExist())
            {
                temp = brd[m + 1][n - 1].getDistance(ball);
                if (short_distance > temp)
                {
                    short_distance = temp;
                    pos = 4;
                }
            }

            if (!brd[m + 1][n].getExist())
            {
                temp = brd[m + 1][n].getDistance(ball);
                if (short_distance > temp)
                {
                    short_distance = temp;
                    pos = 5;
                }
            }

            switch (pos) {
            case 0:
                brd[m - 1][n - 1].setExist(true);
                brd[m - 1][n - 1].revColor(ball.getColor());
                break;
            case 1:
                brd[m - 1][n].setExist(true);
                brd[m - 1][n].revColor(ball.getColor());
                break;
            case 2:
                brd[m][n - 1].setExist(true);
                brd[m][n - 1].revColor(ball.getColor());
                break;
            case 3:
                brd[m][n + 1].setExist(true);
                brd[m][n + 1].revColor(ball.getColor());
                break;
            case 4:
                brd[m + 1][n - 1].setExist(true);
                brd[m + 1][n - 1].revColor(ball.getColor());
                break;
            case 5:
                brd[m + 1][n].setExist(true);
                brd[m + 1][n].revColor(ball.getColor());
                break;
            }

        }
        else
        {

        }

    }

    void chEmpty(int m, int n, int* hMax, int* wMin, int* wMax) {

        if (brd[m][n].getColor() == 0) {
            brd[m][n].setChflag(empFl);
            if (m > *hMax)
                *hMax = m;
            if (n < *wMin)
                *wMin = n;
            else if (n > *wMax)
                *wMax = n;

            if (n > 0)
                chEmpty(m, n - 1, hMax, wMin, wMax);

            if (m % 2 == 0) {

                if (m > 0) {
                    if (n > 0) {
                        chEmpty(m - 1, n - 1, hMax, wMin, wMax);
                    }
                    chEmpty(m - 1, n, hMax, wMin, wMax);
                }


                chEmpty(m, n + 1, hMax, wMin, wMax);
                chEmpty(m + 1, n, hMax, wMin, wMax);
                chEmpty(m + 1, n - 1, hMax, wMin, wMax);

            }
            else if (m % 2 == 1) {

                chEmpty(m - 1, n, hMax, wMin, wMax);
                chEmpty(m - 1, n + 1, hMax, wMin, wMax);
                chEmpty(m, n + 1, hMax, wMin, wMax);
                chEmpty(m + 1, n + 1, hMax, wMin, wMax);
                chEmpty(m + 1, n, hMax, wMin, wMax);
            }
        }
    }

    int bDetach() {

        int i;
        int* min;
        int* max;
        int* hei;
        int hit = 0;
        for (i = 0; i < sizeof(brd[0]) / sizeof(CSphere); i++) {
            if (brd[rBoundary][i].getColor() == 0)
                break;
        }

        *hei = rBoundary;
        *min = i;
        *max = i;

        chEmpty(rBoundary, i, hei, min, max);

        if (*hei < rBoundary && *min < *max) {
            for (int i = *hei; i <= rBoundary; i++) {
                for (int j = *min; j <= *max; j++) {
                    //�Ͷ߸���
                    if (brd[i][j].getChflag() == -2)
                    {
                        brd[i][j].setExist(false);
                        brd[i][j].setColor(d3d::MAGENTA);
                        hit++;
                    }
                }
            }
        }
        return hit;
    }

    void resume(int col, int row, float x, float y, float z, int color, bool exist)
    {
        brd[row][col].setCenter(x, y, z);

        if (color == 1)
        {
            brd[row][col].setColor(d3d::YELLOW);
        }
        else if (color == 2)
        {
            brd[row][col].setColor(d3d::RED);

        }
        else if (color == 3)
        {
            brd[row][col].setColor(d3d::BLUE);
        }
        else if (color == 4)
        {
            brd[row][col].setColor(d3d::GREEN);
        }
        else
        {
            brd[row][col].setColor(d3d::MAGENTA);
        }

        brd[row][col].setExist(exist);
    }

    CSphere getBall(int row, int col)
    {
        return this->brd[row][col];
    }

    int getRow()
    {
        return sizeof(brd) / sizeof(brd[0]);
    }

    int getCol()
    {
        return sizeof(brd[0]) / sizeof(CSphere);
    }

};


