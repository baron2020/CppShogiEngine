#include<iostream>
#include<string>

//CppShogi2：CppShogi1からの変更点として、思考局面を受け取る機能を追加。
//思考局面：46行目のpositionで確認できる。

int main() {
	std::string cmd;
	std::string position;
	bool positionFlg = false;
	std::cout << "コマンドを入力してください。\n";
	std::cout << "quitで終了します。\n";

	while (true) {
		std::cin >> cmd;
		//std::cout << "受け取ったコマンド：" << cmd << "\n";
		
		if(positionFlg && cmd!="go") {
			//局面情報の受け取り
			//平手はstartposから始まる
			//例：position startpos moves 7g7f 3c3d 2g2f
			position += " ";
			position += cmd;
			std::cout << "受け取った局面情報：" << cmd << "\n";
		}
		if (cmd == "usi") {
			//ソフト名
			std::cout << "id name CppShogi2\n";
			//開発者名
			std::cout << "id author yukawa\n";
			std::cout << "usiok\n";
		}
		else if (cmd == "isready") {
			//対局準備
			//読み込みが必要ならここで処理する。
			std::cout << "readyok\n";
		}
		else if (cmd == "usinewgame") {
			//対局開始の合図
			//何もしない
		}
		else if (cmd == "position") {
			//positionコマンドの後に局面が送られてくるため、局面受け取りのを準備する。
			std::cout << "positionコマンド\n";
			position.clear();
			position="position";
			positionFlg = true;
		}
		else if (cmd == "go") {
			//思考開始
			//先手26歩を指す。
			positionFlg = false;
			std::cout << "思考局面：" << position << "\n";
			std::cout << "goコマンド\n";
			std::cout << "bestmove 2g2f\n";
		}
		else if (cmd == "quit") {
			//エンジン停止
			break;
		}
	}
	//エンジンを終了させる。
	std::cout << "終了します。\n";
	exit(1);
	return 0;
}