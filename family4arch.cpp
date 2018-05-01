#include "family4arch.h"

Family4Arch::Family4Arch()
{

}

bool Family4Arch::mapArchitecture()
{
    if(extendedFamily == 0)
    {
      if(family == 0x4)
      {
          if(extendedModel == 0)
          {
              setMicroArchitecture("80486");
              switch (model) {
              case 0x9:
                  setCore("80486DX4");
                  break;
              case 0x8:
                  setCore("80486DX4");
                  break;
              case 0x7:
                  setCore("80486SL");
                  break;
              case 0x5:
                  setCore("80486SL");
                  break;
              case 0x4:
                  setCore("80486SL");
                  break;
              case 0x3:
                  setCore("80486DX2");
                  break;
              case 0x2:
                  setCore("80486SX");
                  break;
              case 0x1:
                  setCore("80486DX");
                  break;
              default:
                  return false;
                  break;
              }
          } else return false;
      } else return false;
    } else return false;
    return true;
}
