#include "Shape.h"

#include<string>
#include <iostream>



int draw_point() {
    ConsoleCanvas canvas ;
    canvas.SetShowWindow(true) ;
    Point p1(1,20) ;
    canvas.DrawShape(&p1) ;
    canvas.Paint() ;
    return 0;
}

int draw_straightline() {
    ConsoleCanvas canvas ;
    canvas.SetShowWindow(true) ;
    StraightLine sl1(0,0,10,10) ;
    sl1.SetDirection(0) ; /// 先横后竖
    sl1.SetFillElement('-','|') ;
    std::cout << sl1 << std::endl ;
    canvas.DrawShape(&sl1) ;  // 画布绘制线

    StraightLine sl2(10,4,38,32) ;
    sl2.SetDirection(1) ; /// 先竖后横
    sl2.SetFillElement('*','*') ;
    std::cout << sl2 << std::endl ;
    canvas.DrawShape(&sl2) ;

    canvas.Paint() ;
    return 0;
}

int draw_rectangle() {
    ConsoleCanvas canvas ;
    canvas.SetShowWindow(true) ;
    Rectangle rect1(10,10,20,4) ;
    rect1.SetText("hello world") ;
    canvas.DrawShape(&rect1) ;
    canvas.Paint() ;
    return 0 ;
}

int draw_rectangle_join() {
    ConsoleCanvas canvas ;
    canvas.SetShowWindow(true) ;
    Rectangle rect1(0,0,20,4) ;
    Rectangle rect2(30,30,20,4) ;
    rect1.SetText("111") ;
    rect2.SetText("222") ;
    StraightLine sl ;
    rect1.JoinShape(rect2,sl) ;

    canvas.DrawShape(&rect1) ;
    canvas.DrawShape(&rect2) ;
    std::cout << sl << std::endl ;
    canvas.DrawShape(&sl) ;
    canvas.Paint() ;
    return 0 ;
}

int main() {
    // draw_point() ;
    // draw_straightline() ;
    // draw_rectangle() ;
    draw_rectangle_join() ;
    return 0 ;
}









