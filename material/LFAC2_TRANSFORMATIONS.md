# Looking for a Challenge 2 — 44 transformation, bản ngắn

Mỗi bài giữ **đề → bước đổi mô hình/ý giải → đánh giá**. Điểm /5 chấm độ bất ngờ và khả năng tái sử dụng; không chấm độ khó. “Đã thêm” chỉ cue thực tế trong notebook.

Nguồn: [PDF tiếng Anh](Lookingforachallenge2.pdf); các trang bên dưới là thứ tự trang file. Lời giải, chứng minh, bài luyện và đối chiếu nguồn: [bản chi tiết](LFAC2_DETAILS.md).

## 2011A — Arithmetic Rectangle

**Đề:** tìm hình chữ nhật lớn nhất mà từng hàng và từng cột là cấp số cộng. *(PDF 17–22)*

**Ý chốt:** Điều kiện cấp số cộng → cửa sổ 3×3 hợp lệ → bảng boolean → histogram. Vùng tâm h×w cho diện tích (h+2)(w+2), không phải hw; xử lý riêng cạnh 1 hoặc 2. O(nm).

**5/5:** Chuỗi giảm bài toán rõ; đổi objective là điểm dễ sai. Cue đã có.

## 2011B — Bytean Road Race

**Đề:** đường phố phẳng, chỉ đi đông/nam; mọi đỉnh nằm trên một tuyến s→t. Với từng cặp p,q, có tuyến s→t qua cả hai không? *(PDF 23–29)*

**Ý chốt:** Reachability phẳng, đơn điệu → hai đường biên trái/phải. Điểm q tới được từ p iff nằm giữa hai biên tại độ cao q. Binary lifting cho O(log n)/query; hai cây successor có thứ tự còn cho O(1)/query.

**5/5:** Hay nhưng cần đúng embedding và mọi đỉnh nằm trên tuyến s→t. Giữ ở khảo sát.

## 2011C — Will It Stop?

**Đề:** n chẵn thì chia 2, n lẻ thì thay bằng 3n+3; hỏi có về 1 không. *(PDF 30–32)*

**Ý chốt:** Mô phỏng → tập bất biến. Bỏ hết thừa số 2: còn 1 thì dừng; còn số lẻ >1 thì bước kế tạo bội 3, về sau luôn là bội 3 nên không tới 1. Đáp án iff n là power of two.

**4/5:** Mẫu tìm tập đóng không chứa đích, thay mô phỏng vô hạn. Giữ ở khảo sát.

## 2011D — Ants

**Đề:** hai kiến đi quanh contour cây, tốc độ lên/xuống khác nhau, gặp nhau thì quay đầu; input rất lớn so với RAM. Tìm lần gặp thứ hai. *(PDF 33–36)*

**Ý chốt:** Chuyển động trên cây → contour với tổng quãng đường a và độ cao k. Quãng lên/xuống là (a±k)/2, nên thời gian affine theo từng cạnh; giải phương trình hai lần gặp bằng một lượt đọc. O(n), RAM O(1).

**4/5:** Đổi tọa độ tốt; các công thức tốc độ riêng để ở bản chi tiết. Giữ ở khảo sát.

## 2011E — Gophers

**Đề:** các điểm cố định bị phủ bởi các đoạn [x−l,x+l] cùng độ dài; di chuyển một đoạn, hỏi số điểm trong hợp. *(PDF 37–39)*

**Ý chốt:** Union động → đóng góp riêng của một đoạn. Với hai tâm hàng xóm p<x<q, phần chỉ x phủ là [max(x−l,p+l+1),min(x+l,q−l−1)]. Binary search đếm điểm; di chuyển=xóa+thêm.

**5/5:** Chỉ hai hàng xóm đủ nhờ các đoạn cùng độ dài. Đã thêm cue.

## 2011F — Laundry

**Đề:** người i cần 2di kẹp cho tất và 3di cho áo; mỗi loại cùng màu, màu không được dùng giữa hai người; ít màu nhất. *(PDF 40–43)*

**Ý chốt:** Phân phối màu → greedy exchange. Xử lý nhu cầu d giảm dần; lấy màu nhỏ nhất đủ 5d nếu có, nếu không lấy hai màu nhỏ nhất đủ 3d và 2d. Multiset cho O((n+k)log k), ngoài sorting.

**3/5:** Exchange hữu ích nhưng ít cấu trúc mới để thêm riêng. Giữ ở khảo sát.

## 2011G — Bits Generator

**Đề:** chuyển seed z theo hàm f cố định, xuất một bit sau mỗi lần chuyển; đếm seed tạo pattern n bit. *(PDF 44–49)*

**Ý chốt:** Thử từng seed → so chuỗi trên functional graph. Doubling nén rank của hai nửa; so prefix/suffix dài 2^floor(log2 n) với pattern. O((m+n)log n), RAM O(m+n); deterministic, không cần hash.

**5/5:** Đổi mô hình mạnh; KMP trên cây không tự có cận tuyến tính. Giữ ở khảo sát.

## 2011H — Afternoon Tea

**Đề:** uống nửa cốc rồi thêm trà/sữa theo một chuỗi; ban đầu tỉ lệ 1:1. Hỏi đã uống loại nào nhiều hơn. *(PDF 50–52)*

**Ý chốt:** Tổng đã uống → tổng đã thêm−phần còn. Bỏ lần thêm cuối; số lần thêm lệch thì loại được thêm nhiều hơn thắng. Nếu hòa, loại đối diện lần thêm áp chót được uống nhiều hơn; n=1 hòa. O(n).

**5/5:** Phần chính nguyên trội correction bị chặn; chỉ xét correction khi hòa. Giữ ở khảo sát.

## 2011I — Intelligence Quotient

**Đề:** hai nhóm đều quen nhau nội bộ; chọn nhóm tất cả quen nhau, tổng trọng số lớn nhất. *(PDF 53–58)*

**Ý chốt:** Weighted clique → đồ thị xung đột bipartite → weighted vertex cover → min-cut. Capacity s→L và R→t là trọng số, cạnh xung đột dùng INF>Σw. Đáp án Σw−mincut.

**5/5:** Mở rộng conflict matching sang trọng số; không dùng matching cardinality. Giữ ở khảo sát.

## 2011J — Cave

**Đề:** chia cây n đỉnh thành các thành phần liên thông cùng số đỉnh; xuất mọi số nhóm khả thi. *(PDF 59–62)*

**Ý chốt:** Chia cây thành nhóm size k → subtree residues. Với k|n, khả thi iff đúng n/k−1 cạnh có subtree size chia hết k. Cắt hết các cạnh ấy; histogram sizes và cộng multiples cho mọi divisor.

**5/5:** Biến partition global thành đếm cạnh, có chứng minh hai chiều. Đã thêm cue.

## 2011K — Cross Spider

**Đề:** n điểm 3D có cùng nằm trên một mặt phẳng không. *(PDF 63–65)*

**Ý chốt:** Coplanarity → cơ sở nhỏ. Tìm ba điểm không thẳng hàng, lấy pháp tuyến N; kiểm N·(p−p0)=0 cho mọi điểm. Nếu không có ba điểm ấy thì tất cả thẳng hàng. O(n), dùng int128.

**3/5:** Mẫu basis rồi validate; cross/dot đã quen thuộc. Giữ ở khảo sát.

## 2012A — Vending Machine

**Đề:** mua loại i nhận thêm một thanh mỗi loại j<i còn hàng; budget k, giá và tồn kho ≤40, tối đa hóa tổng giá trị nhận. *(PDF 69–70)*

**Ý chốt:** Lịch thực hiện tăng chỉ số → lập kế hoạch giảm chỉ số. State chỉ cần số t lần mua loại cao và budget; chọn x≤li, nhận giá trị ci·min(li,t+x). Cap tổng lần mua ở L=max li, tiền ở min(k,L·max ci).

**5/5:** Hai thứ tự khác vai trò; không được cap x bởi li−t. Đã thêm cue.

## 2012B — Bus Trip

**Đề:** ghé các điểm có attractiveness tăng nghiêm ngặt; thu phí Manhattan giữa điểm, cộng giá trị của từng điểm; tối đa doanh thu. *(PDF 71–72)*

**Ý chốt:** DAG dày + Manhattan → bốn extrema dp(p)+sx·xp+sy·yp. Sort attractiveness, query bốn dấu rồi cộng reward. Các điểm cùng attractiveness query cả nhóm trước khi update. O(Nlog N).

**4/5:** Loại Θ(N²) cạnh bằng tuyến tính hóa metric; cần batch ties. Đã thêm cue.

## 2012C — Sequence

**Đề:** đổi ít phần tử nhất để mọi đoạn dài k có tổng chẵn. *(PDF 73)*

**Ý chốt:** XOR hai cửa sổ k liên tiếp → bi=b(i+k). Mỗi lớp mod k chọn một parity; chọn majority để ít đổi nhất. Nếu XOR k lựa chọn sai, đổi lớp có chênh cost nhỏ nhất. O(n+k).

**4/5:** Lấy hiệu các ràng buộc overlapping để lộ tính tuần hoàn. Đã thêm cue.

## 2012D — DNA

**Đề:** chọn chuỗi độ dài n trên A,C,G,T có LCS với chuỗi đã cho nhỏ nhất. *(PDF 74–75)*

**Ý chốt:** Tìm chuỗi → lower bound đạt được. Gọi m là tần suất ký tự ít nhất trong S; pigeonhole cho mọi Y có LCS≥m. Chọn Y lặp đúng ký tự ấy thì LCS=m. O(n).

**4/5:** Một chứng chỉ cực trị thay cả LCS DP. Giữ ở khảo sát.

## 2012E — Evaluation of an Expression

**Đề:** đếm assignment để biểu thức +,×,^k bằng 0 modulo prime p, đáp án modulo 30011; mỗi biến xuất hiện tối đa một lần. *(PDF 76–77)*

**Ý chốt:** Cây biểu thức → histogram residues. Addition là convolution mod p; multiplication nonzero đổi residue thành exponent của primitive root, rồi convolution mod p−1. Xử lý 0 riêng; output histogram gốc tại 0. O(s·p log p).

**5/5:** Đổi phép nhân thành cộng; chỉ độc lập vì biến không lặp. Counting modulus là 30011. Đã thêm cue.

## 2012F — Formula One

**Đề:** các xe ban đầu theo thứ tự 1..n; một lần vượt là swap hai xe kề nhau; xe i phải vượt đúng ai lần. Hỏi có lịch hợp lệ không. *(PDF 78–79)*

**Ý chốt:** Lịch swap → capacity từng xe → một xe critical. Đặt Ak=Σ(i<k)(ai+1); Bk là capacity từ phía sau sau khi trừ blockers. Chỉ kiểm am≤Am+Bm tại m cuối có am≥Am; các xe khác tự thỏa. O(n).

**5/5:** Rất hay nhưng tính đủ cần chứng minh riêng, không đoán từ tổng ai. Giữ ở khảo sát.

## 2012G — Save the Dinosaurs

**Đề:** một điểm an toàn nếu mọi hướng chạy từ đó đều đến gần ít nhất một lính; thêm một lính độc lập cho từng query, tính diện tích an toàn. *(PDF 80–81)*

**Ý chốt:** “Mọi hướng có lính đến gần hơn” → separating line → interior convex hull. Dựng hull; query ngoài hull thay visible chain bằng hai tangent và tính area bằng shoelace prefix sums. O(log h)/query, queries độc lập.

**5/5:** Biến lượng từ về hướng thành điều kiện hình học chuẩn. Giữ ở khảo sát.

## 2012H — Hydra

**Đề:** giết vĩnh viễn đầu loại i giá zi, hoặc chặt giá ui sinh một multiset đầu con; có cycle loại đầu, tìm giá diệt hết một đầu ban đầu. *(PDF 82–83)*

**Ý chốt:** Sinh nhiều đầu con → AND-hypergraph Dijkstra. Khởi tạo cost giết vĩnh viễn zi; production ui+ΣCcon chỉ relax khi mọi occurrence con đã final. Counter và reverse incidences xử lý cả cycles, duplicate children.

**5/5:** Positive ui bảo đảm cha đắt hơn con; không unfold cây vô hạn. Đã thêm cue.

## 2012I — Inversions

**Đề:** đồ thị hoán vị nối hai giá trị tạo inversion; xuất các connected components. *(PDF 84–85)*

**Ý chốt:** Inversion graph dày → prefix cuts. Trong permutation 1..n, cut sau i không có cạnh qua iff max(a1..ai)=i. Các blocks giữa cut là components. Scan O(n), không dựng inversion edges.

**4/5:** Prefix certificate thay đồ thị Θ(n²); cần permutation. Giữ ở khảo sát.

## 2012J — Do It Tomorrow

**Đề:** mỗi công việc có duration và deadline; bắt đầu muộn nhất nhưng vẫn hoàn tất tất cả, bảo đảm có nghiệm. *(PDF 86–87)*

**Ý chốt:** Lịch tùy ý → deadline tăng bằng exchange. Với prefix duration Di, bắt đầu muộn nhất là min_i(ti−Di); không cần idle giữa jobs. O(nlog n).

**3/5:** EDF và prefix slack quen thuộc, giữ làm bài luyện. Giữ ở khảo sát.

## 2012K — Rabbits

**Đề:** thỏ trên vòng n luống; bắn luống i xua hết thỏ tại i, thỏ ở hai hàng xóm nhảy ra xa i; k phát để xua nhiều nhất. *(PDF 88–89)*

**Ý chốt:** Đẩy thỏ phụ thuộc lịch → normal form bắn không kề nhau. Khi k<ceil(n/2), luống i sạch iff bắn i hoặc cả hai hàng xóm. DP vòng giữ hai bits và số phát: O(nk). Nếu k≥ceil(n/2), xua hết.

**5/5:** Phải chứng minh normal form trước khi bỏ thứ tự hành động. Đã thêm cue.

## 2013A — The Motorway

**Đề:** đặt n+1 trạm cách đều L, xen kẽ n lối vào ai đã sort; tìm cả L nhỏ nhất và lớn nhất. *(PDF 93–94)*

**Ý chốt:** Offset b và spacing L → giao intervals cho b. Feasible iff F(L)=max(ai−iL)−min(ai−(i−1)L)≤0. F convex: tìm minimum, rồi binary search hai biên feasible.

**5/5:** Feasible là interval, không phải predicate monotone trên toàn miền. Giữ ở khảo sát.

## 2013B — Bytehattan

**Đề:** xóa lần lượt đường của grid thành phố, query hai đầu đường còn kết nối không; input tiếp theo phụ thuộc đáp án trước. *(PDF 95–96)*

**Ý chốt:** Xóa cạnh primal online → thêm cạnh dual. DSU trên faces, gồm mặt ngoài: nếu hai faces đã cùng component thì cạnh là bridge; nếu khác thì union. O(α(n²))/query sau khởi tạo.

**5/5:** Duality thay time reversal khi input adaptive. Đã thêm cue.

## 2013C — The Carpenter

**Đề:** cắt hai tam giác từ bảng màu để ghép thành bàn cờ vuông lớn nhất; hai phần cắt không chồng interior. *(PDF 97–98)*

**Ý chốt:** Hai tam giác không giao → separating axes x,y,x+y,x−y. DP cho maximal checkerboard triangles bốn hướng. Với L cố định, extrema projections theo màu corner tìm cặp rời nhau; binary search L. O(nm log min(n,m)).

**5/5:** Tránh thử mọi cặp; phải dùng đỉnh hình học và cho phép chạm biên. Giữ ở khảo sát.

## 2013D — Demonstrations

**Đề:** hủy tối đa hai cuộc biểu tình, mỗi cuộc chặn một interval, để tổng chiều dài đường còn bị chặn nhỏ nhất. *(PDF 99–100)*

**Ý chốt:** Thử mọi cặp hủy → coverage layers 1/2. Sweep lấy ui=phần chỉ i phủ, wij=phần chỉ i,j phủ. Gain=ui+uj+wij; chỉ O(n) pairs có wij>0. O(nlog n).

**5/5:** Tương tác sparse dù số cặp đối tượng là Θ(n²). Đã thêm cue.

## 2013E — The Exam

**Đề:** permutation 1..n với mọi adjacent difference≥k. *(PDF 101–102)*

**Ý chốt:** Permutation constraints → obstruction ở số trung tâm + interleave hai nửa. Với n>1, tồn tại iff k≤floor(n/2); constructions đạt gap floor(n/2) hoặc lớn hơn. O(n).

**3/5:** Construction đẹp nhưng khá riêng; n=1 không có ràng buộc cạnh. Giữ ở khảo sát.

## 2013F — Speed Cameras

**Đề:** đặt nhiều camera trên đỉnh cây nhất, mỗi simple path đi qua ≤k camera. *(PDF 103–104)*

**Ý chốt:** Quota trên mọi tree paths → exchange về lá → peel layers. Chọn tất cả lá, bỏ chúng và giảm k đi 2. Chọn floor(k/2) lớp; k lẻ thêm một đỉnh còn lại. O(n).

**5/5:** Greedy có chứng minh thay tree DP n×k. Đã thêm cue.

## 2013G — Marbles

**Đề:** hai người rút luân phiên, cùng số viên; counts các chữ số 0..9 có thể 10^15; hỏi có cách chia cho hai tích bằng nhau. *(PDF 105–106)*

**Ý chốt:** Tích bằng nhau → exponent 2/3 và cùng số viên. Xử lý 0,5,7 riêng; đặt di=ai−bi, giải ba phương trình tuyến tính. Theorem nguồn cho |di|≤6; enumerate bốn biến, suy ba biến còn lại: ≤7^4 cases.

**5/5:** Kernel rất hay; bound 6 có computer-assisted proof, chưa tái lập certificate ở repo. Giữ ở khảo sát.

## 2013H — The Hero

**Đề:** đi tàu trên directed graph; đảo có khoảng ngày bật bẫy, không được ở trên đảo lúc đó; được chờ khi an toàn; outdegree≤10. *(PDF 107–108)*

**Ý chốt:** Đảo có traps → state (đảo,safe interval). Từ t trong [L,R], chuyến d tới được [t+d,R+d]. Relax interval chứa đầu trái; các interval sau tới đúng start nên chỉ xử lý một lần. Dijkstra + ordered intervals.

**5/5:** Earliest arrival chỉ dominates trong cùng safe interval; outdegree≤10 là điều kiện complexity. Đã thêm cue.

## 2013I — Genetic Engineering

**Đề:** longest subsequence ghép từ blocks k ký tự giống nhau; trong các longest chọn lexicographically nhỏ nhất. *(PDF 109–110)*

**Ý chốt:** Lex greedy → suffix-optimum certificate. e[i] là occurrence thứ k từ i; dp[i]=max(dp[i+1],1+dp[e[i]+1]). Chọn ký tự nhỏ nhất còn giữ đủ số blocks, tie lấy occurrence sớm nhất.

**4/5:** Giữ longest trước rồi mới tối ưu lex; greedy hoàn tất block sớm có thể sai lex. Giữ ở khảo sát.

## 2013J — Jánošík

**Đề:** một hộp i xu; chẵn chia đôi, lẻ>1 lấy một xu rồi xử lý tiếp; hộp một xu đem cho; tính xu giữ khi ban đầu có các hộp 1..n. *(PDF 111–112)*

**Ý chốt:** Recursive splitting → f(i)=i−2^floor(log2 i). Tổng f(1..n) bằng arithmetic sums trên các dyadic blocks. O(log n), không mô phỏng phân nhánh.

**4/5:** Nhận closed form rồi nhóm các đoạn cùng highest bit. Giữ ở khảo sát.

## 2013K — Blankets

**Đề:** hình chữ nhật axis-aligned; kỳ vọng diện tích giao của một cặp được chọn đều. *(PDF 113–114)*

**Ý chốt:** Tổng pair intersections → tích phân choose(coverage,2). Sweep x; range-add trên y giữ ∫c và ∫c². Slab góp dx·(S2−S1)/2, cuối chia choose(n,2). O(nlog n), accumulate int128.

**5/5:** Đổi thứ tự sum/integral; dùng geometric lengths, không số indices. Đã thêm cue.

## 2014A — The Lawyer

**Đề:** chọn ngày có hai khách với giờ gặp không giao nhau, xuất IDs. *(PDF 117–118)*

**Ý chốt:** Tìm hai intervals rời → minimum end và maximum start mỗi ngày. Có cặp iff end<start. O(n+m).

**2/5:** Hai extrema đủ; quá cơ bản để thêm cue riêng. Giữ ở khảo sát.

## 2014B — Petrol

**Đề:** queries giữa hai trạm xăng, xe có capacity b; route được refuel tại các trạm, hỏi có đi được không. *(PDF 119–120)*

**Ý chốt:** Refueling → nearest-station edge reweighting. Multi-source Dijkstra lấy dS; đổi cạnh thành dS(u)+w+dS(v). Capacity b khả thi iff kết nối bằng các cạnh mới≤b. Sort queries + DSU.

**5/5:** Không cần fuel states hay all-pairs giữa trạm; chiều đủ dùng station detours. Đã thêm cue.

## 2014C — The Prices

**Đề:** mua m≤16 sản phẩm ở n≤100 kho; mỗi kho có opening/travel cost di, giá cij; minimize tổng. *(PDF 121–122)*

**Ý chốt:** Chọn bundle ở kho → state đã mở kho. Mỗi kho seed open[mask]=old[mask]+di, rồi thêm từng sản phẩm vào open; new=min(old,open). O(nm2^m), RAM O(2^m).

**5/5:** Thêm state để giảm branching; opening cost trả đúng một lần. Đã thêm cue.

## 2014D — Divisors

**Đề:** đếm ordered pairs i≠j với ai chia aj, ai≤U=10^6. *(PDF 123)*

**Ý chốt:** Divisibility pairs → frequencies và multiples sieve. Ans=Σd freq[d]·Σk freq[kd]−n, loại self-pairs nhưng giữ duplicate indices. O(n+Ulog U), int64.

**2/5:** Mẫu sieve đã có; điểm dễ sai là ordered pairs và multiplicities. Giữ ở khảo sát.

## 2014E — Euclidean Nim

**Đề:** người có step p phải bỏ một positive multiple p nếu pile≥p, nếu không phải thêm p; người kia step q; ai làm pile 0 thắng, có thể chơi vô hạn. *(PDF 124–125)*

**Ý chốt:** Game vô hạn → invariant n mod gcd(p,q), rồi forced-add region. Residue khác 0 thì hòa; còn lại scale gcd và phân biệt step nhỏ/lớn. Các nước bị ép rút về modulo q−p; bốn cases ở bản chi tiết.

**4/5:** Trap region biến game cyclic thành số học; không suy winner chỉ từ gcd. Giữ ở khảo sát.

## 2014F — Pillars

**Đề:** đi một cycle qua mọi grid cell còn trống đúng một lần; rectangle dimensions chẵn, holes là các pillars 2×2 tách nhau đủ xa và xa biên. *(PDF 126–127)*

**Ý chốt:** Hamilton cycle → local cycle cover → spanning-tree splicing. Holes cách xa cho patches 2×2/4×4/4×6/6×4; mỗi patch có cycle template. Nối các cycles theo cây adjacency bằng đổi hai cạnh boundary. O(nm+f).

**5/5:** Construction mạnh, cần separation và boundary ports hợp lệ. Đã thêm cue.

## 2014G — Global Warming

**Đề:** longest contiguous subarray mà minimum và maximum đều xuất hiện đúng một lần, ties chọn start sớm nhất. *(PDF 128–129)*

**Ý chốt:** Subarray không hereditary → fix unique minimum i. Nearest values≤ai khóa hai biên; longest candidate phải chứa một occurrence của maximum bên trong. Chỉ thử nearest maximum trái/phải và mở tới occurrence kế. O(nlog n).

**5/5:** Hai candidates thay mọi intervals; sliding window thường không đúng. Đã thêm cue.

## 2014H — Hit of the Season

**Đề:** tìm stamp RGB ngắn nhất phủ cả partial word có ≤19 wildcard; chồng stamp được phép, fixed letters phải khớp, wildcard cho phép các màu chồng khác nhau. *(PDF 130–131)*

**Ý chốt:** Partial-word cover → tách L ngắn/dài. L≥n/2 chỉ cần prefix/suffix compatible. L≤n/2 chọn phía ít wildcard, ≤floor(k/2), rồi enumerate completions; occurrence starts phủ iff max gap≤L. O(n²+n·3^floor(k/2)).

**5/5:** Đối xứng giảm nửa exponent; wildcard compatibility không transitive. Đã thêm cue.

## 2014I — The Staging

**Đề:** mỗi người i đến giờ ti sẽ bắn người pi nếu còn sống; p là permutation, times distinct; đổi một ti và hỏi số sống cuối. *(PDF 132–133)*

**Ý chốt:** Permutation events → cycles → increasing-time runs. Sau mỗi descent, shooting reset rồi alternates; run dài l để floor(l/2) người sống. Đổi ti chỉ ảnh hưởng hai boundaries; ordered set split/merge runs O(log n).

**5/5:** Mô phỏng global biến thành local updates; self-cycle luôn chết. Đã thêm cue.

## 2014J — The Cave

**Đề:** mỗi thám hiểm đi từ ai tới bi bằng walk dài≤di; tìm đỉnh có thể xuất hiện trong walk của **mọi** người. *(PDF 134–135)*

**Ý chốt:** Giao connected tree regions → một witness. Root tùy ý; lấy deepest highest vertex của các regions, rồi kiểm nó thuộc tất cả. Walk budget định nghĩa dist(a,x)+dist(x,b)≤d; distance-to-region cho cách O(n+m).

**5/5:** Tree convexity loại cả việc thử mọi đỉnh lẫn mọi cặp vùng. Đã thêm cue.

## 2014K — The Captain

**Đề:** đi giữa các cảng, thuyền trưởng chọn một trục tự điều khiển mỗi chặng, sĩ quan lái trục kia; minimize thời gian thuyền trưởng cầm lái. *(PDF 136–137)*

**Ý chốt:** Complete graph cost min(|Δx|,|Δy|) → neighbors trong x/y-sort. Mỗi cạnh bị bỏ thay bằng neighbor chain không đắt hơn nhờ telescoping. Dijkstra trên O(n) cạnh: O(nlog n).

**5/5:** Sparsification bảo toàn shortest paths; không cần triangle inequality. Đã thêm cue.

## Kiểm chứng

[Script kiểm tra](lfac2_checks.py): **20.886 đối chiếu nhỏ + 3 cycle templates** đã qua. Phạm vi từng oracle nằm trong [bản chi tiết](LFAC2_DETAILS.md#kiểm-chứng-và-giới-hạn); chưa phải 44 submissions AC, và không thay computer-assisted proof của Marbles.

Notebook đã thêm **21 cue mới**, ngoài Arithmetic Rectangle; PDF build thành công, **23 trang**.
