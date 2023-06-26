#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <random>

//現在の局面データnow_position_strを与え、次の一手を取得するコード
//std::string  now_position_strを変えることで確認できる。
//先手勝利の24000棋譜、後手勝利の17635棋譜
//コメントを少し削除

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
    std::ifstream sente_file("win_sente.txt"); // 読み込むファイルのパスを指定
    std::ifstream gote_file("win_gote.txt");
    std::string sente_line;
    std::string gote_line;

    if (!sente_file) {
        //エラー処理
        std::cout << "file not found win_sente.txt" << std::endl;
    }
    else {
        sente_vector.clear();
        //1行ずつ読み込む
        while (std::getline(sente_file, sente_line)) {
            std::vector<std::string> temp_v = split(sente_line,",");
            //ベクターに追加
            sente_vector.push_back(temp_v);
        }
        std::cout << "sente vector size:" << sente_vector.size() << std::endl;
    }

    if (!gote_file) {
        std::cout << "file not found win_gote.txt" << std::endl;
    }
    else {
        gote_vector.clear();
        while (std::getline(gote_file, gote_line)) {
            std::vector<std::string> temp_v = split(gote_line,",");
            gote_vector.push_back(temp_v);
        }
        std::cout << "gote vector size:" << gote_vector.size() << std::endl;
    }

    //std::string position_str = ("");
    std::string  now_position_str = ("position startpos moves 2g2f 8c8d 2f2e");
    //std::string now_position_str = ("position startpos moves 7g7f 3c3d");
    //std::string now_position_str = ("position startpos moves 2g2f 8c8d 2f2e");
    //std::string now_position_str = ("position startpos moves 7g7f");
    
    std::cout << "position_str:" << now_position_str << std::endl;
    std::vector< std::string > now_position_vector = split(now_position_str, " ");
    //着手のみにする。
    //position,startpos,movesは削除する。
    for (int i = 0; i < now_position_vector.size(); i++) {
        if (now_position_vector[i]=="position" || now_position_vector[i] == "startpos" || now_position_vector[i] == "moves") {
            std::cout << "delete str:" << now_position_vector[i] << std::endl;
            //削除する。
            now_position_vector.erase(now_position_vector.begin()+i);
            i--;
        }
    }
    std::cout << "position_vectorサイズ：" << now_position_vector.size() << std::endl;

    //定跡から次の一手を返す処理
    std::vector<std::string> joseki_vector;//候補手を格納しておくベクター

    if (now_position_vector.size() % 2 == 0) {
        std::cout << "手数:" << now_position_vector.size() << " 先手です。" << std::endl;
        std::cout << "sente_vector size:" << sente_vector.size() << std::endl;
        joseki_vector.clear();//定跡ベクターの初期化

        for (int i = 0; i < sente_vector.size(); i++) {
            if (now_position_vector.size() == 0) {
                //初手の処理
                joseki_vector.push_back(sente_vector[i][0]);
            }else {
                //初手以外の処理
                if (now_position_vector.size() >= sente_vector[i].size()) {
                    //現在の手数より短い棋譜の場合は抜ける
                    //std::cout << "先手、棋譜長さ：" << sente_vector[i].size() << std::endl;
                    std::cout << "抜けます。：" << now_position_vector.size() << "：" << sente_vector[i].size() << std::endl;
                    continue;
                }
                //現在の局面の次の一手候補をベクターに格納する。
                for (int j = 0; j < now_position_vector.size(); j++) {
                    if (now_position_vector[j] != sente_vector[i][j]) {
                        break;
                    }
                    if (j == now_position_vector.size()-1) {
                        joseki_vector.push_back(sente_vector[i][now_position_vector.size()]);
                    }
                }
            }
        }
    }else {
        std::cout << "手数:" << now_position_vector.size() << " 後手です。" << std::endl;
        std::cout << "gote_vector size:" << gote_vector.size() << std::endl;
        joseki_vector.clear();//定跡ベクターの初期化

        for (int i = 0; i < gote_vector.size(); i++) {
            if (now_position_vector.size() >= gote_vector[i].size()) {
                //現在の手数より短い棋譜の場合は抜ける
                continue;
            }
            for (int j = 0; j < now_position_vector.size(); j++) {
                if (now_position_vector[j] != gote_vector[i][j]) {
                    break;
                }
                if (j == now_position_vector.size() - 1) {
                    joseki_vector.push_back(gote_vector[i][now_position_vector.size()]);
                }
            }
        }
    }
    std::cout << "定跡候補サイズ：" << joseki_vector.size() << std::endl;
    //std::cout << "定跡候補[0]：" << joseki_vector[0] << std::endl;
    //std::cout << "定跡候補[1]：" << joseki_vector[1] << std::endl;
    //std::cout << "定跡候補[2]：" << joseki_vector[2] << std::endl;
    //std::cout << "定跡候補[3]：" << joseki_vector[3] << std::endl;
    //std::cout << "定跡候補[4]：" << joseki_vector[4] << std::endl;

    std::cout << "定跡からランダムな候補種を返します。" << std::endl;
    if (joseki_vector.size() >= 1){
        std::cout << "定跡があります。" << std::endl;
        std::mt19937 engine{ std::random_device{}() };
        std::uniform_int_distribution<int> dist(0, joseki_vector.size());
        //表示
        int index = dist(engine);
        std::cout << "定跡候補手数:" << joseki_vector.size() << std::endl;
        std::cout << "index:" << index << std::endl;
        std::cout << "定跡候補手:" << joseki_vector[index] << std::endl;
    }else {
        std::cout << "定跡がありません。" << std::endl;
    }
    
    return (0);
}