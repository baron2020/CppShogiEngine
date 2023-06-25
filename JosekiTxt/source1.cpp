#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//行数が増えても問題なく読み込みが出来るか確認する。
//win_sente.txt:24000行
//win_gote.txt :17635行
//カンマで区切り、ベクターに追加する。

std::vector<std::string> split(std::string str, std::string sep) {
    std::string separator = sep;
    std::vector<std::string> result;
    std::string tstr = str + separator;
    long l = tstr.length(), sl = separator.length();
    std::string::size_type pos = 0, prev = 0;

    for (; pos < l && (pos = tstr.find(separator, pos)) != std::string::npos; prev = (pos += sl)) {
        result.emplace_back(tstr, prev, pos - prev);
    }
    //std::cout << "resultサイズ：" << result.size() << '\n';
    return result;
}

int main() {
    std::vector<std::vector<std::string>> sente_vector;
    std::vector<std::vector<std::string>> gote_vector;
    //sente_vector.clear();
    //gote_vector.clear();

    std::ifstream sente_file("win_sente.txt"); // 読み込むファイルのパスを指定
    std::ifstream gote_file("win_gote.txt");
    std::string sente_line;
    std::string gote_line;

    if (!sente_file) {
        //エラー処理
        std::cout << "ファイルが存在しません。1" << std::endl;
    }
    else {
        //1行ずつ読み込む
        while (std::getline(sente_file, sente_line)) {
            //std::cout << sente_line << std::endl;
            std::vector<std::string> temp_v = split(sente_line,",");
            //ベクターに追加
            sente_vector.push_back(temp_v);
        }
        std::cout << "ベクターサイズ1：" << sente_vector.size() << std::endl;
    }

    if (!gote_file) {
        //エラー処理
        std::cout << "ファイルが存在しません。2" << std::endl;
    }
    else {
        while (std::getline(gote_file, gote_line)) {
            //std::cout << gote_line << std::endl;
            std::vector<std::string> temp_v = split(gote_line,",");
            //ベクターに追加
            gote_vector.push_back(temp_v);
        }
        std::cout << "ベクターサイズ2：" << gote_vector.size() << std::endl;
    }

    //std::string position_str = ("");
    // std::string position_str = ("position startpos moves");
    std::string position_str = ("position startpos moves 7g7f 3c3d 2g2f");

    std::cout << "position_str:" << position_str << std::endl;
    std::vector< std::string > position_vector = split(position_str, " ");
    //着手のみにする。
    //position,startpos,movesは削除する。
    for (int i = 0; i < position_vector.size(); i++) {
        if (position_vector[i]=="position" || position_vector[i] == "startpos" || position_vector[i] == "moves") {            
            std::string target_str = position_vector[i];
            //削除する。
            position_vector.erase(position_vector.begin()+i);
            std::cout <<"削除します:" << target_str << std::endl;
            i--;
        }
    }
    std::cout << "position_vectorサイズ：" << position_vector.size() << std::endl;
    std::cout << "position_vector[0]：" << position_vector[0] << std::endl;
    std::cout << "position_vector[1]：" << position_vector[1] << std::endl;
    //std::cout << "position_vector[2]：" << position_vector[2] << std::endl;
    //std::cout << "position_vector[3]：" << position_vector[3] << std::endl;

    //position_vector.clear();
    //std::cout << "position_vectorサイズ：" << position_vector.size() << std::endl;

    return (0);
}
