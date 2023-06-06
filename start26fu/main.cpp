#include<iostream>
#include<string>

//ビルドで出来たexeファイルは将棋所にエンジン登録できます。
//先手番なら初手26歩を返します。
//quitの入力を受け取ると終了します。
//その他のコマンド：usi,isready,usinewgame,go,quit

int main() {
	while (true) {
		std::string cmd;
		std::cout << "コマンドを入力してください。\n";
		std::cout << "quitで終了します。\n";

		std::cin >> cmd;
		if (cmd == "usi") {
			//ソフト名
			std::cout << "id name yukawa shogi1\n";
			//開発者名
			std::cout << "id author yukawa\n";
			std::cout << "usiok\n";
		}else if (cmd == "isready") {
			//対局準備
			//読み込みが必要ならここで処理する。
			std::cout << "readyok\n";
		}
		else if (cmd == "usinewgame") {
			//対局開始の合図
			//何もしない
		}
		else if (cmd == "go") {
			//思考開始
			//先手26歩を指す。
			std::cout << "bestmove 2g2f\n";
		}else if (cmd == "quit") {
			//エンジン停止
			break;
		}
	}
	//エンジンを終了させる。
	std::cout << "終了します。\n";
	exit(1);
	return 0;
}