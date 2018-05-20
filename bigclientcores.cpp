#include "bigclientcores.h"

bool BigClientCores::mapArchitecture()
{
    this->calculateProcToplogy();
    if(extendedFamily == 0)
        {
          if(family == 0x6)
          {
              switch (extendedModel) {
              case 0x0:
                  switch (model) {
                  case 0x1:
                      setMicroArchitecture("P6");
                      setCore("Katmai");
                      return true;
                  case 0x3:
                      setMicroArchitecture("P6");
                      setCore("Katmai");
                      return true;
                  case 0x5:
                      setMicroArchitecture("P6");
                      setCore("Katmai");
                      return true;
                  case 0x6:
                      setMicroArchitecture("P6");
                      setCore("Katmai");
                      return true;
                  case 0x7:
                      setMicroArchitecture("P6");
                      setCore("Katmai");
                      return true;
                  case 0x8:
                      setMicroArchitecture("P6");
                      setCore("Coppermine");
                      return true;
                  case 0xb:
                      setMicroArchitecture("P6");
                      setCore("Tualatin");
                      return true;
                  case 0x9:
                      setMicroArchitecture("Pentium");
                      setCore("Banias");
                      return true;
                  case 0xd:
                      setMicroArchitecture("Pentium");
                      setCore("Dothan");
                      return true;
                  case 0xe:
                      setMicroArchitecture("Pentium M");
                      setCore("Yonah");
                      return true;
                  case 0xf:
                      setMicroArchitecture("Core");
                      setCore("Merom");
                      return true;
                  default:
                      break;
                  }
              case 0x1:
                  switch (model) {
                  case 0x5:
                      setMicroArchitecture("Pentium M");
                      setCore("Tolapai");
                      return true;
                  case 0x6:
                      setMicroArchitecture("Core");
                      setCore("Merom L");
                      return true;
                  case 0x7:
                      setMicroArchitecture("Penryn");
                      setCore("Wolfdale");
                      return true;
                  case 0xe:
                      setMicroArchitecture("Nehalem");
                      setCore("Clarksfield");
                      return true;
                  case 0xf:
                      setMicroArchitecture("Nehalem");
                      setCore("Havendale");
                      return true;
                  default:
                      break;
                  }
              case 0x2:
                  switch (model) {
                  case 0x5:
                      setMicroArchitecture("Westmare");
                      setCore("Banias");
                      return true;
                  case 0xa:
                      setMicroArchitecture("Sandy Bridge");
                      setCore("M");
                      return true;
                  default:
                      break;
                  }
              case 0x3:
                  switch (model) {
                  case 0xa:
                      setMicroArchitecture("Ivy Bridge");
                      setCore("M");
                      return true;
                  case 0xc:
                      setMicroArchitecture("Haswell");
                      setCore("S");
                      return true;
                  case 0xd:
                      setMicroArchitecture("Broadwell");
                      setCore("U");
                      return true;
                  default:
                      break;
                  }
                  break;
              case 0x4:
                  switch (model) {
                  case 0x5:
                      setMicroArchitecture("Haswell");
                      setCore("ULT");
                      return true;
                  case 0x6:
                      setMicroArchitecture("Haswell");
                      setCore("GT3E");
                      return true;
                  case 0x7:
                      setMicroArchitecture("Broadwell");
                      setCore("C");
                      return true;
                  case 0xe:
                      setMicroArchitecture("Skylake");
                      setCore("Y");
                      return true;
                  default:
                      break;
                  }
              case 0x5:
                  if(model == 0xe)
                  {
                      setMicroArchitecture("Skylake");
                      setCore("DT");
                      return true;
                  }
              case 0x8:
                  if(model == 0xe)
                  {
                      setMicroArchitecture("Kaby Lake");
                      setCore("Y");
                      return true;
                  }
              case 0x9:
                  if(model == 0xe)
                  {
                      setMicroArchitecture("Kaby Lake");
                      setCore("DT");
                      return true;
                  }
              default:
                  break;
              }
          }return false;
    }
}
