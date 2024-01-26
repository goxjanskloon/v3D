#include"v3D.h"
#include<iostream>
#include<random>
inline bool keydown(int vKey){return GetAsyncKeyState(vKey)&0x8000;}
inline int genint(const int &l,const int &r){
    std::random_device rd;
    std::mt19937 gen(rd());
    return std::uniform_int_distribution<>(l,r)(gen);
}
template<typename... argT>
inline void xyprintf(const int &x,const int &y,const PIMAGE &img,const char *fmt,argT... args){
    char bf[8192];
    sprintf(bf,fmt,args...);
    outtextxy(x,y,bf,img);
}
class render:public renderer3d{
public:
    vector3d pos{0,0,0},facing{0,0,400},ud{0,1,0},rd{1,0,0};
    int xl=1000,yl=600,cx=xl>>1,cy=yl>>1;
    PIMAGE img=newimage(xl,yl);
    render &init(){
        initgraph(xl,yl,getinitmode());
        ege_enable_aa(1,img);
        setbkmode(TRANSPARENT,img);
        setfont(20,0,"Consolas",img);
        return *this;
    }
    render &flush(){
        renderer3d::render(pos,facing,ud,rd,xl,yl,img);
        cleardevice();
        putimage(0,0,img);
        cleardevice(img);
        return *this;
    }
};
void test(){
    rect3d rect({-50,50,450},{50,-50,550},{color_t(BLUE),color_t(RED),color_t(GREEN),color_t(YELLOW),color_t(BROWN),color_t(CYAN)}),rectt=rect;
    render rd;
    renderer3d_guard rg(rect,&rd);
    rd.init();
    auto c=rect.center(),udt=rd.ud,rdt=rd.rd;
    int mx,my;
    for(double t=0,dx=0,dy=0;is_run();rect=rectt,t+=0.5,Sleep(5)){
        if(keydown('W')) rd.pos.z+=10;
        if(keydown('S')) rd.pos.z-=10;
        if(keydown('A')) rd.pos.x-=10;
        if(keydown('D')) rd.pos.x+=10;
        if(keydown(' ')) rd.pos.y+=10;
        if(keydown(key_shift)) rd.pos.y-=10;
        mousepos(&mx,&my);
        dx=(rd.cy-my)*180.0/rd.cy,dy=(rd.cx-mx)*180.0/rd.cx;
        rd.ud=udt.protate({0,0,0},dx,0,0),rd.rd=rdt.protate({0,0,0},0,dy,0);
        rect.rotate(c,t,t,t);
        rd.flush();
        xyprintf(0,0,"pos=[%f,%f,%f]",rd.pos.x,rd.pos.y,rd.pos.z);
    }
}
int main(){
    test();
    return 0;
}
