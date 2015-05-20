/*
 * A memóriaszivárgás detektáló funkciókhoz szükséges definiciók
 */
#ifndef MEMCHECK_H
#define MEMCHECK_H

#if defined(MEMCHECK) && defined(MEMTRACE)
# error "Nem lehet a MEMCHECK es a MEMTRACE egyszerre definialt"
#elif !defined(MEMCHECK) && !defined(MEMTRACE)
# undef _StartMemoryCheck
# define _StartMemoryCheck()
# if !defined(_MSC_VER)
#   undef _CrtDumpMemoryLeaks
#   define _CrtDumpMemoryLeaks()
# endif
#elif defined(MEMCHECK)

#if defined(_MSC_VER)           // Ha Visual Studio
# define _CRTDBG_MAP_ALLOC
# define _CRT_SECURE_NO_WARNINGS
# include <stdlib.h>
# include <crtdbg.h>
# define _StartMemoryCheck()
#elif defined(__GNUC__)         // Ha GNU C
# include <malloc.h>
# if defined(__MINGW32_VERSION)
#   define _CrtDumpMemoryLeaks()// nem tudjuk, hogyan kell ellenõrizni, nem csinalunk semmit
#   define _StartMemoryCheck()
# elif __GLIBC__ >= 2
#   include <mcheck.h>
#   define _StartMemoryCheck()    mcheck_pedantic(NULL); mtrace(); static int __uordblks = mallinfo().uordblks;
#   define _CrtDumpMemoryLeaks()  mcheck_check_all(); \
                                  if (__uordblks != mallinfo().uordblks) fprintf(stderr, "Memory leaks!\n");
# else
#   define _StartMemoryCheck()
#   define _CrtDumpMemoryLeaks()  { struct mallinfo m = mallinfo(); \
                                  if (m.uordblks > 48 || m.usmblks) fprintf(stderr, "Memory leaks!\n"); }
# endif
#else				// nem tudjuk milyen fordító, nem csinálunk semmit0
# define _CrtDumpMemoryLeaks()
# define _StartMemoryCheck()
#endif

#endif/* MEMCECK */
#endif /* MEMCHECK_H */
