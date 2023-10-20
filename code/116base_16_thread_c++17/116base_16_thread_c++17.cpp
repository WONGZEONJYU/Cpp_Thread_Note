#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <execution>
using namespace std;
using namespace chrono;

static constexpr char base16[]{ "0123456789abcdef" };
static void Base16Encode(const uint8_t* data, const int size, uint8_t* out)
{
	for (int i{}; i < size; i++)
	{
		const auto t{ data[i] };
		const auto a{ base16[t >> 4] }, b{ base16[t & 0x0f] };
		out[i * 2] = a;
		out[i * 2 + 1] = b;
	}
}

/*C++11多核base16编码*/
static void Base16EncodeThread(const vector<uint8_t>& data, vector<uint8_t>& out)
{
	const auto size{ data.size() };
	//cout << "size : " << size << '\n';
	/*系统支持的线程核心数*/
	auto th_count{ thread::hardware_concurrency() };
	//cout << "th_count : " << th_count << '\n';
	/*对数据进行切片*/
	auto slice_count(size / th_count);
	//cout << "slice_count : " << slice_count << '\n';

	if (size < th_count) { /*如果数据量太小,只切一片*/
		th_count = 1;
		slice_count = size;
	}

	auto d{ data.data() };
	auto o{ out.data() };

	/*准备好线程*/
	vector<thread> ths(th_count);
	//ths.resize(th_count);

	for (int i{}; i < th_count; i++) {

		const auto offset{ i * slice_count };
		auto count{ slice_count };

		/*处理最后一个线程*/
		if ((th_count > 1) && ((th_count - 1) == i)) {
			count = slice_count + size % th_count;
			//cout << "count :" << count << '\n';
		}
		//cout << offset << " : \n" << flush;
		ths[i] = move(thread(Base16Encode, d + offset,
			count, o + static_cast<size_t>(offset * 2)));
	}

	for (auto& th : ths) {
		th.join();
	}
}

int main(int argc, char* argv[])
{
	string s{ "测试base16编码" };

	uint8_t buf[1024]{};
	Base16Encode(reinterpret_cast<const uint8_t*>(s.data()), s.size(), buf);
	cout << "base16: " << buf << "\n\n";

	/*初始化数据*/
	vector<uint8_t> in_data(1024 * 1024 * 200);
	//in_data.resize(1024 * 1024 * 20);
	for (int i{}; i < in_data.size(); i++) {
		in_data[i] = i % 256;
	}

	/*准备好输出结果的空间*/
	vector<uint8_t> out_data(in_data.size() * 2);
	//out_data.resize(in_data.size() * 2);
	/*输出结果保存的容量为待编码数据量的2倍*/

#if 0

	/*测试 c++11 单线程base16编码效率*/
	{
		cout << "Single-threaded base16 encoding starts calculation\n";
		auto start{ system_clock::now() };
		Base16Encode(in_data.data(), in_data.size(), out_data.data());
		auto end{ system_clock::now() };
		auto duration{ duration_cast<milliseconds>(end - start) };
		cout << "Encoding: " << in_data.size() <<
			" Bytes takes " << duration.count() << " ms\n";
		
		//cout << "res1 :" << out_data.data() << "\n";
		cout << "\n";
	}

	/*测试 c++11 多线程Base16编码效率*/
	{
		cout << "c++11 multi-threaded Base16 encoding starts calculation\n";
		auto start{ system_clock::now() };
		Base16EncodeThread(in_data, out_data);
		auto end{ system_clock::now() };
		auto duration{ duration_cast<milliseconds>(end - start) };
		cout << "Encoding: " << in_data.size() <<
			" Bytes takes " << duration.count() << " ms\n";

		//cout << "res2 :" << out_data.data() << "\n";
		cout << "\n";
	}

#endif /*0*/

#if 1

	/*测试C++17 多线程base16编码*/
	{
		cout << "C++17 multi-threaded Base16 encoding starts calculation\n";
		auto start{ system_clock::now() };

		/*直接取in_data与out_data的地址,为了就是性能上的优化*/
		const auto idata{ in_data.data() };
		const auto odata{ out_data.data() };

		/*#include <execution> 需C++17以上版本才支持*/
		/* execution::par 代表并行多核*/

		std::for_each (execution::par, in_data.begin(), in_data.end(),
			[&](auto& d) {
				const auto a{ base16[d >> 4] }, b{ base16[d & 0x0f] };
				auto index{ &d - idata };
				odata[index * 2] = a;
				odata[index * 2 + 1] = b;
		});

		auto end{ system_clock::now() };
		auto duration{ duration_cast<milliseconds>(end - start) };
		cout << "Encoding: " << in_data.size() <<
			" Bytes takes " << duration.count() << " ms\n";

		//cout << "res3 :" << out_data.data() << "\n";
		cout << "\n";
	}

#endif

	_CRT_UNUSED(getchar());
	return 0;
}
