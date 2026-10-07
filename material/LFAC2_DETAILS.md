# Looking for a Challenge 2 — lời giải chi tiết

Bản đọc nhanh: [LFAC2_TRANSFORMATIONS.md](LFAC2_TRANSFORMATIONS.md).

Nguồn đề chính: [Looking for a Challenge 2](Lookingforachallenge2.pdf), 44 bài AMPPZ 2011–2014. Bản tiếng Anh có 11 lời giải năm 2011; 33 mục còn lại ghi “Translation in progress”. Đã đối chiếu các mục khó bằng [bản gốc tiếng Ba Lan trên trang tác giả](https://www.mimuw.edu.pl/~idziaszek/algonotes/looking-for-a-challenge-2-pl.pdf), đặc biệt 2012A/E/F/K, 2013A/C/F/G/H/I và 2014B/C/E/F/G/H/J. Số trang “PDF” bên dưới là **thứ tự trang file tiếng Anh**, không phải số in ở chân trang. Đọc lần lượt từng bài; lời giải dưới đây được tái dựng từ đề và đối chiếu editorial, kèm lập luận kiểm tra. Không coi việc đọc editorial là đã tự phát minh lời giải, cũng không coi giải thích thuật toán là đã có code AC.

**Transformation** là bước đổi cách biểu diễn/nhìn bài toán để mở ra một thuật toán: ghi rõ *trước → sau*, điều kiện và lý do tương đương. Điểm **hay /5** là đánh giá chủ quan về độ bất ngờ, khả năng tái sử dụng và tính cô đọng trong notebook; không phải số sao độ khó của sách. 5: đáng giữ, cấu trúc rất mạnh; 4: hữu ích, có điều kiện rõ; 3: chủ yếu tinh chỉnh một mô hình quen thuộc; 2: mẹo khá riêng; 1: hầu như chỉ là triển khai thuật toán cơ bản. Trong từng bài, “giữ” là đánh giá **đáng lưu ý**, không có nghĩa mọi bài ấy đều được chép vào notebook. Bảng cuối ghi lựa chọn thực tế: 21 cue mới, ngoài Arithmetic Rectangle đã có; các ý còn lại vẫn được giải và đánh giá ở đây.

## 2011A — Arithmetic Rectangle

**Nguồn:** PDF 17–22. **Đề:** tìm hình chữ nhật lớn nhất mà từng hàng và từng cột là cấp số cộng.

**Giải.** Một dãy là cấp số cộng iff mọi bộ ba liên tiếp có sai phân bậc hai bằng 0. Đánh dấu tâm của các cửa sổ 3×3 thỏa cả ngang lẫn dọc. Với H,W≥3, hình chữ nhật hợp lệ iff bảng tâm (H−2)×(W−2) toàn 1: các cửa sổ 3×3 phủ hết mọi điều kiện bộ ba. Chuyển bảng 1 thành histogram theo từng hàng; mỗi bar mở rộng tới các bar nhỏ hơn gần nhất bằng monotonic stack. Candidate tâm h×w có giá trị **(h+2)(w+2)**. Xử lý riêng cạnh dài 1 hoặc 2 bằng run có sai phân ngang/dọc không đổi. Tổng O(nm), có thể xử lý histogram từng hàng.

**Transformation:** điều kiện đại số trên mọi hàng/cột → kiểm tra cửa sổ cục bộ → maximal rectangle → histogram → nearest smaller. **Hay: 5/5, giữ.** Có cả chuỗi giảm bài toán và cảnh báo đổi objective: tâm 4×4 lớn hơn 1×15 nhưng sau thêm viền 36<51. Không được chỉ lấy hình tâm có diện tích lớn nhất. **Luyện:** dựng lời giải và thử bảng 2×3 `0 1 2 / 1 2 3`, đáp án 6; xem chứng minh vùng tâm ở nhật ký đọc.

## 2011B — Bytean Road Race

**Nguồn:** PDF 23–29. **Đề:** đường phố phẳng, chỉ đi đông/nam; mọi đỉnh nằm trên một tuyến s→t. Với từng cặp p,q, có tuyến s→t qua cả hai không?

**Giải.** Cần p đến được q hoặc ngược lại. Xoay trục để mọi cạnh hướng lên. Từ p, đường luôn chọn nhánh trái Lp và luôn chọn nhánh phải Rp bao toàn bộ miền có thể đi qua. Với q cao hơn p, p→q iff tại độ cao q, Lp nằm không bên phải q và Rp nằm không bên trái q. Chiều thuận do tính phẳng; chiều ngược: đường s→q phải giao một biên, ghép đoạn p→điểm giao với đoạn điểm giao→q. Binary lifting trên successor trái/phải cho O((n+k)log n).

Có lời giải O(n+m+k): chọn successor trái của mỗi đỉnh tạo cây TL gốc t, tương tự TR. DFS hai cây, giữ thứ tự con theo vị trí hình học. Quan hệ tổ tiên và trái/phải của hai subtree xác định biên tương đối mà không cần giao với đường ngang. Với p thấp hơn q: nếu q là tổ tiên p trong một cây thì đã có đường; nếu không, p phải ở trái q trong TL và phải q trong TR. Euler enter/exit cho các phép thử O(1).

**Transformation:** nhiều truy vấn reachability → hai đường biên cực trị → hai cây có thứ tự. **Hay: 5/5, giữ với điều kiện.** Rất mạnh nhưng dựa vào embedding phẳng, tính đơn điệu và tất cả đỉnh đều s-reachable/t-co-reachable; không phải reachability DAG tổng quát. **Luyện:** bỏ giả thiết s đến mọi đỉnh rồi tìm ví dụ q nằm giữa hai biên nhưng không đến được từ p. Truy vấn cặp vô hướng phải chọn chiều theo độ cao trước.

## 2011C — Will It Stop?

**Nguồn:** PDF 30–32. **Đề:** n chẵn thì chia 2, n lẻ thì thay bằng 3n+3; hỏi có về 1 không.

**Giải.** Bỏ các thừa số 2 đầu tiên. Nếu còn 1 thì kết thúc. Nếu còn số lẻ >1, bước tiếp theo tạo bội của 3. Tập các bội dương của 3 đóng dưới cả hai phép: nếu bội của 3 chẵn thì chia 2 vẫn là bội của 3; 3n+3 luôn là bội của 3. Vì 1 không thuộc tập đó, không thể kết thúc. Đáp án iff n là lũy thừa 2: `n>0 && (n&(n-1))==0`, O(1) trên kiểu máy; không mô phỏng số có thể vượt 64 bit.

**Transformation:** mô phỏng không có cận dừng → tập trạng thái bất biến không chứa đích. **Hay: 4/5, giữ mẫu nhận diện.** “Tìm tập đóng sau một sự kiện không đảo ngược” áp dụng rộng; phép thử power-of-two riêng không cần mục mới. **Luyện:** giải thích vì sao chứng minh mất hiệu lực nếu thay 3n+3 bằng 3n+1; không suy rộng kết luận sang Collatz.

## 2011D — Ants

**Nguồn:** PDF 33–36. **Đề:** hai kiến đi quanh contour cây, tốc độ lên/xuống khác nhau, gặp nhau thì quay đầu; input rất lớn so với RAM. Tìm lần gặp thứ hai.

**Giải.** Không dựng cây: tại điểm trên contour chỉ cần a=tổng độ dài đã đi từ đầu và k=độ cao. Độ dài đi lên/xuống là (a+k)/2 và (a−k)/2. Vì vậy thời gian với giá lên tu, xuống td là `T(a,k)=(a+k)tu/2+(a−k)td/2`. Lần gặp đầu thỏa `T(a1,k1;2,1)=T(2n−a1,k1;1,1/2)`, tức `9a1+k1=6n`. Trên cạnh có dấu b=±1, đặt a1=a+ε,k1=k+bε; ε=(6n−9a−k)/(9+b). Đọc stream cho đến cạnh chứa ε∈[0,1).

Sau quay đầu, kiến trái mất t1−k1 để về gốc; kiến phải mất t1−k1/2, nên trái về trước dù đi chậm hơn. Tiếp tục cùng contour (giờ mô phỏng kiến phải): điểm gặp tiếp theo thỏa `9a2−k2=12n+9a1−k1`. Trên cạnh mới (a0,k0), ε2=[12n−9(a0−a1)+(k0−k1)]/(9−b0). Tổng thời gian là `[3(a1+a2)+k1+k2]/4`. Dùng phân số chính xác hoặc fixed-point sau khi chứng minh mẫu số; O(n), RAM O(1), không đọc ngược stream.

**Transformation:** động học trên cây → contour 1D + độ cao → phương trình affine theo từng cạnh. **Hay: 4/5, giữ ý “số lên/xuống từ tổng và hiệu”.** Bài cụ thể khá riêng; không chép nguyên cả công thức kiến vào notebook. **Luyện:** tự suy ra vì sao kiến chậm về gốc trước; kiểm tra sample bằng phân số, đáp án 282/5.

## 2011E — Gophers

**Nguồn:** PDF 37–39. **Đề:** các điểm cố định bị phủ bởi các đoạn [x−l,x+l] cùng độ dài; di chuyển một đoạn, hỏi số điểm trong hợp.

**Giải.** Đặt các tâm trong ordered set, các điểm trong sorted array. Khi thêm/xóa tâm x với hai hàng xóm p<x<q, phần chỉ đoạn x phủ là `[max(x−l,p+l+1), min(x+l,q−l−1)]` trên tọa độ nguyên. Các tâm xa hơn không thể che thêm phần này vì endpoint của các đoạn tăng theo tâm. Đếm điểm trong khoảng bằng hai binary search; thêm thì cộng, xóa thì trừ. Di chuyển=xóa+thêm. O(n+m+(m+d)log m+d log n), hoặc khởi tạo bằng quét sau khi dữ liệu đã được sắp; RAM O(n+m).

**Transformation:** dynamic interval union coverage → phần đóng góp riêng phụ thuộc predecessor/successor. **Hay: 5/5, giữ.** Equal-length/proper intervals biến cấu trúc range-update phức tạp thành local update. Không dùng công thức này cho đoạn dài tùy ý; khoảng rỗng góp 0, endpoint ±1 chỉ dành cho tọa độ nguyên. **Luyện:** chứng minh chỉ hai hàng xóm đủ và dựng phản ví dụ khi tâm xa có đoạn dài hơn.

## 2011F — Laundry

**Nguồn:** PDF 40–43. **Đề:** người i cần 2di kẹp cho tất và 3di cho áo; mỗi loại cùng màu, màu không được dùng giữa hai người; ít màu nhất.

**Giải.** Sắp di giảm dần. Với người hiện tại, lấy màu nhỏ nhất có capacity≥5di nếu có; nếu không, lấy màu nhỏ nhất ≥3di rồi màu khác nhỏ nhất ≥2di; thiếu một màu thì vô nghiệm. Dùng multiset (capacity có thể trùng), O(n log n+(n+k)log k). Chứng minh bằng đưa nghiệm OPT về cùng lựa chọn greedy: người lớn nhất còn lại dùng được capacity greedy; đổi một màu lớn hơn sang người về sau không làm người đó thiếu. Nếu OPT dùng hai màu còn greedy dùng một, màu đơn ấy đang rảnh thì giảm số màu; nếu ở người nhỏ hơn, chuyển cặp 2di/3di sang người đó, số màu không tăng. Nhu cầu cùng tỉ lệ là chìa khóa.

**Transformation:** phân phối tài nguyên → xử lý yêu cầu khó trước + smallest adequate capacity + exchange giữa một gói/cặp gói. **Hay: 3/5, không thêm mục riêng.** Chứng minh exchange tốt để luyện, nhưng không được suy thành greedy chung cho bin packing hoặc nhu cầu hai phần tùy ý. **Luyện:** viết exchange riêng cho tình huống màu greedy đang cấp cho tất/áo/mọi quần áo của người sau; kết quả là số **màu**, không phải tổng số kẹp (bản tiếng Anh có chỗ dùng từ thiếu chính xác).

## 2011G — Bits Generator

**Nguồn:** PDF 44–49. **Đề:** chuyển seed z theo hàm f cố định, xuất một bit sau mỗi lần chuyển; đếm seed tạo pattern n bit.

**Giải.** Dựng functional graph m đỉnh, cạnh z→f(z), nhãn đỉnh là bit **của f(z)**. Doubling: `jump[j][v]=f^(2^j)(v)` và rank[j][v] nhận diện chính xác 2^j bit bắt đầu ở v. Rank mới là rank nén của cặp `(rank[j−1][v],rank[j−1][jump[j−1][v]])`, radix sort để O(m) mỗi mức. Thêm chuỗi pattern như một đường đi riêng vào graph. Với L=2^floor(log2 n), so sánh cặp rank của prefix L và suffix L (offset n−L); hai đoạn phủ toàn pattern. Đếm seed có cùng cặp với đầu đường pattern. Tính offset jump từ các bit của n−L ngay trong quá trình doubling; chỉ giữ hai mức: O((m+n)log n) thời gian, O(m+n) RAM.

Editorial còn có O(m+n): functional graph=các cycle có cây đổ vào; đảo pattern, chạy **automaton KMP với transition đã dựng** từ cycle xuống các cây. Khởi tạo trạng thái ở cycle bằng tính tuần hoàn của prefix pattern và Z-array, tránh lặp n ký tự riêng cho mỗi cycle. KMP thường trên từng nhánh không tự có tổng O(m+n), vì cùng failure walk có thể bị lặp ở nhiều con.

**Transformation:** thử từng seed → so sánh các chuỗi xác định trên functional graph; hoặc đảo hướng pattern để đi từ gốc xuống cây. **Hay: 5/5, giữ doubling và bẫy KMP cây.** Không dùng hash như thể chắc chắn đúng; rank nén cặp là deterministic. **Luyện:** n lớn hơn độ dài cycle, và cây nhiều lá tạo cùng failure chain; so sánh với mô phỏng seed nhỏ.

## 2011H — Afternoon Tea

**Nguồn:** PDF 50–52. **Đề:** uống nửa cốc rồi thêm trà/sữa theo một chuỗi; ban đầu tỉ lệ 1:1. Hỏi đã uống loại nào nhiều hơn.

**Giải.** Bỏ lần thêm cuối vì nó không được uống. Lượng đã uống=tổng đã thêm−lượng còn. Nếu số H/M ở n−1 lần thêm còn lại khác nhau, tổng thêm chênh ít nhất nửa cốc; phần còn chỉ nửa cốc, và chứa lượng dương cả hai loại, nên không thể đảo dấu. Nếu số lần bằng nhau, loại còn nhiều hơn là loại thêm ở lần n−1: nó chiếm một nửa phần còn, cộng thêm dư ban đầu. Vì vậy đã uống nhiều hơn loại **đối diện**. n=1 trả HM. Một lượt O(n), O(1) RAM, không cần phân số khổng lồ.

**Transformation:** tính tổng quá trình → bảo toàn lượng (input−residue) → so sánh bằng cận phần dư; khi hòa thì dùng đóng góp lớn nhất. **Hay: 5/5, giữ.** Rộng hơn bài pha cốc: một số nguyên lớn trội một correction bị chặn; chỉ xử lý correction khi phần chính hòa. **Luyện:** `HMH` bỏ H cuối → tổng thêm hòa, lần trước thêm M → đáp án H; đổi ký tự cuối không đổi đáp án.

## 2011I — Intelligence Quotient

**Nguồn:** PDF 53–58. **Đề:** hai nhóm đều quen nhau nội bộ; chọn nhóm tất cả quen nhau, tổng trọng số lớn nhất.

**Giải.** Dựng đồ thị xung đột chỉ gồm các cặp **không quen** giữa hai phía. Tập chọn là independent set; phần bị bỏ là vertex cover có trọng số nhỏ nhất. Dựng flow: s→L capacity wL, R→t capacity wR, mỗi cạnh xung đột L→R capacity INF>tổng trọng số. Cut hữu hạn buộc ít nhất một đầu cạnh xung đột bị loại; cost đúng bằng tổng trọng số bị loại. Đáp án Σw−mincut. Nếu S là các đỉnh reachable từ s trong residual graph, chọn `(L∩S) ∪ (R\S)`; đó là phần bù của cover. Dùng Dinic, cận tổng quát O(V²E), O(V+E) RAM, trọng số/tổng/capacity dùng 64 bit.

**Transformation:** maximum weighted clique trong co-bipartite graph → complement **hai phía** → weighted vertex cover → min-cut. **Hay: 5/5, giữ.** Không thay min-cut bằng cardinality matching khi trọng số khác nhau. Đây là mở rộng có ích của mục Bipartite Conflicts hiện có. **Luyện:** một xung đột nối trọng số 100 và 1: chỉ phải bỏ 1; matching size 1 không cho biết mất bao nhiêu trọng số.

## 2011J — Cave

**Nguồn:** PDF 59–62. **Đề:** chia cây n đỉnh thành các thành phần liên thông cùng số đỉnh; xuất mọi số nhóm khả thi.

**Giải.** Thử kích thước thành phần k|n. Root cây, với mỗi cạnh lưu size a của subtree phía con. Cạnh được cắt phải có a≡0 mod k. Nếu có đúng n/k−1 cạnh như thế, cắt hết: mỗi thành phần còn lại có kích thước là hiệu của các subtree-multiple, nên dương và chia hết k. Có n/k thành phần và tổng n, nên tất cả đúng k. Chiều cần: trong partition đúng k, cạnh có a chia hết k phải là cạnh ngăn hai nhóm; nếu nằm trong nhóm thì phần nhóm ở phía con có số đỉnh từ 1 đến k−1, mâu thuẫn modulo.

Gom histogram `freq[a]` cho **cạnh**, không tính root. Với từng k|n, `cnt[k]=Σ_j freq[jk]`; kiểm tra cnt[k]=n/k−1, xuất số nhóm n/k. Một DFS O(n), tổng vòng multiples trên các divisor là σ(n)=O(n log log n), RAM O(n). Đây là dạng giản lược trực tiếp của cách editorial dùng histogram gcd(a,n−a); vì k|n nên a divisible k đã đủ. Với input parent ai≤i, cộng size từ n xuống 2, không cần recursion sâu.

**Transformation:** bài phân hoạch cây global → đếm các cạnh có subtree residue bằng 0 → histogram/divisor sieve. **Hay: 5/5, giữ.** Chỉ hợp lệ vì các nhóm liên thông và bằng nhau; không tổng quát sang arbitrary-size partition. **Luyện:** cây sao 4 đỉnh không chia được hai nhóm size 2; đường 4 đỉnh chia được.

## 2011K — Cross Spider

**Nguồn:** PDF 63–65. **Đề:** n điểm 3D có cùng nằm trên một mặt phẳng không.

**Giải.** Với n≤3 trả có. Chọn hai điểm phân biệt p1,p2, tìm pi sao cho N=(p2−p1)×(pi−p1)≠0. Không có pi thì tất cả thẳng hàng, trả có. Nếu có, kiểm tra N·(pj−p1)=0 với mọi j. Ba điểm không thẳng hàng xác định duy nhất mặt phẳng; dot với pháp tuyến bằng 0 là điều kiện thuộc mặt phẳng. O(n), có thể stream và giữ vài điểm. Tích ba hiệu tọa độ không bảo đảm fit int64: dùng int128 **từ trước phép nhân**.

**Transformation:** kiểm tra cấu hình hình học toàn cục → dựng một cơ sở nhỏ + kiểm tra membership bằng determinant. **Hay: 3/5, không thêm riêng.** Mẫu “find independent basis then validate” hữu ích nhưng cross/dot đã có trong notebook. **Luyện:** ba điểm đầu thẳng hàng nhưng điểm thứ tư không nằm trên đường đó; không được lấy pháp tuyến 0 rồi chấp nhận tất cả.

## 2012A — Vending Machine

**Nguồn:** PDF 69–70; bản gốc PL, mục Automat. **Đề:** mua loại i nhận thêm một thanh mỗi loại j<i còn hàng; budget k, giá và tồn kho ≤40, tối đa hóa tổng giá trị nhận.

**Giải.** Hai lần mua khác loại có thể đổi về thứ tự **tăng chỉ số** mà vẫn nhận cùng tổng số thanh, đồng thời không làm mất khả năng mua loại thấp vì được mua trước khi hàng miễn phí vét hết. Tuy thực hiện từ trái sang phải, **lập kế hoạch từ phải sang trái**: nếu đã chọn t lần mua loại cao hơn, chọn thêm x lần mua loại i, với 0≤x≤li. Loại i đóng góp `ci·min(li,t+x)`, tốn `ci·x`; tương lai chỉ cần t+x và tiền đã dùng, không cần vector tồn kho. DP hai lớp theo (t,budget), xét mọi x. Có nghiệm tối ưu dùng ≤L=max li lần mua: trong kế hoạch giảm dần, sau L lần mọi hàng thấp đã được tính hết; các lần mua tiếp chỉ tốn tiền. Vì giá ≤C, cap budget K=min(k,LC). Thời gian O(nKL²), RAM O(KL). Editorial còn tối ưu O(nKL) bằng deque trên các đường chéo budget−t·ci sau khi tách phần prefix reward.

**Transformation:** lịch thực hiện thuận → kế hoạch ngược → ảnh hưởng của cả lịch chỉ còn **số lần mua** → DP nhỏ. **Hay: 5/5, giữ.** Hai thứ tự có vai trò khác nhau. Không được bắt x≤li−t: dù hàng miễn phí sau này đã đủ vét loại i, vẫn có thể mua i *trước* để nhận thêm hàng thấp hơn. **Luyện:** tồn `[4,1,2]`, giá `[4,1,4]`, budget 5: mua loại 2 rồi 3 nhận giá trị 13; lập kế hoạch 3 rồi 2 vẫn phải cho phép x2=1.

## 2012B — Bus Trip

**Nguồn:** PDF 71–72. **Đề:** ghé các điểm có attractiveness tăng nghiêm ngặt; thu phí Manhattan giữa điểm, cộng giá trị của từng điểm; tối đa doanh thu.

**Giải.** Sắp theo attractiveness để có DAG ngầm. `dp(q)=cq+max(0,max_p(dp(p)+|xp−xq|+|yp−yq|))`. Đẳng thức Manhattan là max của bốn dạng dấu: giữ `M[sx,sy]=max_p(dp(p)+sx·xp+sy·yp)`, mỗi q query bốn `M−sx·xq−sy·yq`. Các điểm bằng attractiveness **query cả nhóm rồi mới update**, tránh đi giữa các điểm bằng nhau. O(N log N), RAM O(N); nếu bucket được attractiveness, O(N+U). Không dựng O(N²) cạnh.

**Transformation:** longest path trên DAG dày + Manhattan → bốn extrema tuyến tính. **Hay: 4/5, giữ gộp mẫu metric.** Thêm “batch equal keys” vào cue. **Luyện:** vì sao phép max có thể đổi thứ tự giữa p và bốn dấu; điều gì đổi nếu bài yêu cầu tối thiểu thay vì tối đa?

## 2012C — Sequence

**Nguồn:** PDF 73. **Đề:** đổi ít phần tử nhất để mọi đoạn dài k có tổng chẵn.

**Giải.** Chỉ giữ parity bi. XOR hai cửa sổ liên tiếp cho `bi=b(i+k)`: mọi vị trí cùng residue mod k phải chung parity. Ngược lại, điều kiện tuần hoàn đó và XOR của k đại diện bằng 0 bảo đảm mọi cửa sổ chẵn. Với mỗi lớp, cost chọn 0=#ones, chọn 1=#zeros. Chọn từng lớp rẻ nhất; nếu XOR các lựa chọn lẻ, đổi lớp có `|cost0−cost1|` nhỏ nhất. Ties có delta 0. O(n+k), RAM O(k).

**Transformation:** nhiều ràng buộc overlapping windows → lấy hiệu/XOR → lớp đồng dư + một ràng buộc global. **Hay: 4/5, giữ.** Áp dụng với tổng trên nhóm abelian, nhưng bước majority ở đây riêng cho parity và unit cost. **Luyện:** tổng cửa sổ phải ≡c mod m thì quan hệ nào còn đúng, phần tối ưu cuối phải đổi thế nào?

## 2012D — DNA

**Nguồn:** PDF 74–75. **Đề:** chọn chuỗi độ dài n trên A,C,G,T có LCS với chuỗi đã cho nhỏ nhất.

**Giải.** Đặt m=min tần suất bốn ký tự của S. Mọi Y dài n có một ký tự c xuất hiện ≥ceil(n/4)≥m; S cũng có ≥m ký tự c, nên LCS(S,Y)≥m. Chọn Y=c* lặp n lần, với c* ít gặp nhất trong S, thì LCS đúng m. O(n), RAM O(1) ngoài output. Không chạy LCS DP, không tìm chuỗi phức tạp.

**Transformation:** tối ưu trên toàn bộ chuỗi → lower bound bằng pigeonhole + nghiệm đạt bound. **Hay: 4/5, giữ như mẫu extremal certificate.** Đếm một ký tự đủ khóa đáp án. **Luyện:** tổng quát alphabet σ; nếu Y bị bắt có đủ cả σ ký tự thì nghiệm constant mất hiệu lực ở đâu?

## 2012E — Evaluation of an Expression

**Nguồn:** PDF 76–77; PL, mục Ewaluacja wyrażenia. **Đề:** đếm assignment để biểu thức +,×,^k bằng 0 modulo prime p, đáp án modulo 30011; mỗi biến xuất hiện tối đa một lần.

**Giải.** Parse cây; mỗi node lưu histogram D[r] số assignment cho ra r. Lá hằng có một unit mass, lá biến có D[r]=1. Hai subtree có biến rời nhau nên kết hợp bằng tích số cách. Output là histogram gốc tại residue 0. Phép + là cyclic convolution độ dài p. Với ×, chọn primitive root g của Fp: các residue khác 0 viết g^j, phép nhân trở thành cộng chỉ số mod p−1, lại cyclic convolution. Khối 0 tính riêng: `D×[0]=A[0]·sum(B)+B[0]·sum(A)−A[0]B[0]`. Lũy thừa scatter D[r] vào Dnew[r^k mod p]. O(s·p log p), s=số node, bộ nhớ xử lý cây rồi giải phóng histogram con.

Convolution phải đúng **modulo 30011**, không mặc định một NTT modulus khác là đủ. Có thể dùng hai NTT primes và CRT để khôi phục mỗi hệ số nguyên trước giảm modulo: hệ số linear ≤p·30010², tích hai primes chọn lớn hơn bound; sau đó fold cyclic. Khi k=0, dùng quy ước lũy thừa đúng theo parser/đề (đề cho k∈{2,...,9}). Nếu một biến lặp ở hai nhánh, hai histogram không còn độc lập và lời giải này sai.

**Transformation:** phân phối của biểu thức → convolution trên nhóm cộng; nhóm nhân hữu hạn → log cơ số primitive root → convolution trên nhóm cộng khác. **Hay: 5/5, giữ.** Phần đáng nhớ là đổi *operation*, không phải chỉ “dùng FFT”. **Luyện:** p=5, tự lập bảng đếm x+y và xy; giải thích vì sao 0 không có discrete log.

## 2012F — Formula One

**Nguồn:** PDF 78–79; lời giải và chứng minh đầy đủ trong PL, Formuła 1, tr.77–80. **Đề:** các xe ban đầu theo thứ tự 1..n; một lần vượt là swap hai xe kề nhau; xe i phải vượt đúng ai lần. Hỏi có lịch hợp lệ không.

**Giải.** Không suy từ tổng ai. Với xe k, đặt `Ak=Σ(i<k)(ai+1)`: có thể vượt từng xe phía trước một lần và dùng hết lượt của xe đó bằng các cặp vượt qua lại. Phía sau có xe chắn không đủ lượt để vượt k. Quét i>k, giữ b=số xe chắn: nếu ai>b, xe i còn ai−b lượt để vượt k rồi bị k vượt lại; cộng ai−b vào Bk. Nếu ai≤b, tăng b. Do đó capacity của k là `sk=Ak+Bk`; điều kiện cần `ak≤sk` cho mọi k.

Chỉ cần kiểm tra **xe critical m cuối cùng thỏa am≥Am** (luôn có ít nhất xe 1). Với k>m, ak<Ak nên tự đạt điều kiện. Với k<m: `am≥Am≥ak+m−1` và blocker từ k tới m ≤m−2, nên riêng đóng góp của m đã làm sk>ak. Tính Am và Bm bằng hai scan, trả có iff am≤Am+Bm: O(n), RAM O(1) ngoài input.

Tính đủ không chỉ là suy đoán: có lịch dựng bằng cách mỗi bước lấy xe đầu tiên phía sau xe critical còn lượt để vượt xe ngay trước. Nếu không có xe như vậy, Bm=0 và điều kiện buộc am=Am; xe critical dùng chiến lược vượt/cặp luân phiên để hoàn tất mọi xe phía trước. Trong bước thường, swap giảm tổng lượt một; các xe phía sau mất tối đa một đơn vị Ak nhưng trước đó ak<Ak; các xe phía trước giữ capacity khi xe còn phải vượt blocker, hoặc được capacity của xe critical che khi vượt trực tiếp critical. Tách j>m+1 và j=m+1 cho thấy mọi `a'k≤s'k` vẫn đúng; quy nạp theo tổng lượt kết thúc ở vector 0. Đây là phần chứng minh khó, không được thay bằng “greedy chắc đúng”.

**Transformation:** tồn tại lịch swap rất dài → capacity inequalities → một constraint critical chi phối mọi constraint còn lại. **Hay: 5/5, giữ ý dominating witness; công thức riêng để trong khảo sát.** Không mô phỏng Σai có thể cực lớn. **Luyện:** `[1,0,1]` vô nghiệm dù tổng nhỏ; so với `[1,1,1]` có nghiệm. Tự chứng minh bất đẳng thức che cho k<m trước khi đọc chứng minh swap.

## 2012G — Save the Dinosaurs

**Nguồn:** PDF 80–81. **Đề:** một điểm an toàn nếu mọi hướng chạy từ đó đều đến gần ít nhất một lính; thêm một lính độc lập cho từng query, tính diện tích an toàn.

**Giải.** Với hướng đơn vị u, đạo hàm khoảng cách bình phương tới lính s tại x là `−2u·(s−x)`. Mọi hướng có một đạo hàm âm iff x nằm trong interior convex hull các lính: ngoài/boundary có separating/supporting line và hướng không gần ai; trong hull không thể có hướng mà tất cả dot≤0. Boundary không đổi diện tích. Dựng convex hull CCW. Query bên trong trả diện tích cũ; bên ngoài tìm hai tangent bằng binary search O(log h). Visible chain bị thay bằng hai cạnh qua điểm mới; shoelace prefix sums trả tổng cross của chain trong O(1), có xử lý wrap. Query độc lập, không update hull vĩnh viễn. O(n log n+m log h), RAM O(h).

**Transformation:** định lượng “mọi hướng / tồn tại lính” → separating hyperplane → convex hull → tangent update. **Hay: 5/5, giữ.** Điều kiện đạo hàm phải giảm nghiêm ngặt; hull suy biến có diện tích 0. **Luyện:** chỉ hai lính thì có điểm nào thỏa mọi hướng không; vì sao query trong hull không đổi diện tích?

## 2012H — Hydra

**Nguồn:** PDF 82–83. **Đề:** giết vĩnh viễn đầu loại i giá zi, hoặc chặt giá ui sinh một multiset đầu con; có cycle loại đầu, tìm giá diệt hết một đầu ban đầu.

**Giải.** `Ci=min(zi,ui+Σ con Cj)`. Đây là **AND**, không phải chọn một cạnh con rẻ nhất. Khởi tạo mọi tentative Ci=zi trong min-heap. Mỗi production có counter số occurrence con chưa final và sum khởi đầu ui. Khi j được pop/final, cộng Cj cho mọi reverse incidence của j và giảm counter; khi counter=0 mới relax loại cha với sum. Con lặp phải có từng incidence riêng. ui>0 làm candidate cha lớn hơn từng con, nên một production tối ưu không thể cần con chưa final rẻ hơn candidate cha: lập luận Dijkstra vẫn đúng. Cycles không buộc giải hệ phương trình; luôn có phương án giết vĩnh viễn. O((n+R)log n), RAM O(n+R); sum có thể vượt 32 bit dù Ci≤zi.

**Transformation:** sinh nhánh đệ quy có cycle → shortest derivation trên AND hypergraph → Dijkstra với counters. **Hay: 5/5, giữ.** Cue mạnh cho crafting, recipe, grammar cost. **Luyện:** production i→[j,j] phải cộng 2Cj; thử self-loop i→[i] giá dương.

## 2012I — Inversions

**Nguồn:** PDF 84–85. **Đề:** đồ thị hoán vị nối hai giá trị tạo inversion; xuất các connected components.

**Giải.** Một cut sau vị trí i không có cạnh đi qua iff mọi giá trị bên trái nhỏ hơn mọi giá trị bên phải, tức `max(a1..ai)=i` vì đây là hoán vị 1..n. Các minimal blocks giữa những cut đó chính là components: nếu một block không liên thông, hai components không có inversion giữa nhau, nên chúng có cùng thứ tự trong vị trí và giá trị; sẽ tồn tại cut bên trong, trái định nghĩa minimal block. Scan prefix max, mỗi cut xuất interval giá trị liên tiếp của block. O(n), RAM tùy cách output, không dựng Θ(n²) inversion edges.

**Transformation:** connected components trên permutation graph dày → ranh giới không có inversion → prefix certificates. **Hay: 4/5, giữ.** Phụ thuộc permutation; array có duplicates không dùng max=i. **Luyện:** `[2,1,4,3]` có hai components; `[2,3,1]` chỉ có một.

## 2012J — Do It Tomorrow

**Nguồn:** PDF 86–87. **Đề:** mỗi công việc có duration và deadline; bắt đầu muộn nhất nhưng vẫn hoàn tất tất cả, bảo đảm có nghiệm.

**Giải.** Sort deadlines tăng. Swap một cặp deadline đảo thứ tự không làm hỏng feasibility: cả hai cùng kết thúc ở một thời điểm, job deadline sớm được chuyển lên trước. Với prefix duration Di, thời gian bắt đầu s phải thỏa `s+Di≤ti` cho mọi i. Đáp án `min_i(ti−Di)`. Không cần idle giữa các job vì chuyển idle ra đầu chỉ làm chúng xong sớm hơn. O(n log n), dùng int64.

**Transformation:** tối ưu lịch permutation → exchange để cố định thứ tự → min slack của prefixes. **Hay: 3/5, không thêm riêng.** EDF và prefix slack quen thuộc; giữ làm bài luyện exchange, không chiếm trang mới. **Luyện:** vì sao sort duration không có chứng minh tương tự?

## 2012K — Rabbits

**Nguồn:** PDF 88–89; PL, Króliki, tr.97–99. **Đề:** thỏ trên vòng n luống; bắn luống i xua hết thỏ tại i, thỏ ở hai hàng xóm nhảy ra xa i; k phát để xua nhiều nhất.

**Giải.** k≥ceil(n/2) thì bắn cách một luống theo vòng xua được hết. Nếu ít hơn, gọi một luống “sạch” khi các thỏ *ban đầu* ở đó đã bị xua. Các maximal clean intervals cách nhau ≥2 luống: nếu giữa hai interval chỉ một luống, hai phát ở endpoints cũng xua thỏ ở luống giữa. Interval dài l cần ceil((l+1)/2) phát vì phải bắn hai đầu và không được có gap≥2. Nếu l chẵn, cùng số phát có thể làm sạch l+1 luống; với trọng số không âm không thiệt. Vì vậy tồn tại tối ưu gồm các interval lẻ, bắn xen kẽ trong mỗi interval, **không có hai luống bắn kề nhau**.

Đặt xi∈{0,1} biểu diễn luống bắn. Với normal form này, thỏ ban đầu ở i bị xua iff `xi OR (x(i−1) AND x(i+1))`; thứ tự bắn không còn ảnh hưởng payoff. Tối đa `Σai·[điều kiện]`, `Σxi≤k`, forbids adjacent 1 trên cycle. DP đi theo luống, giữ hai bits cuối và số phát; khi biết bit phải thì chốt reward của bit giữa. Enumerate hai bits đầu, đóng vòng và hai rewards cuối. O(nk), RAM O(k). Không dùng normal form independent set cho case xua hết n lẻ mà không xử lý riêng.

**Transformation:** mô phỏng đẩy thỏ phụ thuộc thứ tự → chứng minh normal form → objective local radius 1 → cycle DP. **Hay: 5/5, giữ.** Điểm đáng học là loại bỏ thứ tự bằng exchange/geometry của vùng sạch, không chỉ “DP vòng”. **Luyện:** mô phỏng mọi lịch ngắn trên n≤7 để kiểm tra normal form; phân biệt thỏ ban đầu với số thỏ đang đứng trên luống.

## 2013A — The Motorway

**Nguồn:** PDF 93–94; PL, Autostrada. **Đề:** đặt n+1 trạm cách đều L, xen kẽ n lối vào ai đã sort; tìm cả L nhỏ nhất và lớn nhất.

**Giải.** Gọi b vị trí trạm đầu. Điều kiện thứ i là `ai−iL≤b≤ai−(i−1)L`. Khử b: `F(L)=max_i(ai−iL)−min_i(ai−(i−1)L)≤0`. F convex, nên tập feasible là một interval, **không phải predicate tăng/giảm trên toàn miền**. Dùng ternary/subgradient search tìm điểm min F trên [0,an]; đề bảo đảm miền feasible không rỗng. Sau đó binary search trái/phải của điểm này để tìm hai đầu interval. Mỗi evaluation O(n), tổng O(n log(range/precision)); dùng long double, kiểm soát sai số ở phép iL và kiểm tra tolerance theo yêu cầu output. Từ feasible L dựng b trong interval bounds. Editorial còn dựng upper/lower envelopes của các line có slope đã sort để giải O(n), nhưng implementation số thực phức tạp hơn.

**Transformation:** tồn tại offset và khoảng cách → khử một biến bằng giao interval → convex envelope → hai biên feasible. **Hay: 5/5, giữ.** Cue ngăn binary search sai vì feasible không monotone. **Luyện:** `[2,3,4,5,6,7]` cho L∈[5/6,5/4]; chứng minh bất đẳng thức pairwise cho hai cận `(aj−ai)/(j−i+1)` và `(aj−ai)/(j−i−1)`.

## 2013B — Bytehattan

**Nguồn:** PDF 95–96. **Đề:** xóa lần lượt đường của grid thành phố, query hai đầu đường còn kết nối không; input tiếp theo phụ thuộc đáp án trước.

**Giải.** Không thể offline đảo thời gian vì chưa biết các cạnh xóa. Dựng planar dual: một đỉnh cho mỗi ô mặt và một cho mặt ngoài; mỗi đường primal có hai mặt kề. Xóa đường primal tương ứng **thêm cạnh dual/ghép hai mặt**. Trước xóa, nếu hai mặt đã trong cùng DSU thì cạnh primal là bridge, xóa làm hai endpoint mất kết nối; nếu khác DSU thì có đường primal khác nối endpoint, union hai mặt. Bridge iff hai phía cùng một mặt là tính chất planar embedding, vẫn đúng khi primal đã có nhiều components. O(n²+k α(n²)), RAM O(n²), gán đúng mặt ngoài ở biên.

**Transformation:** online deletions connectivity → planar dual additions connectivity. **Hay: 5/5, giữ.** Duality thay được time reversal ngay cả khi input adaptive; cần embedding và query đúng hai đầu cạnh bị xóa. **Luyện:** xóa một cạnh cycle, rồi xóa cạnh khác cùng cycle; DSU mặt thay đổi thế nào?

## 2013C — The Carpenter

**Nguồn:** PDF 97–98; PL, Cieśla. **Đề:** cắt hai tam giác từ bảng màu để ghép thành bàn cờ vuông lớn nhất; hai phần cắt không chồng interior.

**Giải.** Hai nửa phải là right-isosceles triangles leg L, có checkerboard, cùng màu ô ở góc vuông. Chuẩn hóa `b[r,c]=a[r,c] XOR ((r+c)%2)` thì checkerboard thành monochromatic. Tính maximal leg ở từng ô góc và cả bốn hướng bằng `1+min(DP ở hai hàng xóm theo trục)`, với hàng xóm khác b hoặc ngoài bảng đóng góp 0. Đây là tam giác cell offsets u+v≤L−1, gồm các half-cells trên hypotenuse.

Với L cố định, liệt kê mọi corner có DP≥L; lấy ba **đỉnh hình học** của mỗi triangle, suy ra min/max projection trên x,y,x+y,x−y. Hai tam giác convex loại này có interior rời nhau iff một trong bốn trục đó tách projections (normals của các cạnh). Với từng màu corner và trục, chỉ giữ min của right endpoint và max của left endpoint: có cặp tách iff `min right≤max left`. Một triangle riêng không thể tạo inequality này do projection width>0, nên cặp là hai triangle khác nhau. Shrink giữ nguyên corner và màu nên decision monotone theo L; binary search L. O(nm log min(n,m)), RAM O(nm). Đây là lời giải đơn giản hơn để tái dựng; editorial loại cả log bằng sweep maxima qua O(n+m) separating lines, gồm bước shrink triangle và đổi màu nếu corner dịch.

**Transformation:** hai vùng cắt không giao nhau → separating axis → extrema của projections, tránh so sánh mọi cặp. **Hay: 5/5, giữ cue hình học.** Touch boundary được phép; phải dùng vertices, không chỉ bounding box cell. **Luyện:** hai nửa cùng một ô có thể cho L=1; vì sao xét chỉ x/y bỏ sót hai nửa tách bởi đường chéo?

## 2013D — Demonstrations

**Nguồn:** PDF 99–100. **Đề:** hủy tối đa hai cuộc biểu tình, mỗi cuộc chặn một interval, để tổng chiều dài đường còn bị chặn nhỏ nhất.

**Giải.** Sweep các endpoints theo nhóm tọa độ, active set các IDs. Slab chỉ có một ID i đóng góp ui (unique coverage); đúng hai IDs i,j đóng góp wij; ≥3 IDs không thể mở lại chỉ bằng hai lần hủy. Gain khi xóa i,j là `ui+uj+wij`. Có O(n) slabs nên chỉ O(n) pair entries wij khác 0, dù có Θ(n²) cặp IDs. Lấy baseline hai ui lớn nhất (hoặc một nếu n=1), rồi scan các pairs wij để maximize gain. Những cặp không có entry có gain đúng ui+uj; cặp top-two có entry thì được xét riêng và chỉ tăng gain. Đáp án union ban đầu−best gain. O(n log n), RAM O(n).

**Transformation:** thử mọi cặp xóa → chỉ coverage multiplicity≤2 có ảnh hưởng → sparse pair interactions. **Hay: 5/5, giữ.** Generalization xóa k: chỉ tầng coverage≤k đáng xét, nhưng không mặc định tối ưu chọn k tập vẫn dễ. **Luyện:** vùng có ba cuộc biểu tình luôn còn chặn sau xóa hai, bất kể độ dài.

## 2013E — The Exam

**Nguồn:** PDF 101–102. **Đề:** permutation 1..n với mọi adjacent difference≥k.

**Giải.** Tồn tại iff k≤floor(n/2). Khi k lớn hơn, một số trung tâm không có bất kỳ hàng xóm đủ xa để đứng cạnh, nên n>1 không thể. Với n=2m, dựng `m,2m,m−1,2m−1,...,1,m+1`: differences là m hoặc m+1. Với n=2m+1, dựng `m+1,1,m+2,2,...,2m+1,m`: differences m hoặc m+1. Lấy pattern này cho mọi k≤m. Trường hợp n=1 có permutation đơn, không có pair constraint. O(n).

**Transformation:** tồn tại permutation với bound từng cạnh → obstruction tại phần tử trung tâm + interleave hai nửa đạt bound. **Hay: 3/5, không thêm riêng.** Kỹ thuật extremal construction tốt để luyện, mẫu khá riêng. **Luyện:** tự tính mọi adjacent gap của hai constructions; tránh dựng xen kẽ thấp/cao sai khiến gap cuối chỉ 1.

## 2013F — Speed Cameras

**Nguồn:** PDF 103–104; PL, Fotoradary. **Đề:** đặt nhiều camera trên đỉnh cây nhất, mỗi simple path đi qua ≤k camera.

**Giải.** Mọi path kéo dài thành leaf-to-leaf path. Khi k≥2, có tối ưu đánh dấu toàn bộ lá: nếu thiếu một lá, dời dấu từ marked internal vertex gần nhất về lá; không có marked internal trên đoạn giữa. Path mới bị tăng mà không mất dấu chỉ có thể đi qua phần nhánh rỗng đó và một selected leaf ở đầu kia trước khi tới vertex dời dấu, nên vẫn ≤2; hoặc dùng exchange theo layers như editorial. Sau đánh dấu tất cả lá, bỏ lớp lá: mọi path trong core kéo dài tới hai lá ngoài, nên bài core có budget k−2, và ngược lại thêm hai endpoint leaves chỉ tăng tối đa 2. Lặp floor(k/2) lớp bằng queue độ≤1. k lẻ thì đánh dấu thêm một vertex còn lại; k=1 chỉ chọn một, vì hai vertex luôn cùng nằm trên một path. Core rỗng thì dừng. O(n), RAM O(n).

Điều kiện “đường không có camera giữa lá và vertex dời dấu” cần chọn closest *marked internal*; không dời một lá khác vì như vậy không tiến tới trạng thái chứa mọi lá. Trong singleton core, mở path tới hai lá của cây trước đó vẫn cho residual bound; xử lý empty/singleton rõ để queue không bỏ mất đỉnh cuối.

**Transformation:** ràng buộc trên mọi tree paths → exchange về biên → peel layers, giảm budget 2 mỗi lớp. **Hay: 5/5, giữ.** Khác hẳn DP tree n×k. **Luyện:** cây sao 6 đỉnh, k=2 chọn 5 lá; đường 6 đỉnh, k=2 chỉ chọn 2. Kiểm tra bằng exhaustive subsets trên cây nhỏ.

## 2013G — Marbles

**Nguồn:** PDF 105–106; chứng minh bound trong PL, Gra w kulki, tr.128–132. **Đề:** hai người rút luân phiên, cùng số viên; counts các chữ số 0..9 có thể 10^15; hỏi có cách chia cho hai tích bằng nhau.

**Giải.** ≥2 số 0: chia một cho mỗi bên, có thể cân số viên, trả có; đúng một 0: trả không. Không có 0 thì k5,k7 phải chẵn và chia đôi. Còn digits 1,2,3,4,6,8,9. Đặt di=ai−bi; `|di|≤ki`, `di≡ki (mod2)`. Tích bằng nhau và cùng số viên trở thành ba phương trình:

```
d1+d2+d3+d4+d6+d8+d9 = 0
d2+2d4+d6+3d8 = 0
d3+d6+2d9 = 0
```

**Định lý của editorial:** nếu có nghiệm, có nghiệm với mọi |di|≤6. Vì vậy giảm ki>6 về 5 hoặc 6 cùng parity, tương đương xóa các cặp chia đều. Enumerate d4,d6,d8,d9 trong [-min(ki,6),min(ki,6)] đúng parity, rồi suy ra `d2=−2d4−d6−3d8`, `d3=−d6−2d9`, `d1=d4+d6+2d8+d9`; check bounds/parities cả ba. ≤7^4=2401 cases/test thay vì 7^7. Precheck tổng exponent của 2/3 chẵn.

Bound 6 **không phải do thử một ít input thấy đúng**. Sách chứng minh hỗ trợ máy: xét mọi cấu hình cap0..6, sinh balanced vectors; các cấu hình không có bounded nghiệm bị chứng nhận vô nghiệm cho cả họ mở rộng bằng parity/obstruction, Gaussian elimination với các tọa độ ≤4 cố định; hai họ còn lại được loại bằng đồng dư mod4. Đây là theorem nguồn, chưa tái chạy toàn bộ certificate đó trong repo; kiểm thử nhỏ ở đây chỉ kiểm tra phép giảm/equations, không thay thế chứng minh bound.

**Transformation:** tích khổng lồ → prime-exponent vector + cardinality → bounded imbalance kernel. **Hay: 5/5 về ý tưởng, không đưa số 6 vào cue tổng quát.** Discrete log không dùng được để giữ equality nguyên; prime valuation mới đúng. **Luyện:** chỉ kiểm tra tổng exponent chẵn có đủ không? Counts `[k1,k2,k3,k4,k6,k8,k9]=[0,6,1,0,1,5,3]` cho một obstruction mà editorial giải riêng.

## 2013H — The Hero

**Nguồn:** PDF 107–108; PL, Heros. **Đề:** đi tàu trên directed graph; đảo có khoảng ngày bật bẫy, không được ở trên đảo lúc đó; được chờ khi an toàn; outdegree≤10.

**Giải.** Union traps của mỗi đảo rồi lấy maximal safe intervals [L,R]. State là **(đảo, safe interval)**, không chỉ đảo: đến sớm hơn chỉ dominates đến muộn hơn *trong cùng interval*, vì không thể chờ qua bẫy. Dijkstra lưu earliest arrival t. Với chuyến duration d, có thể tới đảo đích tại bất kỳ thời điểm trong [t+d,R+d]; relax safe intervals giao nó, candidate `max(t+d,Ltarget)`.

Tránh scan p intervals cho mỗi incoming edge: binary search interval chứa t+d nếu có, point-relax nó; mọi target interval có start A∈(t+d,R+d] được tới **đúng đầu interval A**, là cận dưới tuyệt đối, không bao giờ cải thiện nữa. Dùng ordered set hoặc successor DSU chứa các intervals chưa được chạm đầu; range scan rồi remove từng interval được activate. Mỗi interval kiểu này xử lý một lần, mỗi state chỉ có ≤10 outgoing edges. O((n+p)log(n+p)+m) ngoài sort traps, RAM O(n+m+p). Giữ danh sách interval gốc cho binary search kể cả interval đã remove khỏi set. Ngày bắt đầu là 1, output arrival−1.

**Transformation:** time-dependent routes → interval states → split relaxation thành một partial interval và các globally final-at-start intervals. **Hay: 5/5, giữ.** Không time-expand đến 10^9, không FIFO Dijkstra trên mỗi đảo vì đảo không cho chờ qua bẫy. **Luyện:** sample cần đi vòng để sống qua trap; bỏ cycle sẽ làm mất nghiệm.

## 2013I — Genetic Engineering

**Nguồn:** PDF 109–110; PL, Inżynieria genetyczna. **Đề:** longest subsequence ghép từ blocks k ký tự giống nhau; trong các longest chọn lexicographically nhỏ nhất.

**Giải.** Với mỗi position i, occurrence lists cho e[i]=vị trí occurrence thứ k của gi tính từ i; không đủ thì ∞. `dp[i]=max(dp[i+1],1+dp[e[i]+1])` đếm số blocks. Chọn k occurrences sớm nhất không thiệt vì để lại suffix lớn nhất. Khi còn b blocks và vị trí start s, chỉ có thể chọn i≥s với `1+dp[e[i]+1]=b`; trong số đó chọn (gi,i) nhỏ nhất, output gi k lần và s=e[i]+1. Điều kiện suffix bằng b−1 là certificate giữ độ dài tối ưu; chọn ký tự nhỏ nhất bảo đảm lex optimum, tie lấy earliest i không thiệt.

Bucket các i theo b; từng bucket sort theo i (scan tự có thứ tự), dựng suffix minimum pair (gi,i). Mỗi bước binary search s trong bucket b rồi lấy suffix minimum. O(n+M+(n/k)log n), RAM O(n+M). Editorial còn O(n+M): dùng suffix-greedy tính khả năng hoàn tất, scan tới vị trí cuối vẫn còn b−1 blocks rồi lấy giá trị nhỏ nhất đủ k occurrences; rollback tới occurrence thứ k của giá trị đó. Các đoạn rollback nằm trong các vùng suffix-dp bằng nhau và rời nhau, nên tổng scan tuyến tính.

**Transformation:** lexicographic greedy dễ mất longest → suffix-optimum feasibility certificates → greedy chỉ trên lựa chọn còn khả năng hoàn tất. **Hay: 4/5, giữ.** Cue phổ biến khi reconstruct optimal string. **Luyện:** k=3, `[4,4,1,1,4,1,7,7,2,7]`: greedy hoàn tất block sớm lấy 4, đúng lex optimum lấy 1.

## 2013J — Jánošík

**Nguồn:** PDF 111–112. **Đề:** một hộp i xu; chẵn chia đôi, lẻ>1 lấy một xu rồi xử lý tiếp; hộp một xu đem cho; tính xu giữ khi ban đầu có các hộp 1..n.

**Giải.** f(1)=0, `f(2m)=2f(m)`, `f(2m+1)=1+f(2m)` cho m≥1. Quy nạp theo hai trường hợp cho `f(i)=i−2^floor(log2 i)`. Các hộp độc lập nên Σf(i). Chia i thành dyadic blocks [2^b,min(n,2^(b+1)−1)], dùng arithmetic sum trừ count·2^b. O(log n), không mô phỏng exponential splitting; dùng integer shifts và int64 khi n≤10^9.

**Transformation:** branching process → closed form theo highest power of two → gom đoạn quotient/log cố định. **Hay: 4/5, giữ gộp mẫu grouping.** **Luyện:** f(7)=3; tự suy từ recurrence trước khi đoán theo vài output.

## 2013K — Blankets

**Nguồn:** PDF 113–114. **Đề:** hình chữ nhật axis-aligned; kỳ vọng diện tích giao của một cặp được chọn đều.

**Giải.** Đặt c(x,y)=số blankets phủ điểm. Tổng diện tích giao mọi cặp = `∫∫ choose(c,2)`. Sweep x, compress y, segment tree range-add δ=±1 giữ `S1=∫c dy`, `S2=∫c²dy` và geometric length của node. Update `S2←S2+2δ·S1+δ²·len` **trước khi** đổi `S1←S1+δ·len`, compose lazy bằng cộng. Slab width dx góp `dx·(S2−S1)/2`; xử lý endpoints đồng x theo nhóm. Chia tổng cho choose(n,2). O(n log n), RAM O(n); weighted y lengths bắt buộc, accumulate bằng int128 trước chuyển sang floating output (tổng có thể vượt int64).

**Transformation:** tổng Θ(n²) pair intersections → đổi thứ tự sum/integral → polynomial moments của coverage. **Hay: 5/5, giữ.** Tổng triple overlap dùng choose(c,3) và moment bậc 3 tương tự. **Luyện:** ba rectangles trùng nhau: union diện tích A nhưng tổng pair intersections 3A, không nhầm hai quantities.

## 2014A — The Lawyer

**Nguồn:** PDF 117–118. **Đề:** chọn ngày có hai khách với giờ gặp không giao nhau, xuất IDs.

**Giải.** Với từng ngày giữ khách kết thúc sớm nhất e và khách bắt đầu muộn nhất s. Có cặp không giao iff e<s theo điều kiện strict của đề. Nếu e<s, hai IDs tự khác nhau vì mỗi interval start≤end. Nếu có bất kỳ cặp trước/sau, hai extrema còn tách ít nhất bằng cặp đó. O(n+m), RAM O(n).

**Transformation:** tìm cặp intervals trong mỗi bucket → hai extrema. **Hay: 2/5, không thêm.** Một câu đủ cho bài warm-up; không cần mục riêng. **Luyện:** endpoint bằng nhau có được tính không? Đọc đúng strictness của đề.

## 2014B — Petrol

**Nguồn:** PDF 119–120; PL, Benzyna. **Đề:** queries giữa hai trạm xăng, xe có capacity b; route được refuel tại các trạm, hỏi có đi được không.

**Giải.** Multi-source Dijkstra từ mọi trạm S lấy dS(v)=khoảng cách đến trạm gần nhất. Đổi weight **của mỗi cạnh đường gốc** thành `w*(u,v)=dS(u)+w(u,v)+dS(v)`. Route với refuel và từng đoạn≤b tồn tại iff x,y kết nối trong subgraph chỉ cạnh w*≤b.

Chiều cần: mỗi cạnh trong một đoạn từ trạm s1 tới s2 có dS(u)≤đoạn từ s1 tới u và dS(v)≤đoạn v tới s2, nên w*≤chiều dài cả đoạn≤b. Chiều đủ: dọc một path gồm các cạnh w*≤b, trước/sau mỗi cạnh có thể đi vòng tới trạm gần nhất của endpoint; chặng từ trạm gần u qua (u,v) tới trạm gần v dài đúng w*, nên ghép thành route hợp lệ. Detours được phép, không cần đường đơn trong đồ thị gốc. Sort cạnh và queries theo b, DSU; hoặc minimum spanning forest trên w* rồi max-edge LCA cho online queries. O((n+m)log n+(m+q)log(m+q)), RAM O(n+m+q). Component không có trạm thì dS=∞, bỏ cạnh ấy.

**Transformation:** resource-constrained path với refuel → nearest-source distance potentials → threshold connectivity. **Hay: 5/5, giữ.** Tránh fuel state có capacity 10^9 và tránh all-pairs shortest paths giữa trạm. **Luyện:** tại sao chỉ thay weight bằng w+dS(u) bỏ dS(v) sẽ không đủ chứng minh?

## 2014C — The Prices

**Nguồn:** PDF 121–122; PL, Ceny. **Đề:** mua m≤16 sản phẩm ở n≤100 kho; mỗi kho có opening/travel cost di, giá cij; minimize tổng.

**Giải.** Naive partition DP: cost(mask)=min over submask B `[cost(mask\B)+min_i(di+Σj∈B cij)]`, O(n2^m+3^m), đã đủ sau precompute. Có cách O(nm2^m), RAM O(2^m): xử lý từng kho i, old[mask] là best chỉ dùng kho trước. Khởi tạo `open[mask]=old[mask]+di`, biểu diễn mở kho i chưa mua thêm gì. Theo mask tăng, relax `open[mask]=min_j∈mask(open[mask\{j}]+cij)`. Cuối lớp `new[mask]=min(old[mask],open[mask])`.

Mọi assignment sản phẩm cho kho i có thể xây bằng thêm từng sản phẩm vào trạng thái open; trả opening cost đúng một lần. Mọi đường DP cũng là assignment hợp lệ, nên tương đương. Có thể mở nhưng không mua gì vì di≥0, trạng thái đó không cải thiện old. Mask order bảo đảm proper submask đã có giá trị. Không duyệt mọi submask cho từng kho.

**Transformation:** chọn cả bundle ở một kho → thêm cờ “đã mở kho” → thêm sản phẩm đơn lẻ. **Hay: 5/5, giữ.** Tăng state để giảm branching từ 2^popcount xuống popcount; fixed-charge DP cho shopping/facility. **Luyện:** vì sao chỉ giữ best[mask] mà không trạng thái open thì cộng di mỗi sản phẩm sẽ sai?

## 2014D — Divisors

**Nguồn:** PDF 123. **Đề:** đếm ordered pairs i≠j với ai chia aj, ai≤U=10^6.

**Giải.** freq[x] counts. `ans=Σd freq[d]·Σk≥1 freq[kd]−n`: inner loop đi các multiples của d. Trừ n loại đúng các self-pairs, giữ hai indices khác nhau cùng giá trị. O(n+U log U), RAM O(U), ans int64. Nếu đề diễn đạt cặp theo thứ tự chia thì không tự chia kết quả cho 2.

**Transformation:** pairwise divisibility → value frequencies + multiples sieve. **Hay: 2/5, không thêm riêng.** Notebook đã có divisor sieve; giữ làm bài kiểm tra multiplicities. **Luyện:** `[2,2]` phải đếm 2 ordered pairs sau khi trừ self.

## 2014E — Euclidean Nim

**Nguồn:** PDF 124–125; PL, Euklidesowy Nim, tr.169–170. **Đề:** người có step p phải bỏ một positive multiple p nếu pile≥p, nếu không phải thêm p; người kia step q; ai làm pile 0 thắng, có thể chơi vô hạn.

**Giải.** d=gcd(p,q) invariant residue n mod d. Nếu residue≠0 thì không thể về 0, draw. Nếu chia hết, scale cả n,p,q cho d. p=q thì người đi trước lấy hết. Còn lại gọi P có step p nhỏ, Q có step q lớn (p<q), phân biệt người bắt đầu:

- Q bắt đầu, n<q: P thắng. Q buộc thêm q; P bỏ tối đa, để `(n+kq) mod p<p<q`, Q tiếp tục bị buộc thêm. gcd=1 làm các residues chạy tới 0, P thắng hữu hạn.
- P bắt đầu, n≥p: P thắng bằng lấy hết hoặc để n mod p, đưa về case trên.
- P bắt đầu, n<p: P thắng iff n không chia hết q−p. P buộc thêm p; nếu vẫn dưới q đã vào case Q-small và P thắng. Nếu ≥q thì <2q, Q buộc bỏ q. Mỗi cặp nước giảm pile q−p; Q chạm 0 iff n là multiple q−p, nếu không cuối cùng P đẩy vào Q-small.
- Q bắt đầu, n≥q: đặt r=n mod q. Q thắng iff **r<p và r chia hết q−p**, gồm r=0. Nếu Q bỏ ít hơn tối đa thì để pile≥q>p cho P thắng; bỏ tối đa thì các cases trên quyết định.

Ánh xạ lại P/Q sang E/P theo hai step gốc và người E đi trước. O(log min(p,q)) cho gcd, các case O(1). Không cần memo game states tới 10^9, không kết luận mọi vị trí divisible gcd đều là người đầu thắng.

**Transformation:** infinite cyclic game → invariant residue → forced-move trap region → arithmetic progression modulo q−p. **Hay: 4/5, giữ cue “force opponent into add-only region”; không chép bốn case vào notebook.** **Luyện:** step nhỏ 3, step lớn 5, pile 2: người nhỏ đi trước thua; pile 1 thì thắng. Kiểm tra small games bằng retrograde có draw states.

## 2014F — Pillars

**Nguồn:** PDF 126–127; PL, Filary, tr.172–173, có hình templates và thao tác nối cycle. **Đề:** đi một cycle qua mọi grid cell còn trống đúng một lần; rectangle dimensions chẵn, holes là các pillars 2×2 tách nhau đủ xa và xa biên.

**Giải.** Bài là Hamilton cycle, nhưng separation/parity của đề cung cấp cấu trúc riêng. Tile grid bằng 2×2 blocks. Pillar có tâm tọa độ lẻ/lẻ trùng một block, bỏ block đó; các blocks còn lại có 4-cycle. Với tâm chẵn/chẵn, gom patch 4×4 quanh pillar; parity mixed gom 4×6 hoặc 6×4, chiều dài 6 ở trục tọa độ lẻ. Các patch biên ở even coordinates, fit grid; khoảng cách tâm≥6 bảo đảm không overlap (hai patches có interior overlap thì khoảng cách tâm<6). Phần còn lại tile 2×2.

Mỗi patch trừ hole có Hamilton cycle template, chứa các cặp boundary edges của coarse blocks để nối sang neighbor. Với 4×4 là vòng 12 cells; template 4×6 dưới đây là 20 cells (row,col zero-based, hole rows1..2,cols2..3), đóng cycle về đầu:

```
(0,0),(0,1),(0,2),(0,3),(0,4),(0,5),(1,5),(1,4),(2,4),(2,5),
(3,5),(3,4),(3,3),(3,2),(3,1),(3,0),(2,0),(2,1),(1,1),(1,0)
```

Coarse adjacency graph của các regions connected do các holes isolated; tìm spanning tree. Mỗi tree edge, bỏ một side edge trong cycle mỗi region rồi nối hai cặp endpoints ngang qua boundary. Hai cycles biến thành một, không mất/nhân cell; lặp edges cây thì thành một Hamilton cycle toàn vùng. Các boundary pairs khác nhau dùng distinct edges nên template hỗ trợ nhiều neighbors. O(nm+f), RAM O(nm), luôn có nghiệm dưới đúng assumptions đề. Không dùng như một solver Hamilton cycle cho grid holes tùy ý.

**Transformation:** Hamilton cycle khó → cycle cover bằng finite local templates → spanning tree splicing. **Hay: 5/5, giữ.** Đây là cấu trúc construction, không phải chỉ gọi DFS hay dựa vào “grid planar”. **Luyện:** chứng minh splice hai cycles đúng bằng xem degree 2 và connectivity; thử bỏ điều kiện holes cách xa để thấy local patches có thể chồng nhau.

## 2014G — Global Warming

**Nguồn:** PDF 128–129; PL, Globalne ocieplenie. **Đề:** longest contiguous subarray mà minimum và maximum đều xuất hiện đúng một lần, ties chọn start sớm nhất.

**Giải.** Fix i là unique minimum. Monotonic stack cho l1,r1 là nearest positions trái/phải có value≤ai; mọi candidate phải nằm trong open interval (l1,r1), chứa i. Gọi M là max của interval đó. Một longest candidate chứa i phải chứa đúng một occurrence của M: nếu chưa có M thì có thể mở rộng đến occurrence M gần nhất mà vẫn unique min/max. Gọi l2,l3 là hai occurrences M gần i nhất bên trái (thiếu thì sentinel l1), r2,r3 tương tự bên phải (sentinel r1). Chỉ cần hai candidates `(l3,r2)` nếu có M trái, và `(l2,r3)` nếu có M phải; không xét candidate hướng không có M. Chúng mở tối đa mà vẫn giữ chỉ một M. Singleton interval trả length1.

RMQ trả max và occurrence lists của từng value dùng binary search để lấy l2,l3,r2,r3: O(n log n), RAM O(n). Segment tree query max đủ cho bound; không dựng sparse table O(n log n) memory khi n lớn. Editorial còn O(n): enrich monotonic stack blocks bằng max value và hai latest occurrences, merge khi pop; scan reverse lấy pair bên phải và thống nhất global max M.

**Transformation:** subarray property không hereditary → fix unique extremum → forbidden boundaries → chỉ hai candidates quanh occurrences của extremum kia. **Hay: 5/5, giữ.** Ordinary sliding window sai: một đoạn bad có thể trở lại good khi thêm maximum mới. **Luyện:** `[2,2]` bad nhưng `[2,2,1,3]` good; tự so kết quả two-candidate với brute mọi intervals.

## 2014H — Hit of the Season

**Nguồn:** PDF 130–131; PL, Hit sezonu, tr.179–182. **Đề:** tìm stamp RGB ngắn nhất phủ cả partial word có ≤19 wildcard; chồng stamp được phép, fixed letters phải khớp, wildcard cho phép các màu chồng khác nhau.

**Giải.** Với stamp S dài L, gọi Occ là start positions của mọi occurrence compatible với fixed letters. Stamp hợp lệ iff 0∈Occ và `max gap(Occ∪{n})≤L`; điều kiện cuối cũng buộc occurrence cuối tại n−L. Có thể in tại tất cả occurrences vì thêm lượt compatible không làm hỏng fixed cells; wildcard không buộc màu các lượt trùng nhau.

Tách theo L. Nếu L≥ceil(n/2), chỉ cần in đầu/cuối: prefix và suffix dài L có common full completion iff compatible từng letter. Không có consistency problem giữa các wildcard khác positions trong T, bởi stamp offsets mới là các biến. Precompute `Pref[i]=min(n−i, first p with T[p] not compatible T[i+p])` trong O(n²); candidate dài L tồn tại iff Pref[n−L]=L. Đi từ L=ceil(n/2) tìm shortest và dựng common completion.

Nếu L≤floor(n/2), có thể reverse T để nửa prefix ít wildcard hơn, ≤floor(k/2) (hai nửa rời nhau). Enumerate completions **chỉ các wildcard trong nửa này**, không 3^k. Làm DFS xây prefix stamp từng ký tự: ký tự fixed có một nhánh, wildcard ba nhánh. Giữ Occ dưới dạng linked list cùng sentinel n; extension chỉ xóa starts không extend được, max gap chỉ tăng. Với fixed letter p, dùng buckets Pref^-1[p] cho các starts chắc chắn mismatch hoặc tràn text; với wildcard của prefix, scan active starts và check chosen letter. Từ một branch tới branch con copy/rollback Occ. Mỗi start bị xóa một lần giữa hai branching levels, nên O(n) work mỗi branch node; tổng O(n²+n·3^floor(k/2)), RAM O(kn) với copying. Dừng extension tại floor(n/2), kiểm tra gap sau mỗi extension; lưu candidate shortest. Nếu đã reverse, đảo stamp lúc output.

**Transformation:** overlapping printing → partial-word cover + maximum occurrence gap → split short/long regimes → symmetry giảm exponent từ k xuống k/2. **Hay: 5/5, giữ cue split regime/asymmetric enumeration.** Không phải MITM ghép hai halves: chỉ chọn phía ít wildcard, phía còn lại kiểm bằng occurrences. Compatibility không transitive nên KMP bình thường trên wildcard không mặc định đúng. **Luyện:** sample `RRG*R*BRR**B` có stamp `RRGB`; giải thích vì sao chọn một full completion toàn T trước có thể loại mất stamp tối ưu.

## 2014I — The Staging

**Nguồn:** PDF 132–133; PL, Inscenizacja. **Đề:** mỗi người i đến giờ ti sẽ bắn người pi nếu còn sống; p là permutation, times distinct; đổi một ti và hỏi số sống cuối.

**Giải.** Permutation tạo disjoint directed cycles. Đặt si=1 iff i thực sự bắn. Với pred của i trên cycle, nếu tpred≥ti thì pred chưa thể giết i trước giờ bắn, nên si=1; nếu tpred<ti thì `si=1−spred`. Dấu ≥ cũng xử lý self-cycle. Mỗi cycle có ít nhất một reset, vì không thể times tăng strict quanh vòng. Giữa hai resets là run tăng time: s alternates 1,0,1,0,...; run length l có ceil(l/2) shots, floor(l/2) survivors. Mỗi shot giết target khác nhau vì p permutation, nên #dead=#shots.

Giữ ordered set reset boundaries cho từng cycle và tổng floor(runlen/2), bằng cyclic index distances. Đổi ti chỉ đổi status của hai directed edges pred→i và i→pi. Insert/delete boundary chia/ghép runs; trừ contribution cũ, cộng contribution mới, O(log n)/update, RAM O(n). Alternative segment tree compose weighted two-state maps (bit input→bit output, shots sum) nếu muốn tránh xử lý wrap; whole-cycle map có reset nên chọn fixed output bit rồi đọc total shots. O(n+q log n) sau dựng cycles.

**Transformation:** mô phỏng event theo time → permutation cycles → reset/toggle automaton → dynamic run contributions. **Hay: 5/5, giữ.** Cấu trúc permutation loại branching/dependencies chung; nếu hai người cùng target thì shot count không còn equals death count. **Luyện:** cycle times tăng theo index except wrap: survivors=floor(length/2); tự kiểm update tạo/xóa hai descents.

## 2014J — The Cave

**Nguồn:** PDF 134–135; PL, Jaskinia, tr.187–190. **Đề:** mỗi thám hiểm đi từ ai tới bi bằng walk dài≤di; tìm đỉnh có thể xuất hiện trong walk của **mọi** người.

**Giải.** Area i là `{x:dist(ai,x)+dist(x,bi)≤di}`, một connected subtree (path ai–bi nở bán kính floor((di−dist(ai,bi))/2)). Nếu di<dist(ai,bi) thì area rỗng, trả không. Root tại v tùy ý. Mỗi subtree có một highest vertex hi; nếu có common x, mọi hi là ancestor x. hi sâu nhất nằm trên path hj→x cho mọi j, nên cũng nằm trong mọi subtree. Vậy **một candidate** hi sâu nhất đủ để quyết định giao, không cần mark mọi area.

Có cách O(n+m) không LCA: BFS từ root v lấy dist(v,·). Khoảng cách từ v tới area i là `max(0,ceil((dist(v,ai)+dist(v,bi)−di)/2))`. Chọn i có khoảng cách lớn nhất; BFS từ ai,bi để nhận diện area i, scan tìm p∈area i gần root nhất. Cuối cùng BFS từ p và kiểm tất cả `dist(p,aj)+dist(p,bj)≤dj`. Nếu pass, output p; nếu fail, không có common vertex do lemma highest/deepest. Dùng ceil integer đúng với di parity, tổng số BFS hằng số. O(n+m), RAM O(n+m), đọc các constraints theo mỗi query group của đề.

**Transformation:** giao nhiều tree regions → tree convexity → deepest projection witness → kiểm đúng một điểm. **Hay: 5/5, giữ.** Mạnh hơn chỉ dùng Helly pairwise, vì tránh cả Θ(m²) kiểm tra. **Luyện:** generalize từ thickened paths sang bất kỳ connected subtrees: lemma còn đúng, nhưng tính projection không còn công thức distance đơn giản.

## 2014K — The Captain

**Nguồn:** PDF 136–137. **Đề:** đi giữa các cảng, thuyền trưởng chọn một trục tự điều khiển mỗi chặng, sĩ quan lái trục kia; minimize thời gian thuyền trưởng cầm lái.

**Giải.** Một chặng u→v có cost `min(|xu−xv|,|yu−yv|)` vì chọn tự lái trục có displacement nhỏ hơn; đi lùi không giảm lower bound net displacement của trục tự lái. Complete graph Θ(n²) nhưng chỉ giữ neighbors trong x-sort và y-sort. Với cạnh bất kỳ, nếu giá=|Δx|, thay bằng chain x-neighbors giữa hai điểm: mỗi edge cost≤Δx của nó, tổng≤|Δx| bằng telescoping; tương tự y. Vì sparse edges là các cạnh thật của complete graph, sparse shortest paths không rẻ giả; vì mọi dense edge có replacement không đắt hơn, cũng không mất optimum. Dijkstra O(n log n), RAM O(n), giữ zero-cost edges và ties trong sort.

**Transformation:** complete metric-like graph → sorted-neighbor chains bảo toàn shortest paths. **Hay: 5/5, giữ.** Weight min coordinate gaps không thỏa triangle inequality, nhưng replacement proof vẫn đúng; không cần metric premise. **Luyện:** weight đổi thành max(|Δx|,|Δy|) thì neighbor trick trên không có chứng minh này; tìm phản ví dụ.

## Bảng đánh giá và lựa chọn thực tế

Điểm đánh giá transformation, không chấm độ khó của đề. Ưu tiên cue tái sử dụng được, có điều kiện nhận diện rõ và không cần mang cả một chứng minh riêng vào cuộc thi.

| Bài | Điểm /5 | Bước đổi mô hình | Quyết định notebook |
|---|---:|---|---|
| 2011A — Arithmetic Rectangle | 5 | điều kiện đại số trên mọi hàng/cột → kiểm tra cửa sổ cục bộ → maximal rectangle → histogram → nearest smaller | Đã có; sửa citation rõ năm 2011 |
| 2011B — Bytean Road Race | 5 | nhiều truy vấn reachability → hai đường biên cực trị → hai cây có thứ tự | Khảo sát: nhiều điều kiện embedding, cue riêng dài |
| 2011C — Will It Stop? | 4 | mô phỏng không có cận dừng → tập trạng thái bất biến không chứa đích | Khảo sát: luyện invariant, bit test quen thuộc |
| 2011D — Ants | 4 | động học trên cây → contour 1D + độ cao → phương trình affine theo từng cạnh | Khảo sát: động học contour riêng |
| 2011E — Gophers | 5 | dynamic interval union coverage → phần đóng góp riêng phụ thuộc predecessor/successor | Đã thêm cue mới |
| 2011F — Laundry | 3 | phân phối tài nguyên → xử lý yêu cầu khó trước + smallest adequate capacity + exchange giữa một gói/cặp gói | Không thêm: exchange greedy quen thuộc |
| 2011G — Bits Generator | 5 | thử từng seed → so sánh các chuỗi xác định trên functional graph; hoặc đảo hướng pattern để đi từ gốc xuống cây | Khảo sát: functional-graph/string algorithm |
| 2011H — Afternoon Tea | 5 | tính tổng quá trình → bảo toàn lượng (input−residue) → so sánh bằng cận phần dư; khi hòa thì dùng đóng góp lớn nhất | Khảo sát: conservation hay, luật game riêng |
| 2011I — Intelligence Quotient | 5 | maximum weighted clique trong co-bipartite graph → complement **hai phía** → weighted vertex cover → min-cut | Gộp hướng conflict graph/min-cut đã có |
| 2011J — Cave | 5 | bài phân hoạch cây global → đếm các cạnh có subtree residue bằng 0 → histogram/divisor sieve | Đã thêm cue mới |
| 2011K — Cross Spider | 3 | kiểm tra cấu hình hình học toàn cục → dựng một cơ sở nhỏ + kiểm tra membership bằng determinant | Không thêm: cross/dot đã có |
| 2012A — Vending Machine | 5 | lịch thực hiện thuận → kế hoạch ngược → ảnh hưởng của cả lịch chỉ còn **số lần mua** → DP nhỏ | Đã thêm cue mới |
| 2012B — Bus Trip | 4 | longest path trên DAG dày + Manhattan → bốn extrema tuyến tính | Đã thêm cue mới |
| 2012C — Sequence | 4 | nhiều ràng buộc overlapping windows → lấy hiệu/XOR → lớp đồng dư + một ràng buộc global | Đã thêm cue mới |
| 2012D — DNA | 4 | tối ưu trên toàn bộ chuỗi → lower bound bằng pigeonhole + nghiệm đạt bound | Khảo sát: luyện lower-bound witness |
| 2012E — Evaluation of an Expression | 5 | phân phối của biểu thức → convolution trên nhóm cộng; nhóm nhân hữu hạn → log cơ số primitive root → convolution trên nhóm cộng khác | Đã thêm cue mới |
| 2012F — Formula One | 5 | tồn tại lịch swap rất dài → capacity inequalities → một constraint critical chi phối mọi constraint còn lại | Khảo sát: theorem hay, công thức riêng |
| 2012G — Save the Dinosaurs | 5 | định lượng “mọi hướng / tồn tại lính” → separating hyperplane → convex hull → tangent update | Khảo sát: luyện hull/tangent |
| 2012H — Hydra | 5 | sinh nhánh đệ quy có cycle → shortest derivation trên AND hypergraph → Dijkstra với counters | Đã thêm cue mới |
| 2012I — Inversions | 4 | connected components trên permutation graph dày → ranh giới không có inversion → prefix certificates | Khảo sát: prefix certificate cho permutation |
| 2012J — Do It Tomorrow | 3 | tối ưu lịch permutation → exchange để cố định thứ tự → min slack của prefixes | Không thêm: EDF + slack cơ bản |
| 2012K — Rabbits | 5 | mô phỏng đẩy thỏ phụ thuộc thứ tự → chứng minh normal form → objective local radius 1 → cycle DP | Đã thêm cue mới |
| 2013A — The Motorway | 5 | tồn tại offset và khoảng cách → khử một biến bằng giao interval → convex envelope → hai biên feasible | Khảo sát: envelopes, feasible có hai biên |
| 2013B — Bytehattan | 5 | online deletions connectivity → planar dual additions connectivity | Đã thêm cue mới |
| 2013C — The Carpenter | 5 | hai vùng cắt không giao nhau → separating axis → extrema của projections, tránh so sánh mọi cặp | Khảo sát: separating-axis/grid DP |
| 2013D — Demonstrations | 5 | thử mọi cặp xóa → chỉ coverage multiplicity≤2 có ảnh hưởng → sparse pair interactions | Đã thêm cue mới |
| 2013E — The Exam | 3 | tồn tại permutation với bound từng cạnh → obstruction tại phần tử trung tâm + interleave hai nửa đạt bound | Không thêm: construction riêng |
| 2013F — Speed Cameras | 5 | ràng buộc trên mọi tree paths → exchange về biên → peel layers, giảm budget 2 mỗi lớp | Đã thêm cue mới |
| 2013G — Marbles | 5 | tích khổng lồ → prime-exponent vector + cardinality → bounded imbalance kernel | Khảo sát: bound 6 cần theorem riêng |
| 2013H — The Hero | 5 | time-dependent routes → interval states → split relaxation thành một partial interval và các globally final-at-start intervals | Đã thêm cue mới |
| 2013I — Genetic Engineering | 4 | lexicographic greedy dễ mất longest → suffix-optimum feasibility certificates → greedy chỉ trên lựa chọn còn khả năng hoàn tất | Khảo sát: lex reconstruction có certificate |
| 2013J — Jánošík | 4 | branching process → closed form theo highest power of two → gom đoạn quotient/log cố định | Gộp hướng grouping/closed-form |
| 2013K — Blankets | 5 | tổng Θ(n²) pair intersections → đổi thứ tự sum/integral → polynomial moments của coverage | Đã thêm cue mới |
| 2014A — The Lawyer | 2 | tìm cặp intervals trong mỗi bucket → hai extrema | Không thêm: hai extrema cơ bản |
| 2014B — Petrol | 5 | resource-constrained path với refuel → nearest-source distance potentials → threshold connectivity | Đã thêm cue mới |
| 2014C — The Prices | 5 | chọn cả bundle ở một kho → thêm cờ “đã mở kho” → thêm sản phẩm đơn lẻ | Đã thêm cue mới |
| 2014D — Divisors | 2 | pairwise divisibility → value frequencies + multiples sieve | Không thêm: multiples sieve đã có |
| 2014E — Euclidean Nim | 4 | infinite cyclic game → invariant residue → forced-move trap region → arithmetic progression modulo q−p | Khảo sát: chứng minh forced-region; bốn case riêng |
| 2014F — Pillars | 5 | Hamilton cycle khó → cycle cover bằng finite local templates → spanning tree splicing | Đã thêm cue mới |
| 2014G — Global Warming | 5 | subarray property không hereditary → fix unique extremum → forbidden boundaries → chỉ hai candidates quanh occurrences của extremum kia | Đã thêm cue mới |
| 2014H — Hit of the Season | 5 | overlapping printing → partial-word cover + maximum occurrence gap → split short/long regimes → symmetry giảm exponent từ k xuống k/2 | Đã thêm cue mới |
| 2014I — The Staging | 5 | mô phỏng event theo time → permutation cycles → reset/toggle automaton → dynamic run contributions | Đã thêm cue mới |
| 2014J — The Cave | 5 | giao nhiều tree regions → tree convexity → deepest projection witness → kiểm đúng một điểm | Đã thêm cue mới |
| 2014K — The Captain | 5 | complete metric-like graph → sorted-neighbor chains bảo toàn shortest paths | Đã thêm cue mới |

## Bài luyện nên làm theo thứ tự

1. **Sequence (2012C):** lấy hiệu hai windows, chứng minh chiều đảo; tự tìm residue classes trước khi viết DP.
2. **Vending Machine (2012A):** tách execution order và planning order; bắt lỗi cap số lần mua một loại bằng ví dụ trong mục A.
3. **Demonstrations (2013D):** dựng gain bằng coverage 1/2; chứng minh số pair interactions chỉ tuyến tính.
4. **Hydra (2012H):** thử duplicate children và cycle; viết invariant finalization cho AND-Dijkstra.
5. **Bytehattan (2013B):** vẽ dual gồm mặt ngoài rồi xử lý chuỗi xóa, không dùng time reversal.
6. **Speed Cameras (2013F):** chứng minh exchange về lá rồi residual budget−2; so cây đường và cây sao.
7. **The Cave (2014J):** chứng minh deepest projection lemma trước khi dùng walk-budget formula.
8. **Petrol (2014B):** chứng minh hai chiều reweighting; chiều sufficient cần detours tới nearest stations.
9. **Hit of the Season (2014H):** giải riêng L≥n/2, rồi dùng reverse chọn phía ít wildcard cho L≤n/2.
10. **Formula One (2012F), Marbles (2013G):** luyện chứng minh, tách điều kiện cần/đủ và bound được chứng minh/được test.

## Kiểm chứng và giới hạn

Chạy `python3 material/lfac2_checks.py` từ root repo, chỉ cần standard library. Seed cố định 20261007. Đã qua **20,886 đối chiếu** và ba finite cycle templates:

| Nhóm | Oracle độc lập / phạm vi | Số đối chiếu |
|---|---|---:|
| 2012A | Search mọi mua hợp lệ trên vector tồn kho nhỏ vs reverse-planning DP | 150 |
| 2012F | Mọi bounded swap histories n=2..5 vs critical inequality | 660 |
| 2012K | Mọi ordered shot sequences, k dưới all-clear threshold, n=3..7 vs normal form | 108 |
| 2013F | Mọi subsets trên mọi increasing-parent trees n≤7 vs leaf peeling; feasibility và optimum | 5,913 |
| 2013G | Chia viên rồi nhân integer chính xác vs exponent equations; counts≤2 | 125 |
| 2013I | Mọi subsequences n≤10 vs certified lex reconstruction | 180 |
| 2014C | Mọi product-to-shop assignments nhỏ vs incremental open DP | 150 |
| 2014E | Retrograde game có draws, steps≤8 và pile≤30 vs arithmetic cases | 1,920 |
| 2014G | Mọi array alphabet 3, n≤8, và mọi subarray vs two-candidate reduction | 9,840 |
| 2014I | Chronological shooting trên random permutations/times n≤6 vs runs | 720 |
| 2014J | Explicit intersection các tree regions nhỏ vs deepest projection witness | 300 |
| 2014K | Floyd complete graph vs Floyd sorted-neighbor graph trên points nhỏ, có ties | 220 |
| 2012E | Direct multiplication histogram vs primitive-root index convolution; thêm sample polynomial | 150 |
| 2013D | Xóa mọi cặp intervals vs sparse coverage gain | 160 |
| 2014B | Complete station-distance connectivity ở 19 thresholds mỗi graph vs reweighted roads | 150 graphs |
| 2014H | Mọi RGB stamps với n≤7 vs short/long split và phía ít wildcard | 140 |
| 2014F | Hamilton cycle và mọi required boundary-pair edges trong templates 4×4,4×6,6×4 | 3 templates |

Số 20,886 đếm từng input/array/vector/game so sánh như script báo, không đếm lại từng threshold Petrol hay từng subset/path bên trong oracle. Đây là kiểm chứng nhỏ của phép biến đổi, **không** là 44 programs AC, không benchmark tối đa, không tái lập toàn bộ computer-assisted proof cho bound 6 của Marbles, và không test full-size geometric tangent/parser/convolution implementations. Marbles dựa vào theorem có chứng minh trong nguồn; Carpenter ghi rõ lời giải tái dựng O(nm log min(n,m)), không nhận nhầm bound O(nm) của editorial.

Nguồn bổ sung chính thức: [trang sách tiếng Anh của tác giả](https://www.algonotes.com/en/looking-for-a-challenge-2/), [trang bản gốc tiếng Ba Lan](https://www.algonotes.com/pl/looking-for-a-challenge-2/). Các mục tóm tắt và diễn giải thuật toán, không sao chép nguyên đề/editorial.

Notebook đã build bằng `latexmk -pdf -interaction=nonstopmode -halt-on-error main.tex`: **23 trang**, các cue LFAC2 nằm ở trang 22. Đã kiểm tra ảnh trang để bảo đảm không cắt mất nội dung hay tràn sang cột.
