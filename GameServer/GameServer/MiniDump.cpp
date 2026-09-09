// MiniDump.cpp: implementation of the CMiniDump class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MiniDump.h"
#include <crtdbg.h>
#include <stdlib.h>
#include "Util.h"

static LPTOP_LEVEL_EXCEPTION_FILTER PreviousExceptionFilter = 0;

static const char* GetExceptionCodeDescription(DWORD dwCode)
{
	switch(dwCode)
	{
		case EXCEPTION_ACCESS_VIOLATION: return "EXCEPTION_ACCESS_VIOLATION (0xC0000005)";
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "EXCEPTION_ARRAY_BOUNDS_EXCEEDED (0xC000008C)";
		case EXCEPTION_BREAKPOINT: return "EXCEPTION_BREAKPOINT (0x80000003)";
		case EXCEPTION_DATATYPE_MISALIGNMENT: return "EXCEPTION_DATATYPE_MISALIGNMENT (0x80000002)";
		case EXCEPTION_FLT_DENORMAL_OPERAND: return "EXCEPTION_FLT_DENORMAL_OPERAND (0xC000008D)";
		case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "EXCEPTION_FLT_DIVIDE_BY_ZERO (0xC000008E)";
		case EXCEPTION_FLT_INEXACT_RESULT: return "EXCEPTION_FLT_INEXACT_RESULT (0xC000008F)";
		case EXCEPTION_FLT_INVALID_OPERATION: return "EXCEPTION_FLT_INVALID_OPERATION (0xC0000090)";
		case EXCEPTION_FLT_OVERFLOW: return "EXCEPTION_FLT_OVERFLOW (0xC0000091)";
		case EXCEPTION_FLT_STACK_CHECK: return "EXCEPTION_FLT_STACK_CHECK (0xC0000092)";
		case EXCEPTION_FLT_UNDERFLOW: return "EXCEPTION_FLT_UNDERFLOW (0xC0000093)";
		case EXCEPTION_ILLEGAL_INSTRUCTION: return "EXCEPTION_ILLEGAL_INSTRUCTION (0xC000001D)";
		case EXCEPTION_IN_PAGE_ERROR: return "EXCEPTION_IN_PAGE_ERROR (0xC0000006)";
		case EXCEPTION_INT_DIVIDE_BY_ZERO: return "EXCEPTION_INT_DIVIDE_BY_ZERO (0xC0000094)";
		case EXCEPTION_INT_OVERFLOW: return "EXCEPTION_INT_OVERFLOW (0xC0000095)";
		case EXCEPTION_INVALID_DISPOSITION: return "EXCEPTION_INVALID_DISPOSITION (0xC0000026)";
		case EXCEPTION_NONCONTINUABLE_EXCEPTION: return "EXCEPTION_NONCONTINUABLE_EXCEPTION (0xC0000025)";
		case EXCEPTION_PRIV_INSTRUCTION: return "EXCEPTION_PRIV_INSTRUCTION (0xC0000096)";
		case EXCEPTION_SINGLE_STEP: return "EXCEPTION_SINGLE_STEP (0x80000004)";
		case EXCEPTION_STACK_OVERFLOW: return "EXCEPTION_STACK_OVERFLOW (0xC00000FD)";
		case 0xC0000409: return "STATUS_STACK_BUFFER_OVERRUN / FAST_FAIL_FATAL_APP_EXIT (0xC0000409)";
		case 0xC0000374: return "STATUS_HEAP_CORRUPTION (0xC0000374)";
		default: return "UNKNOWN_EXCEPTION";
	}
}

void CMiniDump::CreateDump(EXCEPTION_POINTERS* info, const char* customReason)
{
	char szExePath[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, szExePath, MAX_PATH);

	char* pSlash = strrchr(szExePath, '\\');
	if(pSlash != 0)
	{
		*(pSlash + 1) = '\0';
	}

	char szDumpDir[MAX_PATH] = { 0 };
	wsprintfA(szDumpDir, "%sDUMP", szExePath);
	CreateDirectoryA(szDumpDir, NULL);

	SYSTEMTIME SystemTime;
	GetLocalTime(&SystemTime);

	char szBaseName[MAX_PATH] = { 0 };
	wsprintfA(szBaseName, "%s\\%04d-%02d-%02d_%02dh%02dm%02ds",
		szDumpDir,
		SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
		SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);

	char szFileDmp[MAX_PATH] = { 0 };
	char szFileTxt[MAX_PATH] = { 0 };
	wsprintfA(szFileDmp, "%s.dmp", szBaseName);
	wsprintfA(szFileTxt, "%s.txt", szBaseName);

	// 1. Escribir informe detallado en texto
	HANDLE hTxtFile = CreateFileA(szFileTxt, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if(hTxtFile != INVALID_HANDLE_VALUE)
	{
		char szReport[4096] = { 0 };
		int len = 0;

		len += wsprintfA(szReport + len, "======================================================================\r\n");
		len += wsprintfA(szReport + len, "                   GAMESERVER CRASH REPORT\r\n");
		len += wsprintfA(szReport + len, "======================================================================\r\n");
		len += wsprintfA(szReport + len, "Date & Time      : %04d-%02d-%02d %02d:%02d:%02d\r\n",
			SystemTime.wYear, SystemTime.wMonth, SystemTime.wDay,
			SystemTime.wHour, SystemTime.wMinute, SystemTime.wSecond);

		if(customReason != 0 && customReason[0] != '\0')
		{
			len += wsprintfA(szReport + len, "Crash Reason     : %s\r\n", customReason);
		}

		if(info != 0 && info->ExceptionRecord != 0)
		{
			DWORD code = info->ExceptionRecord->ExceptionCode;
			len += wsprintfA(szReport + len, "Exception Code   : 0x%08X [%s]\r\n", code, GetExceptionCodeDescription(code));
			len += wsprintfA(szReport + len, "Exception Address: 0x%p\r\n", info->ExceptionRecord->ExceptionAddress);

			if(code == EXCEPTION_ACCESS_VIOLATION && info->ExceptionRecord->NumberParameters >= 2)
			{
				ULONG_PTR accessType = info->ExceptionRecord->ExceptionInformation[0];
				ULONG_PTR targetAddr = info->ExceptionRecord->ExceptionInformation[1];
				const char* op = (accessType == 0) ? "Read" : ((accessType == 1) ? "Write" : "Execute");
				len += wsprintfA(szReport + len, "Violation Detail : Attempted to %s invalid address 0x%p\r\n", op, (void*)targetAddr);
			}
		}

		if(info != 0 && info->ContextRecord != 0)
		{
			CONTEXT* ctx = info->ContextRecord;
			len += wsprintfA(szReport + len, "----------------------------- REGISTERS ------------------------------\r\n");
			len += wsprintfA(szReport + len, "EAX: 0x%08X  EBX: 0x%08X  ECX: 0x%08X  EDX: 0x%08X\r\n", ctx->Eax, ctx->Ebx, ctx->Ecx, ctx->Edx);
			len += wsprintfA(szReport + len, "ESI: 0x%08X  EDI: 0x%08X  EBP: 0x%08X  ESP: 0x%08X\r\n", ctx->Esi, ctx->Edi, ctx->Ebp, ctx->Esp);
			len += wsprintfA(szReport + len, "EIP: 0x%08X  EFLAGS: 0x%08X\r\n", ctx->Eip, ctx->EFlags);
		}

		MEMORYSTATUSEX mem;
		mem.dwLength = sizeof(mem);
		if(GlobalMemoryStatusEx(&mem))
		{
			len += wsprintfA(szReport + len, "------------------------------ MEMORY --------------------------------\r\n");
			len += wsprintfA(szReport + len, "Memory Load      : %u%%\r\n", mem.dwMemoryLoad);
			len += wsprintfA(szReport + len, "Avail Physical   : %I64u MB / %I64u MB\r\n", mem.ullAvailPhys / (1024 * 1024), mem.ullTotalPhys / (1024 * 1024));
			len += wsprintfA(szReport + len, "Avail Virtual    : %I64u MB / %I64u MB\r\n", mem.ullAvailVirtual / (1024 * 1024), mem.ullTotalVirtual / (1024 * 1024));
		}

		len += wsprintfA(szReport + len, "======================================================================\r\n");

		DWORD dwWritten = 0;
		WriteFile(hTxtFile, szReport, (DWORD)len, &dwWritten, NULL);
		CloseHandle(hTxtFile);
	}

	// 2. Escribir volcado minidump
	HANDLE hDmpFile = CreateFileA(szFileDmp, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if(hDmpFile != INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId = GetCurrentThreadId();
		mdei.ExceptionPointers = info;
		mdei.ClientPointers = FALSE;

		MINIDUMP_TYPE dumpType = (MINIDUMP_TYPE)(
			MiniDumpNormal |
			MiniDumpWithDataSegs |
			MiniDumpWithIndirectlyReferencedMemory |
			MiniDumpWithThreadInfo |
			MiniDumpWithUnloadedModules);

		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDmpFile, dumpType, (info != 0) ? &mdei : 0, 0, 0);
		CloseHandle(hDmpFile);
	}

	// 3. Intentar imprimir en consola / GUI
	__try
	{
		LogAdd(LOG_RED, "[CRASH DETECTED] Dump written to %s", szFileDmp);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
	}
}

static LONG WINAPI DumpExceptionFilter(EXCEPTION_POINTERS* info)
{
	CMiniDump::CreateDump(info, "Unhandled SEH Exception");
	return EXCEPTION_EXECUTE_HANDLER;
}

static void __cdecl CustomInvalidParameterHandler(
	const wchar_t* expression,
	const wchar_t* function,
	const wchar_t* file,
	unsigned int line,
	uintptr_t pReserved)
{
	char reason[1024] = { 0 };
	wsprintfA(reason, "CRT Invalid Parameter:\r\n  Expression: %ls\r\n  Function  : %ls\r\n  File      : %ls\r\n  Line      : %u",
		(expression ? expression : L"Unknown"),
		(function ? function : L"Unknown"),
		(file ? file : L"Unknown"),
		line);

	CONTEXT ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.ContextFlags = CONTEXT_FULL;
	RtlCaptureContext(&ctx);

	EXCEPTION_RECORD rec;
	memset(&rec, 0, sizeof(rec));
	rec.ExceptionCode = 0xC0000409; // STATUS_STACK_BUFFER_OVERRUN
	rec.ExceptionFlags = EXCEPTION_NONCONTINUABLE;
	rec.ExceptionAddress = (PVOID)ctx.Eip;

	EXCEPTION_POINTERS ep;
	ep.ExceptionRecord = &rec;
	ep.ContextRecord = &ctx;

	CMiniDump::CreateDump(&ep, reason);

	TerminateProcess(GetCurrentProcess(), 0xC0000409);
}

static void __cdecl CustomPurecallHandler()
{
	CONTEXT ctx;
	memset(&ctx, 0, sizeof(ctx));
	ctx.ContextFlags = CONTEXT_FULL;
	RtlCaptureContext(&ctx);

	EXCEPTION_RECORD rec;
	memset(&rec, 0, sizeof(rec));
	rec.ExceptionCode = 0xC0000025; // STATUS_NONCONTINUABLE_EXCEPTION
	rec.ExceptionFlags = EXCEPTION_NONCONTINUABLE;
	rec.ExceptionAddress = (PVOID)ctx.Eip;

	EXCEPTION_POINTERS ep;
	ep.ExceptionRecord = &rec;
	ep.ContextRecord = &ctx;

	CMiniDump::CreateDump(&ep, "CRT Pure Virtual Function Call (Purecall)");

	TerminateProcess(GetCurrentProcess(), 0xC0000025);
}

static void PreventSetUnhandledExceptionFilterReset()
{
	HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
	if(hKernel32 == 0)
	{
		return;
	}

	void* pOrgEntry = (void*)GetProcAddress(hKernel32, "SetUnhandledExceptionFilter");
	if(pOrgEntry == 0)
	{
		return;
	}

	// 32-bit x86: xor eax, eax; ret 4 (opcode: 33 C0 C2 04 00)
	unsigned char code[5] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };

	DWORD dwOldProtect = 0;
	if(VirtualProtect(pOrgEntry, sizeof(code), PAGE_EXECUTE_READWRITE, &dwOldProtect) != 0)
	{
		memcpy(pOrgEntry, code, sizeof(code));
		VirtualProtect(pOrgEntry, sizeof(code), dwOldProtect, &dwOldProtect);
	}
}

void CMiniDump::Start()
{
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

	PreviousExceptionFilter = SetUnhandledExceptionFilter(DumpExceptionFilter);

	_set_invalid_parameter_handler(CustomInvalidParameterHandler);

	_set_purecall_handler(CustomPurecallHandler);

	_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);

	PreventSetUnhandledExceptionFilterReset();
}

void CMiniDump::Clean()
{
	SetUnhandledExceptionFilter(PreviousExceptionFilter);
}
