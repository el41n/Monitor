#include "architecture.h"

#include <QString>

#define bit_SSE3	(1 << 0)
#define bit_PCLMUL	(1 << 1)
#define bit_LZCNT	(1 << 5)
#define bit_SSSE3	(1 << 9)
#define bit_FMA		(1 << 12)
#define bit_CMPXCHG16B	(1 << 13)
#define bit_SSE4_1	(1 << 19)
#define bit_SSE4_2	(1 << 20)
#define bit_MOVBE	(1 << 22)
#define bit_POPCNT	(1 << 23)
#define bit_AES		(1 << 25)
#define bit_XSAVE	(1 << 26)
#define bit_OSXSAVE	(1 << 27)
#define bit_AVX		(1 << 28)
#define bit_F16C	(1 << 29)
#define bit_RDRND	(1 << 30)

#define bit_CMPXCHG8B	(1 << 8)
#define bit_CMOV	(1 << 15)
#define bit_MMX		(1 << 23)
#define bit_FXSAVE	(1 << 24)
#define bit_SSE		(1 << 25)
#define bit_SSE2	(1 << 26)

#define bit_LAHF_LM	(1 << 0)
#define bit_ABM		(1 << 5)
#define bit_SSE4a	(1 << 6)
#define bit_PRFCHW	(1 << 8)
#define bit_XOP         (1 << 11)
#define bit_LWP 	(1 << 15)
#define bit_FMA4        (1 << 16)
#define bit_TBM         (1 << 21)
#define bit_MWAITX      (1 << 29)

#define bit_MMXEXT	(1 << 22)
#define bit_LM		(1 << 29)
#define bit_3DNOWP	(1 << 30)
#define bit_3DNOW	(1u << 31)

#define bit_CLZERO	(1 << 0)
#define bit_WBNOINVD	(1 << 9)

#define bit_FSGSBASE	(1 << 0)
#define bit_SGX (1 << 2)
#define bit_BMI	(1 << 3)
#define bit_HLE	(1 << 4)
#define bit_AVX2	(1 << 5)
#define bit_BMI2	(1 << 8)
#define bit_RTM	(1 << 11)
#define bit_MPX	(1 << 14)
#define bit_AVX512F	(1 << 16)
#define bit_AVX512DQ	(1 << 17)
#define bit_RDSEED	(1 << 18)
#define bit_ADX	(1 << 19)
#define bit_AVX512IFMA	(1 << 21)
#define bit_CLFLUSHOPT	(1 << 23)
#define bit_CLWB	(1 << 24)
#define bit_AVX512PF	(1 << 26)
#define bit_AVX512ER	(1 << 27)
#define bit_AVX512CD	(1 << 28)
#define bit_SHA		(1 << 29)
#define bit_AVX512BW	(1 << 30)
#define bit_AVX512VL	(1u << 31)

#define bit_PREFETCHWT1	  (1 << 0)
#define bit_AVX512VBMI	(1 << 1)
#define bit_PKU	(1 << 3)
#define bit_OSPKE	(1 << 4)
#define bit_AVX512VBMI2	(1 << 6)
#define bit_SHSTK	(1 << 7)
#define bit_GFNI	(1 << 8)
#define bit_VAES	(1 << 9)
#define bit_AVX512VNNI	(1 << 11)
#define bit_VPCLMULQDQ	(1 << 10)
#define bit_AVX512BITALG	(1 << 12)
#define bit_AVX512VPOPCNTDQ	(1 << 14)
#define bit_RDPID	(1 << 22)
#define bit_MOVDIRI	(1 << 27)
#define bit_MOVDIR64B	(1 << 28)

#define bit_AVX5124VNNIW (1 << 2)
#define bit_AVX5124FMAPS (1 << 3)
#define bit_IBT	(1 << 20)
#define bit_PCONFIG	(1 << 18)

#define bit_BNDREGS     (1 << 3)
#define bit_BNDCSR      (1 << 4)


#define bit_XSAVEOPT	(1 << 0)
#define bit_XSAVEC	(1 << 1)
#define bit_XSAVES	(1 << 3)

#define __cpuid(level, a, b, c, d)			\
  __asm__ ("cpuid\n\t"					\
       : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
       : "0" (level))

#define __cpuid_count(level, count, a, b, c, d)		\
  __asm__ ("cpuid\n\t"					\
       : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
       : "0" (level), "2" (count))

static __inline unsigned int
__get_cpuid_max (unsigned int __ext, unsigned int *__sig)
{
  unsigned int __eax, __ebx, __ecx, __edx;

#ifndef __x86_64__
#if __GNUC__ >= 3
  __asm__ ("pushf{l|d}\n\t"
       "pushf{l|d}\n\t"
       "pop{l}\t%0\n\t"
       "mov{l}\t{%0, %1|%1, %0}\n\t"
       "xor{l}\t{%2, %0|%0, %2}\n\t"
       "push{l}\t%0\n\t"
       "popf{l|d}\n\t"
       "pushf{l|d}\n\t"
       "pop{l}\t%0\n\t"
       "popf{l|d}\n\t"
       : "=&r" (__eax), "=&r" (__ebx)
       : "i" (0x00200000));
#else
  __asm__ ("pushfl\n\t"
       "pushfl\n\t"
       "popl\t%0\n\t"
       "movl\t%0, %1\n\t"
       "xorl\t%2, %0\n\t"
       "pushl\t%0\n\t"
       "popfl\n\t"
       "pushfl\n\t"
       "popl\t%0\n\t"
       "popfl\n\t"
       : "=&r" (__eax), "=&r" (__ebx)
       : "i" (0x00200000));
#endif

  if (!((__eax ^ __ebx) & 0x00200000))
    return 0;
#endif

  __cpuid (__ext, __eax, __ebx, __ecx, __edx);

  if (__sig)
    *__sig = __ebx;

  return __eax;
}

static __inline int
__get_cpuid (unsigned int __leaf,
         unsigned int *__eax, unsigned int *__ebx,
         unsigned int *__ecx, unsigned int *__edx)
{
  unsigned int __ext = __leaf & 0x80000000;
  unsigned int __maxlevel = __get_cpuid_max (__ext, 0);

  if (__maxlevel == 0 || __maxlevel < __leaf)
    return 0;

  __cpuid (__leaf, *__eax, *__ebx, *__ecx, *__edx);
  return 1;
}


static __inline int
__get_cpuid_count (unsigned int __leaf, unsigned int __subleaf,
           unsigned int *__eax, unsigned int *__ebx,
           unsigned int *__ecx, unsigned int *__edx)
{
  unsigned int __ext = __leaf & 0x80000000;
  unsigned int __maxlevel = __get_cpuid_max (__ext, 0);

  if (__maxlevel == 0 || __maxlevel < __leaf)
    return 0;

  __cpuid_count (__leaf, __subleaf, *__eax, *__ebx, *__ecx, *__edx);
  return 1;
}

void Architecture::calculateVendorMessage()
{
    unsigned int a,b,c,d,leaf;
    a=b=c=d=leaf=0;
    leaf=0x80000002;
    int error = __get_cpuid(leaf,&a,&b,&c,&d);
    if(!error)
    {
       throw std::runtime_error("Error on executong vendor message");
    }
    QString mes;
    mes.append(registerToMessage(a));
    mes.append(registerToMessage(b));
    mes.append(registerToMessage(c));
    mes.append(registerToMessage(d));
    leaf=0x80000003;
    error = __get_cpuid(leaf,&a,&b,&c,&d);
    if(!error)
    {
       throw std::runtime_error("Error on executing vendor message");
    }
    mes.append(registerToMessage(a));
    mes.append(registerToMessage(b));
    mes.append(registerToMessage(c));
    mes.append(registerToMessage(d));
    leaf=0x80000004;
    error = __get_cpuid(leaf,&a,&b,&c,&d);
    if(!error)
    {
        throw std::runtime_error("Error on executing vendor message");
    }
    mes.append(registerToMessage(a));
    mes.append(registerToMessage(b));
    mes.append(registerToMessage(c));
    mes.append(registerToMessage(d));
    vendorMessage = mes;
}

QString Architecture::getMicroArchitecture()
{
    return microArchitecture;
}

QString Architecture::getCore()
{
    return core;
}

QString Architecture::registerToMessage(unsigned int registerValue)
{
    QString mes;
    unsigned int char0, char1, char2, char3;
    char0 = char1 = char2 = char3 = registerValue;
    char0 = char0 & 0x000000ff;
    char1 = char1 & 0x0000ff00;
    char1 = char1 >> 8;
    char2 = char2 & 0x00ff0000;
    char2 = char2 >> 16;
    char3 = char3 & 0xff000000;
    char3 = char3 >> 24;
    mes[0] = char0;
    mes[1] = char1;
    mes[2] = char2;
    mes[3] = char3;
    return mes;
}

void Architecture::calculateProcToplogy()
{
    unsigned int a,b,c,d,leaf;
    a=b=c=d=leaf=0;
    leaf = 0x01;
    int error = __get_cpuid(leaf,&a,&b,&c,&d);
    if(!error)
    {
        throw std::runtime_error("Error on executing processot topology");
    }
    unsigned int buffer = 0;

    buffer = a;
    buffer = buffer << 4;
    buffer = buffer >> 24;
    extendedFamily = buffer;

    buffer = a;
    buffer = buffer << 12;
    buffer = buffer >>28;
    extendedModel = buffer;

    buffer = a;
    buffer = buffer << 14;
    buffer = buffer >> 30;
    type = buffer;

    buffer = a;
    buffer = buffer << 20;
    buffer = buffer >> 28;
    family = buffer;

    buffer = a;
    buffer = buffer << 24;
    buffer = buffer >> 28;
    model = buffer;

    buffer = a;
    buffer = buffer << 28;
    buffer = buffer >> 28;
    stepping = buffer;
}

void Architecture::calculateCacheInfo()
{
    unsigned int a,b,c,d,leaf, subleaf;
    a=b=c=d=leaf=0;
    leaf = 0x02;

    int error = __get_cpuid(leaf,&a,&b,&c,&d);
    if(!error)
    {
        throw std::runtime_error("Error on executoig cache size");
    }

    unsigned int buffer = b;
    buffer = buffer & 0x000000ff;
    if(buffer == 0xff)
    {
        for(int i=0; i < 4; i++)
        {
            leaf = 0x4;
            subleaf = i;

            int error = __get_cpuid_count(leaf, subleaf,&a,&b,&c,&d);
            if(!error)
            {
                throw std::runtime_error("Error on executoig cache size");
            }

            unsigned int ways, partitions, lineSize, sets, cache;
            ways = partitions = lineSize = b;
            sets = c + 1;

            ways = ways >> 22;
            ways ++;

            partitions = partitions << 10;
            partitions = partitions >> 22;
            partitions ++;

            lineSize = lineSize & 0xfff;
            lineSize ++;

            cache = ways * partitions * lineSize * sets;
            cache ++;

            switch(i)
            {
            case 0:
                L1dataCache = cache;
                break;
            case 1:
                L1instructionCache = cache;
                break;
            case 2:
                L2cache = cache;
                break;
            case 3:
                L3cache = cache;
                break;
            }
        }
    }


}

void Architecture::calculateProcCores()
{
    unsigned int a,b,c,d,leaf, subleaf;
    a=b=c=d=leaf=0;
    leaf = 0x01;

    int error = __get_cpuid(leaf,&a,&b,&c,&d);
    if(!error)
    {
        throw std::runtime_error("Error on executoig proc cores");
    }

    unsigned int corePlusSMTIDMaxCnt;
    corePlusSMTIDMaxCnt = b;
    corePlusSMTIDMaxCnt = corePlusSMTIDMaxCnt & 0x00ff0000;
    corePlusSMTIDMaxCnt = corePlusSMTIDMaxCnt >> 16;

    leaf = 0x04;
    subleaf = 0;

    error = __get_cpuid_count(leaf,subleaf,&a,&b,&c,&d);
    if(!error)
    {
        throw std::runtime_error("Error on executoig proc cores");
    }

    unsigned int coreIDMaxCnt;
    coreIDMaxCnt = a;
    coreIDMaxCnt = coreIDMaxCnt >> 26;
    coreIDMaxCnt ++;

    cores = corePlusSMTIDMaxCnt / coreIDMaxCnt;
}

QString Architecture::getVendorMessage()
{
    return vendorMessage;
}

void Architecture::setMicroArchitecture(QString newMicroArchitecture)
{
    microArchitecture = newMicroArchitecture;
}

void Architecture::setCore(QString newCore)
{
    core = newCore;
}

unsigned int Architecture::getCacheL1DataInfo()
{
    return L1dataCache;
}

unsigned int Architecture::getCacheL1InstructionInfo()
{
    return L1instructionCache;
}

unsigned int Architecture::getCacheL2Info()
{
    return L2cache;
}

unsigned int Architecture::getCacheL3Info()
{
    return L3cache;
}

unsigned int Architecture::getProcCores()
{
    return cores;
}
