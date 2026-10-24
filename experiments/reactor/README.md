# Reactor: tối ưu thuật toán Q × (N + M + P)

`simple.cpp` giữ code người dùng gửi, chỉ đổi chỉ số truy cập của `sumA`
từ `[x][y][z]` sang `[y][z][x]`, `sumB` sang `[x][z][y]` trong cập nhật,
prefix và truy vấn. Giữ nguyên thứ tự vòng prefix, macro, kiểu dữ liệu,
pragma và cơ chế tự đọc `test.inp`/ghi `test.out` nếu file tồn tại.
Biên dịch bằng `g++ -std=c++17 -O2 simple.cpp`; `main()` của code gốc
không ghi kiểu trả về nên GCC cảnh báo, không dùng `-Werror` cho bản này.
`simple_results.json` là số đo cũ khi file này còn dùng fast I/O, không phải
thời gian của bản `cin/cout` hiện tại.

## Chỉ thử fast I/O trên bản gốc

Hai lệnh dưới dùng cùng `original.cpp`, cùng mảng 202³, cùng vòng lặp và pragma.
Cờ `USE_FAST_IO` chỉ đổi đọc/ghi sang bộ đệm `fread`/`fwrite` 64 KiB.

```bash
g++ -std=c++17 -O2 experiments/reactor/original.cpp -o /tmp/reactor-original
g++ -std=c++17 -O2 -DUSE_FAST_IO experiments/reactor/original.cpp -o /tmp/reactor-fastio
python3 experiments/reactor/benchmark.py --variants original original_fastio --output experiments/reactor/fastio_results.json --repeats 3
```

Kết quả chỉ đổi I/O (median 3 lượt, giây; Q=400.000, L=1.000.000):

| N×M×P | Hộp | cin/cout | fread/fwrite |
| --- | --- | ---: | ---: |
| 200×200×50 | dài | 10,085 | 9,152 |
| 50×200×200 | dài | 5,509 | 4,880 |
| 125×125×125 | ngẫu nhiên | 3,164 | 2,585 |
| 200×200×50 | toàn miền | 3,309 | 2,477 |
| 1×200×200 | dài | 1,822 | 1,121 |

Hai bản đều qua 180 test brute force, mọi output stress trùng nhau. Chỉ
thay fast I/O chưa đủ đạt 2 giây trên các bộ lớn của máy đo này. Không thay
layout, không cấp phát lại mảng và không xử lý update theo lô trong phép so sánh này.

Giữ cách tách ba thành phần từ code được cung cấp:

- `S + A*(x-x1)`: duyệt x, cập nhật hình chữ nhật hiệu theo y,z.
- `B*(y-y1)`: duyệt y, cập nhật hình chữ nhật hiệu theo x,z.
- `C*(z-z1)`: duyệt z, cập nhật hình chữ nhật hiệu theo x,y.

Sau prefix 2D trên hai trục tương ứng, cộng ba thành phần khi trả lời.
Độ phức tạp vẫn là `O(Q*(N+M+P) + N*M*P + L)`; mỗi bước cập nhật có bốn lần ghi.

## Chạy

```bash
g++ -std=c++17 -O2 experiments/reactor/solver.cpp -o /tmp/reactor
/tmp/reactor < input.txt > output.txt
```

Bản mặc định dùng layout liên tiếp và xử lý theo lô (`batched`). Để dùng
bản nhanh nhất đã đo trên CPU hỗ trợ AVX2/BMI/BMI2/LZCNT/POPCNT:

```bash
g++ -std=c++17 -O2 -DUSE_PRAGMA experiments/reactor/solver.cpp -o /tmp/reactor
```

Thêm `-DSTREAMING` để quay về xử lý từng cập nhật ngay khi đọc.
Pragma nằm sau header vì GCC 13 trên máy này báo `target specific option mismatch`
khi đặt trước header với bản dùng `std::string`.

```bash
python3 experiments/reactor/benchmark.py --repeats 3
```

Script biên dịch bằng GNU C++17, `-O2 -Wall -Wextra -Werror`, chạy 180 test
nhỏ với brute force độc lập, rồi chạy 5 dạng stress, mỗi dạng 400.000 cập nhật
và 1.000.000 truy vấn. Mọi biến thể phải cho cùng SHA-256 output trên stress.
Stress dùng hệ số ngẫu nhiên trong [-10^6,10^6], gồm hộp dài, hộp ngẫu nhiên,
hộp phủ toàn miền và kích thước có chiều bằng 1. Test nhỏ kiểm tra mọi ô,
truy vấn lặp, hộp suy biến, hệ số 0, âm và biên ±10^6.

## Các biến thể

| Tên | Thay đổi |
| --- | --- |
| original | Thuật toán, ba mảng 202³ và cin/cout như code cung cấp, có cả hai pragma |
| fixed_fastio | Bộ đệm fread/fwrite, chỉ số phẳng và con trỏ, vẫn stride 202 |
| packed | Như trên, cấp phát theo kích thước thật |
| transposed | Mỗi mảng có trục cập nhật ở chiều liên tiếp |
| transposed_pragma | Như trên, thêm cả hai pragma |
| batched | Đọc và lưu các cập nhật, xử lý hết thành phần X rồi Y rồi Z |
| batched_pragma | Như trên, thêm cả hai pragma |

`original.cpp` bỏ macro, chuyển chỉ số sang int 32-bit, giữ năng lượng 64-bit,
dùng `int main()` và bỏ tự động đọc `test.inp`, để benchmark qua stdin/stdout.
`fixed_fastio` và `packed` lưu thành phần B theo [y][x][z], nên bảng này là
so sánh các bản triển khai, không tách tuyệt đối tác dụng của từng thay đổi.
Chỉ cặp `transposed` / `transposed_pragma` cô lập tác dụng của bộ pragma.
`batched` dùng thêm khoảng 21,4 MiB cho 400.000 cập nhật; thứ tự cộng có thể
đổi vì đây là các phép cộng số nguyên không tràn. Tách ba lượt giữ mỗi lần
cập nhật tập trung trên một mảng. So sánh thêm được lưu ở `batched_results.json`:

```bash
python3 experiments/reactor/benchmark.py --variants transposed_pragma batched batched_pragma --output experiments/reactor/batched_results.json --repeats 3
```

## Tối ưu chính

Ba mảng trong bản mặc định lần lượt lưu theo `[y][z][x]`, `[x][z][y]`,
`[x][y][z]`. Bốn con trỏ của mỗi cập nhật đều tiến một phần tử mỗi bước.
GCC có thể vector hóa các vòng này; stride lớn của bản gốc gây nhiều truy cập
cache cách xa nhau. Prefix chạy theo chiều vật lý liên tiếp, tích phân trên
hai chiều còn lại. Hàm query đổi thứ tự tọa độ tương ứng.

Ví dụ hộp [1,2]³ có S=5, A=2, B=-3, C=4: tại (2,2,2), ba mảng sau prefix
cho lần lượt 7, -3, 4; tổng là 8. Hiệu bốn góc cho đúng giá trị trong hình
chữ nhật và 0 ngoài nó. Mỗi mảng giữ nguyên tọa độ trục đã duyệt, nên không
prefix theo trục đó. Đây cũng là lý do không thể cộng ba mảng hiệu trước
khi prefix: chúng cần tích phân trên các cặp trục khác nhau.

Mỗi mảng chỉ có `(N+2)*(M+2)*(P+2)` phần tử 64-bit thay vì `202^3`.
Với 200×200×50, ba mảng dùng khoảng 48,6 MiB, thay cho 188,7 MiB.
Output gom trong string, dự trữ tối đa 22 MB; input có bộ đệm 64 KiB.
Các giá trị trung gian cũng an toàn trong 64-bit với giới hạn đề bài.

## Cách đọc kết quả

`results.json` lưu thời gian từng lần chạy, compiler và dạng input. Thời gian
wall-clock bao gồm khởi động, cấp phát, đọc file và ghi toàn bộ output vào file;
không bao gồm sinh input, biên dịch hoặc hash output. Thứ tự chạy được xáo trộn
mỗi lượt; báo cáo dùng median của ba lượt, dữ liệu đã ở page cache của hệ điều hành.
Máy đo: Intel Core i7-1065G7, một tiến trình solver, không ghim core/tần số.

Đây là kiểm thử local, chưa có submission/judge chính thức để xác nhận AC.
Mốc 2 giây phụ thuộc CPU, compiler và cách tính thời gian của judge.

## Kết quả ngày 22/10/2026

Thời gian median, đơn vị giây. Mỗi dòng có Q=400.000 và L=1.000.000.
Bản gốc và bản tối ưu nằm ở hai lượt benchmark riêng, cùng generator/seed;
điều kiện tải máy có thể khác nhau. Xem toàn bộ số đo trong hai file JSON.

| N×M×P | Hộp | original | transposed + pragma (lượt đầu) | batched + pragma |
| --- | --- | ---: | ---: | ---: |
| 200×200×50 | dài | 11,237 | 1,760 | 1,151 |
| 50×200×200 | dài | 4,634 | 1,393 | 1,249 |
| 125×125×125 | ngẫu nhiên | 3,177 | 0,979 | 1,123 |
| 200×200×50 | toàn miền | 3,106 | 0,763 | 0,915 |
| 1×200×200 | dài | 1,964 | 0,600 | 0,638 |

Chọn `batched + pragma` để có thêm dư địa ở hai dạng hộp dài. Batching không
thắng mọi dạng input. Lượt so sánh trực tiếp trong `batched_results.json` cho
median `transposed + pragma` lần lượt 1,478; 1,568; 1,068; 0,856; 0,610 giây.
Lần chạy chậm nhất của `batched + pragma` trong 15 lần là 1,420 giây.
Cả 8 lượt kiểm tra biến thể (5 lượt đầu, 3 lượt sau) đều qua 180 test brute force;
mọi output stress trong từng lượt benchmark trùng nhau.

Notebook giới hạn 25 trang, tính cả trang bìa/mục lục. Giữ cỡ chữ code 5,75 pt,
chỉnh giãn dòng listing từ 6,7 xuống 6,55 pt để đáp ứng giới hạn. Lệnh
`python3 tests/check_notebook_cpp.py --standalone` đạt 102/103; file không sửa
`source/cpp/math/linalg_gauss.cpp:38` bị `-Werror=misleading-indentation`,
nên script dừng trước phần runtime toàn kho. Template đã qua `-fsyntax-only`.
