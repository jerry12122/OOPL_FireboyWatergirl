#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "RedPlayer.h"
#include "box.h"
#include <iostream>   
#include <fstream> 
#include <string.h>
#include <conio.h>
#include <time.h>
#include <atomic>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <sstream>

namespace game_framework {
    CGameMap::CGameMap(int _stage) {

    }

    CGameMap::CGameMap() :X(10), Y(10), MW(10), MH(10) {
        sizeX = 600 / X;
        sizeY = 800 / Y;
        stage = 1;
    }

    void CGameMap::ReadFile(int stages) {
        std::stringstream filename;
        std::stringstream ss;
        string str;
        ss << stages;
        ss >> str;
        filename << "map\\Run" << str << ".txt";
        ifstream is(filename.str(), std::ifstream::binary);
        std::string line;
        int i = 0;
        while (getline(is, line)) {
            for (int j = 0; j < sizeY; j++) {
                map[i][j] = line[j] - '0';
            }
            i++;
        }
        is.close();
    }

    void CGameMap::LoadBitmap() {
        blue.LoadBitmap(DOT, 1);
    }

    void CGameMap::OnShow() {
        for (int i = 0; i < 80; i++) {
            for (int j = 0; j < 60; j++) {
                switch (map[j][i]) {
                case 1:
                    break;
                case 0:
                    blue.SetTopLeft((10 * i), (10 * j));
                    blue.ShowBitmap();
                    break;
                }
            }
        }
    }

    void CGameMap::setMap(int x, int y, int v) {
        map[y][x] = v;
    }

    void CGameMap::SetStage(int _stage) {
        stage = _stage;
    }

    int CGameMap::mapCoordinate(int x, int y) {
        return map[y][x];
    }

    int CGameMap::GetX() {
        return X;
    }

    int CGameMap::GetY() {
        return Y;
    }

    int CGameMap::GetMH() {
        return MH;
    }

    int CGameMap::GetMW() {
        return MW;
    }

    int CGameMap::GetSizeX() {
        return sizeX;
    }

    int CGameMap::GetSizeY() {
        return sizeY;
    }

    CGameMap::~CGameMap() {
    }

    RedPlayer::RedPlayer()
    {
        Initialize(stage);
    }

    int RedPlayer::GetX1()
    {
        return x;
    }

    int RedPlayer::GetY1()
    {
        return y;
    }

    int RedPlayer::GetX2()
    {
        return x + animation.Width();
    }

    int RedPlayer::GetY2()
    {
        return y + animation.Height();
    }
    void RedPlayer::Initialize(int stages)
    {
        stage = stages;
        gamemap.~CGameMap();
        gamemap.ReadFile(stages);
        int INITIAL_VELOCITY;    // 初始上升速度
        if (stages == 1)
        {
            INITIAL_VELOCITY = 11;
        }
        else
        {
            INITIAL_VELOCITY = 15;
        }
        const int FLOOR = 579;// 地板座標
        const int X_POS = 42;
        const int Y_POS = 542;
        floor = FLOOR;
        isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isOnBox = isFrontBox = isOnButton = false;
        rising = false;
        initial_velocity = INITIAL_VELOCITY;
        velocity = initial_velocity;
        for (int i = 0; i < 60; i++)
        {
            for (int j = 0; j < 80; j++)
            {
                map[i][j] = gamemap.mapCoordinate(j, i);
            }
        }
        for (int j = 0; j < 800; j++)
        {
            x_edge[j] = j + 1;
        }
        for (int j = 0; j < 600; j++)
        {
            y_edge[j] = j + 1;
        }
    }
    void RedPlayer::LoadBitmap()
    {
        animation.AddBitmap(FIRE_RIGHT_RUN_1, RGB(255, 255, 255));
        animation.AddBitmap(FIRE_RIGHT_RUN_2, RGB(255, 255, 255));
        animation.AddBitmap(FIRE_RIGHT_RUN_3, RGB(255, 255, 255));
        animation1.AddBitmap(FIRE_LEFT_RUN_1, RGB(255, 255, 255));
        animation1.AddBitmap(FIRE_LEFT_RUN_2, RGB(255, 255, 255));
        animation1.AddBitmap(FIRE_LEFT_RUN_3, RGB(255, 255, 255));
        bit.LoadBitmap(FIRE_FRONT, RGB(255, 255, 255));
    }
    bool RedPlayer::frontBox(int bx, int by)
    {
        int x1 = bx;
        int y1 = by;
        int x2 = x1 + 35;
        int y2 = y1 + 35;
        return (x + 40 >= x1 && x <= x2 && y + 40 >= y1 && y <= y2);
    }
    bool RedPlayer::onBox(int bx, int by)
    {
        int x1 = bx;
        int y1 = by - 20;
        int x2 = x1 + 35;
        int y2 = y1 + 40;
        return (x + 40 >= x1 && x <= x2 && y + 40 >= y1 && y <= y2);
    }
    void RedPlayer::setOnBox(bool a) {
        isOnBox = a;
    }
    void RedPlayer::setFront(bool a)
    {
        isFrontBox = a;
    }
    bool RedPlayer::isLeftRightEmpty(int x, int y, int value)
    {
        int x_coord = 0, ycoord = 0;
        if (x < 21 || x>788 || y < 21 || y>578)
        {
            return 0;
        }
        bool result = 1;
        if (value == 0) {
            for (int i = 0; i < 800; i++)
            {
                if (x == x_edge[i]) {
                    x_coord = i;
                }
            }
            for (int i = 0; i < 600; i++)
            {
                if (y + value == y_edge[i]) {
                    ycoord = i;
                }
            }
            result = map[ycoord / 10][x_coord / 10] && result;
        }
        else
        {
            for (int i = 0; i < 800; i++)
            {
                if (x == x_edge[i]) {
                    x_coord = i;
                }
            }

            for (int j = 5; j < 35; j += 3)
            {
                for (int i = 0; i < 600; i++)
                {
                    if (y + j == y_edge[i]) {
                        ycoord = i;
                    }
                }
                result = map[ycoord / 10][x_coord / 10] && result;
            }

        }

        return map[ycoord / 10][x_coord / 10];
    }
    int RedPlayer::getCoordX(int x, int y)
    {
        int x_coord = 0, ycoord = 0;
        for (int i = 0; i < 800; i++)
        {
            if (x >= x_edge[i]) {
                x_coord = i;
            }
        }
        return x_coord;
    }
    int RedPlayer::getCoordY(int x, int y)
    {
        int x_coord = 0, ycoord = 0;
        for (int i = 0; i < 600; i++)
        {
            if (y >= y_edge[i]) {
                ycoord = i;
            }
        }
        return ycoord;
    }
    void RedPlayer::setfloor()
    {
        if (!isOnButton)
        {
            if ((map[(y + 38) / 10][(x) / 10]) && (map[(y + 38) / 10][(x + 30) / 10]) == 1) {
                if ((map[(y + 48) / 10][(x) / 10]) && (map[(y + 48) / 10][(x + 30) / 10]) == 1) {
                    if ((map[(y + 58) / 10][(x) / 10]) && (map[(y + 58) / 10][(x + 30) / 10]) == 1) {
                        if ((map[(y + 68) / 10][(x) / 10]) && (map[(y + 68) / 10][(x + 30) / 10]) == 1) {
                            if ((map[(y + 78) / 10][(x) / 10]) && (map[(y + 78) / 10][(x + 30) / 10]) == 1) {
                                if ((map[(y + 88) / 10][(x) / 10]) && (map[(y + 88) / 10][(x + 30) / 10]) == 1) {
                                    if ((map[(y + 98) / 10][(x) / 10]) && (map[(y + 98) / 10][(x + 30) / 10]) == 1) {
                                        if ((map[(y + 108) / 10][(x) / 10]) && (map[(y + 108) / 10][(x + 30) / 10]) == 1) {
                                            if ((map[(y + 118) / 10][(x) / 10]) && (map[(y + 118) / 10][(x + 30) / 10]) == 1) {

                                                floor = (((y + 38) / 10) + 9) * 10;
                                            }
                                            else {
                                                floor = (((y + 38) / 10) + 8) * 10;
                                            }
                                        }
                                        else {
                                            floor = (((y + 38) / 10) + 7) * 10;
                                        }
                                    }
                                    else {
                                        floor = (((y + 38) / 10) + 6) * 10;
                                    }
                                }
                                else {
                                    floor = (((y + 38) / 10) + 5) * 10;
                                }
                            }
                            else {
                                floor = (((y + 38) / 10) + 4) * 10;
                            }
                        }
                        else {
                            floor = (((y + 38) / 10) + 3) * 10;
                        }
                    }
                    else {
                        floor = (((y + 38) / 10) + 2) * 10;
                    }
                }
                else {
                    floor = (((y + 38) / 10) + 1) * 10;
                }
            }
            else {
                floor = ((y + 38) / 10) * 10;
            }
        }

        if (floor >= 580) {
            floor = 579;
        }
        if ((x + 20 >= 122 && x + 20 < 157 && y + 40 >= 21 && y + 40 < 229) && isOnBox)
        {
            floor = 194;
        }
    }

    void RedPlayer::OnMove1() {
        if (!rising && velocity == initial_velocity) {
            y = floor - 38;
        }
    }
    void RedPlayer::OnMove()
    {
        const int STEP_SIZE = 7;
        animation.OnMove();
        animation1.OnMove();
        if (isMood) {
            for (int i = 2; i <= 8; i++) {
                map[37][i] = 0;
            }
        }
        else {
            for (int i = 2; i <= 8; i++) {
                map[37][i] = 1;
            }
        }
        if (stage == 2) {
            if (isButton2) {
                for (int i = 11; i <= 12; i++) {
                    for (int j = 35; j <= 44; j++) {
                        map[i][j] = 0;
                    }
                }
            }
            else {
                for (int i = 11; i <= 12; i++) {
                    for (int j = 35; j <= 44; j++) {
                        map[i][j] = 1;
                    }
                }
            }
            if (isButton3) {
                for (int i = 33; i <= 40; i++) {
                    for (int j = 40; j <= 41; j++) {
                        map[i][j] = 1;
                    }
                }
            }
            else {
                for (int i = 33; i <= 40; i++) {
                    for (int j = 40; j <= 41; j++) {
                        map[i][j] = 0;
                    }
                }
            }
        }
        if (!rising && velocity == initial_velocity) {
            y = floor - 38;

        }
        if (isMovingLeft)
            if (isLeftRightEmpty(x - STEP_SIZE, y, 1) && x > 20 && isFrontBox == false) {
                x -= STEP_SIZE;
                setfloor();
            }
        if (isMovingRight)
            if (isLeftRightEmpty(x + 38 + STEP_SIZE, y, 1) && x < 778) {
                x += STEP_SIZE;
                setfloor();
            }
        if (isMovingUp) {
            rising = true;
            isMovingUp = false;
        }
        if (rising) {            // 上升狀態
            if (velocity > 0) {
                if (!isLeftRightEmpty(x, y - 1, 0))
                {
                    velocity -= 2;
                    setfloor();
                }
                else
                {
                    y -= velocity;    // 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
                    velocity--;        // 受重力影響，下次的上升速度降低
                    setfloor();
                }

            }
            else {
                rising = false; // 當速度 <= 0，上升終止，下次改為下降
                velocity = 1;    // 下降的初速(velocity)為1
            }

        }
        else {                // 下降狀態
            if (y < floor - 39) {  // 當y座標還沒碰到地板
                if (velocity < 9) {
                    y += velocity;    // y軸下降(移動velocity個點，velocity的單位為 點/次)
                    velocity++;        // 受重力影響，下次的下降速度增加
                    setfloor();

                }
                else {
                    y += velocity;
                    setfloor();
                }
            }
            else {
                setfloor();
                y = floor - 38;  // 當y座標低於地板，更正為地板上
                rising = false;    // 探底反彈，下次改為上升
                velocity = initial_velocity;
                // 重設上升初始速度
            }
            isMovingUp = false;
        };
        if (isMovingDown)
            y = floor - 38;
    }
    void RedPlayer::SetButton(bool flag) {
        isButton = flag;
    }
    void RedPlayer::SetButton2(bool flag) {
        isButton2 = flag;
    }
    void RedPlayer::SetButton3(bool flag) {
        isButton3 = flag;
    }
    void RedPlayer::SetMood(bool flag) {
        isMood = flag;
    }
    void RedPlayer::MoodY(int MY) {
        MY = MY;
    }
    bool RedPlayer::butin() {
        int x1 = x;
        int y1 = y;
        int x2 = x1 + bit.Width();
        int y2 = y1 + bit.Height();
        if (x2 >= 709 && x1 < 790 && y2 >= 192 && y1 <= 292) {
            return 1;
        }
        else {
            return 0;
        }
    }

    void RedPlayer::SetFloor(int y) {
        floor = y;
    }
    void RedPlayer::SetMovingDown(bool flag)
    {
        isMovingDown = flag;
    }

    void RedPlayer::SetMovingLeft(bool flag)
    {
        isMovingLeft = flag;
    }

    void RedPlayer::SetMovingRight(bool flag)
    {
        isMovingRight = flag;
    }

    void RedPlayer::SetMovingUp(bool flag)
    {
        isMovingUp = flag;
    }

    void RedPlayer::SetXY(int nx, int ny)
    {
        x = nx; y = ny;
    }

    void RedPlayer::SetVelocity(int velocity) {
        this->velocity = velocity;
        this->initial_velocity = velocity;
    }
    void RedPlayer::OnShow() {
        if (isMovingLeft) {
            animation1.SetTopLeft(x, y);
            animation1.OnShow();
        }
        else if (isMovingRight)
        {
            animation.SetTopLeft(x, y);
            animation.OnShow();
        }

        else if (!isMovingRight && !isMovingLeft)
        {
            bit.SetTopLeft(x, y);
            bit.ShowBitmap();
        }
    }
}