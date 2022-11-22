#include<ncurses.h>
#include<math.h>
#include <sstream>
#include <types.h>


class dobj
{
public:
    dobj() = default;

    dobj(const char* t, vec2i s, vec2f v){
        _s=s;
        _v=v;
        _t = (char*)malloc(sizeof(char)*s.x*s.y);
        int i =0;
        for(int y=0;y<_s.y;y++){
            for(int x=0;x<_s.x;x++){
                _t[i] = t[i];
                i++;
            }
        }
    }

    ~dobj(){
        
    }

    void draw(){
        int i =0;
        for(int y=0;y<_s.y;y++){
            for(int x=0;x<_s.x;x++){
                //if(_t[i]==' ') continue; 
                if(_t[i]==' '){
                    ++i;
                }
                else{
                    mvaddch(y+_v.y,x+_v.x,_t[i]);
                    ++i;
                }
            }
        }
    }

    void update_pos(vec2f v){
        _v=v;
    }

    vec2f _v;
    vec2i _s;
    char* _t;
};


class player{
public:
    player(vec2f p){
        _p=p;
        std::stringstream ss;
        ss<<"_O_";
        ss<<" A ";
        _d = dobj( ss.str().c_str() , vec2i{3,2}, vec2f{_p.x-1.5f,_p.y-1.0f});
    }
    void update_pos(vec2f p){
        _p=p;
        _d.update_pos({_p.x-1.5f, _p.y-1.0f});
    }
    vec2f _p;
    dobj _d;
};

class tree{
public:
    tree(vec2f p){
        _p = p;
        std::stringstream ss;
        ss<<" c8% ";
        ss<<"s++G$";
        ss<<"g*=% ";
        ss<<"  I  ";
        ss<<" .I_ ";  
        _d = dobj(  ss.str().c_str(), {5,5}, {_p.x-2.5f,_p.y-2.5f});
    }

    vec2f _p;
    dobj _d;
};

void draw_bg(){
    for(int y=0;y<LINES;y++){
        for(int x=0;x<COLS;x++){
            char c = ' ';
            if(x==0 || y==0 || x==COLS-1 || y==LINES-1){
                c='&';
            }
            mvaddch(y,x,c);
        }
    }
}


int main(){
    
    initscr();
    noecho();
    timeout(0);
    leaveok(stdscr, TRUE);
    curs_set(0);


    bool run=true;
    char keypress=' ';
    
    player p1({20,20});
    tree trs[4] = {tree({10,10}),
                    tree({20,30}),
                    tree({30,6}),
                    tree({15,30})};
    

    while(run){
        draw_bg();
        
        p1._d.draw();
        
        for(tree tr : trs){
            tr._d.draw();
        }
        

        vec2f pos = p1._p;

        if((keypress = wgetch(stdscr)) != ERR){
            switch (keypress)
            {
            case 'q':
                run=false;
                break;
            case 'w':
                pos.y--;
                if(pos.y<2) pos.y=2;
                p1.update_pos(pos);
                break;
            case 'a':
                pos.x--;
                if(pos.x<3) pos.x=3;
                p1.update_pos(pos);
                break;
            case 's':
                pos.y++;
                if(pos.y>LINES-2) pos.y=LINES-2;
                p1.update_pos(pos);
                break;
            case 'd':
                pos.x++;
                if(pos.x>COLS-2) pos.x=COLS-2;
                p1.update_pos(pos);
                break;
            default:
                break;
            }
            
        }
    }


    endwin();

    return 0;
}