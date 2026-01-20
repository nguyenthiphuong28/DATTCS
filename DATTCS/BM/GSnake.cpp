#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <algorithm>

using namespace std;

// Kích thước màn hình game
const int RONG = 60;
const int CAO = 25;

// Các struct cho game
struct ViTri {
    int x, y;
    
    ViTri(int x = 0, int y = 0) : x(x), y(y) {}
    
    bool operator==(const ViTri& other) const {
        return x == other.x && y == other.y;
    }
};

struct ThucAn {
    ViTri viTri;
    int loai;           // 0: rỗng, 1: thường, 2: đặc biệt
    int diem;
    string kyHieu;
    int thoiGianTonTai; // -1: vĩnh viễn
    
    // Constructor mặc định
    ThucAn() : loai(0), diem(0), kyHieu(""), thoiGianTonTai(-1) {}
    
    ThucAn(ViTri vt, int l = 1, int d = 10, string kh = "🍎", int tgt = -1) 
        : viTri(vt), loai(l), diem(d), kyHieu(kh), thoiGianTonTai(tgt) {}
};

struct HieuUng {
    string ten;
    int thoiGian;
    bool hoatDong;
    
    HieuUng(string t = "", int tg = 0) : ten(t), thoiGian(tg), hoatDong(true) {}
};

struct TrangThaiGame {
    int diem;
    int capDo;
    int tocDo;          // ms giữa các frame
    bool dangChay;
    bool tamDung;
    bool ketThuc;
    
    TrangThaiGame() : diem(0), capDo(1), tocDo(200), dangChay(false), tamDung(false), ketThuc(false) {}
};

class GameRanSanMoi {
private:
    // Thành phần chính của game
    vector<ViTri> ran;
    vector<ThucAn> danhSachThucAn;
    vector<ViTri> vatCan;
    vector<HieuUng> hieuUngDangHoatDong;
    TrangThaiGame trangThai;
    char huong;
    
    // Cấu hình terminal
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
    
    bool viTriHopLe(const ViTri& vt) {
        // Kiểm tra không trùng với rắn
        for (const auto& doan : ran) {
            if (doan == vt) return false;
        }
        // Kiểm tra không trùng với vật cản
        for (const auto& vc : vatCan) {
            if (vc == vt) return false;
        }
        // Kiểm tra trong màn hình
        return vt.x >= 0 && vt.x < RONG && vt.y >= 0 && vt.y < CAO;
    }
    
    ViTri taoViTriNgauNhien() {
        ViTri vt;
        do {
            vt.x = rand() % (RONG - 4) + 2;
            vt.y = rand() % (CAO - 4) + 2;
        } while (!viTriHopLe(vt));
        return vt;
    }

    // Hàm hỗ trợ tạo thức ăn mới
    ThucAn taoThucAnMoi(int loai) {
        if (loai == 1) {
            ThucAn ta;
            ta.viTri = taoViTriNgauNhien();
            ta.loai = 1;
            ta.diem = 10;
            ta.kyHieu = "🍎";
            ta.thoiGianTonTai = -1;
            return ta;
        } else if (loai == 2) {
            // Chỉ tạo thức ăn đặc biệt với 30% cơ hội
            if (rand() % 100 < 30) {
                ThucAn ta;
                ta.viTri = taoViTriNgauNhien();
                ta.loai = 2;
                ta.diem = 50;
                ta.kyHieu = "🍇";
                ta.thoiGianTonTai = 50;
                return ta;
            }
        }
        return ThucAn(); // Trả về thức ăn rỗng
    }

public:
    GameRanSanMoi() : huong('d') {
        srand(time(0));
        
        // Khởi tạo rắn
        int startX = 10;
        int startY = CAO / 2;
        ran.push_back(ViTri(startX, startY));
        ran.push_back(ViTri(startX-1, startY));
        ran.push_back(ViTri(startX-2, startY));
        
        // Tạo thức ăn ban đầu
        taoThucAnThuong();
        taoThucAnThuong();
        
        // Tạo vật cản
        taoVatCan();
        
        cauHinhTerminal(true);
    }
    
    ~GameRanSanMoi() {
        cauHinhTerminal(false);
    }
    
    void taoThucAnThuong() {
        ThucAn ta = taoThucAnMoi(1);
        if (ta.loai != 0) { // Chỉ thêm nếu không rỗng
            danhSachThucAn.push_back(ta);
        }
    }
    
    void taoThucAnDacBiet() {
        ThucAn ta = taoThucAnMoi(2);
        if (ta.loai != 0) { // Chỉ thêm nếu không rỗng
            danhSachThucAn.push_back(ta);
        }
    }
    
    void taoVatCan() {
        for (int i = 0; i < 5 + trangThai.capDo; i++) {
            ViTri vc = taoViTriNgauNhien();
            vatCan.push_back(vc);
        }
    }
    
    void kichHoatHieuUng(const string& ten, int thoiGian) {
        hieuUngDangHoatDong.push_back(HieuUng(ten, thoiGian));
    }
    
    void capNhatHieuUng() {
        for (auto it = hieuUngDangHoatDong.begin(); it != hieuUngDangHoatDong.end();) {
            it->thoiGian--;
            if (it->thoiGian <= 0) {
                it = hieuUngDangHoatDong.erase(it);
            } else {
                ++it;
            }
        }
    }
    
    void veManHinh() {
        system("clear");
        
        // Header
        cout << "🐍 GAME RẮN SĂN MỒI NÂNG CAO 🍎" << endl;
        cout << "Điểm: " << trangThai.diem << " | Cấp: " << trangThai.capDo;
        cout << " | Độ dài: " << ran.size();
        cout << " | Tốc độ: " << (500 - trangThai.tocDo) / 10 << endl;
        
        // Hiệu ứng đang hoạt động
        if (!hieuUngDangHoatDong.empty()) {
            cout << "Hiệu ứng: ";
            for (const auto& hieuUng : hieuUngDangHoatDong) {
                cout << hieuUng.ten << "(" << hieuUng.thoiGian << ") ";
            }
            cout << endl;
        }
        
        // Vẽ khung trên
        cout << "╔";
        for (int i = 0; i < RONG; i++) cout << "═";
        cout << "╗" << endl;
        
        // Vẽ nội dung game
        for (int y = 0; y < CAO; y++) {
            cout << "║";
            for (int x = 0; x < RONG; x++) {
                ViTri vt(x, y);
                
                // Kiểm tra đầu rắn
                if (!ran.empty() && ran[0] == vt) {
                    cout << "🔸";
                    continue;
                }
                
                // Kiểm tra thân rắn
                bool laThanRan = false;
                for (int i = 1; i < ran.size(); i++) {
                    if (ran[i] == vt) {
                        cout << "○";
                        laThanRan = true;
                        break;
                    }
                }
                if (laThanRan) continue;
                
                // Kiểm tra thức ăn
                bool laThucAn = false;
                for (const auto& ta : danhSachThucAn) {
                    if (ta.viTri == vt && ta.loai != 0) {
                        cout << ta.kyHieu;
                        laThucAn = true;
                        break;
                    }
                }
                if (laThucAn) continue;
                
                // Kiểm tra vật cản
                bool laVatCan = false;
                for (const auto& vc : vatCan) {
                    if (vc == vt) {
                        cout << "█";
                        laVatCan = true;
                        break;
                    }
                }
                if (laVatCan) continue;
                
                // Ô trống
                cout << " ";
            }
            cout << "║" << endl;
        }
        
        // Vẽ khung dưới
        cout << "╚";
        for (int i = 0; i < RONG; i++) cout << "═";
        cout << "╝" << endl;
        
        // Hướng dẫn
        cout << "Điều khiển: W-A-S-D | Tạm dừng: P | Thoát: X" << endl;
        
        if (!trangThai.dangChay && !trangThai.ketThuc) {
            cout << "🎮 NHẤN PHÍM BẤT KỲ ĐỂ BẮT ĐẦU!" << endl;
        }
        
        if (trangThai.tamDung) {
            cout << "⏸️  TẠM DỪNG - Nhấn P để tiếp tục" << endl;
        }
        
        if (trangThai.ketThuc) {
            cout << "💀 GAME OVER! Nhấn phím để thoát..." << endl;
        }
    }
    
    void xuLyInput() {
        if (coPhimNhan()) {
            char phim = getchar();
            
            if (trangThai.ketThuc) return;
            
            if (!trangThai.dangChay && !trangThai.ketThuc) {
                trangThai.dangChay = true;
                return;
            }
            
            switch (phim) {
                case 'w': case 'W': if (huong != 's') huong = 'w'; break;
                case 's': case 'S': if (huong != 'w') huong = 's'; break;
                case 'a': case 'A': if (huong != 'd') huong = 'a'; break;
                case 'd': case 'D': if (huong != 'a') huong = 'd'; break;
                case 'p': case 'P': trangThai.tamDung = !trangThai.tamDung; break;
                case 'x': case 'X': trangThai.ketThuc = true; break;
            }
        }
    }
    
    void capNhatGame() {
        if (!trangThai.dangChay || trangThai.tamDung || trangThai.ketThuc) return;
        
        // Di chuyển rắn
        ViTri dauMoi = ran[0];
        switch (huong) {
            case 'w': dauMoi.y--; break;
            case 's': dauMoi.y++; break;
            case 'a': dauMoi.x--; break;
            case 'd': dauMoi.x++; break;
        }
        
        // Kiểm tra va chạm tường
        if (dauMoi.x < 0 || dauMoi.x >= RONG || dauMoi.y < 0 || dauMoi.y >= CAO) {
            trangThai.ketThuc = true;
            return;
        }
        
        // Kiểm tra va chạm thân
        for (int i = 1; i < ran.size(); i++) {
            if (ran[i] == dauMoi) {
                trangThai.ketThuc = true;
                return;
            }
        }
        
        // Kiểm tra va chạm vật cản
        for (const auto& vc : vatCan) {
            if (vc == dauMoi) {
                trangThai.ketThuc = true;
                return;
            }
        }
        
        // Thêm đầu mới
        ran.insert(ran.begin(), dauMoi);
        
        // Kiểm tra ăn thức ăn - PHIÊN BẢN ĐÃ SỬA
        bool daAn = false;
        vector<ThucAn> thucAnMoi; // Lưu thức ăn mới sẽ thêm
        
        for (auto it = danhSachThucAn.begin(); it != danhSachThucAn.end();) {
            if (it->loai != 0 && it->viTri == dauMoi) {
                // Ăn thức ăn
                trangThai.diem += it->diem;
                
                // Hiệu ứng thức ăn đặc biệt
                if (it->loai == 2) {
                    kichHoatHieuUng("TĂNG TỐC", 30);
                    trangThai.tocDo = max(50, trangThai.tocDo - 20);
                }
                
                // Đánh dấu tạo thức ăn mới (không tạo ngay)
                if (it->loai == 1) {
                    thucAnMoi.push_back(taoThucAnMoi(1));
                }
                
                // Đánh dấu tạo thức ăn đặc biệt (với tỉ lệ)
                if (rand() % 100 < 30) {
                    thucAnMoi.push_back(taoThucAnMoi(2));
                }
                
                // Xóa thức ăn đã ăn
                it = danhSachThucAn.erase(it);
                daAn = true;
            } else {
                // Cập nhật thức ăn đặc biệt
                if (it->thoiGianTonTai > 0) {
                    it->thoiGianTonTai--;
                    if (it->thoiGianTonTai <= 0) {
                        it = danhSachThucAn.erase(it);
                    } else {
                        ++it;
                    }
                } else {
                    ++it;
                }
            }
        }
        
        // Thêm thức ăn mới SAU KHI duyệt xong
        for (const auto& ta : thucAnMoi) {
            if (ta.loai != 0) {
                danhSachThucAn.push_back(ta);
            }
        }
        
        // Lên cấp
        if (daAn && trangThai.diem >= trangThai.capDo * 100) {
            trangThai.capDo++;
            taoVatCan();
            kichHoatHieuUng("LÊN CẤP " + to_string(trangThai.capDo), 20);
        }
        
        // Nếu không ăn, xóa đuôi
        if (!daAn) {
            ran.pop_back();
        }
        
        // Cập nhật hiệu ứng
        capNhatHieuUng();
    }
    
    void chay() {
        // Màn hình chào
        system("clear");
        cout << "🎮 GAME RẮN SĂN MỒI NÂNG CAO" << endl;
        cout << "══════════════════════════════" << endl;
        cout << "🍎 Thức ăn thường: 10 điểm" << endl;
        cout << "🍇 Thức ăn đặc biệt: 50 điểm + Tăng tốc" << endl;
        cout << "█ Vật cản: Game Over nếu chạm" << endl;
        cout << "👉 Nhấn phím bất kỳ để bắt đầu..." << endl;
        
        // Chờ phím bất kỳ
        while (!coPhimNhan()) {
            usleep(100000);
        }
        getchar(); // Xóa phím khỏi buffer
        
        // Game loop
        while (!trangThai.ketThuc) {
            veManHinh();
            xuLyInput();
            capNhatGame();
            usleep(trangThai.tocDo * 1000);
        }
        
        // Màn hình kết thúc
        system("clear");
        cout << "╔════════════════════════════════════════╗" << endl;
        cout << "║           💀 GAME OVER 💀             ║" << endl;
        cout << "║                                        ║" << endl;
        cout << "║            Điểm cuối: " << trangThai.diem;
        for (int i = 0; i < 17 - to_string(trangThai.diem).length(); i++) cout << " ";
        cout << "║" << endl;
        cout << "║            Cấp độ: " << trangThai.capDo;
        for (int i = 0; i < 21 - to_string(trangThai.capDo).length(); i++) cout << " ";
        cout << "║" << endl;
        cout << "║            Độ dài: " << ran.size();
        for (int i = 0; i < 20 - to_string(ran.size()).length(); i++) cout << " ";
        cout << "║" << endl;
        cout << "║                                        ║" << endl;
        cout << "║         Nhấn phím để thoát...         ║" << endl;
        cout << "╚════════════════════════════════════════╝" << endl;
        
        while (!coPhimNhan()) {
            usleep(100000);
        }
        getchar();
    }
};

int main() {
    GameRanSanMoi game;
    game.chay();
    return 0;
}