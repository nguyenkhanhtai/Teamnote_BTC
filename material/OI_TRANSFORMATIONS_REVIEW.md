# Khảo sát transformation: COCI, COI, BOI, APIO, CEOI

**Trạng thái:** bản để đọc và chọn; chưa đưa các mục này vào notebook. Không sửa các transformation cũ.

**Phạm vi đã đọc:** 29 bài, trong các cụm editorial bên dưới. Đây là đợt khảo sát đầu tiên, **không phải toàn bộ archive** của năm cuộc thi. BOI ở đây là **Baltic Olympiad in Informatics**; COI là **Croatian Olympiad in Informatics**. Đọc từng cụm và ghi lại cả bài giữ lẫn bài loại.

**Tiêu chí:** ưu tiên bước đổi mô hình khó nhận ra, có thể tái sử dụng; không ưu tiên một bài chỉ vì khó, implementation dài hoặc construction quá riêng. Điểm /5 bên dưới đánh giá **giá trị transformation cho notebook này**, không phải độ khó chính thức.

Nguồn gốc: các PDF/editorial và code chính thức được lưu lại trong [olympiad_sources](olympiad_sources/manifest.json). Kho mirror là `mostafa-saad/MyCompetitiveProgramming`, thư mục `official/`; không coi những mini-editorial riêng của người luyện tập là lời giải chính thức. Với Rainbow và Merchant, đã đọc code chính thức; Rainbow đối chiếu thêm bản đề tiếng Anh.

Bản bổ sung 5 kỳ/mùa gần nhất: [2022–2026](OI_TRANSFORMATIONS_2022_2026.md), kèm [nhật ký độ phủ](OI_TRANSFORMATIONS_2022_2026_COVERAGE.md). Phạm vi 29 bài dưới đây vẫn là đợt đầu, không gồm bản bổ sung.

## Các ứng viên nên đọc trước

| Bài | Nhận xét chính | Đánh giá | Đề xuất |
|---|---|---:|---|
| APIO 2007 — Backup | Giữ khả năng hoàn tác greedy bằng cạnh ảo có chi phí chênh lệch | 5/5 | Ưu tiên |
| APIO 2017 — Rainbow | Đếm thành phần đất qua số mặt của đồ thị phẳng, dùng Euler | 5/5 | Ưu tiên |
| BOI 2018 — Genetics | Nén cả họ kiểm tra khoảng cách thành một tổng có trọng số ngẫu nhiên | 5/5 | Ưu tiên; có xác suất lỗi |
| COI 2016 — Palinilap | Một sửa đổi chỉ mở rộng palindrome qua cặp lệch đầu tiên của tâm | 4/5 | Đáng đọc |
| COCI 2016/2017 R2 — Burza | Đổi game thành phủ subtree; chứng minh tham số lớn luôn thắng, chỉ DP trường hợp nhỏ | 4/5 | Đáng đọc; bound riêng cần hiểu |
| CEOI 2017 — Palindromic Partitions | Chọn border ngắn nhất để tối đa số chunk, không DP mọi cách chia | 4/5 | Cân nhắc nếu chưa quen |

## 1. APIO 2007 — Backup

### Đề tóm tắt

Có các văn phòng trên một đường thẳng, tọa độ tăng dần. Chọn **đúng k cặp văn phòng**, mỗi văn phòng thuộc tối đa một cặp. Chi phí một cặp là khoảng cách giữa hai văn phòng. Tối thiểu hóa tổng chi phí.

### Transformation

**Matching trên đường → các quyết định tăng số cặp thêm 1 → greedy với khả năng hoàn tác được mã hóa bằng cạnh ảo.**

Có một nghiệm tối ưu chỉ ghép các văn phòng kề nhau. Gọi khoảng cách kề là `w[i]`: cần chọn k cạnh không kề nhau.

Greedy lấy cạnh nhỏ nhất rồi bỏ hai hàng xóm **không đúng**. Ví dụ:

```text
Khoảng cách: 11, 5, 3, 6, 14, 10, 9, 10
Cần 2 cặp.
Greedy cứng: 3 + 9 = 12.
Tốt hơn:     5 + 6 = 11.
```

Sau khi chọn cạnh giữa có trọng số 3, đừng quên lựa chọn thay nó bằng cả hai cạnh 5 và 6. Lựa chọn này:

- Tăng số cặp từ 1 lên 2.
- Tăng chi phí thêm `5 + 6 - 3 = 8`.

Vì vậy co ba cạnh thành một **cạnh ảo trọng số 8**. Cạnh ảo không phải dây nối thật; nó biểu diễn một phép đổi quyết định cũ. Tổng chi phí sau hai lần lấy là `3 + 8 = 11`.

### Vì sao đáng chú ý?

Greedy vẫn lấy chi phí nhỏ nhất, nhưng mỗi lựa chọn là **chi phí tăng thêm của một augmenting path**, có thể đảo các cạnh đã chọn trước đó. Công thức co:

\[
w_{new}=w_{left}+w_{right}-w_{chosen}.
\]

Trên đường, cấu trúc sau khi co vẫn là một đường, nên tiếp tục dùng cùng quy tắc. Dùng heap và linked list, xử lý biên khi thiếu hàng xóm; thời gian gồm khởi tạo O(n) và O(k log n) cập nhật.

**Cue:** lựa chọn mới có thể cần bỏ một quyết định cũ → biểu diễn *mức tăng chi phí* của phép thay thế; không đóng băng greedy quá sớm.

**Giới hạn:** công thức co này được bảo đảm cho matching có cấu trúc đường; không tự áp dụng cho mọi bài chọn các phần tử không kề nhau hay mọi greedy.

**Nguồn:** [editorial chính thức, trang PDF 3–5](olympiad_sources/APIO_2007_solutions.pdf#page=3). Đã đối chiếu contraction với vét cạn matching trên đường nhỏ.

## 2. APIO 2017 — Land of the Rainbow Gold

### Đề tóm tắt

Một con rắn đi qua các ô kề cạnh trên lưới, biến các ô nó đi qua thành sông. Các ô sông tạo thành **một tập liên thông**. Với mỗi query hình chữ nhật, hỏi số thành phần liên thông của các ô đất bên trong; hai ô đất kề cạnh được coi là nối nhau.

### Transformation

**Đếm vùng đất liên thông → đếm mặt của một đồ thị phẳng → đếm điểm/cạnh/ô trong hình chữ nhật.**

Vẽ các cạnh bao quanh mọi ô sông trong query, kể cả cạnh chung của hai ô sông, và thêm khung ngoài của query. Trong đồ thị phẳng này:

- Mỗi ô sông là một mặt riêng.
- Mỗi thành phần đất là một mặt riêng.
- Có một mặt vô hạn ở ngoài khung.

Theo Euler, nếu đồ thị có C thành phần:

\[
V-E+F=1+C.
\]

Nếu B là số ô sông, W là số vùng đất, thì `F = B + W + 1`. Do đó:

\[
\boxed{W=E-V-B+C.}
\]

### Chỗ khó: có thật C dễ tính không?

Không được mặc định C = 1. Nếu toàn bộ sông nằm **hoàn toàn bên trong** query, đồ thị của sông tách khỏi khung ngoài, nên C = 2.

Các trường hợp còn lại C = 1. Lý do là tập sông toàn cục liên thông: nếu một phần sông nằm trong query còn phần khác nằm ngoài, đường nối chúng phải chạm khung; các mảnh bị cắt đều nối với khung. Nếu query không có sông, chỉ có khung, cũng C = 1.

Đây là lý do điều kiện “sông tạo bởi một walk liên thông” quan trọng. Với các vùng cấm rời nhau tùy ý, C không còn xác định đơn giản như vậy.

### Hướng triển khai

Tiền xử lý bốn tập đối tượng: ô sông, đỉnh góc, cạnh ngang, cạnh dọc; loại trùng. V, E, B được lấy bằng các query đếm điểm 2D, cộng phần biên của hình chữ nhật. Code chính thức dùng persistent segment tree theo một trục. C kiểm tra bằng bounding box của toàn bộ sông.

**Cue:** bài hỏi số vùng của hình phẳng → thử Euler; nếu đếm được V/E và kiểm soát được C, có thể thay connectivity query bằng range counting.

**Nguồn:** [đề và submit](https://oj.uz/problem/view/APIO17_rainbow), [code chính thức](olympiad_sources/APIO_2017_rainbow_official.cpp). Công thức được đối chiếu với flood fill trên các walk và query nhỏ.

## 3. BOI 2018 — Genetics

### Đề tóm tắt

Cho N chuỗi DNA dài M và số K. Tìm một chuỗi có **Hamming distance đúng K với mọi chuỗi khác**.

### Transformation

**N điều kiện khoảng cách trên mỗi ứng viên → một phương trình tuyến tính với trọng số ngẫu nhiên → gom đóng góp theo cột và ký tự.**

Gán mỗi chuỗi j trọng số ngẫu nhiên w[j]. Với ứng viên i, thay việc kiểm tra từng điều kiện `dist(i,j) = K` bằng:

\[
\sum_{j\ne i}w_j\,dist(i,j)
=K\sum_{j\ne i}w_j.
\]

Tổng bên trái tính nhanh được. Với mỗi cột t và ký tự c, lưu:

\[
A[t,c]=\sum_{j:S_j[t]=c}w_j.
\]

Nếu tổng trọng số là T, đóng góp của cột t vào khoảng cách của chuỗi i là `T - A[t,S_i[t]]`. Cộng M cột là đủ; chuỗi i không tự đóng góp vì khoảng cách với chính nó bằng 0.

Một lượt tiền xử lý và kiểm tra tất cả ứng viên tốn O(NM), thay vì O(N²M).

### Vì sao phải ngẫu nhiên?

Nếu mọi trọng số bằng 1, khoảng cách K-1 và K+1 có thể bù nhau, làm một ứng viên sai vẫn qua kiểm tra.

Với trọng số độc lập, đều trong trường hữu hạn modulo prime P > M, ứng viên sai có một hệ số `dist(i,j)-K` khác 0. Cố định các trọng số khác thì chỉ một giá trị của w[j] làm tổng bằng 0: xác suất lọt một lượt không quá 1/P. Có thể lặp với trọng số mới để giảm lỗi. Ứng viên đúng luôn qua.

**Cue:** phải kiểm tra rất nhiều phương trình cùng dạng → lấy tổ hợp tuyến tính ngẫu nhiên; nếu tổng đổi thứ tự được, có thể tính tất cả ứng viên cùng lúc.

**Giới hạn:** đây là Monte Carlo. Không suy ra tính đúng tuyệt đối từ việc dùng 64-bit overflow. Phân tích xác suất bên trên dùng trường modulo prime, là lựa chọn triển khai đề xuất ở đây; editorial dùng trọng số và số học 64-bit.

**Nguồn:** [editorial chính thức, trang PDF 3–4](olympiad_sources/BOI_2018_day2.pdf#page=3).

## 4. COI 2016 — Palinilap

### Đề tóm tắt

Cho một chuỗi. Được thay đổi tối đa một ký tự để tối đa hóa số substring palindrome. Các lần xuất hiện ở vị trí khác nhau được tính riêng.

### Transformation

**Thử mọi sửa đổi × mọi palindrome → mỗi tâm chỉ có hai sửa đổi có thể tạo palindrome mới.**

Với một tâm, mở rộng ra ngoài đến khi gặp cặp ký tự lệch đầu tiên tại l và r:

```text
... X [ phần giữa đang là palindrome ] Y ...
    l                                  r
```

Nếu X khác Y, mọi palindrome mới ở tâm này đều phải chứa cả l và r. Chỉ sửa một ký tự, nên bắt buộc sửa `l → Y` hoặc `r → X`.

Sửa chỗ khác sẽ không xóa được cặp lệch này. Vì thế mỗi tâm đóng góp gain cho **tối đa hai cặp (vị trí, màu mới)**, thay vì cho mọi sửa đổi.

Sau khi sửa cặp lệch, dùng LCE/hash để xem có thể mở rộng thêm bao xa; cộng số palindrome mới vào hai ứng viên. Palindrome bị mất tính bằng đóng góp theo tâm và interval sweep. Khi tính loss phải phân biệt vị trí nằm ở giữa đối xứng: đổi ký tự trung tâm của palindrome lẻ không phá palindrome đó.

**Cue:** một chỉnh sửa làm một cấu trúc mở rộng được → tìm vật cản đầu tiên; chỉ các chỉnh sửa chạm vật cản ấy mới có tác dụng.

**Giới hạn:** áp dụng cho một sửa đổi; không suy ra mỗi tâm chỉ có hai ứng viên nếu cho phép sửa nhiều ký tự. Hash có rủi ro collision; Manacher và cấu trúc LCE có thể thay một số phần so sánh.

**Nguồn:** [editorial chính thức, trang PDF 2–3](olympiad_sources/COI_2016.pdf#page=2). Đã kiểm tra phần gain ở cả tâm chẵn và lẻ bằng liệt kê palindrome trước/sau sửa.

## 5. COCI 2016/2017 R2 — Burza

### Đề tóm tắt

Có cây, đồng xu xuất phát ở đỉnh 1. Mỗi lượt, Daniel đánh dấu một đỉnh; người kia đánh dấu đỉnh đồng xu đang đứng rồi chuyển đồng xu sang một hàng xóm chưa đánh dấu. Daniel cần một kế hoạch đánh dấu cố định bảo đảm đối phương không đi được k bước, bất kể đường đi được chọn. N ≤ 400.

### Transformation thứ nhất: game → phủ các subtree

Root cây tại 1. Vì các đỉnh đã đi qua bị đánh dấu, đồng xu không thể quay lại: sau i bước nó ở độ sâu i.

Ở lượt i, có thể đưa lựa chọn đánh dấu về một đỉnh độ sâu i: đánh dấu sâu hơn thì thay bằng tổ tiên ở độ sâu i sẽ chặn nhiều đường hơn; đánh dấu quá nông không còn chặn hành trình đang tiến xuống.

Vậy cần chọn tối đa một đỉnh mỗi độ sâu 1..k, sao cho **mọi đường từ root đến độ sâu k đều bị chặn**. Cắt bỏ phần cây không dẫn tới độ sâu k; mỗi subtree giờ phủ một interval của các lá trong thứ tự DFS.

### Transformation thứ hai: tham số lớn → đáp án luôn YES

Editorial chứng minh **k² ≥ N là điều kiện đủ để Daniel thắng**. Đây không phải điều kiện cần, cũng không phải quy luật chỉ đoán từ chạy test.

Chứng minh dùng greedy chọn nhánh có điểm phân nhánh sớm, đếm số đỉnh bị loại rồi quy nạp trên forest còn lại. Phần chứng minh này riêng của bài và dài hơn cue; cần đọc nguồn nếu muốn sử dụng bound.

Nếu k² < N ≤ 400, k chỉ còn tối đa 19. Có thể DP theo prefix lá đã phủ và bitmask các độ sâu đã dùng: xử lý lá đầu tiên chưa phủ, thử đánh dấu một tổ tiên ở độ sâu chưa dùng, rồi phủ hết interval subtree của nó.

**Cue:** trước khi dùng exponential theo k, thử chứng minh k lớn luôn dễ/luôn có đáp án; chỉ nhánh khó mới cần bitmask.

**Đánh giá:** bước đổi game thành static cover khá hay; bound k² là phần riêng phải hiểu. Không nên chép theorem này sang game cây khác.

**Nguồn:** [đề gốc](https://hsin.hr/coci/archive/2016_2017/contest2_tasks.pdf), [editorial chính thức, mục Burza cuối PDF](olympiad_sources/COCI_2016_2017_R2.pdf). Check nhỏ kiểm tra điều kiện đủ bằng vét cạn các lựa chọn theo độ sâu, không thay thế chứng minh cho mọi N.

## 6. CEOI 2017 — Palindromic Partitions

### Đề tóm tắt

Chia chuỗi thành nhiều chunk liên tiếp nhất sao cho dãy chunk đọc từ trái sang phải giống đọc từ phải sang trái. Hai chunk đối xứng phải bằng nhau, nhưng bản thân từng chunk không cần là palindrome.

Ví dụ `abcXYZabc` chia thành `abc | XYZ | abc` được 3 chunk.

### Transformation

**DP thử mọi cặp prefix/suffix bằng nhau → luôn bóc cặp bằng nhau ngắn nhất.**

Nếu prefix và suffix ngắn nhất, không chồng nhau, bằng nhau là C, chọn chúng làm hai chunk ngoài rồi tiếp tục với phần giữa. Nếu không có cặp như vậy, phần còn lại là một chunk.

Điều khó là chứng minh việc bóc ngắn nhất không làm mất nghiệm tối ưu. Editorial xét một chunk ngoài dài hơn C: nó có C ở cả đầu và cuối; nếu hai bản C không chồng thì tách nhỏ được ngay, nếu chồng thì cấu trúc border/periodicity vẫn cho một cách tách mịn hơn. Một nghiệm tối ưu dùng chunk ngoài dài hơn vì thế có thể bị cải thiện hoặc đổi về lựa chọn greedy.

Rolling hash cho phép tăng đồng thời prefix/suffix và cắt ngay khi chúng bằng nhau, chỉ O(n) bước hash. Đây là tốc độ của phép so sánh fingerprint; không khẳng định mọi implementation hash có bảo đảm deterministic O(n).

**Cue:** tối đa số mảnh đối xứng → thử border nhỏ nhất; cần chứng minh có thể tinh chỉnh mọi lựa chọn border lớn hơn.

**Đánh giá:** hữu ích nếu chưa biết chunked-palindrome greedy, nhưng có thể quá quen với bạn. Để ở danh sách cân nhắc, không tự đưa vào notebook.

**Nguồn:** [editorial chính thức, trang PDF 3–4](olympiad_sources/CEOI_2017_day2.pdf#page=3).

## Nhật ký lọc đủ 29 bài

| Cụm đã đọc | Bài | Nhận xét / quyết định |
|---|---|---|
| COCI 2016/2017 R2 | Go | Công thức hóa mô phỏng; quá cơ bản |
| COCI 2016/2017 R2 | Tavan | Thứ tự từ điển → chữ số cơ số K; quen thuộc |
| COCI 2016/2017 R2 | Nizin | Gộp đầu nhỏ hơn nhờ số dương; two pointers, không giữ |
| COCI 2016/2017 R2 | Prosječni | Construction bảng trung bình; quá riêng |
| COCI 2016/2017 R2 | Zamjene | DSU + fingerprint multisets; hay nhưng trùng hướng hashing đã có |
| COCI 2016/2017 R2 | Burza | Game → static cover → large-k theorem; giữ để review |
| COI 2015 final exam 2 | Dostava | Khoảng cách nearest-site bằng đúng D → cấm phần trong, cần witness trên biên; xoay Manhattan/sweep đã khá quen, không ưu tiên |
| COI 2015 final exam 2 | Nafta | Pool liên thông chiếu xuống trục thành interval; chỉ điểm đã chọn gần nhất quyết định interval nào mới nhận; ứng viên dự phòng, không giữ D&C DP như cue riêng |
| COI 2016 | Dijamant | Bỏ các parent bị parent khác bao về reachability, rồi kiểm tra giao ancestor sets; dự phòng |
| COI 2016 | Palinilap | Mỗi tâm chỉ sửa ở cặp lệch đầu tiên; giữ để review |
| COI 2016 | Relay | Miền visibility của relay lồng nhau, chỉ giữ tangent cực trị; phụ thuộc hình học riêng, không ưu tiên |
| COI 2016 | Torrent | Hai nguồn → một cạnh ngăn hai lãnh thổ trên cây; thời gian hai phía ngược chiều → binary search; dự phòng, phần scheduling/exchange không giữ |
| BOI 2018 day 1 | Love Polygon | Functional graph → giữ nhiều cặp nhất / matching trên cây và cycle; không ưu tiên |
| BOI 2018 day 1 | Martian DNA | Sliding window đếm nhu cầu; không giữ |
| BOI 2018 day 1 | Worm Worries | Local maximum: query separator giữ witness; random sampling rồi ascent có cận theo rank; đáng khảo sát tiếp, không gán xác suất chạy tốt cho mọi biến thể |
| BOI 2018 day 2 | Alternating Current | Bỏ containment, đổi sang alternating directions với một chỗ lệch trên vòng lẻ; construction riêng, không ưu tiên |
| BOI 2018 day 2 | Genetics | Weighted random combination của cả họ điều kiện; giữ để review |
| BOI 2018 day 2 | Paths | Màu không lặp → mask màu thay visited vertices; color coding đã có, không giữ riêng |
| APIO 2007 | Mobiles | Tree DP phân loại complete/partially-complete; quen thuộc |
| APIO 2007 | Backup | Greedy có thể hoàn tác qua cạnh ảo; giữ để review |
| APIO 2007 | Zoo | Max-SAT có cửa sổ ngắn → frontier mask DP; quen thuộc |
| APIO 2017 | Rainbow | Connectivity → faces → Euler + range counting; giữ để review |
| APIO 2017 | Merchant | Profit/time → trọng số profit − rate·time → cycle feasibility; bài luyện ratio-to-cycle, không ưu tiên thêm |
| CEOI 2017 day 1 | One-Way Streets | Co bridge-connected components; bên trong định hướng mạnh được, chỉ bridges bị ép; dự phòng |
| CEOI 2017 day 1 | Sure Bet | Sort prefix và tối ưu hai đại lượng ngược chiều; không giữ |
| CEOI 2017 day 1 | Mousetrap | Đưa thao tác chặn lên trước dọn đường để có normal form; game DP riêng, không ưu tiên |
| CEOI 2017 day 2 | Building Bridges | Tổng cost phá cột − cost cột giữ, rồi CHT; technique quen thuộc |
| CEOI 2017 day 2 | Chase | Di chuyển chim phức tạp nhưng gain tại một bước chỉ phụ thuộc đỉnh trước đó; có thể khảo sát tiếp, chưa chọn cue |
| CEOI 2017 day 2 | Palindromic Partitions | Bóc border ngắn nhất; giữ để review |

## Kiểm chứng đã làm

Chạy `python3 material/olympiad_transformation_checks.py`:

| Nhận xét | Oracle độc lập | Số đối chiếu |
|---|---|---:|
| Backup | Vét cạn matching k cạnh không kề nhau, so với contraction | 2.400 |
| Palinilap | Liệt kê palindrome trước/sau sửa, so với gain từ first mismatch | 5.460 |
| Rainbow | Flood fill đất trong query, so với công thức Euler | 3.000 |
| Burza | Vét cạn lựa chọn theo độ sâu ở cây nhỏ, kiểm tra bound đủ | 840 |
| **Tổng** | | **11.700** |

Đây là kiểm chứng nhỏ của các nhận xét, không phải 29 lời giải AC. Chưa viết/submit full solution cho các bài khảo sát. Genetics có phân tích xác suất nhưng chưa benchmark implementation; Palindromic Partitions dựa vào chứng minh trong editorial. Không đưa các bound probabilistic hay thử nghiệm thành theorem deterministic.

Nếu chọn ít nhất có thể để notebook gọn, ưu tiên đọc **Backup → Rainbow → Genetics** trước; các mục còn lại là ứng viên để bạn loại tiếp.
