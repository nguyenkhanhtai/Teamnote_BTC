# CEOI 2022–2026 — nhận xét của từng bài

Bản đọc trước khi chọn vào notebook: **30 bài, chia theo năm**. Mỗi mục giữ đề, bước suy luận then chốt và giới hạn của nhận xét. Không chấm sao ngay từ đầu: một bài có thể hay ở invariant, construction, chứng minh bound hoặc thiết kế state, dù không thích hợp làm một dòng transformation.

**Mức đối chiếu:** E = editorial chính thức; M = model solution chính thức; P = suy luận độc lập. Nhận xét cục bộ không đồng nghĩa đã có toàn bộ lời giải full-score. Những phần còn thiếu chứng minh được ghi ngay trong mục đó. Chưa sửa notebook/PDF.

## 2022

Nguồn E: [editorial cả hai ngày](https://archive.uoi.ua/static/ceoi2022-tutorials.pdf), [bản lưu](olympiad_sources/recent/CEOI_2022_solutions.txt).

### 1. Abracadabra — refinement thay cho simulation

**Đề:** Lặp thao tác chia đôi bộ bài rồi interleave bằng cách so hai lá đầu, lấy lá nhỏ hơn trước. Query hỏi lá ở vị trí i sau t shuffle.

**Nút thắt:** Một shuffle tuyến tính nhưng t có thể rất lớn; cần tìm đại lượng luôn tiến triển, không chỉ đoán quá trình sẽ ổn định.

**Nhận xét:** Chia hoán vị thành block bắt đầu tại các prefix record maximum. Mỗi block có phần tử đầu lớn nhất; shuffle thực chất merge các block theo phần tử đầu. Chỉ block vắt qua điểm chia đôi bị tách; các block không bao giờ hợp lại. Mỗi shuffle thay đổi bộ bài làm số block tăng ít nhất 1 ⇒ tối đa N−1 shuffle hữu hiệu.

**Đi tiếp:** Block vẫn là một đoạn của hoán vị gốc. Next-greater giúp tách block; set giữ thứ tự, Fenwick theo độ dài trả query offline. Editorial cho `O((N+Q) log N)`.

**Cái hay:** *Mô phỏng dài ⇒ tìm partition chỉ refine, không merge*. Bound số lần và cách thực hiện nhanh cùng đến từ một representation. **E; đáng giữ.**

### 2. Homework — threshold certificates thay cho gán hoán vị

**Đề:** Điền hoán vị 1..N vào các lá của biểu thức min/max; đếm giá trị có thể xuất hiện ở root.

**Nhận xét:** Qua threshold, min thành AND, max thành OR. Gọi c1/c0 là số lá 1/0 ít nhất đủ ép root thành 1/0: AND cộng c1, lấy min c0; OR lấy min c1, cộng c0. Các giá trị có thể đạt là `[c0, N−c1+1]`.

**Vì sao không có lỗ:** Các hoán vị nối được qua đổi hai giá trị liên tiếp. Mỗi lá đổi tối đa 1, nên root min/max cũng đổi tối đa 1. Đi từ cấu hình đạt min tới cấu hình đạt max phải đi qua mọi giá trị giữa chúng.

**Cái hay:** *Bỏ nhãn cụ thể bằng threshold + chứng minh ảnh của state space liên thông là interval*. Editorial dùng interval DP tương đương; cách certificate/no-holes là diễn giải độc lập, đã brute-check trên cây nhỏ. **E+P; ưu tiên.**

### 3. Prize — phương trình đường đi thành hiệu potential

**Đề cốt lõi:** Hai cây có chung tập nhãn; thiết kế tập nhãn và query để khôi phục phần cây nhỏ cùng trọng số cạnh, dù thông tin query đồng thời liên quan hai cây.

**Nhận xét:** Chọn K nhãn đầu theo preorder cây thứ nhất; sắp chúng theo preorder cây thứ hai và hỏi các cặp kề. Thêm các LCA nhận được tạo virtual tree. Thay biến trọng số từng cạnh bằng `d(v)` = khoảng cách từ root: đường ancestor–descendant cho phương trình `d(x)−d(y)=w`.

**Vì sao hữu ích:** Hệ phương trình chỉ còn difference equalities; dựng graph phương trình, DFS gán potential. Cấu trúc query kề nhau bảo đảm connectivity cần thiết, tránh Gaussian elimination. Editorial còn có hướng chọn subsequence đồng điệu trong hai preorder bằng Erdős–Szekeres khi `K²≤N`; đây là hướng khác, không phải bước bắt buộc của full solution.

**Cái hay:** *Thiết kế query để hệ phương trình có cấu trúc*, chứ không nhận hệ rồi giải tổng quát. **E; phần protocol đề tương tác cần đọc gốc trước khi triển khai.**

### 4. Drawing — thêm ràng buộc để recursion dễ ghép hơn

**Đề:** Gán các đỉnh cây bậc tối đa 3 vào các điểm hình học, vẽ cạnh thẳng không cắt nhau.

**Nút thắt:** Chia điểm theo góc cho từng subtree dễ đúng nhưng có thể thành recursion lệch, thời gian bậc hai.

**Nhận xét:** Strengthen subproblem: từ một cặp đỉnh–điểm cố định thành hai cặp, root và một leaf được neo vào hai điểm kề nhau trên convex hull. Chọn đỉnh giữa đường root–leaf và điểm phân chia phù hợp, tạo các miền con vẫn giữ được invariant điểm neo.

**Bound:** Chọn leaf theo heavy path; chia đôi đường neo. Các nhánh light có size≤N/2, cho recurrence tổng `O(N log²N)` nếu partition điểm tuyến tính, không sort lại toàn bộ ở mỗi lần gọi.

**Cái hay:** *Thêm điều kiện biên vào interface recursion để lời giải đóng dưới phép chia*. Đây là bài hay về thiết kế subproblem, không nên bỏ chỉ vì construction riêng. **E; lemma tồn tại điểm chia tốt trong editorial chỉ được phác thảo, chưa có proof đầy đủ ở note này.**

### 5. Measures — thời gian đồng bộ thành maximum drawdown

**Đề:** Các người trên trục số di chuyển tốc độ≤1; sau khi thêm người, tìm thời gian nhỏ nhất để mọi khoảng cách kề≥D.

**Nhận xét:** Có thể giữ thứ tự người bằng exchange. Với i≤j, cần `2t≥(j−i)D−(a[j]−a[i])`. Cận này đạt được: đặt `b[1]=a[1]−t`, rồi `b[i]=max(a[i]−t,b[i−1]+D)`; các cận trên bảo đảm `b[i]≤a[i]+t`.

**Transformation:** Đặt `x[i]=a[i]−iD`; đáp án là `max_{i≤j}(x[i]−x[j])/2`. Thêm người làm x của cả suffix giảm D, nên dynamic movement trở thành range-add và cực trị.

**Cái hay:** *Cận từ mọi cặp + construction greedy đạt cận ⇒ bỏ binary search*. **E; đáng giữ cả cận và construction, không chỉ công thức đổi tọa độ.**

### 6. Parking — ghép hai loại quan hệ để lộ chain/cycle

**Đề:** Mỗi chỗ đỗ chứa tối đa hai xe theo stack; mỗi màu có hai xe. Di chuyển xe trên cùng để ghép hai xe cùng màu, tối thiểu số moves hoặc báo không thể.

**Nhận xét:** Graph có đỉnh là vị trí xe, cạnh nối hai xe cùng màu và hai vị trí trong một chỗ đầy. Bậc≤2 ⇒ mỗi component là chain/cycle. Bài toán không gian trống trở thành budget để phá các component này.

**Điểm khó:** Chain không có top-pair xử lý không cần chỗ trống phụ; chain có top-pair cần một. Cycle cần một, hoặc hai nếu có nhiều top-pair. Giải chain trước tạo thêm chỗ trống, rồi mới xử lý cycle. Phân loại còn giúp đạt lower bound số moves; cycle không có top-pair cần move phụ để phá vòng.

**Cái hay:** *Chồng hai matching ⇒ degree-2 graph*, rồi tối ưu thứ tự component theo tài nguyên nó tạo/tiêu thụ. **E; hay về mô hình, implementation construction cần giữ các case.**

## 2023

Nguồn E: [trang task chính thức, kèm spoiler từng bài](https://www.ceoi2023.de/index.php/tasks/); bản lưu trong `olympiad_sources/recent/CEOI_2023-day*/` và `CEOI_2023_avoid_editorial.txt`.

### 7. Light — invariant phải sống sót qua thao tác ngược

**Đề:** Người cầm đuốc thêm/rời ở cuối hàng. Sau mỗi lần, cho lửa lan t vị trí sang phải rồi tùy chọn tắt đuốc; phải giữ đuốc cuối sáng, ít đuốc sáng và t nhỏ so với số người thay đổi.

**Nhận xét:** Đánh số từ cuối hàng; nếu các vị trí sáng là `1=f1<f2<…`, điều kiện `f[i]≤2f[i−1]+1` và đuốc ngoài cùng còn lại sáng cho phép xử lý mọi lần leave bằng t=p. Chọn đuốc kế tiếp xa nhất có thể nhưng vẫn thỏa khoảng đó; mỗi hai đuốc được chọn thì vị trí tăng hơn gấp đôi ⇒ chỉ `O(log N)` đuốc.

**Điểm khó:** Chỉ đặt đuốc tại power-of-two không đủ: một lần xóa đúng ở biên có thể làm invariant sụp. Editorial chứng minh sau leave vẫn tìm được đuốc trong từng khoảng cần thiết, rồi sparsify lại.

**Cái hay:** *Representation thưa không chỉ phủ trạng thái hiện tại; phải chứng minh tái tạo được sau mọi update*. **E; đáng đọc về online invariant.**

### 8. Grading Server — chứng minh chiến lược thắng để giới hạn miền DP

**Đề:** Hai người luân phiên tấn công computing power hoặc phá một firewall của đối thủ; firewall giảm sát thương theo hệ số S. Xác định ai thắng cho nhiều trạng thái.

**Nhận xét:** Dùng sát thương hiệu dụng `α1=c1−S f2`, `α2=c2−S f1`. Nhiều vùng có hành động tối ưu bắt buộc hoặc chiến lược thắng rõ ràng. Chỉ DP vùng còn mơ hồ. Với `βi=S−αi`, chiến lược phá một nửa firewall, tấn công, rồi phá phần còn lại cho thắng khi `β2·max(f1,1)·f2²>8S`.

**Bound then chốt:** Miền chưa được giải ngay thỏa bất đẳng thức ngược. Số tuple `(f1,β2,f2)` là `O(S log S)`: tổng theo f2 dùng `Σ1/f2²` hội tụ, rồi tổng theo β2 dùng harmonic series. Một chiều computing power còn được nén thành ngưỡng thắng nhờ monotonicity.

**Cái hay:** *Không đoán cutoff: dựng chiến lược đủ mạnh để chứng minh mọi state ngoài miền nhỏ đều dễ*. **E; đây là chuỗi lemma, note một dòng sẽ mất context.**

### 9. Balance — cân bằng S màu bằng chia đôi Euler

**Đề:** N core, mỗi core có S submission, S là power-of-two. Mỗi phút mỗi core xử lý một bài; với mỗi task, số submission giữa các phút lệch≤1.

**Nhận xét:** Submission là cạnh core–task. Thay việc lấy perfect matching S lần bằng chia cạnh làm hai nửa cân bằng tại mọi đỉnh, recurse. Thêm core giả nối các task bậc lẻ; tô luân phiên trên Euler tour chẵn của graph bipartite.

**Vì sao đủ:** Bậc core luôn chia đúng đôi, bậc task chia floor/ceil. Sau log S tầng, mỗi màu là một slot và các slot của từng task lệch≤1. `O(NS log S)`.

**Cái hay:** *Cân bằng nhiều nhóm ⇒ chỉ cần primitive chia đôi cân bằng*. **E; dễ đưa vào notebook, giữ điều kiện power-of-two.**

### 10. Trade — chứng minh monotone argmax bằng planar uncrossing

**Đề:** Mua cả một đoạn robot, trả tổng cost; bán đúng K robot trong đoạn lấy tổng sale value. Tìm lợi nhuận lớn nhất và các robot có thể được bán trong một nghiệm tối ưu.

**Nhận xét:** DP theo vị trí và số robot bán là longest path trên grid DAG: mỗi bước đi ngang hoặc chéo. Hai nghiệm có đầu trái tăng nhưng đầu phải giảm buộc giao nhau; đổi đuôi ở điểm giao vẫn hợp lệ. Tính tối ưu ép hai đuôi có cùng trọng số.

**Hệ quả:** Chọn đầu phải tối ưu nhỏ nhất cho mỗi đầu trái ⇒ argmax không giảm. D&C optimization kiểm tra `O(N log N)` đoạn; hai multiset hoặc persistent tree lấy tổng K phần tử lớn nhất, tổng `O(N log²N)`.

**Điểm thêm:** Không thể duyệt mọi đoạn đồng tối ưu để tìm tất cả robot: có thể tới N² đoạn. Cùng lemma uncrossing giúp chỉ giữ `O(N)` đoạn đại diện đủ bao các chỉ số tối ưu.

**Cái hay:** *Vẽ graph DP trước khi cố chứng minh Monge bằng đại số*. **E; ưu tiên, có hai lần dùng chung một structural lemma.**

### 11. Incursion — điểm neo canonical + mỗi lần sai làm giảm nửa

**Đề:** Hai người có cùng cây bậc≤3 nhưng nhãn khác nhau; người biết đích đánh dấu phòng, người đi chỉ thấy dấu khi vào phòng. Phải tìm đích với detour rất nhỏ so với shortest path.

**Nhận xét:** Center/centroid là một đỉnh hoặc hai đỉnh kề nhau, nhận diện được mà không phụ thuộc nhãn. Đánh dấu đường từ neo tới đích. Đi về neo đến khi gặp dấu rồi lần theo đường đánh dấu; khi không biết child nào có dấu, thử child lớn nhất trước.

**Bound:** Mỗi lần thử nhầm rồi quay lại, child đúng nhỏ hơn nửa subtree đang xét. Detour mỗi lần là 2 ⇒ logarithmic. Editorial phân tích thêm trường hợp root có ba nhánh để đạt đúng budget 30; không thể thay bằng một cận O(log N) mơ hồ.

**Cái hay:** *Giao tiếp khi không chung ID ⇒ chọn cấu trúc canonical; giới hạn lỗi bằng heavy-first*. **E; ưu tiên.**

### 12. Avoid — truy vấn OR thành bộ mã có pairwise unions duy nhất

**Đề:** Hai người ở hai trong 1000 vị trí, có thể trùng vị trí. Mỗi robot hỏi một tập vị trí và trả có ai trong tập không. Với một đợt hỏi, full-score cần≤26 robot.

**Nhận xét:** Đảo góc nhìn: mỗi vị trí p có bitmask C[p] của robot được gửi tới nó. Vector đáp án là `C[a] OR C[b]`. Cần mọi unordered pair (kể cả a=b) có OR khác nhau; giải mã bằng bảng OR→pair.

**Cái hay:** *Nonadaptive queries ⇒ thiết kế codewords theo phép gộp của oracle*. Sinh mã offline bằng search/heuristic, nhưng kiểm tra toàn bộ `N(N+1)/2` OR để chứng nhận bộ mã cố định. Editorial dùng greedy, distance constraints và simulated annealing để đạt 26; không chứng minh một random sample bất kỳ đủ tốt.

**Đánh giá:** Hay về thiết kế và verification: tách “tìm witness khó” khỏi “kiểm tra witness dễ”. **E; không có construction đóng gọn đạt 26 trong note này.** [Spoiler](https://www.ceoi2023.de/wp-content/uploads/2023/09/6-avoid-spoiler.pdf).

## 2024

Nguồn E: [trang kỳ thi](https://ceoi2024.fi.muni.cz/); mỗi mục có link editorial riêng.

### 13. Battle — event chỉ xuất hiện giữa hàng xóm sống

**Đề:** Tàu trên lưới đi thẳng cùng tốc độ theo bốn hướng; va chạm làm tàu chìm. Tìm kết quả mà không mô phỏng thời gian khổng lồ.

**Nhận xét:** Với mỗi cặp hướng, các tàu có thể gặp nhau nằm trên cùng một hàng/cột/đường chéo. Nếu có tàu nằm giữa cặp sắp va chạm, nó sẽ va chạm trước với một đầu. Vì thế event kế tiếp chỉ cần cặp hàng xóm trong các linked list, giống hai ngoặc kề nhau có thể triệt tiêu.

**Điểm khó khi code:** Một tàu thuộc nhiều list; event cũ có thể stale. Giữ death time và xử lý cùng timestamp đúng để không bỏ tàu thứ ba cùng va chạm. Xóa làm lộ hàng xóm mới, nên tổng số event tuyến tính, PQ cho `O(N log N)`.

**Cái hay:** *N² tương tác ⇒ adjacency certificate + sửa certificate khi đối tượng biến mất*. **E; [editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/battle.pdf).**

### 14. COVID — tìm người dương tính đầu tiên để tái lập state

**Đề:** Mỗi mẫu dương tính độc lập với xác suất P; query trộn mẫu trả OR. Thiết kế chiến lược tìm mọi mẫu dương tính với ít query kỳ vọng.

**Nhận xét:** Test một block rồi tìm mọi người trong block giữ nhiều thông tin điều kiện khó quản lý. Thay bằng tìm **người dương tính đầu tiên**: khi tìm được, mọi vị trí trước nó đã xác định, phần chưa xử lý lại là suffix với phân phối ban đầu.

**State:** Độ dài suffix chưa xử lý và độ dài prefix biết chắc có người dương tính. Query tiếp luôn một prefix; kết quả co prefix hoặc bỏ các vị trí âm. DP thử độ dài query để tối ưu expectation trong family chiến lược này.

**Cái hay:** *Chọn mục tiêu trung gian sao cho sau khi đạt mục tiêu, quá trình reset về cùng loại state*. **E; editorial tối ưu family này, không cung cấp proof rằng nó tối ưu trong mọi chiến lược query tùy ý.** [Editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/covid.pdf).

### 15. Editor — normalize đường đi trước khi dựng graph lớn

**Đề:** Di chuyển con trỏ bằng bốn phím mũi tên trong văn bản có các dòng dài ngắn khác nhau; lên/xuống có thể clamp cột, trái/phải có thể nhảy dòng. Tìm ít keypress nhất.

**Nhận xét:** Nếu không qua cột đầu, có thể dời mọi bước ngang xuống cuối; phần dọc chỉ cần đi tới một dòng trung gian rồi về dòng đích. Nếu qua cột đầu, không cần ghé nó nhiều lần: đi giữa hai dòng tại cột đầu đã đạt lower bound chênh lệch dòng.

**Đi tiếp:** Chia đường đi thành “chưa qua cột đầu” hoặc “đến cột đầu → chạy dọc → thoát”. Clamp dọc là range minimum độ dài dòng, nên chỉ enumerate dòng trung gian, không enumerate mọi ô. Editorial giải tuyến tính.

**Cái hay:** *Exchange đổi thứ tự thao tác ⇒ normal form của shortest route*. **E; [editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/editor.pdf).**

### 16. Toy — chỉ bỏ tọa độ sau khi chứng minh fiber liên thông

**Đề:** Hai thanh ngang/dọc dài cố định, trượt độc lập trong mê cung nhưng luôn giao nhau. Hỏi có thể đưa giao điểm tới ô đích không.

**Nhận xét:** Fix giao điểm: vị trí khả thi của từng thanh là một interval, có thể trượt giữa mọi vị trí đó mà giữ giao điểm. Mọi cấu hình cùng giao điểm thuộc một component ⇒ contract chúng thành một state.

**Cạnh mới:** Khi đổi giao điểm sang hàng kề, phải có một vị trí thanh ngang nằm trọn phần trống chung hai hàng. Tương tự khi đổi cột. Test bằng độ dài intersection các interval, rồi BFS trên HW ô.

**Cái hay:** *State compression là quotient connectivity, không chỉ xóa biến vì “có vẻ không cần”*. **E; ưu tiên.** [Editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/toy.pdf).

### 17. Stations — nhiều route cùng lịch sử nhiên liệu thành một cohort

**Đề:** Trên cây có N² xe, một xe cho mỗi ordered pair đầu–cuối. Xe chỉ đổ đầy khi không đủ tới thành phố kế; đếm lượt refuel tại từng thành phố.

**Nhận xét:** Nhiều đích có cùng prefix route nên cùng trạng thái nhiên liệu. Gom cohort theo **tầm đi còn lại**, giữ multiplicity thay vì từng xe. Khi một cohort refuel, nhiều tầm đi khác nhau collapse về cùng tầm đi mới.

**Hai cách ghép:** Root cây, tách route lên rồi xuống; propagate multiset nhiên liệu bằng offset và small-to-large, nhưng hướng xuống giữ một family `O(log N)` multiset thay vì merge hai tập lớn. Hoặc centroid decomposition: gom các prefix tới centroid, DFS suffix với rollback các cohort refuel.

**Cái hay:** *Tương tác N² ⇒ gom theo shared history, reset operation còn làm state co lại*. **E; nhận xét dùng lại được, full implementation là phần dài.** [Editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/stations.pdf).

### 18. Sprinklers — loại pattern bằng exchange để chỉ nhớ suffix nhỏ

**Đề:** Vòi tưới trên trục số chọn trái/phải; tối thiểu tầm phun chung để phủ mọi bông hoa.

**Nhận xét:** Ba vòi liên tiếp trong một tầm phun không cần cùng hướng. Nếu cùng hướng, đảo vòi giữa không mất vùng phủ: phần cũ được vòi ngoài cùng cùng hướng phủ thay. Sửa dần để có nghiệm normalized; không khẳng định mọi nghiệm ban đầu đều có dạng này.

**Đi tiếp:** DP chỉ cần vài trạng thái hướng cuối; editorial có cách tuyến tính trực tiếp hoặc binary search tầm phun với feasibility DP.

**Cái hay:** *Existence của nghiệm tránh pattern ⇒ giảm memory của DP*. **E; [editorial](https://ceoi2024.fi.muni.cz/page/tasks/editorials/sprinklers.pdf).**

## 2025

Nguồn: [đề và model trong mirror chính thức SEPI](https://github.com/asociatia-sepi/archive/tree/main/CEOI-2025). Boardgames có E trong gói; Highest có [editorial tác giả, bản lưu trên QOJ](https://qoj.ac/download.php?id=14052&type=solution). Bốn bài còn lại dùng M và suy luận độc lập, không gắn nhãn editorial khi chưa có tài liệu đó.

### 19. Boardgames — tìm một chỗ cắt bắt buộc thay vì DP mọi đoạn

**Đề:** Chia hàng đỉnh theo thứ tự nhãn thành ít đoạn nhất, mỗi đoạn phải liên thông trong induced graph của chính nó.

**Nhận xét:** Nếu cả đoạn đang xét liên thông thì lấy một nhóm. Nếu không, tồn tại hai đỉnh kề i,i+1 thuộc hai component khác nhau. Bất kỳ nhóm hợp lệ nào cũng không chứa đồng thời chúng ⇒ chỗ cắt i là bắt buộc. Recurse hai bên, tính lại connectivity trong từng induced graph; không được dùng component của graph ban đầu mãi.

**Điểm sâu hơn:** Để khỏi bậc hai, giữ nửa lớn và rebuild nửa nhỏ. DSU không xóa tùy ý được; editorial xếp các edge block theo power-of-two, rollback rồi replay phần còn giữ. Potential của block trả chi phí replay khi block bị tách nhỏ.

**Cái hay:** *Constraint sinh separator bắt buộc ⇒ recursion không cần thử mọi split*. Phần đáng học thứ hai là biến dữ liệu rollback dạng stack thành thao tác xóa hai đầu bằng blocking và potential. **E; ưu tiên cả model lẫn amortization.**

### 20. Highest — lifting theo ngân sách phải giữ boundary residue

**Đề:** Từ tầng i đi lên bất kỳ tầng trong hai interval, cost lần lượt 1 và 2. Nhiều query hỏi min-cost từ A tới B.

**Nhận xét:** Các tầng tới được với budget c tạo interval bắt đầu tại A, nên state là mốc xa nhất, không phải một điểm đến cố định. Nhưng ghép hai budget `2^k` không luôn đủ: một jump cost 2 có thể vắt qua điểm chia.

**Cách sửa:** Lưu cả reach với budget `2^k` và `2^k−1`. Khi doubling xét hai nửa thông thường, hoặc `(2^k−1) + một jump cost 2 + (2^k−1)`. RMQ lấy reach tốt nhất trên toàn interval tới được, không chỉ nhảy từ mốc xa nhất. Budget lẻ cũng ghép hai thứ tự chẵn/lẻ tương ứng.

**Cái hay:** *Compose các đoạn theo tổng cost ⇒ giữ thiếu hụt nhỏ ở biên khi một operation không thể cắt đôi*. **E; ưu tiên.** Editorial cho preprocessing `O(N log²N)` và query `O(log N)` với RMQ đủ bộ nhớ.

### 21. Lawnmower — residual capacity lớn nhưng chỉ có ít phase cần nhớ

**Đề:** Cắt các lane theo thứ tự, tank capacity C. Lane i có lượng cỏ v[i], một lượt đi hết lane tốn a[i]; chỉ đổ tank ở cuối lane, tốn B, và được đổ sớm. Min tổng thời gian, tank cuối cùng phải rỗng.

**Nhận xét:** Fix lần đổ sớm gần nhất j. Nếu từ đó chỉ đổ khi đầy, độ đầy tại boundary i là `(prefixGrass[i]−prefixGrass[j]) mod C`. Vì vậy mọi lịch sử j có cùng **phase `prefixGrass[j] mod C`** có diễn biến tương lai giống nhau; chỉ giữ cost tốt nhất của phase đó.

**Update:** Qua một lane, số lượt tăng thêm thay đổi đúng tại các phase vượt biên remainder của prefix. Thay update mọi trạng thái bằng cộng chung và cộng thêm trên một cyclic interval phase. Nén phase từ prefix, segment tree range-add/min; mở một phase mới từ global minimum tương ứng chọn đổ sớm tại boundary.

**Cái hay:** *Resource tới 10⁹ ⇒ quotient/remainder của tích lũy; nhiều lịch sử cùng phase có thể dominate nhau*. **M+P; đã đọc model, chưa trình bày full recurrence/cách hạch toán lần đổ cuối trong note này.**

### 22. Equalmex — đếm k khả thi thành tối đa số block

**Đề:** Với mỗi đoạn query, đếm số k mà có thể chia đoạn thành k đoạn con cùng mex; mex là số nguyên dương nhỏ nhất vắng mặt.

**Nhận xét:** Nếu các block cùng mex x thì cả đoạn cũng có mex x. Vì x vắng trong cả đoạn, mỗi block chỉ cần chứa đủ 1..x−1. Cắt greedy ngay khi đủ tập đó cho số block tối đa K; phần dư ghép vào block cuối.

**Tại sao đáp án là K:** Merging hai block không đổi mex x, nên mọi số lượng 1..K đều đạt được. Bài “đếm số k” thành một bài tối ưu, không cần DP theo k. Nếu x=1 thì mọi singleton hợp lệ ⇒ K bằng độ dài đoạn.

**Phần query lớn:** Model tổ chức D&C, gom các endpoint có cùng mex, tính greedy-block summaries và xử lý residual bằng last-occurrence queries. Có ba lượt residual trong source; **chưa có proof bound này trong bản note**, không chép nó thành quy tắc tổng quát.

**Cái hay:** *Statistic của union ép statistic từng block; tính đóng dưới merge loại bỏ chiều đếm*. **M+P; nhận xét đầu đủ chắc, thuật query full-score cần phân tích tiếp.**

### 23. Splits — phép biến đổi subsequence thành số descent

**Đề:** Split một hoán vị p bằng cách chia thành hai subsequence rồi nối chúng. Cho M hoán vị kết quả khác nhau; đếm những p có thể sinh ra tất cả.

**Nhận xét:** Viết mỗi kết quả q bằng vị trí các phần tử trong p. q là split của p khi và chỉ khi dãy vị trí đó có **tối đa một descent**. Một descent xác định chỗ tách; hai phần đều tăng ⇒ đảo lại được bằng interleave hai subsequence.

**Nén miền nghiệm:** Fix một q đầu vào. Mọi p là interleave của prefix/suffix q tại một cut. Nếu p khác tất cả q đã cho, mỗi q cần ít nhất một descent, nên tổng số descent phải đúng M. Trie của các q giúp biết lúc prefix p đã khác tất cả chúng: từ đó không được tạo thêm descent, những quan hệ thứ tự còn lại là bắt buộc. Model ghép trie frontier với two-stream DP.

**Cái hay:** *Inverse stable split ⇒ tính chất local của inverse permutation; tổng violation trở thành budget*. **M+P; descent equivalence đã chứng minh, counting toàn bộ còn cần invariant để không đếm p theo nhiều cut. Không coi mô tả này là full proof của model.**

### 24. Theseus — một bit hướng cạnh, detour trả bằng doubling

**Đề:** Ariadne biết graph và đích t, gắn mỗi cạnh một bit. Theseus không có memory, chỉ thấy ID node/hàng xóm và bit cạnh; từ start bất kỳ phải tới t trong shortest distance+14 bước, N≤10000.

**Nhận xét:** Một bit đủ mã hóa hướng cạnh bằng thứ tự ID hai đầu. BFS từ t chia layer; hướng cạnh khác layer về t. Vấn đề chỉ còn cạnh cùng layer: cần làm đường đi ngang ngắn mà người đi nhận ra chỉ từ dữ liệu local.

**Model:** Xử lý cạnh theo layer giảm dần rồi priority cạnh cố định giảm dần. Mỗi node có mass ban đầu 1. Cạnh cùng layer hướng mass nhỏ sang mass lớn; chuyển mass sang đầu nhận, đặt mass đầu mất bằng 0. Người đi chọn cạnh hướng ra có priority cao nhất.

**Lý do bound:** Ở cạnh ngang được chọn, node mất mass lần đầu trong thứ tự xử lý; đầu nhận có mass ít nhất bằng đầu gửi, nên mass của đoàn ít nhất nhân đôi. Đi xuống layer không giảm mass được truyền tiếp. Mass≤N ⇒ chỉ logarithmic bước ngang; các bước xuống đúng bằng khoảng cách BFS. Priority gắn labeling với routing nên không cần memory.

**Cái hay:** *Small-to-large không chỉ phân tích runtime: dùng nó để encode đường đi có ít lỗi*. **M+P; đã kiểm tra 81900 start states trên graph random nhỏ; finite tests không thay proof.** Source hiện dùng `paint`, dù bản đề ghi `label`.

## 2026

Nguồn E: [ngày 1](https://ceoi2026.fri.uni-lj.si/res/CEOI26-day1-solutions.pdf), [ngày 2](https://ceoi2026.fri.uni-lj.si/res/CEOI26-day2-solutions.pdf); đề và bản text nằm trong `olympiad_sources/recent/CEOI_2026_day*`.

### 25. Birdwatchers — subtree relocation chỉ đổi mass trên hai nhánh ancestor

**Đề:** Cây cấp trên–cấp dưới, mỗi node có số thành viên. Sau khi chuyển cả subtree sang cấp trên mới, tìm người sâu nhất có tổng thành viên dưới quyền ít nhất nửa toàn bộ.

**Nhận xét:** Các node đủ mass tạo một chain; đáp án là weighted centroid với tie-break sâu nhất. Khi chuyển subtree từ y sang z, mass subtree chỉ đổi trên hai đường y/z tới LCA; ở trên LCA hoặc trong subtree bị chuyển thì mass không đổi.

**Đi tiếp:** Tìm ứng viên mới dọc hai đường bị đổi thay vì descend lại toàn cây. Euler tour tree biến chuyển subtree thành cut/paste interval; lazy depth shift và minimum depth cho ancestor search. Editorial dùng treap/splay đạt `O(log²N)` mỗi update.

**Cái hay:** *Update toàn cấu trúc nhưng đại lượng quyết định chỉ đổi trên một vùng nhỏ*. **E; điều đáng đọc là localization + representation, không chỉ tên dynamic centroid.**

### 26. DFS — trace traversal thành lựa chọn cạnh độc lập

**Đề:** Cho output DFS gồm ID và depth, khi hàng xóm được xét theo ID tăng. Đếm graph có thể cho đúng output ấy.

**Nhận xét:** Stack khôi phục DFS tree, các tree edge bắt buộc. Cross-edge giữa hai subtree bị cấm. Back-edge tới ancestor có thể thêm nếu nó không làm DFS đi tới node sớm hơn: nhãn node phải lớn hơn child của ancestor dẫn vào nhánh đang xét.

**Vì sao đếm dễ:** Mỗi cạnh hợp lệ tự nó không đổi traversal; thêm đồng thời các cạnh đó vẫn không đổi, vì tới lúc được xét đầu kia đã visited. Có K cạnh tùy chọn ⇒ `2^K`. Duyệt DFS, giữ nhãn child đang active của các ancestor bằng Fenwick để đếm các lựa chọn.

**Cái hay:** *Inverse execution ⇒ phân loại quyết định mandatory/forbidden/independent*. **E+P; ưu tiên.** K có thể bậc hai nhưng chỉ cần đếm, không dựng từng cạnh.

### 27. Treasure Hunt — tìm boundary nơi một nghiệm không còn giải thích oracle

**Đề:** Có≤3 kho báu trên lưới rất lớn. Query trả các hướng của shortest routes tới kho báu gần nhất; nhiều kho có thể cùng gần và gây nhiễu.

**Nhận xét:** Khi đã tìm kho T, dọc một tia từ T, ban đầu đáp án được giải thích hoàn toàn bởi T. Tìm cell đầu tiên mà hướng trả về không còn chỉ quay về T: đó là boundary nơi một kho khác cạnh tranh khoảng cách. Manhattan distance biến thông tin boundary thành một cạnh của diamond chứa kho chưa biết.

**Điểm khó:** Tìm một tọa độ rồi tọa độ kia, tránh binary search cả hai đồng thời vì oracle có thể đổi kho gần nhất. Với ba kho, một kho tìm tiếp có thể không thuộc diamond mong đợi; giao các ràng buộc diamond từ nhiều boundary giúp tìm kho cuối.

**Cái hay:** *Oracle bị distractor ⇒ quan sát nơi lời giải đã biết ngừng chi phối, thay vì cố loại distractor khỏi query*. **E; hình học cụ thể và xử lý tie là phần thiết yếu, note này chưa đủ để code budget 11 log N.**

### 28. Flower Cutting — closure rule buộc maximal cliques không chung cạnh

**Đề:** Graph đã bão hòa theo rule: hai node có hai common neighbors thì thêm cạnh giữa chúng. Xóa nhiều cạnh nhất sao cho closure mọc lại đúng graph ban đầu.

**Nhận xét:** Một 4-cycle đóng thành K4. Hai clique chung hai node phải nhập thành clique lớn: mọi cặp node riêng có hai common neighbors. Vì thế maximal cliques có thể chung đỉnh nhưng không chung cạnh; bài toán seed graph tách theo clique.

**Construction:** Seed dạng ladder giúp thêm hai node chỉ bằng ba cạnh. Editorial đưa cận cạnh cho clique size c: `3c/2−2` nếu c chẵn, `3(c−1)/2` nếu c lẻ; clique size 2 chỉ giữ cạnh đó.

**Cái hay:** *Rule closure ⇒ decomposition thành blocks, rồi tối ưu seed trong từng block*. **E; proof tối ưu số cạnh còn thiếu trong editorial, nên mới ghi construction/structural observation, chưa xem công thức cực trị là đã chứng minh ở đây.**

### 29. Towers — pairing mất danh tính khi viết thành open/close gains

**Đề:** Ghép các máy tính trên trục số thành cặp; cable được đi qua các tower để có bonus, nhưng chiều dài gây penalty. Max tổng score.

**Nhận xét:** Với hai endpoint, score tách thành phần ở giữa và extension tối ưu trái/phải. Quét từ trái sang phải, endpoint chỉ là mở/đóng một pair; đóng pair nào không ảnh hưởng score nên bỏ được danh tính các endpoint đang mở.

**Bước mạnh hơn:** Cho mọi endpoint tạm làm đầu mở và kéo cable tới tận bên phải. Đổi endpoint i thành đầu đóng có gain d[i] độc lập nó ghép với ai. Chọn N/2 gain, với mỗi prefix i không được đóng quá floor(i/2) pair.

**Vì sao greedy:** Các prefix là family lồng nhau, tạo laminar matroid. Quét gain, giữ heap và bỏ gain nhỏ nhất khi vượt capacity; đây là maximum-weight basis có đúng N/2 phần tử, không chỉ một greedy thử nghiệm.

**Cái hay:** *Pairing ⇒ endpoint roles ⇒ chọn subset dưới prefix capacity*. **E+P; ưu tiên.** Editorial cho `O(N log N)`; cách nhận diện matroid giải thích phần optimality bị viết ngắn trong editorial.

### 30. VIM — chặn DP bằng construction, rồi tách tối ưu magnitude và exact witness

**Đề:** Từ một ký tự, dùng move/copy/paste theo quy tắc con trỏ để tạo đúng N ký tự, tối thiểu keypress và dựng lệnh.

**Nhận xét chắc:** Một construction dùng `O(√N)` lệnh cho upper bound L. Offset con trỏ từ cuối string là tọa độ tự nhiên: paste đổi offset đúng 1. State cần hơn L bước chỉ để tới offset đó không thể tối ưu ⇒ upper bound giúp cắt một chiều state.

**Nhận xét của editorial cho N lớn:** Normal form gồm các group một copy và n[i] paste. Khi đã ở form này, độ dài có công thức đối xứng theo n[i]: cố định tổng và số group thì **minimize Σn[i]²** để maximize độ dài, nên các group gần bằng nhau. Sau đó dịch paste giữa các group để giảm độ dài tới đúng N.

**Cái hay:** *Construction upper bound để chặn state; tối ưu “đạt ít nhất N” chưa đủ, phải dựng exact N*. **E; normal form/cutoff N nhỏ–lớn và thuật chỉnh exact length chưa được chứng minh đầy đủ trong note. Editorial có chỗ ghi maximize sum-of-squares, nhưng công thức ngay trước cho dấu trừ: phải là minimize.**

## Các mục nên đọc trước

Đây là thứ tự đọc đề xuất, không phải danh sách loại các bài khác:

| Muốn học gì | Bài |
|---|---|
| Partition chỉ refine để có amortized bound | Abracadabra |
| Tăng điều kiện biên để recursion đóng dưới phép chia | Drawing |
| Chứng minh miền DP nhỏ bằng chiến lược thắng | Grading Server |
| Chứng minh argmax monotone bằng hình học của DP | Trade |
| Giao tiếp không chung ID, chặn số lần thử sai | Incursion |
| Contract state qua connectivity | Toy |
| Separator bắt buộc và rollback blocking | Boardgames |
| Compose cost có operation vắt qua biên | Highest |
| Nén lịch sử bằng phase của prefix tích lũy | Lawnmower |
| Small-to-large để encode đường đi ít detour | Theseus |

## Kiểm tra và giới hạn

- Đã đọc **26 editorial** và **4 model** cho 30 mục; không đồng nghĩa đã implement/submit đủ 30 bài. Nguồn và phần chưa chứng minh được ghi ở từng mục.
- [Script kiểm tra mới](ceoi_transformation_checks.py) chạy thành công: Theseus 81900 start states trên graph random nhỏ; Equalmex 1092 xâu với mọi partition; Splits 15017 cặp hoán vị; DFS 146 trace từ mọi graph liên thông N≤5. Đây là kiểm tra hữu hạn của các nhận xét tự bổ sung.
- Homework dùng kiểm tra đã có trong [script khảo sát trước](oi_recent_transformation_checks.py): 175 expression tree, duyệt mọi hoán vị lá.
- Chưa có full proof tại đây cho: geometric separator của Drawing; query bound trong Equalmex; toàn bộ counting của Splits; cận tối ưu clique seed trong Flower Cutting; normal form/cutoff và exact construction của VIM. Các mục đó vẫn có nhận xét đáng học, nhưng không trình bày phần chưa chắc như định lý đã chứng minh.
- Không thêm mục nào vào notebook/PDF trong đợt này.
