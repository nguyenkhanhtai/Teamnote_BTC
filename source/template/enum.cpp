// ==========================================
// 1. CÁCH KHAI BÁO ENUM
// ==========================================

// Mặc định phần tử đầu = 0, các phần tử sau tự tăng +1
enum Direction { UP, RIGHT, DOWN, LEFT }; // 0, 1, 2, 3

// Khai báo giá trị tùy chọn (phần tử sau tự tăng tiếp)
enum Custom { A = 1, B, C = 10, D }; // A=1, B=2, C=10, D=11


// ==========================================
// 2. CÁC CASE SỬ DỤNG PHỔ BIẾN TRONG CP
// ==========================================

// Case 1: 4 hướng di chuyển trên lưới ô vuông
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};
// int nx = x + dx[UP], ny = y + dy[UP];

// Case 2: DFS 3 màu phát hiện chu trình đồ thị có hướng
// WHITE: chưa thăm | GRAY: đang trong nhánh DFS | BLACK: đã duyệt xong
enum Color { WHITE, GRAY, BLACK }; // 0, 1, 2
// int color[MAXN];
// if (color[v] == GRAY) có chu trình;

// Case 3: Sắp xếp sự kiện Sweep-line / Offline Query
// Gán giá trị để ưu tiên xử lý khi tọa độ trùng nhau
enum EventType { REMOVE = 0, QUERY = 1, ADD = 2 };
struct Event {
    int x;
    EventType type;
    int id;
    bool operator<(const Event& o) const {
        if (x != o.x) return x < o.x;
        return type < o.type; // Cùng x: xử lý REMOVE -> QUERY -> ADD
    }
};

// Case 4: Trạng thái Game / Quy hoạch động
enum Outcome { LOSE, DRAW, WIN }; // 0, 1, 2

// Case 5: Cờ bitmask (Flags)
enum Flags {
    READ  = 1 << 0, // 1
    WRITE = 1 << 1, // 2
    EXEC  = 1 << 2  // 4
};
// mask |= READ;        // Bật cờ
// if (mask & READ) ... // Kiểm tra cờ có bật không
// mask &= ~WRITE;      // Tắt cờ
