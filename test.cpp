#include "PerformanceProfiler.h"

//测试用例

//普通情况
///////////////////////////////////////////////////////////////////////////////////
//void Test1()
//{
//	PPSection* section = PerformanceProfiler::GetInstance()    \
//		->CreateSection(__FILE__, __FUNCTION__, __LINE__, "第一段代码");
//	
//	section->Begin();
//	Sleep(5000);
//	section->End();
//}

void Test2()
{
	PERFORMANCE_PROFILER_EE_BEGIN(sql, "数据库");
	Sleep(1000);
	PERFORMANCE_PROFILER_EE_END(sql);

	PERFORMANCE_PROFILER_EE_BEGIN(network, "网络");
	Sleep(2000);
	PERFORMANCE_PROFILER_EE_END(network);
}
//Test2调用3次
void TestN2()
{
	for (int i = 3; i > 0; i--)
	{
		Test2();
	}
}

///////////////////////////////////////////////////////////////////////////////////
//测试递归
LongType Fib(size_t n)
{
	PERFORMANCE_PROFILER_EE_BEGIN(fib, "递归");
	LongType ret = 0;
	if (n < 2)
	{
		ret = n;
	}		
	else
	{
		ret = Fib(n - 1) + Fib(n - 2);
	}	
	PERFORMANCE_PROFILER_EE_END(fib);
	return ret;
}
void TestN3()
{
	PERFORMANCE_PROFILER_EE_BEGIN(fib, "FIB");
	Fib(20);
	PERFORMANCE_PROFILER_EE_END(fib);
}

//测试多线程
void ThreadRun(int count)
{
	cout << this_thread::get_id() << endl;
	while (count--)
	{
		PERFORMANCE_PROFILER_EE_BEGIN(ThreadRun, "ThreadRun");
		this_thread::sleep_for(std::chrono::milliseconds(100));
		PERFORMANCE_PROFILER_EE_END(ThreadRun);
	}
}
void TestMhread()
{
	cout << this_thread::get_id() << endl;
	thread t1(ThreadRun, 15);
	thread t2(ThreadRun, 10);
	thread t3(ThreadRun, 5);

	t1.join();
	t2.join();
	t3.join();
}

int main()
{
	SET_CONFIG_OPTION(PERFORMANCE_PROFILER_EE | SAVE_TO_CONSOLE);
	//Test2();
	TestN3();
	//TestMhread();
	system("pause");
	return 0;
}