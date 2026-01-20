/*
- dùng vector để lưu vị trí các đoạn của con rắn(nó là mảng động )
cấu trúc dữ liệu là gì 
tại sao lại dùng nó

*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

using namespace std;

class SnakeGame {
private:
    const int RONG = 60;
    const int CAO = 35;
    vector<pair<int, int>> ran;
    pair<int, int> thucAn;
    int diem;
    char huong;
    bool ketThuc;
    bool batDau;
    
    void cauHinhTerminal(bool enable) {
        static struct termios oldt, newt;
        if (enable) {
            tcgetattr(STDIN_FILENO, &oldt);
            newt = oldt;
            newt.c_lflag &= ~(ICANON | ECHO);
            tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        } else {
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        }
    }
    
    bool coPhimNhan() {
        struct termios oldt, newt;
        int ch;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if(ch != EOF) {
            ungetc(ch, stdin);
            return true;
        }
        return false;
    }

public:
    SnakeGame() : diem(0), huong('d'), ketThuc(false), batDau(false) {
        srand(time(0));
        
        // Khởi tạo rắn cách xa tường
        int startX = 10;
        int startY = CAO / 2;
        
        ran.push_back({startX, startY});
        ran.push_back({startX-1, startY});
        ran.push_back({startX-2, startY});
        
        taoThucAn();
        cauHinhTerminal(true);
    }
    
    ~SnakeGame() { 
        cauHinhTerminal(false); 
    }
    
    void taoThucAn() {
        bool hopLe;
        do {
            hopLe = true;
            thucAn.first = rand() % (RONG-4) + 2;
            thucAn.second = rand() % (CAO-4) + 2;
            
            for (const auto& doan : ran) {
                if (doan.first == thucAn.first && doan.second == thucAn.second) {
                    hopLe = false;
                    break;
                }
            }
        } while (!hopLe);
    }
    
    void veManHinh() {
        system("clear");
        
        cout << "🐍 GAME SNAKE - MÀN HÌNH LỚN 🍎 - Điểm: " << diem << " - Độ dài: " << ran.size() << endl;
        
        // Vẽ khung trên
        cout << "╔";
        for (int i = 0; i < RONG; i++) cout << "═";
        cout << "╗" << endl;
        
        for (int y = 0; y < CAO; y++) {
            cout << "║";
            for (int x = 0; x < RONG; x++) {
                bool laDau = false;
                bool laThan = false;
                bool laThucAn = false;
                
                // Kiểm tra đầu rắn
                if (!ran.empty() && ran[0].first == x && ran[0].second == y) {
                    laDau = true;
                }
                // Kiểm tra thân rắn
                else {
                    for (int i = 1; i < ran.size(); i++) {
                        if (ran[i].first == x && ran[i].second == y) {
                            laThan = true;
                            break;
                        }
                    }
                }
                
                // Kiểm tra thức ăn
                if (thucAn.first == x && thucAn.second == y) {
                    laThucAn = true;
                }
                
                // Vẽ ký tự
                if (laDau) cout << "🔸";
                else if (laThan) cout << "○";
                else if (laThucAn) cout << "🍎";
                else cout << " ";
            }
            cout << "║" << endl;
        }
        
        // Vẽ khung dưới
        cout << "╚";
        for (int i = 0; i < RONG; i++) cout << "═";
        cout << "╝" << endl;
        
        cout << "Điều khiển: W-A-S-D | Thoát: X" << endl;
        
        if (!batDau) {
            cout << "🎮 NHẤN PHÍM BẤT KỲ ĐỂ BẮT ĐẦU!" << endl;
        }
        
        if (ketThuc) {
            cout << "💀 GAME OVER! Nhấn phím để thoát..." << endl;
        }
    }
    
    void xuLyInput() {
        if (coPhimNhan()) {
            char phim = getchar();
            
            if (ketThuc) {
                return; // Đã kết thúc, không xử lý thêm
            }
            
            if (!batDau) {
                batDau = true;
                return;
            }
            
            switch (phim) {
                case 'w': if (huong != 's') huong = 'w'; break;
                case 's': if (huong != 'w') huong = 's'; break;
                case 'a': if (huong != 'd') huong = 'a'; break;
                case 'd': if (huong != 'a') huong = 'd'; break;
                case 'x': ketThuc = true; break;
            }
        }
    }
    
    void capNhatGame() {
        if (!batDau || ketThuc) return;
        
        // Lấy vị trí đầu mới
        auto dauMoi = ran[0];
        
        switch (huong) {
            case 'w': dauMoi.second--; break;
            case 's': dauMoi.second++; break;
            case 'a': dauMoi.first--; break;
            case 'd': dauMoi.first++; break;
        }
        
        // Kiểm tra va chạm tường
        if (dauMoi.first < 0 || dauMoi.first >= RONG || 
            dauMoi.second < 0 || dauMoi.second >= CAO) {
            ketThuc = true;
            return;
        }
        
        // Kiểm tra va chạm thân
        for (int i = 1; i < ran.size(); i++) {
            if (ran[i].first == dauMoi.first && ran[i].second == dauMoi.second) {
                ketThuc = true;
                return;
            }
        }
        
        // Di chuyển rắn
        ran.insert(ran.begin(), dauMoi);
        
        // Kiểm tra ăn thức ăn
        if (dauMoi.first == thucAn.first && dauMoi.second == thucAn.second) {
            diem += 10;
            taoThucAn();
        } else {
            ran.pop_back();
        }
    }
    
    void chay() {
        // 🔥 CHỈ hiển thị 1 lần duy nhất khi bắt đầu
        system("clear");
        cout << "🎮 Game Snake - Màn Hình Lớn" << endl;
        cout << "👉 Nhấn phím bất kỳ để bắt đầu chơi" << endl;
        cout << "👉 Điều khiển: W-A-S-D, Thoát: X" << endl;
        sleep(2);
        
        while (!ketThuc) {
            veManHinh();      // CHỈ 1 khung được vẽ mỗi lần lặp
            xuLyInput();
            capNhatGame();
            usleep(200000);
        }
        
        // 🔥 HIỂN THỊ MÀN HÌNH KẾT THÚC CUỐI CÙNG
        system("clear");
        cout << "╔════════════════════════════════════════╗" << endl;
        cout << "║           💀 GAME OVER 💀             ║" << endl;
        cout << "║                                        ║" << endl;
        cout << "║            Điểm cuối: " << diem;
        // Căn chỉnh cho đẹp
        for (int i = 0; i < 17 - to_string(diem).length(); i++) cout << " ";
        cout << "║" << endl;
        cout << "║            Độ dài: " << ran.size();
        for (int i = 0; i < 20 - to_string(ran.size()).length(); i++) cout << " ";
        cout << "║" << endl;
        cout << "║                                        ║" << endl;
        cout << "║         Nhấn phím để thoát...         ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        
        // Chờ nhấn phím để thoát
        while (!coPhimNhan()) {
            usleep(100000);
        }
        getchar(); // Xóa phím khỏi buffer
    }
};

int main() {
    SnakeGame game;
    game.chay();
    return 0;
}