# Transformation từ 5 kỳ gần nhất — bản đọc trước khi chọn vào notebook

Phạm vi: **COI, Baltic BOI, APIO, CEOI 2022–2026**; COCI là **2021/22–2025/26**. Năm ghi cho COCI là năm kết thúc mùa: chẳng hạn Akcija ở mùa 2021/22 nhưng round diễn ra tháng 12/2021.

Đây là bản khảo sát, **chưa thêm vào notebook**. Sao dưới đây đánh giá độ bất ngờ và khả năng tái sử dụng của **transformation**, không phải độ khó chính thức của bài. Chỉ gọi một mục là đã đối chiếu khi đã đọc editorial hoặc phân tích model solution; xem đề không đồng nghĩa đã giải bài.

Bản phân tích riêng đủ 30 bài CEOI: [CEOI 2022–2026](CEOI_TRANSFORMATIONS_2022_2026.md).

## Các ứng viên đã đối chiếu

### COCI 2021/22 R1 — Volontiranje · 5/5

**Đề:** Cho hoán vị; lấy nhiều LIS nhất có thể, các LIS không dùng chung phần tử và đều dài bằng LIS của hoán vị ban đầu.

**Transformation:** Packing nhiều đường → **uncrossing** → lấy đường trái nhất. Xếp phần tử vào layer theo độ dài LIS kết thúc tại nó; mỗi LIS đi qua đủ các layer. Khi hai đường cắt nhau, đổi đuôi vẫn thu được hai LIS hợp lệ. Vì thế có nghiệm tối ưu gồm các đường không cắt nhau, và có thể lấy LIS trái nhất trước.

**Điểm khó:** Không phải “cứ lấy một LIS bất kỳ”. Uncrossing chứng minh một lựa chọn cực trị có thể nằm trong nghiệm tối ưu. Bỏ các phần tử đứng trước đường đã lấy trong từng layer, đồng thời loại các điểm không thể nối tiếp; tổng số lần xử lý được amortize.

**Đáng giữ:** Rất đáng — cue là *packing đường có thể đổi đuôi ⇒ thử greedy đường cực trị*. Editorial cho thuật toán tổng thể `O(n log n)`.

[Đề](https://hsin.hr/coci/archive/2021_2022/contest1_tasks.pdf) · [Editorial](https://hsin.hr/coci/archive/2021_2022/contest1_solutions.zip).

### COCI 2021/22 R3 — Akcija · 5/5

**Đề:** Chọn sản phẩm để mua trước các deadline, mỗi phút mua tối đa một sản phẩm. Liệt kê k tập tốt nhất: ưu tiên nhiều sản phẩm hơn, rồi tổng giá thấp hơn.

**Transformation:** Oracle tìm nghiệm tối ưu → duyệt **k-best solutions**. Một miền tìm kiếm ghi các sản phẩm bắt buộc lấy/bỏ. Tìm nghiệm tốt nhất `S` của miền đó và đưa vào heap. Khi lấy `S` ra, chia phần còn lại theo **phần tử đầu tiên của S bị bỏ**: bắt buộc lấy các phần tử S trước nó, bắt buộc bỏ nó. Các miền con rời nhau và phủ mọi nghiệm khác S.

**Điểm khó:** Không tự tạo một đồ thị “đổi một sản phẩm” rồi hy vọng không lặp. Chia theo phần tử đầu tiên bị bỏ bảo đảm không trùng. Không bỏ sót: S có cardinality lớn nhất trong miền, nên nghiệm khác không thể chứa trọn S; vì vậy phải bỏ ít nhất một phần tử của S. Cách chia vẫn dùng được khi các nghiệm có kích thước khác nhau.

**Đáng giữ:** Rất đáng — dùng lại được khi có optimization oracle dưới các quyết định forced-in/forced-out. Bản oracle tổng quát chưa tự có bound nhanh của bài; editorial còn khai thác exchange để cập nhật nghiệm.

[Đề](https://hsin.hr/coci/archive/2021_2022/contest3_tasks.pdf) · [Editorial](https://hsin.hr/coci/archive/2021_2022/contest3_solutions.zip).

### COCI 2022/23 R1 — Berilij · 5/5

**Đề:** Tâm các đường tròn đã cố định; một số cặp phải tiếp xúc ngoài. Chọn bán kính không âm, tối thiểu tổng bình phương bán kính.

**Transformation:** Với cạnh `(u,v)`, `r_u+r_v=dist(u,v)`. Chọn `r_root=t`; lan truyền được mọi `r_v=sign_v*t+c_v`. Cả connected component chỉ còn **một tham số**. Cạnh nối hai parity khác nhau kiểm tra consistency; odd cycle cố định t. Nếu chưa cố định, điều kiện không âm cho một interval, hàm mục tiêu là quadratic: lấy nghiệm cực tiểu rồi clamp vào interval.

**Ví dụ:** Ba cạnh có độ dài 8, 10, 6 cho `r_1=t, r_2=8-t, r_3=6-t`; cạnh còn lại ép `14-2t=10`, tức `t=2`.

**Đáng giữ:** Rất đáng — *phương trình cộng trên cạnh ⇒ affine một biến; odd cycle triệt tiêu bậc tự do*. Không cần Gaussian elimination tổng quát; `O(n+m)` phép xử lý đồ thị.

[Đề](https://hsin.hr/coci/archive/2022_2023/contest1_tasks.pdf) · [Editorial](https://hsin.hr/coci/archive/2022_2023/contest1_solutions.zip).

### COCI 2022/23 R5 — Diskurs · 4/5

**Đề:** Với mỗi xâu nhị phân dài m trong tập, tìm khoảng cách Hamming lớn nhất tới một xâu trong tập.

**Transformation:** `max_y H(x,y) = m - min_y H(~x,y)`. Bài farthest-neighbor trở thành nearest-neighbor tại **điểm đối cực**. Multi-source BFS trên hypercube từ tất cả xâu đầu vào, rồi tra khoảng cách của complement.

**Đáng giữ:** Gọn và có thể dùng lại; mạnh khi `2^m` đủ nhỏ. `O(m·2^m)`, không phải BFS riêng cho từng xâu. Có thể để dự bị nếu cue complement → nearest đã có trong notebook.

[Đề](https://hsin.hr/coci/archive/2022_2023/contest5_tasks.pdf) · [Editorial](https://hsin.hr/coci/archive/2022_2023/contest5_solutions.zip).

### COCI 2023/24 R4 — Lepeze · 4/5

**Đề:** Biến triangulation của đa giác thành một fan có chung đỉnh, bằng flip đường chéo; đếm các thứ tự flip ngắn nhất.

**Transformation:** Nghiệm ngắn nhất chỉ thêm đường chéo tới đỉnh fan. Những flip phải xảy ra trước/sau nhau tạo **dependency tree**. Đếm lịch thao tác trở thành đếm linear extensions của cây: nếu có k thao tác thì số lịch là `k! / ∏ size(subtree)`.

**Điểm khó:** Phải chứng minh flip tối ưu không cần phá một cạnh fan đã có, và dependency tree mô tả đủ mọi thứ tự hợp lệ. Công thức đếm chỉ là bước cuối.

**Đáng giữ:** Có — cue *đếm thứ tự thao tác ⇒ tìm partial order bắt buộc*, nhưng construction riêng của triangulation cần context.

[Đề](https://hsin.hr/coci/archive/2023_2024/contest4_tasks.pdf) · [Editorial](https://hsin.hr/coci/archive/2023_2024/contest4_solutions.zip).

### COCI/HONI 2024/25 R1 — Zbunjenost · 4/5

**Đề:** Đa giác đã triangulate; đếm các simple cycle tạo bởi cạnh biên và đường chéo đã cho.

**Transformation:** Dựng **weak dual**: mỗi tam giác là một đỉnh, hai tam giác chung đường chéo thì nối cạnh. Dual là cây. Mỗi cycle bao đúng một tập tam giác liên thông, và biên của mỗi tập liên thông là một cycle. Đếm cycle → đếm connected vertex subsets trên cây.

**Đáng giữ:** Có — điều đáng ghi là bijection *biên khép kín ↔ miền liên thông trong dual tree*, không phải tree DP sau đó.

[Đề HONI](https://hsin.hr/honi/arhiva/2024_2025/kolo1_zadaci.pdf) · [Editorial chính thức](https://hsin.hr/honi/arhiva/2024_2025/kolo1_rjesenja.zip). Dùng bản Croatian do archive COCI mùa này không truy cập được.

### COCI 2025/26 R2 — Tornjevi · 5/5

**Đề:** Với một đoạn xâu hai màu, chia các phần tử thành ít subsequence nhất sao cho mỗi subsequence có màu xen kẽ.

**Transformation:** Mã hóa hai màu `+1/-1`, prefix sum p. Đáp án là **`max(p)-min(p)`** trên các prefix của đoạn, kể cả prefix rỗng.

**Vì sao + construction:** Một interval có chênh lệch hai màu d cần ít nhất |d| subsequence; chênh lệch lớn nhất là biên độ prefix. Với mỗi bước của walk p, gán phần tử vào tower của **mức cao mà bước đó vượt qua**. Các lần vượt cùng một mức luôn luân phiên lên/xuống ⇒ màu xen kẽ. Có đúng biên độ mức được dùng.

**Đáng giữ:** Rất đáng — *partition xen kẽ ⇒ walk qua các mức*, đồng thời có lower bound và construction. Query trở thành range min/max.

[Đề](https://hsin.hr/coci/contest2_tasks.pdf) · [Editorial](https://hsin.hr/coci/contest2_solutions.zip). Không nhầm với Tornjevi mùa 2024/25, là bài gcd.

### COCI 2025/26 R3 — Domjenak · 5/5

**Đề:** 2N người dự tiệc có quan hệ bạn bè bipartite và được ghép thành các cặp bạn bè theo đúng một cách. Mỗi người kể tin cho tối đa một người chưa biết, ưu tiên bạn cùng cặp. Tìm chuỗi truyền tin dài nhất và dựng chuỗi đó.

**Transformation:** Hướng cạnh matching `L→R`, cạnh khác `R→L`. Directed cycle chính là alternating cycle; đảo matching quanh nó tạo matching thứ hai. Vì matching duy nhất, đồ thị có hướng là **DAG**. Longest alternating chain trở thành longest path trên DAG.

**Hệ quả xây dựng:** Trong đồ thị còn perfect matching duy nhất phải có đỉnh bậc 1: DAG có sink; sink không thể ở L vì còn cạnh matching đi ra. Chốt cặp của đỉnh đó, xóa hai đầu, lặp lại — tìm matching tuyến tính bằng queue.

**Đáng giữ:** Rất đáng — *tính duy nhất ⇒ không có cycle cho phép exchange ⇒ DAG + forced peeling*. Chuỗi truyền tin tối ưu có thể lấy xen kẽ cạnh cặp và cạnh ngoài cặp; xét cả hai chiều bằng cách đảo chuỗi.

[Đề](https://hsin.hr/coci/contest3_tasks.pdf) · [Editorial](https://hsin.hr/coci/contest3_solutions.zip).

### COCI 2025/26 R4 — Tjelesni · 4/5

**Đề:** Trên hoán vị, mỗi thao tác sắp một đoạn theo thứ tự nhỏ nhất, lớn nhất, nhỏ nhì, lớn nhì…; tìm vị trí cuối của một giá trị m.

**Transformation:** Chạy hai bản **threshold projection**: `x≥m` và `x≥m+1`. Thao tác trên xâu nhị phân chỉ phụ thuộc số 0/1: lấy luân phiên hai đầu cho tới khi một loại hết. Hai kết quả chỉ khác ở vị trí chứa m.

**Đáng giữ:** Có — *không mô phỏng từng giá trị; xác định một giá trị bằng hiệu của hai tập ngưỡng lồng nhau*. Segment tree là phần thực hiện sau transformation.

[Đề](https://hsin.hr/coci/contest4_tasks.pdf) · [Editorial](https://hsin.hr/coci/contest4_solutions.zip).

### COI 2022 — Povjerenstvo · 5/5

**Đề:** Directed graph không có directed odd cycle. Chọn tập độc lập S sao cho mỗi đỉnh ngoài S có cạnh đi tới S (một **kernel**).

**Transformation:** Điều kiện directed odd cycle không làm cả graph bipartite, nhưng làm **mỗi SCC bipartite khi bỏ hướng**. Trong SCC, cạnh hướng ngược có thể thay bằng directed path; path đó phải dài lẻ, nếu không đã có directed odd cycle. Vì thế một odd cycle vô hướng sẽ cho odd closed walk có hướng và mâu thuẫn.

**Construction:** Xử lý SCC từ sink lên. Trong phần còn lại của SCC, chốt mọi sink vào S và xóa các tiền nhiệm; khi không còn sink, lấy một phía của bipartition. Mỗi đỉnh phía kia có outgoing neighbor nên được cover. Không cần tính lại SCC sau mỗi lần xóa.

**Đáng giữ:** Rất đáng — *điều kiện có hướng ⇒ cấu trúc vô hướng bên trong SCC*, mở đường cho construction `O(n+m)`.

[Đề](https://hsin.hr/hio2022/zadaci/zadaci.pdf) · [Editorial](https://hsin.hr/hio2022/rjesenja.zip).

### CEOI 2024 — Toy · 5/5

**Đề:** Di chuyển đồ chơi gồm một thanh ngang dài K và một thanh dọc dài L trong mê cung; hai thanh luôn giao nhau, có thể dịch độc lập miễn vẫn giao nhau và không gặp tường.

**Transformation:** Trạng thái tưởng phải giữ vị trí hai thanh. Nhưng **mọi cấu hình hợp lệ cùng giao điểm đều đi được tới nhau**: các vị trí khả thi của mỗi thanh là một interval trượt qua giao điểm. Contract cả lớp thành một trạng thái giao điểm.

**Kiểm tra cạnh:** Hai giao điểm kề dọc A,B nối được khi phần trống ngang chung của hai hàng đủ chứa thanh K: `min(left_A,left_B)+min(right_A,right_B)-1 ≥ K`. Tương tự cho cạnh ngang với L; cả hai đầu phải là trạng thái hợp lệ.

**Đáng giữ:** Rất đáng — *bỏ biến trạng thái sau khi chứng minh fiber liên thông*, không chỉ thấy “biến này không quan trọng”. Từ không gian 4 tọa độ xuống BFS `O(HW)`.

[Đề](https://ceoi2024.fi.muni.cz/page/tasks/statements/toy.pdf) · [Editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/toy.pdf).

### CEOI 2024 — Sprinklers · 4/5

**Đề:** Vòi tưới trên trục số, mỗi vòi chọn hướng trái/phải; tìm tầm phun chung nhỏ nhất để phủ mọi bông hoa.

**Transformation:** Nếu ba vòi liên tiếp nằm trong tầm phun mà cùng hướng, đảo vòi giữa **không làm mất vùng phủ**: phần nó từng phủ được vòi ngoài cùng cùng hướng phủ thay. Do đó luôn có nghiệm tối ưu đã normalize, loại được những cấu hình dài khó nhớ; DP chỉ cần một số trạng thái suffix.

**Đáng giữ:** Có — *exchange giữ nguyên chất lượng ⇒ cấm pattern ⇒ finite-state DP*. Tránh ghi nhầm “mọi nghiệm đều không có ba vòi cùng hướng”; chỉ cần tồn tại nghiệm tối ưu đã sửa như vậy.

[Đề](https://ceoi2024.fi.muni.cz/page/tasks/statements/sprinklers.pdf) · [Editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/sprinklers.pdf).

### APIO 2026 — APIOBike · 5/5

**Đề:** Các trạm trên cây có A xe, muốn thành B xe. Xe tải chứa không giới hạn, ban đầu rỗng, được chọn điểm đầu/cuối; tìm walk vận chuyển ngắn nhất và lịch bốc/dỡ.

**Transformation:** Prune lá đã đúng A=B. Mỗi cạnh có hướng vận chuyển bắt buộc từ phía dư sang phía thiếu. Cố định đường đầu–cuối: cạnh ngoài đường cần ít nhất 2 lần; cạnh trên đường cần 1 lần nếu thuận dòng, **3 lần nếu ngược dòng**. So với baseline `2·|E|`, thuận tiết kiệm 1, ngược tốn thêm 1. Tối ưu walk → **maximum signed path**, cạnh có net flow 0 luôn được tính thuận.

**Điểm khó:** Chỉ tìm directed longest path là sai: đôi khi chấp nhận vài cạnh ngược để nối hai đoạn thuận dài sẽ tốt hơn. Editorial có phản ví dụ đạt 7 thay vì 8 bước.

**Đủ để là lời giải:** Cận dưới đạt được bằng gom các đoạn ngược, đi ba lượt; xử lý nhánh dư trước nhánh thiếu để xe tải không âm. DP trên cây tìm signed path và dựng lịch trong `O(n)`.

**Đáng giữ:** Rất đáng — *route + resource feasibility ⇒ parity số lần vượt cut ⇒ signed path*, có construction đạt cận dưới.

[Đề](https://github.com/apio2026/apio-2026/blob/main/bike/statements/en.pdf) · [Editorial chính thức](https://drive.google.com/file/d/1N0ebF1oszzkB1aPENo1YffU6bCbYkF_c/view).

### APIO 2026 — Scallion Pancake Party · 5/5

**Đề:** Khách ngồi nối tiếp nhưng không biết số phòng; mỗi người có một vị bị cấm, các vị cấm tạo hoán vị. Túi bánh được chuyển qua các phòng, mỗi người chỉ thấy túi khi tới mình; người ngoài cuối cùng phải khôi phục hoán vị từ những túi đã ăn.

**Transformation:** Không cần khách biết vị trí tuyệt đối. Gán mỗi vị f một vị ăn được riêng `(f+1) mod N`. Khách ăn túi đầu của vị riêng và ghi số túi đầu đã trống mà mình nhìn thấy. Theo thứ tự xuất hiện lần đầu của các vị ăn được, con số đó chính là **insertion rank của mình trong các khách đã được mã hóa trước**.

**Giải mã:** Vị ăn được g xuất hiện lần đầu xác định khách có vị cấm `f=(g-1) mod N`. Xét khách theo thứ tự công khai đó; chèn người thứ i vào vị trí `e_i+1`. Mỗi khách mã hóa e_i bằng bit trên các túi tiếp theo của vị riêng. Đây là một inversion/insertion code, không phải truyền nguyên room ID.

**Đáng giữ:** Rất đáng — *không biết chỉ số toàn cục ⇒ gửi relative rank theo một thứ tự công khai*. Cần giữ cả cách gán vị ăn được riêng để các kênh không tranh chấp.

[Đề](https://github.com/apio2026/apio-2026/blob/main/party/statements/en.pdf) · [Editorial chính thức](https://drive.google.com/file/d/1N0ebF1oszzkB1aPENo1YffU6bCbYkF_c/view), solution 2.

### COI 2026 — Jedinstven · 5/5

**Đề:** Cho N−1 đoạn [L,R] trên N vị trí. Dựng hai xâu nhị phân khác nhau nhưng có cùng số 1 trong từng đoạn đã cho.

**Transformation:** Đặt p là prefix sum của hiệu hai xâu: mỗi điều kiện thành `p[R]=p[L−1]`. Nối hai prefix đó. Graph có N+1 đỉnh, N−1 cạnh nên có ít nhất hai component. Chọn một component không chứa prefix 0, đặt p=1 trên nó và p=0 ở ngoài.

**Construction:** `d[i]=p[i]−p[i−1]` chỉ là −1,0,1. Đặt `a[i]=max(d[i],0)`, `b[i]=max(−d[i],0)`. Hai xâu khác nhau vì p không hằng; mọi tổng đoạn của hiệu đều bằng 0.

**Đáng giữ:** Rất đáng — *ràng buộc tổng đoạn ⇒ đồng nhất potential ⇒ lấy discrete gradient để dựng witness*. DSU `O(N α(N))`. Đây là chứng minh tự đối chiếu từ đề; chưa có editorial công khai để so sánh.

[Đề chính thức](https://hsin.hr/hio2026/zadaci/zadaci.pdf).

### BOI 2022 — Art Collections · 5/5

**Đề:** Có thứ tự thật của N món đồ. Mỗi query gửi một hoán vị và nhận số cặp đảo thứ tự so với thứ tự thật. Khôi phục thứ tự với tối đa 4000 query; N≤4000.

**Transformation:** Hỏi N phép xoay vòng của cùng một hoán vị. Giữa hai query liên tiếp, chỉ phần tử x chuyển từ đầu xuống cuối; mọi cặp không chứa x triệt tiêu trong hiệu đáp án. Nếu rank thật của x là r, đánh số từ 0, thì `F_next−F_now=N−1−2r`.

**Giải:** Suy ra `r=(N−1+F_now−F_next)/2`. Query cuối nối về query đầu đã biết, nên đúng N query là đủ; không phải hỏi thêm lần thứ N+1.

**Đáng giữ:** Rất đáng — *oracle trả tổng toàn cục ⇒ thiết kế hai query chỉ khác đóng góp của một đối tượng*. Đã đối chiếu model solution và kiểm tra công thức độc lập.

[Đề](https://boi.cses.fi/files/boi2022_day1.pdf) · [Source chính thức](https://boi.cses.fi/files/boi2022_solutions.zip).

### BOI 2024 — Portal · 5/5

**Đề:** Tô lưới vô hạn bằng nhiều màu nhất sao cho người đi bốn hướng không phát hiện mình bị teleport giữa các portal. Người đó chỉ quan sát màu; mọi hành trình nhìn thấy phải nhất quán với một lưới không teleport.

**Transformation:** Dịch chuyển giữa portal i và portal 0 buộc màu bất biến dưới vector `v_i=P_i−P_0`, tại mọi vị trí. Các vector sinh một integer lattice L. Những vị trí cùng coset của `Z²/L` phải cùng màu; tô mỗi coset một màu cũng đủ che mọi teleport.

**Đáp án:** Rank L<2 thì vô hạn màu. Rank 2 thì số màu là index của lattice, bằng `gcd(|det(v_i,v_j)|)` trên mọi cặp. Không duyệt mọi cặp ở input lớn: duy trì basis bằng phép biến đổi nguyên/Euclid.

**Đáng giữ:** Rất đáng — *không phân biệt được sau phép dịch ⇒ quotient lattice*, rồi bài tô màu thành đếm lớp tương đương. Công thức và bijection được giải thích độc lập; không cung cấp implementation chỉ từ việc đọc source.

[Đề](https://boi.cses.fi/files/boi2024_day1.pdf) · [Source chính thức](https://boi.cses.fi/files/boi2024_solutions.zip).

### CEOI 2022 — Homework · 5/5

**Đề:** Biểu thức chỉ có min/max và N ô trống. Điền hoán vị 1..N; đếm những giá trị có thể thu được ở root.

**Transformation:** Qua threshold, `max` thành OR, `min` thành AND. Chỉ cần hai certificate size: c1 là ít lá 1 nhất để root=1, c0 là ít lá 0 nhất để root=0. Ở lá cả hai bằng 1; AND cộng c1, lấy min c0; OR lấy min c1, cộng c0.

**Kết quả:** Giá trị root nằm trong `[c0, N−c1+1]`. Đủ số 0/1 để ép root chứng minh hai đầu đạt được. Không có lỗ ở giữa: graph các hoán vị nối được bằng đổi hai giá trị liên tiếp; một lần đổi làm mọi lá đổi tối đa 1, nên root min/max cũng đổi tối đa 1.

**Đáng giữ:** Rất đáng — *phân phối nhãn ⇒ threshold certificate + connected state space*. Editorial dùng interval DP tương đương; cách diễn đạt certificate và chứng minh không có lỗ ở đây được tự suy ra. Tổng `O(N)`.

[Editorial chính thức](https://archive.uoi.ua/static/ceoi2022-tutorials.pdf), mục Homework.

### CEOI 2023 — Balance · 4/5

**Đề:** N core, mỗi core có S submission, S là lũy thừa của 2. Sắp lịch S phút, mỗi core xử lý một submission/phút; số submission của mỗi task giữa các phút phải lệch không quá 1.

**Transformation:** Submission là cạnh bipartite core–task. Không lấy matching lần lượt: chia cạnh thành hai nửa cân bằng tại mọi đỉnh, rồi recurse. Nối các task bậc lẻ tới một core giả để mọi bậc chẵn; tô luân phiên cạnh trên Euler tour. Tour có độ dài chẵn vì graph bipartite, nên cả chỗ nối cuối–đầu cũng cân bằng.

**Vì sao đủ:** Bậc core được chia đúng đôi; bậc task chia floor/ceil. Sau log S tầng, mỗi màu là một phút và số lần của từng task chỉ là floor/ceil của tổng/S. `O(NS log S)`.

**Đáng giữ:** Có — *cân bằng nhiều nhóm ⇒ chia đôi cân bằng bằng Euler*. Nếu đã có balanced edge coloring trong notebook thì không cần thêm bài riêng.

[Archive chính thức](https://ceoi.elte.hu/tasks-archive.html), 2023 ngày 1, spoiler Balance.

### APIO 2023 — Cyberland · 5/5

**Đề:** Đường đi trên graph có trọng số không âm. Một số đỉnh reset chi phí tích lũy về 0, một số chia đôi chi phí; được chia tối đa K lần, K tới 10⁶. Đến H thì kết thúc, không được dùng H làm đỉnh trung gian. Cần đáp án với sai số cho phép.

**Transformation:** Phép co `x→x/2` xóa dần ảnh hưởng quá khứ. Giữ L lần chia cuối của một walk tối ưu, thay prefix trước đó bằng đường thường có giá ≤N·Cmax. Phần sai khác bị chia L lần, nên sai số cuối **≤N·Cmax/2^L**. Đây là cận xấp xỉ, không phải chứng minh nghiệm tối ưu dùng ít lần chia.

**Giải:** Các đỉnh reset tới được từ 0 trong graph bỏ H trở thành nguồn chi phí 0. Sau đó dùng L layer theo số lần chia, mỗi layer một multi-source Dijkstra. Editorial chọn `L=min(K,70)` theo giới hạn bài và tolerance.

**Đáng giữ:** Rất đáng — *state history rất lớn + contraction ⇒ cắt lịch sử bằng ε-bound đã chứng minh*. Không chép số 70 thành cutoff phổ quát.

[Đề gốc, bản lưu](https://relia.uk/download.php?id=6527&type=statement) · [Editorial gốc, bản lưu](https://relia.uk/download.php?id=6527&type=solution).

### APIO 2023 — Sequence · 5/5

**Đề:** Chọn một đoạn và một median của đoạn, tối đa số lần median xuất hiện. Với độ dài chẵn, có thể chọn một trong hai phần tử giữa làm median.

**Transformation:** Fix một block c lần xuất hiện liên tiếp của giá trị x; đoạn chứa block được nới hai đầu nhưng không lấy thêm x. Đặt `D=#(>x)−#(<x)`. x là median khi và chỉ khi `−c≤D≤c`.

**Kiểm tra nhanh:** Các lựa chọn hai đầu tạo một miền trạng thái liên thông. Mỗi bước nới/co một đầu chỉ đổi D đúng ±1, nên tập D đạt được không có lỗ. Chỉ cần `D_min≤c` và `D_max≥−c`, dù hai cực trị đạt ở hai đoạn khác nhau. Min/max lấy từ prefix/suffix extrema; editorial tổ chức bằng segment tree và two pointers, tổng `O(N log N)`.

**Đáng giữ:** Rất đáng — *existence trên miền trạng thái liên thông + giá trị đổi một đơn vị ⇒ chỉ kiểm tra hai cực trị*. Điểm dễ sai là đòi hai phép kiểm tra phải có cùng argmin/argmax.

[Đề gốc, bản lưu](https://relia.uk/download.php?id=6528&type=statement) · [Editorial gốc, bản lưu](https://relia.uk/download.php?id=6528&type=solution).

### APIO 2025 — Rotating Lines · 5/5

**Đề:** N hướng trên vòng độ dài 50000; mục tiêu là tổng khoảng cách ngắn trên vòng giữa mọi cặp. Mỗi thao tác xoay cùng góc một nhóm, không được giảm mục tiêu; tổng số phần tử tham gia thao tác ≤2 triệu.

**Transformation:** Gom các hướng trùng nhau hoặc đối cực thành component. Khi xoay một component giữa hai sự kiện tiếp xúc với component khác, mục tiêu **tuyến tính theo góc xoay**: không cặp nào đi qua điểm gãy của hàm khoảng cách. Vì vậy ít nhất một đầu đoạn không kém vị trí hiện tại; xoay tới đó rồi merge.

**Construction + bound:** Luôn xoay component nhỏ nhất, nên mỗi phần tử tham gia merge `O(log N)` lần. Cuối cùng mọi hướng nằm trên một cặp đối cực; chuyển từ phía đông hơn sang phía ít hơn tới khi hai phía cân bằng, mỗi bước không giảm mục tiêu.

**Tại sao tối ưu:** Quét đường kính chia vòng thành hai nửa. Một cặp được tách trong một khoảng có độ dài đúng bằng khoảng cách của nó. Do đó mục tiêu là tích phân của `k(N−k)`, không vượt `25000·floor(N²/4)`; construction cân bằng đạt đúng cận này.

**Đáng giữ:** Rất đáng — *piecewise-linear objective ⇒ đi tới event để merge*, nối với small-to-large để dựng lời giải có budget. Đã đọc model; phần chứng minh cận trên ở đây được viết độc lập.

[Đề chính thức](https://github.com/apio2025/apio2025_tasks/blob/main/statements/rotate/en.pdf) · [Model chính thức](https://github.com/apio2025/apio2025_tasks/blob/main/rotate/solutions/model_solution/correct.cpp).

## Nhật ký độ phủ

Đã sàng lọc **230 đề** của 25 kỳ/mùa; chọn **22 ứng viên** ở trên để đọc trước. Sàng lọc không đồng nghĩa giải full-score từng bài. [Nhật ký tên bài và quyết định](OI_TRANSFORMATIONS_2022_2026_COVERAGE.md) ghi cả những bài không chọn.

| Nhóm | Phạm vi | Mức đối chiếu |
|---|---|---|
| COCI | 135 bài / 27 round / 5 mùa | Đọc editorial từng round; mùa 2024/25 dùng HONI chính thức, chỉ tính 5 bài COCI mỗi round |
| COI | 20 bài / 2022–2026 | 2022 có editorial; 2023–2026 mới có đề. Jedinstven có chứng minh độc lập |
| BOI | 30 bài / 2022–2026 | Có đủ đề và gói source; phân tích một phần model, mức từng bài ghi trong nhật ký |
| CEOI | 30 bài / 2022–2026 | Editorial 2022, 2024, 2026; đủ 6 bài năm 2023; 2025 có Boardgames/Highest editorial và 4 model |
| APIO | 15 bài / 2022–2026 | 2023 có đủ 3 editorial; 2024 có 2 editorial và model Magic Show; 2022/2025 dùng model; 2026 Bike/Party đọc sâu, Navigation mới đọc một phần |

Các nguồn nhỏ được lưu ở `olympiad_sources/recent/`, URL trong `manifest*.json`. Link mirror của APIO 2023 trỏ tới tài liệu gốc được lưu lại, không phải lời giải riêng của người luyện tập. Điểm 4–5 là đề xuất để bạn chọn, **chưa được thêm vào notebook/PDF**.

### Những điểm chưa đủ chắc để dùng làm note

- CEOI 2026 VIM: editorial dùng kết quả thực nghiệm cho các n nhỏ và ngưỡng lớn; không chép cutoff thành định lý đã chứng minh.
- CEOI 2026 Flower Cutting: công thức tối thiểu số cạnh được editorial nói rõ là khó chứng minh; chưa chọn chỉ dựa vào việc submit đúng.
- HONI 2024/25 R4 Cipele: editorial xác nhận **official solution sai**; không chọn transformation toàn bài từ source này.
- HONI 2024/25 R5 Crtež: đề và test có bất nhất được tác giả đính chính; phải nói rõ phiên bản sửa nếu phân tích.
- BOI 2026 Hamilton: file source trong gói solutions có bản dummy/WA; tên thư mục “solutions” không chứng minh đó là lời giải full-score.

## Kiểm tra độc lập

[Script kiểm tra](oi_recent_transformation_checks.py) đã chạy thành công: Art trên 5913 hoán vị (N≤7), Jedinstven trên 3000 bộ ràng buộc, Homework trên 175 expression tree với mọi cách gán lá, Sequence trên 41280 block xuất hiện trong mọi xâu ba giá trị dài ≤7. Đây là kiểm tra hữu hạn để bắt lỗi diễn đạt/công thức, không thay cho chứng minh hay validation full-score của 22 bài.
