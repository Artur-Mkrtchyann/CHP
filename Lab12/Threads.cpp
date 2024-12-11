#include <iostream>
using namespace std;

#ifdef _COMPILE_WINDOWS
#include <Windows.h>
typedef HANDLE THREADVAR;
typedef DWORD WINAPI THREADFUNCVAR;
typedef LPVOID THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef CRITICAL_SECTION THREAD_LOCK;
#endif
#ifdef _COMPILE_LINUX
#include <pthread.h>
#include <unistd.h>
typedef pthread_t THREADVAR;
typedef void* THREADFUNCVAR;
typedef void* THREADFUNCARGS;
typedef THREADFUNCVAR(*THREADFUNC)(THREADFUNCARGS);
typedef pthread_mutex_t THREAD_LOCK;
typedef unsigned long int DWORD_PTR;
typedef unsigned int DWORD;
typedef unsigned long long int uint64;
typedef long long int int64;
#endif

THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg);
void StopThread(THREADVAR t);
void InitThreadLock(THREAD_LOCK& t);
void LockThread(THREAD_LOCK& t);
void UnlockThread(THREAD_LOCK& t);
void sleep(int ms);

THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam);

int globlint = 0;
bool quitnow = false;

int main() {
	THREAD_LOCK recv_lock;
	InitThreadLock(recv_lock);

	DWORD_PTR* svRecvThrArgs = new DWORD_PTR[1];
	svRecvThrArgs[0] = (DWORD_PTR)&recv_lock;

	THREADVAR recvThrHandle = PrepareThread(MyAsyncSimpleThread, (THREADFUNCARGS)svRecvThrArgs);

	while (!quitnow) {
		LockThread(recv_lock);
		globlint++;
		if (globlint > 5000) {
			quitnow = true;
		}
		cout << "\n\tMain loop.\t" << globlint << '\n';
		UnlockThread(recv_lock);
		sleep(5);
	}

	StopThread(recvThrHandle);
}

THREADFUNCVAR MyAsyncSimpleThread(THREADFUNCARGS lpParam) {
	DWORD_PTR* arg = (DWORD_PTR*)lpParam;
	THREAD_LOCK& ref_recv_lock = *((THREAD_LOCK*)arg[0]);

	while (!quitnow) {
		LockThread(ref_recv_lock);
		globlint++;
		if (globlint > 100) {
			quitnow = true;
		}
		cout << "\nMyAsyncSimpleThread.\t" << globlint << endl;
		UnlockThread(ref_recv_lock);
		sleep(1);
	}
	return NULL;
}

THREADVAR PrepareThread(THREADFUNC f, THREADFUNCARGS arg) {
#ifdef _COMPILE_LINUX
	pthread_t out;
	pthread_create(&out, NULL, f, arg);
	return out;
#endif
#ifdef _COMPILE_WINDOWS
	DWORD thrId;
	THREADVAR out = CreateThread(
		NULL, 0, (LPTHREAD_START_ROUTINE)f, arg, 0, &thrId);
	return out;
#endif
}

void StopThread(THREADVAR t) {
#ifdef _COMPILE_LINUX
	pthread_exit((void*)t);
#endif
#ifdef _COMPILE_WINDOWS
	TerminateThread(t, 0);
	CloseHandle(t);
#endif
}

void InitThreadLock(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
	t = PTHREAD_MUTEX_INITIALIZER;
#endif
#ifdef _COMPILE_WINDOWS
	InitializeCriticalSection(&t);
#endif
}

void LockThread(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
	pthread_mutex_lock(&t);
#endif
#ifdef _COMPILE_WINDOWS
	EnterCriticalSection(&t);
#endif
}

void UnlockThread(THREAD_LOCK& t) {
#ifdef _COMPILE_LINUX
	pthread_mutex_unlock(&t);
#endif
#ifdef _COMPILE_WINDOWS
	LeaveCriticalSection(&t);
#endif
}

void sleep(int ms) {
#ifdef _COMPILE_LINUX
	usleep(ms * 1000);
#endif
#ifdef _COMPILE_WINDOWS
	Sleep(ms);
#endif
}
