#include <iostream>
#include <map>
#include <vector>

struct Vertex{
    int number;
    bool flag;
    std::map<char,int> edge;
    std::map<char,int> auto_move;
    int suffix_link;
    int parent;
    char symbol;

    Vertex(int m_parent,char m_symbol) {
        flag = false;
        number = 0;
        suffix_link = -1;
        parent = m_parent;
        symbol = m_symbol;
    }
};

class AK{
    std::vector <Vertex> bohr;
    std::vector <std::string> patterns;
    int counter_of_ver;
public:
    AK(){
        bohr.push_back(Vertex(0,0));
        counter_of_ver = 1;
    }


    void add_string(const std::string& pattern){
        size_t tmp = 0;
        patterns.push_back(pattern);
        for (auto sym : pattern) {
            if(bohr[tmp].edge.find(sym) == bohr[tmp].edge.end()){
                bohr.push_back(Vertex(tmp, sym));
                bohr[tmp].edge[sym] = counter_of_ver++;
            }
            tmp = bohr[tmp].edge[sym];
        }
        bohr[tmp].flag = true;
        bohr[tmp].number = patterns.size();
    }


    void find_all_pos(const std::string& str){
        int tmp = 0;
        for(int i = 0; i < str.size(); i++){
            tmp = get_auto_move(tmp, str[i]);
            for(int node = tmp; node != 0; node = get_suffix_link(node)){
                if (bohr[node].flag){
                    int pat = bohr[node].number;
                    int position = i - patterns[pat-1].size()+2;
                    std::cout<< position << " " << pat << std::endl;
                }
            }
        }
    }

    int get_suffix_link(int node){
            if(bohr[node].suffix_link == -1)
                if(!node || !bohr[node].parent)
                    bohr[node].suffix_link = 0;
                else
                    bohr[node].suffix_link = get_auto_move(get_suffix_link(bohr[node].parent), bohr[node].symbol);
            return bohr[node].suffix_link;
        }


    int get_auto_move(int node, char symbol){
            if(bohr[node].auto_move.find(symbol) == bohr[node].auto_move.end())
                if(bohr[node].edge.find(symbol) != bohr[node].edge.end())
                    bohr[node].auto_move[symbol]=bohr[node].edge[symbol];
                else
                    bohr[node].auto_move[symbol]= (!node) ? 0 : get_auto_move(get_suffix_link(node),symbol);
            return bohr[node].auto_move[symbol];
        }
};

int main()
{
    AK ak;
    std::string text, pattern;
    int num;
    std::cin >> text;
    std::cin >> num;
    for(int i = 0; i < num; i++) {
        std::cin >> pattern;
        ak.add_string(pattern);
    }
    ak.find_all_pos(text);
    return 0;

}
