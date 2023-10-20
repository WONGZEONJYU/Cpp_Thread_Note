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

/*C++11���base16����*/
static void Base16EncodeThread(const vector<uint8_t>& data, vector<uint8_t>& out)
{
	const auto size{ data.size() };
	//cout << "size : " << size << '\n';
	/*ϵͳ֧�ֵ��̺߳�����*/
	auto th_count{ thread::hardware_concurrency() };
	//cout << "th_count : " << th_count << '\n';
	/*�����ݽ�����Ƭ*/
	auto slice_count(size / th_count);
	//cout << "slice_count : " << slice_count << '\n';

	if (size < th_count) { /*���������̫С,ֻ��һƬ*/
		th_count = 1;
		slice_count = size;
	}

	auto d{ data.data() };
	auto o{ out.data() };

	/*׼�����߳�*/
	vector<thread> ths(th_count);
	//ths.resize(th_count);

	for (int i{}; i < th_count; i++) {

		const auto offset{ i * slice_count };
		auto count{ slice_count };

		/*�������һ���߳�*/
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
	string s{ "����base16����" };

	uint8_t buf[1024]{};
	Base16Encode(reinterpret_cast<const uint8_t*>(s.data()), s.size(), buf);
	cout << "base16: " << buf << "\n\n";

	/*��ʼ������*/
	vector<uint8_t> in_data(1024 * 1024 * 200);
	//in_data.resize(1024 * 1024 * 20);
	for (int i{}; i < in_data.size(); i++) {
		in_data[i] = i % 256;
	}

	/*׼�����������Ŀռ�*/
	vector<uint8_t> out_data(in_data.size() * 2);
	//out_data.resize(in_data.size() * 2);
	/*���������������Ϊ��������������2��*/

#if 0

	/*���� c++11 ���߳�base16����Ч��*/
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

	/*���� c++11 ���߳�Base16����Ч��*/
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

	/*����C++17 ���߳�base16����*/
	{
		cout << "C++17 multi-threaded Base16 encoding starts calculation\n";
		auto start{ system_clock::now() };

		/*ֱ��ȡin_data��out_data�ĵ�ַ,Ϊ�˾��������ϵ��Ż�*/
		const auto idata{ in_data.data() };
		const auto odata{ out_data.data() };

		/*#include <execution> ��C++17���ϰ汾��֧��*/
		/* execution::par �����ж��*/

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
