# Transformation: nhật ký đọc theo section

Mục tiêu: nhận ra mô hình ẩn trong đề, dựng phép biến đổi, kiểm tra vì sao tương đương, rồi chọn thuật toán. Notebook giữ bản tra nhanh; file này giữ giải thích và bài tập.

## Đợt 1 — CPH

Nguồn: [Competitive Programmer’s Handbook](CPH.pdf), bản Draft August 19, 2019. Số trang dưới đây là số in trong sách; trang PDF lệch +10. Đã đọc bốn section dưới đây, chưa khảo sát toàn bộ sách hay các PDF khác trong `material`.

### §20.3 — Maximum matchings, trang 187–190

**Tóm tắt.** Matching ghép các cặp sao cho mỗi đỉnh dùng tối đa một lần. Với đồ thị hai phía, dựng flow `s → L → R → t`, mọi capacity bằng 1. Hall mô tả điều kiện ghép hết phía trái: mọi tập X phải có ít nhất |X| láng giềng. Kőnig cho minimum vertex cover bằng maximum matching; phần bù của cover là maximum independent set.

**Transformation.** “Giữ nhiều đối tượng nhất mà không có cặp xung đột” → đỉnh là đối tượng, cạnh là xung đột → kiểm tra hai phía → đáp án `n − matching`. “Xóa ít đối tượng nhất để hết xung đột” → minimum vertex cover → đáp án `matching`. Điều kiện hai phía là bắt buộc cho các công thức dùng matching này.

**Vì sao.** Tập được giữ độc lập khi và chỉ khi tập bị xóa chạm mọi cạnh. Kőnig biến bài toán tìm tập bị xóa thành matching. Muốn lấy nghiệm: từ các đỉnh trái chưa ghép, đi cạnh chưa ghép sang phải và cạnh đã ghép về trái; gọi tập đến được là Z. Cover là `(L \ Z) ∪ (R ∩ Z)`.

**Bài tự luyện (biên soạn từ phép biến đổi, không phải bài trích nguyên văn).** Cho bàn cờ có ô cấm; đặt nhiều quân mã nhất để không quân nào ăn nhau. Dựng cạnh giữa hai ô được phép nếu mã đi được giữa chúng. Mã luôn đổi màu bàn cờ nên đồ thị hai phía. Đáp án là số ô được phép trừ matching. Thử bàn 3×3 không ô cấm: đáp án 5; ô giữa là đỉnh cô lập và vẫn được tính.

### §20.4 — Path covers, trang 190–192

**Tóm tắt.** Phủ đỉnh DAG bằng ít đường đi nhất có hai phiên bản: mỗi đỉnh thuộc đúng một đường, hoặc đỉnh được dùng trong nhiều đường. Cả hai dùng matching giữa hai bản sao của tập đỉnh; phiên bản đầu dùng cạnh gốc, phiên bản sau dùng quan hệ đến được.

**Transformation.** “Chia công việc thành ít dây chuyền nhất” → DAG của các chuyển tiếp hợp lệ → matching giữa bản trái/phải. Một đỉnh có tối đa một công việc kế tiếp và một công việc trước đó. Mỗi cạnh matching giảm số dây chuyền một đơn vị, nên đáp án `n − matching`. DAG bảo đảm các cạnh đã chọn không tạo chu trình.

**Bẫy.** Không tự ý thêm transitive closure vào bài yêu cầu đường đi không chung đỉnh. Dilworth nói về chain trong quan hệ thứ tự; cần cạnh cho mọi cặp so sánh được. Chain qua cạnh reachability có thể mở rộng thành đường đi dùng chung đỉnh trong DAG gốc.

**Bài tự luyện.** DAG có cạnh `a→c, b→c, c→d, c→e`. Tìm số đường phủ nhỏ nhất với hai quy định. Không chung đỉnh: matching cạnh gốc có size 2, đáp án 3. Cho phép chung đỉnh: hai đường `a→c→d` và `b→c→e`, đáp án 2; matching trên reachability có size 3. Đây là ví dụ để nhớ vì sao hai cách dựng khác nhau.

### §20.2 — Disjoint paths, trang 186–187

**Tóm tắt.** Nhiều tuyến không chung cạnh → max-flow với capacity cạnh bằng 1. Nhiều tuyến không chung đỉnh nội bộ → tách mỗi đỉnh thành đầu vào/đầu ra, giới hạn flow qua cạnh nối chúng.

**Transformation.** “Mỗi trạm/ô chỉ phục vụ c_v lượt” → `v_in → v_out` capacity `c_v`; cạnh gốc `u→v` thành `u_out→v_in`. Mọi lượt qua trạm phải qua cạnh nội bộ, nên giới hạn tài nguyên ở đỉnh trở thành giới hạn ở cạnh. Với các tuyến không chung đỉnh nội bộ, dùng capacity 1 cho các đỉnh khác s,t; có thể giữ s,t nguyên. Giữ capacity cạnh gốc bằng 1 để một cạnh trực tiếp s→t không bị đếm nhiều lần.

**Bài tự luyện.** Trong DAG có `s→a, s→b, a→c, b→c, c→d, c→e, d→t, e→t`, hỏi số tuyến không chung cạnh và số tuyến không chung đỉnh nội bộ. Đáp án lần lượt 2 và 1. Đỉnh c là nút thắt dù có hai nhánh vào và hai nhánh ra. Tiếp theo thử c có capacity 2, các đỉnh nội bộ khác capacity 1: đáp án thành 2.

### §19.3 — De Bruijn sequences, trang 178

**Tóm tắt.** Chuỗi chứa mỗi từ dài n trên bảng chữ cái k ký tự đúng một lần có thể dựng bằng Euler. Đỉnh là từ dài n−1; từ dài n là cạnh nối prefix với suffix. In đỉnh bắt đầu rồi ký tự cuối của từng cạnh.

**Transformation.** Khi đề yêu cầu “mỗi đối tượng xuất hiện một lần”, thử đặt đối tượng thành cạnh thay vì đỉnh. Chồng lấp n−1 ký tự trở thành điều kiện hai cạnh liên tiếp nối được nhau. Bài sắp xếp các từ thành chuỗi chuyển sang Euler trên đồ thị có hướng.

**Vì sao.** Mỗi cạnh được dùng một lần tương ứng một cửa sổ dài n. Có k^n cửa sổ khác nhau nên chuỗi tuyến tính cần ít nhất k^n+n−1 ký tự. Đồ thị đầy đủ các từ cân bằng bậc và liên thông, có Euler circuit đạt đúng cận này. Với tập từ bất kỳ, kiểm tra liên thông yếu của các đỉnh có cạnh và bậc: mọi đỉnh cân bằng cho circuit; trail mở có một đỉnh out−in=1, một đỉnh in−out=1, các đỉnh khác cân bằng. Giữ cạnh song song nếu từ lặp; n=1 có một đỉnh là chuỗi rỗng.

**Bài tự luyện.** (1) Dựng chuỗi nhị phân ngắn nhất chứa mọi từ dài 3: `0001011100`, dài 10, có đủ 8 cửa sổ khác nhau. (2) Cho multiset `ab, bc, ca, ab`; ghép với overlap 1 để dùng mỗi từ đúng một lần: `abcab`. Cạnh ab phải tồn tại hai lần; out−in của a là 1, của b là −1.

## Đợt 2 — Các tài liệu ngoài CPH

Đọc theo từng mục bên dưới, không đọc trọn các sách. Ví dụ mang tên bài gốc là bài luyện từ tài liệu; ví dụ số nhỏ ghi “tự luyện” là tự biên soạn. Các kết luận và chứng minh dưới đây là diễn giải, không phải trích nguyên văn.

### CP3 §4.4.3 — Full Tank?, trang sách 150 / PDF 175

**Tóm tắt.** Giá xăng thay đổi theo thành phố, bình có dung tích hữu hạn. Chi phí đến một thành phố không đủ quyết định chi phí tương lai: lượng xăng còn lại cũng quan trọng.

**Transformation.** Đồ thị vị trí → đồ thị trạng thái tích `(thành phố, xăng)`. Mua một đơn vị xăng tạo cạnh giá `p[v]`; đi đường dài d tạo cạnh giá 0, giảm xăng d. Mọi lịch trình mua/đi hợp lệ tạo đường đi trên đồ thị mới và ngược lại. Có `V(C+1)` trạng thái; cạnh đi đường và mua xăng có tổng số `O((V+E)C)`. Dijkstra áp dụng vì giá không âm.

**Nhận diện.** Hai người cùng vị trí nhưng có các lựa chọn tương lai khác nhau → cần thêm trạng thái. Các biến thể: hướng đi cuối, vé giảm giá đã dùng chưa, tập chìa khóa. Không lưu toàn bộ lịch sử; chỉ lưu thông tin đủ xác định bước tiếp theo.

**Bài gốc.** UVa 11367 — Full Tank?. **Tự luyện:** đường s–a dài 2, a–t dài 2; giá xăng s=5, a=1; bình C=4, ban đầu rỗng. Tối ưu mua 2 tại s, 2 tại a, tổng 12, thay vì mua 4 tại s mất 20. Kiểm tra với C=1: không thể đi. Bình cho phép mức xăng từ 0 đến C, nên có C+1 mức.

### CP3 §4.6.4 — Flow Graph Modeling, trang sách 166 / PDF 191

**Tóm tắt.** Software Allocation phân ứng dụng cho máy tương thích, mỗi ứng dụng có nhu cầu nhiều đơn vị còn mỗi máy chỉ chạy một đơn vị.

**Transformation.** `s→ứng dụng` capacity bằng nhu cầu, `ứng dụng→máy tương thích` capacity 1, `máy→t` capacity 1. Khả thi iff flow bằng tổng nhu cầu; tính nguyên của flow cho phép khôi phục phân công. Đây là matching có capacity, không cần tạo một đỉnh riêng cho từng bản ứng dụng.

**Bài gốc.** UVa 259 — Software Allocation. **Tự luyện:** A cần 2 máy, dùng được {0,1}; B cần 1 máy, dùng được {1,2}. Có nghiệm A→0,1 và B→2; nếu B chỉ dùng được {1} thì vô nghiệm. Đã có các mục flow/matching trong notebook nên mục này lưu ở nhật ký, tránh thêm một mục gần trùng.

### Looking for a Challenge 2 — A: Arithmetic Rectangle, trang sách 3–8 / PDF 17–22

**Tóm tắt từng phần.** “Air crashes” tìm phần tử nhỏ hơn gần nhất bằng các liên kết bỏ qua phần tử không còn hữu ích, tương đương monotonic stack. “Plot” chuyển hình chữ nhật toàn 1 thành histogram độ dài dãy 1 theo cột, rồi mở rộng mỗi cột đến hai cột nhỏ hơn gần nhất. “Arithmetic rectangle” tạo bảng đánh dấu cửa sổ 3×3 hợp lệ để dùng lại lời giải Plot.

**Transformation.** Cấp số cộng ⇔ sai phân bậc hai bằng 0 trên mọi bộ ba liên tiếp. Đánh dấu tâm cửa sổ 3×3 nếu cả ba hàng và cả ba cột đều là cấp số cộng. Với H,W≥3, hình chữ nhật hợp lệ iff mọi tâm trong phần bên trong đều được đánh dấu: các cửa sổ phủ toàn bộ các bộ ba ngang/dọc của hình chữ nhật.

Nếu phần tâm có kích thước h×w thì diện tích gốc là `(h+2)(w+2)`. Histogram vẫn dùng được vì hàm diện tích tăng theo cả hai chiều: với mỗi bar, mở rộng tối đa trong phạm vi các bar không thấp hơn nó. Phải lấy max theo **diện tích mới** trên mọi candidate. Không chỉ lấy hình có hw lớn nhất rồi cộng viền.

**Bẫy và trường hợp nhỏ.** 4×4 có diện tích tâm 16, lớn hơn 1×15 có diện tích tâm 15, nhưng diện tích gốc là 36 và 51. Các hình có một cạnh dài 1 hoặc 2 không có vùng tâm, phải xử lý riêng: một hàng/cột dùng run có sai phân không đổi; hai hàng dùng các run mà bộ ba trên cả hai hàng đều hợp lệ, tương tự hai cột. Vì chỉ có tối đa hai phần tử theo chiều hẹp nên điều kiện cấp số cộng ở chiều đó tự thỏa. Tổng O(nm).

**Bài gốc.** AMPPZ 2011 — Arithmetic Rectangle (mã ary). **Tự luyện:** chứng minh phép đánh dấu rồi kiểm tra bảng 2×3 `0 1 2 / 1 2 3` phải trả 6; đây là test bắt lỗi bỏ quên hình hẹp.

### Programming Challenges §9.6.3 — The Tourist Guide, trang sách 206–207 / PDF 226–227; §9.7 hint, PDF 236

**Tóm tắt.** Mỗi cạnh vô hướng có sức chứa xe. Dẫn T khách dọc một tuyến; hướng dẫn viên chiếm một chỗ ở mỗi chuyến. Hint trong sách gợi ý chuyển sang kiểm tra liên thông.

**Transformation.** Sức chứa tuyến là minimum sức chứa cạnh. Tối thiểu số chuyến ⇔ tối đa nút thắt `B=max_P min_{e∈P} c_e`. Tuyến có B≥X iff s,t liên thông sau khi bỏ cạnh capacity<X. Duyệt cạnh giảm dần và DSU: capacity tại thời điểm s,t lần đầu liên thông chính là B. Tương đương lấy minimum cạnh trên đường s–t trong maximum spanning tree. Các công thức/thuật toán này là triển khai của gợi ý liên thông, được kiểm tra bằng lập luận ngưỡng.

**Bài gốc.** UVa 10099 — The Tourist Guide. Số chuyến `ceil(T/(B−1))`, không phải `ceil(T/B)`. Sample sách có tuyến 1–2–4–7, B=25, T=99 nên cần 5 chuyến. Điều kiện: có đường đi, s≠t và B>1; trường hợp không có khách trả 0. Không nhầm maximum spanning tree với minimum spanning tree.

### CRRC 2025 — C: «И снова лабиринт», PDF 1–2

**Tóm tắt.** Editorial dùng hai BFS để lấy các ô trên ít nhất một đường ngắn nhất, rồi xét các điểm khớp; cũng xét đồ thị gốc để phân biệt xóa ô làm đường dài hơn với làm mất đường hoàn toàn.

**Transformation.** Câu hỏi về tất cả nghiệm tối ưu → lọc đồ thị của các đường ngắn nhất. Giữ v khi `ds[v]+dt[v]=D`. Mình dùng phiên bản DAG theo lớp: giữ cạnh định hướng u→v khi `ds[v]=ds[u]+1`. Với cạnh đơn vị, mỗi đường ngắn nhất đi qua đúng một đỉnh mỗi lớp; do đó v thuộc mọi đường ngắn nhất iff lớp của nó chỉ có một đỉnh. Nếu một lớp có nhiều đỉnh, mỗi đỉnh khác đều có đường ngắn nhất đi qua nó, cung cấp đường tránh v.

**Phân biệt hai kết quả.** Với đỉnh nội bộ bắt buộc, xóa nó luôn phá khoảng cách tối ưu cũ. Nếu v không tách s,t trong đồ thị gốc thì còn đường vòng dài hơn; nếu có thì mất mọi đường. Đừng dùng mọi điểm khớp của đồ thị gốc: cần điểm khớp **tách s,t**. Root DFS tại s; đỉnh v≠s tách s,t nếu có con c chứa t trong subtree và `low[c]≥tin[v]`.

**Bài tự luyện.** Đồ thị vô hướng có hai nhánh ngắn `s–a–c–t`, `s–b–c–t` và đường vòng `s–x–y–z–t`. Chỉ c bắt buộc trong các đỉnh nội bộ của đường ngắn nhất; xóa c làm khoảng cách tăng từ 3 lên 4. Bỏ đường vòng: xóa c làm mất kết nối. Quy tắc singleton layer ở đây chỉ áp dụng đồ thị không trọng số/cạnh đơn vị; với trọng số khác nhau, dùng tight-edge graph và dominator hoặc phân tích phù hợp.

### CRRC 2025 — D: «Колеблющаяся подпоследовательность», PDF 2

**Tóm tắt.** Khi dãy đang đi xuống, gặp giá trị còn nhỏ hơn thì thay endpoint thay vì thêm phần tử; endpoint nhỏ hơn vẫn cho phép mọi lần nối lên mà endpoint cũ cho phép. Chiều đi lên đối xứng.

**Transformation.** DP chọn subsequence → nén các đoạn cùng chiều thành endpoint tốt nhất. Bỏ hiệu 0, đếm các run dấu +/− trong hiệu của phần tử kề nhau; đáp án 1 + số run. Dãy rỗng có đáp án 0, dãy toàn bằng nhau có đáp án 1. Đây là dao động nghiêm ngặt, không lấy hiệu 0 làm một lần đổi chiều.

**Bài tự luyện.** `1,2,2,5,3,3,4` có dấu sau khi bỏ 0 là `+,+,−,+`, tức 3 run; đáp án 4, lấy `1,5,3,4`. Giải thích vì sao `1,2,5` chỉ đóng góp hai endpoint thay vì ba.

### Astana team notebook §7.9 — About Graph Minimum Cut, PDF 25

Nguồn thực tế: **Team Note of PS akgwi**, Soongsil University, dành cho World Finals Astana; file `240919-icpc-world-finals-astana.pdf` không phải đề/editorial World Finals.

**Tóm tắt.** Mục này liệt kê cách mô hình hóa chi phí gán nhãn boolean và implication thành cut. Các chi phí đơn đỉnh, phạt true→false và phạt hai nhãn khác nhau đều có mẫu cạnh trực tiếp.

**Transformation.** Phía nguồn=true, phía đích=false. Cạnh chỉ tính vào cut khi đi từ phía nguồn sang phía đích. Vì vậy: phạt i=true dùng i→t; phạt i=false dùng s→i; phạt `(i=true,j=false)` dùng i→j; phạt khác nhãn w dùng cả i→j và j→i capacity w. Không cộng 2w: trong một cut chỉ một trong hai cạnh đi đúng hướng. Implication i⇒j dùng i→j capacity INF lớn hơn mọi chi phí hữu hạn khả thi.

**Điều kiện.** Capacity không âm. Bảng chi phí cặp nhãn tổng quát chỉ biểu diễn trực tiếp bằng mẫu graph cut khi submodular: `E00+E11≤E01+E10` (có thể cần tách hằng số và unary). Không suy ra mọi bài boolean optimization đều là min-cut.

**Bài tự luyện.** Hai biến x,y: true tốn lần lượt 1,4; false tốn 3,0; khác nhãn tốn 5. Cấu hình FF,TF,FT,TT có chi phí 3,6,12,5; tối ưu FF=3. Dựng mạng theo mẫu và đối chiếu bốn cách cắt. Thêm implication x⇒y sẽ cấm TF.

### Winning Ways, Vol. 1, Ch.2 — The Negative of a Game; Cancelling a Game with its Negative, trang sách 33–34 / PDF 53–54

File `game_theory_notebook.pdf` là bản scan **Winning Ways for Your Mathematical Plays, Volume 1, Second Edition**, không có text layer dùng được ở các trang đã kiểm tra; đã đọc hình trang trực tiếp.

**Tóm tắt.** Game đối dấu −G đổi vai trò Left/Right ở mọi vị trí. Trong tổng G+(−G), người đi sau đáp lại đúng bước tương ứng ở thành phần kia để khôi phục một cặp đối dấu. Với impartial game, G là đối dấu của chính nó.

**Transformation.** Tìm vị trí thắng/thua trên trạng thái lớn → ghép các thành phần độc lập thành cặp triệt tiêu. Không cần tính hết game tree nếu có ánh xạ đối xứng bảo toàn nước đáp. Sau nước G→H, đáp −G→−H; trạng thái trở lại H+(−H). Vì game hữu hạn, người thứ hai luôn có nước đáp cuối cùng.

**Điều kiện.** Normal play: người hết nước thua; mỗi lượt đi trong đúng một thành phần; các thành phần độc lập; không có chuỗi chơi vô hạn. Tài nguyên dùng chung hoặc misère làm lập luận này có thể sai. Hai game cùng trạng thái thắng/thua chưa chắc thay thế được nhau trong một tổng.

**Bài tự luyện.** Hai đống bằng nhau n>0; mỗi lượt lấy một số dương tùy ý từ một đống; ai không đi được thua. Người sau lấy đúng số đó từ đống kia. Với ba đống n,n,m, cặp n,n triệt tiêu, còn game một đống m; nếu m>0, người trước lấy hết đống m rồi dùng chiến thuật đáp đối xứng. Đây là ví dụ tự luyện của phép triệt tiêu, không phải đề trích từ sách.

## Phạm vi đã đọc và cách đọc tiếp

Đã khảo sát ít nhất một mục cụ thể trong **tất cả bảy PDF** hiện có: CPH và sáu tài liệu ngoài CPH. Cập nhật 2026-10-07: đã đọc đủ **44/44 đề Looking for a Challenge 2**, giải bằng lập luận và đánh giá từng transformation trong [LFAC2_TRANSFORMATIONS.md](LFAC2_TRANSFORMATIONS.md); bản tiếng Anh thiếu 33 editorials nên đã dùng bản gốc tác giả để đối chiếu các mục khó. Các tài liệu khác vẫn mới khảo sát từng mục, chưa đọc trọn. Mỗi mục trên có nguồn/trang, tóm tắt, phép biến đổi, điều kiện và bài tập; các phần còn lại chưa được đánh giá. CP3 Software Allocation được lưu để luyện, còn bảy phép biến đổi mới còn lại được thêm vào notebook.

Khi đọc tiếp: chọn một section/bài, tóm tắt ngay, kiểm tra điều kiện tương đương, đối chiếu phần Transformations hiện có rồi mới bổ sung.

## LFAC2 — khảo sát toàn bộ problem set (2026-10-07)

Không chỉ lấy Arithmetic Rectangle: đọc lần lượt 2011A–K, 2012A–K, 2013A–K và 2014A–K. File khảo sát có đủ đề rút gọn, lời giải/lập luận, complexity, transformation trước→sau, đánh giá /5, điều kiện và bài luyện cho từng bài. Các cue cuối cùng đưa vào `main.tex` được liệt kê trong bảng quyết định ở cuối khảo sát. [lfac2_checks.py](lfac2_checks.py) đối chiếu các ý dễ sai với brute/mô phỏng nhỏ; không phải bộ 44 submissions AC.
