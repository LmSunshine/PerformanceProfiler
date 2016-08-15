#include "PerformanceProfiler.h"

//��������

//��ͨ���
///////////////////////////////////////////////////////////////////////////////////
//void Test1()
//{
//	PPSection* section = PerformanceProfiler::GetInstance()    \
//		->CreateSection(__FILE__, __FUNCTION__, __LINE__, "��һ�δ���");
//	
//	section->Begin();
//	Sleep(5000);
//	section->End();
//}

void Test2()
{
	PERFORMANCE_PROFILER_EE_BEGIN(sql, "���ݿ�");
	Sleep(1000);
	PERFORMANCE_PROFILER_EE_END(sql);

	PERFORMANCE_PROFILER_EE_BEGIN(network, "����");
	Sleep(2000);
	PERFORMANCE_PROFILER_EE_END(network);
}
//Test2����3��
void TestN2()
{
	for (int i = 3; i > 0; i--)
	{
		Test2();
	}
}

///////////////////////////////////////////////////////////////////////////////////
//���Եݹ�
LongType Fib(size_t n)
{
	PERFORMANCE_PROFILER_EE_BEGIN(fib, "�ݹ�");
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

//���Զ��߳�
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