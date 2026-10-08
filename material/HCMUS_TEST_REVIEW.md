# HCMUS Test — chọn transformation

Đã đọc đề của 12 bài A–L trong `HCMUS_Test`. Ưu tiên **I → E → J**, sau đó **G, D**. Đánh giá dưới đây là độ đáng ghi vào notebook, không phải độ khó bài.

Các lời giải là phân tích từ đề, chưa có editorial chính thức. Nhận xét của I, E, G, J đã qua 9.114 phép kiểm tra nhỏ bằng vét cạn hoặc thuật toán đối chiếu độc lập; đây không phải kiểm tra trên judge. Chưa thêm vào notebook.

| Bài | Ý chính | Đánh giá |
|---|---|---|
| A — Danh the Naughty Pig | Ô → cạnh giữa hàng và cột; hành trình → Euler trail | Hay nhưng notebook đã có cue này |
| B — Freezer | Chất lượng chỉ còn hai nhóm: 4 và ≥5; mỗi ngày cần ít nhất một phần nhóm tốt | Chưa thấy transformation nổi bật; chưa chốt greedy |
| C — Fluorine's Fun Function | Dịch chỉ số Fibonacci → nhân ma trận; dịch âm dùng ma trận nghịch đảo | Hữu ích nhưng khá kinh điển |
| D — Tidal Wave | Tập hàng tới được → một khoảng với parity cố định | Gọn, đáng cân nhắc |
| E — Danh the Pig Emperor | Bỏ tam giác bị chứa → hợp chỉ cần trừ giao của hai tam giác kề nhau | **Ưu tiên** |
| F — Wagon Sorting | Thứ tự đầu ra ép các thao tác queue | Greedy mô phỏng khá quen |
| G — Whisper Chain | Xếp hàng → path cover trên functional graph; phá cycle có thể không mất thêm cạnh | Đáng đọc |
| H — Raining | Tam giác lớn nhất chỉ cần đỉnh convex hull; phân phối ngẫu nhiên ảnh hưởng kích thước hull | Có ý, nhưng chưa xác nhận bound hiệu năng |
| I — Danh the Happy Pig | Vị trí tự xác định số bước → bỏ một chiều DP | **Nổi bật nhất** |
| J — Crafting Costs | Dijkstra trên hypergraph: công thức chỉ kích hoạt khi đủ mọi nguyên liệu | **Ưu tiên** |
| K — Lithium and Lithuania | Nhân điểm với 2 để làm tròn bằng số nguyên | Warmup |
| L — Lucky Numbers | Gom chữ số theo mod 3; lấy singleton 0, cặp 1–2, rồi bộ ba cùng loại | Khá cơ bản |

## I — Danh the Happy Pig

**Đề:** Có giá trị `a[1..n]`, có thể âm. Bắt đầu tại 0; lần nhảy thứ `t` đi `t` hoặc `t+1` ô. Đến ô nào phải ăn giá trị ô đó; chỉ kết thúc khi nhảy ra ngoài `n`. Tối đa tổng giá trị, `n ≤ 5·10⁶`.

**Transformation:** Sau `t` lần nhảy, vị trí là

`p = T_t + k`, với `T_t = t(t+1)/2`, `0 ≤ k ≤ t`.

Các miền vị trí là `[T_t, T_{t+1}−1]`: **không giao nhau và nối tiếp nhau**. Ví dụ:

| Số lần nhảy | Vị trí có thể tới |
|---|---|
| 0 | 0 |
| 1 | 1, 2 |
| 2 | 3, 4, 5 |
| 3 | 6, 7, 8, 9 |

Vậy biết `p` là biết `t`. Chỉ cần `dp[p]`, chuyển sang `p+t+1` và `p+t+2`. Mỗi vị trí xử lý hai chuyển tiếp: **O(n)**. Có thể giữ hai layer rộng O(√n) nếu đọc và xử lý giá trị theo từng layer.

**Điểm đáng giữ:** Trước khi lưu thêm một chiều DP, kiểm tra xem chiều đó đã được xác định bởi miền giá trị của chiều còn lại chưa.

**Bẫy:** Không được lấy max của mọi `dp[p]`: đề không cho dừng tùy ý. Chỉ cập nhật đáp án từ chuyển tiếp nhảy ra ngoài; điều này quan trọng khi có giá trị âm.

## E — Danh the Pig Emperor

**Đề:** Mỗi đoạn `[l_i,r_i]` trên trục hoành là cạnh huyền của một tam giác vuông cân nằm phía trên. Tính diện tích hợp của các tam giác, xuất `4 × diện tích`, `n ≤ 2·10⁵`.

**Transformation:** Tam giác có độ cao `h_i(x)=min(x−l_i,r_i−x)` trên đoạn của nó. Đoạn bị chứa thì tam giác cũng bị chứa: bỏ đi. Sắp phần còn lại theo `l`; lúc này cả `l` và `r` đều tăng nghiêm ngặt.

Nếu một điểm thuộc tam giác `i` và `k`, nó cũng thuộc mọi tam giác nằm giữa hai chỉ số này. Do đó các tam giác chứa một điểm luôn là **một đoạn chỉ số liên tục**. Điểm thuộc `s` tam giác xuất hiện `s` lần trong tổng diện tích và `s−1` lần trong tổng giao kề nhau: còn đúng một lần.

Giao của hai tam giác kề là tam giác trên `[l_{i+1},r_i]`, nếu đoạn này không rỗng. Suy ra:

`4A = Σ(r_i−l_i)² − Σ max(0,r_i−l_{i+1})²`.

Ví dụ `[0,4]`, `[2,6]`: `4A = 16+16−4 = 28`. Tổng thời gian **O(n log n)**.

**Điểm đáng giữ:** Sau khi loại dominance, chứng minh các đối tượng phủ một điểm có chỉ số liên tục → inclusion–exclusion chỉ còn giao kề nhau.

**Bẫy:** Tổng diện tích từng tam giác trước khi trừ có thể tràn `long long`; dùng `__int128` cho tổng trung gian.

## J — Crafting Costs

**Đề:** Mỗi loại vật phẩm có giá mua trực tiếp. Một công thức tiêu thụ một vật phẩm của **mỗi loại nguyên liệu** và trả thêm phí không âm để tạo vật phẩm đích. Có nhiều công thức và có thể có vòng phụ thuộc. Tìm chi phí nhỏ nhất cho mọi loại.

**Transformation:** Một công thức là **hyperedge dạng AND**: phải có đủ tất cả nguyên liệu, không phải chọn một cạnh đi tới đích. Tuy có cycle, chi phí sản phẩm qua công thức luôn ≥ chi phí từng nguyên liệu.

Dùng Dijkstra:

1. Khởi tạo `d[i]` bằng giá mua, đưa mọi loại vào min-heap.
2. Mỗi công thức giữ số nguyên liệu chưa chốt và tổng chi phí đã chốt, khởi đầu bằng phí chế tạo.
3. Khi chốt `u`, cộng `d[u]` vào mọi công thức dùng `u`, giảm bộ đếm.
4. Khi bộ đếm về 0, dùng tổng đó relax vật phẩm đích.

**Vì sao chốt được?** Nếu một lời giải rẻ hơn dùng công thức, mọi nguyên liệu của nó đều có giá không lớn hơn lời giải đó. Chúng sẽ được xử lý trước khi chốt một giá đích lớn hơn. Các công thức có cycle không cần topological order.

Với `K` là tổng số nguyên liệu được liệt kê: **O(K + (n+m) log(n+m))** bằng heap có bản ghi cũ.

**Điểm đáng giữ:** Dijkstra có thể dùng với trạng thái cần hoàn thành **tất cả tiền nhiệm**, khi phép kết hợp chi phí không làm giá mới nhỏ hơn bất kỳ tiền nhiệm nào.

**Bẫy:** Nguyên liệu bị tiêu thụ. Nếu hai nhánh cùng cần một loại thì vẫn phải trả hai lần, không gộp thành một vật phẩm dùng chung.

## G — Whisper Chain

**Đề:** Mỗi người `i` muốn đứng ngay trước `s_i`, với `s_i ≠ i`. Xếp tất cả thành một hàng để thỏa nhiều người nhất, và xuất cách xếp, `n ≤ 10⁴`.

**Transformation:** Các cạnh thỏa `i → s_i` phải tạo thành những directed path rời nhau: mỗi đỉnh có indegree/outdegree ≤1 và không có cycle. Nối các path thành một hàng. Bài toán thành **path cover trên functional graph**.

Trong mỗi component, gọi `L` là số đỉnh indegree 0:

- Nếu `L>0`: cần ít nhất `L` path, và đạt được đúng `L`. Chọn một cạnh vào cho mỗi đỉnh có indegree dương; tại một đỉnh cycle có cây đi vào, chọn cạnh từ cây thay cạnh từ cycle. Cycle bị phá mà số cạnh được chọn không giảm.
- Nếu component là cycle thuần: bỏ một cạnh, còn một path.

Vậy số điều kiện tối đa là `n − số đỉnh indegree 0 − số component cycle thuần`. Dựng bằng peel cycle và chọn cạnh vào, **O(n)**.

**Điểm đáng giữ:** Khi cycle có nhánh đi vào, có thể phá cycle bằng một phép đổi cạnh, không cần trả thêm một path.

## D — Tidal Wave

**Đề:** Đi từ `(1,1)` tới cột cuối; mỗi bước sang cột kế và đổi hàng ±1. Mỗi cột chỉ cho đi trong một đoạn hàng `[l_j+1,n−r_j]`; `n,m ≤ 10⁵`.

**Transformation:** Ở cột `j`, các hàng tới được luôn có parity `j mod 2` và tạo một khoảng cách đều 2. Giữ hai biên `L,R`; sang cột kế, mở thành `[L−1,R+1]`, giao với đoạn được phép rồi chỉnh biên theo parity. Rỗng thì không đi được. **O(m)** thời gian, O(1) trạng thái.

**Điểm đáng giữ:** Tập trạng thái có lỗ nhưng các lỗ tuân theo parity → khoảng + residue vẫn biểu diễn chính xác, không cần DP từng ô.
