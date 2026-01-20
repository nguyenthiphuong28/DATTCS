/*
 Game Snake
================================================================
- Mô tả: Trò chơi Snake là một game đơn giản trên màn hình 2D, trong đó người chơi điều khiển một con rắn di chuyển trên màn hình để ăn các mục tiêu (thường là "thức ăn") và tăng chiều dài. Nhiệm vụ chính của người chơi là điều hướng sao cho con rắn không va vào tường hoặc chính cơ thể của nó khi nó ngày càng dài hơn. Trò chơi thường kết thúc khi người chơi không thể tránh va chạm. Với lối chơi dễ hiểu nhưng đầy thử thách, Snake là một trò chơi giải trí nhẹ nhàng, thích hợp cho mọi lứa tuổi..
- Cấu trúc dữ liệu chính & giải thuật chính: Linked list hoặc Queue và các giải thuật di chuyển
- Tính năng chính:
     + Phát sinh thức ăn.
     + Kiểm tra va chạm và các chức năng khác.


dùng struct để lưu vị trí, tạo thức ăn

- chơi và bt tổ chức ,mạng b1
- chức năng : di chuyên , ktra (dụng biên hay hạt), lên điểm-chết
- 2 vấn đề ctdl , đồ hoạ ,giai thuật
-liệt kê chức năng nêu ra cấu trúc và giải thuật chính

*/
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
const int WIDTH = 60;
const int HEIGHT = 20;

// Struct cho một node trong linked list (một đoạn của con rắn)
struct SnakeNode {
    int x, y;
    SnakeNode* next;
    SnakeNode* prev;
    
    SnakeNode(int x = 0, int y = 0) : x(x), y(y), next(nullptr), prev(nullptr) {}
};
// Struct cho thức ăn
struct Food {
    int x, y;
    bool exists;
    
    Food() : x(0), y(0), exists(false) {}
};

// Enum cho hướng di chuyển
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

class SnakeGame {
private:
    // Con rắn (linked list)
    SnakeNode* head;
    SnakeNode* tail;
    
    // Thức ăn
    Food food;
    Direction dir;
    int score;
    bool gameOver;  
};