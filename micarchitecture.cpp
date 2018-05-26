#include "micarchitecture.h"

bool MICArchitecture::mapArchitecture()
{
    if(extendedFamily == 0)
    {
      if(family == 0x6)
      {
          if(extendedModel == 0X8)
          {
              if(model == 0x5)
              {
                  setMicroArchitecture("Knights Mill");
                  setCore("KM");
                  return true;
              }
          }
          if(extendedModel == 0x5)
          {
              if(model == 0x7)
              {
                  setMicroArchitecture("Knights Landing");
                  setCore("KL");
                  return true;
              }
          }
      }
    }
    return false;
}

