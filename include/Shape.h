//
// Created by SunnyTeng on 2020/12/31.
//
#ifndef __SHAPE_ELEM_H__
#define __SHAPE_ELEM_H__
#include "ToolFunction.h"
#include <iostream>
#include <string>
#include <vector>
#include<string.h>
#include <stdlib.h>


typedef unsigned char  uint8 ;
typedef unsigned short uint16 ;
typedef unsigned int   uint32 ;
typedef unsigned long long uint64 ;

typedef char  int8 ;
typedef short int16 ;
typedef int   int32 ;
typedef long long int64 ;

/**
 * @class: DrawI
 * @brief: 图形绘画接口
 */
class DrawI {
public:
    virtual  void Paint(char** buf, int32 iMaxRow, int32 iMaxCol) = 0;
};



/**
 * @class: ConsoleCanvas
 * @brief: 控制台字符画布背景
 * @detail: 视窗为屏幕左上角，通过注册的paint接口对注册的图形进行绘画
     坐标系，与正常的坐标系有点区别，注意（直线斜率有区别）
       +----------------------------> （X)
       |
       |
       |
       |
       |
       V
       (Y)
*/
class ConsoleCanvas {
public:
    ConsoleCanvas():m_IsShowWindow(false),m_iRowSize(100),m_iColSize(100){
        m_bufCanvas = new char*[m_iRowSize] ;
        for(int32 i=0 ; i < m_iRowSize; ++i) {
            m_bufCanvas[i] = new char[m_iColSize] ;
            memset(m_bufCanvas[i],' ', m_iColSize) ;
        }
    }
    void Paint() {
        std::cout << "-----------------------------------------------" << std::endl ;
        for(int32 i=0 ; i < m_iRowSize; ++i) {
            std::cout << m_bufCanvas[i] << std::endl ;
        }
        std::cout << "-----------------------------------------------" << std::endl ;
        std::cout << std::endl ;
    }
    virtual ~ConsoleCanvas() {
        for(int32 i=0 ; i < m_iRowSize; ++i) {
            delete []m_bufCanvas[i] ;
        }
        delete []m_bufCanvas ;
        m_bufCanvas = NULL ;
    }
    void DrawShape(DrawI* di) {
        di->Paint(m_bufCanvas, m_iRowSize, m_iColSize) ;
    }
    void SetShowWindow(const bool bShow) {
        m_IsShowWindow = bShow ;
    }
    void SetWindowSize(const int32 iRowSize, const int32 iColSize) {
        m_iRowSize = iRowSize ;
        m_iColSize = iColSize ;
    }
private:
    bool m_IsShowWindow ;
    char** m_bufCanvas ; /// 绘画缓存区
    int32 m_iRowSize ;   /// 行宽
    int32 m_iColSize ;   /// 列宽
    std::vector<DrawI*> m_vecShape ;
};



/**
 @class: Point
 @brief: 图形坐标点信息
*/
class Point : public DrawI {
public:
    Point(): m_iX(0),m_iY(0) {
    }
    Point(int32 iX, int32 iY): m_iX(iX),m_iY(iY) {
    }
    virtual void Paint(char** buf, int32 iMaxRow, int32 iMaxCol) {
        if(m_iX < iMaxRow && m_iY < iMaxCol) {
            buf[m_iX][m_iY] = '*' ;
            std::cout << "drawshape <point> at (" << m_iX << "," << m_iY << ")" << std::endl ;
        }
    }
    int32 X() const {
        return m_iX ;
    }
    int32 Y() const {
        return m_iY ;
    }
    void Set(int32 x, int32 y) {
        m_iX = x ;
        m_iY = y ;
    }
    friend std::ostream & operator<<(std::ostream& output,const Point& p) {
        output << "{\"x\":" << p.X() << ",\"y\":" << p.Y() << "}" ;
        return output ;
    }
public:
    int32 m_iX ;   /// x坐标
    int32 m_iY ;   /// y坐标
} ;



/**
 @class: StraightLine
 @brief: 直线
*/
class StraightLine : public DrawI {
public:
    StraightLine():
            m_chRowElem('*'),m_chColElem('*'),m_uiDirection(0),m_pointBeg(0, 0),m_pointEnd(0, 0) {

    }
    StraightLine(int32 iBegX, int32 iBegY, int32 iEndX, int32 iEndY):
            m_chRowElem('*'),m_chColElem('*'),m_uiDirection(0), m_pointBeg(iBegX,iBegY),m_pointEnd(iEndX,iEndY) {
    }
    StraightLine(const Point& beg, const Point& end):
            m_chRowElem('*'),m_chColElem('*'),m_uiDirection(0), m_pointBeg(beg),m_pointEnd(end) {
    }
public:
    void SetEndpoint(const Point& beg, const Point& end){
        m_pointBeg = beg ;
        m_pointEnd = end ;
    }
    void SetEndpoint(int32 iBegX, int32 iBegY, int32 iEndX, int32 iEndY) {
        m_pointBeg.Set(iBegX, iBegY) ;
        m_pointEnd.Set(iEndX, iEndY) ;
    }
    void SetDirection(uint8 uiDirect) {
        m_uiDirection = uiDirect ;
    }
    void SetFillElement(const char rowElem, const char colElem) {
        m_chRowElem = rowElem ;
        m_chColElem = colElem ;
    }
    virtual void Paint(char** buf, int32 iMaxRow, int32 iMaxCol) {
        int32 lx = m_pointBeg.X() ;
        int32 ly = m_pointBeg.Y() ;
        int32 rx = m_pointEnd.X() ;
        int32 ry = m_pointEnd.Y() ;
        /// 数据断言
        if(lx > iMaxRow || rx > iMaxRow ) {
            return ;
        }
        if(ly > iMaxCol || ry > iMaxCol) {
            return ;
        }
        int32 i, j ,stepx, stepy ;
        if(lx > rx) {
            stepx = -1 ;
        } else {
            stepx = 1 ;
        }
        if(ly > ry) {
            stepy = -1 ;
        } else {
            stepy = 1 ;
        }
        int32 iDirectX, iDirectY ;
        if(m_uiDirection == 0) { // 先横后竖
            iDirectX = lx ;
            iDirectY = ry ;
        } else {  // 先竖后横
            iDirectX = rx ;
            iDirectY = ly ;
        }
        i = lx ;
        while(i != rx && i < iMaxRow) {
            buf[iDirectY][i] = m_chRowElem;
            i += stepx ;
        }
        j = ly ;
        while(j != ry && i < iMaxCol) {
            buf[j][iDirectX] = m_chColElem ;
            j += stepy ;
        }
    }
    friend std::ostream & operator<<(std::ostream& output,const StraightLine& sl) {
        output << "{\"begpoint\":" << sl.m_pointBeg << ",\"endpoint\":" << sl.m_pointEnd << "}" ;
        return output ;
    }
private:
    char m_chRowElem ;   /// 行直线填充字符
    char m_chColElem ;   /// 列执行填充字节
    uint8 m_uiDirection ;/// 执行方向 0:横起笔 1:竖起笔

    Point m_pointBeg ;   /// 起点
    Point m_pointEnd ;   /// 终点
};




/**
 @class: Rectangle
 @brief: 矩形信息
 @detail: 矩形基本单元
 */
class Rectangle : public DrawI {
public:
    Rectangle(): m_chRowElem('*'), m_chColElem('*'), m_pointBeg(0,0), m_pointEnd(0,0) {
    }
    Rectangle(int32 iLeftX, int32 iLeftY, int32 iWidth, int32 iHeight)
            :m_chRowElem('*'), m_chColElem('*'), m_pointBeg(iLeftX,iLeftY),m_pointEnd(iLeftX + iWidth,iLeftY + iHeight) {
    }
    Rectangle(const Point& pointBeg, const Point& pointEnd)
            :m_chRowElem('*'),m_chColElem('*'),m_pointBeg(pointBeg),m_pointEnd(pointEnd) {
    }
    Rectangle(const Point& pointBeg, int32 iWidth, int32 iHeight):
            m_chRowElem('*'), m_chColElem('*'),m_pointBeg(pointBeg), m_pointEnd(pointBeg.X() + iWidth, pointBeg.Y() + iHeight){
    }
public:
    void Reset(int32 iLeftX, int32 iLeftY, int32 iWidth, int32 iHeight) {
        m_pointBeg.Set(iLeftX, iLeftY) ;
        m_pointEnd.Set(iLeftX +  iWidth, iLeftY + iHeight) ;
    }
    void Rest(const Point& pointBeg, int32 iWidth, int32 iHeight) {
        m_pointBeg = pointBeg ;
        m_pointEnd.Set(pointBeg.X() + iWidth, pointBeg.Y() + iHeight) ;
    }

    /// 矩形宽
    int32 Width() const {
        return m_pointEnd.X() - m_pointBeg.X() ;
    }
    /// 矩形高
    int32 Height() const {
        return m_pointEnd.Y() - m_pointBeg.Y() ;
    }
    /// 矩形中心点
    Point CentralPoint() const {
        return Point((m_pointBeg.X() + m_pointEnd.X())/2, (m_pointBeg.Y() + m_pointEnd.Y())/2) ;
    }
    /// 矩形左上角顶点
    Point LeftTopPoint() {
        return m_pointBeg ;
    }
    void SetFillElement(const char rowElem, const char colElem) {
        m_chRowElem = rowElem ;
        m_chColElem = colElem ;
    }
    void SetText(const std::string& strText) {
        m_strText = strText ;
    }
    void  Coordinate(Point& topLeft, Point& bottomRight) const {
        topLeft = m_pointBeg ;
        bottomRight = m_pointEnd ;
    }
    void JoinShape(const Rectangle& obj, StraightLine& sl) {
        Point btl, bbr;
        obj.Coordinate(btl, bbr);
        int32 bx, by, bw, bh;     // obj 中心位置: (bx,by), 宽半径: bw, 高半径: bh
        bx = (btl.X() + bbr.X()) / 2;
        by = (btl.Y() + bbr.Y()) / 2;
        bw = obj.Width() / 2;
        bh = obj.Height() / 2;

        int32 ax, ay, aw, ah;    //
        ax = (m_pointBeg.X() + m_pointEnd.X()) / 2;
        ay = (m_pointBeg.Y() + m_pointEnd.Y()) / 2;
        aw = Width() / 2;
        ah = Height() / 2;
        int32 px, py, qx, qy, direct;
        direct = 0 ;
        if (ax == bx) {
            if (ay > by) {
                px = ax - aw;
                py = ay;
                qx = bx + bw;
                qy = by;
            } else {
                px = ax + aw;
                py = ay;
                qx = bx - bw;
                qy = by;
            }
        } else {
            if (ax > bx) {    /// a指向左边的点
                swap(ax, bx);
                swap(ay, by);
                swap(aw, bw);
                swap(ah, bh);
            }
            double ka = double(ah) / double(aw) ;
            double kb = double(bh) / double(bw) ;
            double kc = double(by - ay) / double(bx - ax) ;
            if(kc < 0) {
                kc = -kc ;
                if(ka > kc) {
                    direct = 1 ;
                    px = ax + aw ;
                    py = ay ;
                } else {
                    px = ax ;
                    py = ay - ah ;
                }
                if(kb > kc) {
                    qx = bx - bw ;
                    qy = by ;
                } else {
                    qx = bx ;
                    qy = by + bh ;
                }
            } else {
                if(ka > kc) {
                    direct = 1 ;
                    px = ax + aw ;
                    py = py ;
                } else {
                    px = ax ;
                    py = ay + ah ;
                }
                if(kb > kc) {
                    qx = bx ;
                    qy = by - bh ;
                } else {
                    qx = bx - bw ;
                    qy = by ;
                }
            }
        }
        sl.SetEndpoint(px, py, qx, qy) ;
        sl.SetDirection(direct) ;
    }
public:
    virtual void Paint(char** buf, int32 iMaxRow, int32 iMaxCol) {
        int32 lx = m_pointBeg.X() ;
        int32 ly = m_pointBeg.Y() ;
        int32 rx = m_pointEnd.X() ;
        int32 ry = m_pointEnd.Y() ;
        /// 数据断言
        if(lx > iMaxRow || rx > iMaxRow ) {
            return ;
        }
        if(ly > iMaxCol || ry > iMaxCol) {
            return ;
        }
        int32 i,j, stepx, stepy;
        if(lx > rx) {
            stepx = -1 ;
        } else {
            stepx = 1 ;
        }
        if(ly > ry) {
            stepy = - 1;
        } else {
            stepy = 1 ;
        }

        i = (ly + ry) / 2 ;
        j = lx + 2 ;
        size_t txtSize = m_strText.size() ;
        if(txtSize > (iMaxCol - j)) {
            txtSize = iMaxCol - j ;
        }
        memcpy(buf[i]+j,m_strText.c_str(), txtSize) ;

        i = lx ;
        while(i != rx && i < iMaxRow) {
            buf[ly][i] = m_chColElem;
            buf[ry][i] = m_chColElem ;
            i += stepx ;
        }
        j = ly ;
        while(j != ry && j < iMaxCol) {
            buf[j][lx] = m_chRowElem ;
            buf[j][rx] = m_chRowElem ;
            j += stepy ;
        }
    }
private:
    bool m_IsFill ;      /// 是否填充
    bool m_IsRandFill ;  /// 是否填充随机字符
    char m_chRowElem ;   /// 行填充字符
    char m_chColElem ;   /// 列填充字符
    Point m_pointBeg ;   /// 矩形左上点
    Point m_pointEnd ;   /// 矩形右下点

    std::string m_strText ;   /// 矩形内部文本
};


#endif // __SHAPE_ELEM_H__
